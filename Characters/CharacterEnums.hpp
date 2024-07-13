#pragma once

// Generic Character Stats
enum CHARACTER_STATS
{
	BASE_HP = 0, // Not used in curStats
	EXTRA_HP, // Not used in curStats
	HP,
	BASE_ATK, // Not used in curStats
	EXTRA_ATK, // Not used in curStats
	ATK,
	BASE_DEF, // Not used in curStats
	EXTRA_DEF, // Not used in curStats
	DEF,
	BASE_SPD, // Not used in curStats
	EXTRA_SPD, // Not used in curStats
	SPD,
	CRIT_RATE,
	CRIT_DMG,
	NUM_STATS
};

// Character target type
enum TARGET_TYPE
{
	SINGLE_ENEMY = 0,
	BLAST_ENEMY,
	AOE_ENEMY,
	BOUNCE_ENEMY,
	SINGLE_TEAMMATE,
	BLAST_TEAMMATE,
	AOE_TEAMMATE,
	NUM_TARGET_TYPE
};


// Character actions
enum CHARACTER_ACTION
{
	BASIC_ATTACK = 0,
	SKILL,
	ULTIMATE,
	NUM_ACTION_TYPE
};

// Element Types
// The order of element types matches the order of curse colors!
enum ELEMENT_TYPE
{
	QUANTUM = 0,
	WIND,
	ICE,
	FIRE,
	LIGHTNING,
	IMAGINARY,
	PHYSICAL,
	NUM_ELEMENT_TYPE
};

#define ENERGY_RECHARGE_SKILL 30.0f
#define ENERGY_RECHARGE_BASIC_ATK 20.0f
#define ENERGY_RECHARGE_ULT 5.0f
#define ENERGY_RECHARGE_KILL 10.0f