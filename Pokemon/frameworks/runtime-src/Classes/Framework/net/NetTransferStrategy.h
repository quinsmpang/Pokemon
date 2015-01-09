/******************************
Description: Transfer rule in net.
Author: M.Wan
Date: 01/09/2015
******************************/

#ifndef __NET_NETTRANSFERSTRATEGY__
#define __NET_NETTRANSFERSTRATEGY__

#include <string>

namespace framework
{
	enum class NetTransferType
	{
		JSON = 1,
		XML = 2,
		PROTOBUF = 3,
	};

	class NetTransferStrategy
	{
	public:
		/**
		* NetTransferStrategy destructor.
		*/
		virtual ~NetTransferStrategy() {}

		/**
		* Convert body to the specified transfer data.
		*
		* @param Net body data.
		*/
		virtual void *toTransferData(const std::string &body) = 0;

		/**
		* Get transfer type.
		*
		* @return The exact transfer type.
		*/
		virtual NetTransferType getTransferType() = 0;
	};
}

#endif