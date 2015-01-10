/******************************
 Description: Transfer rule in http.
 Author: M.Wan
 Date: 01/10/2015
 ******************************/

#ifndef __HTTP_HTTPTRANSFERSTRATEGY__
#define __HTTP_HTTPTRANSFERSTRATEGY__

#include "../containers/Map.h"
#include <string>

namespace framework {
    class HttpTransferStrategy
    {
    public:
        /**
         * HttpTransferStrategy destructor.
         */
		virtual ~HttpTransferStrategy() {}
        
        /**
         * How to get url parameters to transfer based on your rule?
         *
         * @return The mapping of your transfer parameters in http.
         */
        virtual Map *transferParameters() = 0;
    };
}

#endif
