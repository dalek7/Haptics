#pragma once


// ddEdit

class ddEdit : public CEdit
{
	DECLARE_DYNAMIC(ddEdit)

public:
	ddEdit();
	virtual ~ddEdit();

public:
	BOOL Create( DWORD dw,CRect rect,CWnd *p,UINT n);
	void SetValuef(float v);
	float GetValuef();
	
	void SetValued(int v);
	int GetValued();

	
	CString GetBuffer();

	BOOL IsEmpty();

	void	dbg(LPCTSTR,...);

// Overrides
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

protected:
	CFont	m_font;



protected:
	//{{AFX_MSG(ddEdit)
	
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);	

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


