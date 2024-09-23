#include "TcpConnection.h"

TcpConnection::pointer TcpConnection::Create(boost::asio::ip::tcp::socket& socket)
{
    return pointer(new TcpConnection(socket));
}

boost::asio::ip::tcp::socket& TcpConnection::GetSocket()
{
    return socket;
}

void TcpConnection::Start()
{
    while (true)
    {
        char data[4096];

        socket.write_some(boost::asio::buffer("AAA"));
        socket.read_some(boost::asio::buffer(data, sizeof(data)));
    }
}

TcpConnection::TcpConnection(boost::asio::ip::tcp::socket& socket) : socket(socket)
{
}
