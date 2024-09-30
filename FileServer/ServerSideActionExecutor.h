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

	static std::shared_ptr<ResponseType> Execute(
		boost::asio::ip::tcp::socket& socket, RequestFunction requestFunction)
	{
		std::shared_ptr<RequestType> request = Deserializer::FromSocket<RequestType>(socket);
		return requestFunction(*request);
	}
};
