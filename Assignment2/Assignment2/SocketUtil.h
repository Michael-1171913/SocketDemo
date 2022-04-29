#pragma once

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include "Windows.h"
#include "WinSock2.h"
#include "Ws2tcpip.h"
typedef int socklen_t;
//typedef char* receiveBufer_t;
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netdb.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
//typedef void* receiveBufer_t;
typedef int SOCKET;
const int NO_ERROR = 0;
const int INVALID_SOCKET = -1;
const int WSAECONNRESET = ECONNRESET;
const int WSAEWOULDBLOCK = EAGAIN;
const int SOCKET_ERROR = -1;
#endif

#include "UDPSocket.h"
#include "TCPSocket.h"
#include "StringUtils.h"

#include <vector>

enum class SocketAddressFamily
{
	INET = AF_INET,
	INET6 = AF_INET6
};

class SocketUtil
{
public:

	static bool			StaticInit();
	static void			CleanUp();

	static void			ReportError(const char* inOperationDesc);
	static int			GetLastError();

	static int			Select( const std::vector< TCPSocketPtr >* inReadSet,
							    std::vector< TCPSocketPtr >* outReadSet,
							    const std::vector< TCPSocketPtr >* inWriteSet,
							    std::vector< TCPSocketPtr >* outWriteSet,
							    const std::vector< TCPSocketPtr >* inExceptSet,
							    std::vector< TCPSocketPtr >* outExceptSet);

	static UDPSocketPtr	CreateUDPSocket(SocketAddressFamily inFamily);
	static TCPSocketPtr	CreateTCPSocket(SocketAddressFamily inFamily);

private:

	inline static fd_set* FillSetFromVector(fd_set& outSet, const std::vector< TCPSocketPtr >* inSockets, int& ioNaxNfds);
	inline static void FillVectorFromSet(std::vector< TCPSocketPtr >* outSockets, const std::vector< TCPSocketPtr >* inSockets, const fd_set& inSet);
};