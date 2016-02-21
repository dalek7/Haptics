#if !defined(AFX_GTIMER_H__66558B38_5476_431E_9B0D_77858C69C884__INCLUDED_)
#define AFX_GTIMER_H__66558B38_5476_431E_9B0D_77858C69C884__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GTimer.h : header file
//

#include <afxmt.h>
#include "elapsed.h"
/////////////////////////////////////////////////////////////////////////////
// CGTimer thread

class CGTimer : public CWinThread
{
	DECLARE_DYNCREATE(CGTimer)

public:
	CGTimer();           // protected constructor used by dynamic creation
	~CGTimer();

// Attributes
public:
	BOOL	bRun;
	void	Init(CWnd*);
	void	Close();

	CElapsed	m_tm;
	CEvent		m_event;
	CWnd		*pParentWnd;

	void		BeginRun();
	int			EndRun();
	double		GetTime()	{	return m_tm.End();	}


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGTimer)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGTimer)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GTIMER_H__66558B38_5476_431E_9B0D_77858C69C884__INCLUDED_)
