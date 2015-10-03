#pragma once


// диалоговое окно CDialog2

class CDialog2 : public CDialog
{
	DECLARE_DYNAMIC(CDialog2)

public:
	CDialog2(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CDialog2();

// Данные диалогового окна
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
private:
	afx_msg void OnBnClickedSvshow();
	afx_msg void OnBnClickedSvexcel();
	CDateTimeCtrl m_DtFrom;
	CDateTimeCtrl m_DtTo;
	char cRepFl[200];
	char cExlRep[200];
	bool m_zvit;
	bool FormOtchet();
};
