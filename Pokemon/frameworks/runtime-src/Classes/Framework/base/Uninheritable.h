/******************************
Description: Make the class uninheritable, just let your class inherit the Uninheritable<T>
Author: M.Wan
Date: 11/25/2014
******************************/

#ifndef __BASE_UNINHERITABLE__
#define __BASE_UNINHERITABLE__

namespace framework
{
	template<typename T>
	class Uninheritable;

	template<typename T>
	class Sealed
	{
		friend T;
		friend Uninheritable<T>;
	private:
		Sealed() {}
	};

    
	/**
     * Make the object inheritable.
     */
	template<typename T>
	class Uninheritable : public virtual Sealed<T>		// use virtual inherit is to ensure the derived class of a sealed class must call the Sealed's constructor at first.
	{
	protected:
		Uninheritable() {}
	};
}

#endif