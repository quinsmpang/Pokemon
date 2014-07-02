/******************************
Description: Data structure: Array
Author: M.Wan
Date: 5/30/2014
******************************/

#ifndef __CONTAINERS_VECTOR__
#define __CONTAINERS_VECTOR__

#include "cocos2d.h"
#include <vector>
#include <string>

namespace framework
{
	class Vector : public cocos2d::Ref
	{
	public:
		static Vector *create();

		explicit Vector();
		~Vector();
		void addString(const std::string &str);
		void addInteger(const int &num);
		void addDouble(const float &num);
		void addObject(cocos2d::Ref *obj);
		void removeObject(cocos2d::Ref *obj);
		void removeAt(int index);
		cocos2d::Ref *objectAt(int index);
		void setObjectAt(cocos2d::Ref *obj, int index);
		void clear();
		int getLength();
		bool isEmpty();

	private:
		std::vector<cocos2d::Ref*> *_container;
	};
}

#endif