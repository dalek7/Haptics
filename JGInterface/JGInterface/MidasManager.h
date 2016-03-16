#pragma once
#include "SerialManager2.h"

// see definition of SensorData in Stdafx.h

#define kHistory 500
class MidasManager :	public SerialManager2
{
public:
	MidasManager(void);
	~MidasManager(void);


	SensorData sn0;
	SensorData sn1;

public:
	// Applicable to vibrating : Motor ID 2 (original version of 0, 1)
	//void SetMotorValues(int duty_over_100, int freq_over_255, int time_over_255, int motor_id);


public:

	void Init();

	
	int n0_AccX[kHistory];
	int n0_AccY[kHistory];
	int n0_AccZ[kHistory];
	int n0_IRs[kHistory];

	int n1_AccX[kHistory];
	int n1_AccY[kHistory];
	int n1_AccZ[kHistory];
	int n1_IRs[kHistory];



public:
	



public:
	virtual void	CheckPacket(int nID=0);
};
