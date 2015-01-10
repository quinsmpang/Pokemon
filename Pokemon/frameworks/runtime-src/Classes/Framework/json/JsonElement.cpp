#include "JsonElement.h"
#include "cocos2d.h"
#include <new>

using namespace cocos2d;
using namespace std;

namespace framework {
    JsonBoolean *JsonBoolean::create(bool value)
    {
        auto pElement = new (nothrow) JsonBoolean(value);
        if (pElement) {
            pElement->autorelease();
            return pElement;
        }
        return nullptr;
    }
    
    JsonBoolean::JsonBoolean(bool value)
        : _val(value)
    {
    }
    
    bool JsonBoolean::boolValue()
    {
        return _val;
    }
    
    double JsonBoolean::numberValue()
    {
        if (_val) {
            return 1;
        } else {
            return 0;
        }
    }
    
    const char *JsonBoolean::stringValue()
    {
        if (_val) {
            return "true";
        } else {
            return "false";
        }
    }
    
    JsonNumber *JsonNumber::create(double value)
    {
        auto pElement = new (nothrow) JsonNumber(value);
        if (pElement) {
            pElement->autorelease();
            return pElement;
        }
        return nullptr;
    }
    
    
    JsonNumber::JsonNumber(double value)
        : _val(value)
    {
    }
    
    bool JsonNumber::boolValue()
    {
        return bool(_val);
    }
    
    double JsonNumber::numberValue()
    {
        return _val;
    }
    
    const char *JsonNumber::stringValue()
    {
        __String *pStr = __String::createWithFormat("%lf", _val);
        // format the number.
        std::string str = pStr->getCString();
        while (str.find_first_of('.') != -1 && (str.at(str.size() - 1) == '.' || str.at(str.size() - 1) == '0')) {
            str.erase(str.begin() + str.size() - 1);
        }
        return str.c_str();
    }
    
    JsonString *JsonString::create(const string &value)
    {
        auto pElement = new (nothrow) JsonString(value);
        if (pElement) {
            pElement->autorelease();
            return pElement;
        }
        return nullptr;
    }
    
    
    JsonString::JsonString(const std::string &value)
        : _val(value)
    {
    }
    
    bool JsonString::boolValue()
    {
        if (_val.size() > 0) {
            return true;
        } else {
            return false;
        }
    }
    
    double JsonString::numberValue()
    {
        double num;
        sscanf(_val.c_str(), "%lf", &num);
        return num;
    }
    
    const char *JsonString::stringValue()
    {
        return _val.c_str();
    }
}