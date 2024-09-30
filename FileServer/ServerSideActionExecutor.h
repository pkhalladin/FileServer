#pragma once
#include "Serializer.h"
#include "Deserializer.h"

template <typename TAction>
class ServerSideActionExecutor
{
public:
	typedef typename TAction::RequestType RequestType;
	typedef typename TAction::ResponseType ResponseType;
	typedef std::shared_ptr<ResponseType> (*RequestFunction)(const RequestType& request);

	static std::shared_ptr<Header> ReadHeader(boost::asio::ip::tcp::socket& socket)
	{
		Header *header = new Header();
		size_t n = boost::asio::read(socket, boost::asio::buffer(&header, sizeof(Header)));
		if (n != sizeof(Header))
		{
			delete header;
			throw std::runtime_error("Failed to read header from socket");
		}
		return std::shared_ptr<Header>(header);
	}

	static std::shared_ptr<ResponseType> Execute(
		boost::asio::ip::tcp::socket& socket, RequestFunction requestFunction)
	{
		std::shared_ptr<RequestType> request = Deserializer::FromSocket<RequestType>(socket);
		return requestFunction(*request);
	}
};
