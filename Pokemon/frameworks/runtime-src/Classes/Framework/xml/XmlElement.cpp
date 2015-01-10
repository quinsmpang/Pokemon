#include "XmlElement.h"
#include "cocos2d.h"
#include <new>

using namespace cocos2d;
using namespace std;

namespace framework {
    XmlBoolean *XmlBoolean::create(bool value)
    {
        auto pElement = new (nothrow) XmlBoolean(value);
        if (pElement) {
            pElement->autorelease();
            return pElement;
        }
        return nullptr;
    }
    
    XmlBoolean::XmlBoolean(bool value)
        : _val(value)
    {
    }
    
    bool XmlBoolean::boolValue()
    {
        return _val;
    }
    
    double XmlBoolean::numberValue()
    {
        if (_val) {
            return 1;
        } else {
            return 0;
        }
    }
    
    const char *XmlBoolean::stringValue()
    {
        if (_val) {
            return "true";
        } else {
            return "false";
        }
    }
    
    XmlNumber *XmlNumber::create(double value)
    {
        auto pElement = new (nothrow) XmlNumber(value);
        if (pElement) {
            pElement->autorelease();
            return pElement;
        }
        return nullptr;
    }
    
    
    XmlNumber::XmlNumber(double value)
        : _val(value)
    {
    }
    
    bool XmlNumber::boolValue()
    {
        return bool(_val);
    }
    
    double XmlNumber::numberValue()
    {
        return _val;
    }
    
    const char *XmlNumber::stringValue()
    {
        __String *pStr = __String::createWithFormat("%lf", _val);
        // format the number.
        std::string str = pStr->getCString();
        while (str.find_first_of('.') != -1 && (str.at(str.size() - 1) == '.' || str.at(str.size() - 1) == '0')) {
            str.erase(str.begin() + str.size() - 1);
        }
        return str.c_str();
    }
    
    XmlString *XmlString::create(const string &value)
    {
        auto pElement = new (nothrow) XmlString(value);
        if (pElement) {
            pElement->autorelease();
            return pElement;
        }
        return nullptr;
    }
    
    
    XmlString::XmlString(const std::string &value)
        : _val(value)
    {
    }
    
    bool XmlString::boolValue()
    {
        if (_val.size() > 0) {
            return true;
        } else {
            return false;
        }
    }
    
    double XmlString::numberValue()
    {
        double num;
        sscanf(_val.c_str(), "%lf", &num);
        return num;
    }
    
    const char *XmlString::stringValue()
    {
        return _val.c_str();
    }
}
