/******************************
Description: Binary data, to save raw data and data size
Author: M.Wan
Date: 8/4/2014
******************************/

#ifndef __BASE_BINARYDATA__
#define __BASE_BINARYDATA__

#include "base/CCRef.h"
#include <memory>

namespace framework
{
	/**
	* Wrapper of binary data.
	*/
	class BinaryData : public cocos2d::Ref
	{
	public:
		/**
		* Create BinaryObject object.
		*
		* @param data Raw binary data.
		* @param size Binary data size.
		*
		* @return Return BinaryData instance, or return nullptr when encounter an error.
		*/
		static BinaryData *create(unsigned char *data, unsigned long size);

		/**
		* BinaryData destructor.
		*/
		virtual ~BinaryData();

		/**
		* Get raw data.
		*
		* @return Return the raw data.
		*/
		unsigned char *getData() const;
		/**
		* Get data size.
		*
		* @return Return data size.
		*/
		unsigned long getSize() const;

	private:
		bool init(unsigned char *data, unsigned long size);

		unsigned char *_data;
		unsigned long _size;
	};
}

#endif