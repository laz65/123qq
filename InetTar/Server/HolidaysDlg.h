#if !defined(AFX_HOLIDAYSDLG_H__81003771_ADB3_11D6_8BC7_0050044D962D__INCLUDED_)
#define AFX_HOLIDAYSDLG_H__81003771_ADB3_11D6_8BC7_0050044D962D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HolidaysDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHolidaysDlg dialog

class CHolidaysDlg : public CDialog
{
// Construction
public:
	CHolidaysDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHolidaysDlg)
	enum { IDD = IDD_HOLIDAYS };
	CEdit	m_CRem;
	CEdit	m_CDate;
	CMonthCalCtrl	m_CCal;
	CButton	m_Ins;
	CListCtrl	m_Holidays;
	CButton	m_Del;
	CTime	m_Cal;
	CString	m_Date;
	CString	m_Rem;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHolidaysDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    char BTT[300][11];
    char BTR[300][100];
    int CT;

	// Generated message map functions
	//{{AFX_MSG(CHolidaysDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCalendar(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickHolidays(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnGetdaystateCalendar(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnIns();
	afx_msg void OnDel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOLIDAYSDLG_H__81003771_ADB3_11D6_8BC7_0050044D962D__INCLUDED_)
