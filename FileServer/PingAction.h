#pragma once
#include "Protocol.h"

struct PingRequest : public Request
{
	PingRequest() : Request(MAKE_ID(PingRequest))
	{
	}

	HAS_EMPTY_READ_WRITE_PAYLOAD_METHODS;
};

struct PingResponse : public Response
{
	PingResponse() : Response(MAKE_ID(PingResponse))
	{
	}

	HAS_EMPTY_READ_WRITE_PAYLOAD_METHODS
};

typedef Action<PingRequest, PingResponse> PingAction;
