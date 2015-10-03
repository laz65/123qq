#if !defined(AFX_VNESENIE_H__E5D6D1BC_F2D6_4C9E_8A14_ED4A387A8184__INCLUDED_)
#define AFX_VNESENIE_H__E5D6D1BC_F2D6_4C9E_8A14_ED4A387A8184__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Vnesenie.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVnesenie dialog

class CVnesenie : public CDialog
{
// Construction
public:
	CVnesenie(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CVnesenie)
	enum { IDD = IDD_VNESENIE };
	CEdit	m_Vness;
	CString sTitle;
	int		m_KopSum;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVnesenie)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CVnesenie)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VNESENIE_H__E5D6D1BC_F2D6_4C9E_8A14_ED4A387A8184__INCLUDED_)
