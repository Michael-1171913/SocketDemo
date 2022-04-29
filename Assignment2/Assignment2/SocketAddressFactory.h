#pragma once

#include <string>
#include <WinSock2.h>

#include "Ws2tcpip.h"

#include "SocketAddress.h"
#include "SocketUtil.h"

class SocketAddressFactory
{
public:

	static SocketAddressPtr CreateIPv4FromString(const std::string& inString);
};