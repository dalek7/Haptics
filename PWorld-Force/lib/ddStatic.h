#pragma once


// ddStatic

class ddStatic : public CStatic
{
	DECLARE_DYNAMIC(ddStatic)

public:
	ddStatic();
	virtual ~ddStatic();

	BOOL Create(CString str, DWORD dw,CRect rect,CWnd *p,UINT n, int fontSize = 90);

public:
	void	dbg(LPCTSTR,...);
	BOOL	IsIn(CPoint);
	void	GetCursorPtInObjCoord(CPoint*);
	
	void	SetFontSize(int sz);
	int		sz_font;
public:
	CFont	m_font;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


