/******************************
Description: Define some macros
Author: M.Wan
Date: 8/3/2014
******************************/

/**
* Make a class singleton
*/
#define SINGLETON(__TYPE__)		\
public:		\
	static __TYPE__* getInstance()	\
	{	\
		static __TYPE__* _instance;	\
		if (!_instance)	\
		{	\
			_instance = new __TYPE__();	\
		}	\
		return _instance;		\
	}	\
private:	\
	__TYPE__();

/**
* Convert std::string to wchar*
*/
#define STDSTRING_TO_WCHAR(__STR__, __BUFFER__)		\
for (int i = 0; i < (__STR__).size(); i++)	\
{	\
	(__BUFFER__)[i] = (__STR__)[i];	\
}