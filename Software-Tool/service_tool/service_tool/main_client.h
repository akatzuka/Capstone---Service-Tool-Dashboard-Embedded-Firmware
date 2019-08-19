#pragma once
#ifndef CLIENT
#define CLIENT

#include "supplemental/interphasic.h"
#include "supplemental/TCPClient.h"

using namespace interphasic;

#include <fstream>
#include <iterator>

public class Client {
	net_state socketState = TCP_DISCONNECTED;
	net_event socketEvent = LISTENING;
	CTCPClient *TCP_Client; // for debugging

	IOS_Data newStruct;

public:
	Client() {
		WSADATA wsaData;
		WSAStartup(MAKEWORD(2, 2), &wsaData);
		TCP_Client = new CTCPClient(PRINT_LOG);
	}

	bool connectToClient(const string &ipAddress) {
		printf("connecting to %s on port %d\n", ipAddress, PORT);
		if (TCP_Client->Connect(ipAddress, DEFAULT_PORT)) // should return true if the connection succeeds
		{
			printf("connected\n");
			socketState = TCP_CONNECTED;
			return Authorize();
		}
		else {
			printf("connection failed");
			return false;
		}
	}
	
	void sendCmd(const char CMD[]) {
		printf("ready to send commands\n");
		/// sample sending and receive of struct
		// request observe
		printf("request observe\n");
		TCP_Client->Send(CMD);
	}

	bool Authorize() {
		printf("authenticating\n");
		// client connected, start auth
		char szRcvBuffer[BUFFER_SIZE] = {};
		TCP_Client->Send(CLIENT_AUTH_TCP, sizeof(CLIENT_AUTH_TCP));
		TCP_Client->Recv(szRcvBuffer, sizeof(CLIENT_AUTH_PASS));
		int check = strcmp(CLIENT_AUTH_PASS, szRcvBuffer);
		if (!check) {
			//client authorized
			printf("authentication success\n");
			socketState = WAITING_FOR_COMMANDS;
			return false;
		}
		else if (!strcmp(CLIENT_AUTH_FAIL, szRcvBuffer)) {
			// auth failed, disconnect immediately
			printf("authentication failure\n");
			socketState = TCP_DISCONNECTED;
			TCP_Client->Disconnect();
			return false;
		}
		else {
			printf("authentication corrupted\n");
			socketState = TCP_DISCONNECTED;
			TCP_Client->Disconnect();
			return false;
		}
	}

	System::String ^Observe() {
		char szRcvBuffer2[BUFFER_SIZE] = {};
		// request observe
		printf("request observe\n");
		TCP_Client->Send(REQUEST_OBSERVE_COM, sizeof(REQUEST_OBSERVE_COM));
		 //get server confirm
		TCP_Client->Recv(szRcvBuffer2, BUFFER_SIZE);
		if (!strcmp(SERVER_CONFIRM_COM, szRcvBuffer2)) {
			// get data
			printf("receive data\n");
			bool error = TCP_Client->Recv((char*)&newStruct, sizeof(IOS_Data));
			socketEvent = STANDBY_FOR_ORDERS;
			return printStruct(newStruct);
		}
		else {
			printf("observe fail\n");
			socketEvent = STANDBY_FOR_ORDERS;
			return "Observe failed";
		}
	}

	bool Manual(O_DATA sendBuffer) {
		TCP_Client->Send(REQUEST_MANUAL_COM, BUFFER_SIZE);
		int oDataSize = sizeof(O_DATA);
		//printf("Sending manual: %i bytes\n\n", oDataSize);
		int error = TCP_Client->Send((const char *)&sendBuffer, oDataSize);
		return error;
	}

	bool Stop_Manual() {
		bool error = TCP_Client->Send(CANCEL_MANUAL, BUFFER_SIZE);
		return error;
	}

	bool Update(string file) {
		TCP_Client->Send(REQUEST_UPDATE_COM, BUFFER_SIZE);
		std::ifstream input(file, std::ios::binary);
		std::vector<unsigned char> sendBuffer(std::istreambuf_iterator<char>(input), {});
		input.close();
		int firmwareSize = sendBuffer.size() * sizeof(unsigned char);
		//printf("%i\n", firmwareSize);
		TCP_Client->Send((const char*)&firmwareSize, sizeof(int));
		bool error = TCP_Client->Send((const char*)sendBuffer.data(), firmwareSize);
		return error;
	}

	System::String ^receiveObserveData() {
		IOS_Data dataStruct;
		// get server confirm
		char szRcvBuffer[sizeof(BUFFER_SIZE)] = {};
		TCP_Client->Recv(szRcvBuffer, BUFFER_SIZE);
		if (!strcmp(SERVER_CONFIRM_COM, szRcvBuffer)) {
			// get data
			printf("receive data\n");
			bool error = TCP_Client->Recv((char*)&newStruct, sizeof(IOS_Data));
			socketEvent = STANDBY_FOR_ORDERS;
			return printStruct(newStruct);
		}
		else {
			printf("observe fail\n");
			socketEvent = STANDBY_FOR_ORDERS;
			return "Observe Failed";
		}
	}

	bool closeSocket()
	{
		TCP_Client->Send(CLIENT_DISCONNECT, BUFFER_SIZE);
		TCP_Client->Disconnect();
		socketState = TCP_DISCONNECTED;
		return true;
	}

	System::String ^printStruct(IOS_Data dataStruct) {
		System::String ^s = "";
		for (int i = 0; i < 10; i++) {
			printf("Din %i: %i \n", i, dataStruct.din[i]);
			s += "Din " + i + ": " + System::Int32(dataStruct.din[i]) + " \n";
		}

		for (int n = 0; n < 10; n++) {
			printf("Dout %i: %i \n", n, dataStruct.dout[n]);
			s += "Dout " + n + ": " + System::Int32(dataStruct.dout[n]) + " \n";
		}

		for (int k = 0; k < 3; k++) {
			printf("Ain %i: %f \n", k, dataStruct.ain[k]);
			s += "Ain " + k + ": " + System::Single(dataStruct.ain[k]) + " \n";
		}

		return s;
	}

	//void changeSocketState(net_event socketEvent) {
	//	socketState = checkEvents(socketEvent);
	//	switch (socketState)
	//	{
	//	case TCP_DISCONNECTED:
	//	{
	//		printf("connecting to %s on port %d\n", LOCALHOST, PORT);
	//		// connect to server
	//		if (TCP_Client->Connect(LOCALHOST, DEFAULT_PORT)) // should return true if the connection succeeds
	//		{
	//			printf("connected\n");
	//			socketState = TCP_CONNECTED;
	//			socketEvent = CLIENT_AUTHORIZING;
	//		}
	//	}
	//	break;
	//	case TCP_CONNECTED:
	//	{
	//		printf("authenticating\n");
	//		// client connected, start auth
	//		char szRcvBuffer[sizeof(CLIENT_AUTH_PASS)] = {};
	//		TCP_Client->Send(CLIENT_AUTH_TCP);
	//		TCP_Client->Recv(szRcvBuffer, sizeof(CLIENT_AUTH_PASS) - 1);
	//		int check = strcmp(CLIENT_AUTH_PASS, szRcvBuffer);
	//		if (!check) {
	//			//client authorized
	//			printf("authentication success\n");
	//			socketEvent = AUTH_COMPLETED;
	//		}
	//		else {
	//			// auth failed, disconnect immediately
	//			printf("authentication failure\n");
	//			socketEvent = AUTH_FAIL_BAD_CODE;
	//		}
	//	}
	//	break;
	//	case WAITING_FOR_COMMANDS:
	//	{
	//		if (socketEvent == CLIENT_SHUTDOWN) {
	//		}
	//	}
	//	break;
	//	case TERMINATE_CONNECTION:
	//	{
	//		printf("terminating connection\n");
	//		TCPClient->Disconnect();
	//		socketState = TCP_DISCONNECTED;
	//		socketEvent = LISTENING;
	//	}
	//	break;
	//	case NOT_LISTENING:
	//	{
	//	}
	//	}

	//	//const std::string strSendData = "Hello World !";
	//	//TCPClient->Send(strSendData);
	//	/* or */
	//	//TCPClient->Send(strSendData.c_str(), 13);
	//	/* or even an std::vector<char> */

	//	//char szRcvBuffer[14] = {};
	//	//TCPClient->Receive(szRcvBuffer, 13);

	//}

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
};

#endif