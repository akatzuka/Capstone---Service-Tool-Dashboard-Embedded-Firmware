#define ETH_IP_ADDR "169.254.4.10"
#define SUBNET_ADDR "255.255.0.0"
#define IP_GATEWAY "169.254.4.1"
#define PORT 12000
#define DEFAULT_PORT "12000"
#define MAX_CONN 1
#define BUFFER_SIZE 9

// these are defines for the number of I/O on the Nucleo board
#define NUCLEO_DIN 10
#define NUCLEO_DOUT 10
#define NUCLEO_AIN 3


#define XL45BX50_IN 45
#define XL45BX50_OUT 50

/* ENUMS */
typedef enum {
	NOT_LISTENING,
	TCP_DISCONNECTED,
	TCP_CONNECTED,
	AUTH_CLIENT_CONN,
	WAITING_FOR_COMMANDS,
	TERMINATE_CONNECTION,
	MAX_STATES
} net_state;

typedef enum {
	IDLE,
	LISTENING,
	CLIENT_AUTHORIZING,
	AUTH_FAIL_BAD_CODE,
	AUTH_COMPLETED,
	STANDBY_FOR_ORDERS,
	CLIENT_SHUTDOWN,
	SERVER_SHUTDOWN,
	REQUEST_OBSERVE,
	REQUEST_UPDATE,
	REQUEST_MANUAL,
	REQUEST_LOGS,
	MAX_EVENTS
} net_event;

typedef enum {
	BOARD_MODE_DEFAULT,
	BOARD_MODE_OBSERVE,
	BOARD_MODE_MANUAL,
	BOARD_MODE_UPDATE,
	BOARD_MODE_DEBUG,
	BOARD_MODE_END_OF_MODES
} board_mode;

typedef enum {
	INTERVAL_RATE_10_MS,
	INTERVAL_RATE_100_MS,
	INTERVAL_RATE_200_MS,
	INTERVAL_RATE_500_MS,
	INTERVAL_RATE_1000_MS
} DATA_INTERVAL_RATE;

typedef struct {
	int din[NUCLEO_DIN];
	int dout[NUCLEO_DOUT];

	float ain[NUCLEO_AIN];
} IOS_Data;

typedef struct {
	int dout[NUCLEO_DOUT];
} O_DATA;

/* COMMANDS */
const char CLIENT_AUTH_TCP[] = "auth_tcp";
const char CLIENT_AUTH_FAIL[] = "authfail";
const char CLIENT_AUTH_PASS[] = "authpass";

const char CLIENT_DISCONNECT[] = "clientdi";
const char SERVER_DISCONNECT[] = "servdisc";
const char SERVER_CONFIRM_COM[] = "servconf";
const char SERVER_DENY_COM[] = "servdeny";

const char REQUEST_OBSERVE_COM[] = "req_obsv";
const char REQUEST_MANUAL_COM[] = "req_manu";
const char REQUEST_UPDATE_COM[] = "req_upda";
const char REQUEST_LOGS_COM[] = "req_logs";

const char CANCEL_OBSERVE[] = "can_obsv";
const char CANCEL_MANUAL[] = "can_manu";
const char CANCEL_UPDATE[] = "can_upda";
const char CANCEL_LOGS[] = "can_logs";

namespace Dummy {
	// create static data, verifies integrity of application
	void createStaticFakeData(IOS_Data &dataStruct) {
		dataStruct.din[0] = 1;
		dataStruct.din[1] = 0;
		dataStruct.din[2] = 0;
		dataStruct.din[3] = 0;
		dataStruct.din[4] = 1;
		dataStruct.din[5] = 0;
		dataStruct.din[6] = 1;
		dataStruct.din[7] = 1;
		dataStruct.din[8] = 0;
		dataStruct.din[9] = 1;

		dataStruct.dout[0] = 0;
		dataStruct.dout[1] = 1;
		dataStruct.dout[2] = 1;
		dataStruct.dout[3] = 0;
		dataStruct.dout[4] = 1;
		dataStruct.dout[5] = 1;
		dataStruct.dout[6] = 1;
		dataStruct.dout[7] = 0;
		dataStruct.dout[8] = 1;
		dataStruct.dout[9] = 0;

		dataStruct.ain[0] = 0.5f;
		dataStruct.ain[1] = 0.2f;
		dataStruct.ain[2] = 0.7f;
	}

	void fakeManual1( O_DATA &data ) {
		data.dout[0] = 0;
		data.dout[1] = 0;
		data.dout[2] = 1;
		data.dout[3] = 0;
		data.dout[4] = 1;
		data.dout[5] = 0;
		data.dout[6] = 1;
		data.dout[7] = 0;
		data.dout[8] = 0;
		data.dout[9] = 0;
	}

}