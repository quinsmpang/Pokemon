/******************************
Description: Make the object uncopyable, just inherit this class privately
Author: M.Wan
Date: 11/25/2014
******************************/

#ifndef __BASE_UNCOPYABLE__
#define __BASE_UNCOPYABLE__

namespace framework
{
	class Uncopyable
	{
	public:
		~Uncopyable() {}

	protected:
		Uncopyable() {}

	private:
		Uncopyable(const Uncopyable&);
		Uncopyable &operator=(const Uncopyable&);
	};
}

#endif
