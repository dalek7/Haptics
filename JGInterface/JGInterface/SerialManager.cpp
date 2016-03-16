// SerialManager.cpp : implementation file
//

#include "stdafx.h"
#include "SerialManager.h"

#include "JGInterfaceDoc.h"
#include "JGInterfaceView.h"


extern CJGInterfaceView *pv;


HWND hCommWnd;

// SerialManager

IMPLEMENT_DYNAMIC(SerialManager, CWnd)

SerialManager::SerialManager()
{
	
	portnum			= -1;
	tcnt0			= 0;
}

SerialManager::~SerialManager()
{
}


void SerialManager::Create(CWnd *pWnd)
{
	CWnd::Create( NULL,"",WS_CHILD,CRect(0,0,1,1),pWnd,0);//|WS_VISIBLE|WS_BORDER
	
}


BEGIN_MESSAGE_MAP(SerialManager, CWnd)
	ON_MESSAGE(WM_COMM_READ , OnCommunication)
	ON_WM_CREATE()
END_MESSAGE_MAP()



void SerialManager::getPortLists()
{
	EnumerateSerialPorts(ports);
}


void SerialManager::fireL(CString str)
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
void SerialManager::fire(BYTE c, BOOL visible)
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


BOOL SerialManager::isConnected()
{
	return m_ComuPort.m_bConnected;
}


void SerialManager::Connect(int nPort, int baudRate, int nID)//int _portnum
{
	

	if(!m_ComuPort.m_bConnected)
	{
		if(nPort <1)
			portnum = ports.ElementAt(ports.GetSize()-1 );
		else
			portnum = nPort ; 

		if(m_ComuPort.OpenPort(portnum-1,baudRate,3,0,0))
		{

			Dbg("COM%d opened", portnum);

			CString buf;
			buf.Format("COM%d opened", portnum);
			pv->DbgSerial(buf);
		
		}
	}
	else
	{
		m_ComuPort.ClosePort();
		Dbg("Serial Closed");

		pv->DbgSerial("Serial Closed");
		
		
	}	

	m_ComuPort.nID = nID;

}




// SerialManager message handlers


long SerialManager::OnCommunication(WPARAM wParam, LPARAM lParam)
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


int SerialManager::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	hCommWnd = m_hWnd;
	getPortLists();

	return 0;
}




float SerialManager::jegob(float arg)
{
	return arg*arg;
}



void SerialManager::GetDevStatus(CString* str)
{
	*str = status;
}


void SerialManager::SetStatus( LPCTSTR lpFmt,... )
{

	va_list	marker;
	va_start( marker,lpFmt );
	char text[1000]={0,};
	
	vsprintf( text,lpFmt,marker);
	va_end( marker );

	CString str(text);


	status = str;
}



void SerialManager::dbg(LPCTSTR lpFmt,... )
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
