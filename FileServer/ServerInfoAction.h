#pragma once
#include "Protocol.h"
#include <string>

struct ServerInfoRequest : public Request
{
	ServerInfoRequest() : Request(MAKE_ID(ServerInfoRequest))
	{
	}

	HAS_EMPTY_READ_WRITE_PAYLOAD_METHODS;
};

struct ServerInfoResponse : public Response
{
	std::string machineName;
	std::string version;

	ServerInfoResponse() : Response(MAKE_ID(ServerInfoResponse))
	{
		header.hasPayload = true;
	}

	void ReadPayload(const Payload& payload)
	{
		if (payload.size() != 2)
		{
			throw std::runtime_error("Invalid payload size");
		}

		machineName = std::string((char*)payload[0].data, payload[0].size);
		version = std::string((char*)payload[1].data, payload[1].size);
	}

	void WritePayload(Payload& payload) const
	{
		payload.push_back({ machineName.size(), (uint8_t*)machineName.c_str() });
		payload.push_back({ version.size(), (uint8_t*)version.c_str() });
	}
};

typedef Action<ServerInfoRequest, ServerInfoResponse> ServerInfoAction;


