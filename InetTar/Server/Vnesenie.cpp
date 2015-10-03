// Vnesenie.cpp : implementation file
//

#include "stdafx.h"
#include "InetTarif.h"
#include "Vnesenie.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVnesenie dialog
CVnesenie::CVnesenie(CWnd* pParent /*=NULL*/)
	: CDialog(CVnesenie::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVnesenie)
	m_KopSum = 0;
	//}}AFX_DATA_INIT
}


void CVnesenie::DoDataExchange(CDataExchange* pDX)
{
	CString cStr;
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVnesenie)
	DDX_Control(pDX, IDC_VNESS, m_Vness);
//	DDX_Text(pDX, IDC_VNESS, m_KopSum);
	DDX_Text(pDX, IDC_VNESS, cStr);
	m_KopSum = atoi(cStr);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVnesenie, CDialog)
	//{{AFX_MSG_MAP(CVnesenie)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVnesenie message handlers
BOOL CVnesenie::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetWindowText(sTitle);
	//m_Vness.SetWindowText("0");
	// TODO: Add extra initialization here
	//m_Vness.SetWindowText(temp);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CVnesenie::OnOK() 
{
	CString cStr;
	m_Vness.GetWindowText(cStr);
	if (atoi(cStr) <= 0)
	{
		MessageBox("Указанная сумма недостаточна!", "Внимание", MB_OK|MB_ICONEXCLAMATION);
		return;
	}
	CDialog::OnOK();
}
