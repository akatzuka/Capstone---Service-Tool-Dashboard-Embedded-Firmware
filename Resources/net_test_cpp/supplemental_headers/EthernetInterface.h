#include "TCPServer.h"
#include <fstream>

// used by the socket wrapper - remove in embedded
#define PRINT_LOG [](const std::string& strLogMsg) { std::cout << strLogMsg << std::endl; }
#define DEFAULT_PORT "12000"

CTCPServer TCP_Server(PRINT_LOG, DEFAULT_PORT);
ASocket::Socket ConnectedClient;

#define NSAPI_IP_BYTES 16

class NetworkStack;
class EthInterface;
class NetworkInterface;
class OnboardNetworkStack;

enum nsapi_error {
	NSAPI_ERROR_OK = 0,        /*!< no error */
	NSAPI_ERROR_WOULD_BLOCK = -3001,     /*!< no data is not available but call is non-blocking */
	NSAPI_ERROR_UNSUPPORTED = -3002,     /*!< unsupported functionality */
	NSAPI_ERROR_PARAMETER = -3003,     /*!< invalid configuration */
	NSAPI_ERROR_NO_CONNECTION = -3004,     /*!< not connected to a network */
	NSAPI_ERROR_NO_SOCKET = -3005,     /*!< socket not available for use */
	NSAPI_ERROR_NO_ADDRESS = -3006,     /*!< IP address is not known */
	NSAPI_ERROR_NO_MEMORY = -3007,     /*!< memory resource not available */
	NSAPI_ERROR_NO_SSID = -3008,     /*!< ssid not found */
	NSAPI_ERROR_DNS_FAILURE = -3009,     /*!< DNS failed to complete successfully */
	NSAPI_ERROR_DHCP_FAILURE = -3010,     /*!< DHCP failed to complete successfully */
	NSAPI_ERROR_AUTH_FAILURE = -3011,     /*!< connection to access point failed */
	NSAPI_ERROR_DEVICE_ERROR = -3012,     /*!< failure interfacing with the network processor */
	NSAPI_ERROR_IN_PROGRESS = -3013,     /*!< operation (eg connect) in progress */
	NSAPI_ERROR_ALREADY = -3014,     /*!< operation (eg connect) already in progress */
	NSAPI_ERROR_IS_CONNECTED = -3015,     /*!< socket is already connected */
	NSAPI_ERROR_CONNECTION_LOST = -3016,     /*!< connection lost */
	NSAPI_ERROR_CONNECTION_TIMEOUT = -3017,     /*!< connection timed out */
	NSAPI_ERROR_ADDRESS_IN_USE = -3018,     /*!< Address already in use */
	NSAPI_ERROR_TIMEOUT = -3019,     /*!< operation timed out */
};

typedef enum nsapi_connection_status {
	NSAPI_STATUS_LOCAL_UP = 0,        /*!< local IP address set */
	NSAPI_STATUS_GLOBAL_UP = 1,        /*!< global IP address set */
	NSAPI_STATUS_DISCONNECTED = 2,        /*!< no connection to network */
	NSAPI_STATUS_CONNECTING = 3,        /*!< connecting to network */
	NSAPI_STATUS_ERROR_UNSUPPORTED = NSAPI_ERROR_UNSUPPORTED
} nsapi_connection_status_t;

typedef enum nsapi_event {
	NSAPI_EVENT_CONNECTION_STATUS_CHANGE = 0, /*!< network connection status has changed, the parameter = new status (nsapi_connection_status_t) */
	NSAPI_EVENT_CELLULAR_STATUS_BASE = 0x1000,  /*!< Cellular modem status has changed, See the enum values from enum cellular_connection_status_t in /features/cellular/framework/common/CellularCommon.h */
	NSAPI_EVENT_CELLULAR_STATUS_END = 0x1FFF   /*!< cellular modem status has changed, See the enum values from enum cellular_connection_status_t in /features/cellular/framework/common/CellularCommon.h */
} nsapi_event_t;

typedef signed int nsapi_error_t;

typedef unsigned int nsapi_size_t;

typedef signed int nsapi_size_or_error_t;

typedef signed int nsapi_value_or_error_t;

typedef void *nsapi_socket_t;

typedef enum nsapi_protocol {
	NSAPI_TCP, /*!< Socket is of TCP type */
	NSAPI_UDP, /*!< Socket is of UDP type */
} nsapi_protocol_t;

typedef enum nsapi_version {
	NSAPI_UNSPEC,   /*!< Address is unspecified */
	NSAPI_IPv4,     /*!< Address is IPv4 */
	NSAPI_IPv6,     /*!< Address is IPv6 */
} nsapi_version_t;

typedef struct nsapi_addr {
	/** IP version
	 *  - NSAPI_IPv4
	 *  - NSAPI_IPv6
	 *  - NSAPI_UNSPEC
	 */
	nsapi_version_t version;

	/** IP address
	 *  The raw bytes of the IP address stored in big-endian format
	 */
	uint8_t bytes[NSAPI_IP_BYTES];
} nsapi_addr_t;

typedef struct nsapi_stack {
	const struct nsapi_stack_api *stack_api;

	void *stack;

	// Internal nsapi buffer
	unsigned _stack_buffer[16];
} nsapi_stack_t;

typedef enum nsapi_ip_stack {
	DEFAULT_STACK = 0,
	IPV4_STACK,
	IPV6_STACK,
	IPV4V6_STACK
} nsapi_ip_stack_t;

class SocketAddress {
public:

	SocketAddress(nsapi_addr_t addr = nsapi_addr_t(), uint16_t port = 0) {}

	SocketAddress(const char *addr, uint16_t port = 0) {}

	SocketAddress(const void *bytes, nsapi_version_t version, uint16_t port = 0) {}

	SocketAddress(const SocketAddress &addr) {}

	/** Destructor */
	~SocketAddress() {}

	bool set_ip_address(const char *addr) {}

	void set_ip_bytes(const void *bytes, nsapi_version_t version) {}

	void set_addr(nsapi_addr_t addr) {}

	void set_port(uint16_t port) {}

	const char *get_ip_address() const {
		return "192.168.0.20";
	}

	const void *get_ip_bytes() const {}

	nsapi_version_t get_ip_version() const {}

	nsapi_addr_t get_addr() const {
		return nsapi_addr_t();
	}

	uint16_t get_port() const {
		return 12000;
	}

	operator bool() const {}

	SocketAddress &operator=(const SocketAddress &addr) {}

	friend bool operator==(const SocketAddress &a, const SocketAddress &b) {}

	friend bool operator!=(const SocketAddress &a, const SocketAddress &b) {}

private:
	void _SocketAddress(NetworkStack *iface, const char *host, uint16_t port) {}

	mutable char *_ip_address;
	nsapi_addr_t _addr;
	uint16_t _port;
};

class DNS {
public:
	virtual nsapi_error_t gethostbyname(const char *host, SocketAddress *address, nsapi_version_t version = NSAPI_UNSPEC) = 0;
};

class NetworkInterface: public DNS {
public:

	virtual ~NetworkInterface() {};

	static NetworkInterface *get_default_instance() {}

	virtual const char *get_mac_address() { return "0"; }

	virtual const char *get_ip_address() { return "0"; }

	virtual const char *get_netmask() { return "0"; }

	virtual const char *get_gateway() { return "0"; }

	virtual nsapi_error_t set_network(const char *ip_address, const char *netmask, const char *gateway) { return 0; }

	virtual nsapi_error_t set_dhcp(bool dhcp) { return 0; }

	virtual nsapi_error_t connect() = 0;

	virtual nsapi_error_t disconnect() = 0;

	virtual nsapi_error_t gethostbyname(const char *host, SocketAddress *address, nsapi_version_t version = NSAPI_UNSPEC) { return 0; }

	virtual nsapi_error_t set_blocking(bool blocking) { return 0; }

	/** Dynamic downcast to an EthInterface */
	virtual EthInterface *ethInterface()
	{
		return 0;
	}

protected:
	friend class InternetSocket;
	friend class UDPSocket;
	friend class TCPSocket;
	friend class TCPServer;
	friend class SocketAddress;
	//template <typename IF>
	//friend NetworkStack *nsapi_create_stack(IF *iface);

	virtual NetworkStack *get_stack() = 0;
};

class EMAC {
public:
	static EMAC &get_default_instance();

	//virtual uint32_t get_mtu_size() const = 0;

	//virtual uint32_t get_align_preference() const = 0;

	//virtual void get_ifname(char *name, uint8_t size) const = 0;

	//virtual uint8_t get_hwaddr_size() const = 0;

	//virtual bool get_hwaddr(uint8_t *addr) const = 0;

	//virtual void set_hwaddr(const uint8_t *addr) = 0;
};

class DOOT : public EMAC {
public:
	static DOOT &get_instance() {
		static DOOT emac;
		return emac;
	}
};

EMAC & EMAC::get_default_instance()
{
	return DOOT::get_instance();
}

class EthInterface : public virtual NetworkInterface {
public:

	virtual EthInterface *ethInterface()
	{
		return this;
	}

	static EthInterface *get_default_instance() {}

protected:
	static EthInterface *get_target_default_instance() {}
};

class NetworkStack : public DNS {
public:
	virtual ~NetworkStack() {};

	virtual const char *get_ip_address() { return "0"; }

	//virtual nsapi_error_t gethostbyname(const char *host, SocketAddress *address, nsapi_version_t version = NSAPI_UNSPEC);

	//virtual nsapi_value_or_error_t gethostbyname_async(const char *host, hostbyname_cb_t callback, nsapi_version_t version = NSAPI_UNSPEC);

protected:
	friend class InternetSocket;
	friend class UDPSocket;
	friend class TCPSocket;
	friend class TCPServer;

	virtual nsapi_error_t socket_open(nsapi_socket_t *handle, nsapi_protocol_t proto) = 0;

	virtual nsapi_error_t socket_close(nsapi_socket_t handle) = 0;

	virtual nsapi_error_t socket_bind(nsapi_socket_t handle, const SocketAddress &address) = 0;

	virtual nsapi_error_t socket_listen(nsapi_socket_t handle, int backlog) = 0;

	virtual nsapi_error_t socket_connect(nsapi_socket_t handle, const SocketAddress &address) = 0;

	virtual nsapi_error_t socket_accept(nsapi_socket_t server,
		nsapi_socket_t *handle, SocketAddress *address = 0) = 0;

	virtual nsapi_size_or_error_t socket_send(nsapi_socket_t handle,
		const void *data, nsapi_size_t size) = 0;

	virtual nsapi_size_or_error_t socket_recv(nsapi_socket_t handle,
		void *data, nsapi_size_t size) = 0;

	virtual void socket_attach(nsapi_socket_t handle, void(*callback)(void *), void *data) = 0;

	virtual nsapi_error_t setsockopt(nsapi_socket_t handle, int level,
		int optname, const void *optval, unsigned optlen) { return 0;}

	virtual nsapi_error_t getsockopt(nsapi_socket_t handle, int level,
		int optname, void *optval, unsigned *optlen) {
		return 0;
	}
};

class OnboardNetworkStack : public NetworkStack {
public:
	
	static OnboardNetworkStack &get_default_instance();

	class Interface {
	public:
		virtual ~Interface() {}

		//virtual nsapi_error_t bringup(bool dhcp, const char *ip,const char *netmask, const char *gw,nsapi_ip_stack_t stack = DEFAULT_STACK,bool blocking = true) = 0;

		//virtual nsapi_error_t bringdown() = 0;

		//virtual nsapi_connection_status_t get_connection_status() const = 0;

		//virtual char *get_mac_address(char *buf, nsapi_size_t buflen) = 0;

		//virtual char *get_ip_address(char *buf, nsapi_size_t buflen) = 0;

		//virtual char *get_netmask(char *buf, nsapi_size_t buflen) = 0;

		//virtual char *get_gateway(char *buf, nsapi_size_t buflen) = 0;
	};

	//virtual nsapi_error_t add_ethernet_interface(EMAC &emac, bool default_if, Interface **interface_out) = 0;
};

class LWIP : public OnboardNetworkStack {
public:

	static LWIP &get_instance();

	virtual nsapi_error_t gethostbyname(const char *host, SocketAddress *address, nsapi_version_t version = NSAPI_UNSPEC) { return 0; }

	class Interface : public OnboardNetworkStack::Interface {
	public:
		virtual nsapi_error_t bringup(bool dhcp, const char *ip,
			const char *netmask, const char *gw,
			nsapi_ip_stack_t stack = DEFAULT_STACK,
			bool blocking = true
		) {
			return 0;
		}

	private:
		friend LWIP;

		Interface();

	};

protected:
	LWIP() {}
	virtual ~LWIP() {}

	virtual nsapi_error_t socket_open(nsapi_socket_t *handle, nsapi_protocol_t proto) { return 0; }

	virtual nsapi_error_t socket_close(nsapi_socket_t handle) { return 0; }

	virtual nsapi_error_t socket_bind(nsapi_socket_t handle, const SocketAddress &address) { return 0; }

	virtual nsapi_error_t socket_listen(nsapi_socket_t handle, int backlog) { return 0; }

	virtual nsapi_error_t socket_connect(nsapi_socket_t handle, const SocketAddress &address) { return 0; }

	virtual nsapi_error_t socket_accept(nsapi_socket_t server,
		nsapi_socket_t *handle, SocketAddress *address = 0) {
		return 0;
	}

	virtual nsapi_size_or_error_t socket_send(nsapi_socket_t handle,
		const void *data, nsapi_size_t size) {
		return 0;
	}

	virtual nsapi_size_or_error_t socket_recv(nsapi_socket_t handle,
		void *data, nsapi_size_t size) {
		return 0;
	}

	virtual nsapi_size_or_error_t socket_sendto(nsapi_socket_t handle, const SocketAddress &address,
		const void *data, nsapi_size_t size) {
		return 0;
	}

	virtual nsapi_size_or_error_t socket_recvfrom(nsapi_socket_t handle, SocketAddress *address,
		void *buffer, nsapi_size_t size) {
		return 0;
	}

	virtual void socket_attach(nsapi_socket_t handle, void(*callback)(void *), void *data) {}

	virtual nsapi_error_t setsockopt(nsapi_socket_t handle, int level,
		int optname, const void *optval, unsigned optlen) {
		return 0;
	}

	virtual nsapi_error_t getsockopt(nsapi_socket_t handle, int level,
		int optname, void *optval, unsigned *optlen) {
		return 0;
	}
private:

};

OnboardNetworkStack & OnboardNetworkStack::get_default_instance()
{
	return LWIP::get_instance();
}

LWIP &LWIP::get_instance() {
	static LWIP lwip;
	return lwip;
}

class EMACInterface : public virtual NetworkInterface {
public:
	//_blocking(true)
	EMACInterface(EMAC &emac, OnboardNetworkStack &stack) :
		_emac(emac),
		_stack(stack),
		_interface(NULL),
		_dhcp(true)
		
	{
	}

	virtual nsapi_error_t set_network(const char *ip_address, const char *netmask, const char *gateway) { return 0; }

	virtual nsapi_error_t set_dhcp(bool dhcp) { return 0; }

	virtual nsapi_error_t connect() { return 0; }

	virtual nsapi_error_t disconnect() { return 0; }

	virtual const char *get_mac_address() { return "0"; }

	virtual const char *get_ip_address() { return "0"; }

	virtual const char *get_netmask() { return "0"; }

	virtual const char *get_gateway() { return "0"; }

	virtual nsapi_connection_status_t get_connection_status() const { return NSAPI_STATUS_LOCAL_UP; }

	virtual nsapi_error_t set_blocking(bool blocking) { return 0; }

	EMAC &get_emac() const
	{
		return _emac;
	}

	virtual EMACInterface *emacInterface()
	{
		return this;
	}

protected:
	/** Provide access to the underlying stack
	 *
	 *  @return The underlying network stack
	 */
	virtual NetworkStack *get_stack() { return &_stack; }

	EMAC &_emac;
	OnboardNetworkStack &_stack;
	OnboardNetworkStack::Interface *_interface;
	bool _dhcp;
	bool _blocking;
};

class EthernetInterface : public EMACInterface, public EthInterface {
public:
	EthernetInterface(EMAC &emac = EMAC::get_default_instance(), OnboardNetworkStack &stack = OnboardNetworkStack::get_default_instance()) : EMACInterface(emac, stack) { }
};

class Socket {
public:
	
	virtual ~Socket() {}

	virtual nsapi_error_t close() = 0;

	virtual nsapi_error_t connect(const SocketAddress &address) = 0;

	virtual nsapi_size_or_error_t send(const void *data, nsapi_size_t size) = 0;

	virtual nsapi_size_or_error_t recv(void *data, nsapi_size_t size) = 0;

	virtual nsapi_error_t bind(const SocketAddress &address) = 0;

	virtual void set_blocking(bool blocking) = 0;

	virtual void set_timeout(int timeout) = 0;

	virtual nsapi_error_t setsockopt(int level, int optname, const void *optval, unsigned optlen) = 0;

	virtual nsapi_error_t getsockopt(int level, int optname, void *optval, unsigned *optlen) = 0;

	virtual Socket *accept(nsapi_error_t *error = NULL) = 0;

	virtual nsapi_error_t listen(int backlog = 1) = 0;
};

class InternetSocket : public Socket {
public:
	
	virtual ~InternetSocket() {}

	nsapi_error_t open(NetworkStack *stack) { return 0; }

	template <typename S>
	nsapi_error_t open(S *stack)
	{
		return 0;
	}

	virtual nsapi_error_t close() {
		int error = TCP_Server.Disconnect(ConnectedClient);
		return error;
	}

	nsapi_error_t bind(uint16_t port) {}

	nsapi_error_t bind(const char *address, uint16_t port) {
		
		return 0;
	}

	virtual nsapi_error_t bind(const SocketAddress &address) {
		return 0;
	}

	virtual void set_blocking(bool blocking) {}

	virtual void set_timeout(int timeout) {}

	virtual nsapi_error_t setsockopt(int level, int optname, const void *optval, unsigned optlen) { 
		return 0;
	}

	virtual nsapi_error_t getsockopt(int level, int optname, void *optval, unsigned *optlen) {
		return 0;
	}

protected:
	InternetSocket() {}
};

class TCPSocket : public InternetSocket {
public:
	
	TCPSocket() {
		// constructor
	}

	virtual ~TCPSocket() {}

	nsapi_error_t connect(const char *host, uint16_t port) {}
	
	virtual nsapi_error_t connect(const SocketAddress &address) { return 0; }
	
	virtual nsapi_size_or_error_t send(const void *data, nsapi_size_t size) { 
		int error = TCP_Server.Send(ConnectedClient, (const char*)data, (const size_t)size);
		return error; 
	}

	virtual nsapi_size_or_error_t recv(void *data, nsapi_size_t size) {
		int error = TCP_Server.Recv(ConnectedClient, (char*)data, size);
		return error;
	}

	virtual TCPSocket *accept(nsapi_error_t *error = NULL);

	virtual nsapi_error_t listen(int backlog = 1) {
		int error = TCP_Server.Listen();
		return error;
	}

protected:
	friend class TCPServer;
	//virtual nsapi_protocol_t get_proto();
};

TCPSocket *TCPSocket::accept(nsapi_error_t *error) {
	TCPSocket *connection = new TCPSocket();
	return connection;
}

class TCPServer : public TCPSocket {
public:
		TCPServer() {}

		virtual ~TCPServer() {}

		// Allow legacy TCPServer::accept() to override inherited Socket::accept()
		using TCPSocket::accept;

		nsapi_error_t accept(TCPSocket *connection, SocketAddress *address = NULL) {
			int error = TCP_Server.Accept(ConnectedClient);
			return error;
		}
};
