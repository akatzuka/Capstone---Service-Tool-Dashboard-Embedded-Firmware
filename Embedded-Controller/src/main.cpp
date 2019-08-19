// main loop and helper functions

#include "firmware.h"

net_state socketState = TCP_DISCONNECTED; // beginning state
net_event socketEvent = LISTENING; // beginning event (none)
board_mode curBoardMode = BOARD_MODE_DEFAULT;

TCPServer srv;
TCPSocket clt_sock;
SocketAddress clt_addr;

net_state checkEvents(net_event netevent);
void printStruct(void);
bool verifyCommand(const char[], char[]);
static inline void recvCMD(void);

/* SM FUNCTIONS */
static inline void Authorize(void);
static inline void Observe(void);
static inline void Manual(void);
static inline void Update(void);
static inline void Stop_Manual(void);

void TCP_Server_Thread(void const *args);

int main() {
	//perform setup
	init();
	
	/*board.initEthInterface();
	board.setIP();
	board.server_init_tcp();
	board.server_apply_settings();*/

	if (debugMode == BOARD_MODE_DEBUG) {
		printConstructor1("Start Network Thread\n");
	}
	Thread netThread(TCP_Server_Thread);

	if (debugMode == BOARD_MODE_DEBUG) {
		printConstructor1("Start LED threads");
	}
	Thread led_thread1(GREEN_LIGHT_THREAD);
	Thread led_thread2(RED_LIGHT_THREAD);

	
	//Thread pt(PRINT_THREAD);

	if (debugMode == BOARD_MODE_DEBUG) {
		printConstructor1("Start Loop\n");
	}
	while (1) {
		// infinite lööp
		
		// Read all Inputs
		readInputs();

		// Perform Control Logic
		Dummy::dummyLogic();

		// Check faults


		// copy new struct data to RAM
		if (newOverrideData) {
			storeStructToRAM();
		}
		// copy ram to struct when needed
		if (dataRequested) {
			storeRAMtoStruct();
		}

		// Set Outputs
		writeOutputs();
		
		//WATCHDOG_Reset();
	}
}

void TCP_Server_Thread(void const *args) {
	if (debugMode == BOARD_MODE_DEBUG) {
		printConstructor2("Basic TCP server example\r\n");
	}

	eth->connect();

	if (debugMode == BOARD_MODE_DEBUG) {
		printf("The target IP address is '%s'\r\n", eth->get_ip_address());
	}
	
	/* Open the server on ethernet stack */
	srv.open(eth);

	/* Bind the HTTP port (TCP 80) to the server */
	srv.bind(eth->get_ip_address(), PORT);


	srv.set_blocking(false);
	while (true) {
		if (debugMode == BOARD_MODE_DEBUG) {
			printConstructor2("waiting for client\r\n");
		}
		/* Can handle 5 simultaneous connections */
		signed int err = srv.listen(1);
		if (debugMode == BOARD_MODE_DEBUG) {
			printConstructor2("server listening error : %d\r\n", err);
		}

		while (1)
		{
			socketState = checkEvents(socketEvent);
			switch (socketState)
			{
				case TCP_DISCONNECTED:
				{
					if (debugMode == BOARD_MODE_DEBUG) {
						if (debugRepeat == false) {
							printConstructor2("waiting for connection\n");
						}
					}
					err = srv.accept(&clt_sock, &clt_addr);
					// accept client connection
					if (err == 0) {
						socketEvent = CLIENT_AUTHORIZING; // proceed to authorize with server
						if (debugMode == BOARD_MODE_DEBUG) {
							printConstructor2("client connected :%s:%d\r\n", clt_addr.get_ip_address(), clt_addr.get_port());
						}
					}
					else if (err < 0)
					{
						if (debugMode == BOARD_MODE_DEBUG) {
							if (debugRepeat == false) {
								//printConstructor2((signed char)err + "\n");
							}
						}
					}

					if (debugMode == BOARD_MODE_DEBUG) {
						if (socketEvent == LISTENING) {
							debugRepeat = true;
						}
						else {
							debugRepeat = false;
						}
					}
				}
				break;
				case TCP_CONNECTED:
				{
					Authorize();
					break;
				}
				case WAITING_FOR_COMMANDS:
				{
					if (debugMode == BOARD_MODE_DEBUG) {
						if (debugRepeat == false) {
							printConstructor2("waiting to recieve commands\n");
						}
					}

					recvCMD();

					switch (curBoardMode)
					{
						case BOARD_MODE_OBSERVE:
						{
							Observe();
							break;
						}
						case BOARD_MODE_MANUAL:
						{
							Manual();
							break;
						}
						case BOARD_MODE_UPDATE:
						{
							Update();
							break;
						}
						default: BOARD_MODE_DEFAULT;
							break;
					}
					if (debugMode == BOARD_MODE_DEBUG) {
						if (socketEvent == (AUTH_COMPLETED || STANDBY_FOR_ORDERS)) {
							debugRepeat = true;
						}
						else {
							debugRepeat = false;
						}
					}
				}
				break;
				case TERMINATE_CONNECTION:
				{
					if (debugMode == BOARD_MODE_DEBUG) {
						printConstructor2("terminating connection with client\n");
					}
					clt_sock.close();
					socketEvent = LISTENING;
				}
				break;
				case NOT_LISTENING:
				{
					//do nothing
				}
			}
		}
	}
}

static inline void recvCMD() {
	// receive a command
	char szRcvBuffer[BUFFER_SIZE] = {};
	clt_sock.recv(szRcvBuffer, BUFFER_SIZE);

	if (!strcmp(REQUEST_OBSERVE_COM, szRcvBuffer))
	{
		curBoardMode = BOARD_MODE_OBSERVE;
	}
	else if (!strcmp(REQUEST_MANUAL_COM, szRcvBuffer))
	{
		curBoardMode = BOARD_MODE_MANUAL;
	}
	else if (!strcmp(REQUEST_UPDATE_COM, szRcvBuffer))
	{
		curBoardMode = BOARD_MODE_UPDATE;
	}
	else if (!strcmp(CLIENT_DISCONNECT, szRcvBuffer))
	{
		socketEvent = CLIENT_SHUTDOWN;
	}
	else if (!strcmp(REQUEST_LOGS_COM, szRcvBuffer))
	{
		// TODO: Implement
	}
	else if (!strcmp(CANCEL_MANUAL, szRcvBuffer))
	{
		Stop_Manual();
	}
}

static inline void Authorize() {
	if (debugMode == BOARD_MODE_DEBUG) {
		printConstructor2("starting authentication\n");
	}
	// client connected, start auth
	char szRcvBuffer[BUFFER_SIZE] = {};
	clt_sock.recv(szRcvBuffer, sizeof(CLIENT_AUTH_TCP));
	//printf(szRcvBuffer);
	int check = strcmp(CLIENT_AUTH_TCP, szRcvBuffer);
	if (!check) {
		//client authorized
		if (debugMode == BOARD_MODE_DEBUG) {
			printConstructor2("authentication success\n");
		}
		clt_sock.send(CLIENT_AUTH_PASS, sizeof(CLIENT_AUTH_PASS));
		socketEvent = AUTH_COMPLETED;
	}
	else {
		// auth failed, disconnect immediately
		if (debugMode == BOARD_MODE_DEBUG) {
			printConstructor2("authentication failure\n");
		}
		clt_sock.send(CLIENT_AUTH_FAIL, sizeof(CLIENT_AUTH_FAIL));
		socketEvent = AUTH_FAIL_BAD_CODE;
	}
}

static inline void Observe() {
	clt_sock.send(SERVER_CONFIRM_COM, sizeof(SERVER_CONFIRM_COM));
	dataRequested = true;
	wait_ms(10);
	// copy transfer ram to transfer buffer
	IOS_Data transferBuffer = dataToSend;
	// send data
	if (debugMode == BOARD_MODE_DEBUG) {
		printConstructor2("sending data\n");
	}
	clt_sock.send((const char*)&transferBuffer, sizeof(IOS_Data));
	curBoardMode = BOARD_MODE_DEFAULT;
}

void printStruct(O_DATA &data) {
	for (int n = 0; n < 10; n++) {
		printConstructor2("Dout %i: %i \n", n, data.dout[n]);
	}
}

static inline void Manual() {
	O_DATA recieveBuffer;
	int dataSize = sizeof(O_DATA);
	clt_sock.recv((char *)&recieveBuffer, dataSize);
	overrideDataStruct = recieveBuffer;
	newOverrideData = true;
	if (debugMode == BOARD_MODE_DEBUG) {
		printConstructor2("O_DATA Size: %i\n", dataSize);
		printStruct(overrideDataStruct);
	}
	curBoardMode = BOARD_MODE_DEFAULT;
}

static inline void Update() {
	if (debugMode == BOARD_MODE_DEBUG) {
		printConstructor2("Beginning Update");
	}
	//std:vector<unsigned char> recieveBuffer;
	int firmwareSize = 0;
	// get firmware size
	clt_sock.recv((char*)&firmwareSize, sizeof(int));
	firmwareUpdate = new vector<unsigned char>(firmwareSize);
	//firmwareUpdate->reserve(firmwareSize);
	// get firmware
	clt_sock.recv((char*)firmwareUpdate->data(), firmwareSize);
	if (debugMode == BOARD_MODE_DEBUG) {
		printConstructor2("New firmware received: %i bytes\n", firmwareSize);
	}
	//firmwareUpdate = recieveBuffer;
	newFirmwareFlag = true;
	curBoardMode = BOARD_MODE_DEFAULT;
}

static inline void Stop_Manual() {
	newOverrideData = false;
}


net_state checkEvents(net_event netEvent) {
	net_state nt;
	switch (netEvent) {
	case IDLE:
		nt = NOT_LISTENING;
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
	case SERVER_SHUTDOWN:
		nt = TERMINATE_CONNECTION;
		break;
	}
	return nt;
}

void printStruct(void) {
	for (int i = 0; i < 10; i++) {
		//printConstructor2("Din %i: %i \n", i, dataToSend.din[i]);
	}

	for (int n = 0; n < 10; n++) {
		//printConstructor2("Dout %i: %i \n", n, dataToSend.dout[n]);
	}

	for (int k = 0; k < 3; k++) {
		//printConstructor2("Ain %i: %f \n", k, dataToSend.ain[k]);
	}
}

bool verifyCommand(const char command[], char buffer[]) {
	if (!strcmp(command, buffer))
		return true;
	return false;
}