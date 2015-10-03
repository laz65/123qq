// InetTarif.h : main header file for the INETTARIF application
//

#if !defined(AFX_INETTARIF_H__78696A6E_83ED_11D4_945E_0050044D962D__INCLUDED_)
#define AFX_INETTARIF_H__78696A6E_83ED_11D4_945E_0050044D962D__INCLUDED_

//#define _WIN32_IE 0x0500

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CInetTarifApp:
// See InetTarif.cpp for the implementation of this class
//
class CInetTarifApp : public CWinApp
{
public:
	bool EnterSystem();
	void SaveUsers();
	void LoadUsers();
	CInetTarifApp();
	void LoadProfiles ();
	void SaveProfiles ();
	void LoadDopusl ();

	CDaoDatabase m_database;
	CDaoRecordset *pRsExtTarif;

    CMenu TempMenu;
	// Получение числовых данных из COleVariant
	double GetAccDouble(COleVariant m_OleVariant);
	long GetAccInteger(COleVariant m_OleVariant);
	//Таблица тарифов
	int InsExTar(CString sInfo, float fTarif, int iCodeRf, CString sCodeInfoRf, int iRate, int iTarType);
	int EditExTar(int iID, CString sInfo, float fTarif, int iCodeRf, CString sCodeInfoRf, int iRate, int iTarType);
	BOOL DeleteExTar(int iID);
	// Журнал оплат
	int InsPayLog(int iUserID, CTime tPayDate, int iTarifID, int iServCnt, 
		long fDepSum, long fCalcSum, long fСhangeSum, CString sNumStud, CString sFioStud);
	// Журнал соединений
	int InsInetLog(int iCompID, int iPayLogID, CTime tDateStart, 
	double fTarif, int iElapceTime, double fCalcSum);

//protected:
private:
	CDaoTableDef *pTdExtTarif;
	CDaoTableDef *pTdInetLog;
	CDaoTableDef *pTdPayLog;

	CDaoRecordset *pRsInetLog;
	CDaoRecordset *pRsPayLog;

	bool OpenDatabase();
	void CloseDatabase();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInetTarifApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CInetTarifApp)
	afx_msg void OnAdmin();
	afx_msg void OnHolidays();
	afx_msg void OnManage();
	afx_msg void OnChangepass();
	afx_msg void OnDayoff();
	afx_msg void OnTarif();
	afx_msg void OnSetUsl();
	afx_msg void OnAbout();
	afx_msg void OnTip();
	afx_msg void OnXotchet();
	afx_msg void OnXotchetT();
	afx_msg void OnZotchet();
	afx_msg void OnZotchetT();
	afx_msg void OnMotchet();
	afx_msg void OnOtkr();
	afx_msg void OnVnesenie();
	afx_msg void OnIzyatie();
	afx_msg void OnInternet();
	afx_msg void OnPayment();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ShowTipAtStartup(void);
private:
	void ShowTipOfTheDay(void);

public:
	afx_msg void OnDelrep();
	afx_msg void OnSvpayrep();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INETTARIF_H__78696A6E_83ED_11D4_945E_0050044D962D__INCLUDED_)
