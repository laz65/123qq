#if !defined(AFX_TARIFDLG_H__AD256736_87A8_11D4_9461_0050044D962D__INCLUDED_)
#define AFX_TARIFDLG_H__AD256736_87A8_11D4_9461_0050044D962D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TarifDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTarifDlg dialog

class CTarifDlg : public CDialog
{
// Construction
public:
	CTarifDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTarifDlg)
	enum { IDD = IDD_TARIFDLG };
	CEdit	m_CurNds;
	CEdit	m_TarifCtrl8;
	CEdit	m_TarifCtrl7;
	CEdit	m_TarifCtrl6;
	CEdit	m_TarifCtrl5;
	CEdit	m_TarifCtrl4;
	CEdit	m_TarifCtrl3;
	CEdit	m_TarifCtrl2;
	CEdit	m_TarifCtrl1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTarifDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTarifDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeTarif1();
	afx_msg void OnEnChangeCurnds();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TARIFDLG_H__AD256736_87A8_11D4_9461_0050044D962D__INCLUDED_)
