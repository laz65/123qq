#include "afxwin.h"
#if !defined(AFX_TARIF_H__AA260D83_8A8D_11D7_912F_0050044D962D__INCLUDED_)
#define AFX_TARIF_H__AA260D83_8A8D_11D7_912F_0050044D962D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Tarif.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CTarif dialog

class CTarif : public CDialog
{
// Construction
public:
	CTarif(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CTarif)
	enum { IDD = IDD_TARIF };
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTarif)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
private:
	void FillGrid();
	// Редактирование сущ-щей записи
	void EditTarif(int nItem);
// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTarif)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl	m_TarifList;
	virtual BOOL OnInitDialog();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButadd();
	afx_msg void OnBnClickedButedit();
	afx_msg void OnBnClickedButdelete();
	afx_msg void OnNMDblclkTarif(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnrfsh();
	CButton m_RfrshBtn;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TARIF_H__AA260D83_8A8D_11D7_912F_0050044D962D__INCLUDED_)
