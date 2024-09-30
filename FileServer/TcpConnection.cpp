#include "TcpConnection.h"
#include "Logger.h"
#include "ServerSideActionExecutor.h"

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
