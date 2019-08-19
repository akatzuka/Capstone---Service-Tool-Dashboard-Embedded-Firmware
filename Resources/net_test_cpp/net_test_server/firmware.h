/*
 * firmware.h
 * Service Tool Sample Firmware
 * Interphasic LLC
 * Main header for firmware
 */

#ifndef _____Abstr_Firm__
#define _____Abstr_Firm__

#include "F429ZI.h"
 //#include "XL45BX50.h"
#include <vector>
#include <queue>

#define WATCHDOG_Reset() (IWDG->KR = 0xAAAA)

//Mutex stdio_mutex;

/* Variables */
bool dataRequested;
bool newOverrideData;
bool redLEDAlertFlag;
bool newFirmwareFlag;

IOS_Data dataToSend;
O_DATA overrideDataStruct;

std::vector<unsigned char> *firmwareUpdate = NULL;

board_mode debugMode = BOARD_MODE_DEBUG;
//board_mode debugMode = BOARD_MODE_DEFAULT;

bool debugRepeat = false; // false for first time, true if already passed through command loop once, change back to false if state change

// printf message queue
std::queue<char*> t1PrintQueue;
std::queue<char*> t2PrintQueue;

char printBuffer1[100];
char printBuffer2[100];

template<typename... Args>
static inline void printConstructor1(const char* string, Args... args) {
	snprintf(printBuffer1, 100, string, args...);
	t1PrintQueue.push(printBuffer1);
}

template<typename... Args>
static inline void printConstructor2(const char* string, Args... args) {
	snprintf(printBuffer2, 100, string, args...);
	//t2PrintQueue.push(printBuffer2);
	//printf(printBuffer2);
}

static inline void printMessageQueue() {
	//stdio_mutex.lock();
	if (!t1PrintQueue.empty()) {
		printf(t1PrintQueue.front());
		t1PrintQueue.pop();
		///wait(0.1);
	}
	if (!t2PrintQueue.empty()) {
		printf(t2PrintQueue.front());
		t2PrintQueue.pop();
		///wait(0.1);
	}
	//stdio_mutex.unlock();
}

void PRINT_THREAD() {
	while (true) {
		if (debugMode == BOARD_MODE_DEBUG) {
			printMessageQueue();
		}
	}
}

/* I/O Functions */
static inline void readInputs()
{
	for (int i = 0; i < NUCLEO_AIN; i++) {
		*(ain_ram[i]) = 1000 * (analog_input_array[i]->read());
		///wait_us(3.5);
	}

	for (int k = 0; k < NUCLEO_DIN; k++) {
		*(din_ram[k]) = digital_input_array[k]->read();
	}
}

static inline void writeOutputs()
{
	for (int k = 0; k < NUCLEO_DOUT; k++) {
		digital_output_array[k]->write(*(dout_ram[k]));
	}
}

static inline void storeRAMtoStruct() {
	for (int i = 0; i < NUCLEO_DIN; i++) {
		dataToSend.din[i] = *(din_ram[i]);
		dataToSend.dout[i] = *(dout_ram[i]);
	}

	for (int k = 0; k < NUCLEO_AIN; k++) {
		dataToSend.ain[k] = *(ain_ram[k]);
	}
	dataRequested = false;
}

static inline void storeStructToRAM() {
	for (int i = 0; i < NUCLEO_DOUT; i++) {
		*(dout_ram[i]) = overrideDataStruct.dout[i];
	}
	//newOverrideData = false;
}

/* LED THREADS */
void RED_LIGHT_THREAD() {
	while (true) {
		if (redLEDAlertFlag) {
			///led3 = !led3;
			///wait(0.25);
		}
		///else if (!redLEDAlertFlag && led3 == 1) {
			///led3 = !led3;
		///}
	}
}

void GREEN_LIGHT_THREAD() {
	while (true) {
		///led1 = !led1;
		///wait(0.5);
	}
}

#endif

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

	static inline void dummyLogic()
	{

		if (*(ain_ram[0]) > 500.0f) {
			redLEDAlertFlag = true;
		}
		else if (*(ain_ram[1]) > 500.0f) {
			redLEDAlertFlag = true;
		}
		else if (*(ain_ram[2]) > 500.0f) {
			redLEDAlertFlag = true;
		}
		else {
			redLEDAlertFlag = false;
		}

		for (int i = 0; i < NUCLEO_DOUT; i++) {
			*(dout_ram[i]) = *(din_ram[i]);
		}

		/*for (int k = 0; k < 10; k++) {
			printf("%i\n", dout[k]);
		}*/

	}

}