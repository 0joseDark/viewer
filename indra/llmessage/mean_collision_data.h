/** 
 * @file mean_collision_data.h
 * @brief data type to log interactions between stuff and agents that
 * might be community standards violations
 *
 * Copyright (c) 2000-$CurrentYear$, Linden Research, Inc.
 * $License$
 */

#ifndef LL_MEAN_COLLISIONS_DATA_H
#define LL_MEAN_COLLISIONS_DATA_H

#include "lldbstrings.h"
#include "lluuid.h"

const F32 MEAN_COLLISION_TIMEOUT = 5.f;
const S32 MAX_MEAN_COLLISIONS = 5;

typedef enum e_mean_collision_types
{
	MEAN_INVALID,
	MEAN_BUMP,
	MEAN_LLPUSHOBJECT,
	MEAN_SELECTED_OBJECT_COLLIDE,
	MEAN_SCRIPTED_OBJECT_COLLIDE,
	MEAN_PHYSICAL_OBJECT_COLLIDE,
	MEAN_EOF
} EMeanCollisionType;

class LLMeanCollisionData
{
public:
	LLMeanCollisionData(const LLUUID &victim, const LLUUID &perp, time_t time, EMeanCollisionType type, F32 mag)
		: mVictim(victim), mPerp(perp), mTime(time), mType(type), mMag(mag)
	{ mFirstName[0] = 0; mLastName[0] =  0; }
	
	LLMeanCollisionData(LLMeanCollisionData *mcd)
		: mVictim(mcd->mVictim), mPerp(mcd->mPerp), mTime(mcd->mTime), mType(mcd->mType), mMag(mcd->mMag)
	{ 
		strncpy(mFirstName, mcd->mFirstName, sizeof(mFirstName) -1); /* Flawfinder: Ignore */
		mFirstName[sizeof(mFirstName) -1] = '\0'; 
		strncpy(mLastName, mcd->mLastName, sizeof(mLastName) -1); /* Flawfinder: Ignore */
		mLastName[sizeof(mLastName) -1] = '\0';
	}		
	
	friend std::ostream&	 operator<<(std::ostream& s, const LLMeanCollisionData &a)
	{
		switch(a.mType)
		{
		case MEAN_BUMP:
			s << "Mean Collision: " << a.mPerp << " bumped " << a.mVictim << " with a velocity of " << a.mMag << " at " << ctime(&a.mTime);
			break;
		case MEAN_LLPUSHOBJECT:
			s << "Mean Collision: " << a.mPerp << " llPushObject-ed " << a.mVictim << " with a total force of " << a.mMag  << " at "<<  ctime(&a.mTime);
			break;
		case MEAN_SELECTED_OBJECT_COLLIDE:
			s << "Mean Collision: " << a.mPerp << " dragged an object into " << a.mVictim << " with a velocity of " << a.mMag  << " at "<<  ctime(&a.mTime);
			break;
		case MEAN_SCRIPTED_OBJECT_COLLIDE:
			s << "Mean Collision: " << a.mPerp << " smacked " << a.mVictim << " with a scripted object with velocity of " << a.mMag  << " at "<<  ctime(&a.mTime);
			break;
		case MEAN_PHYSICAL_OBJECT_COLLIDE:
			s << "Mean Collision: " << a.mPerp << " smacked " << a.mVictim << " with a physical object with velocity of " << a.mMag  << " at "<<  ctime(&a.mTime);
			break;
		default:
			break;
		}
		return s;
	}

	LLUUID mVictim;
	LLUUID mPerp;
	time_t mTime;
	EMeanCollisionType mType;
	F32	   mMag;
	char   mFirstName[DB_FIRST_NAME_BUF_SIZE];		/* Flawfinder: Ignore */
	char   mLastName[DB_LAST_NAME_BUF_SIZE];		/* Flawfinder: Ignore */
};


#endif
