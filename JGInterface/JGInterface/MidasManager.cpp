#include "stdafx.h"
#include "MidasManager.h"

#include "JGInterfaceDoc.h"
#include "JGInterfaceView.h"


extern CJGInterfaceView *pv;


MidasManager::MidasManager(void)
{

	Init();

}

MidasManager::~MidasManager(void)
{

}


void MidasManager::Init()
{
	int i;

	for( i=0; i<kHistory; i++)
	{
		n0_AccX[i]= 0;
		n0_AccY[i]= 0;
		n0_AccZ[i]= 0;
		n0_IRs[i] = 0;

		n1_AccX[i]= 0;
		n1_AccY[i]= 0;
		n1_AccZ[i]= 0;
		n1_IRs[i] = 0;
	}
	
	memset(&sn0, 0, sizeof(SensorData));
	memset(&sn1, 0, sizeof(SensorData));
}

void MidasManager::CheckPacket(int nID)
{
	int i,j;
	BYTE aByte;

	CCommThread *pc;
	if(nID ==0) pc = &m_ComuPort;
	else		pc = &m_ComuPort1;


	int iSize =  pc->m_QueueRead.GetSize(); 

/*	if(iSize<2)
	{
		m_ComuPort.m_QueueRead.Clear();
		return;
	}*/

	int acc1,acc2, acc3, IR1, IR2, IR3;
	pc->m_QueueRead.GetByte(&aByte);
	acc1 = aByte;

	pc->m_QueueRead.GetByte(&aByte);
	acc2 = aByte;


	pc->m_QueueRead.GetByte(&aByte);
	acc3 = aByte;



	pc->m_QueueRead.Clear();


	CString buf;
	buf.Format("%d]%d_%d,%d,%d", nID,iSize, acc1, acc2, acc3);
	pv->DbgSerial(buf);


	return;
////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//m_ComuPort.m_QueueRead.GetByte(&aByte);

	CString concat=buf,tmp;
	BYTE arr1[20];
	if(iSize>20) iSize = 20;
	for(i=0; i<iSize; i++)
	{
		m_ComuPort.m_QueueRead.GetByte(&aByte);
		arr1[i] = aByte;
		tmp.Format("%d,",arr1[i]);
		concat += tmp;

	}
	
	if(iSize==5)
	{
		pv->DbgSerial(concat);


	}

	//if(aByte == 254 || aByte == 255) // NODE 1
	{



	}


	return;

	if(aByte == 254) // NODE 1
	{
		// Get X-position
		m_ComuPort.m_QueueRead.GetByte(&aByte);
		int b0 = aByte;
		m_ComuPort.m_QueueRead.GetByte(&aByte);
		int b1 = aByte;
		m_ComuPort.m_QueueRead.GetByte(&aByte);
		int b2 = aByte;

		m_ComuPort.m_QueueRead.GetByte(&aByte);
		int b3 = aByte;

		buf.Format("%c%c%c", b0,b1,b2);


		memset(&sn0, 0, sizeof(SensorData));
		sn0.accX = b0;
		sn0.accY = b1;
		sn0.accZ = b2;
		sn0.IRs = b3;	
		//m_ComuPort.m_QueueRead.Clear();	


		//Update array

		ShiftWithNew(n0_AccX, (int)sn0.accX, kHistory);
		ShiftWithNew(n0_AccY, (int)sn0.accY, kHistory);
		ShiftWithNew(n0_AccZ, (int)sn0.accZ, kHistory);
		ShiftWithNew(n0_IRs, (int)sn0.IRs, kHistory);

		pv->DbgSensor0();



	}
	else if(aByte == 255) // NODE 2
	{
		// Get X-position
		m_ComuPort.m_QueueRead.GetByte(&aByte);
		int b0 = aByte;
		m_ComuPort.m_QueueRead.GetByte(&aByte);
		int b1 = aByte;
		m_ComuPort.m_QueueRead.GetByte(&aByte);
		int b2 = aByte;

		m_ComuPort.m_QueueRead.GetByte(&aByte);
		int b3 = aByte;

		buf.Format("%c%c%c", b0,b1,b2);


		memset(&sn1, 0, sizeof(SensorData));
		sn1.accX = b0;
		sn1.accY = b1;
		sn1.accZ = b2;
		sn1.IRs = b3;	
		//m_ComuPort.m_QueueRead.Clear();	
		
		//Update array
		ShiftWithNew(n1_AccX, (int)sn1.accX, kHistory);
		ShiftWithNew(n1_AccY, (int)sn1.accY, kHistory);
		ShiftWithNew(n1_AccZ, (int)sn1.accZ, kHistory);
		ShiftWithNew(n1_IRs, (int)sn1.IRs, kHistory);

		pv->DbgSensor1();
		
	}
}
