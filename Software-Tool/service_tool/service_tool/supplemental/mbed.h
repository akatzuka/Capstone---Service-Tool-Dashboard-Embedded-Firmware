//#include <stdlib.h>
//#include <stdint.h>
//#include <stdio.h>
#include <thread>
#include "TCPServer.h"

#define RAND_MACRO_DIGITAL() rand() % 2;
#define RAND_MACRO_FLOAT() static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
#define RAND_MACRO_USHORT() rand() % sizeof(unsigned short)-1;

#ifndef MBED_H
#define MBED_H

typedef enum {
	PC_2,
	PC_3,
	PC_0,

	/* Inputs */
	PC_14,
	PC_15,
	PD_4,
	PD_5,
	PD_6,
	PD_7,
	PF_0,
	PF_1,
	PE_0,
	PE_1,

	/* OUTPUTS */
	PD_13,
	PD_12,
	PD_11,
	PE_10,
	PE_12,
	PE_14,
	PE_15,
	PE_13,
	PF_13,
	PF_12,

	LED1
} PinName;

typedef struct {
	//
} gpio_t;

class DigitalIn {
public:
	DigitalIn(PinName pin) {
		//
	}
	int read() {
		return RAND_MACRO_DIGITAL();
	}
protected:
	gpio_t gpio;
};

class DigitalOut {
public:
	DigitalOut(PinName pin) {
		//
	}
	void write(int value) {
		//
	}
protected:
	gpio_t gpio;
};

class AnalogIn {
public:
	AnalogIn(PinName pin) {
		//
	}
	float read() {
		return RAND_MACRO_FLOAT();
	}
	unsigned short read_u16(){
		return RAND_MACRO_USHORT();
	}
};

class EthernetInterface {
public:
	EthernetInterface() {
		// constructor
	}
	void connect(void) {
		// connect
	}
};

class SocketAddress {

};


using namespace std;

#endif