#include "afxcmn.h"
#include "afxwin.h"
#if !defined(AFX_NEWSEANS_H__D62DBB8D_8388_4AA0_81C4_D89067116E9A__INCLUDED_)
#define AFX_NEWSEANS_H__D62DBB8D_8388_4AA0_81C4_D89067116E9A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewSeans.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewSeans dialog

class CNewSeans : public CDialog
{
// Construction
public:
	CNewSeans(CWnd* pParent = NULL);   // standard constructor
	int tarn;
	int iComp;
	CString sTitle, sButTitle;

// Dialog Data
	//{{AFX_DATA(CNewSeans)
	enum { IDD = IDD_SETSEANS };
	CSpinButtonCtrl	m_sbM;
	CSpinButtonCtrl	m_sbH;
	CEdit	m_Hour;
	CEdit	m_Min;
	CEdit	m_ceZalog;
	double m_ceZalogVal;
	CString	m_sCol;
	CComboBox	m_cbTarNm;
	CButton	m_buNal;
	CButton	m_buIz;
	CStatic	m_csSdacha;
	CButton	m_cbNewSeans;
	CEdit m_cePriem;
	CStatic m_stTarif;
	CStatic m_stPrin;
	CStatic m_stZdach;
	//}}AFX_DATA

private:
	bool isNal;
	bool isIz;
	double dTarif;
	void SetZalogVal();
	void SetTimeVal();
	void SetSdachaVal();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewSeans)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewSeans)
	virtual BOOL OnInitDialog();
	afx_msg void OnNalRb();
	afx_msg void OnTimeRb();
	afx_msg void OnSelendokTarname();
	afx_msg void OnChangeZalog();
	afx_msg void OnNewseans();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnChangeMin();
	afx_msg void OnChangeHour();
	afx_msg void OnEnChangePriem();
	afx_msg void OnBnClickedCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedIz();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWSEANS_H__D62DBB8D_8388_4AA0_81C4_D89067116E9A__INCLUDED_)
