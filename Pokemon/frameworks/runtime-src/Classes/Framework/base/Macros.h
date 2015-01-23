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
protected:	\
	__TYPE__();

/**
* Convert std::string to wchar*
*/
#define STDSTRING_TO_WCHAR(__STR__, __BUFFER__)		\
for (int i = 0; i < (__STR__).size(); i++)	\
{	\
	(__BUFFER__)[i] = (__STR__)[i];	\
}

/**
* Mark as deprecated
*/
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#define FRAMEWORK_DEPRECATED __attribute__((deprecated))
#elif _MSC_VER >= 1400 //vs 2005 or higher
#define FRAMEWORK_DEPRECATED __declspec(deprecated)
#else
#define FRAMEWORK_DEPRECATED
#endif