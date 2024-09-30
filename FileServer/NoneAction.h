#pragma once
#include "Protocol.h"

struct NoneRequest : public Request
{
	NoneRequest() : Request(MAKE_ID(NoneRequest))
	{
	}
};

struct NoneResponse : public Response
{
	NoneResponse() : Response(MAKE_ID(NoneResponse))
	{
	}
};

typedef Action<NoneRequest, NoneResponse> NoneAction;
