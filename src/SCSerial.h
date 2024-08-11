/*
 * SCSerial.h
 * FIT serial servo hardware interface layer program
 */

#include <SoftwareSerial.h>
#ifndef _SCSERIAL_H
#define _SCSERIAL_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "SCS.h"

class pSerial_
{
public:
	pSerial_();
	HardwareSerial *pSerial_h = NULL;//串口指针
	SoftwareSerial *pSerial_s = NULL;//串口指针
	int read();
	size_t write(uint8_t *data, uint8_t *len);
};

class SCSerial : public SCS
{
public:
	SCSerial();
	SCSerial(u8 End);
	SCSerial(u8 End, u8 Level);

protected:
	virtual int writeSCS(unsigned char *nDat, int nLen); // Output nLen bytes
	virtual int readSCS(unsigned char *nDat, int nLen); // Input nLen bytes
	virtual int writeSCS(unsigned char bDat); // Output 1 byte
	virtual void rFlushSCS();
	virtual void wFlushSCS();
public:
	unsigned long int IOTimeOut; // Input and output timeout
	pSerial_ pSerial_hack;
	pSerial_ *pSerial;//串口指针
	int Err;
public:
	virtual int getErr(){  return Err;  }
};

#endif