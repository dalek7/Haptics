// JGInterfaceDoc.cpp : implementation of the CJGInterfaceDoc class
//

#include "stdafx.h"
#include "JGInterface.h"

#include "JGInterfaceDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJGInterfaceDoc

IMPLEMENT_DYNCREATE(CJGInterfaceDoc, CDocument)

BEGIN_MESSAGE_MAP(CJGInterfaceDoc, CDocument)
	//{{AFX_MSG_MAP(CJGInterfaceDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJGInterfaceDoc construction/destruction

CJGInterfaceDoc::CJGInterfaceDoc()
{
	// TODO: add one-time construction code here

}

CJGInterfaceDoc::~CJGInterfaceDoc()
{
}

BOOL CJGInterfaceDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CJGInterfaceDoc serialization

void CJGInterfaceDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CJGInterfaceDoc diagnostics

#ifdef _DEBUG
void CJGInterfaceDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CJGInterfaceDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CJGInterfaceDoc commands
