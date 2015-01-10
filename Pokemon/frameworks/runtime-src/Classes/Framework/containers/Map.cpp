#include "Map.h"
#include "../base/RefString.h"
#include "../base/RefInteger.h"
#include "../base/RefDouble.h"
#include "../base/RefBoolean.h"

using namespace std;
using namespace cocos2d;

namespace framework
{
	Map::Map()
		: Ref()
		, _container(new map<std::string, Ref*>())
	{
	}

	Map::~Map()
	{
		this->clear();
		if (this->_container)
		{
			delete this->_container;
		}
	}

	Map *Map::create()
	{
		auto pDict = new Map();
		if (pDict)
		{
			pDict->autorelease();
			return pDict;
		}
		CC_SAFE_RELEASE_NULL(pDict);
		return nullptr;
	}

	Vector *Map::allKeys()
	{
		auto pAry = Vector::create();

		for (auto iter = this->_container->cbegin(); iter != this->_container->cend(); ++iter)
		{
			pAry->addObject(RefString::create(iter->first.c_str()));
		}

		return pAry;
	}

	Ref *Map::objectForKey(const string &key)
	{
		return this->_container->at(key);
	}
    
    void Map::setBooleanForKey(bool value, const std::string &key)
    {
        auto refBoolean = RefBoolean::create(value);
        refBoolean->retain();
        (*(this->_container))[key] = refBoolean;
    }

	void Map::setStringForKey(const string &value, const string &key)
	{
		auto refStr = RefString::create(value.c_str());
		refStr->retain();
		(*(this->_container))[key] = refStr;
	}

	void Map::setIntegerForKey(const int &value, const string &key)
	{
		auto refNum = RefInteger::create(value);
		refNum->retain();
		(*(this->_container))[key] = refNum;
	}

	void Map::setDoubleForKey(const float &value, const string &key)
	{
		auto refNum = RefDouble::create(value);
		refNum->retain();
		(*(this->_container))[key] = refNum;
	}

	void Map::setObjectForKey(Ref *obj, const string &key)
	{
		if ((*(this->_container))[key])
		{
			(*(this->_container))[key]->release();
		}
		obj->retain();
		(*(this->_container))[key] = obj;
	}

	void Map::removeObjectForKey(const string &key)
	{
		if ((*(this->_container))[key])
		{
			(*(this->_container))[key]->release();
		}
		this->_container->erase(key);
	}

	void Map::clear()
	{
		for (auto iter = this->_container->cbegin(); iter != this->_container->cend(); ++iter)
		{
			iter->second->release();
		}
		this->_container->clear();
	}

	int Map::getLength()
	{
		return this->_container->size();
	}
}