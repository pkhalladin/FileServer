#pragma once
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>

class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{
public:
	typedef std::shared_ptr<TcpConnection> pointer;

	static pointer Create(boost::asio::ip::tcp::socket& socket);
	boost::asio::ip::tcp::socket& GetSocket();
	void Start();
private:
	boost::asio::ip::tcp::socket& socket;
	std::string workingDirectory = "C:/";

	TcpConnection(boost::asio::ip::tcp::socket& socket);
};

