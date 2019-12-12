/*
 * Copyright (C) 2008-2019 TrinityCore <https://www.trinitycore.org/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/* ContentData
go_cat_figurine (the "trap" version of GO, two different exist)
go_barov_journal
go_ethereum_prison
go_ethereum_stasis
go_sacred_fire_of_life
go_shrine_of_the_birds
go_southfury_moonstone
go_orb_of_command
go_resonite_cask
go_tablet_of_madness
go_tablet_of_the_seven
go_tele_to_dalaran_crystal
go_tele_to_violet_stand
go_scourge_cage
go_jotunheim_cage
go_table_theka
go_soulwell
go_bashir_crystalforge
go_soulwell
go_dragonflayer_cage
go_amberpine_outhouse
go_hive_pod
go_veil_skith_cage
go_toy_train_set
go_bells
EndContentData */

#include "ScriptMgr.h"
#include "DBCStructure.h"
#include "GameEventMgr.h"
#include "GameObject.h"
#include "GameObjectAI.h"
#include "GameTime.h"
#include "Log.h"
#include "MotionMaster.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "Spell.h"
#include "SpellInfo.h"
#include "SpellMgr.h"
#include "TemporarySummon.h"
#include "WorldSession.h"

/*######
## go_cat_figurine
######*/

enum CatFigurine
{
    SPELL_SUMMON_GHOST_SABER    = 5968,
};

class go_cat_figurine : public GameObjectScript
{
public:
    go_cat_figurine() : GameObjectScript("go_cat_figurine") { }

    struct go_cat_figurineAI : public GameObjectAI
    {
        go_cat_figurineAI(GameObject* go) : GameObjectAI(go) { }

        bool GossipHello(Player* player) override
        {
            player->CastSpell(player, SPELL_SUMMON_GHOST_SABER, true);
            return false;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_cat_figurineAI(go);
    }
};

/*######
## go_barov_journal
######*/

class go_barov_journal : public GameObjectScript
{
public:
    go_barov_journal() : GameObjectScript("go_barov_journal") { }

    struct go_barov_journalAI : public GameObjectAI
    {
        go_barov_journalAI(GameObject* go) : GameObjectAI(go) { }

        bool GossipHello(Player* player) override
        {
            if (player->HasSkill(SKILL_TAILORING) && player->GetBaseSkillValue(SKILL_TAILORING) >= 280 && !player->HasSpell(26086))
                player->CastSpell(player, 26095, false);

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_barov_journalAI(go);
    }
};

/*######
## go_gilded_brazier (Paladin First Trail quest (9678))
######*/

enum GildedBrazier
{
    NPC_STILLBLADE        = 17716,
    QUEST_THE_FIRST_TRIAL = 9678
};

class go_gilded_brazier : public GameObjectScript
{
public:
    go_gilded_brazier() : GameObjectScript("go_gilded_brazier") { }

    struct go_gilded_brazierAI : public GameObjectAI
    {
        go_gilded_brazierAI(GameObject* go) : GameObjectAI(go) { }

        bool GossipHello(Player* player) override
        {
            if (me->GetGoType() == GAMEOBJECT_TYPE_GOOBER)
            {
                if (player->GetQuestStatus(QUEST_THE_FIRST_TRIAL) == QUEST_STATUS_INCOMPLETE)
                {
                    if (Creature* Stillblade = player->SummonCreature(NPC_STILLBLADE, 8106.11f, -7542.06f, 151.775f, 3.02598f, TEMPSUMMON_DEAD_DESPAWN, 60000))
                        Stillblade->AI()->AttackStart(player);
                }
            }
            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_gilded_brazierAI(go);
    }
};

/*######
## go_orb_of_command
######*/

class go_orb_of_command : public GameObjectScript
{
public:
    go_orb_of_command() : GameObjectScript("go_orb_of_command") { }

    struct go_orb_of_commandAI : public GameObjectAI
    {
        go_orb_of_commandAI(GameObject* go) : GameObjectAI(go) { }

        bool GossipHello(Player* player) override
        {
            if (player->GetQuestRewardStatus(7761))
                player->CastSpell(player, 23460, true);

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_orb_of_commandAI(go);
    }
};

/*######
## go_tablet_of_madness
######*/

class go_tablet_of_madness : public GameObjectScript
{
public:
    go_tablet_of_madness() : GameObjectScript("go_tablet_of_madness") { }

    struct go_tablet_of_madnessAI : public GameObjectAI
    {
        go_tablet_of_madnessAI(GameObject* go) : GameObjectAI(go) { }

        bool GossipHello(Player* player) override
        {
            if (player->HasSkill(SKILL_ALCHEMY) && player->GetSkillValue(SKILL_ALCHEMY) >= 300 && !player->HasSpell(24266))
                player->CastSpell(player, 24267, false);

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_tablet_of_madnessAI(go);
    }
};

/*######
## go_tablet_of_the_seven
######*/

class go_tablet_of_the_seven : public GameObjectScript
{
public:
    go_tablet_of_the_seven() : GameObjectScript("go_tablet_of_the_seven") { }

    struct go_tablet_of_the_sevenAI : public GameObjectAI
    {
        go_tablet_of_the_sevenAI(GameObject* go) : GameObjectAI(go) { }

        /// @todo use gossip option ("Transcript the Tablet") instead, if Trinity adds support.
        bool GossipHello(Player* player) override
        {
            if (me->GetGoType() != GAMEOBJECT_TYPE_QUESTGIVER)
                return true;

            if (player->GetQuestStatus(4296) == QUEST_STATUS_INCOMPLETE)
                player->CastSpell(player, 15065, false);

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_tablet_of_the_sevenAI(go);
    }
};

/*#####
## go_jump_a_tron
######*/

class go_jump_a_tron : public GameObjectScript
{
public:
    go_jump_a_tron() : GameObjectScript("go_jump_a_tron") { }

    struct go_jump_a_tronAI : public GameObjectAI
    {
        go_jump_a_tronAI(GameObject* go) : GameObjectAI(go) { }

        bool GossipHello(Player* player) override
        {
            if (player->GetQuestStatus(10111) == QUEST_STATUS_INCOMPLETE)
                player->CastSpell(player, 33382, true);

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_jump_a_tronAI(go);
    }
};

/*######
## go_ethereum_prison
######*/

enum EthereumPrison
{
    SPELL_REP_LC        = 39456,
    SPELL_REP_SHAT      = 39457,
    SPELL_REP_CE        = 39460,
    SPELL_REP_CON       = 39474,
    SPELL_REP_KT        = 39475,
    SPELL_REP_SPOR      = 39476
};

const uint32 NpcPrisonEntry[] =
{
    22810, 22811, 22812, 22813, 22814, 22815,               //good guys
    20783, 20784, 20785, 20786, 20788, 20789, 20790         //bad guys
};

class go_ethereum_prison : public GameObjectScript
{
public:
    go_ethereum_prison() : GameObjectScript("go_ethereum_prison") { }

    struct go_ethereum_prisonAI : public GameObjectAI
    {
        go_ethereum_prisonAI(GameObject* go) : GameObjectAI(go) { }

        bool GossipHello(Player* player) override
        {
            me->UseDoorOrButton();
            int Random = rand32() % (sizeof(NpcPrisonEntry) / sizeof(uint32));

            if (Creature* creature = player->SummonCreature(NpcPrisonEntry[Random], me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetAbsoluteAngle(player),
                TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000))
            {
                if (!creature->IsHostileTo(player))
                {
                    if (FactionTemplateEntry const* pFaction = creature->GetFactionTemplateEntry())
                    {
                        uint32 Spell = 0;

                        switch (pFaction->faction)
                        {
                            case 1011: Spell = SPELL_REP_LC; break;
                            case 935: Spell = SPELL_REP_SHAT; break;
                            case 942: Spell = SPELL_REP_CE; break;
                            case 933: Spell = SPELL_REP_CON; break;
                            case 989: Spell = SPELL_REP_KT; break;
                            case 970: Spell = SPELL_REP_SPOR; break;
                        }

                        if (Spell)
                            creature->CastSpell(player, Spell, false);
                        else
                            TC_LOG_ERROR("scripts", "go_ethereum_prison summoned Creature (entry %u) but faction (%u) are not expected by script.", creature->GetEntry(), creature->GetFaction());
                    }
                }
            }

            return false;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_ethereum_prisonAI(go);
    }
};

/*######
## go_ethereum_stasis
######*/

const uint32 NpcStasisEntry[] =
{
    22825, 20888, 22827, 22826, 22828
};

class go_ethereum_stasis : public GameObjectScript
{
public:
    go_ethereum_stasis() : GameObjectScript("go_ethereum_stasis") { }

    struct go_ethereum_stasisAI : public GameObjectAI
    {
        go_ethereum_stasisAI(GameObject* go) : GameObjectAI(go) { }

        bool GossipHello(Player* player) override
        {
            me->UseDoorOrButton();
            int Random = rand32() % (sizeof(NpcStasisEntry) / sizeof(uint32));

            player->SummonCreature(NpcStasisEntry[Random], me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetAbsoluteAngle(player),
                TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);

            return false;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_ethereum_stasisAI(go);
    }
};

/*######
## go_resonite_cask
######*/

enum ResoniteCask
{
    NPC_GOGGEROC    = 11920
};

class go_resonite_cask : public GameObjectScript
{
public:
    go_resonite_cask() : GameObjectScript("go_resonite_cask") { }

    struct go_resonite_caskAI : public GameObjectAI
    {
        go_resonite_caskAI(GameObject* go) : GameObjectAI(go) { }

        bool GossipHello(Player* /*player*/) override
        {
            if (me->GetGoType() == GAMEOBJECT_TYPE_GOOBER)
                me->SummonCreature(NPC_GOGGEROC, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 300000);

            return false;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_resonite_caskAI(go);
    }
};

/*######
## go_sacred_fire_of_life
######*/

enum SacredFireOfLife
{
    NPC_ARIKARA     = 10882
};

class go_sacred_fire_of_life : public GameObjectScript
{
public:
    go_sacred_fire_of_life() : GameObjectScript("go_sacred_fire_of_life") { }

    struct go_sacred_fire_of_lifeAI : public GameObjectAI
    {
        go_sacred_fire_of_lifeAI(GameObject* go) : GameObjectAI(go) { }

        bool GossipHello(Player* player) override
        {
            if (me->GetGoType() == GAMEOBJECT_TYPE_GOOBER)
                player->SummonCreature(NPC_ARIKARA, -5008.338f, -2118.894f, 83.657f, 0.874f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_sacred_fire_of_lifeAI(go);
    }
};

/*######
## go_shrine_of_the_birds
######*/

enum ShrineOfTheBirds
{
    NPC_HAWK_GUARD      = 22992,
    NPC_EAGLE_GUARD     = 22993,
    NPC_FALCON_GUARD    = 22994,
    GO_SHRINE_HAWK      = 185551,
    GO_SHRINE_EAGLE     = 185547,
    GO_SHRINE_FALCON    = 185553
};

class go_shrine_of_the_birds : public GameObjectScript
{
public:
    go_shrine_of_the_birds() : GameObjectScript("go_shrine_of_the_birds") { }

    struct go_shrine_of_the_birdsAI : public GameObjectAI
    {
        go_shrine_of_the_birdsAI(GameObject* go) : GameObjectAI(go) { }

        bool GossipHello(Player* player) override
        {
            uint32 BirdEntry = 0;

            float fX, fY, fZ;
            me->GetClosePoint(fX, fY, fZ, me->GetCombatReach(), INTERACTION_DISTANCE);

            switch (me->GetEntry())
            {
                case GO_SHRINE_HAWK:
                    BirdEntry = NPC_HAWK_GUARD;
                    break;
                case GO_SHRINE_EAGLE:
                    BirdEntry = NPC_EAGLE_GUARD;
                    break;
                case GO_SHRINE_FALCON:
                    BirdEntry = NPC_FALCON_GUARD;
                    break;
            }

            if (BirdEntry)
                player->SummonCreature(BirdEntry, fX, fY, fZ, me->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);

            return false;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_shrine_of_the_birdsAI(go);
    }
};

/*######
## go_southfury_moonstone
######*/

enum Southfury
{
    NPC_RIZZLE                  = 23002,
    SPELL_BLACKJACK             = 39865, //stuns player
    SPELL_SUMMON_RIZZLE         = 39866
};

class go_southfury_moonstone : public GameObjectScript
{
public:
    go_southfury_moonstone() : GameObjectScript("go_southfury_moonstone") { }

    struct go_southfury_moonstoneAI : public GameObjectAI
    {
        go_southfury_moonstoneAI(GameObject* go) : GameObjectAI(go) { }

        bool GossipHello(Player* player) override
        {
            //implicitTarget=48 not implemented as of writing this code, and manual summon may be just ok for our purpose
            //player->CastSpell(player, SPELL_SUMMON_RIZZLE, false);

            if (Creature* creature = player->SummonCreature(NPC_RIZZLE, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_DEAD_DESPAWN, 0))
                creature->CastSpell(player, SPELL_BLACKJACK, false);

            return false;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_southfury_moonstoneAI(go);
    }
};

/*######
## go_fel_crystalforge
######*/

#define GOSSIP_FEL_CRYSTALFORGE_TEXT 31000
#define GOSSIP_FEL_CRYSTALFORGE_ITEM_TEXT_RETURN 31001
#define GOSSIP_FEL_CRYSTALFORGE_ITEM_1 "Purchase 1 Unstable Flask of the Beast for the cost of 10 Apexis Shards"
#define GOSSIP_FEL_CRYSTALFORGE_ITEM_5 "Purchase 5 Unstable Flask of the Beast for the cost of 50 Apexis Shards"
#define GOSSIP_FEL_CRYSTALFORGE_ITEM_RETURN "Use the fel crystalforge to make another purchase."

enum FelCrystalforge
{
    SPELL_CREATE_1_FLASK_OF_BEAST   = 40964,
    SPELL_CREATE_5_FLASK_OF_BEAST   = 40965,
};

class go_fel_crystalforge : public GameObjectScript
{
public:
    go_fel_crystalforge() : GameObjectScript("go_fel_crystalforge") { }

    struct go_fel_crystalforgeAI : public GameObjectAI
    {
        go_fel_crystalforgeAI(GameObject* go) : GameObjectAI(go) { }

        bool GossipHello(Player* player) override
        {
            if (me->GetGoType() == GAMEOBJECT_TYPE_QUESTGIVER) /* != GAMEOBJECT_TYPE_QUESTGIVER) */
                player->PrepareQuestMenu(me->GetGUID()); /* return true*/

            AddGossipItemFor(player, GOSSIP_ICON_CHAT, GOSSIP_FEL_CRYSTALFORGE_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, GOSSIP_FEL_CRYSTALFORGE_ITEM_5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

            SendGossipMenuFor(player, GOSSIP_FEL_CRYSTALFORGE_TEXT, me->GetGUID());

            return true;
        }

        bool GossipSelect(Player* player, uint32 /*menuId*/, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);
            switch (action)
            {
                case GOSSIP_ACTION_INFO_DEF:
                    player->CastSpell(player, SPELL_CREATE_1_FLASK_OF_BEAST, false);
                    AddGossipItemFor(player, GOSSIP_ICON_CHAT, GOSSIP_FEL_CRYSTALFORGE_ITEM_RETURN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    SendGossipMenuFor(player, GOSSIP_FEL_CRYSTALFORGE_ITEM_TEXT_RETURN, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF + 1:
                    player->CastSpell(player, SPELL_CREATE_5_FLASK_OF_BEAST, false);
                    AddGossipItemFor(player, GOSSIP_ICON_CHAT, GOSSIP_FEL_CRYSTALFORGE_ITEM_RETURN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    SendGossipMenuFor(player, GOSSIP_FEL_CRYSTALFORGE_ITEM_TEXT_RETURN, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF + 2:
                    AddGossipItemFor(player, GOSSIP_ICON_CHAT, GOSSIP_FEL_CRYSTALFORGE_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                    AddGossipItemFor(player, GOSSIP_ICON_CHAT, GOSSIP_FEL_CRYSTALFORGE_ITEM_5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                    SendGossipMenuFor(player, GOSSIP_FEL_CRYSTALFORGE_TEXT, me->GetGUID());
                    break;
            }
            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_fel_crystalforgeAI(go);
    }
};

/*######
## go_bashir_crystalforge
######*/

#define GOSSIP_BASHIR_CRYSTALFORGE_TEXT 31100
#define GOSSIP_BASHIR_CRYSTALFORGE_ITEM_TEXT_RETURN 31101
#define GOSSIP_BASHIR_CRYSTALFORGE_ITEM_1 "Purchase 1 Unstable Flask of the Sorcerer for the cost of 10 Apexis Shards"
#define GOSSIP_BASHIR_CRYSTALFORGE_ITEM_5 "Purchase 5 Unstable Flask of the Sorcerer for the cost of 50 Apexis Shards"
#define GOSSIP_BASHIR_CRYSTALFORGE_ITEM_RETURN "Use the bashir crystalforge to make another purchase."

enum BashirCrystalforge
{
    SPELL_CREATE_1_FLASK_OF_SORCERER   = 40968,
    SPELL_CREATE_5_FLASK_OF_SORCERER   = 40970,
};

class go_bashir_crystalforge : public GameObjectScript
{
public:
    go_bashir_crystalforge() : GameObjectScript("go_bashir_crystalforge") { }

    struct go_bashir_crystalforgeAI : public GameObjectAI
    {
        go_bashir_crystalforgeAI(GameObject* go) : GameObjectAI(go) { }

        bool GossipHello(Player* player) override
        {
            if (me->GetGoType() == GAMEOBJECT_TYPE_QUESTGIVER) /* != GAMEOBJECT_TYPE_QUESTGIVER) */
                player->PrepareQuestMenu(me->GetGUID()); /* return true*/

            AddGossipItemFor(player, GOSSIP_ICON_CHAT, GOSSIP_BASHIR_CRYSTALFORGE_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, GOSSIP_BASHIR_CRYSTALFORGE_ITEM_5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

            SendGossipMenuFor(player, GOSSIP_BASHIR_CRYSTALFORGE_TEXT, me->GetGUID());

            return true;
        }

        bool GossipSelect(Player* player, uint32 /*menuId*/, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);
            switch (action)
            {
                case GOSSIP_ACTION_INFO_DEF:
                    player->CastSpell(player, SPELL_CREATE_1_FLASK_OF_SORCERER, false);
                    AddGossipItemFor(player, GOSSIP_ICON_CHAT, GOSSIP_BASHIR_CRYSTALFORGE_ITEM_RETURN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    SendGossipMenuFor(player, GOSSIP_BASHIR_CRYSTALFORGE_ITEM_TEXT_RETURN, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF + 1:
                    player->CastSpell(player, SPELL_CREATE_5_FLASK_OF_SORCERER, false);
                    AddGossipItemFor(player, GOSSIP_ICON_CHAT, GOSSIP_BASHIR_CRYSTALFORGE_ITEM_RETURN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    SendGossipMenuFor(player, GOSSIP_BASHIR_CRYSTALFORGE_ITEM_TEXT_RETURN, me->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF + 2:
                    AddGossipItemFor(player, GOSSIP_ICON_CHAT, GOSSIP_BASHIR_CRYSTALFORGE_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                    AddGossipItemFor(player, GOSSIP_ICON_CHAT, GOSSIP_BASHIR_CRYSTALFORGE_ITEM_5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                    SendGossipMenuFor(player, GOSSIP_BASHIR_CRYSTALFORGE_TEXT, me->GetGUID());
                    break;
            }
            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_bashir_crystalforgeAI(go);
    }
};

/*######
## matrix_punchograph
######*/

enum MatrixPunchograph
{
    ITEM_WHITE_PUNCH_CARD = 9279,
    ITEM_YELLOW_PUNCH_CARD = 9280,
    ITEM_BLUE_PUNCH_CARD = 9282,
    ITEM_RED_PUNCH_CARD = 9281,
    ITEM_PRISMATIC_PUNCH_CARD = 9316,
    SPELL_YELLOW_PUNCH_CARD = 11512,
    SPELL_BLUE_PUNCH_CARD = 11525,
    SPELL_RED_PUNCH_CARD = 11528,
    SPELL_PRISMATIC_PUNCH_CARD = 11545,
    MATRIX_PUNCHOGRAPH_3005_A = 142345,
    MATRIX_PUNCHOGRAPH_3005_B = 142475,
    MATRIX_PUNCHOGRAPH_3005_C = 142476,
    MATRIX_PUNCHOGRAPH_3005_D = 142696,
};

class go_matrix_punchograph : public GameObjectScript
{
public:
    go_matrix_punchograph() : GameObjectScript("go_matrix_punchograph") { }

    struct go_matrix_punchographAI : public GameObjectAI
    {
        go_matrix_punchographAI(GameObject* go) : GameObjectAI(go) { }

        bool GossipHello(Player* player) override
        {
            switch (me->GetEntry())
            {
                case MATRIX_PUNCHOGRAPH_3005_A:
                    if (player->HasItemCount(ITEM_WHITE_PUNCH_CARD))
                    {
                        player->DestroyItemCount(ITEM_WHITE_PUNCH_CARD, 1, true);
                        player->CastSpell(player, SPELL_YELLOW_PUNCH_CARD, true);
                    }
                    break;
                case MATRIX_PUNCHOGRAPH_3005_B:
                    if (player->HasItemCount(ITEM_YELLOW_PUNCH_CARD))
                    {
                        player->DestroyItemCount(ITEM_YELLOW_PUNCH_CARD, 1, true);
                        player->CastSpell(player, SPELL_BLUE_PUNCH_CARD, true);
                    }
                    break;
                case MATRIX_PUNCHOGRAPH_3005_C:
                    if (player->HasItemCount(ITEM_BLUE_PUNCH_CARD))
                    {
                        player->DestroyItemCount(ITEM_BLUE_PUNCH_CARD, 1, true);
                        player->CastSpell(player, SPELL_RED_PUNCH_CARD, true);
                    }
                    break;
                case MATRIX_PUNCHOGRAPH_3005_D:
                    if (player->HasItemCount(ITEM_RED_PUNCH_CARD))
                    {
                        player->DestroyItemCount(ITEM_RED_PUNCH_CARD, 1, true);
                        player->CastSpell(player, SPELL_PRISMATIC_PUNCH_CARD, true);
                    }
                    break;
                default:
                    break;
            }
            return false;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_matrix_punchographAI(go);
    }
};

/*######
## go_blood_filled_orb
######*/

enum BloodFilledOrb
{
    NPC_ZELEMAR     = 17830

};

class go_blood_filled_orb : public GameObjectScript
{
public:
    go_blood_filled_orb() : GameObjectScript("go_blood_filled_orb") { }

    struct go_blood_filled_orbAI : public GameObjectAI
    {
        go_blood_filled_orbAI(GameObject* go) : GameObjectAI(go) { }

        bool GossipHello(Player* player) override
        {
            if (me->GetGoType() == GAMEOBJECT_TYPE_GOOBER)
                player->SummonCreature(NPC_ZELEMAR, -369.746f, 166.759f, -21.50f, 5.235f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);

            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_blood_filled_orbAI(go);
    }
};

enum TableTheka
{
    GOSSIP_TABLE_THEKA = 1653,

    QUEST_SPIDER_GOLD = 2936
};

class go_table_theka : public GameObjectScript
{
public:
    go_table_theka() : GameObjectScript("go_table_theka") { }

    struct go_table_thekaAI : public GameObjectAI
    {
        go_table_thekaAI(GameObject* go) : GameObjectAI(go) { }

        bool GossipHello(Player* player) override
        {
            if (player->GetQuestStatus(QUEST_SPIDER_GOLD) == QUEST_STATUS_INCOMPLETE)
                player->AreaExploredOrEventHappens(QUEST_SPIDER_GOLD);

            SendGossipMenuFor(player, GOSSIP_TABLE_THEKA, me->GetGUID());
            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_table_thekaAI(go);
    }
};

/*######
## go_inconspicuous_landmark
######*/

enum InconspicuousLandmark
{
    SPELL_SUMMON_PIRATES_TREASURE_AND_TRIGGER_MOB    = 11462,
    ITEM_CUERGOS_KEY                                 = 9275,
};

class go_inconspicuous_landmark : public GameObjectScript
{
public:
    go_inconspicuous_landmark() : GameObjectScript("go_inconspicuous_landmark") { }

    struct go_inconspicuous_landmarkAI : public GameObjectAI
    {
        go_inconspicuous_landmarkAI(GameObject* go) : GameObjectAI(go) { }

        bool GossipHello(Player* player) override
        {
            if (player->HasItemCount(ITEM_CUERGOS_KEY))
                return false;

            player->CastSpell(player, SPELL_SUMMON_PIRATES_TREASURE_AND_TRIGGER_MOB, true);
            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_inconspicuous_landmarkAI(go);
    }
};

/*######
## go_soulwell
######*/

enum SoulWellData
{
    GO_SOUL_WELL_R1                     = 181621,
    GO_SOUL_WELL_R2                     = 193169,

    SPELL_IMPROVED_HEALTH_STONE_R1      = 18692,
    SPELL_IMPROVED_HEALTH_STONE_R2      = 18693,

    SPELL_CREATE_MASTER_HEALTH_STONE_R0 = 34130,
    SPELL_CREATE_MASTER_HEALTH_STONE_R1 = 34149,
    SPELL_CREATE_MASTER_HEALTH_STONE_R2 = 34150,

    SPELL_CREATE_FEL_HEALTH_STONE_R0    = 58890,
    SPELL_CREATE_FEL_HEALTH_STONE_R1    = 58896,
    SPELL_CREATE_FEL_HEALTH_STONE_R2    = 58898,
};

class go_soulwell : public GameObjectScript
{
    public:
        go_soulwell() : GameObjectScript("go_soulwell") { }

        struct go_soulwellAI : public GameObjectAI
        {
            go_soulwellAI(GameObject* go) : GameObjectAI(go)
            {
                _stoneSpell = 0;
                _stoneId = 0;
                switch (go->GetEntry())
                {
                    case GO_SOUL_WELL_R1:
                        _stoneSpell = SPELL_CREATE_MASTER_HEALTH_STONE_R0;
                        if (Unit* owner = go->GetOwner())
                        {
                            if (owner->HasAura(SPELL_IMPROVED_HEALTH_STONE_R1))
                                _stoneSpell = SPELL_CREATE_MASTER_HEALTH_STONE_R1;
                            else if (owner->HasAura(SPELL_CREATE_MASTER_HEALTH_STONE_R2))
                                _stoneSpell = SPELL_CREATE_MASTER_HEALTH_STONE_R2;
                        }
                        break;
                    case GO_SOUL_WELL_R2:
                        _stoneSpell = SPELL_CREATE_FEL_HEALTH_STONE_R0;
                        if (Unit* owner = go->GetOwner())
                        {
                            if (owner->HasAura(SPELL_IMPROVED_HEALTH_STONE_R1))
                                _stoneSpell = SPELL_CREATE_FEL_HEALTH_STONE_R1;
                            else if (owner->HasAura(SPELL_CREATE_MASTER_HEALTH_STONE_R2))
                                _stoneSpell = SPELL_CREATE_FEL_HEALTH_STONE_R2;
                        }
                        break;
                }
                if (_stoneSpell == 0) // Should never happen
                    return;

                SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(_stoneSpell);
                if (!spellInfo)
                    return;

                _stoneId = spellInfo->Effects[EFFECT_0].ItemType;
            }

            bool GossipHello(Player* player) override
            {
                Unit* owner = me->GetOwner();
                if (_stoneSpell == 0 || _stoneId == 0)
                    return true;

                if (!owner || owner->GetTypeId() != TYPEID_PLAYER || !player->IsInSameRaidWith(owner->ToPlayer()))
                    return true;

                // Don't try to add a stone if we already have one.
                if (player->HasItemCount(_stoneId))
                {
                    if (SpellInfo const* spell = sSpellMgr->GetSpellInfo(_stoneSpell))
                        Spell::SendCastResult(player, spell, 0, SPELL_FAILED_TOO_MANY_OF_ITEM);
                    return true;
                }

                owner->CastSpell(player, _stoneSpell, true);
                // Item has to actually be created to remove a charge on the well.
                if (player->HasItemCount(_stoneId))
                    me->AddUse();

                return false;
            }

        private:
            uint32 _stoneSpell;
            uint32 _stoneId;
        };

        GameObjectAI* GetAI(GameObject* go) const override
        {
            return new go_soulwellAI(go);
        }
};

/*######
## Quest 1126: Hive in the Tower
## go_hive_pod
######*/

enum Hives
{
    QUEST_HIVE_IN_THE_TOWER                       = 9544,
    NPC_HIVE_AMBUSHER                             = 13301
};

class go_hive_pod : public GameObjectScript
{
public:
    go_hive_pod() : GameObjectScript("go_hive_pod") { }

    struct go_hive_podAI : public GameObjectAI
    {
        go_hive_podAI(GameObject* go) : GameObjectAI(go) { }

        bool GossipHello(Player* player) override
        {
            player->SendLoot(me->GetGUID(), LOOT_CORPSE);
            me->SummonCreature(NPC_HIVE_AMBUSHER, me->GetPositionX() + 1, me->GetPositionY(), me->GetPositionZ(), me->GetAbsoluteAngle(player), TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 60000);
            me->SummonCreature(NPC_HIVE_AMBUSHER, me->GetPositionX(), me->GetPositionY() + 1, me->GetPositionZ(), me->GetAbsoluteAngle(player), TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 60000);
            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_hive_podAI(go);
    }
};

/*######
#### go_veil_skith_cage
#####*/

enum MissingFriends
{
   QUEST_MISSING_FRIENDS    = 10852,
   NPC_CAPTIVE_CHILD        = 22314,
   SAY_FREE_0               = 0,
};

class go_veil_skith_cage : public GameObjectScript
{
    public:
       go_veil_skith_cage() : GameObjectScript("go_veil_skith_cage") { }

       struct go_veil_skith_cageAI : public GameObjectAI
       {
           go_veil_skith_cageAI(GameObject* go) : GameObjectAI(go) { }

           bool GossipHello(Player* player) override
           {
               me->UseDoorOrButton();
               if (player->GetQuestStatus(QUEST_MISSING_FRIENDS) == QUEST_STATUS_INCOMPLETE)
               {
                   std::vector<Creature*> childrenList;
                   GetCreatureListWithEntryInGrid(childrenList, me, NPC_CAPTIVE_CHILD, INTERACTION_DISTANCE);
                   for (Creature* creature : childrenList)
                   {
                       player->KilledMonsterCredit(NPC_CAPTIVE_CHILD, creature->GetGUID());
                       creature->DespawnOrUnsummon(5000);
                       creature->GetMotionMaster()->MovePoint(1, me->GetPositionX() + 5, me->GetPositionY(), me->GetPositionZ());
                       creature->AI()->Talk(SAY_FREE_0);
                       creature->GetMotionMaster()->Clear();
                   }
               }
               return false;
           }
       };

       GameObjectAI* GetAI(GameObject* go) const override
       {
           return new go_veil_skith_cageAI(go);
       }
};

/*######
## go_midsummer_bonfire
######*/

enum MidsummerBonfire
{
    STAMP_OUT_BONFIRE_QUEST_COMPLETE    = 45458,
};

class go_midsummer_bonfire : public GameObjectScript
{
public:
    go_midsummer_bonfire() : GameObjectScript("go_midsummer_bonfire") { }

    struct go_midsummer_bonfireAI : public GameObjectAI
    {
        go_midsummer_bonfireAI(GameObject* go) : GameObjectAI(go) { }

        bool GossipSelect(Player* player, uint32 /*menuId*/, uint32 /*gossipListId*/) override
        {
            player->CastSpell(player, STAMP_OUT_BONFIRE_QUEST_COMPLETE, true);
            CloseGossipMenuFor(player);
            return false;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_midsummer_bonfireAI(go);
    }
};

enum MidsummerPoleRibbon
{
    SPELL_TEST_RIBBON_POLE_1 = 29705,
    SPELL_TEST_RIBBON_POLE_2 = 29726,
    SPELL_TEST_RIBBON_POLE_3 = 29727,
    NPC_POLE_RIBBON_BUNNY    = 17066,
    ACTION_COSMETIC_FIRES    = 0
};

uint32 const RibbonPoleSpells[3] =
{
    SPELL_TEST_RIBBON_POLE_1,
    SPELL_TEST_RIBBON_POLE_2,
    SPELL_TEST_RIBBON_POLE_3
};

class go_midsummer_ribbon_pole : public GameObjectScript
{
public:
    go_midsummer_ribbon_pole() : GameObjectScript("go_midsummer_ribbon_pole") { }

    struct go_midsummer_ribbon_poleAI : public GameObjectAI
    {
        go_midsummer_ribbon_poleAI(GameObject* go) : GameObjectAI(go) { }

        bool GossipHello(Player* player) override
        {
            if (Creature* creature = me->FindNearestCreature(NPC_POLE_RIBBON_BUNNY, 10.0f))
            {
                creature->GetAI()->DoAction(ACTION_COSMETIC_FIRES);
                player->CastSpell(player, RibbonPoleSpells[urand(0, 2)], true);
            }
            return true;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_midsummer_ribbon_poleAI(go);
    }
};

/*####
## go_brewfest_music
####*/

enum BrewfestMusic
{
    EVENT_BREWFESTDWARF01 = 11810, // 1.35 min
    EVENT_BREWFESTDWARF02 = 11812, // 1.55 min
    EVENT_BREWFESTDWARF03 = 11813, // 0.23 min
    EVENT_BREWFESTGOBLIN01 = 11811, // 1.08 min
    EVENT_BREWFESTGOBLIN02 = 11814, // 1.33 min
    EVENT_BREWFESTGOBLIN03 = 11815 // 0.28 min
};

// These are in seconds
enum BrewfestMusicTime
{
    EVENT_BREWFESTDWARF01_TIME = 95000,
    EVENT_BREWFESTDWARF02_TIME = 155000,
    EVENT_BREWFESTDWARF03_TIME = 23000,
    EVENT_BREWFESTGOBLIN01_TIME = 68000,
    EVENT_BREWFESTGOBLIN02_TIME = 93000,
    EVENT_BREWFESTGOBLIN03_TIME = 28000
};

enum BrewfestMusicAreas
{
    SILVERMOON = 3430, // Horde
    UNDERCITY = 1497,
    ORGRIMMAR_1 = 1296,
    ORGRIMMAR_2 = 14,
    THUNDERBLUFF = 1638,
    IRONFORGE_1 = 809, // Alliance
    IRONFORGE_2 = 1,
    STORMWIND = 12,
    EXODAR = 3557,
    DARNASSUS = 1657,
    SHATTRATH = 3703 // General
};

enum BrewfestMusicEvents
{
    EVENT_BM_SELECT_MUSIC = 1,
    EVENT_BM_START_MUSIC = 2
};

class go_brewfest_music : public GameObjectScript
{
public:
    go_brewfest_music() : GameObjectScript("go_brewfest_music") { }

    struct go_brewfest_musicAI : public GameObjectAI
    {
        uint32 rnd = 0;
        uint32 musicTime = 1000;

        go_brewfest_musicAI(GameObject* go) : GameObjectAI(go)
        {
            _events.ScheduleEvent(EVENT_BM_SELECT_MUSIC, 1s);
            _events.ScheduleEvent(EVENT_BM_START_MUSIC, 2s);
        }

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);
            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_BM_SELECT_MUSIC:
                    if (!sGameEventMgr->IsActiveEvent(HOLIDAY_BREWFEST)) // Check if Brewfest is active
                        break;
                    rnd = urand(0, 2); // Select random music sample
                    _events.ScheduleEvent(EVENT_BM_SELECT_MUSIC, musicTime); // Select new song music after play time is over
                    break;
                case EVENT_BM_START_MUSIC:
                    if (!sGameEventMgr->IsActiveEvent(HOLIDAY_BREWFEST)) // Check if Brewfest is active
                        break;

                    switch (me->GetAreaId())
                    {
                        // Horde
                        case SILVERMOON:
                        case UNDERCITY:
                        case ORGRIMMAR_1:
                        case ORGRIMMAR_2:
                        case THUNDERBLUFF:
                            if (rnd == 0)
                            {
                                me->PlayDirectMusic(EVENT_BREWFESTGOBLIN01);
                                musicTime = EVENT_BREWFESTGOBLIN01_TIME;
                            }
                            else if (rnd == 1)
                            {
                                me->PlayDirectMusic(EVENT_BREWFESTGOBLIN02);
                                musicTime = EVENT_BREWFESTGOBLIN02_TIME;
                            }
                            else
                            {
                                me->PlayDirectMusic(EVENT_BREWFESTGOBLIN03);
                                musicTime = EVENT_BREWFESTGOBLIN03_TIME;
                            }
                            break;
                        // Alliance
                        case IRONFORGE_1:
                        case IRONFORGE_2:
                        case STORMWIND:
                        case EXODAR:
                        case DARNASSUS:
                            if (rnd == 0)
                            {
                                me->PlayDirectMusic(EVENT_BREWFESTDWARF01);
                                musicTime = EVENT_BREWFESTDWARF01_TIME;
                            }
                            else if (rnd == 1)
                            {
                                me->PlayDirectMusic(EVENT_BREWFESTDWARF02);
                                musicTime = EVENT_BREWFESTDWARF02_TIME;
                            }
                            else
                            {
                                me->PlayDirectMusic(EVENT_BREWFESTDWARF03);
                                musicTime = EVENT_BREWFESTDWARF03_TIME;
                            }
                            break;
                        // Neurtal
                        case SHATTRATH:
                            std::vector<Player*> playersNearby;
                            me->GetPlayerListInGrid(playersNearby, me->GetVisibilityRange());
                            for (Player* player : playersNearby)
                            {
                                if (player->GetTeamId() == TEAM_HORDE)
                                {
                                    if (rnd == 0)
                                    {
                                        me->PlayDirectMusic(EVENT_BREWFESTGOBLIN01);
                                        musicTime = EVENT_BREWFESTGOBLIN01_TIME;
                                    }
                                    else if (rnd == 1)
                                    {
                                        me->PlayDirectMusic(EVENT_BREWFESTGOBLIN02);
                                        musicTime = EVENT_BREWFESTGOBLIN02_TIME;
                                    }
                                    else
                                    {
                                        me->PlayDirectMusic(EVENT_BREWFESTGOBLIN03);
                                        musicTime = EVENT_BREWFESTGOBLIN03_TIME;
                                    }
                                }
                                else
                                {
                                    if (rnd == 0)
                                    {
                                        me->PlayDirectMusic(EVENT_BREWFESTDWARF01);
                                        musicTime = EVENT_BREWFESTDWARF01_TIME;
                                    }
                                    else if (rnd == 1)
                                    {
                                        me->PlayDirectMusic(EVENT_BREWFESTDWARF02);
                                        musicTime = EVENT_BREWFESTDWARF02_TIME;
                                    }
                                    else
                                    {
                                        me->PlayDirectMusic(EVENT_BREWFESTDWARF03);
                                        musicTime = EVENT_BREWFESTDWARF03_TIME;
                                    }
                                }
                            }
                            break;
                    }

                    _events.ScheduleEvent(EVENT_BM_START_MUSIC, 5s); // Every 5 second's SMSG_PLAY_MUSIC packet (PlayDirectMusic) is pushed to the client
                    break;
                default:
                    break;
                }
            }
        }
    private:
        EventMap _events;
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_brewfest_musicAI(go);
    }
};

/*####
## go_midsummer_music
####*/

enum MidsummerMusic
{
    EVENTMIDSUMMERFIREFESTIVAL_A = 12319, // 1.08 min
    EVENTMIDSUMMERFIREFESTIVAL_H = 12325, // 1.12 min
};

enum MidsummerMusicEvents
{
    EVENT_MM_START_MUSIC = 1
};

class go_midsummer_music : public GameObjectScript
{
public:
    go_midsummer_music() : GameObjectScript("go_midsummer_music") { }

    struct go_midsummer_musicAI : public GameObjectAI
    {
        go_midsummer_musicAI(GameObject* go) : GameObjectAI(go)
        {
            _events.ScheduleEvent(EVENT_MM_START_MUSIC, 1s);
        }

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);
            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_MM_START_MUSIC:
                    {
                        if (!sGameEventMgr->IsActiveEvent(HOLIDAY_FIRE_FESTIVAL))
                            break;

                        std::vector<Player*> playersNearby;
                        me->GetPlayerListInGrid(playersNearby, me->GetVisibilityRange());
                        for (Player* player : playersNearby)
                        {
                            if (player->GetTeamId() == TEAM_HORDE)
                                me->PlayDirectMusic(EVENTMIDSUMMERFIREFESTIVAL_H, player);
                            else
                                me->PlayDirectMusic(EVENTMIDSUMMERFIREFESTIVAL_A, player);
                        }
                        _events.ScheduleEvent(EVENT_MM_START_MUSIC, 5s); // Every 5 second's SMSG_PLAY_MUSIC packet (PlayDirectMusic) is pushed to the client (sniffed value)
                        break;
                    }
                default:
                    break;
                }
            }
        }
    private:
        EventMap _events;
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_midsummer_musicAI(go);
    }
};

/*####
## go_darkmoon_faire_music
####*/

enum DarkmoonFaireMusic
{
    MUSIC_DARKMOON_FAIRE_MUSIC = 8440
};

enum DarkmoonFaireMusicEvents
{
    EVENT_DFM_START_MUSIC = 1
};

class go_darkmoon_faire_music : public GameObjectScript
{
public:
    go_darkmoon_faire_music() : GameObjectScript("go_darkmoon_faire_music") { }

    struct go_darkmoon_faire_musicAI : public GameObjectAI
    {
        go_darkmoon_faire_musicAI(GameObject* go) : GameObjectAI(go)
        {
            _events.ScheduleEvent(EVENT_DFM_START_MUSIC, 1s);
        }

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);
            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_DFM_START_MUSIC:
                    if (!sGameEventMgr->IsActiveEvent(HOLIDAY_DARKMOON_FAIRE_ELWYNN) || !sGameEventMgr->IsActiveEvent(HOLIDAY_DARKMOON_FAIRE_THUNDER) || !sGameEventMgr->IsActiveEvent(HOLIDAY_DARKMOON_FAIRE_SHATTRATH))
                            break;
                        me->PlayDirectMusic(MUSIC_DARKMOON_FAIRE_MUSIC);
                        _events.ScheduleEvent(EVENT_DFM_START_MUSIC, 5s);  // Every 5 second's SMSG_PLAY_MUSIC packet (PlayDirectMusic) is pushed to the client (sniffed value)
                        break;
                    default:
                        break;
                }
            }
        }
    private:
        EventMap _events;
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_darkmoon_faire_musicAI(go);
    }
};

/*####
## go_bells
####*/

enum BellHourlySoundFX
{
    BELLTOLLHORDE          = 6595, // Horde
    BELLTOLLTRIBAL         = 6675,
    BELLTOLLALLIANCE       = 6594, // Alliance
    BELLTOLLNIGHTELF       = 6674,
    BELLTOLLDWARFGNOME     = 7234,
    BELLTOLLKHARAZHAN      = 9154 // Kharazhan
};

enum BellHourlySoundAreas
{
    UNDERCITY_AREA         = 1497,
    IRONFORGE_1_AREA       = 809,
    IRONFORGE_2_AREA       = 1,
    DARNASSUS_AREA         = 1657,
    TELDRASSIL_ZONE        = 141,
    KHARAZHAN_MAPID        = 532
};

enum BellHourlyObjects
{
    GO_HORDE_BELL          = 175885,
    GO_ALLIANCE_BELL       = 176573,
    GO_KHARAZHAN_BELL      = 182064
};

enum BellHourlyMisc
{
    GAME_EVENT_HOURLY_BELLS = 73,
    EVENT_RING_BELL        = 1
};

class go_bells : public GameObjectScript
{
public:
    go_bells() : GameObjectScript("go_bells") { }

    struct go_bellsAI : public GameObjectAI
    {
        go_bellsAI(GameObject* go) : GameObjectAI(go), _soundId(0) { }

        void InitializeAI() override
        {
            switch (me->GetEntry())
            {
                case GO_HORDE_BELL:
                    _soundId = me->GetAreaId() == UNDERCITY_AREA ? BELLTOLLHORDE : BELLTOLLTRIBAL;
                    break;
                case GO_ALLIANCE_BELL:
                {
                    if (me->GetAreaId() == IRONFORGE_1_AREA || me->GetAreaId() == IRONFORGE_2_AREA)
                        _soundId = BELLTOLLDWARFGNOME;
                    else if (me->GetAreaId() == DARNASSUS_AREA || me->GetZoneId() == TELDRASSIL_ZONE)
                        _soundId = BELLTOLLNIGHTELF;
                    else
                        _soundId = BELLTOLLALLIANCE;

                    break;
                }
                case GO_KHARAZHAN_BELL:
                    _soundId = BELLTOLLKHARAZHAN;
                    break;
            }
        }

        void OnGameEvent(bool start, uint16 eventId) override
        {
            if (eventId == GAME_EVENT_HOURLY_BELLS && start)
            {
                time_t time = WorldGameTime::GetGameTime();
                tm localTm;
                localtime_r(&time, &localTm);
                uint8 _rings = (localTm.tm_hour - 1) % 12 + 1;

                for (auto i = 0; i < _rings; ++i)
                    _events.ScheduleEvent(EVENT_RING_BELL, Seconds(i * 4 + 1));
            }
        }

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_RING_BELL:
                        me->PlayDirectSound(_soundId);
                        break;
                    default:
                        break;
                }
            }
        }
    private:
        EventMap _events;
        uint32 _soundId;
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_bellsAI(go);
    }
};

void AddSC_go_scripts()
{
    new go_cat_figurine();
    new go_barov_journal();
    new go_gilded_brazier();
    new go_orb_of_command();
    new go_shrine_of_the_birds();
    new go_southfury_moonstone();
    new go_tablet_of_madness();
    new go_tablet_of_the_seven();
    new go_jump_a_tron();
    new go_ethereum_prison();
    new go_ethereum_stasis();
    new go_resonite_cask();
    new go_sacred_fire_of_life();
    new go_fel_crystalforge();
    new go_bashir_crystalforge();
    new go_matrix_punchograph();
    new go_blood_filled_orb();
    new go_table_theka();
    new go_inconspicuous_landmark();
    new go_soulwell();
    new go_hive_pod();
    new go_veil_skith_cage();
    new go_midsummer_bonfire();
    new go_midsummer_ribbon_pole();
    new go_brewfest_music();
    new go_midsummer_music();
    new go_darkmoon_faire_music();
    new go_bells();
}
