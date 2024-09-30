#pragma once
#include <memory>
#include <boost/asio.hpp>

class Deserializer
{
public:
	template <typename T>
	static std::shared_ptr<T> FromSocket(boost::asio::ip::tcp::socket& socket)
	{
		static_assert(std::is_standard_layout<T>::value);

		T* instance = new T();
		size_t n = boost::asio::read(socket, boost::asio::buffer(&instance->header, sizeof(Header)));
		if (n != sizeof(Header))
		{
			delete instance;
			throw std::runtime_error("Failed to read header from socket");
		}
		if (instance->header.hasPayload)
		{
			size_t payloadSize;
			n = boost::asio::read(socket, boost::asio::buffer(&payloadSize, sizeof(size_t)));

			if (n != sizeof(size_t))
			{
				delete instance;
				throw std::runtime_error("Failed to read payload size from socket");
			}

			Payload payload(payloadSize);

			for (size_t i = 0; i < payloadSize; i++)
			{
				size_t payloadItemSize;
				n = boost::asio::read(socket, boost::asio::buffer(&payloadItemSize, sizeof(size_t)));

				if (n != sizeof(size_t))
				{
					delete instance;
					throw std::runtime_error("Failed to read payload item size from socket");
				}

				payload[i].size = payloadItemSize;
				payload[i].data = new uint8_t[payloadItemSize];

				n = boost::asio::read(socket, boost::asio::buffer(payload[i].data, payloadItemSize));

				if (n != payloadItemSize)
				{
					delete instance;
					throw std::runtime_error("Failed to read payload item from socket");
				}
			}

			instance->ReadPayload(payload);

			for (size_t i = 0; i < payloadSize; i++)
			{
				delete[] payload[i].data;
			}
		}
		return std::shared_ptr<T>(instance);
	}
};

