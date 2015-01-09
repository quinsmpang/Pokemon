#include "HttpForm.h"
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

namespace framework
{
	bool HttpForm::init()
	{
		return true;
	}

	HttpForm::~HttpForm()
	{
	}

	void HttpForm::putParam(const std::string &paramName, const std::string &paramValue)
	{
		_params[paramName] = paramValue;
	}

	const char *HttpForm::getParam(const std::string &paramName)
	{
		if (_params.find(paramName) != _params.end())
		{
			return _params[paramName].c_str();
		}
		return nullptr;
	}

	void HttpForm::removeParam(const std::string &paramName)
	{
		auto iter = _params.find(paramName);
		if (iter != _params.end())
		{
			_params.erase(iter);
		}
	}

	const std::string &HttpForm::toString()
	{
		std::string paramUrl;
		auto end = --_params.end();
		for (auto iter = _params.begin(); iter != _params.end(); ++iter)
		{
			paramUrl.append(iter->first);
			paramUrl.append("=");
			paramUrl.append(iter->second);
			if (iter != end)
			{
				paramUrl.append("&");
			}
		}

		return paramUrl;
	}

	char HttpForm::decToHexChar(short n)
	{
		if (n >= 0 && n <= 9)
		{
			return char(short('0') + n);
		}
		else if (n >= 10 & n <= 15)
		{
			return char(short('A') + n - 10);
		}
		else
		{
			return char(0);
		}
	}

	short HttpForm::hexCharToDec(char c)
	{
		if (c >= '0' && c <= '9')
		{
			return short(c - '0');
		}
		else if (c >= 'a' && c <= 'f')
		{
			return short(c - 'a') + short(10);
		}
		else if (c >= 'A' && c <= 'F')
		{
			return short(c - 'A') + short(10);
		}
		else
		{
			return -1;
		}
	}

	const std::string &HttpForm::encodeUrl(const std::string &url)
	{
		string result;
		for (size_t i = 0; i < url.size(); i++)
		{
			char c = url[i];
			if ((c >= '0'&&c <= '9') || (c >= 'a'&&c <= 'z') || (c >= 'A'&&c <= 'Z') || c == '/' || c == '.')
			{
				result += c;
			}
			else
			{
				int j = c;
				if (j < 0)
				{
					j += 256;
				}
				int i1, i0;
				i1 = j / 16;
				i0 = j - i1 * 16;
				result += '%';
				result += this->decToHexChar(i1);
				result += this->decToHexChar(i0);
			}
		}

		return result;
	}

	const std::string &HttpForm::decodeUrl(const std::string &url)
	{
		string result;
		for (size_t i = 0; i < url.size(); i++)
		{
			char c = url[i];
			if (c != '%')
			{
				result += c;
			}
			else
			{
				char c1 = url[++i];
				char c0 = url[++i];
				int num = this->hexCharToDec(c1) * 16 + this->hexCharToDec(c0);
				result += char(num);
			}
		}

		return result;
	}
}