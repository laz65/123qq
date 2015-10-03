#include "afxwin.h"
#if !defined(AFX_NEWEDIT_H__09112F26_9BEB_11D7_9142_0050044D962D__INCLUDED_)
#define AFX_NEWEDIT_H__09112F26_9BEB_11D7_9142_0050044D962D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTarifEdit dialog

class CTarifEdit : public CDialog
{
// Construction
public:
	CTarifEdit(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTarifEdit)
	enum { IDD = IDD_TARIF_EDIT };
	CString	m_Name;
	float m_Tarif;
	int m_RfCode;
	CString	m_RfName;
	int m_RfRate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTarifEdit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTarifEdit)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit m_EdName;
	CEdit m_EdRfName;
	int m_TarType;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWEDIT_H__09112F26_9BEB_11D7_9142_0050044D962D__INCLUDED_)
