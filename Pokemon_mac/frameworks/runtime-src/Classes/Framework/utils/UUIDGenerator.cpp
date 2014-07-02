#include "UUIDGenerator.h"

using namespace std;

namespace framework
{
	UUIDGenerator *UUIDGenerator::_instance = nullptr;

	UUIDGenerator *UUIDGenerator::getInstance()
	{
		if (!_instance)
		{
			_instance = new UUIDGenerator();
		}
		return _instance;
	}

	GUID UUIDGenerator::createGUID()
	{
		GUID guid;
#ifdef WIN32
		::CoCreateGuid(&guid);
#else
		::uuid_generate(reinterpret_cast<unsigned char*>(&guid));
#endif
		return guid;
	}

	const string &UUIDGenerator::guidToString(const GUID &guid)
	{
		char buffer[64] = { 0 };
#ifdef __GNUC__
		::snprintf(
#else	// msvc
		::_snprintf_s(
#endif
			buffer, sizeof(buffer), "{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}", guid.Data1, guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);

		return string(buffer);
	}

	const string &UUIDGenerator::generateUUID()
	{
		return this->guidToString(this->createGUID());
	}
}