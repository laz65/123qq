// Tarif.cpp : implementation file
//

#include "stdafx.h"
#include "InetTarif.h"
#include "Tarif.h"
#include "TarifEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CInetTarifApp theApp;
extern Setup m_Setup;
extern void PrintChek(CString strChek);
/////////////////////////////////////////////////////////////////////////////
// CTarif dialog


CTarif::CTarif(CWnd* pParent /*=NULL*/)
	: CDialog(CTarif::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTarif)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTarif::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTarif)
	DDX_Control(pDX, IDC_TARIF, m_TarifList);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_BTNRFSH, m_RfrshBtn);
}


BEGIN_MESSAGE_MAP(CTarif, CDialog)
	//{{AFX_MSG_MAP(CTarif)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CTarif::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTADD, &CTarif::OnBnClickedButadd)
	ON_BN_CLICKED(IDC_BUTEDIT, &CTarif::OnBnClickedButedit)
	ON_BN_CLICKED(IDC_BUTDELETE, &CTarif::OnBnClickedButdelete)
	ON_NOTIFY(NM_DBLCLK, IDC_TARIF, &CTarif::OnNMDblclkTarif)
	ON_BN_CLICKED(IDC_BTNRFSH, &CTarif::OnBnClickedBtnrfsh)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTarif message handlers

BOOL CTarif::OnInitDialog() 
{
	CDialog::OnInitDialog();
	if (m_Setup.UseRF2160 == true)
	{
		m_RfrshBtn.EnableWindow(TRUE);
	}
	//
	int i;
	// Delete all of the columns.
	for (i=0; i < m_TarifList.GetHeaderCtrl()->GetItemCount(); i++)
	   m_TarifList.DeleteColumn(0);
	m_TarifList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_TarifList.InsertColumn(0, "№ п/п", LVCFMT_RIGHT, 50, 0);
	m_TarifList.InsertColumn(1, "Наименование", LVCFMT_LEFT, 260, 1);
	m_TarifList.InsertColumn(2, "Тариф", LVCFMT_RIGHT, 100, 2);
	m_TarifList.InsertColumn(3, "Тип тарифа", LVCFMT_RIGHT, 80, 3);
	m_TarifList.InsertColumn(4, "Код РФ", LVCFMT_RIGHT, 70, 4);
	m_TarifList.InsertColumn(5, "Наименование РФ", LVCFMT_LEFT, 180, 5);
	m_TarifList.InsertColumn(6, "Код ставки налога", LVCFMT_RIGHT, 80, 6);
	//
	FillGrid();
	return TRUE;
}
//
void CTarif::FillGrid()
{
	m_TarifList.SetRedraw(false);
	m_TarifList.DeleteAllItems();
	//
	CDaoQueryDef QdExtTar( &theApp.m_database );
	CDaoRecordset pRsData(&theApp.m_database);
	CString strSQL;
	COleVariant m_OleVariant;
	strSQL = "SELECT info, tarif, code_reg, code_info, ID, rf_rate, tarif_type "
		"FROM ExtTar "
		"WHERE ExtTar.ID > 1 "
		"ORDER BY ExtTar.ID" ;
	try
	{
		QdExtTar.Create( "", strSQL );
		// RecordSet
		pRsData.Open(&QdExtTar);
		//
		char cStr[100];
		double dTmp;
		int iRows = 0;
		int iIndex;
		while ( !pRsData.IsEOF( ) )
		{
			// ID
			pRsData.GetFieldValue("ID", m_OleVariant);
			sprintf(cStr, "%i", m_OleVariant.lVal);
			iIndex = m_TarifList.InsertItem(iRows, cStr, 0);
			// info
			pRsData.GetFieldValue("info", m_OleVariant);
			sprintf(cStr, "%s", m_OleVariant.bstrVal);
			m_TarifList.SetItem(iIndex, 1, LVIF_TEXT, cStr, 0,0,0,0);
			// tarif
			pRsData.GetFieldValue("tarif", m_OleVariant);
			if (m_OleVariant.vt == VT_DECIMAL)
			{
				if (m_OleVariant.decVal.sign == '-')
					dTmp = 0-m_OleVariant.decVal.Lo64/pow((double) 10, m_OleVariant.decVal.scale);
				else
					dTmp = m_OleVariant.decVal.Lo64/pow((double) 10, m_OleVariant.decVal.scale);
			}
			else
				dTmp = m_OleVariant.dblVal;
			sprintf(cStr, "%.8f", dTmp);
			m_TarifList.SetItem(iIndex, 2, LVIF_TEXT, cStr, 0,0,0,0);
			// 28.12.2009
			pRsData.GetFieldValue("tarif_type", m_OleVariant);
			sprintf(cStr, "%i", m_OleVariant.lVal);
			m_TarifList.SetItem(iIndex, 3, LVIF_TEXT, cStr, 0,0,0,0);
			//code_reg
			pRsData.GetFieldValue("code_reg", m_OleVariant);
			sprintf(cStr, "%i", m_OleVariant.lVal);
			m_TarifList.SetItem(iIndex, 4, LVIF_TEXT, cStr, 0,0,0,0);
			//code_info
			pRsData.GetFieldValue("code_info", m_OleVariant);
			sprintf(cStr, "%s", m_OleVariant.bstrVal);
			m_TarifList.SetItem(iIndex, 5, LVIF_TEXT, cStr, 0,0,0,0);
			//08.12.2009 rf_rate
			pRsData.GetFieldValue("rf_rate", m_OleVariant);
			sprintf(cStr, "%i", m_OleVariant.lVal);
			m_TarifList.SetItem(iIndex, 6, LVIF_TEXT, cStr, 0,0,0,0);
			//
			iRows++;
			pRsData.MoveNext( );
		}
		pRsData.Close();
		QdExtTar.Close();
	}
	catch (CDaoException* e)
	{
		AfxMessageBox("Ошибка открытия БД: " + e->m_pErrorInfo->m_strDescription);
		e->Delete();
		if (pRsData.IsOpen()) 
			pRsData.Close();
		if (QdExtTar.IsOpen())
			QdExtTar.Close();
	}
	m_TarifList.SetRedraw(true);
}
//Выйти из окна
void CTarif::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	OnOK();
}
// Добавить новый тариф
void CTarif::OnBnClickedButadd()
{
	CTarifEdit NewTarDlg;
	if (NewTarDlg.DoModal()==IDOK)
	{
		int iTarifID = theApp.InsExTar(NewTarDlg.m_Name, NewTarDlg.m_Tarif, NewTarDlg.m_RfCode, 
			NewTarDlg.m_RfName, NewTarDlg.m_RfRate, NewTarDlg.m_TarType);
		if (iTarifID <= 0)
		{
			MessageBox ("Ошибка добавления нового тарифа в таблицу.", "Ошибка", MB_OK|MB_ICONERROR);
		}
		FillGrid();
	}
}
// Изменить существующий тариф
void CTarif::OnBnClickedButedit()
{
	POSITION pos = m_TarifList.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox("Выберите тариф из списка для редактирования",
			"Внимание", MB_OK|MB_ICONINFORMATION);
		return;
	}
	//
	int nItem = m_TarifList.GetNextSelectedItem(pos);
	EditTarif(nItem);
}
// Редактирование сущ-щей записи
void CTarif::EditTarif(int nItem)
{
	long iTarID = atoi(m_TarifList.GetItemText(nItem, 0));
	//
	CTarifEdit NewTarDlg;
	NewTarDlg.m_Name = m_TarifList.GetItemText(nItem, 1);
	NewTarDlg.m_Tarif = atof(m_TarifList.GetItemText(nItem, 2));
	NewTarDlg.m_TarType = atoi(m_TarifList.GetItemText(nItem, 3));
	NewTarDlg.m_RfCode = atoi(m_TarifList.GetItemText(nItem, 4));
	NewTarDlg.m_RfName = m_TarifList.GetItemText(nItem, 5);
	NewTarDlg.m_RfRate = atoi(m_TarifList.GetItemText(nItem, 6));
	if (NewTarDlg.DoModal()==IDOK)
	{
		int iTarifID = theApp.EditExTar(iTarID, NewTarDlg.m_Name, NewTarDlg.m_Tarif, NewTarDlg.m_RfCode, 
			NewTarDlg.m_RfName, NewTarDlg.m_RfRate, NewTarDlg.m_TarType);
		if (iTarifID <= 0)
		{
			MessageBox ("Ошибка вненсения изменений в существующий тариф.", "Ошибка", MB_OK|MB_ICONERROR);
		}
		FillGrid();
	}
}
// Удалить существующий тариф
void CTarif::OnBnClickedButdelete()
{
	POSITION pos = m_TarifList.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox("Выберите тариф из списка для редактирования",
			"Внимание", MB_OK|MB_ICONINFORMATION);
		return;
	}
	//
	int nItem = m_TarifList.GetNextSelectedItem(pos);
	long iTarID = atoi(m_TarifList.GetItemText(nItem, 0));
	//
	CDaoQueryDef QdPayLog( &theApp.m_database );
	CDaoRecordset pRsData(&theApp.m_database);
	CString strSQLPay;
	CString strParam = "PARAMETERS [parTarif] INTEGER;";
	strSQLPay = strParam + "SELECT Count(ID) AS CntREc FROM PayLog WHERE TarifID = [parTarif]";
	try
	{
		// Temporary
		QdPayLog.Create("", strSQLPay);
		//
		COleVariant m_OleVariant;
		m_OleVariant = (long) iTarID;
		QdPayLog.SetParamValue( "[parTarif]", m_OleVariant );
		// RecordSet
		pRsData.Open(&QdPayLog);
		//
		long iRows = 0;
		while ( !pRsData.IsEOF( ) )
		{
			pRsData.GetFieldValue("CntREc", m_OleVariant);
			iRows+= theApp.GetAccInteger(m_OleVariant);
			pRsData.MoveNext( );
		}
		pRsData.Close();
		QdPayLog.Close();
		//
		if ( iRows > 0 )
		{
			MessageBox ("Не могу удалить запись.\nСуществуют платежи со ссылкой на данный тариф.", 
				"Ошибка", MB_OK|MB_ICONERROR);
		}
		else
		{
			if ( MessageBox("Удалить тариф без возможности восстановления?", "Внимание", MB_OKCANCEL|MB_ICONQUESTION) == IDOK)
			{
				BOOL bRes = theApp.DeleteExTar(iTarID);
				if (!bRes)
					MessageBox ("Не могу удалить тариф", "Ошибка", MB_OK|MB_ICONERROR);
				else
					FillGrid();
			}
		}
	}
	catch (CDaoException* e)
	{
		AfxMessageBox("Ошибка открытия БД: " + e->m_pErrorInfo->m_strDescription);
		e->Delete();
		if (pRsData.IsOpen()) 
			pRsData.Close();
		if (QdPayLog.IsOpen())
			QdPayLog.Close();
	}
}
// Двойной щелчек на строке
void CTarif::OnNMDblclkTarif(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: добавьте свой код обработчика уведомлений
	int Row = pNMItemActivate->iItem;
	EditTarif(Row);
	//
	*pResult = 0;
}

BOOL CTarif::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	/*if (wParam==WM_DESTROY)	theApp.LoadDopusl ();*/
	return CDialog::OnCommand(wParam, lParam);
}
// Обновление настроек кассового РФ-2160
void CTarif::OnBnClickedBtnrfsh()
{
	if ( MessageBox("Перед программированием перечня услуг\nРФ-2160 будет переведен в Z-режим\nи будет выполнен Z-отчет с обнулением.\nПродолжать?", "Внимание", MB_OKCANCEL|MB_ICONQUESTION) == IDOK)
	{
		// Z-режим с обнулением кодировка русская ОЕМ
		char str_z[100];
		sprintf (str_z, "Z$\nI$р$Z\n");
		//CharToOem (str_z, str_z);
		//
		CString str, tmpChek;
		tmpChek.Format("%s", str_z);
		int nomusl;
		int iRfRate;
		//
		CDaoQueryDef QdExtTar( &theApp.m_database );
		CDaoRecordset pRsData(&theApp.m_database);
		CString strSQL;
		COleVariant m_OleVariant;
		strSQL = "SELECT info, tarif, code_reg, code_info, ID, rf_rate "
			"FROM ExtTar "
			"ORDER BY ExtTar.ID" ;
		try
		{
			QdExtTar.Create( "", strSQL );
			// RecordSet
			pRsData.Open(&QdExtTar);
			while ( !pRsData.IsEOF( ) )
			{
				//code_reg
				pRsData.GetFieldValue("code_reg", m_OleVariant);
				nomusl = theApp.GetAccInteger(m_OleVariant);
				//code_info
				pRsData.GetFieldValue("code_info", m_OleVariant);
				//sprintf(rf_name, "%s", );
				sprintf(str_z, "%s", m_OleVariant.bstrVal);
				//CharToOem (str_z, str_z);
				// 08.12.2009 
				pRsData.GetFieldValue("rf_rate", m_OleVariant);
				iRfRate = theApp.GetAccInteger(m_OleVariant);
				// Цена=1.00, к-во=1.000 для кода Интернет, где передается сумма в к-во
				//str.Format("P$%i$1$0$1$0$1$%s$100$1000\n", nomusl, str_z);
				str.Format("P$%i$%i$0$1$0$1$%s$100$1000\n", nomusl, iRfRate, str_z);
				tmpChek = tmpChek + str;
				pRsData.MoveNext( );
			}
			pRsData.Close();
			QdExtTar.Close();
		}
		catch (CDaoException* e)
		{
			AfxMessageBox("Ошибка открытия БД: " + e->m_pErrorInfo->m_strDescription);
			e->Delete();
			if (pRsData.IsOpen()) 
				pRsData.Close();
			if (QdExtTar.IsOpen())
				QdExtTar.Close();
		}
		/*
		if( !theApp.pRsExtTarif->IsOpen())
		{
			MessageBox("Нет доступа перечню услуг.\nРежим отменен.", "Ошибка", MB_OK|MB_ICONSTOP);
			#ifdef _LOG_ITAR
				LogWrite ("Нет курсора по таблице тарифов");
			#endif
			return;
		}
		COleVariant m_OleVariant;
		theApp.pRsExtTarif->MoveFirst();
		int nomusl;
		//CString rf_name;
		while ( !theApp.pRsExtTarif->IsEOF( ) )
		{
			//code_reg
			theApp.pRsExtTarif->GetFieldValue("code_reg", m_OleVariant);
			nomusl = theApp.GetAccInteger(m_OleVariant);
			//code_info
			theApp.pRsExtTarif->GetFieldValue("code_info", m_OleVariant);
			//sprintf(rf_name, "%s", );
			sprintf(str_z, "%s", m_OleVariant.bstrVal);
			CharToOem (str_z, str_z);
			// Цена=1.00, к-во=1.000 для кода Интернет, где передается сумма в к-во
			str.Format("P$%i$1$0$1$0$1$%s$100$1000\n", nomusl, str_z);
			tmpChek = tmpChek + str;
			theApp.pRsExtTarif->MoveNext( );
		}
		*/
		PrintChek(tmpChek);
		MessageBox("Чек на программирование РФ сформирован.", "Информация", MB_OK|MB_ICONINFORMATION);
	}
	else
	{
		MessageBox("Режим отменен.\nВ случае расхождения перечня и наименованиий услуг\nв ПП и РФ печать чека будет невозможна.", "Внимание", MB_OK|MB_ICONEXCLAMATION);
	}

}
