#if !defined(AFX_GLWND_H__C1E73FCB_F6E5_480D_A88E_0299BA5A1848__INCLUDED_)
#define AFX_GLWND_H__C1E73FCB_F6E5_480D_A88E_0299BA5A1848__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GLWnd.h : header file
//

#include "../lib/3d/dhVector.h"
#include "../lib/ddGL.h"
#include "../lib/vwO.h"
#include "../lib/vwPrimitives.h"

#include "../lib/Elapsed.h"

#include "ProcHaptics.h"


/////////////////////////////////////////////////////////////////////////////
// CGLWnd window

class CGLWnd : public CWnd
{
// Construction
public:
	CGLWnd();

// Attributes
public:
	void	Draw();
	HDC		m_hDC;			
	HGLRC	m_hRC;			
	int		tcnt0;
// Operations
public:

	ddGL	m_gl;


	vwO	m_obj;
	float tangle;

	

	void initScene();

	void updateWorkspace();
	void drawSceneHaptics();
	void drawSceneGraphics();
	void drawCursor();

	int objID;

	

	ProcHaptics	m_haptics;
	ProcHaptics *pHL;
	
	


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGLWnd)
	public:
	
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGLWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGLWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GLWND_H__C1E73FCB_F6E5_480D_A88E_0299BA5A1848__INCLUDED_)
