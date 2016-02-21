// PWorldDoc.h : interface of the CPWorldDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PWORLDDOC_H__EAF6E298_DC36_429E_8734_8E917D4FCA71__INCLUDED_)
#define AFX_PWORLDDOC_H__EAF6E298_DC36_429E_8734_8E917D4FCA71__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPWorldDoc : public CDocument
{
protected: // create from serialization only
	CPWorldDoc();
	DECLARE_DYNCREATE(CPWorldDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPWorldDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPWorldDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPWorldDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PWORLDDOC_H__EAF6E298_DC36_429E_8734_8E917D4FCA71__INCLUDED_)
