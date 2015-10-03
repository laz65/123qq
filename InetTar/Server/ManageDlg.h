#if !defined(AFX_MANAGEDLG_H__5ACD4FF3_B030_11D6_8BCB_0050044D962D__INCLUDED_)
#define AFX_MANAGEDLG_H__5ACD4FF3_B030_11D6_8BCB_0050044D962D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ManageDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CManageDlg dialog

class CManageDlg : public CDialog
{
// Construction
public:
	CImageList img;
	CManageDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CManageDlg)
	enum { IDD = IDD_MANAGE };
	CComboBox	m_Oper;
	CListCtrl	m_Comp;
	CButton	m_All;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CManageDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CManageDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkComp(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANAGEDLG_H__5ACD4FF3_B030_11D6_8BCB_0050044D962D__INCLUDED_)
