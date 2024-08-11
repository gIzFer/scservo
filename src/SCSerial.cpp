/*
 * SCSerial.h
 * FIT serial servo hardware interface layer program
 */

#include "SCSerial.h"

pSerial_::pSerial_()
{
	pSerial_h = NULL;
	pSerial_s = NULL;
}

int pSerial_::read()
{
		//DEBUG#Serial.println("reading!");
	if(pSerial_h != NULL){
		//DEBUG#Serial.println("rh");
		return pSerial_h->read();
	}else if(pSerial_s != NULL){
		//DEBUG#Serial.println("rs");
		return pSerial_s->read();
	}
	//DEBUG#Serial.print("error");
}

size_t pSerial_::write(uint8_t *data, uint8_t *len)
{
		//DEBUG#Serial.println("writing!");
	if(pSerial_h != NULL){
		//DEBUG#Serial.println("wh");
		return pSerial_h->write(data, len);
	}else if(pSerial_s != NULL){
		//DEBUG#Serial.println("ws");
		return pSerial_s->write(data, len);
	}
	//DEBUG#Serial.print("error");
}

SCSerial::SCSerial()
{
	IOTimeOut = 100;
	pSerial_hack = pSerial_();
	pSerial = &pSerial_hack;
}

SCSerial::SCSerial(u8 End):SCS(End)
{
	IOTimeOut = 100;
	pSerial_hack = pSerial_();
	pSerial = &pSerial_hack;
}

SCSerial::SCSerial(u8 End, u8 Level):SCS(End, Level)
{
	IOTimeOut = 100;
	pSerial_hack = pSerial_();
	pSerial = &pSerial_hack;
}

int SCSerial::readSCS(unsigned char *nDat, int nLen)
{
	int Size = 0;
	int ComData;
	unsigned long t_begin = millis();
	unsigned long t_user;
	while(1){
		ComData = pSerial->read();
		if(ComData!=-1){
			if(nDat){
				nDat[Size] = ComData;
			}
			Size++;
			t_begin = millis();
		}
		if(Size>=nLen){
			break;
		}
		t_user = millis() - t_begin;
		if(t_user>IOTimeOut){
			break;
		}
	}
	return Size;
}

int SCSerial::writeSCS(unsigned char *nDat, int nLen)
{
	if(nDat==NULL){
		return 0;
	}
	return pSerial->write(nDat, nLen);
}

int SCSerial::writeSCS(unsigned char bDat)
{
	return pSerial->write(&bDat, 1);
}

void SCSerial::rFlushSCS()
{
	while(pSerial->read()!=-1);
}

void SCSerial::wFlushSCS()
{
}