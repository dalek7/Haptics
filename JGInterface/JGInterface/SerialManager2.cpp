// SerialManager2.cpp : implementation file
//

#include "stdafx.h"
#include "SerialManager2.h"

#include "JGInterfaceDoc.h"
#include "JGInterfaceView.h"

extern CJGInterfaceView *pv;

HWND hCommWnd;

// SerialManager2

IMPLEMENT_DYNAMIC(SerialManager2, CWnd)

SerialManager2::SerialManager2()
{
	
	portnum			= -1;
	tcnt0			= 0;
}

SerialManager2::~SerialManager2()
{
}


void SerialManager2::Create(CWnd *pWnd)
{
	CWnd::Create( NULL,"",WS_CHILD,CRect(0,0,1,1),pWnd,0);//|WS_VISIBLE|WS_BORDER
	
}


BEGIN_MESSAGE_MAP(SerialManager2, CWnd)
	ON_MESSAGE(WM_COMM_READ , OnCommunication)
	ON_WM_CREATE()
END_MESSAGE_MAP()



void SerialManager2::getPortLists()
{
	EnumerateSerialPorts(ports);
}


void SerialManager2::fireL(CString str)
{

	char* ch = str.GetBuffer(str.GetLength());

	m_ComuPort.WriteComm((BYTE*)ch, str.GetLength());


	/*
	for(int i=0; i<str.GetLength(); i++)
	{
		BYTE ch = (int) str.GetAt(i);
		fire(ch,TRUE);

		//Sleep(1);
	}
	*/

}
void SerialManager2::fire(BYTE c, BOOL visible)
{
	if(m_ComuPort.m_bConnected && c>=0 && c <=255)
	{
		m_ComuPort.WriteComm(&c, 1);
		
		//CString buf;
		//buf.Format("BYTE %d ", c);
		//pWnd->dbg(buf);
		Dbg("Sending> %c (%d)", c,c);
	}
}


BOOL SerialManager2::isConnected(int nNode)
{
	if(nNode ==0)
		return bConnected0;
	else
		return bConnected1;
}


void SerialManager2::Connect0(int nPort, int baudRate, int nID)//int _portnum
{
	
	CCommThread *pcomm = &m_ComuPort;

	if(!pcomm->m_bConnected)
	{
		if(nPort <1)
			portnum = ports.ElementAt(ports.GetSize()-1 );
		else
			portnum = nPort ; 

		if(pcomm->OpenPort(portnum-1,baudRate,3,0,0))
		{

			//Dbg("COM%d opened", portnum);
			Dbg("OK Node#0 P#%d", portnum);
			CString buf;
			buf.Format("OK Node#0 P#%d", portnum);
			pv->DbgSerial(buf);
		
		}
	}
	else
	{
		pcomm->ClosePort();
		Dbg("Serial Closed");

		pv->DbgSerial("Serial Closed : #N0");
		
		
	}	

	pcomm->nID = nID;

}


void SerialManager2::Connect1(int nPort, int baudRate, int nID)//int _portnum
{
	
	CCommThread *pcomm = &m_ComuPort1;

	if(!pcomm->m_bConnected)
	{
		if(nPort <1)
			portnum = ports.ElementAt(ports.GetSize()-1 );
		else
			portnum = nPort ; 

		if(pcomm->OpenPort(portnum-1,baudRate,3,0,0))
		{

			Dbg("OK Node#1 P#%d", portnum);

			CString buf;
			buf.Format("OK Node#1 P#%d", portnum);
			pv->DbgSerial(buf);
		
		}
	}
	else
	{
		pcomm->ClosePort();
		Dbg("Serial Closed");

		pv->DbgSerial("Serial Closed");
		
		
	}	

	pcomm->nID = nID;

}


// SerialManager2 message handlers


long SerialManager2::OnCommunication(WPARAM wParam, LPARAM lParam)
{
	tcnt0++;

	CheckPacket(wParam);
	/*
	BYTE aByte;
	int iSize =  m_ComuPort.m_QueueRead.GetSize(); 

	for(int i=0; i<iSize; i++)
	{
		m_ComuPort.m_QueueRead.GetByte(&aByte);
		CheckPacket(aByte);
	}

*/

	return 0;
}


int SerialManager2::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	hCommWnd = m_hWnd;
	getPortLists();

	return 0;
}




float SerialManager2::jegob(float arg)
{
	return arg*arg;
}



void SerialManager2::GetDevStatus(CString* str)
{
	*str = status;
}


void SerialManager2::SetStatus( LPCTSTR lpFmt,... )
{

	va_list	marker;
	va_start( marker,lpFmt );
	char text[1000]={0,};
	
	vsprintf( text,lpFmt,marker);
	va_end( marker );

	CString str(text);


	status = str;
}



void SerialManager2::dbg(LPCTSTR lpFmt,... )
{
	va_list	marker;
	va_start( marker,lpFmt );
	char text[1000]={0,};
	
	vsprintf( text,lpFmt,marker);
	va_end( marker );

	CString ret(text);
	

	SetStatus(ret);

	OutputDebugString (ret);

}
