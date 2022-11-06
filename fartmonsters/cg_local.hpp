#pragma once

#ifndef cglocal
#define cglocal

namespace cg
{
	struct __declspec(align(2)) usercmd_s
	{
		int serverTime;
		int buttons;
		int angles[3];
		char weapon;
		char offHandIndex;
		char selectedLocation[2];
		char forwardmove;
		char rightmove;
	};
	enum pmflags_t
	{
		PMF_NONE = 0x0,
		PMF_PRONE = 0x1,
		PMF_DUCKED = 0x2,
		PMF_MANTLE = 0x4,
		PMF_SIGHT_AIMING = 0x10,
		PMF_LADDER = 0x20,
		PMF_LADDER_DOWN = 0x30,
		PMF_WALKING = 0x40,
		PMF_TIME_LAND = 0x80,
		PMF_TIME_KNOCKBACK = 0x100,
		PMF_PRONEMOVE_OVERRIDDEN = 0x200,
		PMF_RESPAWNED = 0x400,
		PMF_FROZEN = 0x800,
		PMF_PRONE_BLOCKED = 0x1000,
		PMF_LADDER_FALL = 0x2000,
		PMF_SPRINTING = 0x8000,
		PMF_SHELLSHOCKED = 0x10000,
		PMF_MELEE_CHARGE = 0x20000,
		PMF_NO_SPRINT = 0x40000,
		PMF_JUMPING = 0x80000,
		PMF_VEHICLE_ATTACHED = 0x100000,
	};
	enum pmtype_t
	{
		PM_NORMAL = 0x0,
		PM_NORMAL_LINKED = 0x1,
		PM_NOCLIP = 0x2,
		PM_UFO = 0x3,
		PM_SPECTATOR = 0x4,
		PM_INTERMISSION = 0x5,
		PM_DEAD = 0x6,
		PM_DEAD_LINKED = 0x7,
	};
	enum TraceHitType
	{
		TRACE_HITTYPE_NONE = 0x0,
		TRACE_HITTYPE_ENTITY = 0x1,
		TRACE_HITTYPE_DYNENT_MODEL = 0x2,
		TRACE_HITTYPE_DYNENT_BRUSH = 0x3,
	};
	enum surfTraceType_t
	{
		SURF_NODAMAGE = 0x1,
		SURF_SLICK = 0x2,
		SURF_SKY = 0x4,
		SURF_LADDER = 0x8,
		SURF_NOIMPACT = 0x10,
		SURF_NOMARKS = 0x20,
		SURF_NODRAW = 0x80,
		SURF_NOPENETRATE = 0x100,
		SURF_NOLIGHTMAP = 0x400,
		SURF_NOSTEPS = 0x2000,
		SURF_NONSOLID = 0x4000,
		SURF_NODLIGHT = 0x20000,
		SURF_NOCASTSHADOW = 0x40000,
		SURF_MANTLEON = 0x2000000,
		SURF_MANTLEOVER = 0x4000000,
		SURF_PORTAL = 0x80000000,
		SURF_BARK = 0x100000,
		SURF_BRICK = 0x200000,
		SURF_CARPET = 0x300000,
		SURF_CLOTH = 0x400000,
		SURF_CONCRETE = 0x500000,
		SURF_DIRT = 0x600000,
		SURF_FLESH = 0x700000,
		SURF_FOLIAGE = 0x800000,
		SURF_GLASS = 0x900000,
		SURF_GRASS = 0xA00000,
		SURF_GRAVEL = 0xB00000,
		SURF_ICE = 0xC00000,
		SURF_METAL = 0xD00000,
		SURF_MUD = 0xE00000,
		SURF_PAPER = 0xF00000,
		SURF_PLASTER = 0x1000000,
		SURF_ROCK = 0x1100000,
		SURF_SAND = 0x1200000,
		SURF_SNOW = 0x1300000,
		SURF_WATER = 0x1400000,
		SURF_WOOD = 0x1500000,
		SURF_ASPHALT = 0x1600000,
		SURF_CERAMIC = 0x1700000,
		SURF_PLASTIC = 0x1800000,
		SURF_RUBBER = 0x1900000,
		SURF_CUSHION = 0x1A00000,
		SURF_FRUIT = 0x1B00000,
		SURF_PAINTEDMETAL = 0x1C00000,
	};

	struct __declspec(align(2)) trace_t
	{
		float fraction;
		float normal[3];
		surfTraceType_t surfaceFlags;
		int contents;
		const char* material;
		TraceHitType hitType;
		unsigned __int16 hitId;
		unsigned __int16 modelIndex;
		unsigned __int16 partName;
		unsigned __int16 partGroup;
		bool allsolid;
		bool startsolid;
		bool walkable;
	};
	struct pml_t
	{
		float forward[3];
		float right[3];
		float up[3];
		float frametime;
		int msec;
		int walking;
		int groundPlane;
		int almostGroundPlane;
		trace_t groundTrace;
		float previous_origin[3];
		float previous_velocity[3];
	};
	struct playerState_s
	{
		int commandTime;
		pmtype_t pm_type;
		int weapFlags;
		pmflags_t pm_flags;
		int pm_time;
		float origin[3];
		float velocity[3];
		float oldVelocity[2];
		int weaponTime;
		int weaponDelay;
		int grenadeTimeLeft;
		int weaponRestrictKickTime;
		int foliageSoundTime;
		int gravity;
		float leanf;
		int speed;
		float delta_angles[3];
		int groundEntityNum;
		float vLadderVec[3];
		int jumpTime;
		float jumpOriginZ;
		int legsTimer;
		int legsAnim;
		int torsoTimer;
		int torsoAnim;
		int legsAnimDuration;
		int torsoAnimDuration;
		int damageTimer;
		int movementDir;
		int eFlags;
		int eventSequence;
		int events[4];
		unsigned int eventParms[4];
		int oldEventSequence;
		int offhandSecondary;
		unsigned int pad001;
		float fWeaponPosFrac;
		int offHandIndex;
		unsigned int weapon;
		int weaponstate;
		unsigned int weaponShotCount;
		int adsDelayTime;
		int spreadOverride;
		float viewangles[3];
	};
	struct __declspec(align(4)) pmove_t
	{
		playerState_s* ps;
		usercmd_s cmd;
		usercmd_s oldcmd;
		int tracemask;
		int numtouch;
		int touchents[32];
		float mins[3];
		float maxs[3];
		float xyspeed;
		int proneChange;
		char handler;
		float maxSprintTimeMultiplier;
		bool mantleStarted;
		float mantleEndPos[3];
		int mantleDuration;
		int viewChangeTime;
		float viewChange;
	};


}

#endif