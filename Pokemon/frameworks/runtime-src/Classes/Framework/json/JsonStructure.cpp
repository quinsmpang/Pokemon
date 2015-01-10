#include "JsonStructure.h"
#include "JsonElement.h"
#include "JsonParser.h"
#include "JsonFormatter.h"
#include "../base/RefString.h"

namespace framework {
    /** JsonObject implementation **/
    JsonObject::JsonObject()
        : _dataHolder(new Map())
    {
    }
    
    JsonObject::~JsonObject()
    {
        CC_SAFE_RELEASE(_dataHolder);
    }
    
    bool JsonObject::init()
    {
        return true;
    }
    
    JsonObject *JsonObject::createWithString(const std::string &jsonStr)
    {
        return dynamic_cast<JsonObject*>(JsonParser::getInstance()->parseString(jsonStr));
    }
    
    JsonObject *JsonObject::createWithFile(const std::string &jsonPath)
    {
        return dynamic_cast<JsonObject*>(JsonParser::getInstance()->parseFile(jsonPath));
    }
    
    bool JsonObject::hasKey(const std::string &key)
    {
        return _dataHolder->objectForKey(key) != nullptr;
    }
    
    int JsonObject::count()
    {
        return _dataHolder->getLength();
    }
    
    void JsonObject::putBoolean(const std::string &key, bool value)
    {
        auto val = JsonBoolean::create(value);
        _dataHolder->setObjectForKey(val, key);
    }
    
    bool JsonObject::getBoolean(const std::string &key) const
    {
        auto val = (JsonBoolean*)_dataHolder->objectForKey(key);
        return val->boolValue();
    }
    
    void JsonObject::putNumber(const std::string &key, double value)
    {
        auto val = JsonNumber::create(value);
        _dataHolder->setObjectForKey(val, key);
    }
    
    double JsonObject::getNumber(const std::string &key) const
    {
        auto val = (JsonNumber*)_dataHolder->objectForKey(key);
        return val->numberValue();
    }
    
    void JsonObject::putString(const std::string &key, const std::string &value)
    {
        auto val = JsonString::create(value);
        _dataHolder->setObjectForKey(val, key);
    }
    
    const char *JsonObject::getString(const std::string &key) const
    {
        auto val = (JsonString*)_dataHolder->objectForKey(key);
        return val->stringValue();
    }
    
    void JsonObject::putJsonObject(const std::string &key, JsonObject *value)
    {
        _dataHolder->setObjectForKey(value, key);
    }
    
    JsonObject *JsonObject::getJsonObject(const std::string &key) const
    {
        return dynamic_cast<JsonObject*>(_dataHolder->objectForKey(key));
    }
    
    void JsonObject::putJsonArray(const std::string &key, JsonArray *value)
    {
        _dataHolder->setObjectForKey(value, key);
    }
    
    JsonArray *JsonObject::getJsonArray(const std::string &key) const
    {
        return dynamic_cast<JsonArray*>(_dataHolder->objectForKey(key));
    }
    
    void JsonObject::remove(const std::string &key)
    {
        _dataHolder->removeObjectForKey(key);
    }
    
    void JsonObject::clear()
    {
        _dataHolder->clear();
    }
    
    Vector *JsonObject::allKeys()
    {
        return _dataHolder->allKeys();
    }
    
    const std::string &JsonObject::toString()
    {
        return JsonFormatter::getInstance()->format(this);
    }
    
    const std::string &JsonObject::toPrettyString()
    {
        return JsonFormatter::getInstance()->format(this, true);
    }
    
    const std::string &JsonObject::toLuaString()
    {
        // begining
        std::string luaStr = "{\n";
        int num = this->count();
        Vector *keys = this->allKeys();
        for (int i = 0; i < num; ++i) {
            // key
            const char *szKey = static_cast<RefString*>(keys->objectAt(i))->getCString();
            luaStr.append("[\"");
            luaStr.append(szKey);
            luaStr.append("\"]");
            luaStr.append("=");
            // value
            Ref *pVal = _dataHolder->objectForKey(szKey);
            JsonBoolean *pJsonBool = nullptr;
            JsonNumber *pJsonNum = nullptr;
            JsonString *pJsonStr = nullptr;
            JsonObject *pJsonObj = nullptr;
            JsonArray *pJsonAry = nullptr;
            if ((pJsonBool = dynamic_cast<JsonBoolean*>(pVal)) != nullptr) {
                luaStr.append(pJsonBool->stringValue());
            } else if ((pJsonNum = dynamic_cast<JsonNumber*>(pVal)) != nullptr) {
                luaStr.append(pJsonNum->stringValue());
            } else if ((pJsonStr = dynamic_cast<JsonString*>(pVal)) != nullptr) {
                luaStr.append("[==[");
                luaStr.append(pJsonStr->stringValue());
                luaStr.append("]==]");
            } else if ((pJsonObj = dynamic_cast<JsonObject*>(pVal)) != nullptr) {
                std::string value = pJsonObj->toLuaString();
                luaStr.append(value);
            } else if ((pJsonAry = dynamic_cast<JsonArray*>(pVal)) != nullptr) {
                std::string value = pJsonAry->toLuaString();
                luaStr.append(value);
            }
            
            if (i < num - 1) {
                luaStr.append(",");
                luaStr.append("\n");
            }
        }
        // ending
        luaStr.append("\n}");
        return luaStr;
    }
    
    /** JsonArray implementation **/
    JsonArray::JsonArray()
        : _dataHolder(new Vector())
    {
    }
    
    JsonArray::~JsonArray()
    {
        CC_SAFE_RELEASE(_dataHolder);
    }
    
    bool JsonArray::init()
    {
        return true;
    }
    
    JsonArray *JsonArray::createWithString(const std::string &jsonStr)
    {
        return dynamic_cast<JsonArray*>(JsonParser::getInstance()->parseString(jsonStr));
    }
    
    JsonArray *JsonArray::createWithFile(const std::string &jsonPath)
    {
        return dynamic_cast<JsonArray*>(JsonParser::getInstance()->parseFile(jsonPath));
    }
    
    int JsonArray::count()
    {
        return _dataHolder->getLength();
    }
    
    void JsonArray::appendBoolean(bool value)
    {
        auto val = JsonBoolean::create(value);
        _dataHolder->addObject(val);
    }
    
    void JsonArray::insertBoolean(bool value, int index)
    {
        _dataHolder->setObjectAt(JsonBoolean::create(value), index);
    }
    
    bool JsonArray::getBooleanAt(int index)
    {
        auto val = (JsonBoolean*)_dataHolder->objectAt(index);
        return val->boolValue();
    }
    
    void JsonArray::appendNumber(double value)
    {
        auto val = JsonNumber::create(value);
        _dataHolder->addObject(val);
    }
    
    void JsonArray::insertNumber(double value, int index)
    {
        _dataHolder->setObjectAt(JsonNumber::create(value), index);
    }
    
    double JsonArray::getNumberAt(int index)
    {
        auto val = (JsonNumber*)_dataHolder->objectAt(index);
        return val->numberValue();
    }
    
    void JsonArray::appendString(const std::string &value)
    {
        auto val = JsonString::create(value);
        _dataHolder->addObject(val);
    }
    
    void JsonArray::insertString(const std::string &value, int index)
    {
        _dataHolder->setObjectAt(JsonString::create(value), index);
    }
    
    const char *JsonArray::getStringAt(int index)
    {
        auto val = (JsonString*)_dataHolder->objectAt(index);
        return val->stringValue();
    }
    
    void JsonArray::appendJsonObject(JsonObject *value)
    {
        _dataHolder->addObject(value);
    }
    
    void JsonArray::insertJsonObject(JsonObject *value, int index)
    {
        _dataHolder->setObjectAt(value, index);
    }
    
    JsonObject *JsonArray::getJsonObjectAt(int index)
    {
        return dynamic_cast<JsonObject*>(_dataHolder->objectAt(index));
    }
    
    void JsonArray::appendJsonArray(JsonArray *value)
    {
        _dataHolder->addObject(value);
    }
    
    void JsonArray::insertJsonArray(JsonArray *value, int index)
    {
        _dataHolder->setObjectAt(value, index);
    }
    
    JsonArray *JsonArray::getJsonArrayAt(int index)
    {
        return dynamic_cast<JsonArray*>(_dataHolder->objectAt(index));
    }
    
    void JsonArray::removeAt(int index)
    {
        _dataHolder->removeAt(index);
    }
    
    void JsonArray::clear()
    {
        _dataHolder->clear();
    }
    
    const std::string &JsonArray::toString()
    {
        return JsonFormatter::getInstance()->format(this);
    }
    
    const std::string &JsonArray::toPrettyString()
    {
        return JsonFormatter::getInstance()->format(this, true);
    }
    
    const std::string &JsonArray::toLuaString()
    {
        // begining
        std::string luaStr = "{\n";
        int num = this->count();
        for (int i = 0; i < num; ++i) {
            // value
            Ref *pVal = _dataHolder->objectAt(i);
            JsonBoolean *pJsonBool = nullptr;
            JsonNumber *pJsonNum = nullptr;
            JsonString *pJsonStr = nullptr;
            JsonObject *pJsonObj = nullptr;
            JsonArray *pJsonAry = nullptr;
            if ((pJsonBool = dynamic_cast<JsonBoolean*>(pVal)) != nullptr) {
                luaStr.append(pJsonBool->stringValue());
            } else if ((pJsonNum = dynamic_cast<JsonNumber*>(pVal)) != nullptr) {
                luaStr.append(pJsonNum->stringValue());
            } else if ((pJsonStr = dynamic_cast<JsonString*>(pVal)) != nullptr) {
                luaStr.append("[==[");
                luaStr.append(pJsonStr->stringValue());
                luaStr.append("]==]");
            } else if ((pJsonObj = dynamic_cast<JsonObject*>(pVal)) != nullptr) {
                std::string value = pJsonObj->toLuaString();
                luaStr.append(value);
            } else if ((pJsonAry = dynamic_cast<JsonArray*>(pVal)) != nullptr) {
                std::string value = pJsonAry->toLuaString();
                luaStr.append(value);
            }
            
            if (i < num - 1) {
                luaStr.append(",");
                luaStr.append("\n");
            }
        }
        // ending
        luaStr.append("\n}");
        return luaStr;
    }
}