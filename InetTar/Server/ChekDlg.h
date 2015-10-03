#include "afxwin.h"
#if !defined(AFX_CHEKDLG_H__A9DDC040_4876_4908_9A0A_459CC0521952__INCLUDED_)
#define AFX_CHEKDLG_H__A9DDC040_4876_4908_9A0A_459CC0521952__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChekDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ChekDlg dialog

class ChekDlg : public CDialog
{
// Construction
public:
	ChekDlg(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(ChekDlg)
	enum { IDD = IDD_CHEK };
	CComboBox	m_doplist;
	CStatic	m_sum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ChekDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ChekDlg)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSelchangeDopusl();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeDopkol();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	void SetTarif(int iPos);
	float dTarif;
	char cCodeInfo[100];
	int iCodeUsl;
	int iID;
	// 08.12.2009 код ставки налога
	int iRfRate;
	// 28.12.2009
	int iTarType;
	POSITION pos;
	hDopusl tempusl;
public:
	CEdit m_cePriem;
	CStatic m_csSdacha;
	CStatic m_tar;
	afx_msg void OnEnChangePriem();
	CEdit m_cntusl;
	CButton m_check1;
	long SumOpl;
	CStatic m_TarTypeInfo;
	//int m_DopKol;
	afx_msg void OnBnClickedCheck1();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHEKDLG_H__A9DDC040_4876_4908_9A0A_459CC0521952__INCLUDED_)
