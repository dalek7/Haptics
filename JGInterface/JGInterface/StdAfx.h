// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__EDAB9A37_A01F_4BC8_90B2_6AB00F70BB8A__INCLUDED_)
#define AFX_STDAFX_H__EDAB9A37_A01F_4BC8_90B2_6AB00F70BB8A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "Constants.h"


typedef struct __SensorData 
{
	BYTE accX;
	BYTE accY;
	BYTE accZ;

	BYTE IRs;

} SensorData;


#define DD_DBG
#include "../lib/DBG.h"
#include "../lib/ddMacros.h"
#include "../lib/ddmath.h"
#include <afxtempl.h>



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__EDAB9A37_A01F_4BC8_90B2_6AB00F70BB8A__INCLUDED_)
