#pragma once
#include <stdint.h>
#include <boost/date_time.hpp>

static uint64_t MakeId(const char* symbol)
{
	uint64_t id = 1, c;
	while ((c = *symbol++) != 0)
	{
		id *= c;
		if (id == 0)
		{
			id = 1;
		}
	}
	return id;
}

#define MAKE_ID(symbol) MakeId(#symbol)

#define NOW_MICROSECONDS() (boost::posix_time::microsec_clock::universal_time().time_of_day().total_microseconds())

// TODO: dodaæ makro HAS_EMPTY_READ_WRITE_PAYLOAD_METHODS
