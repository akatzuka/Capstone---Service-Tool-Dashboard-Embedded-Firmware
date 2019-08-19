/* 
 * Definitions file for XL45BX50 board.
*/

#ifndef _____XL45BX50__
#define _____XL45BX50__

#include "mbed.h"

#define ETH_IP_ADDR "169.254.4.10"
#define SUBNET_ADDR "255.255.0.0"
#define DEF_GATEWAY "169.254.4.1"
#define ETH_PORT 7401
#define MAX_CONN 1

/* ENUMS */


/* INPUTS */

/* OUTPUTS */

/* PORTS */

/* ETHERNET */

/* TIMERS */


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



/* Some notes here on program flow when waiting for commands from program

(states and flow)
	-disconnected
		-wait for TCP connection
			-verify connection is authentic
			-connected

	-connected and authorized
		-wait for command
			-set observe
			-set update
			-set manual
			-close conn
			-request logs
		
*/

#endif
