#pragma once

#include "Protocol.h"
#include "Logger.h"

struct ListRequest : public Request
{
	std::string path;

	ListRequest(const std::string& path = "") : Request(MAKE_ID(ListRequest)), path(path)
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

struct PathInfo
{
	std::string name;
	uint64_t size;
	bool isDirectory;
};

struct ListResponse : public Response
{
	std::vector<PathInfo> paths;

	ListResponse() : Response(MAKE_ID(ListResponse))
	{
		header.hasPayload = true;
	}

	void ReadPayload(const Payload& payload)
	{
		paths.clear();

		size_t offset = 0;
		while (offset < payload.size())
		{
			PathInfo pathInfo;
			pathInfo.name = std::string((char*)payload[offset].data, payload[offset].size);
			offset++;
			pathInfo.size = *(uint64_t*)payload[offset].data;
			offset++;
			pathInfo.isDirectory = *(bool*)payload[offset].data;
			offset++;
			paths.push_back(pathInfo);
		}
	}

	void WritePayload(Payload& payload) const
	{
		for (const PathInfo& pathInfo : paths)
		{
			payload.push_back({ pathInfo.name.size(), (uint8_t*)pathInfo.name.c_str() });
			payload.push_back({ sizeof(uint64_t), (uint8_t*)&pathInfo.size });
			payload.push_back({ sizeof(bool), (uint8_t*)&pathInfo.isDirectory });
		}
	}
};

typedef Action<ListRequest, ListResponse> ListAction;
