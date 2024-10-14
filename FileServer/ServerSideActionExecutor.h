#pragma once
#include "Serializer.h"
#include "Deserializer.h"

template <typename TAction>
class ServerSideActionExecutor
{
public:
	typedef typename TAction::RequestType RequestType;
	typedef typename TAction::ResponseType ResponseType;
	typedef std::function<std::shared_ptr<ResponseType>(const RequestType& request)> RequestFunction;

	static std::shared_ptr<Header> ReadHeader(boost::asio::ip::tcp::socket& socket)
	{
		Header *header = new Header();
		size_t n = boost::asio::read(socket, boost::asio::buffer(header, sizeof(Header)));
		if (n != sizeof(Header))
		{
			delete header;
			throw std::runtime_error("Failed to read header from socket");
		}
		return std::shared_ptr<Header>(header);
	}

	static std::shared_ptr<ResponseType> Execute(boost::asio::ip::tcp::socket& socket, 
		std::shared_ptr<Header> header, RequestFunction requestFunction)
	{
		std::shared_ptr<RequestType> request = Deserializer::FromSocket<RequestType>(socket, header);
		std::shared_ptr<ResponseType> response = requestFunction(*request);
		Serializer::ToSocket(socket, *response);
		return response;
	}
};
