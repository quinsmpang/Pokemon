/******************************
Description: UUID maker
Author: M.Wan
Date: 6/22/2014
******************************/

#ifndef __UTILS_UUIDGENERATOR__
#define __UTILS_UUIDGENERATOR__

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
		std::string generateUUID();
	};
}

#endif