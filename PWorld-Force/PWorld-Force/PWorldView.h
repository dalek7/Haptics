// PWorldView.h : interface of the CPWorldView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PWORLDVIEW_H__C61FCEF7_C604_4AE1_BAEF_9A3595707E13__INCLUDED_)
#define AFX_PWORLDVIEW_H__C61FCEF7_C604_4AE1_BAEF_9A3595707E13__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GLWnd.h"
#include "../lib/ddStatic.h"
#include "../lib/CMDEdit.h"
#include "../lib/ddEdit.h"

class CPWorldView : public CFormView
{
protected: // create from serialization only
	CPWorldView();
	DECLARE_DYNCREATE(CPWorldView)

public:
	CGLWnd m_wnd;
	
	void dbg(int uID, LPCTSTR lpFmt,...);
	//{{AFX_DATA(CPWorldView)
	enum { IDD = IDD_PWORLD_FORM };
	CButton	m_chk_fill;
	ddStatic	m_info3;
	ddStatic	m_info2;
	ddEdit	m_edit_angle;
	ddEdit	m_model_id;
	CCMDEdit	m_edit_vp;
	CCMDEdit	m_edit_pm;
	CCMDEdit	m_edit_mm;
	CCMDEdit	m_edit_proxyform;
	ddStatic	m_info1;
	//}}AFX_DATA

// Attributes
public:
	CPWorldDoc* GetDocument();

// Operations
public:
	void SetProxyForm(double *m);

	void DispMM(double *mm);
	void DispPM(double *pm);
	void DispVP(int *vp);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPWorldView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPWorldView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPWorldView)
	afx_msg void OnInitDev();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PWorldView.cpp
inline CPWorldDoc* CPWorldView::GetDocument()
   { return (CPWorldDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PWORLDVIEW_H__C61FCEF7_C604_4AE1_BAEF_9A3595707E13__INCLUDED_)
