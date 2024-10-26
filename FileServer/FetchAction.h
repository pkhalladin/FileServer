#pragma once

#include "Protocol.h"
#include "Logger.h"

struct FetchRequest : public Request
{
	std::string path;

	FetchRequest(const std::string& path = "") : Request(MAKE_ID(FetchRequest)), path(path)
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

struct FetchResponse : public Response
{
	std::shared_ptr<uint8_t[]> data;
	
	FetchResponse() : Response(MAKE_ID(FetchResponse))
	{
		header.hasPayload = true;
	}

	void ReadPayload(const Payload& payload)
	{
		if (payload.size() != 1)
		{
			throw std::runtime_error("Invalid payload size");
		}

		data = std::shared_ptr<uint8_t[]>(new uint8_t[payload[0].size]);
		memcpy(data.get(), payload[0].data, payload[0].size);
	}

	void WritePayload(Payload& payload) const
	{
		payload.push_back({ sizeof(uint8_t), data.get()});
	}
};

typedef Action<FetchRequest, FetchResponse> FetchAction;
