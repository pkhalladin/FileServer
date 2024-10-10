#pragma once
#include "Protocol.h"

struct NoneRequest : public Request
{
	NoneRequest() : Request(MAKE_ID(NoneRequest))
	{
	}

	HAS_EMPTY_READ_WRITE_PAYLOAD_METHODS;
};

struct NoneResponse : public Response
{
	NoneResponse() : Response(MAKE_ID(NoneResponse))
	{
	}

	HAS_EMPTY_READ_WRITE_PAYLOAD_METHODS;
};

typedef Action<NoneRequest, NoneResponse> NoneAction;
