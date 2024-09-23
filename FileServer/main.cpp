#include <iostream>
#include "CommandLine.h"
#include "TcpServer.h"

using namespace std;

const int DEFAULT_PORT = 3333;
const bool DEFAULT_REMOTE_STATE = false;

int main(int argc, char** argv)
{
	CommandLine commandLine(DEFAULT_PORT, DEFAULT_REMOTE_STATE);

	if (!commandLine.TryParse(argc, argv))
	{
		return -1;
	}

	boost::asio::io_context context;
	TcpServer server(context, commandLine.GetPort(), commandLine.IsRemote());

	server.StartAccept();

	return 0;
}		

