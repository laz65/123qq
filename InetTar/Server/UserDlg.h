#if !defined(AFX_USERDLG_H__7C393C44_AA94_11D6_8BC5_0050044D962D__INCLUDED_)
#define AFX_USERDLG_H__7C393C44_AA94_11D6_8BC5_0050044D962D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUserDlg dialog

class CUserDlg : public CDialog
{
// Construction
public:
	void SetManage(bool State);
	void SetState(bool State);
	CUserDlg(CWnd* pParent = NULL);   // standard constructor
	bool m_Add;


// Dialog Data
	//{{AFX_DATA(CUserDlg)
	enum { IDD = IDD_USER };
	CEdit	m_ID;
	int		m_Super;
	int     m_User;
	UINT	m_Id;
	CString	m_Fio;
	BOOL	m_Com;
	BOOL	m_Change;
	BOOL	m_Tarif;
	CString	m_Creator;
	BOOL	m_Block;
	BOOL	m_Holiday;
	BOOL	m_InetOff;
	BOOL	m_InetOn;
	BOOL	m_Manage;
	BOOL	m_Reboot;
	BOOL	m_Shutdown;
	BOOL	m_Unblock;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUserDlg)
	afx_msg void OnAdmin();
	afx_msg void OnUser();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnManage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERDLG_H__7C393C44_AA94_11D6_8BC5_0050044D962D__INCLUDED_)
