#pragma once


// ���������� ���� CSessMove

class CSessMove : public CDialog
{
	DECLARE_DYNAMIC(CSessMove)

public:
	CSessMove(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CSessMove();
	int iCurrComp;
	int NewNumbComp;

// ������ ����������� ����
	enum { IDD = IDD_SESSMOVE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_Grid;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
};
