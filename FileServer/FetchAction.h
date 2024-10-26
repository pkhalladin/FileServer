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
	uint64_t size;
	bool isOk;

	FetchResponse() : Response(MAKE_ID(FetchResponse)), size(0), isOk(false)
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
		size = payload[0].size;
		memcpy(data.get(), payload[0].data, payload[0].size);
		isOk = (bool)payload[1].data[0];
	}

	void WritePayload(Payload& payload) const
	{
		payload.push_back({ size, data.get() });
		payload.push_back({ 1, (uint8_t*)&isOk });
	}
};

typedef Action<FetchRequest, FetchResponse> FetchAction;
