#pragma once

class ExpUtil
{
public:
	ExpUtil(void);
	~ExpUtil(void);



public:
	static void		ShuffleArray(int* src, int sz);
	static void		MakeFileNameWithDateTime(CString *rtn);
	static CString	CreateFolder(CString name, BOOL bRelativePath=FALSE);

	static CString	GetPath(CString);

};
