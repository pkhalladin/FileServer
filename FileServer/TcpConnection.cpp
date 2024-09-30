#include "TcpConnection.h"
#include "Logger.h"
#include "ServerSideActionExecutor.h"
#include "NoneAction.h"
#include "PingAction.h"
#include "ServerInfoAction.h"

using namespace std;
using namespace boost::asio;

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
            shared_ptr<Header> header = ServerSideActionExecutor<NoneAction>::ReadHeader(socket);

            if (header->id == MAKE_ID(PingRequest))
            {
                write(socket, buffer("PING"));
            }
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
