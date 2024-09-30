#pragma once
#include "Macro.h"
#include <vector>

struct Header
{
	uint64_t id;
	uint64_t creationMoment;
	bool hasPayload;

	Header(uint64_t id = 0L) : id(id), creationMoment(NOW_MICROSECONDS()), hasPayload(false)
	{
	}
};

struct PayloadItem
{
	size_t size;
	uint8_t* data;
};

using Payload = std::vector<PayloadItem>;

struct Request
{
	Header header;

	Request(uint64_t id) : header(id)
	{
	}
};

struct Response
{
	Header header;

	Response(uint64_t id) : header(id)
	{
	}
};

template <typename TRequest, typename TResponse>
struct Action
{
	typedef TRequest RequestType;
	typedef TResponse ResponseType;
};