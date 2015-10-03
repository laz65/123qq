// NewEdit.cpp : implementation file
//

#include "stdafx.h"
#include "InetTarif.h"
#include "TarifEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTarifEdit dialog


CTarifEdit::CTarifEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CTarifEdit::IDD, pParent)
	, m_RfRate(0)
	, m_TarType(0)
{
	//{{AFX_DATA_INIT(CTarifEdit)
	m_Name = _T("Новий");
	m_Tarif = 0.0f;
	m_RfCode = 0;
	m_RfName = _T("Новий");
	m_RfRate = 1;
	m_TarType = 1;
	//}}AFX_DATA_INIT
}


void CTarifEdit::DoDataExchange(CDataExchange* pDX)
{
	// заменено 40 на 39, 20 на 19 - из-за невозм-ти изменить структуру доп.услуг(поддержка старых установок)
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NAME, m_Name);
	DDX_Text(pDX, IDC_TAR, m_Tarif);
	DDX_Text(pDX, IDC_RFCODE, m_RfCode);
	DDX_Text(pDX, IDC_RFNAME,m_RfName);
	DDV_MaxChars(pDX, m_Name, 39);
	DDV_MinMaxFloat(pDX, m_Tarif, 0, 999.99999999);
	DDV_MinMaxInt(pDX, m_RfCode, 400, 499);
	DDV_MaxChars(pDX, m_RfName, 19);
	DDX_Control(pDX, IDC_NAME, m_EdName);
	DDX_Control(pDX, IDC_RFNAME, m_EdRfName);
	DDX_Text(pDX, IDC_RFRATE, m_RfRate);
	DDV_MinMaxInt(pDX, m_RfRate, 1, 9);
	DDX_Text(pDX, IDC_TARTYPE, m_TarType);
	DDV_MinMaxInt(pDX, m_TarType, 1, 2);
}


BEGIN_MESSAGE_MAP(CTarifEdit, CDialog)
	//{{AFX_MSG_MAP(CTarifEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTarifEdit message handlers
BOOL CTarifEdit::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_EdName.SetLimitText(39);
	m_EdRfName.SetLimitText(19);
	return TRUE;
}
void CTarifEdit::OnOK() 
{
	// TODO: Add extra validation here
	CDialog::OnOK();
}

void CTarifEdit::OnCancel() 
{
	// TODO: Add extra cleanup here
	CDialog::OnCancel();
}
