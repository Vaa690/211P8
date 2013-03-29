/* EECS 211 - PROGRAM 6: WORKING WITH COMMAND LINE COMMANDS

BY: VICTOR ABECASSIS
DATE: 2/15/2012

*/

#include "definitions.h" 
#include "system_utilities.h"
#include "devices.h"
#include "events.h"
#include <iostream>
#include <fstream>

using namespace std;

device *dList[MAX_DEVICES];
int num_devices = 0;
int time = 0;
int checkEngine = 0;

int main() {

	char cline[MAX_CMD_LINE_LENGTH];
	char *tklist[MAX_TOKENS_ON_A_LINE];
	int tokCount;
	int halt =0;
	int val;
	int pt;

	list *event_list;
	event_list = new list();
	EVENT *new_event;

	ifstream infile;
	infile.open("p7input.txt", ios::in);

	if(!infile.is_open()) {
		cout<<"The File was not opened."<<endl;
		return 0;
	}

	void fillSystemCommandList();

	while(halt == 0) {

		memset(cline, 0 , MAX_CMD_LINE_LENGTH);
		infile.getline(cline, MAX_CMD_LINE_LENGTH);
		tokCount = parseCommandLine(cline,tklist);

		cout<<"There are "<<tokCount<<" tokens on the command line."<<endl;
		cout<<"\nBelow is a list of the tokens:\n"<<endl;
		for(int i=0; i<tokCount; i++) {
			char *str = tklist[i];
			cout<<"Token number "<<i+1<<" is: "<<str<<endl;
			cout<<"\n";
		}

		int tokCommand = getCommandNumber(tklist[0]);
		int test_convert = convertIntToValue(tklist[1]);

		switch(tokCommand) {
		case HALT:
			cout << "Command halt recognized." << endl;
			halt++;
			break;
		case STATUS:
			cout << "Command status recognized." << endl;
			cout<<"\nTime: "<<time<<endl;
			if(strcmp(tklist[1], "devices")==0) {
				cout<<"\nThere are "<<num_devices<<" devices."<<endl;
				for(int i=0; i<num_devices; i++) {
					dList[i] ->display();
					cout<<endl<<"\n"<<endl;
				}
			}
			if(strcmp(tklist[1],"events")==0) {
				event_list ->display();
			}
			break;
		case TIME_CLICK:
			cout << "Command time-click recognized." << endl;
			time++;
			break;
		case CREATE_DEVICE:
			cout << "Command create-device recognized." << endl;
			if(num_devices == MAX_DEVICES)
				cout<< "ERROR: THERE IS NO MORE SPACE IN THE SYSTEM"<<endl;
			else {
				dList[num_devices] = makeDevice(tklist);
				if(dList[num_devices] == NULL)
					cout<<"The Device Named by the third token could not be created"<<endl;
				else
					num_devices++;
			}
			break;
		case CREATE_EVENT:
			cout << "Command create-event recognized." << endl;
			val = convertIntToValue(tklist[2]);
			pt = convertIntToValue(tklist[3]);
			new_event = new EVENT(tklist[1], val, pt);
			new_event->display();
			event_list->insertEvent(new_event);
			break;
		case SET_DEVICE_VALUE:
			cout << "Command set-device-value recognized." << endl;
			break;
		case PROCESS_EVENTS:
			cout << "Command process-events recognized." << endl;
			processEvents(event_list, time);
			break;
		case UNDEFINED_COMMAND:
			cout << "Command not recognized." << endl;
			break;
		}
		cout<<"\n============================";
		cout<<"\n============================\n"<<endl;

		for(int k=0; k<tokCount; k++) {
			free((void *)tklist[k]);
		}
	}

	infile.close();
	int close_program;
	cout<<"Enter 0 to exit the program"<<endl;
	cin>>close_program;
	return 0;
}