#pragma once
#include "afxdtctl.h"


// ���������� ���� CSvRep

class CSvRep : public CDialog
{
	DECLARE_DYNAMIC(CSvRep)

public:
	CSvRep(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CSvRep();

// ������ ����������� ����
	enum { IDD = IDD_SVREP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
private:
	afx_msg void OnBnClickedSvshow();
	afx_msg void OnBnClickedSvexcel();
	CDateTimeCtrl m_DtFrom;
	CDateTimeCtrl m_DtTo;
	char cRepFl[200];
	char cExlRep[200];
	bool FormSvRepPay();
};
