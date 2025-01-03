#pragma once

#include "Protocol.h"
#include "Logger.h"

struct CdRequest : public Request
{
	std::string path;

	CdRequest(const std::string& path = "") : Request(MAKE_ID(CdRequest)), path(path)
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

struct CdResponse : public Response
{
	std::string path;

	CdResponse() : Response(MAKE_ID(CdResponse))
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

typedef Action<CdRequest, CdResponse> CdAction;
