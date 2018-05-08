#include "../../ClassSpellsDamage.h"
#include "../../ClassSpellsCoeff.h"
#include "SpellHistory.h"

#define SOUL_SHARD 6265

class SuppressionTest : public TestCaseScript
{
public:
    SuppressionTest() : TestCaseScript("talents warlock suppression") { }

    class SuppressionTestImpt : public TestCase
    {
    public:
        SuppressionTestImpt() : TestCase(STATUS_KNOWN_BUG) { } // Curse of Doom is not affected, should be.

        void Test() override
        {
            TestPlayer* warlock = SpawnRandomPlayer(CLASS_WARLOCK);
            Creature* dummy = SpawnCreature(12); // Boss

            LearnTalent(warlock, Talents::Warlock::SUPPRESSION_RNK_5);
            float const hitTalentFactor = 10.0f;
            float const hitChance = 16.0f - hitTalentFactor;

            TEST_SPELL_HIT_CHANCE(warlock, dummy, ClassSpells::Warlock::CORRUPTION_RNK_8, hitChance, SPELL_MISS_RESIST);
            TEST_SPELL_HIT_CHANCE(warlock, dummy, ClassSpells::Warlock::CURSE_OF_AGONY_RNK_7, hitChance, SPELL_MISS_RESIST);
            TEST_SPELL_HIT_CHANCE(warlock, dummy, ClassSpells::Warlock::CURSE_OF_DOOM_RNK_2, hitChance, SPELL_MISS_RESIST);
            TEST_SPELL_HIT_CHANCE(warlock, dummy, ClassSpells::Warlock::CURSE_OF_EXHAUSTION_RNK_1, hitChance, SPELL_MISS_RESIST);
            TEST_SPELL_HIT_CHANCE(warlock, dummy, ClassSpells::Warlock::CURSE_OF_RECKLESSNESS_RNK_5, hitChance, SPELL_MISS_RESIST);
            TEST_SPELL_HIT_CHANCE(warlock, dummy, ClassSpells::Warlock::CURSE_OF_THE_ELEMENTS_RNK_4, hitChance, SPELL_MISS_RESIST);
            TEST_SPELL_HIT_CHANCE(warlock, dummy, ClassSpells::Warlock::CURSE_OF_TONGUES_RNK_2, hitChance, SPELL_MISS_RESIST);
            TEST_SPELL_HIT_CHANCE(warlock, dummy, ClassSpells::Warlock::CURSE_OF_WEAKNESS_RNK_8, hitChance, SPELL_MISS_RESIST);
            TEST_SPELL_HIT_CHANCE(warlock, dummy, ClassSpells::Warlock::DEATH_COIL_RNK_4, hitChance, SPELL_MISS_RESIST);
            TEST_SPELL_HIT_CHANCE(warlock, dummy, ClassSpells::Warlock::DRAIN_LIFE_RNK_8, hitChance, SPELL_MISS_RESIST);
            TEST_SPELL_HIT_CHANCE(warlock, dummy, ClassSpells::Warlock::DRAIN_MANA_RNK_6, hitChance, SPELL_MISS_RESIST);
            TEST_SPELL_HIT_CHANCE(warlock, dummy, ClassSpells::Warlock::FEAR_RNK_3, hitChance, SPELL_MISS_RESIST);
            TEST_SPELL_HIT_CHANCE(warlock, dummy, ClassSpells::Warlock::HOWL_OF_TERROR_RNK_2, hitChance, SPELL_MISS_RESIST);
            TEST_SPELL_HIT_CHANCE(warlock, dummy, ClassSpells::Warlock::SEED_OF_CORRUPTION_RNK_1, hitChance, SPELL_MISS_RESIST);
            TEST_SPELL_HIT_CHANCE(warlock, dummy, ClassSpells::Warlock::SIPHON_LIFE_RNK_6, hitChance, SPELL_MISS_RESIST);
            TEST_SPELL_HIT_CHANCE(warlock, dummy, ClassSpells::Warlock::UNSTABLE_AFFLICTION_RNK_3, hitChance, SPELL_MISS_RESIST);

            TEST_SPELL_HIT_CHANCE(warlock, dummy, ClassSpells::Warlock::SHADOW_BOLT_RNK_11, 16.0f, SPELL_MISS_RESIST);
        }
    };

    std::shared_ptr<TestCase> GetTest() const override
    {
        return std::make_shared<SuppressionTestImpt>();
    }
};

class ImprovedCorruptionTest : public TestCaseScript
{
public:
    ImprovedCorruptionTest() : TestCaseScript("talents warlock improved_corruption") { }

    class ImprovedCorruptionTestImpt : public TestCase
    {
    public:
        ImprovedCorruptionTestImpt() : TestCase(STATUS_PASSING) { }

        void TestCorruptionCastTime(TestPlayer* caster, uint32 talentSpellId, uint32 talentFactor)
        {
            LearnTalent(caster, talentSpellId);
            uint32 const expectedCastTime = 2000 - talentFactor;
            TEST_SPELL_CAST_TIME(caster, ClassSpells::Warlock::CORRUPTION_RNK_8, expectedCastTime);
        }

        void Test() override
        {
            TestPlayer* warlock = SpawnRandomPlayer(CLASS_WARLOCK);

            uint32 const castTimeReducedPerTalentPoint = 400;

            TestCorruptionCastTime(warlock, Talents::Warlock::IMPROVED_CORRUPTION_RNK_1, 1 * castTimeReducedPerTalentPoint);
            TestCorruptionCastTime(warlock, Talents::Warlock::IMPROVED_CORRUPTION_RNK_2, 2 * castTimeReducedPerTalentPoint);
            TestCorruptionCastTime(warlock, Talents::Warlock::IMPROVED_CORRUPTION_RNK_3, 3 * castTimeReducedPerTalentPoint);
            TestCorruptionCastTime(warlock, Talents::Warlock::IMPROVED_CORRUPTION_RNK_4, 4 * castTimeReducedPerTalentPoint);
            TestCorruptionCastTime(warlock, Talents::Warlock::IMPROVED_CORRUPTION_RNK_5, 5 * castTimeReducedPerTalentPoint);
        }
    };

    std::shared_ptr<TestCase> GetTest() const override
    {
        return std::make_shared<ImprovedCorruptionTestImpt>();
    }
};

class ImprovedCurseOfWeaknessTest : public TestCaseScript
{
public:
    ImprovedCurseOfWeaknessTest() : TestCaseScript("talents warlock improved_curse_of_weakness") { }

    class ImprovedCurseOfWeaknessTestImpt : public TestCase
    {
    public:
        ImprovedCurseOfWeaknessTestImpt() : TestCase(STATUS_PASSING) { }

        void Test() override
        {
            TestPlayer* warlock = SpawnPlayer(CLASS_WARLOCK, RACE_HUMAN);
            TestPlayer* rogue = SpawnPlayer(CLASS_ROGUE, RACE_ORC);
            EQUIP_NEW_ITEM(rogue, 34188); // Leggins of Immortal Night - 124 AP

            LearnTalent(warlock, Talents::Warlock::IMPROVED_CURSE_OF_WEAKNESS_RNK_2);
            float const talentFactor = 1.2f;

            uint32 const curseOfWeaknessAPMalus = 350 * talentFactor;
            float const expectedRogueAP = rogue->GetTotalAttackPowerValue(BASE_ATTACK) - curseOfWeaknessAPMalus;

            FORCE_CAST(warlock, rogue, ClassSpells::Warlock::CURSE_OF_WEAKNESS_RNK_8);
            ASSERT_INFO("Rogue has %f AP, should have %f.", rogue->GetTotalAttackPowerValue(BASE_ATTACK), expectedRogueAP);
            TEST_ASSERT(Between<float>(rogue->GetTotalAttackPowerValue(BASE_ATTACK), expectedRogueAP - 0.1f, expectedRogueAP + 0.1f));
        }
    };

    std::shared_ptr<TestCase> GetTest() const override
    {
        return std::make_shared<ImprovedCurseOfWeaknessTestImpt>();
    }
};

class ImprovedDrainSoulTest : public TestCaseScript
{
public:
    ImprovedDrainSoulTest() : TestCaseScript("talents warlock improved_drain_soul") { }

    class ImprovedDrainSoulTestImpt : public TestCase
    {
    public:
        ImprovedDrainSoulTestImpt() : TestCase(STATUS_KNOWN_BUG) { } // Curse of Doom doesnt gets its threat reduced

        void Test() override
        {
            TestPlayer* warlock = SpawnPlayer(CLASS_WARLOCK, RACE_HUMAN);
            _location.MoveInFront(_location, 10.0f);
            TestPlayer* rogue = SpawnPlayer(CLASS_ROGUE, RACE_ORC);
            warlock->DisableRegeneration(true);
            rogue->DisableRegeneration(true);
            rogue->SetHealth(100); // Less than a Drain Soul tick
            Wait(3000);

            LearnTalent(warlock, Talents::Warlock::IMPROVED_DRAIN_SOUL_RNK_2);
            float const talentManaFactor = 0.15f;
            float const talentThreatFactor = 1 - 0.1f;

            // Mana returned
            uint32 const drainSoulManaCost = 360;
            warlock->SetPower(POWER_MANA, drainSoulManaCost);

            uint32 const expectedManaReturn = warlock->GetMaxPower(POWER_MANA) * talentManaFactor;
            FORCE_CAST(warlock, rogue, ClassSpells::Warlock::DRAIN_SOUL_RNK_5);
            Wait(4000);
            TEST_ASSERT(rogue->IsDead());
            TEST_ASSERT(warlock->GetPower(POWER_MANA) == expectedManaReturn);

            // Only get mana if the drain soul kills the target
            rogue->ResurrectPlayer(1.0f);
            warlock->SetPower(POWER_MANA, drainSoulManaCost);
            FORCE_CAST(warlock, rogue, ClassSpells::Warlock::DRAIN_SOUL_RNK_5);
            Wait(1000);
            rogue->KillSelf();
            Wait(2000);
            TEST_ASSERT(warlock->GetPower(POWER_MANA) == 0);

            // Threat reduced by 10% for all affliction spells
            Creature* dummy = SpawnCreature();

            const float expectedCorruptionThreat = ClassSpellsDamage::Warlock::CORRUPTION_RNK_8_TOTAL * talentThreatFactor;
            TEST_DOT_THREAT(warlock, dummy, ClassSpells::Warlock::CORRUPTION_RNK_8, expectedCorruptionThreat, false);

            const float expectedCoAThreat = ClassSpellsDamage::Warlock::CURSE_OF_AGONY_RNK_7_TOTAL * talentThreatFactor;
            TEST_DOT_THREAT(warlock, dummy, ClassSpells::Warlock::CURSE_OF_AGONY_RNK_7, expectedCoAThreat, false);

            const float expectedCoDThreat = ClassSpellsDamage::Warlock::CURSE_OF_DOOM_RNK_2 * talentThreatFactor;
            TEST_DOT_THREAT(warlock, dummy, ClassSpells::Warlock::CURSE_OF_DOOM_RNK_2, expectedCoDThreat, false);

            const float expectedDeathCoilThreat = ClassSpellsDamage::Warlock::DEATH_COIL_RNK_4_LVL_70 * talentThreatFactor;
            TEST_DOT_THREAT(warlock, dummy, ClassSpells::Warlock::DEATH_COIL_RNK_4, expectedDeathCoilThreat, false);

            const float expectedDrainLifeThreat = ClassSpellsDamage::Warlock::DRAIN_LIFE_RNK_8_TICK * 5.0f * talentThreatFactor;
            TEST_DOT_THREAT(warlock, dummy, ClassSpells::Warlock::DRAIN_LIFE_RNK_8, expectedDrainLifeThreat, false);

            const float expectedDrainSoulThreat = ClassSpellsDamage::Warlock::DRAIN_SOUL_RNK_5_TOTAL * talentThreatFactor;
            TEST_DOT_THREAT(warlock, dummy, ClassSpells::Warlock::DRAIN_SOUL_RNK_5, expectedDrainSoulThreat, false);

            const float expectedSoCThreat = ClassSpellsDamage::Warlock::SEED_OF_CORRUPTION_RNK_1_TOTAL * talentThreatFactor;
            TEST_DOT_THREAT(warlock, dummy, ClassSpells::Warlock::SEED_OF_CORRUPTION_RNK_1, expectedSoCThreat, false);
            // TODO: SoC Direct damage
        }
    };

    std::shared_ptr<TestCase> GetTest() const override
    {
        return std::make_shared<ImprovedDrainSoulTestImpt>();
    }
};

class ImprovedLifeTapTest : public TestCaseScript
{
public:
	ImprovedLifeTapTest() : TestCaseScript("talents warlock improved_life_tap") { }

	class ImprovedLifeTapTestImpt : public TestCase
	{
	public:
		ImprovedLifeTapTestImpt() : TestCase(STATUS_PASSING) { }

		void Test() override
		{
			TestPlayer* warlock = SpawnRandomPlayer(CLASS_WARLOCK);
            warlock->DisableRegeneration(true);
			warlock->SetPower(POWER_MANA, 0);

            LearnTalent(warlock, Talents::Warlock::IMPROVED_LIFE_TAP_RNK_2);
            float const improvedLifeTapFactor = 1.2f;

            uint32 const spellLevel = 68;
            uint32 const perLevelPoint = 1;
            uint32 const perLevelGain = std::max(warlock->GetLevel() - spellLevel, uint32(0)) * perLevelPoint;
            uint32 const expectedManaGained = (ClassSpellsDamage::Warlock::LIFE_TAP_RNK_7 + perLevelGain) * improvedLifeTapFactor;

			warlock->CastSpell(warlock, ClassSpells::Warlock::LIFE_TAP_RNK_7);
			TEST_ASSERT(warlock->GetPower(POWER_MANA) == expectedManaGained);
		}
	};

	std::shared_ptr<TestCase> GetTest() const override
	{
		return std::make_shared<ImprovedLifeTapTestImpt>();
	}
};

class SoulSiphonTest : public TestCaseScript
{
public:
    SoulSiphonTest() : TestCaseScript("talents warlock soul_siphon") { }

    class SoulSiphonTestImpt : public TestCase
    {
    public:
        SoulSiphonTestImpt() : TestCase(STATUS_KNOWN_BUG) { } // Bug: Should have a 60% limit for drain life bonus

        void Add5AfflictionSpell(TestPlayer* warlock, Creature* dummy, uint32 curseSpellId)
        {
            FORCE_CAST(warlock, dummy, curseSpellId, SPELL_MISS_NONE, TRIGGERED_FULL_MASK);
            FORCE_CAST(warlock, dummy, ClassSpells::Warlock::CORRUPTION_RNK_8, SPELL_MISS_NONE, TRIGGERED_FULL_MASK);
            FORCE_CAST(warlock, dummy, ClassSpells::Warlock::UNSTABLE_AFFLICTION_RNK_3, SPELL_MISS_NONE, TRIGGERED_FULL_MASK);
            FORCE_CAST(warlock, dummy, ClassSpells::Warlock::SIPHON_LIFE_RNK_6, SPELL_MISS_NONE, TRIGGERED_FULL_MASK);
            FORCE_CAST(warlock, dummy, ClassSpells::Warlock::DRAIN_SOUL_RNK_5);
        }

        void IsAffectedByTalent(TestPlayer* warlock, TestPlayer* warlock2, Creature* dummy, uint32 spellId, float talentFactor)
        {
            warlock->SetHealth(1);
            FORCE_CAST(warlock2, dummy, spellId, SPELL_MISS_NONE, TRIGGERED_FULL_MASK);
            uint32 warlockExpectedHealth = 1 + 5.0f * floor(ClassSpellsDamage::Warlock::DRAIN_LIFE_RNK_8_TICK * (1.0f + talentFactor));
            FORCE_CAST(warlock, dummy, ClassSpells::Warlock::DRAIN_LIFE_RNK_8);
            WaitNextUpdate(); //Wait for channel to start
            ASSERT_INFO("After Drain Life started, target didnt have aura %u.", spellId);
            TEST_HAS_AURA(dummy, spellId);
            Wait(6000); //Wait for drain life to finish
            ASSERT_INFO("After spell %u, Warlock has %u HP but should have %u HP.", spellId, warlock->GetHealth(), warlockExpectedHealth);
            TEST_ASSERT(warlock->GetHealth() == warlockExpectedHealth);
            dummy->RemoveAurasDueToSpell(spellId);
            warlock->SetPower(POWER_MANA, warlock->GetMaxPower(POWER_MANA));
            warlock2->SetPower(POWER_MANA, warlock2->GetMaxPower(POWER_MANA));
        }

        uint32 GetHarmfulAurasCount(Creature* dummy)
        {
            uint32 harmfulAuraCount = 0;
            auto& auras = dummy->GetAppliedAuras();
            for (const auto & i : auras)
            {
                if (!i.second->IsPositive())
                    harmfulAuraCount++;
            }
            return harmfulAuraCount;
        }

        void Test() override
        {
            TestPlayer* warlock = SpawnPlayer(CLASS_WARLOCK, RACE_ORC);
            warlock->DisableRegeneration(true);

            TestPlayer* warlock2 = SpawnPlayer(CLASS_WARLOCK, RACE_ORC);
            Creature* dummy = SpawnCreature();
            dummy->_disableSpellBreakChance = true; //needed for fears

            LearnTalent(warlock, Talents::Warlock::SOUL_SIPHON_RNK_2);
            float const bonusPerSpell = 0.04f;

            // Solo Drain Life
            warlock->SetHealth(1);
            uint32 warlockExpectedHealth = 1 + 5.0f * floor(ClassSpellsDamage::Warlock::DRAIN_LIFE_RNK_8_TICK * (1 + bonusPerSpell));
            FORCE_CAST(warlock, dummy, ClassSpells::Warlock::DRAIN_LIFE_RNK_8);
            Wait(5500);
            ASSERT_INFO("After Drain Life, Warlock has %u HP but should have %u HP.", warlock->GetHealth(), warlockExpectedHealth);
            TEST_ASSERT(warlock->GetHealth() == warlockExpectedHealth);

            IsAffectedByTalent(warlock, warlock2, dummy, ClassSpells::Warlock::CORRUPTION_RNK_8, 2 * bonusPerSpell);
            IsAffectedByTalent(warlock, warlock2, dummy, ClassSpells::Warlock::CURSE_OF_AGONY_RNK_7, 2 * bonusPerSpell);
            IsAffectedByTalent(warlock, warlock2, dummy, ClassSpells::Warlock::CURSE_OF_DOOM_RNK_2, 2 * bonusPerSpell);
            IsAffectedByTalent(warlock, warlock2, dummy, ClassSpells::Warlock::CURSE_OF_EXHAUSTION_RNK_1, 2 * bonusPerSpell);
            IsAffectedByTalent(warlock, warlock2, dummy, ClassSpells::Warlock::CURSE_OF_RECKLESSNESS_RNK_5, 2 * bonusPerSpell);
            IsAffectedByTalent(warlock, warlock2, dummy, ClassSpells::Warlock::CURSE_OF_THE_ELEMENTS_RNK_4, 2 * bonusPerSpell + 0.1f); // +10% from CoE
            IsAffectedByTalent(warlock, warlock2, dummy, ClassSpells::Warlock::CURSE_OF_TONGUES_RNK_2, 2 * bonusPerSpell);
            IsAffectedByTalent(warlock, warlock2, dummy, ClassSpells::Warlock::CURSE_OF_WEAKNESS_RNK_8, 2 * bonusPerSpell);
            IsAffectedByTalent(warlock, warlock2, dummy, ClassSpells::Warlock::DRAIN_MANA_RNK_6, 2 * bonusPerSpell);
            IsAffectedByTalent(warlock, warlock2, dummy, ClassSpells::Warlock::FEAR_RNK_3, 2 * bonusPerSpell);
            dummy->NearTeleportTo(_location);
            WaitNextUpdate();
            IsAffectedByTalent(warlock, warlock2, dummy, ClassSpells::Warlock::HOWL_OF_TERROR_RNK_2, 2 * bonusPerSpell);
            dummy->NearTeleportTo(_location);
            WaitNextUpdate();
            IsAffectedByTalent(warlock, warlock2, dummy, ClassSpells::Warlock::SEED_OF_CORRUPTION_RNK_1, 2 * bonusPerSpell);
            IsAffectedByTalent(warlock, warlock2, dummy, ClassSpells::Warlock::SIPHON_LIFE_RNK_6, 2 * bonusPerSpell);
            IsAffectedByTalent(warlock, warlock2, dummy, ClassSpells::Warlock::UNSTABLE_AFFLICTION_RNK_3, 2 * bonusPerSpell);

            // Test Max bonus: +60% -- Bugged, goes beyond 60%
            TestPlayer* warlock3 = SpawnPlayer(CLASS_WARLOCK, RACE_ORC);
            TestPlayer* warlock4 = SpawnPlayer(CLASS_WARLOCK, RACE_ORC);
            TestPlayer* warlock5 = SpawnPlayer(CLASS_WARLOCK, RACE_ORC);
            TestPlayer* warlock6 = SpawnPlayer(CLASS_WARLOCK, RACE_ORC);

            Add5AfflictionSpell(warlock2, dummy, ClassSpells::Warlock::CURSE_OF_AGONY_RNK_7);
            Add5AfflictionSpell(warlock3, dummy, ClassSpells::Warlock::CURSE_OF_THE_ELEMENTS_RNK_4);
            Add5AfflictionSpell(warlock4, dummy, ClassSpells::Warlock::CURSE_OF_DOOM_RNK_2);
            Add5AfflictionSpell(warlock5, dummy, ClassSpells::Warlock::CURSE_OF_WEAKNESS_RNK_8);
            Add5AfflictionSpell(warlock6, dummy, ClassSpells::Warlock::CURSE_OF_TONGUES_RNK_2);
            WaitNextUpdate();

            // Dummy should be affected by 25 Affliction spells
            warlock->SetHealth(1);
            uint32 const harmfulAuraCount = GetHarmfulAurasCount(dummy);
            ASSERT_INFO("Dummy has %u harmful auras instead of %u.", harmfulAuraCount, 18);
            TEST_ASSERT(harmfulAuraCount == 25);

            float const expectedDrainLifeBonus = std::min(1.0f + harmfulAuraCount * bonusPerSpell, 1.60f);
            warlockExpectedHealth = 1 + 5.0f * floor(ClassSpellsDamage::Warlock::DRAIN_LIFE_RNK_8_TICK * expectedDrainLifeBonus);
            FORCE_CAST(warlock, dummy, ClassSpells::Warlock::DRAIN_LIFE_RNK_8);
            Wait(5500);
            TEST_ASSERT(GetHarmfulAurasCount(dummy) == 25);
            ASSERT_INFO("Warlock has %u HP but should have %u HP.", warlock->GetHealth(), warlockExpectedHealth);
            TEST_ASSERT(warlock->GetHealth() == warlockExpectedHealth);
        }
    };

    std::shared_ptr<TestCase> GetTest() const override
    {
        return std::make_shared<SoulSiphonTestImpt>();
    }
};

class AmplifyCurseTest : public TestCaseScript
{
public:

    AmplifyCurseTest() : TestCaseScript("talents warlock amplify_curse") { }

    class AmplifyCurseTestImpt : public TestCase
    {
    public:
        AmplifyCurseTestImpt() : TestCase(STATUS_KNOWN_BUG) { } // Doesnt boost Curse of Doom and somehow reduce it

        void Test() override
        {
            TestPlayer* warlock = SpawnPlayer(CLASS_WARLOCK, RACE_ORC);
            TestPlayer* warrior = SpawnPlayer(CLASS_WARRIOR, RACE_HUMAN);
            Creature* dummy = SpawnCreature();

            LearnTalent(warlock, Talents::Warlock::AMPLIFY_CURSE_RNK_1);
            float const codAndCoABoostFactor = 1.5f;
            float const coeBoostFactor = 0.5f;

            TEST_CAST(warlock, warlock, ClassSpells::Warlock::AMPLIFY_CURSE_RNK_1);
            TEST_AURA_MAX_DURATION(warlock, ClassSpells::Warlock::AMPLIFY_CURSE_RNK_1, Seconds(30));

            // Curse of Exhaustion
            float const expectedSpeed = warrior->GetSpeed(MOVE_RUN) * coeBoostFactor;
            FORCE_CAST(warlock, warrior, ClassSpells::Warlock::CURSE_OF_EXHAUSTION_RNK_1);
            ASSERT_INFO("Warrior has %f speed, %f was expected.", warrior->GetSpeed(MOVE_RUN), expectedSpeed);
            TEST_ASSERT(Between<float>(warrior->GetSpeed(MOVE_RUN), expectedSpeed - 0.1f, expectedSpeed + 0.1f));
            TEST_HAS_NOT_AURA(warlock, ClassSpells::Warlock::AMPLIFY_CURSE_RNK_1);
            TEST_HAS_COOLDOWN(warlock, ClassSpells::Warlock::AMPLIFY_CURSE_RNK_1, Minutes(3)); // Cooldown starts when consuming a spell

            // Curse of Agony
            float const expectedCoAMaxDamage = ClassSpellsDamage::Warlock::CURSE_OF_AGONY_RNK_7_TOTAL * codAndCoABoostFactor;
            uint32 const expectedCoADamage = (4 * expectedCoAMaxDamage / 24.0f) + (4 * expectedCoAMaxDamage / 12.0f) + (4 * expectedCoAMaxDamage / 8.0f);
            TEST_CAST(warlock, warlock, ClassSpells::Warlock::AMPLIFY_CURSE_RNK_1, SPELL_CAST_OK, TRIGGERED_IGNORE_SPELL_AND_CATEGORY_CD);
            TEST_DOT_DAMAGE(warlock, dummy, ClassSpells::Warlock::CURSE_OF_AGONY_RNK_7, expectedCoADamage, false);

            // Curse of Doom
            float const expectedCoDDamage = ClassSpellsDamage::Warlock::CURSE_OF_DOOM_RNK_2 * codAndCoABoostFactor;
            TEST_CAST(warlock, warlock, ClassSpells::Warlock::AMPLIFY_CURSE_RNK_1, SPELL_CAST_OK, TRIGGERED_IGNORE_SPELL_AND_CATEGORY_CD);
            TEST_DOT_DAMAGE(warlock, dummy, ClassSpells::Warlock::CURSE_OF_DOOM_RNK_2, expectedCoDDamage, false);
        }
    };

    std::shared_ptr<TestCase> GetTest() const override
    {
        return std::make_shared<AmplifyCurseTestImpt>();
    }
};

class ImprovedCurseOfAgonyTest : public TestCaseScript
{
public:

	ImprovedCurseOfAgonyTest() : TestCaseScript("talents warlock improved_curse_of_agony") { }

	class ImprovedCurseOfAgonyTestImpt : public TestCase
	{
	public:
		ImprovedCurseOfAgonyTestImpt() : TestCase(STATUS_PASSING) { }

		void Test() override
		{
			TestPlayer* warlock = SpawnRandomPlayer(CLASS_WARLOCK);
            Creature* dummy = SpawnCreature();

            LearnTalent(warlock, Talents::Warlock::IMPROVED_CURSE_OF_AGONY_RNK_2);
            float const improvedCoAFactor = 1.1f;

			float const expectedCoAMaxDamage = ClassSpellsDamage::Warlock::CURSE_OF_AGONY_RNK_7_TOTAL * improvedCoAFactor;
            uint32 const expectedCoADamage = (4 * expectedCoAMaxDamage / 24.0f) + (4 * expectedCoAMaxDamage / 12.0f) + (4 * expectedCoAMaxDamage / 8.0f);

            TEST_DOT_DAMAGE(warlock, dummy, ClassSpells::Warlock::CURSE_OF_AGONY_RNK_7, expectedCoADamage, false);
		}
	};

	std::shared_ptr<TestCase> GetTest() const override
	{
		return std::make_shared<ImprovedCurseOfAgonyTestImpt>();
	}
};

class NightfallTest : public TestCaseScript
{
public:

    NightfallTest() : TestCaseScript("talents warlock nightfall") { }

    class NightfallTestImpt : public TestCase
    {
    public:
        NightfallTestImpt() : TestCase(STATUS_WIP) { } // Proc doesnt proc!

        void Test() override
        {
            TestPlayer* warlock = SpawnPlayer(CLASS_WARLOCK, RACE_ORC);
            Creature* dummy = SpawnCreature();

            LearnTalent(warlock, Talents::Warlock::NIGHTFALL_RNK_2);
            LearnTalent(warlock, Talents::Warlock::IMPROVED_CORRUPTION_RNK_5);
            float const procChance = 4.f;
            uint32 const procSpellId = 17941;

            // Proc chance
            auto callback = [&](Unit* caster, Unit* target) {
                bool hasAura = caster->HasAura(procSpellId);
                caster->RemoveAllAuras();
                return hasAura;
            };
            Wait(5000);
            TEST_AURA_TICK_PROC_CHANCE(warlock, dummy, ClassSpells::Warlock::DRAIN_LIFE_RNK_8, EFFECT_0, procChance, callback);
            TEST_AURA_TICK_PROC_CHANCE(warlock, dummy, ClassSpells::Warlock::CORRUPTION_RNK_8, EFFECT_0, procChance, callback);

            // Instant shadow bolt
            warlock->AddAura(procSpellId, warlock);
            TEST_SPELL_CAST_TIME(warlock, ClassSpells::Warlock::SHADOW_BOLT_RNK_11, uint32(0));
        }
    };

    std::shared_ptr<TestCase> GetTest() const override
    {
        return std::make_shared<NightfallTestImpt>();
    }
};

class EmpoweredCorruptionTest : public TestCaseScript
{
public:

	EmpoweredCorruptionTest() : TestCaseScript("talents warlock empowered_corruption") { }

	class EmpoweredCorruptionTestImpt : public TestCase
	{
	public:
		EmpoweredCorruptionTestImpt() : TestCase(STATUS_PASSING) { }

		void Test() override
		{
			TestPlayer* warlock = SpawnRandomPlayer(CLASS_WARLOCK);
            Creature* dummy = SpawnCreature();

            LearnTalent(warlock, Talents::Warlock::EMPOWERED_CORRUPTION_RNK_3);
            float const empoweredCorruptionFactor = 0.36f;

            EQUIP_NEW_ITEM(warlock, 34336); // Sunflare - 292 SP

            uint32 const spellPower = warlock->GetInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + SPELL_SCHOOL_SHADOW);
            TEST_ASSERT(spellPower == 292);

			float const corruptionSpellCoeff = ClassSpellsCoeff::Warlock::CORRUPTION;
			float const expectedCorruptionDamage = ClassSpellsDamage::Warlock::CORRUPTION_RNK_8_TOTAL + (corruptionSpellCoeff + empoweredCorruptionFactor) * spellPower;

            TEST_DOT_DAMAGE(warlock, dummy, ClassSpells::Warlock::CORRUPTION_RNK_8, expectedCorruptionDamage, false);
		}
	};

	std::shared_ptr<TestCase> GetTest() const override
	{
		return std::make_shared<EmpoweredCorruptionTestImpt>();
	}
};

class ShadowEmbraceTest : public TestCaseScript
{
public:
    ShadowEmbraceTest() : TestCaseScript("talents warlock shadow_embrace") { }

    class ShadowEmbraceTestImpt : public TestCase
    {
    public:
        /*
        Bugs:
        - Siphon Life doesnt remove Shadow Embrace at the end.
        - Seed of Corruption doesnt apply Shadow Embrace.
        */
        //See hack in AuraEffect::CleanupTriggeredSpells for spell cleanup handling
        ShadowEmbraceTestImpt() : TestCase(STATUS_KNOWN_BUG) { }

        void SpellAppliesAndRemovesShadowEmbrace(TestPlayer* warlock, TestPlayer* victim, uint32 spellId, Seconds dotTime, uint32 shadowEmbraceId)
        {
            //TC_LOG_TRACE("test.unit_test", "SpellAppliesAndRemovesShadowEmbrace %u", spellId);
            victim->SetFullHealth();
            FORCE_CAST(warlock, victim, spellId, SPELL_MISS_NONE, TriggerCastFlags(TRIGGERED_FULL_MASK | TRIGGERED_PROC_AS_NON_TRIGGERED));
            //ASSERT_INFO("After spell %u, warlock doesn't have Shadow Embrace.", spellId);
            TEST_HAS_AURA(victim, shadowEmbraceId);
            Wait(dotTime);
            //ASSERT_INFO("After spell %u, warlock still has Shadow Embrace.", spellId);
            TEST_HAS_NOT_AURA(victim, shadowEmbraceId);
        }

        void ApplyShadowEmbrace(TestPlayer* rogue, uint32 shadowEmbraceId)
        {
            if (!rogue->HasAura(shadowEmbraceId))
                rogue->AddAura(shadowEmbraceId, rogue);
        }

        void Test() override
        {
            TestPlayer* warlock = SpawnPlayer(CLASS_WARLOCK, RACE_ORC);
            TestPlayer* rogue = SpawnPlayer(CLASS_ROGUE, RACE_HUMAN);

            LearnTalent(warlock, Talents::Warlock::SHADOW_EMBRACE_RNK_5);
            float const shadowEmbraceFactor = 1 - 0.05f;

            uint32 const SHADOW_EMBRACE_AURA_RNK_5 = 32391;

            SpellAppliesAndRemovesShadowEmbrace(warlock, rogue, ClassSpells::Warlock::CORRUPTION_RNK_8, Seconds(18), SHADOW_EMBRACE_AURA_RNK_5);
            SpellAppliesAndRemovesShadowEmbrace(warlock, rogue, ClassSpells::Warlock::CURSE_OF_AGONY_RNK_7, Seconds(24), SHADOW_EMBRACE_AURA_RNK_5);
            SpellAppliesAndRemovesShadowEmbrace(warlock, rogue, ClassSpells::Warlock::SEED_OF_CORRUPTION_RNK_1, Seconds(18), SHADOW_EMBRACE_AURA_RNK_5);
            SpellAppliesAndRemovesShadowEmbrace(warlock, rogue, ClassSpells::Warlock::SIPHON_LIFE_RNK_6, Seconds(30), SHADOW_EMBRACE_AURA_RNK_5);

            // Physical damage reduced by 5%
            Creature* dummy = SpawnCreature();
            EQUIP_NEW_ITEM(rogue, 32837); // Warglaive of Azzinoth MH
            Wait(1500);
            EQUIP_NEW_ITEM(rogue, 32838); // Warglaive of Azzinoth OH
            WaitNextUpdate();
            int const sinisterStrikeBonus = 98;
            float const normalizedSwordSpeed = 2.4f;
            float const AP = rogue->GetTotalAttackPowerValue(BASE_ATTACK);
            float const armorFactor = 1 - (dummy->GetArmor() / (dummy->GetArmor() + 10557.5f));
            // Sinister strike
            uint32 const weaponMinDamage = 214 + (AP / 14 * normalizedSwordSpeed);
            uint32 const weaponMaxDamage = 398 + (AP / 14 * normalizedSwordSpeed);
            uint32 const expectedSinisterStrikeMin = (weaponMinDamage + sinisterStrikeBonus) * armorFactor * shadowEmbraceFactor;
            uint32 const expectedSinisterStrikeMax = (weaponMaxDamage + sinisterStrikeBonus) * armorFactor * shadowEmbraceFactor;
            ApplyShadowEmbrace(rogue, SHADOW_EMBRACE_AURA_RNK_5);
            TEST_DIRECT_SPELL_DAMAGE(rogue, dummy, ClassSpells::Rogue::SINISTER_STRIKE_RNK_10, expectedSinisterStrikeMin, expectedSinisterStrikeMax, false);
            // Melee
            uint32 const mhMinDamage = (214 + (AP / 14 * 2.8f)) * armorFactor * shadowEmbraceFactor;
            uint32 const mhMaxDamage = (398 + (AP / 14 * 2.8f)) * armorFactor * shadowEmbraceFactor;
            uint32 const ohMinDamage = (107 + (AP / 14 * 1.4f)) / 2.0f * armorFactor * shadowEmbraceFactor;
            uint32 const ohMaxDamage = (199 + (AP / 14 * 1.4f)) / 2.0f * armorFactor * shadowEmbraceFactor;
            ApplyShadowEmbrace(rogue, SHADOW_EMBRACE_AURA_RNK_5);
            TEST_MELEE_DAMAGE(rogue, dummy, BASE_ATTACK, mhMinDamage, mhMaxDamage, false);
            ApplyShadowEmbrace(rogue, SHADOW_EMBRACE_AURA_RNK_5);
            TEST_MELEE_DAMAGE(rogue, dummy, OFF_ATTACK, ohMinDamage, ohMaxDamage, false);
        }
    };

    std::shared_ptr<TestCase> GetTest() const override
    {
        return std::make_shared<ShadowEmbraceTestImpt>();
    }
};

class SiphonLifeTest : public TestCaseScript
{
public:
    SiphonLifeTest() : TestCaseScript("talents warlock siphon_life") { }

    class SiphonLifeTestImpt : public TestCase
    {
    public:
        SiphonLifeTestImpt() : TestCase(STATUS_PASSING) { }

        void TestCorruptionCastTime(TestPlayer* caster, Creature* victim, uint32 talentSpellId, uint32 talentFactor)
        {
            LearnTalent(caster, talentSpellId);
            uint32 const expectedCastTime = 2000 - talentFactor;
            TEST_SPELL_CAST_TIME(caster, ClassSpells::Warlock::CORRUPTION_RNK_8, expectedCastTime);
        }

        void Test() override
        {
            TestPlayer* warlock = SpawnRandomPlayer(CLASS_WARLOCK);
            Creature* dummy = SpawnCreature();

            warlock->DisableRegeneration(true);

            EQUIP_NEW_ITEM(warlock, 34336); // Sunflare - 292 SP

            uint32 const spellPower = warlock->GetInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + SPELL_SCHOOL_SHADOW);
            TEST_ASSERT(spellPower == 292);

            uint32 const expectedSiphonLifeManaCost = 410;
            TEST_POWER_COST(warlock, ClassSpells::Warlock::SIPHON_LIFE_RNK_6, POWER_MANA, expectedSiphonLifeManaCost);

            // Damage
            float const spellCoefficient = ClassSpellsCoeff::Warlock::SIPHON_LIFE; // DrDamage & WoWWiki coeff
            float const tickAmount = 10.0f;
            uint32 const expectedSLTick = ClassSpellsDamage::Warlock::SIHPON_LIFE_RNK_6_TICK + spellPower * spellCoefficient / tickAmount;
            uint32 const expectedSLTotal = expectedSLTick * tickAmount;
            warlock->SetHealth(1);
            TEST_DOT_DAMAGE(warlock, dummy, ClassSpells::Warlock::SIPHON_LIFE_RNK_6, expectedSLTotal, true);
            TEST_ASSERT(warlock->GetHealth() == 1 + expectedSLTotal);
        }
    };

    std::shared_ptr<TestCase> GetTest() const override
    {
        return std::make_shared<SiphonLifeTestImpt>();
    }
};

class CurseOfExhaustionTest : public TestCaseScript
{
public:

    CurseOfExhaustionTest() : TestCaseScript("talents warlock curse_of_exhaustion") { }

    class CurseOfExhaustionTestImpt : public TestCase
    {
    public:
        CurseOfExhaustionTestImpt() : TestCase(STATUS_WIP) { }

        void Test() override
        {
            TestPlayer* warlock = SpawnPlayer(CLASS_WARLOCK, RACE_ORC);
            TestPlayer* warrior = SpawnPlayer(CLASS_WARRIOR, RACE_HUMAN);

            LearnTalent(warlock, Talents::Warlock::CURSE_OF_EXHAUSTION_RNK_1);
            float const speedMalusFactor = 1 - 0.3f;

            float const warriorSpeed = warrior->GetSpeed(MOVE_RUN);
            float const expectedSpeed = warrior->GetSpeed(MOVE_RUN) * speedMalusFactor;
            FORCE_CAST(warlock, warrior, ClassSpells::Warlock::CURSE_OF_EXHAUSTION_RNK_1);
            ASSERT_INFO("Warrior has %f speed, %f was expected.", warrior->GetSpeed(MOVE_RUN), expectedSpeed);
            TEST_ASSERT(Between<float>(warrior->GetSpeed(MOVE_RUN), expectedSpeed - 0.1f, expectedSpeed + 0.1f));
            TEST_AURA_MAX_DURATION(warrior, ClassSpells::Warlock::CURSE_OF_EXHAUSTION_RNK_1, Seconds(12));

            TEST_POWER_COST(warlock, ClassSpells::Warlock::CURSE_OF_EXHAUSTION_RNK_1, POWER_MANA, 156);
        }
    };

    std::shared_ptr<TestCase> GetTest() const override
    {
        return std::make_shared<CurseOfExhaustionTestImpt>();
    }
};

class ShadowMasteryTest : public TestCaseScript
{
public:

	ShadowMasteryTest() : TestCaseScript("talents warlock shadow_mastery") { }

	class ShadowMasteryTestImpt : public TestCase
	{
	public:
        /*
            Bugs:
                - Drain Soul is not affected by the talent, should.
                - Drain Life and Siphon Life heals gain double effect, should not.
        */
		ShadowMasteryTestImpt() : TestCase(STATUS_KNOWN_BUG) { }

		void Test() override
		{
			TestPlayer* warlock = SpawnRandomPlayer(CLASS_WARLOCK);
            Creature* dummy = SpawnCreature();

            dummy->DisableRegeneration(true);
            warlock->DisableRegeneration(true);

            LearnTalent(warlock, Talents::Warlock::SHADOW_MASTERY_RNK_5);
            float const shadowMasteryFactor = 1.1f;

            // Corruption
			float const expectedCorruptionDamage = ClassSpellsDamage::Warlock::CORRUPTION_RNK_8_TOTAL * shadowMasteryFactor;
            TEST_DOT_DAMAGE(warlock, dummy, ClassSpells::Warlock::CORRUPTION_RNK_8, expectedCorruptionDamage, false);

            // Curse of Agony
			float const expectedCoaDamage = ClassSpellsDamage::Warlock::CURSE_OF_AGONY_RNK_7_TOTAL * shadowMasteryFactor;
            TEST_DOT_DAMAGE(warlock, dummy, ClassSpells::Warlock::CURSE_OF_AGONY_RNK_7, expectedCoaDamage, false);

            // Curse of Doom should not be affected by Shadow Mastery cf Leulier's DPS Spreadsheet v1.12 (http://www.leulier.fr/spreadsheet/) and WoWWiki also mentions it
            TEST_DOT_DAMAGE(warlock, dummy, ClassSpells::Warlock::CURSE_OF_DOOM_RNK_2, ClassSpellsDamage::Warlock::CURSE_OF_DOOM_RNK_2, false);

            // Death Coil
            uint32 const spellLevel = 68;
            float const dmgPerLevel = 3.4f;
            float const dmgPerLevelGain = std::max(warlock->GetLevel() - spellLevel, uint32(0)) * dmgPerLevel;
			float const expectedDeathCoilDamage = (ClassSpellsDamage::Warlock::DEATH_COIL_RNK_4 + dmgPerLevelGain) * shadowMasteryFactor;
            TEST_DIRECT_SPELL_DAMAGE(warlock, dummy, ClassSpells::Warlock::DEATH_COIL_RNK_4, expectedDeathCoilDamage, expectedDeathCoilDamage, false);

            // Drain Life
            float const drainLifeTickAmount = 5.0f;
            uint32 const expectedDrainLifeTick = ClassSpellsDamage::Warlock::DRAIN_LIFE_RNK_8_TICK * shadowMasteryFactor;
            uint32 const expectedDrainLifeTotal = drainLifeTickAmount * expectedDrainLifeTick;
            uint32 const dummyExpectedHealth = dummy->GetHealth() - expectedDrainLifeTotal;
            warlock->SetHealth(1);
            FORCE_CAST(warlock, dummy, ClassSpells::Warlock::DRAIN_LIFE_RNK_8);
            Wait(5500);
            ASSERT_INFO("Dummy has %u HP but %u was expected.", dummy->GetHealth(), dummyExpectedHealth);
            TEST_ASSERT(dummy->GetHealth() == dummyExpectedHealth);
            ASSERT_INFO("Warlock has %u HP but %u was expected.", warlock->GetHealth(), 1 + expectedDrainLifeTotal);
            TEST_ASSERT(warlock->GetHealth() == 1 + expectedDrainLifeTotal);

            // Drain Soul
            float const drainSoulTickAmount = 5.0f;
            uint32 const expectedDrainSoulTick = ClassSpellsDamage::Warlock::DRAIN_SOUL_RNK_5_TICK * shadowMasteryFactor;
            TEST_CHANNEL_DAMAGE(warlock, dummy, ClassSpells::Warlock::DRAIN_SOUL_RNK_5, ClassSpells::Warlock::DRAIN_SOUL_RNK_5, drainSoulTickAmount, expectedDrainSoulTick);

            // Seed of Corruption
            float const seedOfCorruptionTickAmount = 6.0f;
            uint32 const expectedSoCTick = ClassSpellsDamage::Warlock::SEED_OF_CORRUPTION_RNK_1_TICK * shadowMasteryFactor;
            uint32 const expectedSoCTotalAmount = seedOfCorruptionTickAmount * expectedSoCTick;
            TEST_DOT_DAMAGE(warlock, dummy, ClassSpells::Warlock::SEED_OF_CORRUPTION_RNK_1, expectedSoCTotalAmount, true);

            // Siphon Life 
            float const siphonLifetickAmount = 10.0f;
            uint32 const expectedSLTotalAmount = ClassSpellsDamage::Warlock::SIHPON_LIFE_RNK_6_TICK * siphonLifetickAmount * shadowMasteryFactor;
            warlock->SetHealth(1);
            TEST_DOT_DAMAGE(warlock, dummy, ClassSpells::Warlock::SIPHON_LIFE_RNK_6, expectedSLTotalAmount, true);
            ASSERT_INFO("Warlock has %u HP but %u was expected.", warlock->GetHealth(), 1 + expectedSLTotalAmount);
            TEST_ASSERT(warlock->GetHealth() == 1 + expectedSLTotalAmount);

            // Shadow Bolt
            uint32 const expectedShadowBoltMin = ClassSpellsDamage::Warlock::SHADOW_BOLT_RNK_11_MIN * shadowMasteryFactor;
            uint32 const expectedShadowBoltMax = ClassSpellsDamage::Warlock::SHADOW_BOLT_RNK_11_MAX * shadowMasteryFactor;
            TEST_DIRECT_SPELL_DAMAGE(warlock, dummy, ClassSpells::Warlock::SHADOW_BOLT_RNK_11, expectedShadowBoltMin, expectedShadowBoltMax, false);

            // Shadowburn
            uint32 const expectedShadowBurnMin = ClassSpellsDamage::Warlock::SHADOWBURN_RNK_8_MIN * shadowMasteryFactor;
            uint32 const expectedShadowBurnMax = ClassSpellsDamage::Warlock::SHADOWBURN_RNK_8_MAX * shadowMasteryFactor;
            TEST_DIRECT_SPELL_DAMAGE(warlock, dummy, ClassSpells::Warlock::SHADOWBURN_RNK_8, expectedShadowBurnMin, expectedShadowBurnMax, false);
		}
	};

	std::shared_ptr<TestCase> GetTest() const override
	{
		return std::make_shared<ShadowMasteryTestImpt>();
	}
};

class ContagionTest : public TestCaseScript
{
public:

	ContagionTest() : TestCaseScript("talents warlock contagion") { }

	class ContagionTestImpt : public TestCase
	{
	public:
		ContagionTestImpt() : TestCase(STATUS_WIP) { } // Needs to fix Seed of Corruption spell

		void Test() override
		{
			TestPlayer* warlock = SpawnPlayer(CLASS_WARLOCK, RACE_ORC);
            Creature* dummy = SpawnCreature();

            LearnTalent(warlock, Talents::Warlock::CONTAGION_RNK_5);
            float const contagionFactor = 1.05f;

            // Corruption
			uint32 const expectedCorruptionDamage = ClassSpellsDamage::Warlock::CORRUPTION_RNK_8_TOTAL * contagionFactor;
            //TEST_DOT_DAMAGE(warlock, dummy, ClassSpells::Warlock::CORRUPTION_RNK_8, expectedCorruptionDamage, false);

            // Curse of Agony
			uint32 const expectedCoADamage = ClassSpellsDamage::Warlock::CURSE_OF_AGONY_RNK_7_TOTAL * contagionFactor;
            //TEST_DOT_DAMAGE(warlock, dummy, ClassSpells::Warlock::CURSE_OF_AGONY_RNK_7, expectedCoADamage, false);

            // Seed of Corruption
			uint32 const expectedSoCDamage = ClassSpellsDamage::Warlock::SEED_OF_CORRUPTION_RNK_1_TICK * contagionFactor;
            //TEST_DOT_DAMAGE(warlock, dummy, ClassSpells::Warlock::SEED_OF_CORRUPTION_RNK_1, expectedSoCDamage, false);

            Creature* dummy2 = SpawnCreature();
            uint32 const expectedDetonationMin = ClassSpellsDamage::Warlock::SEED_OF_CORRUPTION_RNK_1_MIN * contagionFactor;
            uint32 const expectedDetonationMax = ClassSpellsDamage::Warlock::SEED_OF_CORRUPTION_RNK_1_MAX * contagionFactor;
            //FIXME: next line not working ("GetSpellDamageDoneInfoTo found no data for this victim (Testing Creature)")
            //TEST_DIRECT_SPELL_DAMAGE(warlock, dummy2, ClassSpells::Warlock::SEED_OF_CORRUPTION_RNK_1_DETONATION, expectedDetonationMin, expectedDetonationMax, false);
            dummy2->DespawnOrUnsummon();

            // Reduces the chance your Affliction spells wtill be dispelled by 30% (5/5)
            const float dispelTalentFactor = 30.f;
            float const expectedResist = dispelTalentFactor + 3.f; // priest has 0 spell hit rating

            _location.MoveInFront(_location, 5.f);
            TestPlayer* priest = SpawnPlayer(CLASS_PRIEST, RACE_HUMAN);
            WaitNextUpdate();
            warlock->ForceSpellHitResult(SPELL_MISS_NONE);

            //Kelno: FIXME: we cant use TEST_SPELL_HIT_CHANCE_CALLBACK, spells is supposed to always hit but fails to dispel with a SMSG_DISPEL_FAILED sent seperately.
            ASSERT_INFO("Corruption");
            TEST_SPELL_HIT_CHANCE_CALLBACK(priest, priest, ClassSpells::Priest::DISPEL_MAGIC_RNK_1, expectedResist, SPELL_MISS_RESIST, [warlock](Unit* caster, Unit* target) {
                warlock->CastSpell(caster, ClassSpells::Warlock::CORRUPTION_RNK_8, TRIGGERED_FULL_MASK);
            });
            WaitNextUpdate();
            ASSERT_INFO("Death Coil");
            TEST_SPELL_HIT_CHANCE_CALLBACK(priest, priest, ClassSpells::Priest::DISPEL_MAGIC_RNK_1, expectedResist, SPELL_MISS_RESIST, [warlock](Unit* caster, Unit* target) {
                warlock->CastSpell(caster, ClassSpells::Warlock::DEATH_COIL_RNK_4, TRIGGERED_FULL_MASK);
            });
            WaitNextUpdate();
            ASSERT_INFO("Drain Life");
            TEST_SPELL_HIT_CHANCE_CALLBACK(priest, priest, ClassSpells::Priest::DISPEL_MAGIC_RNK_1, expectedResist, SPELL_MISS_RESIST, [warlock](Unit* caster, Unit* target) {
                warlock->CastSpell(caster, ClassSpells::Warlock::DRAIN_LIFE_RNK_8);
            });
            WaitNextUpdate();
            ASSERT_INFO("Drain Mana");
            TEST_SPELL_HIT_CHANCE_CALLBACK(priest, warlock, ClassSpells::Priest::DISPEL_MAGIC_RNK_1, expectedResist, SPELL_MISS_RESIST, [](Unit* caster, Unit* target) {
                target->CastSpell(caster, ClassSpells::Warlock::DRAIN_MANA_RNK_6);
            });
            WaitNextUpdate();
            ASSERT_INFO("Fear");
            TEST_SPELL_HIT_CHANCE_CALLBACK(priest, warlock, ClassSpells::Priest::DISPEL_MAGIC_RNK_1, expectedResist, SPELL_MISS_RESIST, [](Unit* caster, Unit* target) {
                target->CastSpell(caster, ClassSpells::Warlock::FEAR_RNK_3, TRIGGERED_FULL_MASK);
            });
            WaitNextUpdate();
            ASSERT_INFO("Howl of Terror");
            TEST_SPELL_HIT_CHANCE_CALLBACK(priest, warlock, ClassSpells::Priest::DISPEL_MAGIC_RNK_1, expectedResist, SPELL_MISS_RESIST, [](Unit* caster, Unit* target) {
                target->CastSpell(caster, ClassSpells::Warlock::HOWL_OF_TERROR_RNK_2, TRIGGERED_FULL_MASK);
            });
            WaitNextUpdate();
            ASSERT_INFO("Seed of Corruption");
            TEST_SPELL_HIT_CHANCE_CALLBACK(priest, warlock, ClassSpells::Priest::DISPEL_MAGIC_RNK_1, expectedResist, SPELL_MISS_RESIST, [](Unit* caster, Unit* target) {
                target->CastSpell(caster, ClassSpells::Warlock::SEED_OF_CORRUPTION_RNK_1, TRIGGERED_FULL_MASK);
            });
            WaitNextUpdate();
            ASSERT_INFO("Siphon Life");
            TEST_SPELL_HIT_CHANCE_CALLBACK(priest, warlock, ClassSpells::Priest::DISPEL_MAGIC_RNK_1, expectedResist, SPELL_MISS_RESIST, [](Unit* caster, Unit* target) {
                target->CastSpell(caster, ClassSpells::Warlock::SIPHON_LIFE_RNK_6, TRIGGERED_FULL_MASK);
            });
            WaitNextUpdate();
            ASSERT_INFO("Unstable Affliction");
            TEST_SPELL_HIT_CHANCE_CALLBACK(priest, warlock, ClassSpells::Priest::DISPEL_MAGIC_RNK_1, expectedResist, SPELL_MISS_RESIST, [](Unit* caster, Unit* target) {
                target->CastSpell(caster, ClassSpells::Warlock::UNSTABLE_AFFLICTION_RNK_3, TRIGGERED_FULL_MASK);
            });
            WaitNextUpdate();

            TestPlayer* druid = SpawnPlayer(CLASS_DRUID, RACE_NIGHTELF);
            druid->SetMaxHealth(std::numeric_limits<uint32>::max());
            ASSERT_INFO("Curse of Agony");
            TEST_SPELL_HIT_CHANCE_CALLBACK(druid, warlock, ClassSpells::Druid::REMOVE_CURSE_RNK_1, expectedResist, SPELL_MISS_RESIST, [](Unit* caster, Unit* target) {
                target->CastSpell(caster, ClassSpells::Warlock::CURSE_OF_AGONY_RNK_7, TRIGGERED_FULL_MASK);
            });
            WaitNextUpdate();
            ASSERT_INFO("Curse of Recklessness");
            TEST_SPELL_HIT_CHANCE_CALLBACK(druid, warlock, ClassSpells::Druid::REMOVE_CURSE_RNK_1, expectedResist, SPELL_MISS_RESIST, [](Unit* caster, Unit* target) {
                target->CastSpell(caster, ClassSpells::Warlock::CURSE_OF_RECKLESSNESS_RNK_5, TRIGGERED_FULL_MASK);
            });
            WaitNextUpdate();
            ASSERT_INFO("Curse of the elements");
            TEST_SPELL_HIT_CHANCE_CALLBACK(druid, warlock, ClassSpells::Druid::REMOVE_CURSE_RNK_1, expectedResist, SPELL_MISS_RESIST, [](Unit* caster, Unit* target) {
                target->CastSpell(caster, ClassSpells::Warlock::CURSE_OF_THE_ELEMENTS_RNK_4, TRIGGERED_FULL_MASK);
            });
            WaitNextUpdate();
            ASSERT_INFO("Curse of Tongues");
            TEST_SPELL_HIT_CHANCE_CALLBACK(druid, warlock, ClassSpells::Druid::REMOVE_CURSE_RNK_1, expectedResist, SPELL_MISS_RESIST, [](Unit* caster, Unit* target) {
                target->CastSpell(caster, ClassSpells::Warlock::CURSE_OF_TONGUES_RNK_2, TRIGGERED_FULL_MASK);
            });
            WaitNextUpdate();
            ASSERT_INFO("Curse of Weakness");
            TEST_SPELL_HIT_CHANCE_CALLBACK(druid, warlock, ClassSpells::Druid::REMOVE_CURSE_RNK_1, expectedResist, SPELL_MISS_RESIST, [](Unit* caster, Unit* target) {
                target->CastSpell(caster, ClassSpells::Warlock::CURSE_OF_WEAKNESS_RNK_8, TRIGGERED_FULL_MASK);
            });
		}
	};

	std::shared_ptr<TestCase> GetTest() const override
	{
		return std::make_shared<ContagionTestImpt>();
	}
};

class DarkPactTest : public TestCaseScript
{
public:
    DarkPactTest() : TestCaseScript("talents warlock dark_pact") { }

    class DarkPactTestImpt : public TestCase
    {
    public:
        DarkPactTestImpt() : TestCase(STATUS_KNOWN_BUG) { } // Not affected by Spell Coefficient

        void Test() override
        {
            TestPlayer* warlock = SpawnRandomPlayer(CLASS_WARLOCK);
            warlock->DisableRegeneration(true);

            EQUIP_NEW_ITEM(warlock, 34336); // Sunflare - 292 SP

            uint32 const spellPower = warlock->GetInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + SPELL_SCHOOL_SHADOW);
            TEST_ASSERT(spellPower == 292);

            TEST_CAST(warlock, warlock, ClassSpells::Warlock::DARK_PACT_RNK_4, SPELL_FAILED_NO_PET);

            // Summon Voidwalker
            TEST_CAST(warlock, warlock, ClassSpells::Warlock::SUMMON_VOIDWALKER_RNK_1, SPELL_CAST_OK, TRIGGERED_FULL_MASK);
            WaitNextUpdate();
            Guardian* voidwalker = warlock->GetGuardianPet();
            TEST_ASSERT(voidwalker != nullptr);
            voidwalker->DisableRegeneration(true);

            uint32 expectedManaDrained = ClassSpellsDamage::Warlock::DARK_PACT_RNK_4 + spellPower * ClassSpellsCoeff::Warlock::DARK_PACT; // WoWWiki
            uint32 expectedPetMana = std::max(voidwalker->GetPower(POWER_MANA) - expectedManaDrained, uint32(0));
            warlock->SetPower(POWER_MANA, 0);
            TEST_CAST(warlock, warlock, ClassSpells::Warlock::DARK_PACT_RNK_4);
            ASSERT_INFO("Voidwalker has %u MP but should have %u MP.", voidwalker->GetPower(POWER_MANA), expectedPetMana);
            TEST_ASSERT(voidwalker->GetPower(POWER_MANA) == expectedPetMana);
            ASSERT_INFO("Warlock has %u MP but should have %u MP.", warlock->GetPower(POWER_MANA), expectedManaDrained);
            TEST_ASSERT(warlock->GetPower(POWER_MANA) == expectedManaDrained);
        }
    };

    std::shared_ptr<TestCase> GetTest() const override
    {
        return std::make_shared<DarkPactTestImpt>();
    }
};

class ImprovedHowOfTerrorTest : public TestCaseScript
{
public:
    ImprovedHowOfTerrorTest() : TestCaseScript("talents warlock improved_howl_of_terror") { }

    class ImprovedHowOfTerrorTestImpt : public TestCase
    {
    public:
        ImprovedHowOfTerrorTestImpt() : TestCase(STATUS_PASSING) { }

        void Test() override
        {
            TestPlayer* warlock = SpawnRandomPlayer(CLASS_WARLOCK);

            LearnTalent(warlock, Talents::Warlock::IMPROVED_HOWL_OF_TERROR_RNK_1);
            TEST_SPELL_CAST_TIME(warlock, ClassSpells::Warlock::HOWL_OF_TERROR_RNK_2, 700);
            LearnTalent(warlock, Talents::Warlock::IMPROVED_HOWL_OF_TERROR_RNK_2);
            TEST_SPELL_CAST_TIME(warlock, ClassSpells::Warlock::HOWL_OF_TERROR_RNK_2, uint32(0));
        }
    };

    std::shared_ptr<TestCase> GetTest() const override
    {
        return std::make_shared<ImprovedHowOfTerrorTestImpt>();
    }
};

class MaledictionTest : public TestCaseScript
{
public:
    MaledictionTest() : TestCaseScript("talents warlock malediction") { }

    class MaledictionTestImpt : public TestCase
    {
    public:
        MaledictionTestImpt() : TestCase(STATUS_PASSING) { }

        void Test() override
        {
            TestPlayer* warlock = SpawnPlayer(CLASS_WARLOCK, RACE_HUMAN);
            Creature* dummy = SpawnCreature();

            LearnTalent(warlock, Talents::Warlock::MALEDICTION_RNK_3);
            float const talentFactor = 1.13f;

            // Apply CoE
            FORCE_CAST(warlock, dummy, ClassSpells::Warlock::CURSE_OF_THE_ELEMENTS_RNK_4);

            // Increase damage taken by Shadow, Fire, Arcane and Frost by 10%
            TEST_DIRECT_SPELL_DAMAGE(warlock, dummy, ClassSpells::Warlock::SHADOW_BOLT_RNK_11, ClassSpellsDamage::Warlock::SHADOW_BOLT_RNK_11_MIN * talentFactor, ClassSpellsDamage::Warlock::SHADOW_BOLT_RNK_11_MAX * talentFactor, false);
            TEST_DIRECT_SPELL_DAMAGE(warlock, dummy, ClassSpells::Warlock::INCINERATE_RNK_2, ClassSpellsDamage::Warlock::INCINERATE_RNK_2_MIN * talentFactor, ClassSpellsDamage::Warlock::INCINERATE_RNK_2_MAX * talentFactor, false);
            TestPlayer* druid = SpawnPlayer(CLASS_DRUID, RACE_NIGHTELF);
            TEST_DIRECT_SPELL_DAMAGE(druid, dummy, ClassSpells::Druid::STARFIRE_RNK_8, ClassSpellsDamage::Druid::STARFIRE_RNK_8_MIN * talentFactor, ClassSpellsDamage::Druid::STARFIRE_RNK_8_MAX * talentFactor, false);
            TestPlayer* mage = SpawnPlayer(CLASS_MAGE, RACE_HUMAN);
            TEST_DIRECT_SPELL_DAMAGE(mage, dummy, ClassSpells::Mage::ICE_LANCE_RNK_1, ClassSpellsDamage::Mage::ICE_LANCE_RNK_1_MIN * talentFactor, ClassSpellsDamage::Mage::ICE_LANCE_RNK_1_MAX * talentFactor, false);
        }
    };

    std::shared_ptr<TestCase> GetTest() const override
    {
        return std::make_shared<MaledictionTestImpt>();
    }
};

class UnstableAfflictionTest : public TestCaseScript
{
public:
    UnstableAfflictionTest() : TestCaseScript("talents warlock unstable_affliction") { }

    class UnstableAfflictionTestImpt : public TestCase
    {
    public:
        UnstableAfflictionTestImpt() : TestCase(STATUS_KNOWN_BUG) { } // Wrong Direct Damage spell coeff

        void Test() override
        {
            TestPlayer* warlock = SpawnPlayer(CLASS_WARLOCK, RACE_HUMAN);
            Creature* dummy = SpawnCreature();

            EQUIP_NEW_ITEM(warlock, 34336); // Sunflare - 292 SP

            uint32 const spellPower = warlock->GetInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + SPELL_SCHOOL_SHADOW);
            TEST_ASSERT(spellPower == 292);

            uint32 const expectedUnstableAfflictionManaCost = 400;
            TEST_POWER_COST(warlock, ClassSpells::Warlock::UNSTABLE_AFFLICTION_RNK_3, POWER_MANA, expectedUnstableAfflictionManaCost);

            // DoT
            float const spellCoefficient = ClassSpellsCoeff::Warlock::UNSTABLE_AFFLICTION_DOT;
            float const tickAmount = 6.0f;
            uint32 const expectedUnstableAfflictionTick = ClassSpellsDamage::Warlock::UNSTABLE_AFFLICTION_RNK_3_TICK + spellPower * spellCoefficient / tickAmount;
            uint32 const expectedUnstableAfflictionTotal = expectedUnstableAfflictionTick * tickAmount;
            TEST_DOT_DAMAGE(warlock, dummy, ClassSpells::Warlock::UNSTABLE_AFFLICTION_RNK_3, expectedUnstableAfflictionTotal, true);

            // Dispell & damage
            TestPlayer* priest = SpawnPlayer(CLASS_PRIEST, RACE_BLOODELF);
            priest->SetMaxHealth(uint32(10000));
            priest->SetFullHealth();
            priest->DisableRegeneration(true);
            WaitNextUpdate();
            uint32 const expectedUADamage = ClassSpellsDamage::Warlock::UNSTABLE_AFFLICTION_RNK_3_DISPELLED + spellPower * ClassSpellsCoeff::Warlock::UNSTABLE_AFFLICTION;
            uint32 const expectedPriestHealth = priest->GetHealth() - expectedUADamage;
            FORCE_CAST(warlock, priest, ClassSpells::Warlock::UNSTABLE_AFFLICTION_RNK_3, SPELL_MISS_NONE, TRIGGERED_FULL_MASK);
            FORCE_CAST(priest, priest, ClassSpells::Priest::DISPEL_MAGIC_RNK_2);
            TEST_AURA_MAX_DURATION(priest, ClassSpells::Warlock::UNSTABLE_AFFLICTION_SILENCE, Seconds(5));
            TEST_CAST(priest, priest, ClassSpells::Priest::RENEW_RNK_12, SPELL_FAILED_SILENCED);
            ASSERT_INFO("Priest has %u HP but %u was expected.", priest->GetHealth(), expectedPriestHealth);
            TEST_ASSERT(priest->GetHealth() == expectedPriestHealth);
        }
    };

    std::shared_ptr<TestCase> GetTest() const override
    {
        return std::make_shared<UnstableAfflictionTestImpt>();
    }
};

class ImprovedHealthstoneTest : public TestCaseScript
{
public:
	ImprovedHealthstoneTest() : TestCaseScript("talents warlock improved_healthstone") { }

	class ImprovedHealthstoneTestImpt : public TestCase
	{
	public:
		ImprovedHealthstoneTestImpt() : TestCase(STATUS_PASSING) { }

        void TestImprovedHealthstone(TestPlayer* caster, float talentFactor, uint32 healthstoneSpellId, uint32 healthstoneItemId, uint32 healthRestored)
        {
            caster->SetHealth(1);
            uint32 const expectedHealthRestored = 1 + healthRestored * talentFactor;
            uint32 const expectedHealthRestoredCrit = 1 + healthRestored * talentFactor * 1.5f;
            TEST_CAST(caster, caster, healthstoneSpellId, SPELL_CAST_OK, TRIGGERED_FULL_MASK);
            TEST_ASSERT(caster->GetItemCount(healthstoneItemId, false) == 1);
            USE_ITEM(caster, caster, healthstoneItemId);
            ASSERT_INFO("After Healthstone %u, Warlock should have %u HP but has %u.", healthstoneItemId, expectedHealthRestored, caster->GetHealth());
            TEST_ASSERT(caster->GetHealth() == expectedHealthRestored || caster->GetHealth() == expectedHealthRestoredCrit);
            caster->GetSpellHistory()->ResetAllCooldowns();
        }

		void Test() override
		{
			TestPlayer* warlock = SpawnRandomPlayer(CLASS_WARLOCK);
            warlock->DisableRegeneration(true);

            LearnTalent(warlock, Talents::Warlock::IMPROVED_HEALTHSTONE_RNK_1);
            float const improvedHealthStoneFactorRank1 = 1.1f;
            TestImprovedHealthstone(warlock, improvedHealthStoneFactorRank1, ClassSpells::Warlock::CREATE_HEALTHSTONE_RNK_1, 19004, ClassSpellsDamage::Warlock::CREATE_HEALTHSTONE_RNK_1_HP_RESTORED);
            TestImprovedHealthstone(warlock, improvedHealthStoneFactorRank1, ClassSpells::Warlock::CREATE_HEALTHSTONE_RNK_2, 19006, ClassSpellsDamage::Warlock::CREATE_HEALTHSTONE_RNK_2_HP_RESTORED);
            TestImprovedHealthstone(warlock, improvedHealthStoneFactorRank1, ClassSpells::Warlock::CREATE_HEALTHSTONE_RNK_3, 19008, ClassSpellsDamage::Warlock::CREATE_HEALTHSTONE_RNK_3_HP_RESTORED);
            TestImprovedHealthstone(warlock, improvedHealthStoneFactorRank1, ClassSpells::Warlock::CREATE_HEALTHSTONE_RNK_4, 19010, ClassSpellsDamage::Warlock::CREATE_HEALTHSTONE_RNK_4_HP_RESTORED);
            TestImprovedHealthstone(warlock, improvedHealthStoneFactorRank1, ClassSpells::Warlock::CREATE_HEALTHSTONE_RNK_5, 19012, ClassSpellsDamage::Warlock::CREATE_HEALTHSTONE_RNK_5_HP_RESTORED);
            TestImprovedHealthstone(warlock, improvedHealthStoneFactorRank1, ClassSpells::Warlock::CREATE_HEALTHSTONE_RNK_6, 22104, ClassSpellsDamage::Warlock::CREATE_HEALTHSTONE_RNK_6_HP_RESTORED);

            LearnTalent(warlock, Talents::Warlock::IMPROVED_HEALTHSTONE_RNK_2);
            float const improvedHealthStoneFactorRank2 = 1.2f;
            TestImprovedHealthstone(warlock, improvedHealthStoneFactorRank2, ClassSpells::Warlock::CREATE_HEALTHSTONE_RNK_1, 19005, ClassSpellsDamage::Warlock::CREATE_HEALTHSTONE_RNK_1_HP_RESTORED);
            TestImprovedHealthstone(warlock, improvedHealthStoneFactorRank2, ClassSpells::Warlock::CREATE_HEALTHSTONE_RNK_2, 19007, ClassSpellsDamage::Warlock::CREATE_HEALTHSTONE_RNK_2_HP_RESTORED);
            TestImprovedHealthstone(warlock, improvedHealthStoneFactorRank2, ClassSpells::Warlock::CREATE_HEALTHSTONE_RNK_3, 19009, ClassSpellsDamage::Warlock::CREATE_HEALTHSTONE_RNK_3_HP_RESTORED);
            TestImprovedHealthstone(warlock, improvedHealthStoneFactorRank2, ClassSpells::Warlock::CREATE_HEALTHSTONE_RNK_4, 19011, ClassSpellsDamage::Warlock::CREATE_HEALTHSTONE_RNK_4_HP_RESTORED);
            TestImprovedHealthstone(warlock, improvedHealthStoneFactorRank2, ClassSpells::Warlock::CREATE_HEALTHSTONE_RNK_5, 19013, ClassSpellsDamage::Warlock::CREATE_HEALTHSTONE_RNK_5_HP_RESTORED);
            TestImprovedHealthstone(warlock, improvedHealthStoneFactorRank2, ClassSpells::Warlock::CREATE_HEALTHSTONE_RNK_6, 22105, ClassSpellsDamage::Warlock::CREATE_HEALTHSTONE_RNK_6_HP_RESTORED);
		}
	};

	std::shared_ptr<TestCase> GetTest() const override
	{
		return std::make_shared<ImprovedHealthstoneTestImpt>();
	}
};

class DemonicEmbraceTest : public TestCaseScript
{
public:
	DemonicEmbraceTest() : TestCaseScript("talents warlock demonic_embrace") { }

	class DemonicEmbraceTestImpt : public TestCase
	{
	public:
		DemonicEmbraceTestImpt() : TestCase(STATUS_PASSING) { }

		void Test() override
		{
			TestPlayer* warlock = SpawnRandomPlayer(CLASS_WARLOCK);

            float const demonicEmbraceStaminaFactor = 1.15f;
            float const demonicEmbraceSpiritFactor = 0.95f;

            float const expectedWarlockStamina = warlock->GetStat(STAT_STAMINA) * demonicEmbraceStaminaFactor;
            float const expectedWarlockSpirit = warlock->GetStat(STAT_SPIRIT) * demonicEmbraceSpiritFactor;

			LearnTalent(warlock, Talents::Warlock::DEMONIC_EMBRACE_RNK_5);
			TEST_ASSERT(Between<float>(warlock->GetStat(STAT_STAMINA), expectedWarlockStamina - 1, expectedWarlockStamina + 1));
			TEST_ASSERT(Between<float>(warlock->GetStat(STAT_SPIRIT), expectedWarlockSpirit - 1, expectedWarlockSpirit + 1));
		}
	};

	std::shared_ptr<TestCase> GetTest() const override
	{
		return std::make_shared<DemonicEmbraceTestImpt>();
	}
};

class ImprovedHealthFunnelTest : public TestCaseScript
{
public:
	ImprovedHealthFunnelTest() : TestCaseScript("talents warlock improved_health_funnel") { }

	class ImprovedHealthFunnelTestImpt : public TestCase
	{
	public:
		ImprovedHealthFunnelTestImpt() : TestCase(STATUS_KNOWN_BUG) { } // Talent is working but spell is not, so it will fail as long as the spell test is failing

		void Test() override
		{
			TestPlayer* warlock = SpawnRandomPlayer(CLASS_WARLOCK);
            warlock->DisableRegeneration(true);

            LearnTalent(warlock, Talents::Warlock::IMPROVED_HEALTH_FUNNEL_RNK_2);
            float const talentHealthTransferredFactor = 1.2f;
            float const talentInitialCostFactor = 0.8f;

            // Summon Voidwalker
            TEST_CAST(warlock, warlock, ClassSpells::Warlock::SUMMON_VOIDWALKER_RNK_1, SPELL_CAST_OK, TRIGGERED_FULL_MASK);
            WaitNextUpdate();
            Guardian* voidwalker = warlock->GetGuardianPet();
            TEST_ASSERT(voidwalker != nullptr);
            voidwalker->DisableRegeneration(true);
            voidwalker->SetHealth(1);

            // Calculate new health restored and initial cost
            float const tickAmount = 10.0f;
            uint32 const totalHealthFunnelHeal = tickAmount * ClassSpellsDamage::Warlock::HEALTH_FUNNEL_RNK_8_HEAL_PER_TICK * talentHealthTransferredFactor;
            uint32 const expectedTickAmount = totalHealthFunnelHeal / tickAmount;
            uint32 const expectedInitialCost = ClassSpellsDamage::Warlock::HEALTH_FUNNEL_RNK_8_HP_COST * talentInitialCostFactor;
            uint32 const totalHealthCost = tickAmount * ClassSpellsDamage::Warlock::HEALTH_FUNNEL_RNK_8_HP_PER_TICK + expectedInitialCost;

            uint32 const expectedWarlockHealth = warlock->GetHealth() - totalHealthCost;
            uint32 const expectedVoidwalkerHealth = voidwalker->GetHealth() + expectedTickAmount * tickAmount;

            Wait(5000);
            TEST_CAST(warlock, voidwalker, ClassSpells::Warlock::HEALTH_FUNNEL_RNK_8);
            Wait(Seconds(11));
            ASSERT_INFO("Warlock has %u HP, %u was expected.", warlock->GetHealth(), expectedWarlockHealth);
            TEST_ASSERT(warlock->GetHealth() == expectedWarlockHealth);
            ASSERT_INFO("Voidwalker has %u HP, %u was expected.", voidwalker->GetHealth(), expectedVoidwalkerHealth);
            TEST_ASSERT(voidwalker->GetHealth() == expectedVoidwalkerHealth);
		}
	};

	std::shared_ptr<TestCase> GetTest() const override
	{
		return std::make_shared<ImprovedHealthFunnelTestImpt>();
	}
};

class FelIntellectTest : public TestCaseScript
{
public:
	FelIntellectTest() : TestCaseScript("talents warlock fel_intellect") { }

	class FelIntellectTestImpt : public TestCase
	{
	public:
		FelIntellectTestImpt() : TestCase(STATUS_KNOWN_BUG) { }

		float GetPetInt(TestPlayer* caster, uint32 summonPetSpellId)
		{
            TEST_CAST(caster, caster, summonPetSpellId, SPELL_CAST_OK, TRIGGERED_FULL_MASK);
            Guardian* pet = caster->GetGuardianPet();
            TEST_ASSERT(pet != nullptr);
			return pet->GetStat(STAT_INTELLECT);
		}

		void Test() override
		{
			TestPlayer* warlock = SpawnRandomPlayer(CLASS_WARLOCK);

            LearnTalent(warlock, Talents::Warlock::SUMMON_FELGUARD_RNK_1);
            float const intellectTalentFactor = 1.15f;
            float const manaTalentFactor = 1.03f;

            uint32 const expectedMaxMana = warlock->GetMaxPower(POWER_MANA) * manaTalentFactor;

			float const expectedImpInt          = GetPetInt(warlock, ClassSpells::Warlock::SUMMON_IMP_RNK_1) * intellectTalentFactor;
			float const expectedVoidwalkerInt   = GetPetInt(warlock, ClassSpells::Warlock::SUMMON_VOIDWALKER_RNK_1) * intellectTalentFactor;
			float const expectedSuccubusInt     = GetPetInt(warlock, ClassSpells::Warlock::SUMMON_SUCCUBUS_RNK_1) * intellectTalentFactor;
			float const expectedFelhunterInt    = GetPetInt(warlock, ClassSpells::Warlock::SUMMON_FELSTEED_RNK_1) * intellectTalentFactor;
			float const expectedFelguardInt     = GetPetInt(warlock, ClassSpells::Warlock::SUMMON_FELGUARD_RNK_1) * intellectTalentFactor;

            LearnTalent(warlock, Talents::Warlock::FEL_INTELLECT_RNK_3);
            Wait(1000);

            ASSERT_INFO("Warlock has %u max mana, %u expected.", warlock->GetMaxPower(POWER_MANA), expectedMaxMana);
            TEST_ASSERT(Between<uint32>(warlock->GetMaxPower(POWER_MANA), expectedMaxMana - 1, expectedMaxMana + 1));

			float const impNextInt = GetPetInt(warlock, ClassSpells::Warlock::SUMMON_IMP_RNK_1);
            ASSERT_INFO("Imp has %f Intellect, %f expected.", impNextInt, expectedImpInt);
			TEST_ASSERT(Between<float>(impNextInt, expectedImpInt - 1.0f, expectedImpInt + 1.0f));

			float const voidwalkerNextInt = GetPetInt(warlock, ClassSpells::Warlock::SUMMON_VOIDWALKER_RNK_1);
            ASSERT_INFO("Voidwalker has %f Intellect, %f expected.", voidwalkerNextInt, expectedVoidwalkerInt);
			TEST_ASSERT(Between<float>(voidwalkerNextInt, expectedVoidwalkerInt - 1.0f, expectedVoidwalkerInt + 1.0f));

			float const succubusNextInt = GetPetInt(warlock, ClassSpells::Warlock::SUMMON_SUCCUBUS_RNK_1);
            ASSERT_INFO("Succubus has %f Intellect, %f expected.", succubusNextInt, expectedSuccubusInt);
			TEST_ASSERT(Between<float>(succubusNextInt, expectedSuccubusInt - 1.0f, expectedSuccubusInt + 1.0f));

			float const felhunterNextInt = GetPetInt(warlock, ClassSpells::Warlock::SUMMON_FELSTEED_RNK_1);
            ASSERT_INFO("Felhunter has %f Intellect, %f expected.", felhunterNextInt, expectedFelhunterInt);
			TEST_ASSERT(Between<float>(felhunterNextInt, expectedFelhunterInt - 1.0f, expectedFelhunterInt + 1.0f));

			float const felguardNextInt = GetPetInt(warlock, ClassSpells::Warlock::SUMMON_FELGUARD_RNK_1);
            ASSERT_INFO("Felguard has %f Intellect, %f expected.", felguardNextInt, expectedFelguardInt);
			TEST_ASSERT(Between<float>(felguardNextInt, expectedFelguardInt - 1.0f, expectedFelguardInt + 1.0f));
		}
	};

	std::shared_ptr<TestCase> GetTest() const override
	{
		return std::make_shared<FelIntellectTestImpt>();
	}
};

class FelDominationTest : public TestCaseScript
{
public:
	FelDominationTest() : TestCaseScript("talents warlock fel_domination") { }

	class FelDominationTestImpt : public TestCase
	{
	public:
		FelDominationTestImpt() : TestCase(STATUS_PASSING) { }

		void TestSummonManaCost(TestPlayer* warlock, uint32 summonSpellId, uint32 expectedManaCost)
		{
            warlock->SetPower(POWER_MANA, expectedManaCost);
			warlock->GetSpellHistory()->ResetAllCooldowns();

            TEST_CAST(warlock, warlock, ClassSpells::Warlock::FEL_DOMINATION_RNK_1);
            TEST_HAS_COOLDOWN(warlock, ClassSpells::Warlock::FEL_DOMINATION_RNK_1, Minutes(15));
            TEST_AURA_MAX_DURATION(warlock, ClassSpells::Warlock::FEL_DOMINATION_RNK_1, Seconds(15));

            TEST_CAST(warlock, warlock, summonSpellId);
			Wait(Seconds(5));
			Pet* pet = warlock->GetPet();
			TEST_ASSERT(pet != nullptr);

			TEST_ASSERT(warlock->GetPower(POWER_MANA) == 0);
		}

		void Test() override
		{
			TestPlayer* warlock = SpawnRandomPlayer(CLASS_WARLOCK);
            warlock->DisableRegeneration(true);

            LearnTalent(warlock, Talents::Warlock::SUMMON_FELGUARD_RNK_1);
            LearnTalent(warlock, Talents::Warlock::FEL_DOMINATION_RNK_1);
            float const talentFactor = 0.5f;

            uint32 const baseMana = warlock->GetMaxPower(POWER_MANA) - warlock->GetManaBonusFromIntellect();
            uint32 const expectedImpManaCost        = baseMana * 0.64f * talentFactor;
            uint32 const expectedFelguardManaCost   = baseMana * 0.80f * talentFactor;
            uint32 const expectedFelhunterManaCost  = baseMana * 0.80f * talentFactor;
            uint32 const expectedSuccubusManaCost   = baseMana * 0.80f * talentFactor;
            uint32 const expectedVoidwalkerManaCost = baseMana * 0.80f * talentFactor;

            warlock->AddItem(SOUL_SHARD, 4);
			TEST_ASSERT(warlock->HasItemCount(6265, 4, false));

			TestSummonManaCost(warlock, ClassSpells::Warlock::SUMMON_IMP_RNK_1, expectedImpManaCost);
			TestSummonManaCost(warlock, ClassSpells::Warlock::SUMMON_FELGUARD_RNK_1, expectedFelguardManaCost);
			TestSummonManaCost(warlock, ClassSpells::Warlock::SUMMON_FELHUNTER_RNK_1, expectedFelhunterManaCost);
			TestSummonManaCost(warlock, ClassSpells::Warlock::SUMMON_SUCCUBUS_RNK_1, expectedSuccubusManaCost);
			TestSummonManaCost(warlock, ClassSpells::Warlock::SUMMON_VOIDWALKER_RNK_1, expectedVoidwalkerManaCost);
		}
	};

	std::shared_ptr<TestCase> GetTest() const override
	{
		return std::make_shared<FelDominationTestImpt>();
	}
};

class FelStaminaTest : public TestCaseScript
{
public:
	FelStaminaTest() : TestCaseScript("talents warlock fel_stamina") { }

	class FelStaminaTestImpt : public TestCase
	{
	public:
		FelStaminaTestImpt() : TestCase(STATUS_PASSING) { }

		float GetPetSta(TestPlayer* warlock, uint32 summonSpellId)
		{
            TEST_CAST(warlock, warlock, summonSpellId, SPELL_CAST_OK, TRIGGERED_FULL_MASK);
			Pet* pet = warlock->GetPet();
			TEST_ASSERT(pet != nullptr);
			return pet->GetStat(STAT_STAMINA);
		}

		void Test() override
		{
			TestPlayer* warlock = SpawnRandomPlayer(CLASS_WARLOCK);

            LearnTalent(warlock, Talents::Warlock::SUMMON_FELGUARD_RNK_1);
            float const talentStaminaFactor = 1.15f;
            float const talentHealthFactor = 1.03f;

			uint32 const expectedWarlockHealth = warlock->GetHealth() * talentHealthFactor;

            warlock->AddItem(SOUL_SHARD, 8);
			TEST_ASSERT(warlock->HasItemCount(6265, 8, false));

			float const expectedImpStamina          = GetPetSta(warlock, ClassSpells::Warlock::SUMMON_IMP_RNK_1);
			float const expectedVoidwalkerStamina   = GetPetSta(warlock, ClassSpells::Warlock::SUMMON_VOIDWALKER_RNK_1);
			float const expectedSuccubusStamina     = GetPetSta(warlock, ClassSpells::Warlock::SUMMON_SUCCUBUS_RNK_1);
			float const expectedFelhunterStamina    = GetPetSta(warlock, ClassSpells::Warlock::SUMMON_FELSTEED_RNK_1);
			float const expectedFelguardStamina     = GetPetSta(warlock, ClassSpells::Warlock::SUMMON_FELGUARD_RNK_1);

			LearnTalent(warlock, Talents::Warlock::FEL_STAMINA_RNK_3);
			TEST_ASSERT(Between<uint32>(warlock->GetHealth(), expectedWarlockHealth - 1, expectedWarlockHealth + 1));

			float const impNextInt = GetPetSta(warlock, ClassSpells::Warlock::SUMMON_IMP_RNK_1);
			TEST_ASSERT(Between<float>(impNextInt, expectedImpStamina - 1.0f, expectedImpStamina + 1.0f));

			float const voidwalkerNextInt = GetPetSta(warlock, ClassSpells::Warlock::SUMMON_VOIDWALKER_RNK_1);
			TEST_ASSERT(Between<float>(voidwalkerNextInt, expectedVoidwalkerStamina - 1.0f, expectedVoidwalkerStamina + 1.0f));

			float const succubusNextInt = GetPetSta(warlock, ClassSpells::Warlock::SUMMON_SUCCUBUS_RNK_1);
			TEST_ASSERT(Between<float>(succubusNextInt, expectedSuccubusStamina - 1.0f, expectedSuccubusStamina + 1.0f));

			float const felhunterNextInt = GetPetSta(warlock, ClassSpells::Warlock::SUMMON_FELSTEED_RNK_1);
			TEST_ASSERT(Between<float>(felhunterNextInt, expectedFelhunterStamina - 1.0f, expectedFelhunterStamina + 1.0f));

			float const felguardNextInt = GetPetSta(warlock, ClassSpells::Warlock::SUMMON_FELGUARD_RNK_1);
			TEST_ASSERT(Between<float>(felguardNextInt, expectedFelguardStamina - 1.0f, expectedFelguardStamina + 1.0f));
		}
	};

	std::shared_ptr<TestCase> GetTest() const override
	{
		return std::make_shared<FelStaminaTestImpt>();
	}
};

class DemonicAegisTest : public TestCaseScript
{
public:
	DemonicAegisTest() : TestCaseScript("talents warlock demonic_aegis") { }

	class DemonicAegisTestImpt : public TestCase
	{
	public:
		DemonicAegisTestImpt() : TestCase(STATUS_KNOWN_BUG) { } // Talent is OK, Demon Armor spell is not

        void TestDemonArmorBonuses(TestPlayer* caster, Creature* victim, float talentFactor, uint32 demonArmorSpellId, uint32 armorBonus, uint32 shadowResBonus, uint32 healthRestore)
        {
            TEST_ASSERT(caster->IsInCombatWith(victim));

            caster->SetHealth(1);
            uint32 const expectedArmor = caster->GetArmor() + armorBonus * talentFactor;
            uint32 const expectedShadowRes = caster->GetResistance(SPELL_SCHOOL_SHADOW) + shadowResBonus * talentFactor;

            TEST_CAST(caster, caster, demonArmorSpellId);
            TEST_ASSERT(caster->GetArmor() == expectedArmor);
            TEST_ASSERT(caster->GetResistance(SPELL_SCHOOL_SHADOW) == expectedShadowRes);

            uint32 const regenTick = floor(healthRestore * talentFactor / 2.5f);
            uint32 const beforeWaitTime = GameTime::GetGameTimeMS();
            Wait(2000);
            uint32 const afterWaitTime = GameTime::GetGameTimeMS();
            uint32 const elapsedTimeInSeconds = floor((afterWaitTime - beforeWaitTime) / 1000.0f);
            uint32 const expectedTickAmount = floor(elapsedTimeInSeconds / 2.0f);
            uint32 const expectedHealth = 1 + regenTick * expectedTickAmount;
            ASSERT_INFO("%u, Health: %u, expected: %u", demonArmorSpellId, caster->GetHealth(), expectedHealth);
            TEST_ASSERT(caster->GetHealth() == expectedHealth);
        }

        void TestFelArmorBonuses(TestPlayer* caster, TestPlayer* healer, float talentFactor, uint32 felArmorSpellId, uint32 spellDamageBonus)
        {
            // Spell power
            uint32 const expectedSpellDamage = caster->GetInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + SPELL_SCHOOL_SHADOW) + spellDamageBonus * talentFactor;
            TEST_CAST(caster, caster, felArmorSpellId);
            TEST_ASSERT(uint32(caster->GetInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + SPELL_SCHOOL_SHADOW)) == expectedSpellDamage);

            // Healing
            float const felArmorFactor = 1.26f; // boosted by the talent
            uint32 const expectedHTMin = ClassSpellsDamage::Druid::HEALING_TOUCH_RNK_13_MIN * felArmorFactor;
            uint32 const expectedHTMax = ClassSpellsDamage::Druid::HEALING_TOUCH_RNK_13_MAX * felArmorFactor;
            TEST_DIRECT_HEAL(healer, caster, ClassSpells::Druid::HEALING_TOUCH_RNK_13, expectedHTMin, expectedHTMax, false);

            caster->RemoveAurasDueToSpell(felArmorSpellId);
        }

        void Test() override
        {
            TestPlayer* warlock = SpawnPlayer(CLASS_WARLOCK, RACE_HUMAN);
            TestPlayer* druid = SpawnPlayer(CLASS_DRUID, RACE_NIGHTELF);
            Creature* dummy = SpawnCreature();

            warlock->AttackerStateUpdate(dummy, BASE_ATTACK);

            LearnTalent(warlock, Talents::Warlock::DEMONIC_AEGIS_RNK_3);
            float const talentFactor = 1.3f;

            TestDemonArmorBonuses(warlock, dummy, talentFactor, ClassSpells::Warlock::DEMON_ARMOR_RNK_1, 210, 3, 7);
            TestDemonArmorBonuses(warlock, dummy, talentFactor, ClassSpells::Warlock::DEMON_ARMOR_RNK_2, 300, 6, 9);
            TestDemonArmorBonuses(warlock, dummy, talentFactor, ClassSpells::Warlock::DEMON_ARMOR_RNK_3, 390, 9, 11);
            TestDemonArmorBonuses(warlock, dummy, talentFactor, ClassSpells::Warlock::DEMON_ARMOR_RNK_4, 480, 12, 13);
            TestDemonArmorBonuses(warlock, dummy, talentFactor, ClassSpells::Warlock::DEMON_ARMOR_RNK_5, 570, 15, 15);
            TestDemonArmorBonuses(warlock, dummy, talentFactor, ClassSpells::Warlock::DEMON_ARMOR_RNK_6, 660, 18, 18);

            EQUIP_NEW_ITEM(warlock, 34336); // Sunflare - 292 SP

            uint32 const spellPower = warlock->GetInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + SPELL_SCHOOL_SHADOW);
            TEST_ASSERT(spellPower == 292);

            TestFelArmorBonuses(warlock, druid, talentFactor, ClassSpells::Warlock::FEL_ARMOR_RNK_1, 50);
            TestFelArmorBonuses(warlock, druid, talentFactor, ClassSpells::Warlock::FEL_ARMOR_RNK_2, 100);
        }
	};

	std::shared_ptr<TestCase> GetTest() const override
	{
		return std::make_shared<DemonicAegisTestImpt>();
	}
};

class MasterSummonerTest : public TestCaseScript
{
public:
	MasterSummonerTest() : TestCaseScript("talents warlock master_summoner") { }

	class MasterSummonerTestImpt : public TestCase
	{
	public:
		MasterSummonerTestImpt() : TestCase(STATUS_PASSING) { }

        void TestSummonManaCost(TestPlayer* warlock, uint32 summonSpellId, uint32 expectedManaCost, bool useFelDomination = false)
        {
            warlock->SetPower(POWER_MANA, expectedManaCost);
            warlock->GetSpellHistory()->ResetAllCooldowns();

            if (useFelDomination)
                TEST_CAST(warlock, warlock, ClassSpells::Warlock::FEL_DOMINATION_RNK_1);

            TEST_CAST(warlock, warlock, summonSpellId);
            useFelDomination ? Wait(Seconds(1)) : Wait(Seconds(7));
            Pet* pet = warlock->GetPet();
            TEST_ASSERT(pet != nullptr);

            ASSERT_INFO("After %u, Warlock should have 0 mana but has %u", summonSpellId, warlock->GetPower(POWER_MANA));
            TEST_ASSERT(warlock->GetPower(POWER_MANA) == 0);
        }

        void Test() override
        {
            TestPlayer* warlock = SpawnRandomPlayer(CLASS_WARLOCK);
            warlock->DisableRegeneration(true);

            LearnTalent(warlock, Talents::Warlock::SUMMON_FELGUARD_RNK_1);
            LearnTalent(warlock, Talents::Warlock::FEL_DOMINATION_RNK_1);
            LearnTalent(warlock, Talents::Warlock::MASTER_SUMMONER_RNK_2);
            float const masterSummonerManaCostFactor = 1 - 0.4f;
            float const felDominationManaCostFactor = 0.5f;

            uint32 const baseMana = warlock->GetMaxPower(POWER_MANA) - warlock->GetManaBonusFromIntellect();
            uint32 const expectedImpManaCost = baseMana * 0.64f;
            uint32 const expectedFelguardManaCost = baseMana * 0.80f;
            uint32 const expectedFelhunterManaCost = baseMana * 0.80f;
            uint32 const expectedSuccubusManaCost = baseMana * 0.80f;
            uint32 const expectedVoidwalkerManaCost = baseMana * 0.80f;

            warlock->AddItem(SOUL_SHARD, 8);
            TEST_ASSERT(warlock->HasItemCount(6265, 8, false));

            TestSummonManaCost(warlock, ClassSpells::Warlock::SUMMON_IMP_RNK_1, expectedImpManaCost * masterSummonerManaCostFactor);
            TestSummonManaCost(warlock, ClassSpells::Warlock::SUMMON_FELGUARD_RNK_1, expectedFelguardManaCost * masterSummonerManaCostFactor);
            TestSummonManaCost(warlock, ClassSpells::Warlock::SUMMON_FELHUNTER_RNK_1, expectedFelhunterManaCost * masterSummonerManaCostFactor);
            TestSummonManaCost(warlock, ClassSpells::Warlock::SUMMON_SUCCUBUS_RNK_1, expectedSuccubusManaCost * masterSummonerManaCostFactor);
            TestSummonManaCost(warlock, ClassSpells::Warlock::SUMMON_VOIDWALKER_RNK_1, expectedVoidwalkerManaCost * masterSummonerManaCostFactor);

            float talentsFactor = 1 - (felDominationManaCostFactor + 1 - masterSummonerManaCostFactor);
            TestSummonManaCost(warlock, ClassSpells::Warlock::SUMMON_IMP_RNK_1, expectedImpManaCost * talentsFactor, true);
            TestSummonManaCost(warlock, ClassSpells::Warlock::SUMMON_FELGUARD_RNK_1, expectedFelguardManaCost * talentsFactor, true);
            TestSummonManaCost(warlock, ClassSpells::Warlock::SUMMON_FELHUNTER_RNK_1, expectedFelhunterManaCost * talentsFactor, true);
            TestSummonManaCost(warlock, ClassSpells::Warlock::SUMMON_SUCCUBUS_RNK_1, expectedSuccubusManaCost * talentsFactor, true);
            TestSummonManaCost(warlock, ClassSpells::Warlock::SUMMON_VOIDWALKER_RNK_1, expectedVoidwalkerManaCost * talentsFactor, true);
        }
	};

	std::shared_ptr<TestCase> GetTest() const override
	{
		return std::make_shared<MasterSummonerTestImpt>();
	}
};

class DemonicSacrificeTest : public TestCaseScript
{
public:
	DemonicSacrificeTest() : TestCaseScript("talents warlock demonic_sacrifice") { }

	class DemonicSacrificeTestImpt : public TestCase
	{
	public:
		DemonicSacrificeTestImpt() : TestCase(STATUS_KNOWN_BUG) { } // Will break as long as Seed of Corruption is broken

		void SacrificePet(TestPlayer* warlock, uint32 summonSpellId, uint32 aura, uint32 previousAura = 0)
		{
			TEST_CAST(warlock, warlock, summonSpellId, SPELL_CAST_OK, TRIGGERED_FULL_MASK);
            WaitNextUpdate();
			Pet* pet = warlock->GetPet();
			TEST_ASSERT(pet != nullptr);
			if(previousAura != 0)
                TEST_HAS_NOT_AURA(warlock, previousAura);

			TEST_CAST(warlock, warlock, ClassSpells::Warlock::DEMONIC_SACRIFICE_RNK_1);
            TEST_HAS_AURA(warlock, aura);
		}

		void TestImpSacrifice(TestPlayer* warlock, Creature* dummy, float sacrificeFactor)
		{
			// Immolate
            uint32 const immolateSpellLevel = 69; //db values
            float const immolateDmgPerLevel = 4.3f; //db values
            float const immolateDmgPerLevelGain = std::max(warlock->GetLevel() - immolateSpellLevel, uint32(0)) * immolateDmgPerLevel;
			uint32 expectedDirectImmolate = (ClassSpellsDamage::Warlock::IMMOLATE_RNK_9 + immolateDmgPerLevelGain) * sacrificeFactor;
			uint32 expectedDotImmolate = ClassSpellsDamage::Warlock::IMMOLATE_RNK_9_DOT * sacrificeFactor;
			TEST_DIRECT_SPELL_DAMAGE(warlock, dummy, ClassSpells::Warlock::IMMOLATE_RNK_9, expectedDirectImmolate, expectedDirectImmolate, false);
			TEST_DOT_DAMAGE(warlock, dummy, ClassSpells::Warlock::IMMOLATE_RNK_9, expectedDotImmolate, false);

			// Rain of Fire
			uint32 expectedRoFTick = ClassSpellsDamage::Warlock::RAIN_OF_FIRE_RNK_5_TOTAL * sacrificeFactor / 4.0f;
			TEST_CHANNEL_DAMAGE(warlock, dummy, ClassSpells::Warlock::RAIN_OF_FIRE_RNK_5, ClassSpells::Warlock::RAIN_OF_FIRE_RNK_5_PROC, 4, expectedRoFTick);

			// Incinerate
			uint32 expectedIncinerateMin = ClassSpellsDamage::Warlock::INCINERATE_RNK_2_MIN * sacrificeFactor;
			uint32 expectedIncinerateMax = ClassSpellsDamage::Warlock::INCINERATE_RNK_2_MAX * sacrificeFactor;
			TEST_DIRECT_SPELL_DAMAGE(warlock, dummy, ClassSpells::Warlock::INCINERATE_RNK_2, expectedIncinerateMin, expectedIncinerateMax, false);

			// Searing Pain
			uint32 expectedSearingPainMin = ClassSpellsDamage::Warlock::SEARING_PAIN_RNK_8_MIN * sacrificeFactor;
			uint32 expectedSearingPainMax = ClassSpellsDamage::Warlock::SEARING_PAIN_RNK_8_MAX * sacrificeFactor;
			TEST_DIRECT_SPELL_DAMAGE(warlock, dummy, ClassSpells::Warlock::SEARING_PAIN_RNK_8, expectedSearingPainMin, expectedSearingPainMax, false);

			// Soul Fire
			uint32 expectedSoulFireMin = ClassSpellsDamage::Warlock::SOUL_FIRE_RNK_4_MIN * sacrificeFactor;
			uint32 expectedSoulFireMax = ClassSpellsDamage::Warlock::SOUL_FIRE_RNK_4_MAX * sacrificeFactor;
			TEST_DIRECT_SPELL_DAMAGE(warlock, dummy, ClassSpells::Warlock::SOUL_FIRE_RNK_4, expectedSoulFireMin, expectedSoulFireMax, false);

			// Hellfire
            warlock->SetMaxHealth(uint32(10000000));
            warlock->SetFullHealth();

            uint32 const hellfireSpellLevel = 68;
            float const hellfireDmgPerLevel = 0.8f;
            float const hellfireDmgPerLevelGain = std::max(warlock->GetLevel() - hellfireSpellLevel, uint32(0)) * hellfireDmgPerLevel;
			uint32 totalHellfire = 15.0f * floor((ClassSpellsDamage::Warlock::HELLFIRE_RNK_4_TICK + hellfireDmgPerLevelGain) * sacrificeFactor);
            uint32 hellfireTickAmount = totalHellfire / 15.0f;
            TEST_CHANNEL_DAMAGE(warlock, dummy, ClassSpells::Warlock::HELLFIRE_RNK_4, ClassSpells::Warlock::HELLFIRE_RNK_4_TRIGGER, 15, hellfireTickAmount);

            // Self damage
            TEST_DOT_DAMAGE(warlock, warlock, ClassSpells::Warlock::HELLFIRE_RNK_4, totalHellfire, false);
		}

		void TestVoidwalkerSacrifice(TestPlayer* warlock, Creature* dummy)
		{
            warlock->AttackerStateUpdate(dummy, BASE_ATTACK);
			warlock->DisableRegeneration(false);
			warlock->SetHealth(1);
            // Restores 2% every 4 sec.
            uint32 const regenTick = warlock->GetMaxHealth() * 0.02f;

            uint32 const beforeWaitTime = GameTime::GetGameTimeMS();
            Wait(5000);
            uint32 const afterWaitTime = GameTime::GetGameTimeMS();
            uint32 const elapsedTimeInSeconds = floor((afterWaitTime - beforeWaitTime) / 1000.0f);
            uint32 const expectedTickAmount = floor(elapsedTimeInSeconds / 4.0f);
            uint32 const expectedHealth = 1 + regenTick * expectedTickAmount;
            ASSERT_INFO("Warlock should have %u HP but has %u HP.", expectedHealth, warlock->GetHealth());
            TEST_ASSERT(warlock->GetHealth() == expectedHealth);
		}

		void TestSuccubusSacrifice(TestPlayer* warlock, Creature* dummy, float sacrificeFactor)
		{
			// Death Coil
            uint32 const deathCoilSpellLevel = 68;
            float const deathCoilDmgPerLevel = 3.4f;
            float const deathCoilDmgPerLevelGain = std::max(warlock->GetLevel() - deathCoilSpellLevel, uint32(0)) * deathCoilDmgPerLevel;
			uint32 const expectedDeathCoil = (ClassSpellsDamage::Warlock::DEATH_COIL_RNK_4 + deathCoilDmgPerLevelGain) * sacrificeFactor;
			TEST_DIRECT_SPELL_DAMAGE(warlock, dummy, ClassSpells::Warlock::DEATH_COIL_RNK_4, expectedDeathCoil, expectedDeathCoil, false);

			// Shadow Bolt
			uint32 const expectedShadowBoltMin = ClassSpellsDamage::Warlock::SHADOW_BOLT_RNK_11_MIN * sacrificeFactor;
			uint32 const expectedShadowBoltMax = ClassSpellsDamage::Warlock::SHADOW_BOLT_RNK_11_MAX * sacrificeFactor;
			TEST_DIRECT_SPELL_DAMAGE(warlock, dummy, ClassSpells::Warlock::SHADOW_BOLT_RNK_11, expectedShadowBoltMin, expectedShadowBoltMax, false);

            // Shadowburn
            uint32 const expectedShadowburnMin = ClassSpellsDamage::Warlock::SHADOWBURN_RNK_8_MIN * sacrificeFactor;
            uint32 const expectedShadowburnMax = ClassSpellsDamage::Warlock::SHADOWBURN_RNK_8_MAX * sacrificeFactor;
		    TEST_DIRECT_SPELL_DAMAGE(warlock, dummy, ClassSpells::Warlock::SHADOWBURN_RNK_8, expectedShadowburnMin, expectedShadowburnMax, false);

			// Corruption
            float const corruptionTickAmount = 6.0f;
			uint32 const expectedCorruption = ClassSpellsDamage::Warlock::CORRUPTION_RNK_8_TICK * sacrificeFactor * corruptionTickAmount;
			TEST_DOT_DAMAGE(warlock, dummy, ClassSpells::Warlock::CORRUPTION_RNK_8, expectedCorruption, false);

			// Curse of Agony
            uint32 const expectedCoAMaxDamage = ClassSpellsDamage::Warlock::CURSE_OF_AGONY_RNK_7_TOTAL * sacrificeFactor;
            uint32 const expectedCoADamage = (4.0f * expectedCoAMaxDamage / 24.0f) + (4.0f * expectedCoAMaxDamage / 12.0f) + (4.0f * expectedCoAMaxDamage / 8.0f);
			TEST_DOT_DAMAGE(warlock, dummy, ClassSpells::Warlock::CURSE_OF_AGONY_RNK_7, expectedCoADamage, false);

			// Curse of Doom
			uint32 const expectedCoD = ClassSpellsDamage::Warlock::CURSE_OF_DOOM_RNK_2 * sacrificeFactor;
			TEST_DOT_DAMAGE(warlock, dummy, ClassSpells::Warlock::CURSE_OF_DOOM_RNK_2, expectedCoD, false);

            // Seed of Corruption
            Creature* dummy2 = SpawnCreature(); // spawn second dummy to take SoC detonation

            float const socTickAmount = 6.0f;
            uint32 const seedOfCorruptionTick = ClassSpellsDamage::Warlock::SEED_OF_CORRUPTION_RNK_1_TICK * sacrificeFactor;
            uint32 const expectedSoCTotalAmount = socTickAmount * seedOfCorruptionTick;
            TEST_DOT_DAMAGE(warlock, dummy, ClassSpells::Warlock::SEED_OF_CORRUPTION_RNK_1, expectedSoCTotalAmount, true);

            uint32 const expectedDetonationMin = ClassSpellsDamage::Warlock::SEED_OF_CORRUPTION_RNK_1_MIN * sacrificeFactor;
            uint32 const expectedDetonationMax = ClassSpellsDamage::Warlock::SEED_OF_CORRUPTION_RNK_1_MAX * sacrificeFactor;
            //FIXME: next line not working ("GetSpellDamageDoneInfoTo found no data for this victim (Testing Creature)")
            TEST_DIRECT_SPELL_DAMAGE(warlock, dummy2, ClassSpells::Warlock::SEED_OF_CORRUPTION_RNK_1_DETONATION, expectedDetonationMin, expectedDetonationMax, false);
            dummy2->DespawnOrUnsummon();
		}

		void TestFelhunterSacrifice(TestPlayer* warlock, Creature* dummy, float sacrificeFactor)
		{
            warlock->AttackerStateUpdate(dummy, BASE_ATTACK);
            warlock->DisableRegeneration(true);
            warlock->SetPower(POWER_MANA, 0);
            // Restores x% of total mana every 4 sec.
            uint32 const regenTick = warlock->GetMaxPower(POWER_MANA) * sacrificeFactor;

            uint32 const beforeWaitTime = GameTime::GetGameTimeMS();
            Wait(5000);
            uint32 const afterWaitTime = GameTime::GetGameTimeMS();
            uint32 const elapsedTimeInSeconds = floor((afterWaitTime - beforeWaitTime) / 1000.0f);
            uint32 const expectedTickAmount = floor(elapsedTimeInSeconds / 4.0f);
            uint32 const expectedMana = regenTick * expectedTickAmount;
            ASSERT_INFO("Warlock should have %u MP but has %u MP.", expectedMana, warlock->GetPower(POWER_MANA));
            TEST_ASSERT(warlock->GetPower(POWER_MANA) == expectedMana);
		}

		void TestFelguardSacrifice(TestPlayer* warlock, Creature* dummy)
		{
			TestSuccubusSacrifice(warlock, dummy, 1.1f);
			TestFelhunterSacrifice(warlock, dummy, 0.02f);
		}

		void Test() override
		{
			TestPlayer* warlock = SpawnPlayer(CLASS_WARLOCK, RACE_ORC);
            Creature* dummy = SpawnCreature();

            LearnTalent(warlock, Talents::Warlock::SUMMON_FELGUARD_RNK_1);
            LearnTalent(warlock, Talents::Warlock::DEMONIC_SACRIFICE_RNK_1);

			SacrificePet(warlock, ClassSpells::Warlock::SUMMON_IMP_RNK_1, 18789); // Burning Wish
			TestImpSacrifice(warlock, dummy, 1.15f);
			SacrificePet(warlock, ClassSpells::Warlock::SUMMON_VOIDWALKER_RNK_1, 18790, 18789); // Fel Stamina
			TestVoidwalkerSacrifice(warlock, dummy);
			SacrificePet(warlock, ClassSpells::Warlock::SUMMON_SUCCUBUS_RNK_1, 18791, 18790); // Touch of Shadow
			TestSuccubusSacrifice(warlock, dummy, 1.15f);
			SacrificePet(warlock, ClassSpells::Warlock::SUMMON_FELHUNTER_RNK_1, 18792, 18791); // Fel Energy
			TestFelhunterSacrifice(warlock, dummy, 0.03f);
			SacrificePet(warlock, ClassSpells::Warlock::SUMMON_FELGUARD_RNK_1, 35701, 18792); // Touch of Shadow
			TestFelguardSacrifice(warlock, dummy);
		}
	};

	std::shared_ptr<TestCase> GetTest() const override
	{
		return std::make_shared<DemonicSacrificeTestImpt>();
	}
};

class ManaFeedTest : public TestCaseScript
{
public:
	ManaFeedTest() : TestCaseScript("talents warlock mana_feed") { }

	class ManaFeedTestImpt : public TestCase
	{
	public:
		ManaFeedTestImpt() : TestCase(STATUS_KNOWN_BUG) { }

		void AssertManaFeed(TestPlayer* warlock, TestPlayer* enemy, uint32 summonSpell)
		{
            TEST_CAST(warlock, warlock, summonSpell, SPELL_CAST_OK, TRIGGERED_FULL_MASK);
			Pet* pet = warlock->GetPet();
			TEST_ASSERT(pet != nullptr);

			pet->DisableRegeneration(true);
			pet->SetPower(POWER_MANA, 0);
            warlock->SetPower(POWER_MANA, 2000);
            enemy->SetPower(POWER_MANA, 2000);

			// Drain Mana -- bug here
			uint32 expectedManaDrained = ClassSpellsDamage::Warlock::DRAIN_MANA_RNK_6_TICK * 5.0f;
			TEST_CAST(warlock, enemy, ClassSpells::Warlock::DRAIN_MANA_RNK_6);
			Wait(5500);
            ASSERT_INFO("Drain Mana, Pet invoqued with %u, should have %u MP but has %u MP.", summonSpell, expectedManaDrained, pet->GetPower(POWER_MANA));
			TEST_ASSERT(pet->GetPower(POWER_MANA) == expectedManaDrained);

			// Life Tap
            pet->SetPower(POWER_MANA, 0);
            uint32 const spellLevel = 68;
            uint32 const perLevelPoint = 1;
            uint32 const perLevelGain = std::max(warlock->GetLevel() - spellLevel, uint32(0)) * perLevelPoint;
            uint32 const expectedManaGained = ClassSpellsDamage::Warlock::LIFE_TAP_RNK_7 + perLevelGain;
			TEST_CAST(warlock, warlock, ClassSpells::Warlock::LIFE_TAP_RNK_7, SPELL_CAST_OK, TRIGGERED_FULL_MASK);
            ASSERT_INFO("Life Tap Pet invoqued with %u, should have %u MP but has %u MP.", summonSpell, expectedManaGained, pet->GetPower(POWER_MANA));
			TEST_ASSERT(pet->GetPower(POWER_MANA) == expectedManaGained);
		}

		void Test() override
		{
			TestPlayer* warlock = SpawnPlayer(CLASS_WARLOCK, RACE_ORC);

			Position spawnPosition(_location);
			spawnPosition.MoveInFront(_location, 10.0f);
			TestPlayer* enemy = SpawnPlayer(CLASS_WARLOCK, RACE_HUMAN, 70, spawnPosition);

			LearnTalent(warlock, Talents::Warlock::SUMMON_FELGUARD_RNK_1);
			LearnTalent(warlock, Talents::Warlock::MANA_FEED_RNK_3);
			AssertManaFeed(warlock, enemy, ClassSpells::Warlock::SUMMON_IMP_RNK_1);
			AssertManaFeed(warlock, enemy, ClassSpells::Warlock::SUMMON_VOIDWALKER_RNK_1);
			AssertManaFeed(warlock, enemy, ClassSpells::Warlock::SUMMON_SUCCUBUS_RNK_1);
			AssertManaFeed(warlock, enemy, ClassSpells::Warlock::SUMMON_FELHUNTER_RNK_1);
			AssertManaFeed(warlock, enemy, ClassSpells::Warlock::SUMMON_FELGUARD_RNK_1);
		}
	};

	std::shared_ptr<TestCase> GetTest() const override
	{
		return std::make_shared<ManaFeedTestImpt>();
	}
};

class DemonicKnowledgeTest : public TestCaseScript
{
public:
	DemonicKnowledgeTest() : TestCaseScript("talents warlock demonic_knowledge") { }

	class DemonicKnowledgeTestImpt : public TestCase
	{
	public:
		DemonicKnowledgeTestImpt() : TestCase(STATUS_KNOWN_BUG) { }

		void AssertDemonicKnowledge(TestPlayer* warlock, uint32 summonSpellId, float spellPower, float talentFactor)
		{
			TEST_CAST(warlock, warlock, summonSpellId, SPELL_CAST_OK, TRIGGERED_FULL_MASK);
			Pet* pet = warlock->GetPet();
			TEST_ASSERT(pet != nullptr);

			float const expectedSP = spellPower + (pet->GetStat(STAT_STAMINA) + pet->GetStat(STAT_INTELLECT)) * talentFactor;
            ASSERT_INFO("After %u, Warlock should have %f SP but has %f SP.", summonSpellId, expectedSP, warlock->GetFloatValue(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + SPELL_SCHOOL_SHADOW));
			TEST_ASSERT(Between<float>(warlock->GetFloatValue(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + SPELL_SCHOOL_SHADOW), expectedSP - 0.1f, expectedSP + 0.1f));
		}

		void Test() override
		{
			TestPlayer* warlock = SpawnRandomPlayer(CLASS_WARLOCK);

			float const spellPower = warlock->GetFloatValue(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + SPELL_SCHOOL_SHADOW);
            float const talentFactor = 0.12f;

			LearnTalent(warlock, Talents::Warlock::SUMMON_FELGUARD_RNK_1);
			LearnTalent(warlock, Talents::Warlock::DEMONIC_KNOWLEDGE_RNK_3);

			AssertDemonicKnowledge(warlock, ClassSpells::Warlock::SUMMON_IMP_RNK_1, spellPower, talentFactor);
			AssertDemonicKnowledge(warlock, ClassSpells::Warlock::SUMMON_VOIDWALKER_RNK_1, spellPower, talentFactor);
			AssertDemonicKnowledge(warlock, ClassSpells::Warlock::SUMMON_SUCCUBUS_RNK_1, spellPower, talentFactor);
			AssertDemonicKnowledge(warlock, ClassSpells::Warlock::SUMMON_FELHUNTER_RNK_1, spellPower, talentFactor);
			AssertDemonicKnowledge(warlock, ClassSpells::Warlock::SUMMON_FELGUARD_RNK_1, spellPower, talentFactor);
		}
	};

	std::shared_ptr<TestCase> GetTest() const override
	{
		return std::make_shared<DemonicKnowledgeTestImpt>();
	}
};

class ImprovedShadowBoltTest : public TestCaseScript
{
public:
    ImprovedShadowBoltTest() : TestCaseScript("talents warlock improved_shadow_bolt") { }

    class ImprovedShadowBoltTestImpt : public TestCase
    {
    public:
        ImprovedShadowBoltTestImpt() : TestCase(STATUS_KNOWN_BUG) { } // SB crit doesn't proc the ISB buff

        void Test() override
        {
            TestPlayer* warlock = SpawnRandomPlayer(CLASS_WARLOCK);
            Creature* dummy = SpawnCreature();

            LearnTalent(warlock, Talents::Warlock::IMPROVED_SHADOW_BOLT_RNK_5);
            float const talentFactor = 1.2f;
            EnableCriticals(warlock, true);

            uint32 const IMPROVED_SHADOW_BOLT_RNK_5_PROC = 17800;

            // Buff is applied
            FORCE_CAST(warlock, dummy, ClassSpells::Warlock::SHADOW_BOLT_RNK_11);
            TEST_AURA_MAX_DURATION(dummy, IMPROVED_SHADOW_BOLT_RNK_5_PROC, Seconds(12));

            uint32 expectedMinDamage = ClassSpellsDamage::Warlock::SHADOW_BOLT_RNK_11_MIN * talentFactor * 1.5f;
            uint32 expectedMaxDamage = ClassSpellsDamage::Warlock::SHADOW_BOLT_RNK_11_MAX * talentFactor * 1.5f;
            TEST_DIRECT_SPELL_DAMAGE_CALLBACK(warlock, dummy, ClassSpells::Warlock::SHADOW_BOLT_RNK_11, expectedMinDamage, expectedMaxDamage, true, [IMPROVED_SHADOW_BOLT_RNK_5_PROC](Unit* caster, Unit* target) {
                if(!target->HasAura(IMPROVED_SHADOW_BOLT_RNK_5_PROC))
                    target->AddAura(IMPROVED_SHADOW_BOLT_RNK_5_PROC, target);
            });
        }
    };

    std::shared_ptr<TestCase> GetTest() const override
    {
        return std::make_shared<ImprovedShadowBoltTestImpt>();
    }
};

class CataclysmTest : public TestCaseScript
{
public:
    CataclysmTest() : TestCaseScript("talents warlock cataclysm") { }

    class CataclysmTestImpt : public TestCase
    {
    public:
        CataclysmTestImpt() : TestCase(STATUS_PASSING) { }

        void Test() override
        {
            TestPlayer* warlock = SpawnRandomPlayer(CLASS_WARLOCK);

            LearnTalent(warlock, Talents::Warlock::CATACLYSM_RNK_5);
            float const talentFactor = 1 - 0.05f;

            TEST_POWER_COST(warlock, ClassSpells::Warlock::CONFLAGRATE_RNK_6, POWER_MANA, 305 * talentFactor);
            TEST_POWER_COST(warlock, ClassSpells::Warlock::HELLFIRE_RNK_4, POWER_MANA, 1665 * talentFactor);
            TEST_POWER_COST(warlock, ClassSpells::Warlock::IMMOLATE_RNK_9, POWER_MANA, 445 * talentFactor);
            TEST_POWER_COST(warlock, ClassSpells::Warlock::INCINERATE_RNK_2, POWER_MANA, 355 * talentFactor);
            TEST_POWER_COST(warlock, ClassSpells::Warlock::RAIN_OF_FIRE_RNK_5, POWER_MANA, 1480 * talentFactor);
            TEST_POWER_COST(warlock, ClassSpells::Warlock::SEARING_PAIN_RNK_8, POWER_MANA, 205 * talentFactor);
            TEST_POWER_COST(warlock, ClassSpells::Warlock::SHADOW_BOLT_RNK_11, POWER_MANA, 420 * talentFactor);
            TEST_POWER_COST(warlock, ClassSpells::Warlock::SHADOWBURN_RNK_8, POWER_MANA, 515 * talentFactor);
            TEST_POWER_COST(warlock, ClassSpells::Warlock::SHADOWFURY_RNK_3, POWER_MANA, 710 * talentFactor);
            TEST_POWER_COST(warlock, ClassSpells::Warlock::SOUL_FIRE_RNK_4, POWER_MANA, 250 * talentFactor);
        }
    };

    std::shared_ptr<TestCase> GetTest() const override
    {
        return std::make_shared<CataclysmTestImpt>();
    }
};

class BaneTest : public TestCaseScript
{
public:
    BaneTest() : TestCaseScript("talents warlock bane") { }

    class BaneTestImpt : public TestCase
    {
    public:
        BaneTestImpt() : TestCase(STATUS_PASSING) { }

        void TestCorruptionCastTime(TestPlayer* caster, uint32 talentSpellId, uint32 talentPoint, uint32 shadowbBoltImmolateFactor, uint32 soulFireFactor)
        {
            LearnTalent(caster, talentSpellId);
            uint32 const shadowBolt = 3000 - talentPoint * shadowbBoltImmolateFactor;
            TEST_SPELL_CAST_TIME(caster, ClassSpells::Warlock::SHADOW_BOLT_RNK_11, shadowBolt);
            uint32 const immolate = 2000 - talentPoint * shadowbBoltImmolateFactor;
            TEST_SPELL_CAST_TIME(caster, ClassSpells::Warlock::SHADOW_BOLT_RNK_11, shadowBolt);
            uint32 const soulFire = 6000 - talentPoint * soulFireFactor;
            TEST_SPELL_CAST_TIME(caster, ClassSpells::Warlock::SOUL_FIRE_RNK_4, soulFire);
        }

        void Test() override
        {
            TestPlayer* warlock = SpawnRandomPlayer(CLASS_WARLOCK);

            uint32 const shadowbBoltCastTimeReducedPerTalentPoint = 100;
            uint32 const soulFireCastTimeReducedPerTalentPoint = 400;

            TestCorruptionCastTime(warlock, Talents::Warlock::BANE_RNK_1, 1, shadowbBoltCastTimeReducedPerTalentPoint, soulFireCastTimeReducedPerTalentPoint);
            TestCorruptionCastTime(warlock, Talents::Warlock::BANE_RNK_2, 2, shadowbBoltCastTimeReducedPerTalentPoint, soulFireCastTimeReducedPerTalentPoint);
            TestCorruptionCastTime(warlock, Talents::Warlock::BANE_RNK_3, 3, shadowbBoltCastTimeReducedPerTalentPoint, soulFireCastTimeReducedPerTalentPoint);
            TestCorruptionCastTime(warlock, Talents::Warlock::BANE_RNK_4, 4, shadowbBoltCastTimeReducedPerTalentPoint, soulFireCastTimeReducedPerTalentPoint);
            TestCorruptionCastTime(warlock, Talents::Warlock::BANE_RNK_5, 5, shadowbBoltCastTimeReducedPerTalentPoint, soulFireCastTimeReducedPerTalentPoint);
        }
    };

    std::shared_ptr<TestCase> GetTest() const override
    {
        return std::make_shared<BaneTestImpt>();
    }
};

class DevastationTest : public TestCaseScript
{
public:
    DevastationTest() : TestCaseScript("talents warlock devastation") { }

    class DevastationTestImpt : public TestCase
    {
    public:
        DevastationTestImpt() : TestCase(STATUS_WIP) { } // Bugs on Immolate, Incinerate, Searing Pain, Shadow Bolt, Shadowfury

        void Test() override
        {
            TestPlayer* warlock = SpawnPlayer(CLASS_WARLOCK, RACE_ORC);
            Creature* dummy = SpawnCreature();

            LearnTalent(warlock, Talents::Warlock::DEVASTATION_RNK_5);
            float const talentFactor = 5.0f;
            float const expectedSpellCritChance = warlock->GetFloatValue(PLAYER_CRIT_PERCENTAGE) + talentFactor;

            warlock->ForceSpellHitResult(SPELL_MISS_NONE);
            TEST_SPELL_CRIT_CHANCE_CALLBACK(warlock, dummy, ClassSpells::Warlock::CONFLAGRATE_RNK_6, expectedSpellCritChance, [](Unit* caster, Unit* target) {
                caster->CastSpell(target, ClassSpells::Warlock::IMMOLATE_RNK_9, TRIGGERED_FULL_MASK);
            });
            TEST_SPELL_CRIT_CHANCE(warlock, dummy, ClassSpells::Warlock::IMMOLATE_RNK_9, expectedSpellCritChance);
            TEST_SPELL_CRIT_CHANCE(warlock, dummy, ClassSpells::Warlock::INCINERATE_RNK_2, expectedSpellCritChance);
            TEST_SPELL_CRIT_CHANCE(warlock, dummy, ClassSpells::Warlock::SEARING_PAIN_RNK_8, expectedSpellCritChance);
            TEST_SPELL_CRIT_CHANCE(warlock, dummy, ClassSpells::Warlock::SHADOW_BOLT_RNK_11, expectedSpellCritChance);
            TEST_SPELL_CRIT_CHANCE(warlock, dummy, ClassSpells::Warlock::SHADOWBURN_RNK_8, expectedSpellCritChance);
            TEST_SPELL_CRIT_CHANCE(warlock, dummy, ClassSpells::Warlock::SHADOWFURY_RNK_3, expectedSpellCritChance);
            TEST_SPELL_CRIT_CHANCE(warlock, dummy, ClassSpells::Warlock::SOUL_FIRE_RNK_4, expectedSpellCritChance);
            warlock->ResetForceSpellHitResult();
        }
    };

    std::shared_ptr<TestCase> GetTest() const override
    {
        return std::make_shared<DevastationTestImpt>();
    }
};

class ShadowburnTest : public TestCaseScript
{
public:
    ShadowburnTest() : TestCaseScript("talents warlock shadowburn") { }

    class ShadowburnTestImpt : public TestCase
    {
    public:
        ShadowburnTestImpt() : TestCase(STATUS_PASSING) { }

        void Test() override
        {
            TestPlayer* warlock = SpawnPlayer(CLASS_WARLOCK, RACE_HUMAN);
            TestPlayer* enemy = SpawnPlayer(CLASS_WARLOCK, RACE_ORC);
            Creature* dummy = SpawnCreature();

            EQUIP_NEW_ITEM(warlock, 34336); // Sunflare - 292 SP

            uint32 const spellPower = warlock->GetInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + SPELL_SCHOOL_SHADOW);
            TEST_ASSERT(spellPower == 292);

            uint32 const expectedShadowburnManaCost = 515;
            TEST_POWER_COST(warlock, ClassSpells::Warlock::SHADOWBURN_RNK_8, POWER_MANA, expectedShadowburnManaCost);
            
            warlock->AddItem(SOUL_SHARD, 1);
            TEST_CAST(warlock, enemy, ClassSpells::Warlock::SHADOWBURN_RNK_8, SPELL_CAST_OK, TRIGGERED_CAST_DIRECTLY);
            // Consumes a Soul Shard
            TEST_ASSERT(warlock->GetItemCount(SOUL_SHARD, false) == 0);
            TEST_HAS_COOLDOWN(warlock, ClassSpells::Warlock::SHADOWBURN_RNK_8, Seconds(15));
            TEST_AURA_MAX_DURATION(enemy, ClassSpells::Warlock::SHADOWBURN_RNK_8_TRIGGER, Seconds(5));
            Wait(Seconds(2));
            enemy->KillSelf();
            // Gives shard if affected target dies within 5sec
            TEST_ASSERT(warlock->GetItemCount(SOUL_SHARD, false) == 1);

            // Damage
            float const spellCoefficient = ClassSpellsCoeff::Warlock::SHADOWBURN;
            uint32 const expectedShadowburnMin = ClassSpellsDamage::Warlock::SHADOWBURN_RNK_8_MIN + spellPower * spellCoefficient;
            uint32 const expectedShadowburnMax = ClassSpellsDamage::Warlock::SHADOWBURN_RNK_8_MAX + spellPower * spellCoefficient;
            TEST_DIRECT_SPELL_DAMAGE(warlock, dummy, ClassSpells::Warlock::SHADOWBURN_RNK_8, expectedShadowburnMin, expectedShadowburnMax, false);
            TEST_DIRECT_SPELL_DAMAGE(warlock, dummy, ClassSpells::Warlock::SHADOWBURN_RNK_8, expectedShadowburnMin * 1.5f, expectedShadowburnMax * 1.5f, true);
        }
    };

    std::shared_ptr<TestCase> GetTest() const override
    {
        return std::make_shared<ShadowburnTestImpt>();
    }
};

void AddSC_test_talents_warlock()
{
	// Affliction
    new SuppressionTest();
    new ImprovedCorruptionTest();
    new ImprovedCurseOfWeaknessTest();
    new ImprovedDrainSoulTest();
	new ImprovedLifeTapTest();
    new SoulSiphonTest();
    new ImprovedCurseOfAgonyTest();
    // TODO: Fel Concentration
    new AmplifyCurseTest();
    // TODO: Grim Reach
    new NightfallTest();
	new EmpoweredCorruptionTest();
    new ShadowEmbraceTest();
    new SiphonLifeTest();
    new CurseOfExhaustionTest();
	new ShadowMasteryTest();
	new ContagionTest();
    new DarkPactTest();
    new ImprovedHowOfTerrorTest();
    new MaledictionTest();
    new UnstableAfflictionTest();
	// Demonology
	new ImprovedHealthstoneTest();
	new DemonicEmbraceTest();
	new ImprovedHealthFunnelTest();
	new FelIntellectTest();
	new FelDominationTest();
	new FelStaminaTest();
	new DemonicAegisTest();
	new MasterSummonerTest();
	new DemonicSacrificeTest();
	new DemonicKnowledgeTest();
	new ManaFeedTest();
    // Destruction
    new ImprovedShadowBoltTest();
    new CataclysmTest();
    new BaneTest();
    new DevastationTest();
    new ShadowburnTest();
}
