#if !defined(AFX_STUD_H__068B1D06_2A50_459D_A879_6242FE656B53__INCLUDED_)
#define AFX_STUD_H__068B1D06_2A50_459D_A879_6242FE656B53__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Stud.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStud dialog

class CStud : public CDialog
{
// Construction
public:
	CStud(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStud)
	enum { IDD = IDD_STUDENT };
	CEdit	m_num;
	CEdit	m_fio;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStud)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStud)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STUD_H__068B1D06_2A50_459D_A879_6242FE656B53__INCLUDED_)
