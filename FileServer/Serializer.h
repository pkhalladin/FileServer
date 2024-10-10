#pragma once
#include <boost/asio.hpp>
#include "Protocol.h"

class Serializer
{
public:
	template <typename T>
	static void ToSocket(boost::asio::ip::tcp::socket& socket, const T& instance)
	{
		// TODO: sprawdziæ dlaczego ServerInfoAction nie dzia³a
		// static_assert(std::is_standard_layout<T>::value);

		size_t n = boost::asio::write(socket, boost::asio::buffer(&instance.header, sizeof(Header)));
		if (n != sizeof(Header))
		{
			throw std::runtime_error("Failed to write header to socket");
		}
		if (instance.header.hasPayload)
		{
			Payload payload;
			instance.WritePayload(payload);

			size_t payloadSize = payload.size();
			n = boost::asio::write(socket, boost::asio::buffer(&payloadSize, sizeof(size_t)));

			if (n != sizeof(size_t))
			{
				throw std::runtime_error("Failed to write payload size to socket");
			}

			for (size_t i = 0; i < payloadSize; i++)
			{
				size_t payloadItemSize = payload[i].size;
				n = boost::asio::write(socket, boost::asio::buffer(&payloadItemSize, sizeof(size_t)));

				if (n != sizeof(size_t))
				{
					throw std::runtime_error("Failed to write payload item size to socket");
				}

				n = boost::asio::write(socket, boost::asio::buffer(payload[i].data, payloadItemSize));

				if (n != payloadItemSize)
				{
					throw std::runtime_error("Failed to write payload item to socket");
				}
			}
		}
	}
};
