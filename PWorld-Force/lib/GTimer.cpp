// GTimer.cpp : implementation file
//

#include "stdafx.h"
#include "GTimer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGTimer

IMPLEMENT_DYNCREATE(CGTimer, CWinThread)

CGTimer::CGTimer()
{
	bRun	= FALSE;
}

CGTimer::~CGTimer()
{
}

BOOL CGTimer::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CGTimer::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CGTimer, CWinThread)
	//{{AFX_MSG_MAP(CGTimer)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGTimer message handlers
void CGTimer::Init(CWnd *p)
{
	pParentWnd	= p;
	bRun	= TRUE;
	CreateThread();
}

void CGTimer::Close()
{
	bRun	= FALSE;
	m_event.SetEvent();
	::WaitForSingleObject( m_hThread,INFINITE);
}

void CGTimer::BeginRun()
{
	m_tm.Begin();
}

int CGTimer::EndRun()
{
	m_event.Lock();
	ExitThread(0);
	return 0;
}

int CGTimer::Run() 
{
	BeginRun();
	
	while(bRun)
	{
		//m_tm.End();	

	}

	return EndRun();	
}
