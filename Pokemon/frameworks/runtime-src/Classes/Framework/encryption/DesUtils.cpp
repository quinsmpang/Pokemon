#include "DesUtils.h"
#include "libdes\des.h"

using namespace cocos2d;

namespace framework
{
	DesUtils *DesUtils::_instance = nullptr;

	DesUtils *DesUtils::getInstance()
	{
		if (!_instance)
		{
			_instance = new DesUtils();
		}
		return _instance;
	}

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