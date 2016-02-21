// ddStatic.cpp : implementation file
//

#include "stdafx.h"
#include "ddStatic.h"


// ddStatic

IMPLEMENT_DYNAMIC(ddStatic, CStatic)

ddStatic::ddStatic()
{
	sz_font = 90;	
}

ddStatic::~ddStatic()
{
	m_font.DeleteObject();
}




BEGIN_MESSAGE_MAP(ddStatic, CStatic)
	ON_WM_CREATE()
END_MESSAGE_MAP()




BOOL ddStatic::Create( CString str,DWORD dw,CRect rect,CWnd *p,UINT n, int sz_font1)
{
	
	sz_font = sz_font1;

	return CStatic::Create( str, dw,rect,p,n);//|ES_WANTRETURN|ES_MULTILINE|ES_AUTOVSCROLL
}



void ddStatic::GetCursorPtInObjCoord(CPoint* mpt)
{
	CRect rc;
	GetWindowRect(&rc);
	
	CPoint r;

	r.x = mpt->x - rc.left;
	r.y = mpt->y - rc.top;
	
	/*
	if(r.x <0 || r.y <0 || r.x >= (rc.left- rc.right) || r.y >= -(rc.bottom- rc.top ))
	{
		r.x = -1;
		r.y = -1;
	}
	*/
	mpt->x = r.x;
	mpt->y = r.y;
	
}


BOOL ddStatic::IsIn(CPoint pt)
{
	CRect rc, p_rc;
	//this->GetClientRect(&rc);
	
	GetWindowRect(&rc);
	CWnd* p = GetParent();
	
	p->GetWindowRect(&p_rc);
	
	rc.left		= rc.left - p_rc.left;
	rc.top		= rc.top - p_rc.top;
	rc.right	= rc.right - p_rc.left;
	rc.bottom	= rc.bottom - p_rc.top;
	

	if(pt.x >= rc.left && pt.x < rc.right && pt.y >= rc.top && pt.y < rc.bottom)
	{
		return TRUE;

	}
	else
		return FALSE;
	//ScreenToClient(&rc);
	//ScreenToClient

}

void ddStatic::dbg(LPCTSTR lpFmt,... )
{
	va_list	marker;
	va_start( marker,lpFmt );
	char text[1000]={0,};
	
	vsprintf( text,lpFmt,marker);
	va_end( marker );

	CString ret(text);

	this->SetWindowTextA(ret);
	
	//.AddString(ret);
	//m_listbox.SetCurSel(m_listbox.GetCount()-1);
}


// ddStatic message handlers



int ddStatic::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;

	/*
	CFont	mFont;
	mFont.CreatePointFont(80, _T("MS Shell Dlg"));
	this->SetFont(&mFont);
*/

	m_font.CreatePointFont( sz_font,"Tahoma");
	
	SetFont(&m_font);

	return 0;
}
