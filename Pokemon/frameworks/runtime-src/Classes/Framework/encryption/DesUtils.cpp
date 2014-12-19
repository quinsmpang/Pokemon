#include "DesUtils.h"
#include "libdes/des.h"
#include <new>
#include <stdlib.h>
#include <string.h>

namespace framework
{
	DesUtils::DesUtils()
	{
	}

	unsigned char *DesUtils::encrypt(const char *key, unsigned char *data, int inSize, int *outSize)
	{
		DES des;
		*outSize = des.extend(inSize);
		unsigned char *buffer = (unsigned char*)malloc(*outSize);
		memcpy(buffer, data, inSize);
		des.encrypt3((unsigned char*)key, buffer, inSize);

		return buffer;
	}

	unsigned char *DesUtils::decrypt(const char *key, unsigned char *data, int inSize, int *outSize)
	{
		DES des;
		unsigned char *buffer = (unsigned char*)malloc(inSize);
		memcpy(buffer, data, inSize);
		des.decrypt3((unsigned char*)key, buffer, inSize, outSize);

		return buffer;
	}
}