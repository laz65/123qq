// UserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "InetTarif.h"
#include "UserDlg.h"
#include "UserInfo.h"

extern _UInfo UInfo;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserDlg dialog


CUserDlg::CUserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserDlg)
	m_Super = 2;
	m_Id = 0;
	m_Fio = _T("");
	m_Com = FALSE;
	m_Change = FALSE;
	m_Tarif = FALSE;
	m_Creator = _T("");
	m_Block = FALSE;
	m_Holiday = FALSE;
	m_InetOff = FALSE;
	m_InetOn = FALSE;
	m_Manage = FALSE;
	m_Reboot = FALSE;
	m_Shutdown = FALSE;
	m_Unblock = FALSE;
	//}}AFX_DATA_INIT
}


void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserDlg)
	DDX_Control(pDX, IDC_ID, m_ID);
	DDX_Radio(pDX, IDC_SUPER, m_Super);
	DDX_Text(pDX, IDC_ID, m_Id);
	DDV_MinMaxUInt(pDX, m_Id, 0, 999);
	DDX_Text(pDX, IDC_FIO, m_Fio);
	DDV_MaxChars(pDX, m_Fio, 40);
	DDX_Check(pDX, IDC_COM, m_Com);
	DDX_Check(pDX, IDC_CHANGE, m_Change);
	DDX_Check(pDX, IDC_TARIF, m_Tarif);
	DDX_Text(pDX, IDC_CREATOR, m_Creator);
	DDV_MaxChars(pDX, m_Creator, 40);
	DDX_Check(pDX, IDC_BLOCK, m_Block);
	DDX_Check(pDX, IDC_HOLIDAY, m_Holiday);
	DDX_Check(pDX, IDC_INETOFF, m_InetOff);
	DDX_Check(pDX, IDC_INETON, m_InetOn);
	DDX_Check(pDX, IDC_MANAGE, m_Manage);
	DDX_Check(pDX, IDC_REBOOT, m_Reboot);
	DDX_Check(pDX, IDC_SHUTDOWN, m_Shutdown);
	DDX_Check(pDX, IDC_UNBLOCK, m_Unblock);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUserDlg, CDialog)
	//{{AFX_MSG_MAP(CUserDlg)
	ON_BN_CLICKED(IDC_ADMIN, OnAdmin)
	ON_BN_CLICKED(IDC_USER, OnUser)
	ON_BN_CLICKED(IDC_SUPER, OnUser)
	ON_BN_CLICKED(IDC_MANAGE, OnManage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserDlg message handlers

void CUserDlg::OnAdmin() 
{
	// TODO: Add your control notification handler code here
	SetState(true);
	OnManage();
}


void CUserDlg::OnUser() 
{
	// TODO: Add your control notification handler code here
	SetState(false);
	SetManage(false);
}

BOOL CUserDlg::OnInitDialog() 
{
	if (m_Super==1)
	{
		OnAdmin();
		SetManage(m_Manage);
	}
	else
		OnUser();

	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if (!m_Add) 
	{
		SetWindowText("Изменение существующего пользователя");
		CEdit *Ed = (CEdit *)GetDlgItem(IDC_ID);
		Ed->EnableWindow(false);
	}
	else
	{
		CEdit *Ed = (CEdit *)GetDlgItem(IDC_CREATOR);
		Ed->SetWindowText(UInfo.Fio);
	}

	if (UInfo.Type == UT_ADMIN)
	{
		CButton *Btn = (CButton *)GetDlgItem(IDC_SUPER);
		Btn->EnableWindow(false);
		Btn = (CButton *)GetDlgItem(IDC_ADMIN);
		Btn->EnableWindow(false);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CUserDlg::OnOK() 
{
	extern CMapWordToOb Users;
	// TODO: Add extra validation here
	CObject *ob;
	CString s_Id;
	m_ID.GetWindowText(s_Id);
	m_Id = atoi(s_Id);
	if (m_Add && Users.Lookup(m_Id, ob))
	{
		MessageBox("Пользователь с таким идентифицирующим кодом уже существует!\nСмените код.","Ошибка",MB_OK|MB_ICONERROR);
		return;
	}

	CDialog::OnOK();
}

void CUserDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CUserDlg::OnManage() 
{
	// TODO: Add your control notification handler code here
	CButton *Btn = (CButton *)GetDlgItem(IDC_MANAGE);
	SetManage(Btn->GetCheck());
}

void CUserDlg::SetState(bool State)
{
	CButton *Btn = (CButton *)GetDlgItem(IDC_CHANGE);
	Btn->EnableWindow(State);
	Btn = (CButton *)GetDlgItem(IDC_TARIF);
	Btn->EnableWindow(State);
	Btn = (CButton *)GetDlgItem(IDC_COM);
	Btn->EnableWindow(State);
	Btn = (CButton *)GetDlgItem(IDC_HOLIDAY);
	Btn->EnableWindow(State);
	Btn = (CButton *)GetDlgItem(IDC_MANAGE);
	Btn->EnableWindow(State);
}

void CUserDlg::SetManage(bool State)
{
	CButton *Btn = (CButton *)GetDlgItem(IDC_UNBLOCK);
	Btn->EnableWindow(State);
	Btn = (CButton *)GetDlgItem(IDC_BLOCK);
	Btn->EnableWindow(State);
	Btn = (CButton *)GetDlgItem(IDC_REBOOT);
	Btn->EnableWindow(State);
	Btn = (CButton *)GetDlgItem(IDC_SHUTDOWN);
	Btn->EnableWindow(State);
	Btn = (CButton *)GetDlgItem(IDC_INETON);
	Btn->EnableWindow(State);
	Btn = (CButton *)GetDlgItem(IDC_INETOFF);
	Btn->EnableWindow(State);
}
