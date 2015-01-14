#include "JsonFormatter.h"
#include "JsonElement.h"
#include "../base/RefString.h"

using namespace cocos2d;
using namespace std;

namespace framework {
    JsonFormatter::JsonFormatter()
    {
    }
    
    string JsonFormatter::format(Ref *json, bool isPretty)
    {
        JSONNODE *jsonNode = this->formatToJsonNode(json);
        json_char *jsonChar = isPretty ? json_write_formatted(jsonNode) : json_write(jsonNode);
        string jsonStr(jsonChar);
        json_free(jsonChar);
        json_delete(jsonNode);
        
        return jsonStr;
    }
    
    JSONNODE *JsonFormatter::formatToJsonNode(Ref *json)
    {
        CCASSERT(json, "Invalid json.");
        JsonObject *pJsonObj = nullptr;
        JsonArray *pJsonAry = nullptr;
        if ((pJsonObj = dynamic_cast<JsonObject*>(json)) != nullptr) {
            return this->formatJsonObjectToJsonNode(pJsonObj);
        } else if ((pJsonAry = dynamic_cast<JsonArray*>(json)) != nullptr) {
            return this->formatJsonArrayToJsonNode(pJsonAry);
        }
        CCASSERT(false, "Invalid json type.");
        return nullptr;
    }
    
    JSONNODE *JsonFormatter::formatJsonObjectToJsonNode(JsonObject *json)
    {
        CCASSERT(json, "Invalid JsonObject.");
        JSONNODE *jsonNode = json_new(JSON_NODE);
        int count = json->count();
        Vector *keys = json->allKeys();
        for (int i = 0; i < count; ++i) {
            string szKey = ((RefString*)keys->objectAt(i))->getCString();
            Ref *val = json->_dataHolder->objectForKey(szKey);
            JsonBoolean *pJsonBool = nullptr;
            JsonNumber *pJsonNum = nullptr;
            JsonString *pJsonStr = nullptr;
            JsonObject *pJsonObj = nullptr;
            JsonArray *pJsonAry = nullptr;
            if ((pJsonBool = dynamic_cast<JsonBoolean*>(val)) != nullptr) {
                json_push_back(jsonNode, json_new_b(szKey.c_str(), pJsonBool->boolValue()));
            } else if ((pJsonNum = dynamic_cast<JsonNumber*>(val)) != nullptr) {
                json_push_back(jsonNode, json_new_f(szKey.c_str(), pJsonNum->numberValue()));
            } else if ((pJsonStr = dynamic_cast<JsonString*>(val)) != nullptr) {
                json_push_back(jsonNode, json_new_a(szKey.c_str(), pJsonStr->stringValue()));
            } else if ((pJsonObj = dynamic_cast<JsonObject*>(val)) != nullptr) {
                JSONNODE *node = this->formatJsonObjectToJsonNode(pJsonObj);
                json_set_name(node, szKey.c_str());
                json_push_back(jsonNode, node);
            } else if ((pJsonAry = dynamic_cast<JsonArray*>(val)) != nullptr) {
                JSONNODE *node = this->formatJsonArrayToJsonNode(pJsonAry);
                json_set_name(node, szKey.c_str());
                json_push_back(jsonNode, node);
            }
        }
        
        return jsonNode;
    }
    
    JSONNODE *JsonFormatter::formatJsonArrayToJsonNode(JsonArray *json)
    {
        CCASSERT(json, "Invalid JsonObject.");
        JSONNODE *jsonNode = json_new(JSON_ARRAY);
        int count = json->count();
        for (int i = 0; i < count; ++i) {
            Ref *val = json->_dataHolder->objectAt(i);
            JsonBoolean *pJsonBool = nullptr;
            JsonNumber *pJsonNum = nullptr;
            JsonString *pJsonStr = nullptr;
            JsonObject *pJsonObj = nullptr;
            JsonArray *pJsonAry = nullptr;
            if ((pJsonBool = dynamic_cast<JsonBoolean*>(val)) != nullptr) {
                json_push_back(jsonNode, json_new_b(nullptr, pJsonBool->boolValue()));
            } else if ((pJsonNum = dynamic_cast<JsonNumber*>(val)) != nullptr) {
                json_push_back(jsonNode, json_new_f(nullptr, pJsonNum->numberValue()));
            } else if ((pJsonStr = dynamic_cast<JsonString*>(val)) != nullptr) {
                json_push_back(jsonNode, json_new_a(nullptr, pJsonStr->stringValue()));
            } else if ((pJsonObj = dynamic_cast<JsonObject*>(val)) != nullptr) {
                json_push_back(jsonNode, this->formatJsonObjectToJsonNode(pJsonObj));
            } else if ((pJsonAry = dynamic_cast<JsonArray*>(val)) != nullptr) {
                json_push_back(jsonNode, this->formatJsonArrayToJsonNode(pJsonAry));
            }
        }
        
        return jsonNode;
    }
}