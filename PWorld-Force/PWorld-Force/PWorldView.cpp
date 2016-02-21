// PWorldView.cpp : implementation of the CPWorldView class
//

#include "stdafx.h"
#include "PWorld.h"

#include "PWorldDoc.h"
#include "PWorldView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
CPWorldView *pv;
/////////////////////////////////////////////////////////////////////////////
// CPWorldView

IMPLEMENT_DYNCREATE(CPWorldView, CFormView)

BEGIN_MESSAGE_MAP(CPWorldView, CFormView)
	//{{AFX_MSG_MAP(CPWorldView)
	ON_BN_CLICKED(IDC_BUTTON1, OnInitDev)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPWorldView construction/destruction

CPWorldView::CPWorldView()
	: CFormView(CPWorldView::IDD)
{
	//{{AFX_DATA_INIT(CPWorldView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CPWorldView::~CPWorldView()
{
}

void CPWorldView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPWorldView)
	DDX_Control(pDX, IDC_CHECK1, m_chk_fill);
	DDX_Control(pDX, IDC_STATIC3, m_info3);
	DDX_Control(pDX, IDC_STATIC2, m_info2);
	DDX_Control(pDX, IDC_EDIT7, m_edit_angle);
	DDX_Control(pDX, IDC_EDIT6, m_model_id);
	DDX_Control(pDX, IDC_EDIT4, m_edit_vp);
	DDX_Control(pDX, IDC_EDIT3, m_edit_pm);
	DDX_Control(pDX, IDC_EDIT2, m_edit_mm);
	DDX_Control(pDX, IDC_EDIT1, m_edit_proxyform);
	DDX_Control(pDX, IDC_STATIC1, m_info1);
	//}}AFX_DATA_MAP
}

BOOL CPWorldView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}



void CPWorldView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();


	m_edit_proxyform.PutLine("Init the device");
	m_edit_angle.SetValued(0);
	int w,h;
	w	= 800;	h = 600;
	//w	= 500;	h = 500;

	m_wnd.Create(NULL,"",WS_CHILD|WS_VISIBLE,CRect(0,0,w,h),this,0);
	//pGL->GLInit(w,h);

	m_model_id.SetValued(0);
	m_chk_fill.SetCheck(TRUE);
	pv = this;

}



//// Display the proxy transform in world coordinates.
void CPWorldView::SetProxyForm(double *m)
{
	m_edit_proxyform.Reset();

	CString buf;
	int i;
	for(i=0; i<4; i++)
	{
		buf.Format("%.2f %.2f %.2f %.2f", m[4*0+i], m[4*1+i], m[4*2+i], m[4*3+i]);
		m_edit_proxyform.PutLine(buf);
	}

}

void CPWorldView::DispMM(double *m)
{
	m_edit_mm.Reset();

	CString buf;
	int i;
	for(i=0; i<4; i++)
	{
		buf.Format("%.2f %.2f %.2f %.2f", m[4*0+i], m[4*1+i], m[4*2+i], m[4*3+i]);
		m_edit_mm.PutLine(buf);
	}

}

void CPWorldView::DispPM(double *m)
{
	m_edit_pm.Reset();

	CString buf;
	int i;
	for(i=0; i<4; i++)
	{
		buf.Format("%.2f %.2f %.2f %.2f", m[4*0+i], m[4*1+i], m[4*2+i], m[4*3+i]);
		m_edit_pm.PutLine(buf);
	}
}
void CPWorldView::DispVP(int *m)
{
	m_edit_vp.Reset();

	CString buf;
	
	{
		buf.Format("%d %d %d %d", m[0], m[1], m[2], m[3]);
		m_edit_vp.PutLine(buf);
	}
}

void CPWorldView::dbg(int uID, LPCTSTR lpFmt,...)
{
	va_list	marker;
	va_start( marker,lpFmt );
	char text[1000]={0,};
	
	vsprintf( text,lpFmt,marker);
	va_end( marker );

	CString ret(text);

	if(uID==0)
		m_info1.dbg(ret);

	else if(uID==1)
		m_info2.dbg(ret);
	else if(uID==2)
		m_info3.dbg(ret);
	/*
	else if(uID==1)
		m_info2.dbg(ret);
	
	else if(uID==3)
		m_info4.dbg(ret);

*/

}
/////////////////////////////////////////////////////////////////////////////
// CPWorldView printing

BOOL CPWorldView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPWorldView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPWorldView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CPWorldView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CPWorldView diagnostics

#ifdef _DEBUG
void CPWorldView::AssertValid() const
{
	CFormView::AssertValid();
}

void CPWorldView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CPWorldDoc* CPWorldView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPWorldDoc)));
	return (CPWorldDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPWorldView message handlers

BOOL CPWorldView::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	if(pMsg->message==WM_KEYDOWN)
	{

		if(pMsg->wParam==VK_HOME)
		{
			Dbg("PreTranslateMessage: (VK_HOME) %d", pMsg->wParam);
			pGL->pCamera->InitCam();
			return 1;
		}

		else if(pMsg->wParam==VK_UP)
		{
			Dbg("PreTranslateMessage: (VK_UP) %d", pMsg->wParam);
			int ang = m_edit_angle.GetValued();
			m_edit_angle.SetValued(ang+1);
			return 1;
		}

		else if(pMsg->wParam==VK_DOWN)
		{
			Dbg("PreTranslateMessage: (VK_DOWN) %d", pMsg->wParam);
			int ang = m_edit_angle.GetValued();
			m_edit_angle.SetValued(ang-1);
			return 1;
		}


		else if(pMsg->wParam==VK_INSERT)
		{
			Dbg("PreTranslateMessage: (VK_INSERT) %d", pMsg->wParam);
			
			
			m_wnd.m_haptics.ToggleTakingRest();


			return 1;
		}


	}

	return CFormView::PreTranslateMessage(pMsg);
}

void CPWorldView::OnInitDev() 
{

	m_wnd.pHL->initHL();
}
