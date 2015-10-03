// SvRep.cpp: файл реализации
//

#include "stdafx.h"
#include "InetTarif.h"
#include "SvRep.h"
//
#include "UserInfo.h"
#include "ShowRep.h"
//
extern void LogWrite(char *text);
extern CInetTarifApp theApp;
extern hSetup m_Setup;
// Код оператора
extern int User;
extern _UInfo UInfo;
//
extern CMapWordToOb Users;


// диалоговое окно CSvRep

IMPLEMENT_DYNAMIC(CSvRep, CDialog)

CSvRep::CSvRep(CWnd* pParent /*=NULL*/)
	: CDialog(CSvRep::IDD, pParent)
{
	sprintf (cRepFl, "rep_sv.txt");
	sprintf (cExlRep, "rep_sv.xls");
}

CSvRep::~CSvRep()
{
}

void CSvRep::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DTFROM, m_DtFrom);
	DDX_Control(pDX, IDC_DTTO, m_DtTo);
}


BEGIN_MESSAGE_MAP(CSvRep, CDialog)
	ON_BN_CLICKED(IDC_SVSHOW, &CSvRep::OnBnClickedSvshow)
	ON_BN_CLICKED(IDC_SVEXCEL, &CSvRep::OnBnClickedSvexcel)
END_MESSAGE_MAP()


// обработчики сообщений CSvRep

void CSvRep::OnBnClickedSvshow()
{
	if ( !FormSvRepPay() ) return;
	CShowRep DlgShowRep;
	DlgShowRep.sFile = cRepFl;
	DlgShowRep.DoModal();
}

bool CSvRep::FormSvRepPay()
{
	// Справка
	FILE *fl_txt;
    if ((fl_txt = fopen(cRepFl, "w")) == NULL)
    {
		MessageBox("Не могу создать файл отчета.", "Ошибка", MB_OK|MB_ICONERROR);
		return false;
    }
	//
	CTime pDtFrom, pDtTo;
	m_DtFrom.GetTime(pDtFrom);
	m_DtTo.GetTime(pDtTo);
	COleDateTime m_OleDtTmFrom, m_OleDtTmTo;
	m_OleDtTmFrom.SetDate( pDtFrom.GetYear(), pDtFrom.GetMonth(), pDtFrom.GetDay() );
	m_OleDtTmTo.SetDate(pDtTo.GetYear(), pDtTo.GetMonth(), pDtTo.GetDay() );
	//
	CDaoQueryDef QdInetLog( &theApp.m_database );
	CDaoRecordset pRsData(&theApp.m_database);
	COleVariant m_OleVariant;
	CString strSQL;
	try
	{
		if (UInfo.Type == UT_SUPER || UInfo.Type == UT_ADMIN)
		{
			CString strParam = "PARAMETERS [parFromDate] DATETIME, [parToDate] DATETIME;";
			strSQL = strParam + " SELECT PayLog.UserID, ExtTar.info, DateValue(PayLog.PayDate) AS PayDate, PayLog.TarifID, "
				"Count(1) AS CntRec, Sum(PayLog.ServCnt) AS ServCnt, Round(Sum(PayLog.CalcSum),2) AS CalcSum "
				"FROM PayLog, ExtTar "
				"WHERE PayLog.TarifID = ExtTar.ID "
				" AND DateValue(PayLog.PayDate) >= [parFromDate] AND DateValue(PayLog.PayDate) <= [parToDate] "
				"GROUP BY PayLog.TarifID, ExtTar.info, DateValue(PayLog.PayDate), PayLog.UserID "
				"ORDER BY PayLog.TarifID, ExtTar.info, DateValue(PayLog.PayDate), PayLog.UserID ";
			// Temporary
			QdInetLog.Create( "", strSQL );
		}
		else
		{
			CString strParam = "PARAMETERS [parUserID] INTEGER, [parFromDate] DATETIME, [parToDate] DATETIME;";
			strSQL = strParam + " SELECT PayLog.UserID, ExtTar.info, DateValue(PayLog.PayDate) AS PayDate, PayLog.TarifID, "
				"Count(1) AS CntRec, Sum(PayLog.ServCnt) AS ServCnt, Round(Sum(PayLog.CalcSum),2) AS CalcSum "
				"FROM PayLog, ExtTar "
				"WHERE PayLog.TarifID = ExtTar.ID AND PayLog.UserID = [parUserID] "
				" AND DateValue(PayLog.PayDate) >= [parFromDate] AND DateValue(PayLog.PayDate) <= [parToDate] "
				"GROUP BY PayLog.TarifID, ExtTar.info, DateValue(PayLog.PayDate), PayLog.UserID "
				"ORDER BY PayLog.TarifID, ExtTar.info, DateValue(PayLog.PayDate), PayLog.UserID ";
			// Temporary
			QdInetLog.Create( "", strSQL );
			// Заполнить параметр (код оператора)
			m_OleVariant = (long) User;
			QdInetLog.SetParamValue( "[parUserID]", m_OleVariant );
		}
		// Заполнить параметры (дата)
		m_OleVariant = m_OleDtTmFrom;
		QdInetLog.SetParamValue( "[parFromDate]", m_OleVariant );
		m_OleVariant = m_OleDtTmTo;
		QdInetLog.SetParamValue( "[parToDate]", m_OleVariant );
		// RecordSet
		pRsData.Open(&QdInetLog);
	}
	catch (CDaoException* e)
	{
		AfxMessageBox("Ошибка открытия БД: " + e->m_pErrorInfo->m_strDescription);
		e->Delete();
		if (pRsData.IsOpen()) 
			pRsData.Close();
		if (QdInetLog.IsOpen())
			QdInetLog.Close();
		fclose (fl_txt);
		return false;
	}
	//
	char cStr[100];
	//
	sprintf (cStr, "Пункт колективного користування Інтернет: %s - %s", m_Setup.INomer, m_Setup.IName);
	fprintf(fl_txt, "%s\n\n", cStr);
	//
	fprintf(fl_txt, "Зведена відомість з прийому платежів за період з %s по %s\n", 
		pDtFrom.Format(_T("%d/%m/%Y")), pDtTo.Format(_T("%d/%m/%Y")) );
	//
	CTime tCurrTime = CTime::GetCurrentTime();
	sprintf (cStr, "Дата та час складання звіту - %s\n", tCurrTime.Format(_T("%d/%m/%Y %H:%M:%S")) );
	fprintf(fl_txt,"%s",cStr);
	if (UInfo.Type == UT_SUPER || UInfo.Type == UT_ADMIN)
		sprintf (cStr, "Всі платежі. Склав: %d (%s)\n\n", User, UInfo.Fio);
	else
		sprintf (cStr, "Платежі оператора: %d (%s)\n\n", User, UInfo.Fio);
	fprintf(fl_txt,"%s",cStr);
	//
	fprintf(fl_txt,"--------------------------------------------------\n");
	sprintf (cStr, "%-10s%-10s%-10s%-10s%-10s", "Дата", "|№", "|К-сть", "|К-сть", "|Сума");
	fprintf(fl_txt,"%s\n",cStr);
	//
	sprintf (cStr, "%-10s%-10s%-10s%-10s%-10s", "", "|оператора", "|платежів", "|послуг", "|оплати");
	fprintf(fl_txt,"%s\n",cStr);
	fprintf(fl_txt,"--------------------------------------------------\n");
	//
	long iSumRec =0;
	long iTarRec =0;
	long iSumCnt =0;
	long iTarCnt =0;
	double dSumCl=0;
	double dTarCl=0;
	//
	long iPaym = 0;
	CString sTarInfo;
	//
	double dTmp;
	long lTmp;
	CString sTmp;
	while ( !pRsData.IsEOF( ) )
	{
		// Номер тарифа
		pRsData.GetFieldValue("TarifID", m_OleVariant);
		if (iPaym != m_OleVariant.lVal)
		{
			// не первый блок
			if (iPaym != 0)
			{
				fprintf(fl_txt,"--------------------------------------------------\n");
				sprintf (cStr, "Разом:");
				sprintf (cStr, "%-20s%10d%10d%10.2f", cStr, iTarRec, iTarCnt, dTarCl);
				fprintf(fl_txt, "%s\n", cStr);
				fprintf(fl_txt,"--------------------------------------------------\n");
				iTarRec=0;
				iTarCnt=0;
				dTarCl=0;
			}
			iPaym = m_OleVariant.lVal;
			// наименование тарифа
			pRsData.GetFieldValue("info", m_OleVariant);
			sprintf(cStr, "%s", m_OleVariant.bstrVal);
			sTarInfo.Format("%s", cStr);
			//
			fprintf(fl_txt, "Послуга: %s\n", sTarInfo.Trim());
		}
		// Дата
		pRsData.GetFieldValue("PayDate", m_OleVariant);
		strcpy(cStr, COleDateTime (m_OleVariant).Format( _T("%d/%m/%Y") ) );
		fprintf(fl_txt, "%10s", cStr);
		// N оператора
		pRsData.GetFieldValue("UserID", m_OleVariant);
		fprintf(fl_txt, "%10d", m_OleVariant.lVal);
		// К-во платежів
		pRsData.GetFieldValue("CntRec", m_OleVariant);
		fprintf(fl_txt, "%10d", m_OleVariant.lVal);
		iSumRec = iSumRec + m_OleVariant.lVal;
		iTarRec = iTarRec + m_OleVariant.lVal;
		// К-во послуг
		pRsData.GetFieldValue("ServCnt", m_OleVariant);
		if (m_OleVariant.vt == VT_DECIMAL)
		{
			if (m_OleVariant.decVal.sign == '-')
				lTmp = Round( 0-m_OleVariant.decVal.Lo64/pow((double) 10, m_OleVariant.decVal.scale), 0 );
			else
				lTmp = Round( m_OleVariant.decVal.Lo64/pow((double) 10, m_OleVariant.decVal.scale), 0 );
		}
		else
			lTmp = Round( m_OleVariant.dblVal, 0 );
		fprintf(fl_txt, "%10d", lTmp);
		iSumCnt = iSumCnt + lTmp;
		iTarCnt = iTarCnt + lTmp;
		// Сумма оплаты
		pRsData.GetFieldValue("CalcSum", m_OleVariant);
		if (m_OleVariant.vt == VT_DECIMAL)
		{
			if (m_OleVariant.decVal.sign == '-')
				dTmp = Round( 0-m_OleVariant.decVal.Lo64/pow((double) 10, m_OleVariant.decVal.scale), 2 );
			else
				dTmp = Round( m_OleVariant.decVal.Lo64/pow((double) 10, m_OleVariant.decVal.scale), 2 );
		}
		else
			dTmp = Round( m_OleVariant.dblVal, 2 );
		dSumCl+=dTmp;
		dTarCl+=dTmp;
		fprintf(fl_txt, "%10.2f", dTmp);
		//
		fprintf(fl_txt,"\n");
		pRsData.MoveNext( );
	}
	pRsData.Close();
	QdInetLog.Close();
	//
	if (iPaym != 0)
	{
		fprintf(fl_txt,"--------------------------------------------------\n");
		sprintf (cStr, "Разом:");
		sprintf (cStr, "%-20s%10d%10d%10.2f", cStr, iTarRec, iTarCnt, dTarCl);
		fprintf(fl_txt, "%s\n", cStr);
	}
	fprintf(fl_txt,"--------------------------------------------------\n");
	sprintf (cStr, "У с ь о г о:");
	sprintf (cStr, "%-20s%10d%10d%10.2f", cStr, iSumRec, iSumCnt, dSumCl);
	fprintf(fl_txt, "%s\n", cStr);
	fprintf(fl_txt,"--------------------------------------------------\n");
	fclose (fl_txt);
	//
	return true;
}

void CSvRep::OnBnClickedSvexcel()
{
	if ( !FormSvRepPay() ) return;
	ShellExecute (NULL, "open", cExlRep, NULL, NULL, SW_SHOW);
}
