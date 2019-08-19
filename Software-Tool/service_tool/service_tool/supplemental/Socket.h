/*
* @file Socket.h
* @brief Abstract class to perform API global operations
*
* @author Mohamed Amine Mzoughi <mohamed-amine.mzoughi@laposte.net>
* @date 2017-02-10
*/

#define WINDOWS _WIN32

#ifndef INCLUDE_ASOCKET_H_
#define INCLUDE_ASOCKET_H_

#include <cstdio>         // snprintf
#include <exception>
#include <functional>
#include <memory>
#include <stdarg.h>       // va_start, etc.
#include <stdexcept>

#ifdef WINDOWS
#define WIN32_LEAN_AND_MEAN

#ifndef WINSOCK
#define WINSOCK
#include <winsock2.h>
#include <ws2tcpip.h>
#endif

#pragma comment(lib, "Ws2_32.lib")

#ifdef _M_CEE 
#	undef _M_CEE 
#	include <thread> 
#	include <mutex> 
#	define _M_CEE 001 
#else 
#	include <thread> 
#	include <mutex> 
#endif 
#pragma managed(pop)

// Need to link with Ws2_32.lib
#pragma comment(lib,"WS2_32.lib")

#else
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

#include <limits>
#define ACCEPT_WAIT_INF_DELAY std::numeric_limits<size_t>::max()

using namespace std;

class ASocket
{
public:
	// Public definitions
	//typedef std::function<int(void*, double, double, double, double)> ProgressFnCallback;
	typedef std::function<void(const std::string&)>                   LogFnCallback;

	// socket file descriptor id
#ifdef WINDOWS
	typedef SOCKET Socket;
#else
	typedef int Socket;
#define INVALID_SOCKET -1
#endif

	enum SettingsFlag
	{
		NO_FLAGS = 0x00,
		ENABLE_LOG = 0x01,
		ALL_FLAGS = 0xFF
	};

	/* Please provide your logger thread-safe routine, otherwise, you can turn off
	* error log messages printing by not using the flag ALL_FLAGS or ENABLE_LOG */
	explicit ASocket(const LogFnCallback& oLogger,
		const SettingsFlag eSettings = ALL_FLAGS);
	virtual ~ASocket() = 0;

	inline static int GetSocketCount() { return s_iSocketCount; }

	static int SelectSockets(const Socket* pSocketsToSelect, const size_t count,
		const size_t msec, size_t& selectedIndex);

	int SelectSocket(const Socket sd, const size_t msec);

protected:
	// String Helpers
	static std::string StringFormat(const std::string strFormat, ...);

	// Log printer callback
	/*mutable*/const LogFnCallback         m_oLog;

	SettingsFlag         m_eSettingsFlags;

#ifdef WINDOWS
	static WSADATA s_wsaData;
#endif

public:
	void mtx();

private:
	volatile static int   s_iSocketCount;  // Count of the actual socket sessions
	//static std::mutex     s_mtxCount;      // mutex used to sync API global operations
	struct Mtx;
	std::unique_ptr<Mtx> s_mtxCount;
};

class EResolveError : public std::logic_error
{
public:
	explicit EResolveError(const std::string &strMsg) : std::logic_error(strMsg) {}
};

#endif