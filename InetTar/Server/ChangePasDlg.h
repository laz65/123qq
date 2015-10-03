#if !defined(AFX_CHANGEPASDLG_H__1F2631D1_A510_11D6_8BBA_0050044D962D__INCLUDED_)
#define AFX_CHANGEPASDLG_H__1F2631D1_A510_11D6_8BBA_0050044D962D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChangePasDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChangePasDlg dialog

class CChangePasDlg : public CDialog
{
// Construction
public:
	unsigned char m_Hash[16];
	bool m_First;
	CChangePasDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChangePasDlg)
	enum { IDD = IDD_CHANGEPAS };
	CEdit	m_Rep;
	CEdit	m_Old;
	CEdit	m_New;
	CString	m_PwdNew;
	CString	m_PwdOld;
	CString	m_PwdRep;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChangePasDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChangePasDlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANGEPASDLG_H__1F2631D1_A510_11D6_8BBA_0050044D962D__INCLUDED_)
