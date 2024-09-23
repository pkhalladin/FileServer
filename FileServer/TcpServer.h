#pragma once
#include <boost/asio.hpp>
#include "TcpConnection.h"

class TcpServer
{
public:
	TcpServer(boost::asio::io_context& io_context, int port, bool isRemote);
	void StartAccept();
private:
	boost::asio::io_context& io_context;
	boost::asio::ip::tcp::acceptor acceptor;
};
