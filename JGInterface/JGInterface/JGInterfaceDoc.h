// JGInterfaceDoc.h : interface of the CJGInterfaceDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_JGINTERFACEDOC_H__2C41E644_4C3F_4429_89CE_F0AFD83413BF__INCLUDED_)
#define AFX_JGINTERFACEDOC_H__2C41E644_4C3F_4429_89CE_F0AFD83413BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CJGInterfaceDoc : public CDocument
{
protected: // create from serialization only
	CJGInterfaceDoc();
	DECLARE_DYNCREATE(CJGInterfaceDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJGInterfaceDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CJGInterfaceDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CJGInterfaceDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JGINTERFACEDOC_H__2C41E644_4C3F_4429_89CE_F0AFD83413BF__INCLUDED_)
