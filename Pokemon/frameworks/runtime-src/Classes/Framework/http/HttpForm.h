/******************************
Description: Http form to commit.
Author: M.Wan
Date: 01/09/2015
******************************/

#ifndef __HTTP_HTTPFORM__
#define __HTTP_HTTPFORM__

#include "base/CCRef.h"
#include <string>
#include <map>

namespace framework
{
	class HttpForm : public cocos2d::Ref
	{
	public:
		/**
		* HttpForm destructor.
		*/
		~HttpForm();

		/**
		* Create http form object.
		*/
		CREATE_FUNC(HttpForm);

		/**
		* Add new parameter to the form.
		*
		* @param paramName Name of parameter.
		* @param paramValue Value of parameter.
		*/
		void putParam(const std::string &paramName, const std::string &paramValue);
		/**
		* Get the specified parameter value.
		*
		* @param paramName Name of parameter to get.
		*/
		const char *getParam(const std::string &paramName);
		/**
		* Remove the specified parameter.
		*
		* @param paramName Name of parameter to get.
		*/
		void removeParam(const std::string &paramName);

		/**
		* Convert object to connection string.
		*
		* @return String connected with parameters.
		*/
		const std::string &toString();

	protected:
		bool init();

		char decToHexChar(short n);
		short hexCharToDec(char c);
		/* Url decode */
		const std::string &decodeUrl(const std::string &url);
		/* Url encode */
		const std::string &encodeUrl(const std::string &url);

		std::map<std::string, std::string> _params;
	};
}

#endif
