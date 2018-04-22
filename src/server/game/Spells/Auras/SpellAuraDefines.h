
#ifndef TRINITY_SPELLAURADEFINES_H
#define TRINITY_SPELLAURADEFINES_H

#include "Define.h"
#include "ObjectGuid.h"
class Item;
class SpellInfo;
class Unit;
class WorldObject;

#ifdef LICH_KING
#define MAX_AURAS 255                         // Client-side limit
#else
#define MAX_AURAS 56
#endif
#define MAX_POSITIVE_AURAS_PLAYERS      40
#define MAX_POSITIVE_AURAS_CREATURES    16

enum AuraFlags
{
    AFLAG_NONE                   = 0x00,
#ifdef LICH_KING
    AFLAG_EFF_INDEX_0            = 0x01,
    AFLAG_EFF_INDEX_1            = 0x02,
    AFLAG_EFF_INDEX_2            = 0x04,
    AFLAG_CASTER                 = 0x08, 

    AFLAG_POSITIVE               = 0x10,
    AFLAG_DURATION               = 0x20,
    AFLAG_ANY_EFFECT_AMOUNT_SENT = 0x40, // used with AFLAG_EFF_INDEX_0/1/2
    AFLAG_NEGATIVE               = 0x80
#else
    //those are according to mangos-tbc
    AFLAG_HELPFUL                = 0x01,
    AFLAG_HARMFUL                = 0x02,
    AFLAG_PASSIVE_DEPRECATED     = 0x04,     // debuffs can't be queried using this flag. Unused in UI since 1.10.0, new meaning unknown (still the same?)
    AFLAG_HELPFUL_REVEALED       = 0x08,     // Pre-WotLK: unused in UI; Classic: leftover from early Detect Magic-like implementation, required to make any buff/debuff with AFLAG_HELPFUL visible, removing this flag forces client to ignore this aura (including graphics) //corecraft says: "Note: All currently observed data has this toggled on and at least one of the three previous"
    AFLAG_CANCELABLE             = 0x10,     // confirmed on sunstrider: Client does not allow canceling those
    AFLAG_NOT_CANCELABLE         = 0x20,
#endif
};

//m_schoolAbsorb
enum DAMAGE_ABSORB_TYPE
{
    ALL_DAMAGE_ABSORB       = -2,
    ONLY_MAGIC_ABSORB       = -1,
};

enum AuraEffectHandleModes
{
    AURA_EFFECT_HANDLE_DEFAULT         = 0x0,
    AURA_EFFECT_HANDLE_REAL            = 0x01, // handler applies/removes effect from unit
    //Next one are NYI
    AURA_EFFECT_HANDLE_SEND_FOR_CLIENT = 0x02, // handler sends apply/remove packet to unit
    AURA_EFFECT_HANDLE_CHANGE_AMOUNT   = 0x04, // handler updates effect on target after effect amount change
    AURA_EFFECT_HANDLE_REAPPLY         = 0x08, // handler updates effect on target after aura is reapplied on target
    AURA_EFFECT_HANDLE_STAT            = 0x10, // handler updates effect on target when stat removal/apply is needed for calculations by core
    AURA_EFFECT_HANDLE_SKILL           = 0x20, // handler updates effect on target when skill removal/apply is needed for calculations by core

    AURA_EFFECT_HANDLE_SEND_FOR_CLIENT_MASK               = (AURA_EFFECT_HANDLE_SEND_FOR_CLIENT | AURA_EFFECT_HANDLE_REAL), // any case handler need to send packet
    AURA_EFFECT_HANDLE_CHANGE_AMOUNT_MASK                 = (AURA_EFFECT_HANDLE_CHANGE_AMOUNT | AURA_EFFECT_HANDLE_REAL), // any case handler applies effect depending on amount
    AURA_EFFECT_HANDLE_CHANGE_AMOUNT_SEND_FOR_CLIENT_MASK = (AURA_EFFECT_HANDLE_CHANGE_AMOUNT_MASK | AURA_EFFECT_HANDLE_SEND_FOR_CLIENT_MASK),
    AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK               = (AURA_EFFECT_HANDLE_REAPPLY | AURA_EFFECT_HANDLE_REAL)
};


enum AuraRemoveMode
{
    AURA_REMOVE_NONE = 0,
    AURA_REMOVE_BY_DEFAULT = 1,                             // scripted remove, remove by stack with aura with different ids and sc aura remove
    //AURA_REMOVE_BY_STACK,                                   // at replace by semillar aura
    AURA_REMOVE_BY_CANCEL,
    AURA_REMOVE_BY_ENEMY_SPELL,       // dispel and absorb aura destroy
    AURA_REMOVE_BY_EXPIRE,            // aura duration has ended
    AURA_REMOVE_BY_DEATH
};

enum AuraType : uint32
{
    SPELL_AURA_NONE = 0,
    SPELL_AURA_BIND_SIGHT = 1,
    SPELL_AURA_MOD_POSSESS = 2,
    SPELL_AURA_PERIODIC_DAMAGE = 3,
    SPELL_AURA_DUMMY = 4,
    SPELL_AURA_MOD_CONFUSE = 5,
    SPELL_AURA_MOD_CHARM = 6,
    SPELL_AURA_MOD_FEAR = 7,
    SPELL_AURA_PERIODIC_HEAL = 8,
    SPELL_AURA_MOD_ATTACKSPEED = 9,
    SPELL_AURA_MOD_THREAT = 10,
    SPELL_AURA_MOD_TAUNT = 11,
    SPELL_AURA_MOD_STUN = 12,
    SPELL_AURA_MOD_DAMAGE_DONE = 13,
    SPELL_AURA_MOD_DAMAGE_TAKEN = 14,
    SPELL_AURA_DAMAGE_SHIELD = 15,
    SPELL_AURA_MOD_STEALTH = 16,
    SPELL_AURA_MOD_STEALTH_DETECT = 17,
    SPELL_AURA_MOD_INVISIBILITY = 18,
    SPELL_AURA_MOD_INVISIBILITY_DETECTION = 19,
    SPELL_AURA_OBS_MOD_HEALTH = 20,                         //20,21 unofficial
    SPELL_AURA_OBS_MOD_POWER = 21,
    SPELL_AURA_MOD_RESISTANCE = 22,
    SPELL_AURA_PERIODIC_TRIGGER_SPELL = 23,
    SPELL_AURA_PERIODIC_ENERGIZE = 24,
    SPELL_AURA_MOD_PACIFY = 25,
    SPELL_AURA_MOD_ROOT = 26,
    SPELL_AURA_MOD_SILENCE = 27,
    SPELL_AURA_REFLECT_SPELLS = 28,
    SPELL_AURA_MOD_STAT = 29,
    SPELL_AURA_MOD_SKILL = 30,
    SPELL_AURA_MOD_INCREASE_SPEED = 31,
    SPELL_AURA_MOD_INCREASE_MOUNTED_SPEED = 32,
    SPELL_AURA_MOD_DECREASE_SPEED = 33,
    SPELL_AURA_MOD_INCREASE_HEALTH = 34,
    SPELL_AURA_MOD_INCREASE_ENERGY = 35,
    SPELL_AURA_MOD_SHAPESHIFT = 36,
    SPELL_AURA_EFFECT_IMMUNITY = 37,
    SPELL_AURA_STATE_IMMUNITY = 38,
    SPELL_AURA_SCHOOL_IMMUNITY = 39,
    SPELL_AURA_DAMAGE_IMMUNITY = 40,
    SPELL_AURA_DISPEL_IMMUNITY = 41,
    SPELL_AURA_PROC_TRIGGER_SPELL = 42,
    SPELL_AURA_PROC_TRIGGER_DAMAGE = 43,
    SPELL_AURA_TRACK_CREATURES = 44,
    SPELL_AURA_TRACK_RESOURCES = 45,
    SPELL_AURA_MOD_PARRY_SKILL = 46,
    SPELL_AURA_MOD_PARRY_PERCENT = 47,
    SPELL_AURA_MOD_DODGE_SKILL = 48,
    SPELL_AURA_MOD_DODGE_PERCENT = 49,
    SPELL_AURA_MOD_BLOCK_SKILL = 50,
    SPELL_AURA_MOD_BLOCK_PERCENT = 51,
    SPELL_AURA_MOD_WEAPON_CRIT_PERCENT = 52,
    SPELL_AURA_PERIODIC_LEECH = 53,
    SPELL_AURA_MOD_HIT_CHANCE = 54,
    SPELL_AURA_MOD_SPELL_HIT_CHANCE = 55,
    SPELL_AURA_TRANSFORM = 56,
    SPELL_AURA_MOD_SPELL_CRIT_CHANCE = 57,
    SPELL_AURA_MOD_INCREASE_SWIM_SPEED = 58,
    SPELL_AURA_MOD_DAMAGE_DONE_CREATURE = 59,
    SPELL_AURA_MOD_PACIFY_SILENCE = 60,
    SPELL_AURA_MOD_SCALE = 61,
    SPELL_AURA_PERIODIC_HEALTH_FUNNEL = 62,
    SPELL_AURA_PERIODIC_MANA_FUNNEL = 63,
    SPELL_AURA_PERIODIC_MANA_LEECH = 64,
    SPELL_AURA_MOD_CASTING_SPEED = 65,
    SPELL_AURA_FEIGN_DEATH = 66,
    SPELL_AURA_MOD_DISARM = 67,
    SPELL_AURA_MOD_STALKED = 68,
    SPELL_AURA_SCHOOL_ABSORB = 69,
    SPELL_AURA_EXTRA_ATTACKS = 70,
    SPELL_AURA_MOD_SPELL_CRIT_CHANCE_SCHOOL = 71,
    SPELL_AURA_MOD_POWER_COST_SCHOOL_PCT = 72,
    SPELL_AURA_MOD_POWER_COST_SCHOOL = 73,
    SPELL_AURA_REFLECT_SPELLS_SCHOOL = 74,
    SPELL_AURA_MOD_LANGUAGE = 75,
    SPELL_AURA_FAR_SIGHT = 76,
    SPELL_AURA_MECHANIC_IMMUNITY = 77,
    SPELL_AURA_MOUNTED = 78,
    SPELL_AURA_MOD_DAMAGE_PERCENT_DONE = 79,
    SPELL_AURA_MOD_PERCENT_STAT = 80,
    SPELL_AURA_SPLIT_DAMAGE_PCT = 81,
    SPELL_AURA_WATER_BREATHING = 82,
    SPELL_AURA_MOD_BASE_RESISTANCE = 83,
    SPELL_AURA_MOD_REGEN = 84,
    SPELL_AURA_MOD_POWER_REGEN = 85,
    SPELL_AURA_CHANNEL_DEATH_ITEM = 86,
    SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN = 87,
    SPELL_AURA_MOD_HEALTH_REGEN_PERCENT = 88,
    SPELL_AURA_PERIODIC_DAMAGE_PERCENT = 89,
    SPELL_AURA_MOD_RESIST_CHANCE = 90,
    SPELL_AURA_MOD_DETECT_RANGE = 91,
    SPELL_AURA_PREVENTS_FLEEING = 92,
    SPELL_AURA_MOD_UNATTACKABLE = 93,
    SPELL_AURA_INTERRUPT_REGEN = 94,
    SPELL_AURA_GHOST = 95,
    SPELL_AURA_SPELL_MAGNET = 96,
    SPELL_AURA_MANA_SHIELD = 97,
    SPELL_AURA_MOD_SKILL_TALENT = 98,
    SPELL_AURA_MOD_ATTACK_POWER = 99,
    SPELL_AURA_AURAS_VISIBLE = 100,
    SPELL_AURA_MOD_RESISTANCE_PCT = 101,
    SPELL_AURA_MOD_MELEE_ATTACK_POWER_VERSUS = 102,
    SPELL_AURA_MOD_TOTAL_THREAT = 103,
    SPELL_AURA_WATER_WALK = 104,
    SPELL_AURA_FEATHER_FALL = 105,
    SPELL_AURA_HOVER = 106,
    SPELL_AURA_ADD_FLAT_MODIFIER = 107,
    SPELL_AURA_ADD_PCT_MODIFIER = 108,
    SPELL_AURA_ADD_TARGET_TRIGGER = 109,
    SPELL_AURA_MOD_POWER_REGEN_PERCENT = 110,
    SPELL_AURA_ADD_CASTER_HIT_TRIGGER = 111,
    SPELL_AURA_OVERRIDE_CLASS_SCRIPTS = 112,
    SPELL_AURA_MOD_RANGED_DAMAGE_TAKEN = 113,
    SPELL_AURA_MOD_RANGED_DAMAGE_TAKEN_PCT = 114,
    SPELL_AURA_MOD_HEALING = 115,
    SPELL_AURA_MOD_REGEN_DURING_COMBAT = 116,
    SPELL_AURA_MOD_MECHANIC_RESISTANCE = 117,
    SPELL_AURA_MOD_HEALING_PCT = 118,
    SPELL_AURA_SHARE_PET_TRACKING = 119,
    SPELL_AURA_UNTRACKABLE = 120,
    SPELL_AURA_EMPATHY = 121,
    SPELL_AURA_MOD_OFFHAND_DAMAGE_PCT = 122,
    SPELL_AURA_MOD_TARGET_RESISTANCE = 123,
    SPELL_AURA_MOD_RANGED_ATTACK_POWER = 124,
    SPELL_AURA_MOD_MELEE_DAMAGE_TAKEN = 125,
    SPELL_AURA_MOD_MELEE_DAMAGE_TAKEN_PCT = 126,
    SPELL_AURA_RANGED_ATTACK_POWER_ATTACKER_BONUS = 127,
    SPELL_AURA_MOD_POSSESS_PET = 128,
    SPELL_AURA_MOD_SPEED_ALWAYS = 129,
    SPELL_AURA_MOD_MOUNTED_SPEED_ALWAYS = 130,
    SPELL_AURA_MOD_RANGED_ATTACK_POWER_VERSUS = 131,
    SPELL_AURA_MOD_INCREASE_ENERGY_PERCENT = 132,
    SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT = 133,
    SPELL_AURA_MOD_MANA_REGEN_INTERRUPT = 134,
    SPELL_AURA_MOD_HEALING_DONE = 135,
    SPELL_AURA_MOD_HEALING_DONE_PERCENT = 136,
    SPELL_AURA_MOD_TOTAL_STAT_PERCENTAGE = 137,
    SPELL_AURA_MOD_MELEE_HASTE = 138,
    SPELL_AURA_FORCE_REACTION = 139,
    SPELL_AURA_MOD_RANGED_HASTE = 140,
    SPELL_AURA_MOD_RANGED_AMMO_HASTE = 141,
    SPELL_AURA_MOD_BASE_RESISTANCE_PCT = 142,
    SPELL_AURA_MOD_RESISTANCE_EXCLUSIVE = 143,
    SPELL_AURA_SAFE_FALL = 144,
    SPELL_AURA_CHARISMA = 145,
    SPELL_AURA_PERSUADED = 146,
    SPELL_AURA_MECHANIC_IMMUNITY_MASK = 147,
    SPELL_AURA_RETAIN_COMBO_POINTS = 148,
    SPELL_AURA_RESIST_PUSHBACK  = 149,                      //    Resist Pushback
    SPELL_AURA_MOD_SHIELD_BLOCKVALUE_PCT = 150,
    SPELL_AURA_TRACK_STEALTHED  = 151,                      //    Track Stealthed
    SPELL_AURA_MOD_DETECTED_RANGE = 152,                    //    Mod Detected Range
    SPELL_AURA_SPLIT_DAMAGE_FLAT = 153,                     //    Split Damage Flat
    SPELL_AURA_MOD_STEALTH_LEVEL = 154,                     //    Stealth Level Modifier
    SPELL_AURA_MOD_WATER_BREATHING = 155,                   //    Mod Water Breathing
    SPELL_AURA_MOD_REPUTATION_GAIN = 156,                   //    Mod Reputation Gain
    SPELL_AURA_PET_DAMAGE_MULTI = 157,                      //    Mod Pet Damage
    SPELL_AURA_MOD_SHIELD_BLOCKVALUE = 158,
    SPELL_AURA_NO_PVP_CREDIT = 159,
    SPELL_AURA_MOD_AOE_AVOIDANCE = 160,
    SPELL_AURA_MOD_HEALTH_REGEN_IN_COMBAT = 161,
    SPELL_AURA_POWER_BURN = 162,
    SPELL_AURA_MOD_CRIT_DAMAGE_BONUS = 163,
    SPELL_AURA_164 = 164,
    SPELL_AURA_MELEE_ATTACK_POWER_ATTACKER_BONUS = 165,
    SPELL_AURA_MOD_ATTACK_POWER_PCT = 166,
    SPELL_AURA_MOD_RANGED_ATTACK_POWER_PCT = 167,
    SPELL_AURA_MOD_DAMAGE_DONE_VERSUS = 168,
    SPELL_AURA_MOD_CRIT_PERCENT_VERSUS = 169,
    SPELL_AURA_DETECT_AMORE = 170,
    SPELL_AURA_MOD_SPEED_NOT_STACK = 171,
    SPELL_AURA_MOD_MOUNTED_SPEED_NOT_STACK = 172,
    SPELL_AURA_ALLOW_CHAMPION_SPELLS = 173,
    SPELL_AURA_MOD_SPELL_DAMAGE_OF_STAT_PERCENT = 174,      // by default intellect, dependent from SPELL_AURA_MOD_SPELL_HEALING_OF_STAT_PERCENT
    SPELL_AURA_MOD_SPELL_HEALING_OF_STAT_PERCENT = 175,
    SPELL_AURA_SPIRIT_OF_REDEMPTION = 176,
    SPELL_AURA_AOE_CHARM = 177,
    SPELL_AURA_MOD_DEBUFF_RESISTANCE = 178,
    SPELL_AURA_MOD_ATTACKER_SPELL_CRIT_CHANCE = 179,
    SPELL_AURA_MOD_FLAT_SPELL_DAMAGE_VERSUS = 180,
    SPELL_AURA_MOD_FLAT_SPELL_CRIT_DAMAGE_VERSUS = 181,     // unused - possible flat spell crit damage versus
    SPELL_AURA_MOD_RESISTANCE_OF_STAT_PERCENT = 182,
    SPELL_AURA_MOD_CRITICAL_THREAT = 183,
    SPELL_AURA_MOD_ATTACKER_MELEE_HIT_CHANCE = 184,
    SPELL_AURA_MOD_ATTACKER_RANGED_HIT_CHANCE= 185,
    SPELL_AURA_MOD_ATTACKER_SPELL_HIT_CHANCE = 186,
    SPELL_AURA_MOD_ATTACKER_MELEE_CRIT_CHANCE = 187,
    SPELL_AURA_MOD_ATTACKER_RANGED_CRIT_CHANCE = 188,
    SPELL_AURA_MOD_RATING = 189,
    SPELL_AURA_MOD_FACTION_REPUTATION_GAIN = 190,
    SPELL_AURA_USE_NORMAL_MOVEMENT_SPEED = 191,
    SPELL_AURA_MOD_MELEE_RANGED_HASTE = 192,
    SPELL_AURA_MELEE_SLOW = 193,
    SPELL_AURA_MOD_DEPRICATED_1  = 194,                     // not used now, old SPELL_AURA_MOD_SPELL_DAMAGE_OF_INTELLECT
    SPELL_AURA_MOD_DEPRICATED_2  = 195,                     // not used now, old SPELL_AURA_MOD_SPELL_HEALING_OF_INTELLECT
    SPELL_AURA_MOD_COOLDOWN = 196,                          // only 24818 Noxious Breath
    SPELL_AURA_MOD_ATTACKER_SPELL_AND_WEAPON_CRIT_CHANCE = 197,
    SPELL_AURA_MOD_ALL_WEAPON_SKILLS = 198,
    SPELL_AURA_MOD_INCREASES_SPELL_PCT_TO_HIT = 199,
    SPELL_AURA_MOD_XP_PCT = 200,
    SPELL_AURA_FLY = 201,
    SPELL_AURA_IGNORE_COMBAT_RESULT = 202,
    SPELL_AURA_MOD_ATTACKER_MELEE_CRIT_DAMAGE = 203,
    SPELL_AURA_MOD_ATTACKER_RANGED_CRIT_DAMAGE = 204,
    SPELL_AURA_205 = 205,                                   // unused TC SPELL_AURA_MOD_SCHOOL_CRIT_DMG_TAKEN
    SPELL_AURA_MOD_INCREASE_VEHICLE_FLIGHT_SPEED = 206,                     // ? used in strange spells
    SPELL_AURA_MOD_INCREASE_MOUNTED_FLIGHT_SPEED = 207,
    SPELL_AURA_MOD_INCREASE_FLIGHT_SPEED = 208,
    SPELL_AURA_MOD_MOUNTED_FLIGHT_SPEED_ALWAYS = 209,
    SPELL_AURA_210 = 210,                                   // unused TC SPELL_AURA_MOD_VEHICLE_SPEED_ALWAYS
    SPELL_AURA_MOD_FLIGHT_SPEED_NOT_STACK = 211,
    SPELL_AURA_MOD_RANGED_ATTACK_POWER_OF_STAT_PERCENT = 212,
    SPELL_AURA_MOD_RAGE_FROM_DAMAGE_DEALT = 213,
    SPELL_AURA_214 = 214,
    SPELL_AURA_ARENA_PREPARATION = 215,
    SPELL_AURA_HASTE_SPELLS = 216,
    SPELL_AURA_217 = 217,
    SPELL_AURA_HASTE_RANGED = 218,
    SPELL_AURA_MOD_MANA_REGEN_FROM_STAT = 219,
    SPELL_AURA_MOD_RATING_FROM_STAT = 220, //none on BC
    SPELL_AURA_MOD_DETAUNT = 221,
    SPELL_AURA_222 = 222,
    SPELL_AURA_223 = 223,
    SPELL_AURA_224 = 224,
    SPELL_AURA_PRAYER_OF_MENDING = 225,
    SPELL_AURA_PERIODIC_DUMMY = 226,
    SPELL_AURA_PERIODIC_TRIGGER_SPELL_WITH_VALUE = 227,
    SPELL_AURA_DETECT_STEALTH = 228,
    SPELL_AURA_MOD_AOE_DAMAGE_AVOIDANCE = 229,
    SPELL_AURA_230 = 230,
    SPELL_AURA_231 = 231,
    SPELL_AURA_MECHANIC_DURATION_MOD = 232,
    SPELL_AURA_233 = 233, //TC SPELL_AURA_CHANGE_MODEL_FOR_ALL_HUMANOIDS // client-side only
    SPELL_AURA_MECHANIC_DURATION_MOD_NOT_STACK = 234,
    SPELL_AURA_MOD_DISPEL_RESIST = 235,
    SPELL_AURA_236 = 236,
    SPELL_AURA_MOD_SPELL_DAMAGE_OF_ATTACK_POWER = 237,
    SPELL_AURA_MOD_SPELL_HEALING_OF_ATTACK_POWER = 238,
    SPELL_AURA_MOD_SCALE_2 = 239,
    SPELL_AURA_MOD_EXPERTISE = 240,
    SPELL_AURA_FORCE_MOVE_FORWARD = 241,
    SPELL_AURA_MOD_SPELL_DAMAGE_FROM_HEALING = 242,
    SPELL_AURA_243 = 243, // TC SPELL_AURA_MOD_FACTION
    SPELL_AURA_COMPREHEND_LANGUAGE = 244,
    SPELL_AURA_MOD_DURATION_OF_MAGIC_EFFECTS = 245,
    SPELL_AURA_246 = 246, // TC SPELL_AURA_MOD_AURA_DURATION_BY_DISPEL_NOT_STACK
    SPELL_AURA_CLONE_CASTER = 247,
    SPELL_AURA_MOD_COMBAT_RESULT_CHANCE = 248,
    SPELL_AURA_249 = 249, // TC SPELL_AURA_CONVERT_RUNE
    SPELL_AURA_MOD_INCREASE_HEALTH_2 = 250,
    SPELL_AURA_MOD_ENEMY_DODGE = 251,
    SPELL_AURA_252 = 252,
    SPELL_AURA_253 = 253,
    SPELL_AURA_254 = 254,
    SPELL_AURA_255 = 255, //no spell have this on BC. TC : SPELL_AURA_MOD_MECHANIC_DAMAGE_TAKEN_PERCENT
    SPELL_AURA_256 = 256,
    SPELL_AURA_257 = 257,
    SPELL_AURA_258 = 258,
    SPELL_AURA_APPLY_IMMUNITY_ID = 259, //Sunstrider custom (replace this with dummy spells ?)
    SPELL_AURA_APPLY_EXTRA_FLAG = 260, //Sunstrider custom (replace this with dummy spells ?)
    SPELL_AURA_261 = 261,
    TOTAL_AURAS=262
};

enum AuraObjectType
{
    UNIT_AURA_TYPE,
    DYNOBJ_AURA_TYPE
};

enum AreaAuraType : unsigned int
{
    AREA_AURA_PARTY,
    AREA_AURA_FRIEND,
    AREA_AURA_ENEMY,
    AREA_AURA_PET,
    AREA_AURA_OWNER
};

struct TC_GAME_API AuraCreateInfo
{
    friend class Aura;
    friend class UnitAura;
    friend class DynObjAura;

    AuraCreateInfo(SpellInfo const* spellInfo, uint8 auraEffMask, WorldObject* owner);

    AuraCreateInfo& SetCasterGUID(ObjectGuid const& guid) { CasterGUID = guid; return *this; }
    AuraCreateInfo& SetCaster(Unit* caster) { Caster = caster; return *this; }
    AuraCreateInfo& SetBaseAmount(int32 const* bp) { BaseAmount = bp; return *this; }
    AuraCreateInfo& SetCastItem(Item* item) { CastItem = item; return *this; }
    AuraCreateInfo& SetPeriodicReset(bool reset) { ResetPeriodicTimer = reset; return *this; }
    AuraCreateInfo& SetOwnerEffectMask(uint8 effMask) { _targetEffectMask = effMask; return *this; }
    AuraCreateInfo& SetFake(bool fake) { Fake = fake; return *this; }

    SpellInfo const* GetSpellInfo() const { return _spellInfo; }
    uint8 GetAuraEffectMask() const { return _auraEffectMask; }

    ObjectGuid CasterGUID;
    Unit* Caster = nullptr;
    int32 const* BaseAmount = nullptr;
    Item* CastItem = nullptr;
    bool* IsRefresh = nullptr;
    bool ResetPeriodicTimer = true;
    bool Fake = false; // fake = true won't add aura to owner

    private:
        SpellInfo const* _spellInfo = nullptr;
        uint8 _auraEffectMask = 0;
        WorldObject* _owner = nullptr;

        uint8 _targetEffectMask = 0;
};


#endif

