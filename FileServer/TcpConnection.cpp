#include "TcpConnection.h"
#include "Logger.h"

using namespace std;

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
        try
        {
            char data[4096];

            size_t n = socket.read_some(boost::asio::buffer(data, sizeof(data)));
            logger << string(data, n) << endl;
        }
        catch (std::exception& e)
        {
            logger << e.what() << std::endl;
            break;
        }
    }
}

TcpConnection::TcpConnection(boost::asio::ip::tcp::socket& socket) : socket(socket)
{
}
