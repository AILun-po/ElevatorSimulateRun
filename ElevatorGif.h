// ElevatorGif.h : main header file for the ELEVATORGIF application
//

#if !defined(AFX_ELEVATORGIF_H__02E9BE03_7325_4B22_919E_F7BA0EC86EB7__INCLUDED_)
#define AFX_ELEVATORGIF_H__02E9BE03_7325_4B22_919E_F7BA0EC86EB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CElevatorGifApp:
// See ElevatorGif.cpp for the implementation of this class
//

class CElevatorGifApp : public CWinApp
{
public:
	CElevatorGifApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CElevatorGifApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CElevatorGifApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ELEVATORGIF_H__02E9BE03_7325_4B22_919E_F7BA0EC86EB7__INCLUDED_)
