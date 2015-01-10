/******************************
 Description: XML elements classes.
 Author: M.Wan
 Date: 01/11/2015
 ******************************/

#ifndef __XML_XMLELEMENT__
#define __XML_XMLELEMENT__

#include "base/CCRef.h"
#include "../base/Uninheritable.h"
#include <string>

namespace framework {
    /**
     * Xml element base class.
     */
    class XmlElement : public cocos2d::Ref
    {
    public:
        /**
         * XmlElement destructor.
         */
        virtual ~XmlElement() {}
        
        /**
         * Return boolean value.
         */
        virtual bool boolValue() = 0;
        /**
         * Return number value.
         */
        virtual double numberValue() = 0;
        /**
         * Return string value.
         */
        virtual const char *stringValue() = 0;
    };
    
    class XmlBoolean : public cocos2d::Ref, Uninheritable<XmlBoolean>
    {
    public:
        /**
         * Create xml boolean element.
         *
         * @param value Boolean value.
         *
         * @return Return boolean xml element.
         */
        static XmlBoolean *create(bool value);
        
        /**
         * XmlBoolean constructor.
         *
         * @param value Boolean value.
         */
        XmlBoolean(bool value);
        
        /**
         * Return exact value.
         *
         * @return Boolean value.
         */
        bool boolValue();
        /**
         * Return 1 or 0.
         *
         * @return True to 1, False to 0.
         */
        double numberValue();
        /**
         * Return string value.
         *
         * @return True to "true", False to "false".
         */
        const char *stringValue();
        
    private:
        bool _val;
    };
    
    class XmlNumber : public XmlElement, public Uninheritable<XmlNumber>
    {
    public:
        /**
         * Create xml number element.
         *
         * @param value Number value.
         *
         * @return Return number xml element.
         */
        static XmlNumber *create(double value);
        
        /**
         * XmlNumber constructor.
         *
         * @param value Number value.
         */
        XmlNumber(double value);
        
        /**
         * Return true if the number is a non-zero value.
         *
         * @return Non-zero to true, zero to false.
         */
        bool boolValue();
        /**
         * Return exact number.
         *
         * @return Number value.
         */
        double numberValue();
        /**
         * Return string format of number.
         *
         * @return String of number.
         */
        const char *stringValue();
        
    private:
        double _val;
    };
    
    class XmlString : public XmlElement, public Uninheritable<XmlString>
    {
    public:
        /**
         * Create xml string element.
         *
         * @param value String value.
         *
         * @return Return string xml element.
         */
        static XmlString *create(const std::string &value);
        
        /**
         * XmlString constructor.
         *
         * @param value String value.
         */
        XmlString(const std::string &value);
        
        /**
         * Return true if it's not an empty string.
         *
         * @return Non-empty string to true, otherwise false.
         */
        bool boolValue();
        /**
         * Return exact number.
         *
         * @return Number value.
         */
        double numberValue();
        /**
         * Return string format of number.
         *
         * @return String of number.
         */
        const char *stringValue();
        
    private:
        std::string _val;
    };
}

#endif /* defined(__XML_XMLELEMENT__) */
