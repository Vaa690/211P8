#include "devices.h"
#include "definitions.h"
#include "stdlib.h"
#include "string.h"
#include "system_utilities.h"
#include <iostream>
#include <math.h>

using namespace std;

// Initializing constructor:
// Sets the count and time data members to 0, and last malfuntion type to NO_MALFUNCTION

malfunctionRecord::malfunctionRecord() {

	mlfn_count = 0;
	mlfn_time = 0;
	mlfn_type = NO_MALFUNCTION;
}

// Increments the count, sets type and time to mlfn and tm respectively

void malfunctionRecord::malfunction(int mlfn, int tm) {

	mlfn_count++;
	mlfn_type = mlfn;
	mlfn_time = tm;

}

// If count is 0: print that the device never malfunctioned
// If count is greater than 0, print the count, last malfunction type, and time

void malfunctionRecord::display() {

	cout<<"\n=========================================="<<endl;
	cout<<"======== MALFUNCTION INFORMATION ========="<<endl;
	cout<<"=========================================="<<endl;

	if(mlfn_count == 0) {
		cout<<"This device has never malfunctioned"<<endl;
	}

	if(mlfn_count>0) {
		cout<<"The number of malfunctions is: "<<mlfn_count<<endl;
		cout<<"\nThe last malfunction type was: "<<mlfn_type<<endl;
		cout<<"\nThe last malfunction time was: "<<mlfn_time<<endl;
	}

}

// Returns the count as the answer
// Sets m to last malfunction type and t to last malfunction time

int malfunctionRecord::getRecord(int* m, int* t) {

	*m = mlfn_type;
	*t = mlfn_time; 

	return mlfn_count;
}

device::device() {
	device_name = "default";
	serial_number = 0;
	device_value = 0;
	device_type = GENERIC;
}


// Use malloc to allocate enough space to hold string n
// The address returned by malloc should be assigned to the data member for the device name

device::device(char* n, int sn) {

	device_name = (char* )malloc(strlen(n)+1);
	strcpy(device_name, n); // WARNING ON STRCPY
	serial_number = sn;
	device_value = 0;
	device_type = GENERIC;
}

// Destructor: frees memory allocated to hold the name data member

device::~device() {

	free((void *) device_name);

}

// Display information on the device

void device::display() {

	cout<<"\n========================================"<<endl;
	cout<<"========== Device Information ============"<<endl;
	cout<<"=========================================="<<endl;
	cout<<"The name of the device is: "<<device_name<<endl;
	cout<<"\nThe serial number for the device is: "<<serial_number<<endl;
	cout<<"\nThe device value is: "<<device_value<<endl;
	malf.display();

}

// Has the malfunctionRecord data member call its malfunctionRecord function member

void device::recordMalfunction(int m, int t) {

	malf.malfunction(m, t);

}

// Has the malfunctionRecord data member call its getMalfunctionRecord function member
// Returns the answer as it's own answer

int device::getMalfunctionRecord(int* m, int* t) {
	
	int x = malf.getRecord(m, t);

	return x;

}

// Uses strcmp to compare the devices name with the argument n. Returns 1 if equal, 0 if not.

int device::amIThisDevice(char* n) {
	
	if (strcmp(device_name, n) == 0) {
		return 1;
	}

	else {
		return 0;
	}
}

int device::getType() {
        return device_type;
}

int device::getValue() {
        return device_value;
}

DigitalSensorDevice::DigitalSensorDevice(char* n, int id, int val) {
        device_name = (char *) malloc(strlen(n) + 1);
        strcpy(device_name, n);
        serial_number = id;
        device_value = val;
        device_type = DIGITAL_SENSOR;
}

void DigitalSensorDevice::display() {
        device::display();
        cout << "This is a digital sensor device." << endl;
        if(device_value==ON) cout << "This device is currently ON.";
        else if(device_value==OFF) cout << "This device is currently OFF.";
        else cout << "Error: No valid input for value.";
}

void DigitalSensorDevice::setValue(int v) {
        if(v==ON) device_value = ON;
        else device_value = OFF;
}

AnalogSensorDevice::AnalogSensorDevice(char* n, int id, int val, int b) {
        device_name = (char *) malloc(strlen(n) + 1);
        strcpy(device_name, n);
        serial_number = id;
        if(b > 16 || b < 1) bits = 8;
        else bits = b;
        device_type = ANALOG_SENSOR;
        setValue(val);
}

void AnalogSensorDevice::display() {
        device::display();
        cout << "This is an analog sensor device." << endl;
        cout << "The resolution is " << bits << ", and the value is " << device_value << ".";
}

void AnalogSensorDevice::setValue(int v) {
        double y = bits;
        double x = pow(2,y) - 1;

        if(v < 0) device_value = 0;
        else if(v > x) device_value = x;
        else device_value = v;

}

DigitalControllerDevice::DigitalControllerDevice(char* n, int id) {
        device_name = (char *) malloc(strlen(n) + 1);
        strcpy(device_name, n);
        serial_number = id;
        device_value = OFF;
        device_type = DIGITAL_CONTROLLER;
}

void DigitalControllerDevice::display() {
        device::display();
        cout << "This is a digital controller device." << endl;
        if(device_value==ON) cout << "This device is currently ON.";
        else if(device_value==OFF) cout << "This device is currently OFF.";
        else cout << "Error: No valid input for value.";
}

void DigitalControllerDevice::setValue(int v) {
        if(v==ON) device_value = ON;
        else device_value = OFF;
}

AnalogControllerDevice::AnalogControllerDevice(char* n, int id, int val, int up, int low) {
        device_name = (char *) malloc(strlen(n) + 1);
        strcpy(device_name, n);
        serial_number = id;
        upper = up;
        lower = low;
        setValue(val);
        device_type = ANALOG_CONTROLLER;
}

void AnalogControllerDevice::display() {
        device::display();
        cout << "This is an analog controller device with range " << lower << " to " << upper << "." << endl;
        cout << "The value is " << device_value << ".";
}

void AnalogControllerDevice::setValue(int v) {
        if(v < lower) {
                device_value = lower;
                cout << "Error: Value argument too low." << endl;
        }
        else if(v > upper) {
                device_value = upper;
                cout << "Error: Value argument too high." << endl;
        }
        else device_value = v;
}