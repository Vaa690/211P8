#ifndef DEVICES_H
#define DEVICES_H

#include "definitions.h"

class malfunctionRecord {

protected:
	int mlfn_count;
	int mlfn_type;
	int mlfn_time;

public:
	malfunctionRecord();
	void malfunction(int mlfn, int tm);
	void display();
	int getRecord(int *m, int *t);
};


class device {

protected:
	char* device_name;
	malfunctionRecord malf;
	int serial_number;
	int device_value;
	int device_type;

public:
	device ();
	device(char* n, int sn);
	~device();
	virtual void display();
	void recordMalfunction(int m, int t);
	int getMalfunctionRecord(int *m, int *t);
	int amIThisDevice(char *n);
	virtual int getType();
	int getValue();
};

class DigitalSensorDevice: public device
{
public:
        DigitalSensorDevice(char*, int, int);
        void display();
        void setValue(int);
};

class AnalogSensorDevice: public device
{
protected:
        int bits;
public:
        AnalogSensorDevice(char*, int, int, int);
        void display();
        void setValue(int);
};

class DigitalControllerDevice: public device
{
public:
        DigitalControllerDevice(char*, int);
        void display();
        void setValue(int);
};

class AnalogControllerDevice: public device
{
protected:
        int upper;
        int lower;
public:
        AnalogControllerDevice(char*, int, int, int, int);
        void display();
        void setValue(int);
};
#endif