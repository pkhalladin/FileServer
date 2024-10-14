#include "TcpConnection.h"
#include "Logger.h"
#include "ServerSideActionExecutor.h"
#include "NoneAction.h"
#include "PingAction.h"
#include "ServerInfoAction.h"
#include "PwdAction.h"
#include "CdAction.h"
#include <boost/asio/ip/host_name.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
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
				logger << "PingRequest" << endl;
				ServerSideActionExecutor<PingAction>::Execute(socket, header, [](const PingRequest& request) {
					return shared_ptr<PingResponse>(new PingResponse());
					});
			}
			else if (header->id == MAKE_ID(ServerInfoRequest))
			{
				logger << "ServerInfoRequest" << endl;
				ServerSideActionExecutor<ServerInfoAction>::Execute(socket, header, [](const ServerInfoRequest& request) {
					ServerInfoResponse* response = new ServerInfoResponse();
					response->machineName = boost::asio::ip::host_name();
					response->version = "1.0.0.0";
					return shared_ptr<ServerInfoResponse>(response);
					});
			}
			else if (header->id == MAKE_ID(PwdRequest))
			{
				logger << "PwdRequest" << endl;
				ServerSideActionExecutor<PwdAction>::Execute(socket, header, [&](const PwdRequest& request) {
					PwdResponse* response = new PwdResponse();
					response->path = workingDirectory;
					return shared_ptr<PwdResponse>(response);
					});
			}
			else if (header->id == MAKE_ID(CdRequest))
			{
				logger << "CdRequest" << endl;
				ServerSideActionExecutor<CdAction>::Execute(socket, header, [&](const CdRequest& request) {
					CdResponse* response = new CdResponse();
					boost::filesystem::path path = workingDirectory;
					path /= request.path;
					if (boost::filesystem::exists(path)
						&& boost::filesystem::is_directory(path))
					{
						workingDirectory = boost::filesystem::canonical(path).string();
					}
					response->path = workingDirectory;
					return shared_ptr<CdResponse>(response);
					});
			}
			else
			{
				logger << "Unknown request" << endl;
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
