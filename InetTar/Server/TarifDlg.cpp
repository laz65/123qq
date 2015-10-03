// TarifDlg.cpp : implementation file
//

#include "stdafx.h"
#include "InetTarif.h"
#include "TarifDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern void LogWrite(char *text);
/////////////////////////////////////////////////////////////////////////////
// CTarifDlg dialog


CTarifDlg::CTarifDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTarifDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTarifDlg)
	//}}AFX_DATA_INIT
}


void CTarifDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTarifDlg)
	DDX_Control(pDX, IDC_CurNds, m_CurNds);
	DDX_Control(pDX, IDC_TARIF8, m_TarifCtrl8);
	DDX_Control(pDX, IDC_TARIF7, m_TarifCtrl7);
	DDX_Control(pDX, IDC_TARIF6, m_TarifCtrl6);
	DDX_Control(pDX, IDC_TARIF5, m_TarifCtrl5);
	DDX_Control(pDX, IDC_TARIF4, m_TarifCtrl4);
	DDX_Control(pDX, IDC_TARIF3, m_TarifCtrl3);
	DDX_Control(pDX, IDC_TARIF2, m_TarifCtrl2);
	DDX_Control(pDX, IDC_TARIF1, m_TarifCtrl1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTarifDlg, CDialog)
	//{{AFX_MSG_MAP(CTarifDlg)
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_TARIF1, &CTarifDlg::OnEnChangeTarif1)
	ON_EN_CHANGE(IDC_CurNds, &CTarifDlg::OnEnChangeCurnds)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTarifDlg message handlers
extern hSetup m_Setup;
extern CInetTarifApp theApp;


void CTarifDlg::OnOK() 
{
	// TODO: Add extra validation here


	CString m_Edit;
	
	m_TarifCtrl1.GetWindowText(m_Edit);
	m_Setup.Tarif1=atof((LPCSTR) m_Edit);

	m_TarifCtrl2.GetWindowText(m_Edit);
	m_Setup.Tarif2=atof((LPCSTR) m_Edit);


	m_TarifCtrl3.GetWindowText(m_Edit);
	m_Setup.Tarif3=atof((LPCSTR) m_Edit);

	m_TarifCtrl4.GetWindowText(m_Edit);
	m_Setup.Tarif4=atof((LPCSTR) m_Edit);


	m_TarifCtrl5.GetWindowText(m_Edit);
	m_Setup.Tarif5=atof((LPCSTR) m_Edit);

	m_TarifCtrl6.GetWindowText(m_Edit);
	m_Setup.Tarif6=atof((LPCSTR) m_Edit);

	m_TarifCtrl7.GetWindowText(m_Edit);
	m_Setup.Tarif7=atof((LPCSTR) m_Edit);

	m_TarifCtrl8.GetWindowText(m_Edit);
	m_Setup.Tarif8=atof((LPCSTR) m_Edit);

//!!!! Для изменения НДС
	m_CurNds.GetWindowText(m_Edit);
	m_Setup.CurNds=atof((LPCSTR) m_Edit);

	
	#ifdef _LOG_ITAR
		char LogBuffer[200];
		sprintf (LogBuffer, "Change Tarif.");
		LogWrite (LogBuffer);
	#endif

	theApp.SaveProfiles();

	CDialog::OnOK();
}

BOOL CTarifDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	CString TempTarif;
	char TempStr[10];
	
	sprintf (TempStr, "%f", m_Setup.Tarif1);
	TempTarif = TempStr;
	m_TarifCtrl1.SetWindowText(TempTarif);
	
	sprintf (TempStr, "%f", m_Setup.Tarif2);
	TempTarif = TempStr;
	m_TarifCtrl2.SetWindowText(TempTarif);


	sprintf (TempStr, "%f", m_Setup.Tarif3);
	TempTarif = TempStr;
	m_TarifCtrl3.SetWindowText(TempTarif);
	
	sprintf (TempStr, "%f", m_Setup.Tarif4);
	TempTarif = TempStr;
	m_TarifCtrl4.SetWindowText(TempTarif);
	

	sprintf (TempStr, "%f", m_Setup.Tarif5);
	TempTarif = TempStr;
	m_TarifCtrl5.SetWindowText(TempTarif);
	
	sprintf (TempStr, "%f", m_Setup.Tarif6);
	TempTarif = TempStr;
	m_TarifCtrl6.SetWindowText(TempTarif);

	sprintf (TempStr, "%f", m_Setup.Tarif7);
	TempTarif = TempStr;
	m_TarifCtrl7.SetWindowText(TempTarif);
	
	sprintf (TempStr, "%f", m_Setup.Tarif8);
	TempTarif = TempStr;
	m_TarifCtrl8.SetWindowText(TempTarif);

//!!!! Для изменения НДС
	sprintf (TempStr, "%f", m_Setup.CurNds);
	TempTarif = TempStr;
	m_CurNds.SetWindowText(TempTarif);


	#ifdef _LOG_ITAR
		char LogBuffer[200];
		sprintf (LogBuffer, "Enter to Tarif Dialog.");
		LogWrite (LogBuffer);
	#endif
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTarifDlg::OnEnChangeTarif1()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}

void CTarifDlg::OnEnChangeCurnds()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}
