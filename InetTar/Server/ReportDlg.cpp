// ReportDlg.cpp : implementation file
//

#include "stdafx.h"
#include "InetTarif.h"
#include "ReportDlg.h"
#include "UserInfo.h"
#include "ShowRep.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//extern int Except (unsigned int code, struct _EXCEPTION_POINTERS *ep, CString ProcName);
extern void LogWrite(char *text);
extern CInetTarifApp theApp;
extern hSetup m_Setup;
//extern double Round(double dSum);
// ��� ���������
extern int User;
extern _UInfo UInfo;
//
extern CMapWordToOb Users;
/////////////////////////////////////////////////////////////////////////////
// CReportDlg dialog

CReportDlg::CReportDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReportDlg::IDD, pParent)
{
	iRepType = 1;
	//{{AFX_DATA_INIT(CReportDlg)
	//}}AFX_DATA_INIT
}


void CReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReportDlg)
	DDX_Control(pDX, IDC_GRID, m_Grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReportDlg, CDialog)
	//{{AFX_MSG_MAP(CReportDlg)
	ON_BN_CLICKED(IDC_SHOW, OnBnClickedShow)
	ON_BN_CLICKED(IDC_PRINT, OnPrint)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportDlg message handlers

BOOL CReportDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	#ifdef _LOG_ITAR
		LogWrite ("Enter to Report Dialog.");
	#endif
	// ��������� ���� + ���� �������
	char str[200];
	if (iRepType == 1)
	{
		sprintf (cRepFl, "rep_inet.txt");
		sprintf (cExlRep, "rep_inet.xls");
		sprintf (str, "����� �� ������� ���� %s - %s. ��������: %s", m_Setup.INomer, m_Setup.IName, UInfo.Fio);
	}
	else
	{
		sprintf (cRepFl, "rep_paym.txt");
		sprintf (cExlRep, "rep_paym.xls");
		sprintf (str, "����� �� �������� ���� %s - %s. ��������: %s", m_Setup.INomer, m_Setup.IName, UInfo.Fio);
	}
	SetWindowText(str);
	int i;
	// Delete all of the columns.
	for (i=0;i < m_Grid.GetHeaderCtrl()->GetItemCount();i++)
	   m_Grid.DeleteColumn(0);
	// ��������� ������
	char *head[]={"��������", "����", "���-��", "����� � ���" };
	const int width[] = { 80, 80, 90, 110 };
	for (i=0; i<4; i++)
		m_Grid.InsertColumn(i, head[i], LVCFMT_LEFT, width[i], i);
	CHeaderCtrl *h = m_Grid.GetHeaderCtrl();
	// ��� �������� �����
	HDITEM hi;
	for (i=2; i<4; i++)
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
	CDaoRecordset pRsData( &theApp.m_database );
	try
	{
		CString strSQL;
		COleVariant m_OleVariant;
		if (iRepType == 1)
		{
			if (UInfo.Type == UT_SUPER || UInfo.Type == UT_ADMIN)
			{
				strSQL = "SELECT PayLog.UserID, DateValue(InetLog.DateStart) AS DateStart, "
					"Count(1) AS CntRec, Round(Sum(InetLog.CalcSum), 2) AS CalcSum "
					"FROM PayLog, InetLog "
					"WHERE PayLog.ID=InetLog.PayLogID "
					"GROUP BY PayLog.UserID, DateValue(InetLog.DateStart)"
					"ORDER BY DateValue(InetLog.DateStart) desc, PayLog.UserID" ;
				// Adds to db
				//QdInetLog.Create( "RepInetLog", strSQL );
				//QdInetLog.Append( );
				// Temporary
				QdInetLog.Create( "", strSQL );
			}
			else
			{
				CString strParam = "PARAMETERS [parUserID] INTEGER;";
				strSQL = strParam + "SELECT PayLog.UserID, DateValue(InetLog.DateStart) AS DateStart, "
					"Count(*) AS CntRec, Round(Sum(InetLog.CalcSum), 2) AS CalcSum "
					"FROM PayLog, InetLog "
					"WHERE PayLog.ID=InetLog.PayLogID AND PayLog.UserID = [parUserID] "
					"GROUP BY PayLog.UserID, DateValue(InetLog.DateStart) "
					"ORDER BY DateValue(InetLog.DateStart) desc, PayLog.UserID" ;
				// Temporary
				QdInetLog.Create( "", strSQL );
				// ��������� �������� (��� ���������)
				m_OleVariant = (long) User;
				QdInetLog.SetParamValue( "[parUserID]", m_OleVariant );
			}
		}
		else
		{
			if (UInfo.Type == UT_SUPER || UInfo.Type == UT_ADMIN)
			{
				strSQL = "SELECT PayLog.UserID, DateValue(PayLog.PayDate) AS DateStart, "
					"Count(*) AS CntRec, Round(Sum(PayLog.CalcSum), 2) AS CalcSum "
					"FROM PayLog "
					"GROUP BY PayLog.UserID, DateValue(PayLog.PayDate) "
					"ORDER BY DateValue(PayLog.PayDate) DESC, PayLog.UserID" ;
				QdInetLog.Create( "", strSQL );
			}
			else
			{
				CString strParam = "PARAMETERS [parUserID] INTEGER;";
				strSQL = strParam + "SELECT PayLog.UserID, DateValue(PayLog.PayDate) AS DateStart, "
					"Count(*) AS CntRec, Round(Sum(PayLog.CalcSum), 2) AS CalcSum "
					"FROM PayLog "
					"WHERE PayLog.UserID = [parUserID] "
					"GROUP BY PayLog.UserID, DateValue(PayLog.PayDate) "
					"ORDER BY DateValue(PayLog.PayDate) DESC, PayLog.UserID" ;
				// Temporary
				QdInetLog.Create( "", strSQL );
				// ��������� �������� (��� ���������)
				m_OleVariant = (long) User;
				QdInetLog.SetParamValue( "[parUserID]", m_OleVariant );
			}
		}
		// RecordSet
		pRsData.Open(&QdInetLog);
		//
		LVITEM it;
		it.mask = LVIF_TEXT;
		it.cchTextMax = 100;
		//
		char cStr[100];
		double dTmp;
		int iRows = 0;
		while ( !pRsData.IsEOF( ) )
		{
			//��������
			pRsData.GetFieldValue("UserID", m_OleVariant);
			sprintf(cStr, "%i", m_OleVariant.lVal);
			it.pszText = cStr;
			it.iItem = iRows++;
			it.iSubItem = 0;
			m_Grid.InsertItem(&it);
			// ����
			pRsData.GetFieldValue("DateStart", m_OleVariant);
			strcpy(cStr, COleDateTime (m_OleVariant).Format( _T("%d/%m/%Y") ) );
			it.pszText = cStr;
			it.iSubItem = 1;
			m_Grid.SetItem(&it);
			// �-��
			pRsData.GetFieldValue("CntRec", m_OleVariant);
			sprintf(cStr, "%i", m_OleVariant.lVal);
			it.pszText = cStr;
			it.iSubItem = 2;
			m_Grid.SetItem(&it);
			// �����
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
			it.pszText = cStr;
			it.iSubItem = 3;
			m_Grid.SetItem(&it);
			//
			pRsData.MoveNext( );
		}
		pRsData.Close();
		QdInetLog.Close();
	}
	catch (CDaoException* e)
	{
		AfxMessageBox("������ �������� ��: " + e->m_pErrorInfo->m_strDescription);
		e->Delete();
		if (pRsData.IsOpen()) 
			pRsData.Close();
		if (QdInetLog.IsOpen())
			QdInetLog.Close();
	}
	//
	m_Grid.SetRedraw(true);
	//
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(CReportDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CReportDlg)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CReportDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	if (m_Grid)
	{
		LPRECT r = new RECT;
		m_Grid.GetWindowRect(r);
		ScreenToClient(r);
		m_Grid.SetWindowPos(NULL,0, 0, cx-r->left-5, cy-r->top-5, SWP_NOMOVE | SWP_NOZORDER | SWP_SHOWWINDOW);
		delete r;
	}
}

void CReportDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	// TODO: Add your message handler code here
}

void CReportDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	// TODO: Add your message handler code here
}

bool CReportDlg::FormRepInetLog()
{
	// Gets the position of the first selected item in the list view control
	POSITION pTemp = m_Grid.GetFirstSelectedItemPosition();
	if (pTemp == NULL)
	{
		MessageBox("�� ���� ������� �����.\n�� ������ �� ���� ������� ������.",
			"��������", MB_OK|MB_ICONINFORMATION);
		return false;
	}
	// Gets the index of the list item identified by pos, then sets pos to the POSITION value
	int iRow = m_Grid.GetNextSelectedItem(pTemp);
	CString sUser = m_Grid.GetItemText(iRow, 0);
	CString sDate = m_Grid.GetItemText(iRow, 1);
	int iUser = atoi(sUser);
	COleDateTime m_OleDtTm;
	m_OleDtTm.SetDate( atoi(sDate.Mid(6,4)), atoi(sDate.Mid(3,2)), atoi(sDate.Mid(0,2)) );
	// �������
	FILE *fl_txt;
    if ((fl_txt = fopen(cRepFl, "w")) == NULL)
    {
		MessageBox("�� ���� ������� ���� ������.", "������", MB_OK|MB_ICONERROR);
		return false;
    }
	//
	CDaoQueryDef QdInetLog( &theApp.m_database );
	CDaoRecordset pRsData(&theApp.m_database);
	COleVariant m_OleVariant;
	CString strSQL;
	CString strParam = "PARAMETERS [parUserID] INTEGER, [parDate] DATETIME;";
	strSQL = strParam + "SELECT PayLog.UserID, InetLog.CompID, InetLog.DateStart, InetLog.Tarif, "
		"InetLog.ElapceTime, InetLog.CalcSum, InetLog.PayLogID, InetLog.ID "
		"FROM PayLog, InetLog "
		"WHERE PayLog.ID=InetLog.PayLogID AND PayLog.UserID = [parUserID] AND DateValue(InetLog.DateStart) = [parDate] "
		"ORDER BY PayLog.UserID, InetLog.CompID, InetLog.ID, InetLog.DateStart ";
	try
	{
		// Temporary
		QdInetLog.Create( "", strSQL );
		// ��������� ��������� (��� ���������, ����)
		m_OleVariant = (long) iUser;
		QdInetLog.SetParamValue( "[parUserID]", m_OleVariant );
		m_OleVariant = m_OleDtTm;
		QdInetLog.SetParamValue( "[parDate]", m_OleVariant );
		// RecordSet
		pRsData.Open(&QdInetLog);
	}
	catch (CDaoException* e)
	{
		AfxMessageBox("������ �������� ��: " + e->m_pErrorInfo->m_strDescription);
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
	char cTemp[100];
	//
	//sprintf (cStr, "����� ������������� ����������� ��������: %s - %s", m_Setup.INomer, m_Setup.IName);
	sprintf (cStr, "����� ������������ ������������ ��������: %s - %s", m_Setup.INomer, m_Setup.IName);
	//CharToOem (cStr, cStr);
	fprintf(fl_txt, "%s\n\n", cStr);
	//
	CObject *ob;
	if (Users.Lookup(iUser, ob))
	{
		CUserInfo *p_TmpUser = (CUserInfo *)ob;
		strcpy(cTemp, p_TmpUser->Info.Fio);
	}
	else
	{
		//strcpy(cTemp, "!!! ����������� ��������");
		strcpy(cTemp, "!!! �������� ��������");
	}
	//
	//CharToOem("������ ������������� ������� ������� ��� ������ � ��������\n", cStr);
	//fprintf(fl_txt, "%s", cStr);
	//fprintf(fl_txt, "%s", "������ ������������� ������� ������� ��� ������ � ��������\n");
	//sprintf (cStr, "� ������ off-���� �� %s\n\n�������� %d (%s)\n\n", sDate, iUser, cTemp);
	fprintf(fl_txt, "%s", "������ ������������ ������� ������� ��� ������ � ��������\n");
	sprintf (cStr, "�� ������ off-���� �� %s\n\n�������� %d (%s)\n\n", sDate, iUser, cTemp);
	//CharToOem (cStr, cStr);
	fprintf(fl_txt,"%s",cStr);
	//
	CTime tCurrTime = CTime::GetCurrentTime();
	//sprintf (cStr, "���� � ����� �������� ������ - %s\n", tCurrTime.Format(_T("%d/%m/%Y %H:%M:%S")) );
	sprintf (cStr, "���� �� ��� ��������� ���� - %s\n", tCurrTime.Format(_T("%d/%m/%Y %H:%M:%S")) );
	//CharToOem (cStr, cStr);
	fprintf(fl_txt,"%s",cStr);
	//
	fprintf(fl_txt,"-------------------------------------------------------------------\n");
	//sprintf (cStr, "%-6s%-11s%-10s%-10s%-10s%-10s%-10s", "�", "|����", "|�����", "|�����", "|����-���", "|�����", "|�");
	sprintf (cStr, "%-6s%-11s%-10s%-10s%-10s%-10s%-10s", "�", "|����", "|���", "|�����", "|����-���", "|����", "|�");
	//CharToOem (cStr, cStr);
	fprintf(fl_txt,"%s\n",cStr);
	//
	//sprintf (cStr, "%-6s%-11s%-10s%-10s%-10s%-10s%-10s", "����.", "|", "|", "|", "|(���)", "|� ���", "|�������");
	sprintf (cStr, "%-6s%-11s%-10s%-10s%-10s%-10s%-10s", "����.", "|", "|", "|", "|(���)", "|� ���", "|�������");
	//CharToOem (cStr, cStr);
	fprintf(fl_txt,"%s\n",cStr);
	fprintf(fl_txt,"-------------------------------------------------------------------\n");
	//
	long iSumElTime =0;
	long iCompElTime =0;
	double dSumClSum=0;
	double dCompClSum=0;
	//
	long iComp = 0;
	double dTmp;
	while ( !pRsData.IsEOF( ) )
	{
		//����� �������
		pRsData.GetFieldValue("CompID", m_OleVariant);
		if (iComp != m_OleVariant.lVal)
		{
			// �� ������ �������
			if (iComp != 0)
			{
				fprintf(fl_txt,"-------------------------------------------------------------------\n");
				//sprintf (cStr, "����� ��������� � %2i:%26d%10.2f", iComp, iCompElTime, dCompClSum);
				sprintf (cStr, "����� ����`���� � %2i:%26d%10.2f", iComp, iCompElTime, dCompClSum);
				//CharToOem (cStr, cStr);
				fprintf(fl_txt, "%s\n", cStr);
				fprintf(fl_txt,"-------------------------------------------------------------------\n");
				iCompElTime =0;
				dCompClSum=0;
			}
			iComp = m_OleVariant.lVal;
		}
		fprintf(fl_txt, "%6i", m_OleVariant.lVal);
		// ����
		pRsData.GetFieldValue("DateStart", m_OleVariant);
		strcpy(cStr, COleDateTime (m_OleVariant).Format( _T("%d/%m/%Y") ) );
		fprintf(fl_txt, "%11s", cStr);
		// �����
		strcpy(cStr, COleDateTime (m_OleVariant).Format( _T("%H:%M:%S") ) );
		fprintf(fl_txt, "%10s", cStr);
		// �����
		pRsData.GetFieldValue("Tarif", m_OleVariant);
		if (m_OleVariant.vt == VT_DECIMAL)
		{
			dTmp = (double) m_OleVariant.decVal.Lo64;
			dTmp = dTmp/pow( (double) 10, m_OleVariant.decVal.scale);
			if (m_OleVariant.decVal.sign == '-')
				dTmp = Round( 0- dTmp, 6 );
			else
				dTmp = Round( dTmp, 6 );
		}
		else
			dTmp = Round( m_OleVariant.dblVal, 6);
		fprintf(fl_txt, "%10.6f", dTmp);
		// ����-���
		pRsData.GetFieldValue("ElapceTime", m_OleVariant);
		fprintf(fl_txt, "%10d", m_OleVariant.lVal);
		iSumElTime += (long) m_OleVariant.lVal;
		iCompElTime += (long) m_OleVariant.lVal;
		// �����
		pRsData.GetFieldValue("CalcSum", m_OleVariant);
		if (m_OleVariant.vt == VT_DECIMAL)
		{
			if (m_OleVariant.decVal.sign == '-')
				dTmp = Round( 0-m_OleVariant.decVal.Lo64/pow( (double) 10, m_OleVariant.decVal.scale), 2 );
			else
				dTmp = Round( m_OleVariant.decVal.Lo64/pow((double) 10, m_OleVariant.decVal.scale), 2 );
		}
		else
			dTmp = Round( m_OleVariant.dblVal, 2 );
		dSumClSum+=dTmp;
		dCompClSum+=dTmp;
		fprintf(fl_txt, "%10.2f", dTmp);
		// ID �������
		pRsData.GetFieldValue("PayLogID", m_OleVariant);
		fprintf(fl_txt, "%10d", m_OleVariant.lVal);
		//
		fprintf(fl_txt,"\n");
		pRsData.MoveNext( );
	}
	pRsData.Close();
	QdInetLog.Close();
	//
	if (iComp != 0)
	{
		fprintf(fl_txt,"-------------------------------------------------------------------\n");
		sprintf (cStr, "����� ����`���� � %2i:%26d%10.2f", iComp, iCompElTime, dCompClSum);
		//CharToOem (cStr, cStr);
		fprintf(fl_txt, "%s\n", cStr);
	}
	fprintf(fl_txt,"-------------------------------------------------------------------\n");
	sprintf (cStr, "%-37s%10d%10.2f", "� � � � � � :", iSumElTime, dSumClSum);
	//CharToOem (cStr, cStr);
	fprintf(fl_txt, "%s\n", cStr);
	fprintf(fl_txt,"-------------------------------------------------------------------\n");
	fclose (fl_txt);
	//
	return true;
}

bool CReportDlg::FormRepPayLog()
{
	// Gets the position of the first selected item in the list view control
	POSITION pTemp = m_Grid.GetFirstSelectedItemPosition();
	if (pTemp == NULL)
	{
		MessageBox("�� ���� ������� �����.\n�� ������ �� ���� ������� ������.",
			"��������", MB_OK|MB_ICONINFORMATION);
		return false;
	}
	// Gets the index of the list item identified by pos, then sets pos to the POSITION value
	int iRow = m_Grid.GetNextSelectedItem(pTemp);
	CString sUser = m_Grid.GetItemText(iRow, 0);
	CString sDate = m_Grid.GetItemText(iRow, 1);
	int iUser = atoi(sUser);
	COleDateTime m_OleDtTm;
	m_OleDtTm.SetDate( atoi(sDate.Mid(6,4)), atoi(sDate.Mid(3,2)), atoi(sDate.Mid(0,2)) );
	// �������
	FILE *fl_txt;
    if ((fl_txt = fopen(cRepFl, "w")) == NULL)
    {
		MessageBox("�� ���� ������� ���� ������.", "������", MB_OK|MB_ICONERROR);
		return false;
    }
	//
	CDaoQueryDef QdInetLog( &theApp.m_database );
	CDaoRecordset pRsData(&theApp.m_database);
	COleVariant m_OleVariant;
	CString strSQL;
	CString strParam = "PARAMETERS [parUserID] INTEGER, [parDate] DATETIME;";
	strSQL = strParam + " SELECT PayLog.UserID, PayLog.ID, PayLog.PayDate, ExtTar.info, "
		"PayLog.ServCnt, PayLog.DepSum, PayLog.CalcSum, PayLog.�hangeSum, "
		"PayLog.NumStud, PayLog.FioStud, PayLog.TarifID "
		"FROM PayLog, ExtTar "
		"WHERE PayLog.TarifID = ExtTar.ID "
		" AND PayLog.UserID = [parUserID] AND DateValue(PayLog.PayDate) = [parDate] "
		"ORDER BY PayLog.UserID, PayLog.TarifID, PayLog.ID, PayLog.PayDate ";
	try
	{
		// Temporary
		QdInetLog.Create( "", strSQL );
		// ��������� ��������� (��� ���������, ����)
		m_OleVariant = (long) iUser;
		QdInetLog.SetParamValue( "[parUserID]", m_OleVariant );
		m_OleVariant = m_OleDtTm;
		QdInetLog.SetParamValue( "[parDate]", m_OleVariant );
		// RecordSet
		pRsData.Open(&QdInetLog);
	}
	catch (CDaoException* e)
	{
		AfxMessageBox("������ �������� ��: " + e->m_pErrorInfo->m_strDescription);
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
	char cTemp[100];
	//
	//sprintf (cStr, "����� ������������� ����������� ��������: %s - %s", m_Setup.INomer, m_Setup.IName);
	sprintf (cStr, "����� ������������ ������������ ��������: %s - %s", m_Setup.INomer, m_Setup.IName);
	fprintf(fl_txt, "%s\n\n", cStr);
	//
	CObject *ob;
	if (Users.Lookup(iUser, ob))
	{
		CUserInfo *p_TmpUser = (CUserInfo *)ob;
		strcpy(cTemp, p_TmpUser->Info.Fio);
	}
	else
	{
		//strcpy(cTemp, "!!! ����������� ��������");
		strcpy(cTemp, "!!! �������� ��������");
	}
	//
	//fprintf(fl_txt, "������ ������ �������� �� %s\n", sDate);
	fprintf(fl_txt, "������ ������� ������� �� %s\n", sDate);
	sprintf (cStr, "\n�������� %d (%s)\n\n", iUser, cTemp);
	fprintf(fl_txt,"%s",cStr);
	//
	CTime tCurrTime = CTime::GetCurrentTime();
	//sprintf (cStr, "���� � ����� �������� ������ - %s\n", tCurrTime.Format(_T("%d/%m/%Y %H:%M:%S")) );
	sprintf (cStr, "���� �� ��� ��������� ���� - %s\n", tCurrTime.Format(_T("%d/%m/%Y %H:%M:%S")) );
	fprintf(fl_txt,"%s",cStr);
	//
	fprintf(fl_txt,"---------------------------------------------------\n");
	sprintf (cStr, "%-10s%-11s%-10s%-10s%-10s", "�", "|����", "|���", "|�-���", "|����");
	fprintf(fl_txt,"%s\n",cStr);
	//
	sprintf (cStr, "%-10s%-11s%-10s%-10s%-10s", "�������", "|", "|", "|������", "|������");
	fprintf(fl_txt,"%s\n",cStr);
	fprintf(fl_txt,"---------------------------------------------------\n");
	//
	long iSumCnt =0;
	long iTarCnt =0;
	double dSumCl=0;
	double dTarCl=0;
	//
	long iPaym = 0;
	CString sTarInfo;
	//
	double dTmp;
	CString sTmp;
	while ( !pRsData.IsEOF( ) )
	{
		// ����� ������
		pRsData.GetFieldValue("TarifID", m_OleVariant);
		if (iPaym != m_OleVariant.lVal)
		{
			// �� ������ ����
			if (iPaym != 0)
			{
				fprintf(fl_txt,"---------------------------------------------------\n");
				sprintf (cStr, "����� %s(%d):", sTarInfo.Left(25).Trim(), iTarCnt);
				sprintf (cStr, "%-41s%10.2f", cStr, dTarCl);
				fprintf(fl_txt, "%s\n", cStr);
				fprintf(fl_txt,"---------------------------------------------------\n");
				iTarCnt=0;
				dTarCl=0;
			}
			iPaym = m_OleVariant.lVal;
			// ������������ ������
			pRsData.GetFieldValue("info", m_OleVariant);
			sprintf(cStr, "%s", m_OleVariant.bstrVal);
			sTarInfo.Format("%s", cStr);
		}
		// ID �������
		pRsData.GetFieldValue("ID", m_OleVariant);
		fprintf(fl_txt, "%10d", m_OleVariant.lVal);
		// ����
		pRsData.GetFieldValue("PayDate", m_OleVariant);
		strcpy(cStr, COleDateTime (m_OleVariant).Format( _T("%d/%m/%Y") ) );
		fprintf(fl_txt, "%11s", cStr);
		// �����
		strcpy(cStr, COleDateTime (m_OleVariant).Format( _T("%H:%M:%S") ) );
		fprintf(fl_txt, "%10s", cStr);
		// �-��
		pRsData.GetFieldValue("ServCnt", m_OleVariant);
		fprintf(fl_txt, "%10d", m_OleVariant.lVal);
		// ����� ������
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
		// �-�� ��������
		iSumCnt++;
		iTarCnt++;
		// ������������
		pRsData.GetFieldValue("NumStud", m_OleVariant);
		if ( !(m_OleVariant.vt == VT_EMPTY || m_OleVariant.vt == VT_NULL) )
		{
			sprintf(cStr, "%s", m_OleVariant.bstrVal);
			fprintf(fl_txt, "\n������������: � %s", cStr);
			pRsData.GetFieldValue("FioStud", m_OleVariant);
			sprintf(cStr, "%s", m_OleVariant.bstrVal);
			fprintf(fl_txt, " ϲ�: %s", cStr);
		}
		//
		fprintf(fl_txt,"\n");
		pRsData.MoveNext( );
	}
	pRsData.Close();
	QdInetLog.Close();
	//
	if (iPaym != 0)
	{
		fprintf(fl_txt,"---------------------------------------------------\n");
		sprintf (cStr, "����� %s(%d):", sTarInfo.Left(25).Trim(), iTarCnt);
		sprintf (cStr, "%-41s%10.2f", cStr, dTarCl);
		fprintf(fl_txt, "%s\n", cStr);
	}
	fprintf(fl_txt,"---------------------------------------------------\n");
	sprintf (cStr, "� � � � � � (%d):", iSumCnt);
	sprintf (cStr, "%-41s%10.2f", cStr, dSumCl);
	fprintf(fl_txt, "%s\n", cStr);
	fprintf(fl_txt,"---------------------------------------------------\n");
	fclose (fl_txt);
	//
	return true;
}
//
void CReportDlg::OnPrint() 
{
	if (iRepType == 1)
	{
		if ( !FormRepInetLog() ) return;
	}
	else
	{
		if ( !FormRepPayLog() ) return;
	}
	ShellExecute (NULL, "open", cExlRep, NULL, NULL, SW_SHOW);
	//ShellExecute (NULL, "open", "report.xls", NULL, NULL, SW_SHOW);
	//
	//SYSTEMTIME lpSystemTime;
	//GetLocalTime(&lpSystemTime);
	//theApp.WriteProfileInt ("��������", "����1", lpSystemTime.wDay);
	//theApp.WriteProfileInt ("��������", "����2", lpSystemTime.wMonth);
	//theApp.WriteProfileInt ("��������", "����3", lpSystemTime.wYear);
	//ASSERT();

}
//
void CReportDlg::OnBnClickedShow()
{
	if (iRepType == 1)
	{
		if ( !FormRepInetLog() ) return;
	}
	else
	{
		if ( !FormRepPayLog() ) return;
	}
	CShowRep DlgShowRep;
	DlgShowRep.sFile = cRepFl;
	DlgShowRep.DoModal();
}
