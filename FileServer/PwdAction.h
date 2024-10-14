#pragma once

#include "Protocol.h"
#include "Logger.h"

struct PwdRequest : public Request
{
	PwdRequest() : Request(MAKE_ID(PwdRequest))
	{
	}

	HAS_EMPTY_READ_WRITE_PAYLOAD_METHODS;
};

struct PwdResponse : public Response
{
	std::string path;

	PwdResponse() : Response(MAKE_ID(PwdResponse))
	{
		header.hasPayload = true;
	}

	void ReadPayload(const Payload& payload)
	{
		if (payload.size() != 1)
		{
			throw std::runtime_error("Invalid payload size");
		}

		path = std::string((char*)payload[0].data, payload[0].size);
	}

	void WritePayload(Payload& payload) const
	{
		payload.push_back({ path.size(), (uint8_t*)path.c_str() });
	}
};

typedef Action<PwdRequest, PwdResponse> PwdAction;
