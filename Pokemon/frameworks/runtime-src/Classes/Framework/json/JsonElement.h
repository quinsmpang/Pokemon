/******************************
 Description: JSON elements classes.
 Author: M.Wan
 Date: 01/10/2015
 ******************************/

#ifndef __JSON_JSONELEMENT__
#define __JSON_JSONELEMENT__

#include "base/CCRef.h"
#include "../base/Uninheritable.h"
#include <string>

namespace framework {
    /**
     * Json element base class.
     */
    class JsonElement : public cocos2d::Ref
    {
    public:
        /**
         * JsonElement destructor.
         */
        virtual ~JsonElement() {}
        
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
    
    class JsonBoolean : public JsonElement, public Uninheritable<JsonBoolean>
    {
    public:
        /**
         * Create json boolean element.
         *
         * @param value Boolean value.
         *
         * @return Return boolean json element.
         */
        static JsonBoolean *create(bool value);
        
        /**
         * JsonBoolean constructor.
         *
         * @param value Boolean value.
         */
        JsonBoolean(bool value);
        
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
    
    class JsonNumber : public JsonElement, public Uninheritable<JsonNumber>
    {
    public:
        /**
         * Create json number element.
         *
         * @param value Number value.
         *
         * @return Return number json element.
         */
        static JsonNumber *create(double value);
        
        /**
         * JsonBoolean constructor.
         *
         * @param value Boolean value.
         */
        JsonNumber(double value);
        
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
    
    class JsonString : public JsonElement, public Uninheritable<JsonString>
    {
    public:
        /**
         * Create json string element.
         *
         * @param value String value.
         *
         * @return Return string json element.
         */
        static JsonString *create(const std::string &value);
        
        /**
         * JsonString constructor.
         *
         * @param value String value.
         */
        JsonString(const std::string &value);
        
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

#endif /* defined(__JSON_JSONELEMENT__) */
