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
		static Map *create();

		explicit Map();
		~Map();

		Vector *allKeys();
		cocos2d::Ref *objectForKey(const std::string &key);
		void setStringForKey(const std::string &value, const std::string &key);
		void setIntegerForKey(const int &value, const std::string &key);
		void setDoubleForKey(const float &value, const std::string &key);
		void setObjectForKey(cocos2d::Ref *obj, const std::string &key);
		void removeObjectForKey(const std::string &key);
		void clear();
		int getLength();

	private:
		std::map<const std::string, cocos2d::Ref*> *_container;
	};
}

#endif