//I AM THE CLIENT
#include "TCPClient.h"
//#include <cstdint>
#include "main_client.h"
//#include "XL45BX50"
#include <fstream>
#include <iterator>


#define LOCALHOST "LOCALHOST"

#define PRINT_LOG [](const std::string& strLogMsg) { std::cout << strLogMsg << std::endl; }

using namespace std;

/* functions */
void printStruct(IOS_Data);
bool verifyCommand(const char[], char[]);

CTCPClient TCP_Client(PRINT_LOG); // for debugging

IOS_Data newStruct;

net_state socketState = TCP_DISCONNECTED;
net_event socketEvent = LISTENING;

char IP_TO_CONNECT[15] = "";

bool Authorize(void);
bool Connect(void);
bool Observe(void);
bool Manual(void);
bool Update(void);
bool Stop_Manual(void);

const char* status(void) {
	switch (socketState) {
	case NOT_LISTENING:
		return "NOT_LISTENING";
		break;
	case TCP_DISCONNECTED:
		return "TCP_DISCONNECTED";
		break;
	case TCP_CONNECTED:
		return "TCP_CONNECTED";
		break;
	case WAITING_FOR_COMMANDS:
		return "READY_TO_SEND_COMMANDS";
		break;
	case TERMINATE_CONNECTION:
		return "TERMINATE_CONNECTION";
		break;
	}
}

int main(int argc, char * argv[])
{
	char c = '\0'; // command
	bool exit = false;

	do
	{
		cout << "Status: " << status() << endl;
		cout << "c: connect | o: observe | u: update | m: manual | s: stop manual | e: exit" << endl;
		cout << "Enter command: ";
		cin >> c;
		cout << endl;

		switch (c) {
		case 'c':
		{
			if (!Connect()) {
				break;
			}
			else {
				if (!Authorize()) {
					break;
				}
				else {
				}
			}
		}
			break;
		case 'o':
		{
			if (!Observe()) {
				break;
			}
		}
			break;
		case 'u':
		{
			if (!Update()) {
				break;
			}
		}
			break;
		case 'm':
		{
			if (!Manual()) {
				break;
			}
		}
		break;
		case 's':
		{
			if (!Stop_Manual()) {
				break;
			}
		}
			break;
		case 'e':
		{
			TCP_Client.Send(CLIENT_DISCONNECT, BUFFER_SIZE);
			TCP_Client.Disconnect();
			socketState = TCP_DISCONNECTED;
		}
		break;
		}

	} while (!exit);

	system("cls");
	//printStruct();

	TCP_Client.~CTCPClient();
	
	return 0;
}

bool Connect() {
	cout << "Enter address: ";
	cin >> IP_TO_CONNECT;
	printf("connecting to %s on port %d\n", IP_TO_CONNECT, PORT);
	if (TCP_Client.Connect(IP_TO_CONNECT, DEFAULT_PORT)) // should return true if the connection succeeds
	{
		printf("connected\n");
		socketState = TCP_CONNECTED;
		return true;
	}
	else {
		printf("connection failed");
		return false;
	}
}

bool Authorize() {
	printf("authenticating\n");
	// client connected, start auth
	char szRcvBuffer[BUFFER_SIZE] = {};
	TCP_Client.Send(CLIENT_AUTH_TCP, sizeof(CLIENT_AUTH_TCP));
	TCP_Client.Recv(szRcvBuffer, sizeof(CLIENT_AUTH_PASS));
	int check = strcmp(CLIENT_AUTH_PASS, szRcvBuffer);
	if (!check) {
		//client authorized
		printf("authentication success\n");
		socketState = WAITING_FOR_COMMANDS;
		return false;
	}
	else if (!strcmp(CLIENT_AUTH_FAIL, szRcvBuffer)){
		// auth failed, disconnect immediately
		printf("authentication failure\n");
		socketState = TCP_DISCONNECTED;
		TCP_Client.Disconnect();
		return false;
	}
	else {
		printf("authentication corrupted\n");
		socketState = TCP_DISCONNECTED;
		TCP_Client.Disconnect();
		return false;
	}
}

bool Observe() {
	char szRcvBuffer2[BUFFER_SIZE] = {};
	// request observe
	printf("request observe\n");
	TCP_Client.Send(REQUEST_OBSERVE_COM, sizeof(REQUEST_OBSERVE_COM));
	// get server confirm
	TCP_Client.Recv(szRcvBuffer2, BUFFER_SIZE);
	if (!strcmp(SERVER_CONFIRM_COM, szRcvBuffer2)) {
		// get data
		printf("receive data\n");
		bool error = TCP_Client.Recv((char*)&newStruct, sizeof(IOS_Data));
		printStruct(newStruct);
		socketEvent = STANDBY_FOR_ORDERS;
		return error == 0;
	}
	else {
		printf("observe fail\n");
		socketEvent = STANDBY_FOR_ORDERS;
		return false;
	}
}

bool Manual() {
	TCP_Client.Send(REQUEST_MANUAL_COM, BUFFER_SIZE);
	O_DATA sendBuffer;
	Dummy::fakeManual1(sendBuffer);
	int oDataSize = sizeof(O_DATA);
	printf("Sending manual: %i bytes\n\n", oDataSize);
	int error = TCP_Client.Send((const char *)&sendBuffer, oDataSize);
	return error;
}

bool Stop_Manual() {
	bool error = TCP_Client.Send(CANCEL_MANUAL, BUFFER_SIZE);
	return error;
}

bool Update() {
	TCP_Client.Send(REQUEST_UPDATE_COM, BUFFER_SIZE);
	std::ifstream input("ServiceToolDashboard.bin", std::ios::binary);
	std::vector<unsigned char> sendBuffer(std::istreambuf_iterator<char>(input), {});
	input.close();
	int firmwareSize = sendBuffer.size() * sizeof(unsigned char);
	printf("%i\n", firmwareSize);
	TCP_Client.Send((const char*)&firmwareSize, sizeof(int));
	bool error = TCP_Client.Send((const char*)sendBuffer.data(), firmwareSize);
	return error;
}


bool verifyCommand(const char command[], char buffer[]) {
	if (!strcmp(command, buffer))
		return true;
	return false;
}

void printStruct( IOS_Data dataStruct ) {
	for (int i = 0; i < 10; i++) {
		printf("Din %i: %i \n", i, dataStruct.din[i]);
	}

	for (int n = 0; n < 10; n++) {
		printf("Dout %i: %i \n", n, dataStruct.dout[n]);
	}

	for (int k = 0; k < 3; k++)
		printf("Ain %i: %f \n", k, dataStruct.ain[k]);
}