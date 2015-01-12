/******************************
Description: Regex help class.
Author: M.Wan
Date: 01/11/2015
******************************/

#ifndef __UTILS_REGEXUTILS__
#define __UTILS_REGEXUTILS__

#include "base/CCRef.h"
#include "../base/Macros.h"
#include <string>
#include <functional>

namespace framework
{
	class RegexUtils
	{
		/**
		* RegexUtils is a singleton.
		*/
		SINGLETON(RegexUtils);
	public:
		/**
		* Find the first substring which matches the regex expression.
		*
		* @param content Target string to find.
		* @param regex Regex expression.
		*
		* @return Return the first substring which matches the regex, or return nullptr if it doesn't exist.
		*/
		const char *match(const std::string &content, const std::string &regex);

		/**
		* Find and replace the first substring which matches the regex expression.
		*
		* @param content Target string to replace.
		* @param regex Regex expression.
		* @param newStr The new string to replace the old one.
		*
		* @return Return the operation result.
		*/
		bool replaceOnce(const std::string &content, const std::string &regex, const std::string &newStr);

		/**
		* Find and replace all substrings which match the regex expression.
		*
		* @param content Target string to replace.
		* @param regex Regex expression.
		* @param newStr The new string to replace.
		*
		* @return Return success count.
		*/
		int replaceAll(const std::string &content, const std::string &regex, const std::string &newStr);
		/**
		* Replace all substrings which match the regex expression with the new string which is from the callback.
		*
		* @param content Target string to replace.
		* @param regex Regex expression.
		* @param target Callback sender.
		* @param callback The callback function to provide the new string.
		*
		* @return Return success count.
		*/
		int replaceAll(const std::string &content, const std::string &regex, cocos2d::Ref *target, const std::function<const char*(const char*)> &callback);
	};
}

#endif