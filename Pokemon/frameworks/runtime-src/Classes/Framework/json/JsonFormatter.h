/******************************
 Description: JSON formatter.
 Author: M.Wan
 Date: 01/10/2015
 ******************************/

#ifndef __JSON_JSONFORMATTER__
#define __JSON_JSONFORMATTER__

#include "JsonStructure.h"
#include "../base/Macros.h"
#include "libjson/libjson.h"
#include <string>

namespace framework {
    class JsonFormatter
    {
        /**
         * JsonFormatter is a singleton.
         */
        SINGLETON(JsonFormatter);
    public:
        /**
         * Format the json object(JsonObject/JsonArray) into string.
         *
         * @param json Json object.
         *
         * @return Return Formatted string.
         */
        std::string format(cocos2d::Ref *json, bool isPretty = false);
        
    private:
        JSONNODE *formatToJsonNode(cocos2d::Ref *json);
        JSONNODE *formatJsonObjectToJsonNode(JsonObject *json);
        JSONNODE *formatJsonArrayToJsonNode(JsonArray *json);
    };
}

#endif /* defined(__JSON_JSONFORMATTER__) */
