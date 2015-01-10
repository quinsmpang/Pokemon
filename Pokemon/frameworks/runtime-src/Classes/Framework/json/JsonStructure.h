/******************************
 Description: JSON elements classes.
 Author: M.Wan
 Date: 01/10/2015
 ******************************/

#ifndef __JSON_JSONSTRUCTURE__
#define __JSON_JSONSTRUCTURE__

#include "cocos2d.h"
#include "../containers/Map.h"
#include "../containers/Vector.h"
#include <string>

namespace framework {
    class JsonArray;
    class JsonObject;
    
    class JsonObject : public cocos2d::Ref
    {
        friend class JsonFormatter;
    public:
        /**
         * JsonObject constructor
         */
        JsonObject();
        /**
         * JsonObject destructor
         */
        ~JsonObject();
        
        /**
         * Create an empty json object.
         */
        CREATE_FUNC(JsonObject);
        
        /**
         * Create a json object through string.
         *
         * @param jsonStr Json string.
         *
         * @return Return a new json object.
         */
        static JsonObject *createWithString(const std::string &jsonStr);
        /**
         * Create a json object from json file.
         *
         * @param jsonPath Json file path.
         *
         * @return Return a new json object.
         */
        static JsonObject *createWithFile(const std::string &jsonPath);
        
        /**
         * Figure out whether json has the specified key.
         *
         * @param key Key to consult.
         *
         * @return Whether the key exists.
         */
        bool hasKey(const std::string &key);
        
        /**
         * Get pairs count of json.
         *
         * @return Return the count of key-value pairs.
         */
        int count();
        
        /**
         * Add new boolean value to json.
         *
         * @param key Key to insert.
         * @param value Boolean value to add.
         */
        void putBoolean(const std::string &key, bool value);
        /**
         * Return boolean of the specified key.
         *
         * @param key Key to consult.
         *
         * @return Return boolean value of key.
         */
        bool getBoolean(const std::string &key) const;
        
        /**
         * Add new number value to json.
         *
         * @param key Key to insert.
         * @param value Number value to add.
         */
        void putNumber(const std::string &key, double value);
        /**
         * Return number of the specified key.
         *
         * @param key Key to consult.
         *
         * @return Return number value of key.
         */
        double getNumber(const std::string &key) const;
        
        /**
         * Add new string value to json.
         *
         * @param key Key to insert.
         * @param value String value to add.
         */
        void putString(const std::string &key, const std::string &value);
        /**
         * Return string of the specified key.
         *
         * @param key Key to consult.
         *
         * @return Return string value of key.
         */
        const char *getString(const std::string &key) const;
        
        /**
         * Add new json object to json.
         *
         * @param key Key to insert.
         * @param value Json object to add.
         */
        void putJsonObject(const std::string &key, JsonObject *value);
        /**
         * Get json object of the specified key.
         *
         * @param key Key to consult.
         *
         * @return Return json object of key.
         */
        JsonObject *getJsonObject(const std::string &key) const;
        
        /**
         * Add new json array to json.
         *
         * @param key Key to insert.
         * @param value Json array to add.
         */
        void putJsonArray(const std::string &key, JsonArray *value);
        /**
         * Get json array of the specified key.
         *
         * @param key Key to consult.
         *
         * @return Return json array of key.
         */
        JsonArray *getJsonArray(const std::string &key) const;
        
        /**
         * Remove value of the specified key.
         *
         * @param key Key to remove.
         */
        void remove(const std::string &key);
        
        /**
         * Clear json.
         */
        void clear();
        
        /**
         * Get keys of the json.
         *
         * @return All key collection of json.
         */
        Vector *allKeys();
        
        /**
         * Convert to json string.
         *
         * @return Return json string format.
         */
        const std::string &toString();
        /**
         * Convert to pretty string.
         *
         * @return Return pretty version of json string.
         */
        const std::string &toPrettyString();
        /**
         * Convert to lua string.
         *
         * @return Return lua version of json string.
         */
        const std::string &toLuaString();
        
    protected:
        bool init();
        
        Map *_dataHolder;
    };
    
    class JsonArray : public cocos2d::Ref
    {
        friend class JsonFormatter;
    public:
        /**
         * JsonArray constructor
         */
        JsonArray();
        /**
         * JsonArray destructor
         */
        ~JsonArray();
        
        /**
         * Create an empty json array.
         */
        CREATE_FUNC(JsonArray);
        
        /**
         * Create a json array through string.
         *
         * @param jsonStr Json string.
         *
         * @return Return a new json array.
         */
        static JsonArray *createWithString(const std::string &jsonStr);
        /**
         * Create a json array from json file.
         *
         * @param jsonPath Json file path.
         *
         * @return Return a new json array.
         */
        static JsonArray *createWithFile(const std::string &jsonPath);
        
        /**
         * Get json elements count of array.
         *
         * @return Return the count of array.
         */
        int count();
        
        /**
         * Append a boolean value to the array tail.
         *
         * @param value Boolean value.
         */
        void appendBoolean(bool value);
        /**
         * Insert a boolean value at the specified index.
         *
         * @param value Boolean value.
         * @param index Specified index.
         */
        void insertBoolean(bool value, int index);
        /**
         * Get boolean value at specified index.
         *
         * @param index Index to consult.
         *
         * @return Specified value.
         */
        bool getBooleanAt(int index);
        
        /**
         * Append a number value to the array tail.
         *
         * @param value Number value.
         */
        void appendNumber(double value);
        /**
         * Insert a number value at the specified index.
         *
         * @param value Number value.
         * @param index Specified index.
         */
        void insertNumber(double value, int index);
        /**
         * Get number value at specified index.
         *
         * @param index Index to consult.
         *
         * @return Specified value.
         */
        double getNumberAt(int index);
        
        /**
         * Append a string value to the array tail.
         *
         * @param value String value.
         */
        void appendString(const std::string &value);
        /**
         * Insert a string value at the specified index.
         *
         * @param value String value.
         * @param index Specified index.
         */
        void insertString(const std::string &value, int index);
        /**
         * Get string value at specified index.
         *
         * @param index Index to consult.
         *
         * @return Specified value.
         */
        const char *getStringAt(int index);
        
        /**
         * Append a json object to the array tail.
         *
         * @param value Json object.
         */
        void appendJsonObject(JsonObject *value);
        /**
         * Insert a json object at the specified index.
         *
         * @param value Json object.
         * @param index Specified index.
         */
        void insertJsonObject(JsonObject *value, int index);
        /**
         * Get json object at specified index.
         *
         * @param index Index to consult.
         *
         * @return Specified value.
         */
        JsonObject *getJsonObjectAt(int index);
        
        /**
         * Append a json array to the array tail.
         *
         * @param value Json array.
         */
        void appendJsonArray(JsonArray *value);
        /**
         * Insert a json array at the specified index.
         *
         * @param value Json array.
         * @param index Specified index.
         */
        void insertJsonArray(JsonArray *value, int index);
        /**
         * Get json array at specified index.
         *
         * @param index Index to consult.
         *
         * @return Specified value.
         */
        JsonArray *getJsonArrayAt(int index);
        
        /**
         * Remove the object at specified index.
         *
         * @param index Index to remove.
         */
        void removeAt(int index);
        
        /**
         * Clear all array elements.
         */
        void clear();
        
        /**
         * Convert to json string.
         *
         * @return Return json string format.
         */
        const std::string &toString();
        /**
         * Convert to pretty string.
         *
         * @return Return pretty version of json string.
         */
        const std::string &toPrettyString();
        /**
         * Convert to lua string.
         *
         * @return Return lua version of json string.
         */
        const std::string &toLuaString();
        
    protected:
        bool init();
        
        Vector *_dataHolder;
    };
}

#endif /* defined(__JSON_JSONSTRUCTURE__) */
