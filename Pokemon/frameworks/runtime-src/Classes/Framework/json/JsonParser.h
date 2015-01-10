/******************************
 Description: JSON parser.
 Author: M.Wan
 Date: 01/10/2015
 ******************************/

#ifndef __JSON_JSONPARSER__
#define __JSON_JSONPARSER__

#include "JsonStructure.h"
#include "../base/Macros.h"
#include "libjson/libjson.h"

namespace framework {
    class JsonParser
    {
        SINGLETON(JsonParser);
    public:
        /**
         * Parse the json string to json structures(JsonObject/JsonArray).
         *
         * @param jsonStr Json string.
         *
         * @return Return json object if it's a valid string, or return nullptr.
         */
        cocos2d::Ref *parseString(const std::string &jsonStr);
        
        /**
         * Parse the json file to json structures(JsonObject/JsonArray).
         *
         * @param jsonPath Json file path.
         *
         * @return Return json object if it's a valid string, or return nullptr.
         */
        cocos2d::Ref *parseFile(const std::string &jsonPath);
        
    private:
        cocos2d::Ref *parseJsonNode(JSONNODE *jsonNode);
        
        JsonObject *parseToJsonObject(JSONNODE *jsonNode);
        
        JsonArray *parseToJsonArray(JSONNODE *jsonNode);
    };
}

#endif /* defined(__JSON_JSONPARSER__) */
