#pragma once
#include "Protocol.h"

struct PingRequest : public Request
{
	PingRequest() : Request(MAKE_ID(PingRequest))
	{
	}
};

struct PingResponse : public Response
{
	PingResponse() : Response(MAKE_ID(PingResponse))
	{
	}
};

typedef Action<PingRequest, PingResponse> PingAction;
