/******************************
Description: Win32 event args base class
Author: M.Wan
Date: 10/28/2014
******************************/

#ifndef __WIN32_WIN32EVENTARGS__
#define __WIN32_WIN32EVENTARGS__

#include "cocos2d.h"

namespace framework
{
	class GameLayer;

	class Win32EventArgs : public cocos2d::Ref
	{
		friend class Win32Notifier;
	public:
        /**
         * Win32EventArgs constructor.
         *
         * @param params Event related parameters.
         */
		Win32EventArgs(void *params);
        /**
         * Win32EventArgs destructor.
         */
		virtual ~Win32EventArgs();

        /**
         * Get parameters.
         *
         * @return Parameters of the event.
         */
		inline void *getParams() const
		{
			return _params;
		}

	protected:
		void *_params;
	};
}

#endif