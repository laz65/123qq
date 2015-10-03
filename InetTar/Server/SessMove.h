#pragma once


// диалоговое окно CSessMove

class CSessMove : public CDialog
{
	DECLARE_DYNAMIC(CSessMove)

public:
	CSessMove(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CSessMove();
	int iCurrComp;
	int NewNumbComp;

// Данные диалогового окна
	enum { IDD = IDD_SESSMOVE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_Grid;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
};
