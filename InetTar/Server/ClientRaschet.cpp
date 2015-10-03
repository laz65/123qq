// ClientRaschet.cpp : implementation file
// 

#include "stdafx.h"
#include "InetTarif.h"
#include "ClientRaschet.h"
#include "ReportDlg.h"
#include <time.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern void LogWrite(char *text);
extern int User;
extern char card_flag;
extern void PrintChek(CString strChek);
extern double nds;
/////////////////////////////////////////////////////////////////////////////
extern hSetup m_Setup;
extern CInetTarifApp theApp;
//extern double Round(double dSum);
/////////////////////////////////////////////////////////////////////////////
//	DDX_Control(pDX, IDC_OSTATOK, m_Ostatok);
/////////////////////////////////////////////////////////////////////////////
// CClientRaschet dialog
CClientRaschet::CClientRaschet(CWnd* pParent /*=NULL*/)
	: CDialog(CClientRaschet::IDD, pParent)
	, m_sCol(_T(""))
{
	//{{AFX_DATA_INIT(CClientRaschet)
	m_InUseVal = _T("");
	m_ISPTimeVal = _T("");
	m_OstatokVal = _T("");
	m_ZalogVal = _T("");
	AllZalog = 0;
	PriemCops = 0;
	//}}AFX_DATA_INIT
}


void CClientRaschet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientRaschet)
	DDX_Control(pDX, IDC_OST, m_StaticOst);
	DDX_Text(pDX, IDC_INUSE, m_InUseVal);
	DDX_Text(pDX, IDC_ISPTIME, m_ISPTimeVal);
	DDX_Text(pDX, IDC_OSTATOK, m_OstatokVal);
	DDX_Text(pDX, IDC_ZALOG, m_ZalogVal);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_COLCOMP, m_sCol);
}


BEGIN_MESSAGE_MAP(CClientRaschet, CDialog)
	//{{AFX_MSG_MAP(CClientRaschet)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientRaschet message handlers

BOOL CClientRaschet::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	#ifdef _LOG_ITAR
		sprintf(LogBuffer, "Cтанция №%i - Расчет клиента", Comp->NumbComp+1);
		SetWindowText(LogBuffer);
	#endif
	//
	m_sCol.Format("%i", Comp->NumbComp+1);
	//
	double AllSum = 0.0;
	int AllTime = 0;
	// Если была смена тарифов во время работы
	if (Comp->nBills>0)
	{
		for (int i=0; i<Comp->nBills;i++)
		{
			if(Comp->Bills[i].Sum > 0) if (i>0) Comp->Bills[i].Sum -= Comp->Bills[i-1].Sum ;
			if(Comp->Bills[i].Time > 0) if (i>0) Comp->Bills[i].Time -= Comp->Bills[i-1].Time ;
		}
	}
	// Добавить еще не рассчитанное
	if(Comp->Elapce > 0) AllTime = Comp->Elapce;
	// Начисленная сумма последней части сеанса
	// Поскольку расчет от обратного, будем округлять уже итоговую сумму с НДС
	double fSum = 0;
	//double fSum = Round(Comp->Tarif * Comp->Elapce);
	//double fNds = Round(fSum * 0.2);
	//fSum += fNds;
	//
	if(Comp->Elapce > 1800) fSum = Round(Comp->Tarif * Comp->Elapce *  nds , 2);
	else if(Comp->Elapce > 0) fSum = Round(Comp->Tarif * 1800 *  nds , 2);
	AllSum = fSum;
	if ( Comp->AllZalog < AllSum ) AllSum = Comp->AllZalog;
	double Ostatok = Comp->AllZalog - AllSum;
	// Начислено в копейках
	iCops = Round(AllSum*100, 0);
	m_InUseVal.Format("%.2f", AllSum);
	m_ISPTimeVal.Format( "%.2i:%.2i:%.2i", (int)(AllTime/3600), (int)(((AllTime-(int)(AllTime/3600)*3600))/60),
		(int)(AllTime-(int)(AllTime/60)*60) );
	m_OstatokVal.Format("%.2f", Ostatok);
	m_ZalogVal.Format("%.2f", Comp->AllZalog);
	m_CompChar.Format("%d", Comp->NumbComp+1);
	// Если перебрали сумму
	if ( Ostatok < 0 )
	{
		m_StaticOst.SetWindowText("Доплата");
		m_OstatokVal.Format("%.2f", 0-Ostatok);
	}
	else
	{
		m_OstatokVal.Format("%.2f", Ostatok);
	}
	// Обновить значения переменных in dialog wnd
	UpdateData(FALSE);
	// Записать данные в журнал оплат
	// Дата, время окончательного расчета
	CTime time = CTime::GetCurrentTime();
	// Залог в копейках
	long iAllZal = Round(Comp->AllZalog*100, 0);
	if (iCops > iAllZal) //Если необходима доплата
		iAllZal = iCops;
	// 20.05.2009 - чтобы вернуть в вызывающий класс
	AllZalog = iAllZal;
	PriemCops = iCops;
	//оператор, дата, код тарифа, к-во, zalog*100, sum*100, sdacha*100
	int iPayID = theApp.InsPayLog(User, time, 1, 1, iAllZal, iCops, iAllZal-iCops, Comp->sStudNum, Comp->sStudFio);
	if (iPayID <= 0)
	{
		MessageBox ("Ошибка записи данных в журнал платежей.", "Ошибка", MB_OK|MB_ICONERROR);
	}
	// Записать данные в журнал соединений
	if (Comp->nBills>0)
	{
		for (int i=0; i<Comp->nBills;i++)
		{
			int iConn = theApp.InsInetLog(Comp->NumbComp+1, iPayID, (CTime) Comp->Bills[i].TimeBeg, 
				Comp->Bills[i].Tarif, Comp->Bills[i].Time, 0); // Comp->Bills[i].Sum);
			if (iConn <= 0)
			{
				MessageBox ("Ошибка записи данных в журнал соединений.", "Ошибка", MB_OK|MB_ICONERROR);
			}
		}
	}
	int iConn = theApp.InsInetLog(Comp->NumbComp+1, iPayID, (CTime) Comp->DateTimeBeg, Comp->Tarif, Comp->Elapce, fSum);
	if (iConn <= 0)
	{
		MessageBox ("Ошибка записи данных в журнал соединений.", "Ошибка", MB_OK|MB_ICONERROR);
	}
	//ClearComp(Comp);
	//
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CClientRaschet::OnOK() 
{
	// TODO: Add extra validation here
	#ifdef _LOG_ITAR
		sprintf (LogBuffer, "		Статистика: залог - %s, секунд - %s, сумма - %s, остаток - %s",
			(char*)(LPCSTR) m_ZalogVal, (char*)(LPCSTR) m_ISPTimeVal,(char*)(LPCSTR) m_InUseVal,
			(char*)(LPCSTR) m_OstatokVal);
		LogWrite (LogBuffer);
	#endif

	CDialog::OnOK();
}

void CClientRaschet::OnDestroy() 
{
	CDialog::OnDestroy();
	// TODO: Add your message handler code here

	//Вывод на кассовый аппарат
	if (m_Setup.UseCassa==false)
	{
		return ;
	}
	// Если вывод на Самсунг
	if (m_Setup.UseRF2160==false)
	{
		int pLen = strlen(m_Setup.PathBill);
		char billName[300];
		strcpy (billName, m_Setup.PathBill);
		// Если путь не заканчивается палками
		if (m_Setup.PathBill[pLen-2]!='\\')
 			strncat (billName, "\\", 1);
		if (m_Setup.PathBill[pLen-1]!='\\')
 			strncat (billName, "\\", 1);
		//
		strcat (billName, "it.bil");
		FILE *Stream;
		Stream = fopen("temp.bil", "w");
		//int Comp=1;
		//
		char str[100];
		sprintf (str, "@КОМПЬЮТЕР %2s1#\n", (LPCSTR)m_CompChar);
		//CharToOem (str,str);
		fprintf (Stream , str );
		//
		sprintf (str, "@ИНТЕРН. УСЛ.1#\n");
		//CharToOem (str,str);
		fprintf (Stream , str );
		//
		sprintf (str, "@К ВЫПЛАТЕ   %dWO\n", iCops);
		//CharToOem (str,str);
		fprintf (Stream , str );
		//
		fclose (Stream );
		//
		CopyFile( "temp.bil", billName, false);
		//
		#ifdef _LOG_ITAR
			sprintf (LogBuffer, "Create .bil file & Leave Client Rashet Dialog");
			LogWrite (LogBuffer);
		#endif
	}
	else  // Вывод на РФ Экспотрейд
	{
		CString chek;
		// Залог в копейках
		int iAllZal = Round(atof(m_ZalogVal)*100, 0);
		if (iCops > 0) // Если что-то начислено 
		{
			int iOfferSum;
			if (iCops > iAllZal) //Если необходима доплата
				iOfferSum = iCops;
			else
				iOfferSum = iAllZal;
			//CString	chek("Z$\nI$ш$Z\n");
			//	chek.AnsiToOem();
			char str[100], str1[100];
			
			sprintf (str, "IНТЕРНЕТ/КОР КОМП");
			sprintf (str1, "Станція № %2s ", (LPCSTR)m_CompChar);//CompNum);
			//CharToOem (str, str);
			//CharToOem (str1, str1);
			CString	chek;
			CString	temp_sum;
			temp_sum.Format("Сумма проплаты %d. Если проплата картой прошла нажмите ОК, при отказе будет выдан чек на проплату наличными!", iCops);
			if(m_Setup.UseBoth)
			{
				// Служебное изъятие iAllZal, чек на продажу товара по коду 100 в к-ве iCops*10 (3 знака после зпт)
				// Предложенная сумма iOfferSum
				if (card_flag == 1)
				{					
					if (MessageBox(temp_sum, "Оплата картой!!!", MB_OKCANCEL|MB_ICONWARNING) == IDOK)
					chek.Format("9$0$%d$Станція N %2s\nP$100$1$0$1$0$1$%s$%d$999000\n@$%s\n!$100$1000\n2$%d$4\n", iAllZal, (LPCSTR)m_CompChar, str, iCops, str1, iOfferSum);
					else
					chek.Format("9$0$%d$Станція N %2s\nP$100$1$0$1$0$1$%s$%d$999000\n@$%s\n!$100$1000\n2$%d$0\n", iAllZal, (LPCSTR)m_CompChar, str, iCops, str1, iOfferSum);
				}
				else
				chek.Format("9$0$%d$Станція N %2s\nP$100$1$0$1$0$1$%s$%d$999000\n@$%s\n!$100$1000\n2$%d$0\n", iAllZal, (LPCSTR)m_CompChar, str, iCops, str1, iOfferSum);
			}
			else
			{
				// Просто чек на продажу товара по коду 100 в к-ве iCops*10 (3 знака после зпт) 
				// с предложенной суммой iOfferSum
				if (card_flag == 1)
				{
					if ( MessageBox(temp_sum, "Оплата картой!!!", MB_OKCANCEL|MB_ICONWARNING) == IDOK)
					chek.Format("P$100$1$0$1$0$1$%s$%d$999000\n@$%s\n!$100$1000\n2$%d$4\n", str, iCops, str1, iOfferSum);
					else
					chek.Format("P$100$1$0$1$0$1$%s$%d$999000\n@$%s\n!$100$1000\n2$%d$0\n", str, iCops, str1, iOfferSum);
				}
				else
				chek.Format("P$100$1$0$1$0$1$%s$%d$999000\n@$%s\n!$100$1000\n2$%d$0\n", str, iCops, str1, iOfferSum);
			}
			PrintChek(chek);
		}
		else  // Если взяли залог служебным внесением - вернуть
			if(m_Setup.UseBoth)
			{
				chek.Format("9$0$%i$Станція N %2s\n",iAllZal,(LPCSTR)m_CompChar);
				PrintChek(chek);
			}
		#ifdef _LOG_ITAR
			sprintf (LogBuffer, "Создан файл чека для РФ. Выход из окна окончательного расчета");
			LogWrite (LogBuffer);
		#endif
	}  // Вывод на РФ Экспотрейд
}
