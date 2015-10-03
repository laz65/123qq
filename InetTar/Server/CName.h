#include "afxwin.h"
#if !defined(AFX_CNAME_H__F61D5BC5_CAA3_11D4_82EA_0050044D962D__INCLUDED_)
#define AFX_CNAME_H__F61D5BC5_CAA3_11D4_82EA_0050044D962D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CName.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCName dialog

class CCName : public CDialog
{
// Construction
public:
	CCName(CWnd* pParent = NULL);   // standard constructor
	CString sTitle;

// Dialog Data
	//{{AFX_DATA(CCName)
	enum { IDD = IDD_NAMECOMPUTER };
	CEdit	m_NameEdit;
	CString	m_NameEditVal;
	CComboBox m_CmStat;
	int m_CmStatVal;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCName)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCName)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNAME_H__F61D5BC5_CAA3_11D4_82EA_0050044D962D__INCLUDED_)
