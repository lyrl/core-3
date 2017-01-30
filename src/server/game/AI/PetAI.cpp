
#include "PetAI.h"
#include "Errors.h"
#include "Pet.h"
#include "Player.h"
#include "DBCStores.h"
#include "Spell.h"
#include "ObjectAccessor.h"
#include "SpellMgr.h"
#include "Creature.h"
#include "World.h"
#include "Util.h"

int PetAI::Permissible(const Creature *creature)
{
    if( creature->IsPet())
        return PERMIT_BASE_SPECIAL;

    return PERMIT_BASE_NO;
}

PetAI::PetAI(Creature *c) : CreatureAI(c), i_pet(*c), i_tracker(TIME_INTERVAL_LOOK), distanceCheckTimer(3000)
{
    m_AllySet.clear();
    UpdateAllies();
}

void PetAI::EnterEvadeMode(EvadeReason why)
{
}

bool PetAI::_needToStop() const
{
    // This is needed for charmed creatures, as once their target was reset other effects can trigger threat
    if(i_pet.IsCharmed() && i_pet.GetVictim() == i_pet.GetCharmer())
        return true;

    if (i_pet.GetOwner() && i_pet.GetOwner()->ToPlayer() && i_pet.ToPet() && i_pet.ToPet()->isControlled() && i_pet.GetVictim()->IsJustCCed() && i_pet.GetVictim()->GetEntry() != 10) // Training dummy exception
        return true;

    if (i_pet.IsNonMeleeSpellCast(false))
        return true;

    // dont allow pets to follow targets far away from owner
    if (Unit* owner = me->GetCharmerOrOwner())
        if (owner->GetExactDist(me) >= (owner->GetVisibilityRange() - 10.0f))
            return true;

    return i_pet.CanAttack(i_pet.GetVictim()) != CAN_ATTACK_RESULT_OK;
}

void PetAI::ResetMovement()
{
    Unit* owner = i_pet.GetCharmerOrOwner();

    if(owner && i_pet.IsAlive() && i_pet.GetCharmInfo() && i_pet.GetCharmInfo()->HasCommandState(COMMAND_FOLLOW))
    {
        i_pet.GetMotionMaster()->MoveFollow(owner,PET_FOLLOW_DIST,owner->GetFollowAngle());
    }
    else
    {
        i_pet.ClearUnitState(UNIT_STATE_FOLLOW);
        i_pet.GetMotionMaster()->Clear();
        i_pet.GetMotionMaster()->MoveIdle();
    }
}
void PetAI::_stopAttack()
{
    if( !i_pet.IsAlive() )
        i_pet.GetHostileRefManager().deleteReferences();

    ResetMovement();
    i_pet.CombatStop();
}

void PetAI::UpdateAI(const uint32 diff)
{
    if (!i_pet.IsAlive())
        return;

    Unit* owner = i_pet.GetCharmerOrOwner();

    if(m_updateAlliesTimer <= diff)
        // UpdateAllies self set update timer
        UpdateAllies();
    else
        m_updateAlliesTimer -= diff;

    // i_pet.GetVictim() can't be used for check in case stop fighting, i_pet.GetVictim() clear at Unit death etc.
    if( i_pet.GetVictim() )
    {
        // is only necessary to stop casting, the pet must not exit combat
        if (!me->GetCurrentSpell(CURRENT_CHANNELED_SPELL) && // ignore channeled spells (Pin, Seduction)
            me->EnsureVictim()->HasBreakableByDamageCrowdControlAura(me))
        {
            me->InterruptNonMeleeSpells(false);
            return;
        }

        if( _needToStop() )
        {
            //TC_LOG_DEBUG("entities.pet","Pet AI stopped attacking [guid=%u]", i_pet.GetGUIDLow());
            _stopAttack();
            return;
        }

        DoMeleeAttackIfReady();
    }
    else
    {
        if(!i_pet.IsNonMeleeSpellCast(false))
        {
            if(i_pet.IsInCombat() && i_pet.GetAttackers().empty())
            {
               _stopAttack();
            } else if(owner && i_pet.GetCharmInfo()) //no victim
            {
                if(owner->IsInCombat() && !(i_pet.HasReactState(REACT_PASSIVE) || i_pet.GetCharmInfo()->HasCommandState(COMMAND_STAY))) {
                    AttackStart(owner->GetAttackerForHelper());
                }
                else if(i_pet.GetCharmInfo()->HasCommandState(COMMAND_FOLLOW) && !i_pet.HasUnitState(UNIT_STATE_FOLLOW))
                    i_pet.GetMotionMaster()->MoveFollow(owner, PET_FOLLOW_DIST, i_pet.GetFollowAngle());
            }
        }
    }

    if(!me->GetCharmInfo())
        return;

    if (i_pet.GetGlobalCooldown() == 0 && !i_pet.HasUnitState(UNIT_STATE_CASTING))
    {
        bool inCombat = me->GetVictim();

        //Autocast
        for (uint8 i = 0; i < i_pet.GetPetAutoSpellSize(); i++)
        {
            uint32 spellID = i_pet.GetPetAutoSpellOnPos(i);
            if (!spellID)
                continue;

            SpellInfo const *spellInfo = sSpellMgr->GetSpellInfo(spellID);
            if (!spellInfo)
                continue;

            // ignore some combinations of combat state and combat/noncombat spells
            if (!inCombat)
            {
                if (!spellInfo->IsPositive())
                    continue;
            }
            else
            {
                if (!spellInfo->CanBeUsedInCombat())
                    continue;
            }

            auto spell = new Spell(&i_pet, spellInfo, false, 0);

            if(inCombat && !i_pet.HasUnitState(UNIT_STATE_FOLLOW) && spell->CanAutoCast(i_pet.GetVictim()))
            {
                //m_targetSpellStore.push_back(std::make_pair<Unit*, Spell*>(i_pet.GetVictim(), spell));
                m_targetSpellStore.push_back(std::make_pair(i_pet.GetVictim(), spell));
                continue;
            }
            else
            {
                bool spellUsed = false;
                for(uint64 tar : m_AllySet)
                {
                    Unit* Target = ObjectAccessor::GetUnit(i_pet,tar);

                    //only buff targets that are in combat, unless the spell can only be cast while out of combat
                    if(!Target)
                        continue;

                    if(spell->CanAutoCast(Target))
                    {
                        //m_targetSpellStore.push_back(std::make_pair<Unit*, Spell*>(Target, spell));
                        m_targetSpellStore.push_back(std::make_pair(Target, spell));
                        spellUsed = true;
                        break;
                    }
                }
                if (!spellUsed)
                    delete spell;
            }
        }

        //found units to cast on to
        if(!m_targetSpellStore.empty())
        {
            uint32 index = urand(0, m_targetSpellStore.size() - 1);

            Spell* spell  = m_targetSpellStore[index].second;
            Unit*  target = m_targetSpellStore[index].first;

            m_targetSpellStore.erase(m_targetSpellStore.begin() + index);

            SpellCastTargets targets;
            targets.SetUnitTarget( target );

            if( !i_pet.HasInArc(M_PI, target) )
            {
                i_pet.SetInFront(target);
                if( target->GetTypeId() == TYPEID_PLAYER )
                    i_pet.SendUpdateToPlayer( target->ToPlayer() );

                if(owner && owner->GetTypeId() == TYPEID_PLAYER)
                    i_pet.SendUpdateToPlayer( owner->ToPlayer() );
            }

            if(i_pet.IsPet())
                ((Pet*)&i_pet)->CheckLearning(spell->m_spellInfo->Id);

            spell->prepare(&targets);
        }
        while (!m_targetSpellStore.empty())
        {
            delete m_targetSpellStore.begin()->second;
            m_targetSpellStore.erase(m_targetSpellStore.begin());
        }

        if(i_pet.IsPet() && ((Pet*)&i_pet)->getPetType() == MINI_PET)
        {
            Minipet_DistanceCheck(diff);
        }
    }
}

void PetAI::UpdateAllies()
{
    Unit* owner = i_pet.GetCharmerOrOwner();
    Group *pGroup = nullptr;

    m_updateAlliesTimer = 10000;                            //update friendly targets every 10 seconds, lesser checks increase performance

    if(!owner)
        return;
    else if(owner->GetTypeId() == TYPEID_PLAYER)
        pGroup = (owner->ToPlayer())->GetGroup();

    //only pet and owner/not in group->ok
    if(m_AllySet.size() == 2 && !pGroup)
        return;
    //owner is in group; group members filled in already (no raid -> subgroupcount = whole count)
    if(pGroup && !pGroup->isRaidGroup() && m_AllySet.size() == (pGroup->GetMembersCount() + 2))
        return;

    m_AllySet.clear();
    m_AllySet.insert(i_pet.GetGUID());
    if(pGroup)                                              //add group
    {
        for(GroupReference *itr = pGroup->GetFirstMember(); itr != nullptr; itr = itr->next())
        {
            Player* Target = itr->GetSource();
            if(!Target || !pGroup->SameSubGroup(owner->ToPlayer(), Target))
                continue;

            if(Target->GetGUID() == owner->GetGUID())
                continue;

            m_AllySet.insert(Target->GetGUID());
        }
    }
    else                                                    //remove group
        m_AllySet.insert(owner->GetGUID());
}

void PetAI::Minipet_DistanceCheck(uint32 diff)
{
    Unit* owner = me->GetOwner();
    if (!owner)
        return;
    if (distanceCheckTimer <= diff)
    {
        distanceCheckTimer = 2000;
        float masterSpeed = owner->GetSpeed(MOVE_RUN);
        float masterSpeedRate = masterSpeed / baseMoveSpeed[MOVE_RUN];
        float masterDistance = me->GetDistance(owner);
        if(masterDistance >= 20)
        {
            me->SetSpeedRate(MOVE_RUN, masterSpeedRate * (masterDistance / 15.f));
        } else if (me->GetSpeed(MOVE_RUN) > masterSpeed) {
            me->SetSpeedRate(MOVE_RUN, masterSpeedRate);
        }
    } else distanceCheckTimer -= diff;
}