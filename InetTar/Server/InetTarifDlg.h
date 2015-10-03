// InetTarifDlg.h : header file
//
#include "afxwin.h"
#if !defined(AFX_INETTARIFDLG_H__78696A70_83ED_11D4_945E_0050044D962D__INCLUDED_)
#define AFX_INETTARIFDLG_H__78696A70_83ED_11D4_945E_0050044D962D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CInetTarifDlg dialog

class CInetTarifDlg : public CDialog
{
// Construction
public:
	CInetTarifDlg(CWnd* pParent = NULL);	// standard constructor
	//void UpdateWindow();
	// Всплывающее меню
	CMenu Listmn;
	// Подчиненное всплывающее меню
	CMenu Mengmn;

// Dialog Data
	//{{AFX_DATA(CInetTarifDlg)
	enum { IDD = IDD_INETTARIF_DIALOG };
	//}}AFX_DATA
	// 20.05.2009
	//CStatic cPrinUah;
	//CStatic cZalogUah;

private:
	void InitWorkstation();
	bool myProgInit(int);
	CListCtrl	m_List;
	std::vector<CProgressCtrl*> m_vectPrgssCtrl;
	CStatusBarCtrl m_StatusBar;
	// Показывать бегунок для работающего компа
	bool IsShowPrgss;
	//int ListItm;
	CRect ListRct;
	RECT m_desktop;
	int GlobalWTime; //CInetTarifDlg::OnTimer(UINT nIDEvent) 
	// Для пунктов меню Залог, Расчет, Продление, Перенос
	void OnPressMenuZalog(WPARAM wParam, LPARAM lParam);
	void OnPressMenuRasch();
	void OnPressMenuProlong();
	void OnPressMenuMove();
	//
	void ChangeTarif(CompInfo &Comp, double oldt, double newt);
	void StopSeance(int iComp);
	void AtertSeance(int iComp, int iTarCode);
	bool StartInet(int Comp);
	bool StopInet(int Comp);
	// 20.05.2009
	void ShowRaschSum(long lZalog, long lPriem);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInetTarifDlg)
public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	CToolTipCtrl m_tooltip;
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CInetTarifDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnTimer(UINT nIDEvent);
//	afx_msg void OnMoving( UINT nSide, LPRECT lpRect );
//	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnCom();
	afx_msg void OnLogoff();
	afx_msg void OnSmena();
	afx_msg void OnChek();
	afx_msg void OnLvnGetdispinfoList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawLvCustomDraw(NMHDR *pNMHDR, LRESULT *pResult);
	//}}AFX_MSG
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnRemovepssbr();
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnStnClickedZalogUah();
//	afx_msg void OnStnClickedPrinUah();
//	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
//	afx_msg void OnSize(UINT nType, int cx, int cy);
//	afx_msg void OnExitSizeMove();
//	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
//	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnStnClickedPrinUah();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};

	
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INETTARIFDLG_H__78696A70_83ED_11D4_945E_0050044D962D__INCLUDED_)
