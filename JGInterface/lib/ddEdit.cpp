// ddEdit.cpp : implementation file
//

#include "stdafx.h"

#include "ddEdit.h"


// ddEdit

IMPLEMENT_DYNAMIC(ddEdit, CEdit)

ddEdit::ddEdit()
{

}

ddEdit::~ddEdit()
{
	m_font.DeleteObject();
}


BOOL ddEdit::Create( DWORD dw,CRect rect,CWnd *p,UINT n)
{
	return CEdit::Create( dw,rect,p,n);//|ES_WANTRETURN|ES_MULTILINE|ES_AUTOVSCROLL
}


CString ddEdit::GetBuffer()
{
	CString buf;
	this->GetWindowTextA(buf);
	return buf;
}


float ddEdit::GetValuef()
{
	CString buf;
	this->GetWindowTextA(buf);
	return atof(buf);
}

void ddEdit::SetValuef(float v)
{
	CString buf;
	buf.Format("%.2f", v);
	
	this->SetWindowTextA(buf);
}


void ddEdit::SetValued(int v)
{
	CString buf;
	buf.Format("%d", v);
	
	this->SetWindowTextA(buf);
}


int ddEdit::GetValued()
{
	CString buf;
	this->GetWindowTextA(buf);
	return atoi(buf);
}



int ddEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	int ret = CEdit::OnCreate(lpCreateStruct);

	m_font.CreatePointFont( 90,"Tahoma");
	SetFont(&m_font);
	
	return ret;
}



void ddEdit::dbg(LPCTSTR lpFmt,... )
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


BOOL ddEdit::PreTranslateMessage(MSG* pMsg) 
{

	if(pMsg->message==WM_KEYDOWN)
	{
		if(pMsg->wParam==VK_RETURN )//|| pMsg->wParam==VK_ESCAPE
		{

			/*
			CString buf;
			this->GetWindowTextA(buf);
			this->SetWindowTextA(buf);
			*/
			return 1;
		}
	}
	return 0;

	//return CEdit::PreTranslateMessage(pMsg);
}

LRESULT ddEdit::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	//case WM_CHAR:

	
	}
	return CEdit::WindowProc(message, wParam, lParam);
}


BOOL ddEdit::IsEmpty()
{
	CString buf;
	this->GetWindowTextA(buf);
	if(buf.GetLength() ==0)
		return TRUE;
	else
		return FALSE;

}

BEGIN_MESSAGE_MAP(ddEdit, CEdit)
	ON_WM_CREATE()	
END_MESSAGE_MAP()



// ddEdit message handlers


