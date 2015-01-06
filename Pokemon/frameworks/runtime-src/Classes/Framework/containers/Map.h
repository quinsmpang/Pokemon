/******************************
Description: Data structure: Dictionary
Author: M.Wan
Date: 5/30/2014
******************************/

#ifndef __CONTAINERS_MAP__
#define __CONTAINERS_MAP__

#include "cocos2d.h"
#include "Vector.h"
#include <map>
#include <string>

namespace framework
{
	class Map : public cocos2d::Ref
	{
	public:
        /**
         * Create hash map.
         *
         * @return Return Map instance, or return nullptr when encounter an error.
         */
		static Map *create();
        
        /**
         * Map constructor.
         */
		explicit Map();
        /**
         * Map destructor.
         */
		~Map();

        /**
         * Get the collection of all keys of the map.
         *
         * @return Return Vector which contains all keys of the map.
         */
		Vector *allKeys();
        /**
         * Get the value of the specified key.
         *
         * @param key The key you want to consult.
         *
         * @return Return the mapped value of the specified key.
         */
		cocos2d::Ref *objectForKey(const std::string &key);
        /**
         * Set string value to the specified key.
         *
         * @param value The string value.
         * @param key The key you want to set.
         */
		void setStringForKey(const std::string &value, const std::string &key);
        /**
         * Set integer value to the specified key.
         *
         * @param value The integer value.
         * @param key The key you want to set.
         */
		void setIntegerForKey(const int &value, const std::string &key);
        /**
         * Set decimal value to the specified key.
         *
         * @param value The decimal value.
         * @param key The key you want to set.
         */
		void setDoubleForKey(const float &value, const std::string &key);
        /**
         * Set Ref value to the specified key.
         *
         * @param value The cocos2dx object.
         * @param key The key you want to set.
         */
		void setObjectForKey(cocos2d::Ref *obj, const std::string &key);
        /**
         * Remove item of the specified key.
         *
         * @param key The key you want to set.
         */
		void removeObjectForKey(const std::string &key);
        /**
         * Clear all items of the map.
         */
		void clear();
        /**
         * Get total size of the map.
         */
		int getLength();

	private:
		std::map<std::string, cocos2d::Ref*> *_container;
	};
}

#endif