#pragma once

#include <stdio.h>
#include <signal.h>
#include "TCPClient.h"

#define DEFAULT_BUFLEN 1024
#define PORT 12000
#define DEFAULT_PORT "12000"
#define LOCALHOST "LOCALHOST"


// these are defines for the number of I/O on the Nucleo board
#define NUCLEO_DIN 10
#define NUCLEO_DOUT 10
#define NUCLEO_AIN 3

/*
 *	These are defines for the client's equipment in development,
 *	useful for testing the software's variability (dynamic code),
 *	to be used at a later date.
 */
#define XL45BX50_IN 45
#define XL45BX50_OUT 50

 // used by the socket wrapper
#define PRINT_LOG [](const std::string& strLogMsg) { std::cout << strLogMsg << std::endl; }

using namespace std;

namespace interphasic {

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

	typedef struct {
		int din[NUCLEO_DIN];
		int dout[NUCLEO_DOUT];

		float ain[NUCLEO_AIN];
	} NUCLEO_DATA;

	// command listing
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

	volatile sig_atomic_t stop; // ctrl + c handler

	void inthand(int signum) {
		stop = 1;
	}

	net_state checkEvents(net_event netEvent) {
		net_state nt;
		switch (netEvent) {
		case IDLE:
			nt = TCP_DISCONNECTED;
			break;
		case LISTENING:
			nt = TCP_DISCONNECTED;
			break;
		case CLIENT_SHUTDOWN:
			nt = TERMINATE_CONNECTION;
			break;
		case AUTH_FAIL_BAD_CODE:
			nt = TERMINATE_CONNECTION;
			break;
		case CLIENT_AUTHORIZING:
			nt = TCP_CONNECTED;
			break;
		case AUTH_COMPLETED:
			nt = WAITING_FOR_COMMANDS;
			break;
		case STANDBY_FOR_ORDERS:
			nt = WAITING_FOR_COMMANDS;
			break;
		}
		return nt;
	}

	bool verifyCommand(const char command[], char buffer[]) {
		if (!strcmp(command, buffer))
			return true;
		return false;
	}

	void printStruct(NUCLEO_DATA dataStruct) {
		for (int i = 0; i < 10; i++) {
			printf("Din %i: %i \n", i, dataStruct.din[i]);
		}

		for (int n = 0; n < 10; n++) {
			printf("Dout %i: %i \n", n, dataStruct.dout[n]);
		}

		for (int k = 0; k < 3; k++)
			printf("Ain %i: %f \n", k, dataStruct.ain[k]);
	}
}
