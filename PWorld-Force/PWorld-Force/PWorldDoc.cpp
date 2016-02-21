// PWorldDoc.cpp : implementation of the CPWorldDoc class
//

#include "stdafx.h"
#include "PWorld.h"

#include "PWorldDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPWorldDoc

IMPLEMENT_DYNCREATE(CPWorldDoc, CDocument)

BEGIN_MESSAGE_MAP(CPWorldDoc, CDocument)
	//{{AFX_MSG_MAP(CPWorldDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPWorldDoc construction/destruction

CPWorldDoc::CPWorldDoc()
{
	// TODO: add one-time construction code here

}

CPWorldDoc::~CPWorldDoc()
{
}

BOOL CPWorldDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPWorldDoc serialization

void CPWorldDoc::Serialize(CArchive& ar)
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
// CPWorldDoc diagnostics

#ifdef _DEBUG
void CPWorldDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPWorldDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPWorldDoc commands
