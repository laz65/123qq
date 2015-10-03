#pragma once
#include "afxcmn.h"


// CRepDelDlg dialog

class CRepDelDlg : public CDialog
{
	DECLARE_DYNAMIC(CRepDelDlg)

public:
	CRepDelDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRepDelDlg();

// Dialog Data
	enum { IDD = IDD_DELREP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedDel();
	afx_msg void OnBnClickedOk();
	CListCtrl m_Grid;
private:
	void FillGrid();
};
