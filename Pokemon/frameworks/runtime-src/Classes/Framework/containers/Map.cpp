#include "Map.h"

using namespace std;
using namespace cocos2d;

namespace framework
{
	Map::Map()
		: Ref()
		, _container(new map<const std::string, Ref*>())
	{
	}

	Map::~Map()
	{
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
			pAry->addObject(__String::create(iter->first));
		}

		return pAry;
	}

	Ref *Map::objectForKey(const string &key)
	{
		return this->_container->at(key);
	}

	void Map::setStringForKey(const string &value, const string &key)
	{
		this->_container->at(key) = __String::create(value);
	}

	void Map::setIntegerForKey(const int &value, const string &key)
	{
		this->_container->at(key) = __Integer::create(value);
	}

	void Map::setDoubleForKey(const float &value, const string &key)
	{
		this->_container->at(key) = __Double::create(value);
	}

	void Map::setObjectForKey(Ref *obj, const string &key)
	{
		this->_container->at(key) = obj;
	}

	void Map::removeObjectForKey(const string &key)
	{
		this->_container->erase(key);
	}

	void Map::clear()
	{
		this->_container->clear();
	}

	int Map::getLength()
	{
		return this->_container->size();
	}
}