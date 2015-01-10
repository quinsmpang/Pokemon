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
        /**
         * Create ordered array structure.
         *
         * @return Return Vector instance, or return nullptr when encounter an error.
         */
		static Vector *create();

        /**
         * Vector constructor.
         */
		explicit Vector();
        /**
         * Vector destructor.
         */
		~Vector();
        /**
         * Add string to the array.
         *
         * @param str String object to add.
         */
		void addString(const std::string &str);
        /**
         * Add boolean to the array.
         *
         * @param value Boolean to add.
         */
		void addBoolean(const bool &value);
        /**
         * Add integer to the array.
         *
         * @param num Integer to add.
         */
		void addInteger(const int &num);
        /**
         * Add decimal to the array.
         *
         * @param num Decimal number to add.
         */
		void addDouble(const float &num);
        /**
         * Add Ref object to the array.
         *
         * @param obj Cocos2dx object to add.
         */
		void addObject(cocos2d::Ref *obj);
        /**
         * Remove the object from the array.
         *
         * @param obj The object to be removed.
         */
		void removeObject(cocos2d::Ref *obj);
        /**
         * Remove the object at the specified index.
         *
         * @param index The index of the object to be removed.
         */
		void removeAt(int index);
        /**
         * Get the object at the specified index.
         *
         * @param index The index to locate.
         *
         * @return The object at the specified index.
         */
		cocos2d::Ref *objectAt(int index);
        /**
         * Set the object at the specified index.
         *
         * @param obj The new object the replace the old one.
         * @param index The index to replace new object.
         */
		void setObjectAt(cocos2d::Ref *obj, int index);
        /**
         * Clear all items of the array.
         */
		void clear();
        /**
         * Get the size of the array.
         *
         * @return The array size.
         */
		int getLength();
        /**
         * Check whether the array is empty.
         *
         * @return Boolean value which indicates whether the array is empty.
         */
		bool isEmpty();

	private:
		std::vector<cocos2d::Ref*> *_container;
	};
}

#endif