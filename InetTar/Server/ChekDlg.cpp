// ChekDlg.cpp : implementation file
//

#include "stdafx.h"
#include "InetTarif.h"
#include "ChekDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern Setup m_Setup;
extern int User;
extern double nds;

extern double GetTarif(int Type); 

extern CInetTarifApp theApp;
extern void PrintChek(CString strChek);
extern CList <hDopusl, hDopusl&> UslList;
extern void ShowOperSum(long lZalog, long lPriem);
/////////////////////////////////////////////////////////////////////////////
// ChekDlg dialog
/////////////////////////////////////////////////////////////////////////////


ChekDlg::ChekDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ChekDlg::IDD, pParent)
	//, m_DopKol(0)
{
	//{{AFX_DATA_INIT(ChekDlg)
	//}}AFX_DATA_INIT
}


void ChekDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ChekDlg)
	DDX_Control(pDX, IDC_DOPUSL, m_doplist);
	DDX_Control(pDX, IDC_DOPSUMM, m_sum);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_PRIEM, m_cePriem);
	DDX_Control(pDX, IDC_SDACHA, m_csSdacha);
	DDX_Control(pDX, IDC_TAR, m_tar);
	DDX_Control(pDX, IDC_DOPKOL, m_cntusl);
	DDX_Control(pDX, IDC_CHECK1, m_check1);
	DDX_Control(pDX, IDC_STATIC8, m_TarTypeInfo);
	//DDX_Text(pDX, IDC_DOPKOL, m_DopKol);
	//DDV_MinMaxInt(pDX, m_DopKol, 0, 9999);
}


BEGIN_MESSAGE_MAP(ChekDlg, CDialog)
	//{{AFX_MSG_MAP(ChekDlg)
	ON_CBN_SELCHANGE(IDC_DOPUSL, OnSelchangeDopusl)
	ON_EN_CHANGE(IDC_DOPKOL, &ChekDlg::OnChangeDopkol)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_PRIEM, &ChekDlg::OnEnChangePriem)
	ON_BN_CLICKED(IDC_CHECK1, &ChekDlg::OnBnClickedCheck1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ChekDlg message handlers
BOOL ChekDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	GetTarif(0); 
	CFont *font = new CFont();
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
	//
	m_doplist.ResetContent();
	pos = UslList.GetHeadPosition();
	//UslList.GetNext(pos);
	for (int i=0;i < UslList.GetCount() ;i++)
	{
		tempusl = UslList.GetNext(pos);
		m_doplist.InsertString(i,tempusl.name);
	}
	m_doplist.DeleteString(0);
	m_doplist.SetCurSel(0);
	//
	m_sum.SetFont(font);
	m_csSdacha.SetFont(font);
	//
	SetTarif( m_doplist.GetCurSel() );
	//
	SumOpl = 0;
	m_cntusl.SetLimitText(4);
	m_cePriem.SetLimitText(10);
	//
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void ChekDlg::SetTarif(int iPos)
{
	int i;
	CString sStr;
	pos = UslList.GetHeadPosition();
	tempusl = UslList.GetNext(pos);
	for (i=0;i < iPos+1 ;i++)
	{
		tempusl = UslList.GetNext(pos);
	}
	dTarif = tempusl.tarif;
	iCodeUsl = tempusl.rf_code;
	iID = tempusl.nomusl;
	iRfRate = tempusl.rf_rate;
	iTarType = tempusl.tar_type;
	strcpy(cCodeInfo, tempusl.rf_name);
	// 28.12.2009
	if (iTarType == 1)
	{
		m_TarTypeInfo.SetWindowText("Тариф без НДС, грн.:");
	}
	else
	{
		m_TarTypeInfo.SetWindowText("Стоимость товара, грн.:");
	}
	//
	sStr.Format("%f", dTarif);
	m_tar.SetWindowText( sStr );
}
//
void ChekDlg::OnSelchangeDopusl() 
{
	// TODO: Add your control notification handler code here
	SetTarif( m_doplist.GetCurSel() );
	//
	CString sStr;
	m_cntusl.GetWindowText(sStr);
	char cZalo[100];
	// 28.12.2009
	if (iTarType == 1)
	{
		sprintf(cZalo, "%.2f", Round( atof(sStr) * dTarif *  nds , 2 ) );
	}
	else
	{
		sprintf(cZalo, "%.2f", Round( atof(sStr) * dTarif, 2 ) );
	}
	m_sum.SetWindowText(cZalo);
	m_cePriem.SetWindowText("0");
	m_csSdacha.SetWindowText("0");
}
//
void ChekDlg::OnChangeDopkol() 
{
	CString sStr;
	m_cntusl.GetWindowText(sStr);
	char cZalo[100];
	// 28.12.2009
	if (iTarType == 1)
	{
		sprintf(cZalo, "%.2f", Round( atof(sStr) * dTarif *  nds , 2 ) );
	}
	else
	{
		sprintf(cZalo, "%.2f", Round( atof(sStr) * dTarif, 2 ) );
	}
	m_sum.SetWindowText(cZalo);
	m_cePriem.SetWindowText("0");
	m_csSdacha.SetWindowText("0");
}
//
void ChekDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	CDialog::OnCancel();
}
// Для красного цвета
HBRUSH ChekDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if (pWnd->GetDlgCtrlID() == IDC_DOPSUMM)
	   {
		  // Set the text color to red
		  pDC->SetTextColor(RGB(255, 0, 0));
		  // Set the background mode for text to transparent 
		  // so background will show thru.
	   }
	if (pWnd->GetDlgCtrlID() == IDC_SDACHA)
   {
	  // Set the text color to red
	  pDC->SetTextColor(RGB(0, 128, 0));
	  // Set the background mode for text to transparent 
	  // so background will show thru.
   }
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
//
void ChekDlg::OnOK() 
{
	// Проверить
	CString sStr, sPriem;
	m_cePriem.GetWindowText(sPriem);
	m_sum.GetWindowText(sStr);
	float fSumUsl = atof(sStr);
	float fSumPriem = atof(sPriem);
	//Если сумма даных оператору денег меньше необходимой суммы залога
	if ( fSumUsl > fSumPriem )
	{
		MessageBox("Нельзя принять денег меньше стоимости услуги!", "Внимание" ,MB_OK|MB_ICONEXCLAMATION);
		m_cePriem.SetWindowText(sStr);
		m_cePriem.SetFocus();
		return;
	}
	long iUsl = Round(fSumUsl*100, 0);
	long iPriem = Round(fSumPriem*100, 0);
	// Записать данные в журнал оплат
	// Дата, время окончательного расчета
	CTime time = CTime::GetCurrentTime();
	m_cntusl.GetWindowText(sStr);
	int iCnt = atoi(sStr);
	//оператор, дата, код тарифа, к-во услуг, принято, начислено, сдача, № студ, ФИО студ
	int iPayID = theApp.InsPayLog(User, time, iID, iCnt, iPriem, iUsl, iPriem-iUsl, "", "");
	if (iPayID <= 0)
	{
		MessageBox ("Ошибка записи данных в журнал платежей.", "Ошибка", MB_OK|MB_ICONERROR);
	}
	// Чек только для РФ
	if(m_Setup.UseRF2160)
	{
		char str_z[500];
		sprintf (str_z, cCodeInfo); 
		//CharToOem (cCodeInfo, str_z);
		CString chek;
		// 08.12.2009 iRfRate
		//chek.Format("P$%i$1$0$1$0$1$%s$%d$999000\n!$%i$1000\n2$%d\n", iCodeUsl, str_z, iUsl, iCodeUsl, iPriem);
		if (m_check1.GetCheck()) // оплата карточкой
		chek.Format("P$%i$%i$0$1$0$1$%s$%d$999000\n!$%i$1000\n2$%d$4\n", iCodeUsl, iRfRate, str_z, iUsl, iCodeUsl, iPriem);
		else
		chek.Format("P$%i$%i$0$1$0$1$%s$%d$999000\n!$%i$1000\n2$%d$0\n", iCodeUsl, iRfRate, str_z, iUsl, iCodeUsl, iPriem);
		PrintChek(chek);
		//
		sStr.Format("Напечатан чек на сумму %.2f.", fSumUsl);
		MessageBox(sStr, "Информация", MB_OK|MB_ICONINFORMATION);
	}
	else
	{
		MessageBox("Не могу напечатать чек.", "Информация", MB_OK|MB_ICONINFORMATION);
	}
	//
	SumOpl = iUsl;
	//
	CDialog::OnOK();
}

void ChekDlg::OnEnChangePriem()
{
	CString sStr, sPriem;
	m_cePriem.GetWindowText(sPriem);
	m_sum.GetWindowText(sStr);
	double dSum;
	dSum = atof(sPriem) - atof(sStr);
	sStr.Format("%.2f",dSum);
	m_csSdacha.SetWindowText(sStr);
}

void ChekDlg::OnBnClickedCheck1()
{
	CString sStr;
	if (m_check1.GetCheck())
	{
		m_sum.GetWindowText(sStr);
		m_cePriem.SetWindowText(sStr);
		m_cePriem.EnableWindow(false) ;
	}
	else m_cePriem.EnableWindow(true) ;
	// TODO: добавьте свой код обработчика уведомлений
}
