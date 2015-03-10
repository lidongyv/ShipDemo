// ShipDemo.h : main header file for the SHIPDEMO application
//

#if !defined(AFX_SHIPDEMO_H__9939D465_C570_11D4_A7CC_EA7F379C1C5F__INCLUDED_)
#define AFX_SHIPDEMO_H__9939D465_C570_11D4_A7CC_EA7F379C1C5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CShipDemoApp:
// See ShipDemo.cpp for the implementation of this class
//

#define GAME_WIDTH		500
#define GAME_HEIGHT		300

class CShipDemoApp : public CWinApp
{
public:
	CShipDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShipDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CShipDemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHIPDEMO_H__9939D465_C570_11D4_A7CC_EA7F379C1C5F__INCLUDED_)
