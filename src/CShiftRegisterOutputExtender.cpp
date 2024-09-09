/*
 * CShiftRegisterOutputExtender.cpp
 *
 *
 *      Author: Luca Cordes
 */

#include "CShiftRegisterOutputExtender.h"

CShiftRegisterOutputExtender::CShiftRegisterOutputExtender(
		IO *serialData,  IO *shiftRegisterClock,
		IO *bufferRegisterClock) {
	m_serialData = serialData;
	m_shiftRegisterClock = shiftRegisterClock;
	m_bufferRegisterClock = bufferRegisterClock;
}

void CShiftRegisterOutputExtender::prepareOutput(int value) {
	for (int i = 7; i >= 0; i--) { //we start from the left to the right
		//here we write the data into the *m_serialData and each D FF will
		//hold one of the passedon uint8_t value bits
		*m_serialData = value & (1 << i);

		//pin 11 of the ic is shiftRegisterClock. so we need a rising edeg
		//the previous level was 0
		*m_shiftRegisterClock = 1; //now it got 1 so here is our rising Flank
		*m_shiftRegisterClock = 0;
        
	}
	m_preparedOutput = value;
}

void CShiftRegisterOutputExtender::updateOutput() {
	//a rising of RCLK will cause the RS FF to hold the value of each
	//D FF in front of them
	*m_bufferRegisterClock = 1;
	*m_bufferRegisterClock = 0;
	m_currentOutput = m_preparedOutput;
}

void CShiftRegisterOutputExtender::write(int value) {
	prepareOutput(value);
	//updateOutput();
}

CShiftRegisterOutputExtender& CShiftRegisterOutputExtender::operator =(
		int value) {
	write(value);
	return *this;
}

int CShiftRegisterOutputExtender::read() const {
	return m_currentOutput;
}

CShiftRegisterOutputExtender::operator int() const {
	return read();
}