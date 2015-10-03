#pragma once
#include "afxwin.h"

// CShowRep dialog

class CShowRep : public CDialog
{
	//DECLARE_DYNAMIC(CShowRep)

public:
	CShowRep(CWnd* pParent = NULL);   // standard constructor
	virtual ~CShowRep();

// Dialog Data
	enum { IDD = IDD_REPLOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CString sFile;
	afx_msg void OnBnClickedOk();
	CEdit m_EdRepLog;
};
