/******************************
Description: DES algorithm to encrypt and decrypt files
Author: M.Wan
Date: 6/21/2014
******************************/

#ifndef __ENCRYPTION_DESUTILS__
#define __ENCRYPTION_DESUTILS__

#include "../base/Macros.h"

namespace framework
{
	class DesUtils
	{
		SINGLETON(DesUtils);
	public:
		// key: 24-bit encryption key;  data: data to be encrypted;  inSize: data size;  outSize: data size after the encryption.
		// Note: You have to delete the non-nil return value by yourself.  free(p);
		unsigned char *encrypt(const char *key, unsigned char *data, int inSize, int *outSize);

		// Note: You have to delete the non-nil return value by yourself.  free(p);
		unsigned char *decrypt(const char *key, unsigned char *data, int inSize, int *outSize);

	private:
		static DesUtils *_instance;
	};
}

#endif