// RepDelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "InetTarif.h"
#include "RepDelDlg.h"
//
extern void LogWrite(char *text);
extern CInetTarifApp theApp;
extern _UInfo UInfo;
// CRepDelDlg dialog

IMPLEMENT_DYNAMIC(CRepDelDlg, CDialog)
CRepDelDlg::CRepDelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRepDelDlg::IDD, pParent)
{
}

CRepDelDlg::~CRepDelDlg()
{
}

void CRepDelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRID, m_Grid);
}


BEGIN_MESSAGE_MAP(CRepDelDlg, CDialog)
	ON_BN_CLICKED(IDC_DEL, OnBnClickedDel)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CRepDelDlg message handlers
BOOL CRepDelDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	FillGrid();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CRepDelDlg::FillGrid()
{
	int i;
	// Delete all of the columns.
	for (i=0;i < m_Grid.GetHeaderCtrl()->GetItemCount();i++)
	   m_Grid.DeleteColumn(0);
	// Заголовок списка
	char *head[]={"Дата", "Кол-во", "Сумма с НДС" };
	const int width[] = { 100, 90, 110 };
	for (i=0; i<3; i++)
		m_Grid.InsertColumn(i, head[i], LVCFMT_LEFT, width[i], i);
	CHeaderCtrl *h = m_Grid.GetHeaderCtrl();
	// Для числовых полей
	HDITEM hi;
	for (i=1; i<3; i++)
	{	
		hi.fmt = HDF_RIGHT|HDF_STRING;
		hi.mask = HDI_FORMAT;
		h->SetItem(i, &hi);
	}
	m_Grid.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	//
	m_Grid.SetRedraw(false);
	m_Grid.DeleteAllItems();
	//
	CDaoQueryDef QdInetLog( &theApp.m_database );
	CDaoRecordset pRsData(&theApp.m_database);
	COleVariant m_OleVariant;
	CString strSQL;
	strSQL = "SELECT DateValue(PayLog.PayDate) AS DateStart, "
		"Count(*) AS CntRec, Round(Sum(PayLog.CalcSum), 2) AS CalcSum "
		"FROM PayLog "
		"GROUP BY DateValue(PayLog.PayDate) "
		"ORDER BY DateValue(PayLog.PayDate)" ;
	try
	{
		QdInetLog.Create( "", strSQL );
		// RecordSet
		pRsData.Open(&QdInetLog);
		//
		char cStr[100];
		double dTmp;
		int iRows = 0;
		int iIndex;
		while ( !pRsData.IsEOF( ) )
		{
			// Дата
			pRsData.GetFieldValue("DateStart", m_OleVariant);
			strcpy(cStr, COleDateTime (m_OleVariant).Format( _T("%d/%m/%Y") ) );
			iIndex = m_Grid.InsertItem(iRows, cStr, 0);   
			// К-во
			pRsData.GetFieldValue("CntRec", m_OleVariant);
			sprintf(cStr, "%i", m_OleVariant.lVal);
			m_Grid.SetItem(iIndex, 1, LVIF_TEXT, cStr, 0,0,0,0);
			// Сумма
			pRsData.GetFieldValue("CalcSum", m_OleVariant);
			if (m_OleVariant.vt == VT_DECIMAL)
			{
				if (m_OleVariant.decVal.sign == '-')
					dTmp = 0-m_OleVariant.decVal.Lo64/pow((double) 10, m_OleVariant.decVal.scale);
				else
					dTmp = m_OleVariant.decVal.Lo64/pow((double) 10, m_OleVariant.decVal.scale);
			}
			else
				dTmp = m_OleVariant.dblVal;
			sprintf(cStr, "%.2f", dTmp);
			m_Grid.SetItem(iIndex, 2, LVIF_TEXT, cStr, 0,0,0,0);
			iRows++;
			pRsData.MoveNext( );
		}
		pRsData.Close();
		QdInetLog.Close();
	}
	catch (CDaoException* e)
	{
		AfxMessageBox("Ошибка открытия БД: " + e->m_pErrorInfo->m_strDescription);
		e->Delete();
		if (pRsData.IsOpen()) 
			pRsData.Close();
		if (QdInetLog.IsOpen())
			QdInetLog.Close();
	}
	m_Grid.SetRedraw(true);
}
// Удалить выбранные записи
void CRepDelDlg::OnBnClickedDel()
{
	// Gets the position of the first selected item in the list view control
	POSITION pos = m_Grid.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox("Не могу удалить данные.\nНе выбран ни один элемент списка.",
			"Внимание", MB_OK|MB_ICONINFORMATION);
		return;
	}
	if (MessageBox("Удалить выбранные данные без возможности восстановления?", "Предупреждение", 
			MB_YESNO|MB_ICONEXCLAMATION|MB_TOPMOST|MB_SETFOREGROUND|MB_DEFBUTTON2 )==IDNO)
		return;
	//
	CDaoQueryDef QdInetLog( &theApp.m_database );
	CDaoQueryDef QdPayLog( &theApp.m_database );
	CString strSQLPay, strSQLInet;
	CString strParam = "PARAMETERS [parDate] DATETIME;";
	strSQLInet = strParam + "DELETE FROM InetLog WHERE (((InetLog.PayLogID) In " 
		+ "(SELECT PayLog.ID FROM PayLog WHERE  DateValue(PayLog.PayDate) = [parDate])))";
	strSQLPay  = strParam + "DELETE FROM PayLog  WHERE DateValue(PayLog.PayDate)  = [parDate] ";
	try
	{
		// Temporary
		QdInetLog.Create( "", strSQLInet );
		QdPayLog.Create("", strSQLPay);
		//
		CString sDate;
		COleDateTime m_OleDtTm;
		COleVariant m_OleVariant;
		// по всем выбранным строкам
		while (pos)
		{
			// Gets the index of the list item identified by pos, then sets pos to the POSITION value
			int nItem = m_Grid.GetNextSelectedItem(pos);
			sDate = m_Grid.GetItemText(nItem, 0);
			m_OleDtTm.SetDate( atoi(sDate.Mid(6,4)), atoi(sDate.Mid(3,2)), atoi(sDate.Mid(0,2)) );
			// Заполнить параметры (дата)
			m_OleVariant = m_OleDtTm;
			QdInetLog.SetParamValue( "[parDate]", m_OleVariant );
			QdPayLog.SetParamValue( "[parDate]", m_OleVariant );
			char LogBuffer[500];
			// #ifdef _LOG_ITAR
			//sprintf (LogBuffer, "Пользователь %s удалил данные в журналах # %d %s", UInfo.Fio, nItem ,sDate);
			//AfxMessageBox(LogBuffer);
			sprintf (LogBuffer, "Пользователь %s удалил данные в журналах за %s", UInfo.Fio, sDate);
			LogWrite (LogBuffer);
			// #endif
			// Удалить
			QdInetLog.Execute(dbSQLPassThrough);
			QdPayLog.Execute(dbSQLPassThrough);
			//m_Grid.DeleteItem( nItem );! Нельзя - смещение позиций и деселект
		}
		QdInetLog.Close();
		QdPayLog.Close();
	}
	catch(CDaoException* pe)
	{
		AfxMessageBox("Не могу удалить данные из журнала соединений: " + pe->m_pErrorInfo->m_strDescription, MB_ICONERROR);
		pe->Delete();
		if (QdInetLog.IsOpen()) 
			QdInetLog.Close();
		if (QdPayLog.IsOpen())
			QdPayLog.Close();
	}
	//
	FillGrid();
	MessageBox("Данные успешно удалены.", "Информация",MB_OK|MB_ICONINFORMATION);
}
// Закрыть диалог
void CRepDelDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

