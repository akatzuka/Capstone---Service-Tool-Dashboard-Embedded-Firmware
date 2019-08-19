/*
 * Definitions file for F429ZI board.
*/

#ifndef _____F429ZI__
#define _____F429ZI__

#include "mbed.h"
#include "EthernetInterface.h"

/* Networking Constants */
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

/**
 * Watchdog timeout settings
 */
typedef enum {
	WATCHDOG_Timeout_5ms = 0x00,   /*!< System reset called every 5ms */
	WATCHDOG_Timeout_10ms = 0x01,  /*!< System reset called every 10ms */
	WATCHDOG_Timeout_15ms = 0x02,  /*!< System reset called every 15ms */
	WATCHDOG_Timeout_30ms = 0x03,  /*!< System reset called every 30ms */
	WATCHDOG_Timeout_60ms = 0x04,  /*!< System reset called every 60ms */
	WATCHDOG_Timeout_120ms = 0x05, /*!< System reset called every 120ms */
	WATCHDOG_Timeout_250ms = 0x06, /*!< System reset called every 250ms */
	WATCHDOG_Timeout_500ms = 0x07, /*!< System reset called every 500ms */
	WATCHDOG_Timeout_1s = 0x08,    /*!< System reset called every 1s */
	WATCHDOG_Timeout_2s = 0x09,    /*!< System reset called every 2s */
	WATCHDOG_Timeout_4s = 0x0A, /*!< System reset called every 4s */
	WATCHDOG_Timeout_8s = 0x0B,    /*!< System reset called every 8s */
	WATCHDOG_Timeout_16s = 0x0C,   /*!< System reset called every 16s */
	WATCHDOG_Timeout_32s = 0x0D /*!< System reset called every 32s. This is maximum value allowed with IWDG timer */
} WATCHDOG_Timeout_t;

/* STRUCTS */
typedef struct {
	int din[NUCLEO_DIN];
	int dout[NUCLEO_DOUT];

	float ain[NUCLEO_AIN];
} IOS_Data;

typedef struct {
	int dout[NUCLEO_DOUT];
} O_DATA;

/* INPUTS */
AnalogIn *analog_input_array[NUCLEO_AIN];

DigitalIn *digital_input_array[NUCLEO_DIN];

/* OUTPUTS */
DigitalOut *digital_output_array[NUCLEO_DOUT];
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);

/* MEMORY IN */
float *ain_ram[NUCLEO_AIN];

int *din_ram[NUCLEO_DIN];

/* MEMORY OUT */
int *dout_ram[NUCLEO_DOUT];

/* PORTS */
//Serial pc(USBTX, USBRX); // serial printf for debug

/* ETHERNET */
EthernetInterface *eth = NULL;

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

/* FUNCTIONS */
void init() {
	/* INPUTS */
	analog_input_array[0] = new AnalogIn(PC_2);
	analog_input_array[1] = new AnalogIn(PC_3);
	analog_input_array[2] = new AnalogIn(PC_0);

	digital_input_array[0] = new DigitalIn(PC_14);
	digital_input_array[1] = new DigitalIn(PC_15);
	digital_input_array[2] = new DigitalIn(PD_4);
	digital_input_array[3] = new DigitalIn(PD_5);
	digital_input_array[4] = new DigitalIn(PD_6);
	digital_input_array[5] = new DigitalIn(PD_7);
	digital_input_array[6] = new DigitalIn(PF_1);
	digital_input_array[7] = new DigitalIn(PF_0);
	digital_input_array[8] = new DigitalIn(PG_0);
	digital_input_array[9] = new DigitalIn(PE_1);

	/* OUTPUTS */
	digital_output_array[0] = new DigitalOut(PD_13);
	digital_output_array[1] = new DigitalOut(PD_12);
	digital_output_array[2] = new DigitalOut(PD_11);
	digital_output_array[3] = new DigitalOut(PE_10);
	digital_output_array[4] = new DigitalOut(PE_12);
	digital_output_array[5] = new DigitalOut(PE_14);
	digital_output_array[6] = new DigitalOut(PE_15);
	digital_output_array[7] = new DigitalOut(PE_13);
	digital_output_array[8] = new DigitalOut(PF_13);
	digital_output_array[9] = new DigitalOut(PF_12);

	/* SENSORS */


	/* DIGITAL MEMORY */
	for (int i = 0; i < NUCLEO_DIN; i++) {
		din_ram[i] = new int;
		*(din_ram[i]) = 0;

		dout_ram[i] = new int;
		*(dout_ram[i]) = 0;
	}

	/* ANALOG MEMORY */
	for (int k = 0; k < NUCLEO_AIN; k++) {
		ain_ram[k] = new float;
		*(ain_ram[k]) = 0;
	}

	/* Ethernet Port */
	eth = new EthernetInterface();
}

/**
 * Initialize Watchdog timer
 *
 * Parameters:
 *    - WATCHDOG_Timeout_t timeout:
 *        Select time when watchdog reset accur if Watchdog timer is not reset before
 *
 * Returns 1 if system was reset by Watchdog, otherwise 0
 */
 uint8_t WATCHDOG_Init(WATCHDOG_Timeout_t timeout)
 {
	 uint8_t result = 0;
	 uint16_t reload = 0;

	 /* Check if the system has resumed from IWDG reset */
	 if (RCC->CSR & RCC_CSR_WDGRSTF) {
		 /* Reset by IWDG */
		 result = 1;

		 /* Clear reset flags */
		 RCC->CSR |= RCC_CSR_RMVF;
	 }

	 /* Enable write access to IWDG_PR and IWDG_RLR registers */
	 IWDG->KR = 0x5555;

	 /* Set proper clock depending on timeout user select */
	 if (timeout >= WATCHDOG_Timeout_8s) {
		 /* IWDG counter clock: LSI/256 = 128Hz */
		 IWDG->PR = 0x07;
	 }
	 else {
		 /* IWDG counter clock: LSI/32 = 1024Hz */
		 IWDG->PR = 0x03;
	 }

	 /* Set counter reload value */
	 switch (timeout) {
	 case WATCHDOG_Timeout_5ms:
		 reload = 5; /* 1024 Hz IWDG ticking */
	 case WATCHDOG_Timeout_10ms:
		 reload = 10; /* 1024 Hz IWDG ticking */
	 case WATCHDOG_Timeout_15ms:
		 reload = 15; /* 1024 Hz IWDG ticking */
	 case WATCHDOG_Timeout_30ms:
		 reload = 31; /* 1024 Hz IWDG ticking */
	 case WATCHDOG_Timeout_60ms:
		 reload = 61; /* 1024 Hz IWDG ticking */
	 case WATCHDOG_Timeout_120ms:
		 reload = 123; /* 1024 Hz IWDG ticking */
	 case WATCHDOG_Timeout_250ms:
		 reload = 255; /* 1024 Hz IWDG ticking */
	 case WATCHDOG_Timeout_500ms:
		 reload = 511; /* 1024 Hz IWDG ticking */
	 case WATCHDOG_Timeout_1s:
		 reload = 1023; /* 1024 Hz IWDG ticking */
	 case WATCHDOG_Timeout_2s:
		 reload = 2047; /* 1024 Hz IWDG ticking */
	 case WATCHDOG_Timeout_4s:
		 reload = 4095; /* 1024 Hz IWDG ticking */
	 case WATCHDOG_Timeout_8s:
		 reload = 1023; /* 128 Hz IWDG ticking */
	 case WATCHDOG_Timeout_16s:
		 reload = 2047; /* 128 Hz IWDG ticking */
	 case WATCHDOG_Timeout_32s:
		 reload = 4095; /* 128 Hz IWDG ticking */
	 }

	 /* Set reload */
	 IWDG->RLR = reload;

	 /* Reload IWDG counter */
	 IWDG->KR = 0xAAAA;

	 /* Enable IWDG (the LSI oscillator will be enabled by hardware) */
	 IWDG->KR = 0xCCCC;

	 /* Return status */
	 return result;
 }

 void initWatchDog(void)
 {
	 WATCHDOG_Init(WATCHDOG_Timeout_1s);
 }

#endif