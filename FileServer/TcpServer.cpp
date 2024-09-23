#include "TcpServer.h"
#include <boost/thread.hpp>
#include "Logger.h"

using namespace std;

TcpServer::TcpServer(boost::asio::io_context& io_context, int port, bool isRemote) 
	: io_context(io_context), acceptor(io_context, 
		boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
}

void TcpServer::StartAccept()
{
	boost::asio::ip::tcp::socket socket(io_context);
	while (true)
	{
		logger << "Waiting for connection..." << endl;
		socket = acceptor.accept(io_context);
		logger << "Connection accepted..." << endl;
		TcpConnection::pointer connection = TcpConnection::Create(socket);

		boost::thread thread(&TcpConnection::Start, connection);
	}
}
