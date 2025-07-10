/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

/* Code Protection Type, uint8_t */
enum CodeType_t {
	NULL = 0,
	SHA_1 = 1,
	SHA_256 = 2,
	MAX_CODETYPE = 255
};

/* State Flag Type, uint8_t */
enum LockStateType_t {
	STATE_LOCKED = 0,
	STATE_UNLOCKED = 1,
	MAX_LOCKSTATE = 255
};

/* Autolock Flag Type, uint8_t */
enum AutoLockStateType_t {
	INACTIVE = 0,
	ACTIVE = 1
};


/* IMSI (opaque IMSI<1..2^16-1>*/
struct IMSI_t {
	uint16_t  IMSILength;
	uint8_t   IMSIData[IMSILength];
};

/* Control Key Type (<1..2^8-1>)*/
struct CodeHash_t {
	uint8_t CodeHashLength;
	uint8_t CodeHash[CodeHashLength];
};

struct CK_t {
	CodeType_t CodeType;
	uint32_t IterationCount;
	uint8_t Salt[20];
	CodeHash_t CodeHash;
};

/* Configuration */
struct Configuration_t {
	local uint16_t TempLength;
	uint8_t MNCLength; // Needed when autolock is performed
	uint8_t MaxAttempts;
	uint8_t WaitTime; // Wait time in seconds
	CK_t  BombCode;
	CK_t  FactoryFreshCode;
	uint16_t OperatorNameLen;
	char   OperatorName[OperatorNameLen];
	uint16_t ServerMarkerLen;
	char   ServerMarker[ServerMarkerLen];
	uint16_t TestSIMsLength;
/*
 *	TempLength = 0;
 *	while (TempLength < TestSIMsLength) {
 *		IMSI_t IMSI;
 *		TempLength += IMSI.IMSILength + 2;
 *	}
 *	if (TestSIMsLength != TempLength)
 *		Printf("Invalid TestSIMsLength.\n");
 */
};

/* Control Key State */
struct CK_state_t {
	uint8_t failed_attempts_counter;
	uint8_t CodeLength;
	uint8_t CodeData[CodeLength];
};

struct ControlKeyState_t {
	CK_state_t NCK_state;
	CK_state_t NSCK_state;
	CK_state_t SPCK_state;
	CK_state_t CCK_state;
};

/* Codes */
struct Codes_t {
	CK_t NCK;
	CK_t NSCK;
	CK_t SPCK;
	CK_t CCK;
};

/* GID data (opaque GID<1..2^8-1>)*/
struct GID_t {
	uint8_t GIDLength;
	uint8_t GIDData[GIDLength];
};

/* Lock Category */
struct Lock_Category_t {
	local uint16_t TempLength;
	uint16_t LockCategoryLength;
/*
 *	TempLength = 0;
 *	while (TempLength < LockCategoryLength) {
 *		IMSI_t IMSI;
 *		GID_t GID1;
 *		GID_t GID2;
 *		TempLength += IMSI.IMSILength + 2;
 *		TempLength += GID1.GIDLength + 1;
 *		TempLength += GID2.GIDLength + 1;
 *	}
 *	if (LockCategoryLength != TempLength)
 *		Printf("Invalid LockCategoryLength.\n");
 */
};

/* Customization */
struct Customization_t {
	AutoLockStateType_t NetworkAutoLockState;
	AutoLockStateType_t NetworkSubsetAutoLockState;
	AutoLockStateType_t ServiceProviderAutoLockState;
	AutoLockStateType_t CorporateAutoLockState;
	Lock_Category_t Network;
	Lock_Category_t NetworkSubset;
	Lock_Category_t ServiceProvider;
	Lock_Category_t Corporate;
};

/* Autolocked */
struct AutoLocked_t {
	Lock_Category_t Network;
	Lock_Category_t NetworkSubset;
	Lock_Category_t ServiceProvider;
	Lock_Category_t Corporate;
};

/* opaque FactoryFresh (<1..2^8-1>)*/
struct FactoryFresh_t {
	uint8_t CodeHashLength;
	uint8_t CodeHash[CodeHashLength];
};

/* The complete SIM lock data */
struct SIMLockData {
	uint8_t		Bomb[20];	/* Dynamic */
	uint8_t		Version;	/* Static */
	Configuration_t	Configuration;	/* Static */
	Customization_t	Customization;	/* Static */
	Codes_t		Codes;		/* Static */
	ControlKeyState_t ControlKeyState; /* Dynamic */
	AutoLocked_t	AutoLocked;	/* Dynamic */
	FactoryFresh_t	FactoryFresh;	/* Dynamic */
	KIRIN_t		KIRIN;		/* Dynamic */
};
