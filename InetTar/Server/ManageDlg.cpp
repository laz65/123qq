// ManageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "InetTarif.h"
#include "ManageDlg.h"
#include "UserInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern hSetup m_Setup;
extern _UInfo UInfo;
//
extern BOOL UnLockStation(int Comp);
extern BOOL LockStation(int Comp);
extern BOOL ShutdownStation(int Comp);
extern BOOL ResetStation(int Comp);
extern BOOL StopStation(int Comp);
extern BOOL StartInetStation(int Comp);
extern BOOL StopInetStation(int Comp);

/////////////////////////////////////////////////////////////////////////////
// CManageDlg dialog


CManageDlg::CManageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CManageDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CManageDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CManageDlg)
	DDX_Control(pDX, IDC_OPERATION, m_Oper);
	DDX_Control(pDX, IDC_COMP, m_Comp);
	DDX_Control(pDX, IDC_ALL, m_All);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CManageDlg, CDialog)
	//{{AFX_MSG_MAP(CManageDlg)
	ON_NOTIFY(NM_DBLCLK, IDC_COMP, OnDblclkComp)
	ON_BN_CLICKED(IDC_ALL, OnAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CManageDlg message handlers
//
BOOL CManageDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if (!img.GetSafeHandle()) 
	{
		img.Create(16,16,ILC_COLOR, 1,1);
		img.Add(AfxGetApp()->LoadIcon(IDI_COMP));//&b,RGB(0xff,0,0));
	}

	m_Comp.DeleteAllItems();
	m_Comp.SetExtendedStyle(LVS_EX_CHECKBOXES|LVS_EX_FULLROWSELECT);
	m_Comp.SetImageList(&img, LVSIL_SMALL);
	m_Comp.InsertColumn(0, "Станция", LVCFMT_LEFT, 125, 1);
	m_Comp.InsertColumn(1, "Наименование", LVCFMT_LEFT, 100, 1);
	for (int i=0; i<m_Setup.CountComp; i++)
	{
		char cap[50];
		sprintf(cap, "Компьютер №%d",i+1);
		m_Comp.InsertItem(i, cap, 0);   
		m_Comp.SetItem(i, 1, LVIF_TEXT, m_Setup.CompName[i], 0,0,0,0);
	}

	m_Oper.ResetContent();
	DWORD Mask = UInfo.Type == UT_SUPER ? 0xFFFFFFFF : UInfo.Admin;
	if(Mask & MT_UNBLOCK) m_Oper.SetItemData(m_Oper.AddString("Разблокировка"), 0);
	if(Mask & MT_BLOCK) m_Oper.SetItemData(m_Oper.AddString("Блокировка"), 1);
	if(Mask & MT_REBOOT) m_Oper.SetItemData(m_Oper.AddString("Перегрузка"), 2);
	if(Mask & MT_SHUTDOWN) m_Oper.SetItemData(m_Oper.AddString("Выключение"), 3);
	if(Mask & MT_INETON) m_Oper.SetItemData(m_Oper.AddString("Включение Internet'a"), 4);
	if(Mask & MT_INETOFF) m_Oper.SetItemData(m_Oper.AddString("Выключение Internet'a"), 5);
	if(Mask & MT_STOP) m_Oper.SetItemData(m_Oper.AddString("Остановка"), 6);
	m_Oper.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CManageDlg::OnDblclkComp(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_Comp.GetFirstSelectedItemPosition();
	int n=m_Comp.GetNextSelectedItem(pos);
	if (m_Comp.GetCheck(n))
		m_Comp.SetCheck(n,false);
	else
		m_Comp.SetCheck(n,true);
	
	*pResult = 0;
}

void CManageDlg::OnAll() 
{
	// TODO: Add your control notification handler code here
	bool f = m_All.GetCheck();
	for (int i=0; i<m_Comp.GetItemCount(); i++)
		m_Comp.SetCheck(i,f);
}
//
void CManageDlg::OnOK() 
{
	// TODO: Add extra validation here
	int i;
	bool f;
	char st[100], tst[100];
		
	DWORD n = m_Oper.GetItemData(m_Oper.GetCurSel());
	switch(n)
	{
	case 0:
		{
		f = false;
		st[0]='\0';
		for (i=0; i<m_Comp.GetItemCount(); i++)
		{
			if (m_Comp.GetCheck(i))
				if (!UnLockStation(i))
				{
					sprintf(tst, "%d,", i+1);
					strcat(st, tst);
					f = true;
				}
		}
		if (f)
		{
			st[strlen(st)-1] = '\0';
			sprintf(tst, "Не удалось разблокировать станции №[%s]!", st);
			MessageBox(tst, "Ошибка", MB_OK|MB_ICONERROR);
			return;
		}
		break;
		}
	case 1:
		
		f = false;
		st[0]='\0';
		for (i=0; i<m_Comp.GetItemCount(); i++)
		{
			if (m_Comp.GetCheck(i))
				if (!LockStation(i))
				{
					sprintf(tst, "%d,", i+1);
					strcat(st, tst);
					f = true;
				}
		}
		if (f)
		{
			st[strlen(st)-1] = '\0';
			sprintf(tst, "Не удалось заблокировать станции №[%s]!", st);
			MessageBox(tst, "Ошибка", MB_OK|MB_ICONERROR);
			return;
		}
		break;
	case 2:
		
		f = false;
		st[0]='\0';
		for (i=0; i<m_Comp.GetItemCount(); i++)
		{
			if (m_Comp.GetCheck(i))
				if (!ResetStation(i))
				{
					sprintf(tst, "%d,", i+1);
					strcat(st, tst);
					f = true;
				}
		}
		if (f)
		{
			st[strlen(st)-1] = '\0';
			sprintf(tst, "Не удалось перезагрузить станции №[%s]!", st);
			MessageBox(tst, "Ошибка", MB_OK|MB_ICONERROR);
			return;
		}
		break;
	case 3:
		
		f = false;
		st[0]='\0';
		for (i=0; i<m_Comp.GetItemCount(); i++)
		{
			if (m_Comp.GetCheck(i))
				if (!ShutdownStation(i))
				{
					sprintf(tst, "%d,", i+1);
					strcat(st, tst);
					f = true;
				}
		}
		if (f)
		{
			st[strlen(st)-1] = '\0';
			sprintf(tst, "Не удалось выключить станции №[%s]!", st);
			MessageBox(tst, "Ошибка", MB_OK|MB_ICONERROR);
			return;
		}
		break;
	case 4:
		
		f = false;
		st[0]='\0';
		for (i=0; i<m_Comp.GetItemCount(); i++)
		{
			if (m_Comp.GetCheck(i))
				if (!StartInetStation(i))
				{
					sprintf(tst, "%d,", i+1);
					strcat(st, tst);
					f = true;
				}
		}
		if (f)
		{
			st[strlen(st)-1] = '\0';
			sprintf(tst, "Не удалось включить Интернет на станции №[%s]!", st);
			MessageBox(tst, "Ошибка", MB_OK|MB_ICONERROR);
			return;
		}
		break;
	case 5:
		
		f = false;
		st[0]='\0';
		for (i=0; i<m_Comp.GetItemCount(); i++)
		{
			if (m_Comp.GetCheck(i))
				if (!StopInetStation(i))
				{
					sprintf(tst, "%d,", i+1);
					strcat(st, tst);
					f = true;
				}
		}
		if (f)
		{
			st[strlen(st)-1] = '\0';
			sprintf(tst, "Не удалось выключить Интернет на станции №[%s]!", st);
			MessageBox(tst, "Ошибка", MB_OK|MB_ICONERROR);
			return;
		}
		break;
	case 6:
		
		f = false;
		st[0]='\0';
		for (i=0; i<m_Comp.GetItemCount(); i++)
		{
			if (m_Comp.GetCheck(i))
				if (!StopStation(i))
				{
					sprintf(tst, "%d,", i+1);
					strcat(st, tst);
					f = true;
				}
		}
		if (f)
		{
			st[strlen(st)-1] = '\0';
			sprintf(tst, "Не удалось остановить станции №[%s]!", st);
			MessageBox(tst, "Ошибка", MB_OK|MB_ICONERROR);
			return;
		}
		break;
	default:
		MessageBox("Данная операция не реализована!", "Сообщение", MB_OK|MB_ICONINFORMATION);
		return;
	}
	
	CDialog::OnOK();
}
