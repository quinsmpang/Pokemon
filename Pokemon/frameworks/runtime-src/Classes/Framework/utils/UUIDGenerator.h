/******************************
Description: UUID maker
Author: M.Wan
Date: 6/22/2014
******************************/

#ifndef __UTILS_UUIDGENERATOR__
#define __UTILS_UUIDGENERATOR__

#ifdef WIN32
#include <ObjBase.h>
#else
#include <uuid/uuid.h>

typedef struct _GUID {
	unsigned long Data1;
	unsigned short Data2;
	unsigned short Data3;
	unsigned char Data4[8];
} GUID, UUID;
#endif

#include "base/CCRef.h"
#include "../base/Macros.h"
#include <string>

namespace framework
{
	class UUIDGenerator : public cocos2d::Ref
	{
        /**
         * UUIDGenerator is a singleton.
         */
		SINGLETON(UUIDGenerator);
	public:
        /**
         * Generate a GUID.
         *
         * @return New GUID.
         */
		const std::string &generateUUID();

	private:
		GUID createGUID();
		const std::string &guidToString(const GUID &guid);
	};
}

#endif