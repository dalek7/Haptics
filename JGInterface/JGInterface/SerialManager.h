#pragma once


// SerialManager


#include "../lib/CommThread.h"
#include "../lib/enumser.h"

#include <math.h>
#define PI 3.141592

class SerialManager : public CWnd
{
	DECLARE_DYNAMIC(SerialManager)

public:
	SerialManager();
	virtual ~SerialManager();
	virtual void Create(CWnd *);

public:
	CCommThread			m_ComuPort, m_ComuPort2;
	CUIntArray ports;

public:
	static enum  {B4800=0,B9600,B14400,B19200,B38400,B56000, B57600, B115200};

	void	fire(BYTE c, BOOL visible=0);
	void	fireL(CString str);
	float	jegob(float arg);
	virtual void	ProcReceivedData(){}

	void	getPortLists();
	int		portnum;
	

	void	Connect(int nPort=0, int baudRate=B38400, int nID=0);

	virtual void	CheckPacket(int nID=0){};



	void dbg(LPCTSTR lpFmt,... );
	void	GetDevStatus(CString*);

	BOOL isConnected();

	int tcnt0;

	

private:
	CString	status;
	void SetStatus(LPCTSTR lpFmt,... );



protected:
	DECLARE_MESSAGE_MAP()

public:
// Generated message map functions
	afx_msg long OnCommunication(WPARAM wParam, LPARAM lParam); 
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};





