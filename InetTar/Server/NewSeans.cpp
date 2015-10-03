// NewSeans.cpp : implementation file
//

#include "stdafx.h"
#include "InetTarif.h"
#include "NewSeans.h"
#include "InetTarifDlg.h"
#include "Stud.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//
extern hCompInfo Computers[MAX_WORKSTATION];
extern void PrintChek(CString strChek);
extern double GetTarif(int Type); 
extern char cClientZalog[100];
extern char fio[50], num[50]; 
extern Setup m_Setup;
extern double nds;


/////////////////////////////////////////////////////////////////////////////
// CNewSeans dialog
// standard constructor
CNewSeans::CNewSeans(CWnd* pParent /*=NULL*/)
	: CDialog(CNewSeans::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewSeans)
	m_sCol = _T("");
	m_ceZalogVal=0;
	//}}AFX_DATA_INIT
	isNal = true;
	isIz = false;
}


void CNewSeans::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewSeans)
	DDX_Control(pDX, IDC_HOUR, m_Hour);
	DDX_Control(pDX, IDC_CHENGHOUR, m_sbH);
	DDX_Control(pDX, IDC_MIN, m_Min);
	DDX_Control(pDX, IDC_CHENGMIN, m_sbM);
	DDX_Control(pDX, IDC_ZALOG, m_ceZalog);
	DDX_Text(pDX, IDC_ZALOG, m_ceZalogVal);
	DDV_MinMaxDouble(pDX, m_ceZalogVal, 0, 999.99);
	DDX_Text(pDX, IDC_COLCOMP, m_sCol);
	DDX_Control(pDX, IDC_TARNAME, m_cbTarNm);
	DDX_Control(pDX, IDC_RASHTYPE, m_stTarif);
	DDX_Control(pDX, IDC_STATIC12, m_stPrin);
	DDX_Control(pDX, IDC_STATIC11, m_stZdach);
	DDX_Control(pDX, IDC_NAL, m_buNal);
	DDX_Control(pDX, IDC_IZ, m_buIz);
	DDX_Control(pDX, IDC_SDACHA, m_csSdacha);
	DDX_Control(pDX, ID_NEWSEANS, m_cbNewSeans);
	DDX_Control(pDX, IDC_PRIEM, m_cePriem);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewSeans, CDialog)
	//{{AFX_MSG_MAP(CNewSeans)
	ON_BN_CLICKED(IDC_NAL, OnNalRb)
	ON_BN_CLICKED(IDC_TIME, OnTimeRb)
	ON_CBN_SELENDOK(IDC_TARNAME, OnSelendokTarname)
	ON_EN_CHANGE(IDC_ZALOG, OnChangeZalog)
	ON_BN_CLICKED(ID_NEWSEANS, OnNewseans)
	ON_WM_SHOWWINDOW()
	ON_EN_CHANGE(IDC_MIN, OnChangeMin)
	ON_EN_CHANGE(IDC_HOUR, OnChangeHour)
	ON_EN_CHANGE(IDC_PRIEM, OnEnChangePriem)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDCANCEL, &CNewSeans::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_IZ, &CNewSeans::OnBnClickedIz)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewSeans message handlers

BOOL CNewSeans::OnInitDialog() 
{
	CDialog::OnInitDialog();
	//
	if (sTitle.Trim() != "")
		SetWindowText(sTitle);
	else 
		m_buIz.EnableWindow(false);
	if (sButTitle.Trim() != "")
		m_cbNewSeans.SetWindowText(sButTitle);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNewSeans::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	//	
	m_ceZalog.SetLimitText(6);
	m_cePriem.SetLimitText(6);
	//
	m_sbM.SetRange( 0, 59 );
	m_sbH.SetRange( 0, 90 );

	//
	m_sCol.Format("%i", iComp);
	//
	m_buNal.SetCheck(1);
	m_cbTarNm.SetCurSel(0);
	if(tarn > 98)
	{
		m_cbTarNm.SetCurSel((tarn/99)-1);
		m_cbTarNm.EnableWindow(false);
	}
	dTarif = GetTarif( m_cbTarNm.GetCurSel() );
	CString sStr;
	sStr.Format("%f", dTarif);
	m_stTarif.SetWindowText( sStr);
	//Flag that indicates whether dialog box is being initialized (FALSE) 
	//or data is being retrieved (TRUE). 
	UpdateData(false);
		/*CFont *font;
	VERIFY(font->CreateFont(
	30,                        // nHeight
	0,                         // nWidth
	0,                         // nEscapement
	0,                         // nOrientation
	FW_NORMAL,                 // nWeight
	TRUE,                     // bItalic
	FALSE,                     // bUnderline
	0,                         // cStrikeOut
	ANSI_CHARSET,              // nCharSet
	OUT_DEFAULT_PRECIS,        // nOutPrecision
	CLIP_DEFAULT_PRECIS,       // nClipPrecision
	DEFAULT_QUALITY,           // nQuality
	DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
	"Arial"));                 // lpszFacename
	/m_sSdacha.SetFont(font);*/
}

void CNewSeans::OnNalRb() 
{
	// TODO: Add your control notification handler code here
	m_ceZalog.EnableWindow(true);
	//
	m_Hour.EnableWindow(false);
	m_sbH.EnableWindow(false);
	m_Min.EnableWindow(false);
	m_sbM.EnableWindow(false);
	m_cePriem.EnableWindow(true);
	m_stPrin.SetWindowText("Принято:   ");
	m_stZdach.SetWindowText("Здача:   ");
	
	//
	isNal = true;
	isIz = false;
}

void CNewSeans::OnTimeRb() 
{
	// TODO: Add your control notification handler code here
	m_ceZalog.EnableWindow(false);
	//
	m_Hour.EnableWindow(true);
	m_sbH.EnableWindow(true);
	m_Min.EnableWindow(true);
	m_sbM.EnableWindow(true);
	m_cePriem.EnableWindow(true);
	m_stPrin.SetWindowText("Принято:   ");
	m_stZdach.SetWindowText("Здача:   ");

	//
	isNal = false;
	isIz = false;
}
//При смене тарифного пакета
void CNewSeans::OnSelendokTarname() 
{
	// TODO: Add your control notification handler code here
	CString sStr;
	int iCurSel = m_cbTarNm.GetCurSel();
	dTarif = GetTarif(iCurSel);
	// Выбран пакет Интернет-студент
	if (iCurSel==2 || iCurSel==3)
	{
		CStud dlg;
		if( dlg.DoModal()==IDOK && strcmp(fio, "")!=0 && strcmp(num,"")!=0 )
		{
			sStr.Format("%f", dTarif);
			m_stTarif.SetWindowText( sStr );
		}
		else
		{
			m_cbTarNm.SetCurSel(0);
			dTarif = GetTarif(0);
			sStr.Format("%f", dTarif);
			m_stTarif.SetWindowText( sStr );
		}
	}
	else 
	{
		sStr.Format("%f", dTarif);
		m_stTarif.SetWindowText( sStr );
	}
	//UpdateData(false);
	//
	if(isNal)
		SetTimeVal();
	else
		SetZalogVal();
}

void CNewSeans::OnNewseans() 
{
	// Проверить
	CString sStr, sPriem;
		if(isIz)
	{
		sStr.Format("%f",Computers[iComp-1].Ostatok-0.01);
		m_cePriem.SetWindowText(sStr);
	}

	m_cePriem.GetWindowText(sPriem);
	m_ceZalog.GetWindowText(sStr);
	//Если сумма даных оператору денег меньше необходимой суммы залога
	if ( atof(sStr) > atof(sPriem) )
	{
		MessageBox("Нельзя принять денег меньше залога!", "Внимание");
		m_cePriem.SetWindowText(sStr);
		m_cePriem.SetFocus();
		return;
	}
	// порядковый номер пакета (0-2)
	tarn = m_cbTarNm.GetCurSel();
	m_ceZalog.GetWindowText(cClientZalog, 10);
	CString sTmp1, sTmp2;
	CString tmpChek;
	int iTmp = (int)(atof(cClientZalog)*100+0.5);
	// Чек служебного внесения только для РФ
	if(m_Setup.UseBoth && m_Setup.UseRF2160)
	{
		if(isIz)
		{
			tmpChek.Format("9$0$%i$Станція N %d", iTmp, iComp);
			PrintChek(tmpChek);
			//
			sTmp1.Format("Напечатан чек изъятия на сумму %.2f.\n"
				"После нажатия кнопки ОК будет произведён запуск сеанса.\n"
				"После нажатия кнопки Cancel будет напечатан залоговый чек.\n"
				"Выполнять?", atof(cClientZalog));
			sTmp2.Format( "Станция № %i", iComp);
		}
		else
		{
			tmpChek.Format("9$1$%i$Станція N %d", iTmp, iComp);
			PrintChek(tmpChek);
			//
			sTmp1.Format("Напечатан залоговый чек на сумму %.2f.\n"
				"После нажатия кнопки ОК будет произведён запуск сеанса.\n"
				"После нажатия кнопки Cancel будет напечатан чек изъятия.\n"
				"Выполнять?", atof(cClientZalog));
			sTmp2.Format( "Станция № %i", iComp);
		}
		//MB_ICONQUESTION
		//MB_ICONASTERISK
		//MB_ICONINFORMATION
	}
	else
	{
		sTmp1.Format("После нажатия кнопки ОК будет произведён запуск сеанса.\nВыполнять?");
		sTmp2.Format( "Станция № %i", iComp);
	}
	if ( MessageBox(sTmp1, sTmp2, MB_OKCANCEL|MB_ICONQUESTION) == IDOK)
	{	

		if(isIz)
		{
			int mm = 20;
			while(--mm > 0) cClientZalog[mm] = cClientZalog[mm-1];
			cClientZalog[0] = '-';
		}

//		Avans->WriteString("avans","iComp",pos);
		CDialog::OnOK();
	}
	else
	{
		if(m_Setup.UseBoth && m_Setup.UseRF2160)
		{
			if(isIz)
			{
				tmpChek.Format("9$1$%i$Станція N %d", iTmp, iComp);
				PrintChek(tmpChek);
			}
			else
			{
				tmpChek.Format("9$0$%i$Станція N %d", iTmp, iComp);
				PrintChek(tmpChek);
			}
		}
		CDialog::OnCancel();
	}
}
void CNewSeans::OnBnClickedCancel()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialog::OnCancel();
}

void CNewSeans::OnChangeZalog() 
{
	// Предположительное к-во часов, минут на введенную сумму
	if(::IsWindow(m_ceZalog.m_hWnd) && m_ceZalog.IsWindowEnabled())
		SetTimeVal();
	//Проверить прем со сдачей
	SetSdachaVal();
	//Кнопка пуск
	CString cStr;
	m_ceZalog.GetWindowText(cStr);
	if ( atof(cStr) > 0 )
	{
		if ( !m_cbNewSeans.IsWindowEnabled() )
			m_cbNewSeans.EnableWindow(true);
	}
	else
	{
		if ( m_cbNewSeans.IsWindowEnabled() )
		m_cbNewSeans.EnableWindow(false);
	}
}

void CNewSeans::OnChangeMin() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	if(::IsWindow(m_Min.m_hWnd) && m_Min.IsWindowEnabled())
		SetZalogVal();
	// TODO: Add your control notification handler code here
}

void CNewSeans::OnChangeHour() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	if(::IsWindow(m_Hour.m_hWnd) && m_Hour.IsWindowEnabled())
		SetZalogVal();
	// TODO: Add your control notification handler code here
}

void CNewSeans::SetZalogVal()
{
	char cMin[2];
	char cHour[2];
	m_Min.GetWindowText(cMin,2);
	m_Hour.GetWindowText(cHour,2);
	char cZalo[10];
	sprintf(cZalo, "%.2f",
		( atoi(cMin)*60+atoi(cHour)*3600 ) * dTarif *  nds   );
	m_ceZalog.SetWindowText(cZalo);
}

void CNewSeans::SetTimeVal()
{
	CString cStr;
	m_ceZalog.GetWindowText(cStr);
	double dSum;
	dSum = atof(cStr);
	int iMin, iHour;
	char cTm[5];
	iMin = (int) floor( dSum / (dTarif* nds *60) );
	iHour = (int) floor( (double) iMin / 60);
	iMin = iMin - iHour*60;
	if( iHour > 99 )
	{
		iHour = 0;
		iMin = 0;
	}
	sprintf(cTm,"%2i", iHour);
	m_Hour.SetWindowText(cTm);
	sprintf(cTm,"%2i", iMin);
	m_Min.SetWindowText(cTm);
}

void CNewSeans::OnEnChangePriem()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	CString sStr, sPriem;
	m_cePriem.GetWindowText(sPriem);
	m_ceZalog.GetWindowText(sStr);
	double dSum;
	dSum = atof(sPriem) - atof(sStr);
	sStr.Format("%.2f",dSum);
	m_csSdacha.SetWindowText(sStr);
}

void CNewSeans::SetSdachaVal()
{
	CString sStr, sPriem;
	if(isIz)
	{
		sStr.Format("%f",Computers[iComp-1].Ostatok);
		m_cePriem.SetWindowText(sStr);
	}
	m_ceZalog.GetWindowText(sStr);
	m_cePriem.GetWindowText(sPriem);
	//Если сумма даных оператору денег меньше необходимой суммы залога
	if ( atof(sStr) > atof(sPriem) )
	{
		if(!isIz) m_cePriem.SetWindowText(sStr);
		//m_csSdacha.SetWindowText("0.00");
	}
	else
	{
		double dSum;
		dSum = atof(sPriem) - atof(sStr);
		sStr.Format("%.2f",dSum);
		m_csSdacha.SetWindowText(sStr);
	}

}

void CNewSeans::OnBnClickedIz()
{
	// TODO: добавьте свой код обработчика уведомлений
		// TODO: Add your control notification handler code here
	m_ceZalog.EnableWindow(true);
	//
	m_Hour.EnableWindow(false);
	m_sbH.EnableWindow(false);
	m_Min.EnableWindow(false);
	m_sbM.EnableWindow(false);
	m_cePriem.EnableWindow(false);
	m_stPrin.SetWindowText("В наличии:   ");
	m_stZdach.SetWindowText("Остаток:   ");

	//
	isNal = true;
	isIz = true;
}
