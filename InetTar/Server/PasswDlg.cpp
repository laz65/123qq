// PasswDlg.cpp : implementation file
//

#include "stdafx.h"
#include "InetTarif.h"
#include "PasswDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPasswDlg dialog


CPasswDlg::CPasswDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPasswDlg::IDD, pParent)
{
	//pParent = NULL;
	//{{AFX_DATA_INIT(CPasswDlg)
	m_Password = _T("");
	m_Id = 0;
	//}}AFX_DATA_INIT
}


void CPasswDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPasswDlg)
	DDX_Control(pDX, IDC_PASSWEDIT, m_Psw);
	DDX_Text(pDX, IDC_PASSWEDIT, m_Password);
	DDV_MaxChars(pDX, m_Password, 20);
	DDX_Text(pDX, IDC_IDEDIT, m_Id);
	DDV_MinMaxUInt(pDX, m_Id, 0, 999);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPasswDlg, CDialog)
	//{{AFX_MSG_MAP(CPasswDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPasswDlg message handlers
//extern bool m_GlobalBlock;
void CPasswDlg::OnOK() 
{
	// TODO: Add extra validation here

	m_Psw.GetWindowText(m_Password);
	
	CDialog::OnOK();
}

BOOL CPasswDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	//m_GlobalBlock = false;
	return CDialog::DestroyWindow();
}

void CPasswDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
