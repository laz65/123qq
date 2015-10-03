#if !defined(AFX_PASSWDLG_H__5AC38FB6_84C4_11D4_945F_0050044D962D__INCLUDED_)
#define AFX_PASSWDLG_H__5AC38FB6_84C4_11D4_945F_0050044D962D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PasswDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPasswDlg dialog

class CPasswDlg : public CDialog
{
// Construction
public:
	CPasswDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPasswDlg)
	enum { IDD = IDD_PSWDIALOG };
	CEdit	m_Psw;
	CString	m_Password;
	UINT	m_Id;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPasswDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPasswDlg)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PASSWDLG_H__5AC38FB6_84C4_11D4_945F_0050044D962D__INCLUDED_)
