#pragma once
#include "Serializer.h"
#include "Deserializer.h"

template <typename TAction>
class ClientSideActionExecutor
{
public:
	typedef typename TAction::RequestType RequestType;
	typedef typename TAction::ResponseType ResponseType;

	static std::shared_ptr<ResponseType> Execute(
		boost::asio::ip::tcp::socket& socket, const RequestType& request)
	{
		Serializer::ToSocket(socket, request);
		return Deserializer::FromSocket<ResponseType>(socket);
	}
};
