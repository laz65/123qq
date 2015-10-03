// ChangePasDlg.cpp : implementation file
//

#include "stdafx.h"
#include "InetTarif.h"
#include "ChangePasDlg.h"
#include "UserInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CMapWordToOb Users;
extern int User;
extern _UInfo UInfo;

extern CInetTarifApp theApp;
extern void LogWrite(char *);
/////////////////////////////////////////////////////////////////////////////
// CChangePasDlg dialog
CChangePasDlg::CChangePasDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChangePasDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChangePasDlg)
	m_PwdNew = _T("");
	m_PwdOld = _T("");
	m_PwdRep = _T("");
	//}}AFX_DATA_INIT
}


void CChangePasDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChangePasDlg)
	DDX_Control(pDX, IDC_PWDREP, m_Rep);
	DDX_Control(pDX, IDC_PWDOLD, m_Old);
	DDX_Control(pDX, IDC_PWDNEW, m_New);
	DDX_Text(pDX, IDC_PWDNEW, m_PwdNew);
	DDV_MaxChars(pDX, m_PwdNew, 20);
	DDX_Text(pDX, IDC_PWDOLD, m_PwdOld);
	DDV_MaxChars(pDX, m_PwdOld, 20);
	DDX_Text(pDX, IDC_PWDREP, m_PwdRep);
	DDV_MaxChars(pDX, m_PwdRep, 20);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChangePasDlg, CDialog)
	//{{AFX_MSG_MAP(CChangePasDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChangePasDlg message handlers

void CChangePasDlg::OnOK() 
{
	// TODO: Add extra validation here
	m_Rep.GetWindowText(m_PwdRep);
	m_New.GetWindowText(m_PwdNew);
	m_Old.GetWindowText(m_PwdOld);
	
	if (m_PwdNew!=m_PwdRep) 
	{
		MessageBox("Новый и повторенный пароли не совпадают!","Ошибка",MB_OK|MB_ICONERROR);
		return;
	}

	char * psw = (char*)(LPCSTR)m_PwdOld;

	MD5_CTX context;
	if (!m_First)
	{
		MD5Init (&context);
		MD5Update (&context, (unsigned char *)psw, strlen(psw));
		MD5Final (&context);

		if (!memcmp (context.digest, UInfo.Hash, 16)==0)
		{
			MessageBox("Пароль введен неверно!","Ошибка",MB_OK|MB_ICONERROR);
			return;
		}
		CObject *ob;
		Users.Lookup(User, ob);
		CUserInfo *user	= (CUserInfo *)ob;

		psw = (char*)(LPCSTR)m_PwdNew;
		MD5Init (&context);
		MD5Update (&context, (unsigned char *)psw, strlen(psw));
		MD5Final (&context);
		memcpy(user->Info.Hash, context.digest, 16);

		UInfo = user->Info;

		char Log[100];
		sprintf(Log, "Password for user %s was changed", UInfo.Fio);
		LogWrite(Log);

		theApp.SaveUsers();
	}
	else
	{
		psw = (char*)(LPCSTR)m_PwdNew;
		MD5Init (&context);
		MD5Update (&context, (unsigned char *)psw, strlen(psw));
		MD5Final (&context);
		memcpy(m_Hash, context.digest, 16);
	}

	CDialog::OnOK();
}


void CChangePasDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL CChangePasDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if (m_First)
	{
		SetWindowText("Задание начального пароля");
		CEdit *Ed = (CEdit *)GetDlgItem(IDC_PWDOLD);
		Ed->EnableWindow(false);
		Ed = (CEdit *)GetDlgItem(IDC_PWDNEW);
		Ed->SetFocus();
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
