// JGInterfaceView.h : interface of the CJGInterfaceView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_JGINTERFACEVIEW_H__E18A808C_97AF_4642_8AF9_7B0FEFAFC40B__INCLUDED_)
#define AFX_JGINTERFACEVIEW_H__E18A808C_97AF_4642_8AF9_7B0FEFAFC40B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include "../lib/CMDEdit.h"
#include "MidasManager.h"
class CJGInterfaceView : public CFormView
{
protected: // create from serialization only
	CJGInterfaceView();
	DECLARE_DYNCREATE(CJGInterfaceView)

public:
	//{{AFX_DATA(CJGInterfaceView)
	enum { IDD = IDD_JGINTERFACE_FORM };
	CButton	m_btn_connect;
	
	
	
	
	//}}AFX_DATA

// Attributes
public:
	CJGInterfaceDoc* GetDocument();


	MidasManager m_dev;

// Operations
public:


	void DbgSerial(CString);
	void DbgSensor0();
	void DbgSensor1();


	CCMDEdit	m_edit_node0;
	CCMDEdit	m_edit_node1;

	CCMDEdit	m_edit_serial;

	CCMDEdit	m_edit_command;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJGInterfaceView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
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
	virtual ~CJGInterfaceView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CJGInterfaceView)
	afx_msg void OnConnect();
	afx_msg void OnConnect1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in JGInterfaceView.cpp
inline CJGInterfaceDoc* CJGInterfaceView::GetDocument()
   { return (CJGInterfaceDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JGINTERFACEVIEW_H__E18A808C_97AF_4642_8AF9_7B0FEFAFC40B__INCLUDED_)
