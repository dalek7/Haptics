#include "StdAfx.h"
#include "ExpUtil.h"

ExpUtil::ExpUtil(void)
{
}

ExpUtil::~ExpUtil(void)
{
}



void ExpUtil::ShuffleArray(int* src, int sz)
{
	srand(time(0));
	for(int i=0; i<sz; i++)
	{
		int nPos	=  i + (rand() % (sz-i));	//Random remaining position
		int temp	= src[i]; 
		src[i]		= src[nPos]; 
		src[nPos]	= temp;
	}
}


void ExpUtil::MakeFileNameWithDateTime(CString *rtn)
{
	char dateStr[9];
	char timeStr[9];

	_strdate( dateStr); //mm/dd/yy
	_strtime(timeStr);
	CString tmp;
	tmp.Format("%s_%s",dateStr, timeStr);
	tmp.Replace(":", "");
	tmp.Replace("/", "");

	*rtn = tmp;
}


//ExpUtil::CreateFolder("../Output", TRUE);

CString ExpUtil::CreateFolder(CString name, BOOL bRelativePath)
{
	CString sub_folder;
	if(bRelativePath)
	{
		sub_folder = name+"/";
	}
	else
	{
		char buffer[MAX_PATH];
		GetModuleFileName( NULL, buffer, MAX_PATH );

		OutputDebugString(buffer);
		CString loc = GetPath(buffer);
		sub_folder = loc+"/"+name+"/";
	}
	
     if(CreateDirectory( sub_folder, NULL )==ERROR_ALREADY_EXISTS)
     {
          OutputDebugString("Output folder already exists.");
     }
     else
          OutputDebugString("Output folder has been created !!");


	 OutputDebugString(sub_folder);
     return sub_folder;
}



CString ExpUtil::GetPath( CString path)
{
	CString ret;

	int max=0;
	int i=0;
	char *buf = path.GetBuffer( path.GetLength() );
	
	while(1)
	{
		if ( buf[i]==0)	break;
		if ( buf[i]=='\\' || buf[i]=='/')	max	=i;
		i++;
	}

	ret	= buf;
	ret	= ret.Left(max);

	return ret;
}
