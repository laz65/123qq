//{{AFX_INCLUDES()
#include "msflexgrid.h"
#include "StdAfx.h"	// Added by ClassView
//}}AFX_INCLUDES
#if !defined(AFX_CLIENTRASCHET_H__83C6A736_A5BE_11D4_9482_0050044D962D__INCLUDED_)
#define AFX_CLIENTRASCHET_H__83C6A736_A5BE_11D4_9482_0050044D962D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientRaschet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CClientRaschet dialog

class CClientRaschet : public CDialog
{
// Construction
public:
	CompInfo * Comp;
	long AllZalog;
	long PriemCops;
	CClientRaschet(CWnd* pParent = NULL);   // standard constructor
private:
	int 	iCops;
	char LogBuffer[500];
// Dialog Data
	//{{AFX_DATA(CClientRaschet)
	enum { IDD = IDD_RASCHDIALOG };
	CStatic	m_StaticOst;
	CString	m_InUseVal;
	CString	m_ISPTimeVal;
	CString	m_OstatokVal;
	CString	m_ZalogVal;
	CString	m_CompChar;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientRaschet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CClientRaschet)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CString m_sCol;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTRASCHET_H__83C6A736_A5BE_11D4_9482_0050044D962D__INCLUDED_)
