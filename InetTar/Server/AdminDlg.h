#if !defined(AFX_ADMINDLG_H__D7212215_64C4_4901_BDE0_FBA5760F4A27__INCLUDED_)
#define AFX_ADMINDLG_H__D7212215_64C4_4901_BDE0_FBA5760F4A27__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AdminDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAdminDlg dialog

class CAdminDlg : public CDialog
{
// Construction
public:
	void LoadUsers();
	void ChangeButtons();
	CAdminDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAdminDlg)
	enum { IDD = IDD_ADMIN };
	CTreeCtrl	m_Tree;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdminDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HTREEITEM groups[3];
	DWORD curgroup;
	CImageList img;
	// Generated message map functions
	//{{AFX_MSG(CAdminDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnAdd();
	afx_msg void OnEdit();
	afx_msg void OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnActive();
	afx_msg void OnDel();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnDblclkTree(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADMINDLG_H__D7212215_64C4_4901_BDE0_FBA5760F4A27__INCLUDED_)
