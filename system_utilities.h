#ifndef system_utilities
#define system_utilities

#include "devices.h"

class device;
class list;

int parseCommandLine(char cline[], char *tklist[]);

void fillSystemCommandList();
int getCommandNumber(char* s);
int convertIntToValue(char* s);

int getDeviceTypeFromString(char* s);
device* makeDevice(char* tklist[]);

void processEvents(list *evl, int tm);

void displayDashboard();

#endif