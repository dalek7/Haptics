// JGInterfaceView.cpp : implementation of the CJGInterfaceView class
//

#include "stdafx.h"
#include "JGInterface.h"

#include "JGInterfaceDoc.h"
#include "JGInterfaceView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CJGInterfaceView *pv;

/////////////////////////////////////////////////////////////////////////////
// CJGInterfaceView

IMPLEMENT_DYNCREATE(CJGInterfaceView, CFormView)

BEGIN_MESSAGE_MAP(CJGInterfaceView, CFormView)
	//{{AFX_MSG_MAP(CJGInterfaceView)
	ON_BN_CLICKED(IDC_BUTTON1, OnConnect)
	ON_BN_CLICKED(IDC_BUTTON2, OnConnect1)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJGInterfaceView construction/destruction

CJGInterfaceView::CJGInterfaceView()
	: CFormView(CJGInterfaceView::IDD)
{
	//{{AFX_DATA_INIT(CJGInterfaceView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CJGInterfaceView::~CJGInterfaceView()
{
}

void CJGInterfaceView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CJGInterfaceView)
	DDX_Control(pDX, IDC_BUTTON1, m_btn_connect);

	
	//}}AFX_DATA_MAP
}

BOOL CJGInterfaceView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CJGInterfaceView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	pv = this;

	m_dev.Create(this);

	///Create( DWORD dw,CRect rect,CWnd *p,UINT n)
	m_edit_node0.Create(WS_VISIBLE|WS_BORDER|WS_CHILD, CRect(0,0,80*2,220)+CPoint(210,70), this, 0);
	m_edit_node1.Create(WS_VISIBLE|WS_BORDER|WS_CHILD, CRect(0,0,80*2,220)+CPoint(210+170,70), this, 0);


	m_edit_serial.Create(WS_VISIBLE|WS_BORDER|WS_CHILD, CRect(0,0,80*2,220)+CPoint(210-170,70), this, 0);
	
	m_edit_command.Create(WS_VISIBLE|WS_BORDER|WS_CHILD, CRect(0,0,80*2,220)+CPoint(210+170*2,70), this, 0);

	
	


	m_edit_serial.SetReset(12);
	m_edit_node0.SetReset(12);
	m_edit_node1.SetReset(12);
	m_edit_command.SetReset(12);

	m_edit_command.PutLine("Ready..");

	m_btn_connect.SetFocus();

}



void CJGInterfaceView::DbgSensor0()
{

	SensorData *pNode = &m_dev.sn0;

	CString buf;
	buf.Format("%3d,%3d,%3d,IR%d%d%d",	pNode->accX, pNode->accY, pNode->accZ,
											(pNode->IRs & 4)/4, (pNode->IRs & 2)/2, pNode->IRs & 1);


	m_edit_node0.PutLine(buf);


}
void CJGInterfaceView::DbgSensor1()
{

	SensorData *pNode = &m_dev.sn1;


	CString buf;
	buf.Format("%3d,%3d,%3d,IR%d",	pNode->accX, pNode->accY, pNode->accZ,
											pNode->IRs & 1);


	m_edit_node1.PutLine(buf);


}


void CJGInterfaceView::DbgSerial(CString buf)
{
	m_edit_serial.PutLine(buf);
}	



/////////////////////////////////////////////////////////////////////////////
// CJGInterfaceView printing

BOOL CJGInterfaceView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CJGInterfaceView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CJGInterfaceView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CJGInterfaceView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CJGInterfaceView diagnostics

#ifdef _DEBUG
void CJGInterfaceView::AssertValid() const
{
	CFormView::AssertValid();
}

void CJGInterfaceView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CJGInterfaceDoc* CJGInterfaceView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CJGInterfaceDoc)));
	return (CJGInterfaceDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CJGInterfaceView message handlers

void CJGInterfaceView::OnConnect() 
{
	m_dev.Connect0(10, SerialManager2::B38400);
	CString str;
	str.Format("asddg");
	char* ch = str.GetBuffer(str.GetLength());
	m_dev.m_ComuPort.WriteComm((BYTE*)ch, str.GetLength());
}

void CJGInterfaceView::OnConnect1() 
{
	m_dev.Connect1(7, SerialManager2::B38400);
	/*CString str;
	str.Format("asddg");
	char* ch = str.GetBuffer(str.GetLength());
	m_dev.m_ComuPort1.WriteComm((BYTE*)ch, str.GetLength());*/
}
