#include "CommandLine.h"
#include <boost/program_options.hpp>
#include <iostream>

using namespace boost::program_options;
using namespace std;

CommandLine::CommandLine(int port, bool isRemote) : port(port), isRemote(isRemote)
{
}

bool CommandLine::TryParse(int argc, char** argv)
{
	options_description description("Options");
	variables_map variables;

	try
	{
		description.add_options()
			("help,h", "prints this help page")
			("port,p", value<int>(&port)->default_value(port), "port")
			("remote,r", value<bool>(&isRemote)->default_value(isRemote)->implicit_value(true), 
				"remote state")
			;
		store(parse_command_line(argc, argv, description), variables);
		notify(variables);
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
		return false;
	}

	return true;
}

int CommandLine::GetPort() const
{
	return port;
}

bool CommandLine::IsRemote() const
{
	return isRemote;
}
