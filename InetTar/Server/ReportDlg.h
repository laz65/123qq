//{{AFX_INCLUDES()
#include "msflexgrid.h"
#include "afxwin.h"
//}}AFX_INCLUDES
#if !defined(AFX_REPORTDLG_H__08FDE003_889E_11D4_9462_0050044D962D__INCLUDED_)
#define AFX_REPORTDLG_H__08FDE003_889E_11D4_9462_0050044D962D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReportDlg dialog

class CReportDlg : public CDialog
{
// Construction
public:
	CReportDlg(CWnd* pParent = NULL);   // standard constructor
	// 1 - лог, 2 - оплата
	int iRepType;
// Dialog Data
	//{{AFX_DATA(CReportDlg)
	enum { IDD = IDD_REPORTDLG };
	CListCtrl	m_Grid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReportDlg)
	afx_msg void OnPrint();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedShow();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool FormRepInetLog();
	bool FormRepPayLog();
	char cRepFl[200];
	char cExlRep[200];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTDLG_H__08FDE003_889E_11D4_9462_0050044D962D__INCLUDED_)
