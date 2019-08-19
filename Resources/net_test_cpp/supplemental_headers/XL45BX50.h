/*
 * Definitions file for XL45BX50 board.
*/

#ifndef _____XL45BX50__
#define _____XL45BX50__

#define MAX_CONN 1

/*
 *	These are defines for the client's equipment in development,
 *	useful for testing the software's variability (dynamic code),
 *	to be used at a later date.
 */
#define XL45BX50_IN 45
#define XL45BX50_OUT 50

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


#endif
