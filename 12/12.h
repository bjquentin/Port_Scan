// 12.h : main header file for the 12 application
//

#if !defined(AFX_12_H__BB23CCB7_D289_4F49_A691_DA592DD0F5A8__INCLUDED_)
#define AFX_12_H__BB23CCB7_D289_4F49_A691_DA592DD0F5A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMy12App:
// See 12.cpp for the implementation of this class
//

class CMy12App : public CWinApp
{
public:
	CMy12App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy12App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMy12App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_12_H__BB23CCB7_D289_4F49_A691_DA592DD0F5A8__INCLUDED_)
