//{{AFX_INCLUDES()
#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_COMSETUPDLG_H__5AC38FB7_84C4_11D4_945F_0050044D962D__INCLUDED_)
#define AFX_COMSETUPDLG_H__5AC38FB7_84C4_11D4_945F_0050044D962D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComSetupDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CComSetupDlg dialog

class CComSetupDlg : public CDialog
{
// Construction
public:
	CComSetupDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CComSetupDlg)
	enum { IDD = IDD_SETUPDIALOG };
	CListCtrl	m_Grid;
	CButton	m_CheckPipes;
	CButton	m_CheckInet;
	CButton m_UseRF2160;
	CButton	m_CheckExplorer;
	CEdit	m_GateWayName;
	CEdit	m_UnLock;
	CEdit	m_Lock;
	CEdit	m_SharePath;
	CEdit	m_INomer;
	CEdit	m_IName;
	CEdit	m_BillPath;
	CEdit	m_CountComp;
	CSpinButtonCtrl	m_CompSpin;
	CButton	m_CassaCheck;
	CButton	m_Both;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComSetupDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CComSetupDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnCassacheck();
	afx_msg void OnChangeCountcomp();
	afx_msg void OnDblclkGrid(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemdblclickGrid(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	hSetup m_TempSetup;	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMSETUPDLG_H__5AC38FB7_84C4_11D4_945F_0050044D962D__INCLUDED_)
