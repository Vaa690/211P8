#include "system_utilities.h"
#include "definitions.h"
#include "devices.h"
#include "stdlib.h"
#include "string.h"
#include <iostream>
#include "events.h"

using namespace std;

int parseCommandLine(char cline[], char *tklist[]) {
	int string_length, token_length, i, j;
	int next_Token = 0;

	string_length = strlen(cline);
	i = 0;

	while(cline[i] !=0) {

		// Find the next Blank
		while(cline[i]==' ') i++;
		j=i+1; // Set j to the next character

		if(cline[i] !='"') {
			// Keep going through the characters while cline[j] isn't blank
			while(cline[j]!=' ' && cline[j] != 0) j++;
			token_length=j+1 - i;
		}

		else {
			i = i+1;
			j = i+1;
			while(cline[j] != '"') j++;
			token_length = j+1 - i;
			j=j+1;
		}

		tklist[next_Token] = (char* )malloc(token_length);
		memcpy(tklist[next_Token], cline+i, token_length-1);
		tklist[next_Token][token_length-1] = 0;
		next_Token++;
		i = j;
	}

	return next_Token;
}

class COMMAND {

private:
	char *pointer;
	int cmd_num;

public:
	COMMAND();
	COMMAND(char *, int);
	int amIThisCommand(char *);
};

COMMAND::COMMAND() {
	pointer = "null";
	cmd_num = 0;
}
COMMAND::COMMAND(char *cmd, int cmd_int) {
	pointer = cmd;
	cmd_num = cmd_int;
}

int COMMAND::amIThisCommand(char *check_pnt) {
	if(strcmp(pointer, check_pnt) == 0)
		return cmd_num;
	else
		return 0;
}

COMMAND *systemCommands[NUMBER_OF_COMMANDS];

void fillSystemCommandList() {
	systemCommands[0] = new COMMAND("halt", HALT);
	systemCommands[1] = new COMMAND("status", STATUS);
	systemCommands[2] = new COMMAND("time_click", TIME_CLICK);
	systemCommands[3] = new COMMAND("create_device", CREATE_DEVICE);
	systemCommands[4] = new COMMAND("create_event", CREATE_EVENT);
	systemCommands[5] = new COMMAND("set_device_value", SET_DEVICE_VALUE);
	systemCommands[6] = new COMMAND("process_events", PROCESS_EVENTS);
}

int getCommandNumber(char *s) {
	if(strcmp(s, "halt") == 0) 
		return HALT;
    if(strcmp(s, "status") == 0) 
		return STATUS;
    if(strcmp(s, "time_click") == 0) 
		return TIME_CLICK;
    if(strcmp(s, "create_device") == 0) 
		return CREATE_DEVICE;
    if(strcmp(s, "create_event") == 0) 
		return CREATE_EVENT;
    if(strcmp(s, "set_device_value") == 0) 
		return SET_DEVICE_VALUE;
    if(strcmp(s, "process_events") == 0) 
		return PROCESS_EVENTS;
	else
		return UNDEFINED_COMMAND;
}

int convertIntToValue(char* s) {
	// Write an Algorithm that accepts a string and returns an integer value that represents the same number
	int pre_val = 0;
	int conv_val;
	for(int i=0; s[i] != NULL; i++) {
		 conv_val = s[i] - 48;
		 pre_val = (10 * pre_val) + conv_val;
	}
	return pre_val;
}

int getDeviceTypeFromString(char* s) {
        if(strcmp(s, "digital_sensor") == 0) return DIGITAL_SENSOR;
        if(strcmp(s, "analog_sensor") == 0) return ANALOG_SENSOR;
        if(strcmp(s, "digital_controller") == 0) return DIGITAL_CONTROLLER;
        if(strcmp(s, "analog_controller") == 0) return ANALOG_CONTROLLER;
        return GENERIC;
}

device* makeDevice(char* tkl[]) {

        int len = 0;
        for(int i = 0; tkl[i] != NULL; i++) len++;

        device *dev;
        int x;
        x = getDeviceTypeFromString(tkl[1]);
        int y = 0;
        y = convertIntToValue(tkl[3]);
        int z = 0;
        int aa = 0;
        int ab = 0;
        int ac = 0;
        
        switch(x) {
        case DIGITAL_SENSOR:
                if(strcmp(tkl[4], "ON")==0) z = ON;
                if(strcmp(tkl[4], "OFF")==0) z = OFF;

                dev = new DigitalSensorDevice(tkl[2], y, z);
                return dev;
                break;
        case ANALOG_SENSOR:
                aa = convertIntToValue(tkl[4]);
                ab = convertIntToValue(tkl[5]);

                dev = new AnalogSensorDevice(tkl[2], y, aa, ab);
                return dev;
                break;
        case DIGITAL_CONTROLLER:
                dev = new DigitalControllerDevice(tkl[2], y);
                return dev;
                break;
        case ANALOG_CONTROLLER:
                aa = convertIntToValue(tkl[4]);
                ab = convertIntToValue(tkl[5]);
                ac = convertIntToValue(tkl[6]);
                dev = new AnalogControllerDevice(tkl[2], y, aa, ab, ac);
                return dev;
        }
        return NULL;
}

void processEvents(list *evl, int tm) {
	cout<<endl<<"\nProcessing events at time: "<<tm<<"."<<endl;
	evl->processEvents(tm);
}

void displayDashboard() {
	int k, n;
	
	cout << "\n\nTime: " << globalTime << "\n";
	k = findDevice("Left Turn Lamp");
	n = systemDevices[k]->get_value();
	if(n==OFF)  cout << "|   |  |";
	else        cout << "|***|  |";
	
	k = findDevice("Speedometer");
	n = systemDevices[k]->get_value()/4;

	for(k=0; k<n;  k++) cout << "*";
	for(   ; k<32; k++) cout << " ";
	
	k = findDevice("Right Turn Lamp");
	n = systemDevices[k]->get_value();
	if(n==OFF)  cout << "|  |   |  \n";
	else        cout << "|  |***|  \n";
	
	k = findDevice("Brake Lamps");
	n = systemDevices[k]->get_value();
	if(n==OFF)  cout << "                 Brakes |   | \n";
	else        cout << "                 Brakes |***| \n";
	
	if(checkEngine)  cout << "                 CHECK ENGINE\n\n";
	else             cout << "                  Engine OK\n\n";
	
	
}