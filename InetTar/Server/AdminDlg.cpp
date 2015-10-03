// AdminDlg.cpp : implementation file
//

#include "stdafx.h"
#include "InetTarif.h"
#include "AdminDlg.h"
#include "UserInfo.h"
#include "UserDlg.h"
#include "ChangePasDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAdminDlg dialog


CAdminDlg::CAdminDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAdminDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAdminDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAdminDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdminDlg)
	DDX_Control(pDX, IDC_TREE, m_Tree);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAdminDlg, CDialog)
	//{{AFX_MSG_MAP(CAdminDlg)
	ON_BN_CLICKED(IDADD, OnAdd)
	ON_BN_CLICKED(IDEDIT, OnEdit)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE, OnSelchangedTree)
	ON_BN_CLICKED(IDACTIVE, OnActive)
	ON_BN_CLICKED(IDDEL, OnDel)
	ON_WM_SHOWWINDOW()
	ON_NOTIFY(NM_DBLCLK, IDC_TREE, OnDblclkTree)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdminDlg message handlers
extern CInetTarifApp theApp;
extern CMapWordToOb Users;
extern int User;
extern _UInfo UInfo;

BOOL CAdminDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if (!img.GetSafeHandle()) 
	{
		img.Create(16,16,ILC_COLOR, 2,2);
		img.Add(AfxGetApp()->LoadIcon(IDI_GROUP));
		img.Add(AfxGetApp()->LoadIcon(IDI_USER));
		img.Add(AfxGetApp()->LoadIcon(IDI_BADUSER));
	}

	LoadUsers();
	ChangeButtons();
	m_Tree.Expand(groups[0], TVE_COLLAPSE);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//DEL void CAdminDlg::OnClickTree(NMHDR* pNMHDR, LRESULT* pResult) 
//DEL {
//DEL 	// TODO: Add your control notification handler code here
//DEL 
//DEL 	*pResult = 0;
//DEL }

void CAdminDlg::ChangeButtons()
{
	HTREEITEM cur = m_Tree.GetSelectedItem();
	if (!cur) 
	{
		curgroup = 2;
		return;
	}

	if (!m_Tree.GetParentItem(cur)) //корневой
	{
		//WORD id = m_Tree.GetItemData(cur);
		curgroup = m_Tree.GetItemData(cur);
		CButton *Btn = (CButton *)GetDlgItem(IDDEL);
		Btn->EnableWindow(false);
		Btn = (CButton *)GetDlgItem(IDEDIT);
		Btn->EnableWindow(false);
		Btn = (CButton *)GetDlgItem(IDACTIVE);
		Btn->EnableWindow(false);
	    if (UInfo.Type == UT_ADMIN) 
		{
			if (curgroup == 2)
			{
				CButton *Btn = (CButton *)GetDlgItem(IDADD);
				Btn->EnableWindow(true);
			}
			else
			{
				CButton *Btn = (CButton *)GetDlgItem(IDADD);
				Btn->EnableWindow(false);
			}
		}
	}
	else //не корневой
	{
		curgroup = m_Tree.GetItemData(m_Tree.GetParentItem(cur));
		if (UInfo.Type == UT_ADMIN) 
		{
			if (curgroup == 2)//user
			{
				CButton *Btn = (CButton *)GetDlgItem(IDADD);
				Btn->EnableWindow(true);
				Btn = (CButton *)GetDlgItem(IDDEL);
				Btn->EnableWindow(true);
				Btn = (CButton *)GetDlgItem(IDEDIT);
				Btn->EnableWindow(true);
				Btn = (CButton *)GetDlgItem(IDACTIVE);
				Btn->EnableWindow(true);
			}
			else
			{
				CButton *Btn = (CButton *)GetDlgItem(IDADD);
				Btn->EnableWindow(false);
				Btn = (CButton *)GetDlgItem(IDDEL);
				Btn->EnableWindow(false);
				Btn = (CButton *)GetDlgItem(IDEDIT);
				Btn->EnableWindow(false);
				Btn = (CButton *)GetDlgItem(IDACTIVE);
				Btn->EnableWindow(false);
			}
		}
		else 
		{
			CButton *Btn = (CButton *)GetDlgItem(IDDEL);
			Btn->EnableWindow(true);
			Btn = (CButton *)GetDlgItem(IDEDIT);
			Btn->EnableWindow(true);
			Btn = (CButton *)GetDlgItem(IDACTIVE);
			Btn->EnableWindow(true);
		}
	}

}

void CAdminDlg::OnAdd() 
{
	// TODO: Add your control notification handler code here
	CUserDlg dlg;
	dlg.m_Add = true;
	dlg.m_Super = curgroup;
	if (dlg.DoModal()==IDCANCEL) return;
	CChangePasDlg pas;
	pas.m_First = true;
	if(pas.DoModal()==IDCANCEL)
	{
		return;
	}
	_UInfo TempInfo;
	memset(&TempInfo, 0, sizeof(_UInfo));
	TempInfo.Active = true;
	TempInfo.Type = dlg.m_Super;
	if (TempInfo.Type == UT_ADMIN)
	{
		DWORD TempType = 0;
		if (dlg.m_Change) TempType = AT_CREATE;
		if (dlg.m_Tarif) TempType |= AT_TARIF;
		if (dlg.m_Com) TempType |= AT_SETUP;
		if (dlg.m_Holiday) TempType |= AT_HOLIDAY;
		if (dlg.m_Manage) 
		{
			TempType |= AT_MANAGE;
			DWORD TempMenage = 0;
			if (dlg.m_Unblock) TempMenage |= MT_UNBLOCK;
			if (dlg.m_Block) TempMenage |= MT_BLOCK;
			if (dlg.m_Reboot) TempMenage |= MT_REBOOT;
			if (dlg.m_Shutdown) TempMenage |= MT_SHUTDOWN;
			if (dlg.m_InetOn) TempMenage |= MT_INETON;
			if (dlg.m_InetOff) TempMenage |= MT_INETOFF;
			TempType |= TempMenage;
		};

		TempInfo.Admin = TempType;
	}
	strcpy(TempInfo.Creator, UInfo.Fio);
	strcpy(TempInfo.Fio, dlg.m_Fio);
	memcpy(&TempInfo.Hash, &pas.m_Hash, 16);
	CUserInfo *user = new CUserInfo(&TempInfo);
	Users[dlg.m_Id] = user;
	LoadUsers();

	m_Tree.Expand(groups[TempInfo.Type], TVE_EXPAND);

}

void CAdminDlg::OnEdit() 
{
	// TODO: Add your control notification handler code here
	WORD Id;
	HTREEITEM Ti;
	CUserInfo *user = (CUserInfo *)Users[Id=m_Tree.GetItemData(Ti=m_Tree.GetSelectedItem())];
	if (Id == 0 && User != 0) 
	{
		MessageBox("Редактировать данные системного суперпользователя может только он сам!","Ошибка",MB_OK|MB_ICONERROR);
		return;
	}
	_UInfo TempInfo = user->Info;
	CUserDlg dlg;
	dlg.m_Add = false;
	dlg.m_Id = Id;
	dlg.m_Fio = TempInfo.Fio;
	dlg.m_Creator = TempInfo.Creator;
	dlg.m_Super = TempInfo.Type;
	if (TempInfo.Type == UT_ADMIN)
	{
		if (TempInfo.Admin & AT_CREATE)
			dlg.m_Change = true;
		if (TempInfo.Admin & AT_TARIF)
			dlg.m_Tarif = true;
		if (TempInfo.Admin & AT_SETUP)
			dlg.m_Com = true;
		if (TempInfo.Admin & AT_HOLIDAY)
			dlg.m_Holiday = true;
		if (TempInfo.Admin & AT_MANAGE)
		{
			dlg.m_Manage = true;
			if (TempInfo.Admin & MT_UNBLOCK)
				dlg.m_Unblock = true;
			if (TempInfo.Admin & MT_BLOCK)
				dlg.m_Block = true;
			if (TempInfo.Admin & MT_REBOOT)
				dlg.m_Reboot = true;
			if (TempInfo.Admin & MT_SHUTDOWN)
				dlg.m_Shutdown = true;
			if (TempInfo.Admin & MT_INETON)
				dlg.m_InetOn = true;
			if (TempInfo.Admin & MT_INETOFF)
				dlg.m_InetOff = true;
		}
	}
	if (dlg.DoModal()==IDCANCEL) return;

	strcpy(TempInfo.Fio, dlg.m_Fio);

	if (Id == 0 && dlg.m_Super != 0)
	{
		MessageBox("Вы пытались понизить свои права доступа!\nИзменения отклонены.","Ошибка",MB_OK|MB_ICONERROR);
	}
	else
		TempInfo.Type = dlg.m_Super;

	if (TempInfo.Type == UT_ADMIN)
	{
		DWORD TempType = 0;
		if (dlg.m_Change) TempType |= AT_CREATE;
		if (dlg.m_Tarif) TempType |= AT_TARIF;
		if (dlg.m_Com) TempType |= AT_SETUP;
		if (dlg.m_Holiday) TempType |= AT_HOLIDAY;
		if (dlg.m_Manage) 
		{
			TempType |= AT_MANAGE;
			DWORD TempMenage = 0;
			if (dlg.m_Unblock) TempMenage |= MT_UNBLOCK;
			if (dlg.m_Block) TempMenage |= MT_BLOCK;
			if (dlg.m_Reboot) TempMenage |= MT_REBOOT;
			if (dlg.m_Shutdown) TempMenage |= MT_SHUTDOWN;
			if (dlg.m_InetOn) TempMenage |= MT_INETON;
			if (dlg.m_InetOff) TempMenage |= MT_INETOFF;
			TempType |= TempMenage;
		};
		TempInfo.Admin = TempType;
	}

	user->Info = TempInfo;
	
	int gr = curgroup;

	LoadUsers();

	m_Tree.Expand(groups[gr], TVE_EXPAND);



}

void CAdminDlg::OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
    ChangeButtons();

	*pResult = 0;
}

void CAdminDlg::LoadUsers()
{
	m_Tree.LockWindowUpdate();
	m_Tree.DeleteAllItems();
	// Groups definitions
	groups[0] = m_Tree.InsertItem("Суперпользователи",0,0);
	m_Tree.SetItemData(groups[0], 0);
	//m_Tree.SetItemState(groups[0], TVIS_BOLD, TVIS_BOLD);
	groups[1] = m_Tree.InsertItem("Администраторы",0,0);
	m_Tree.SetItemData(groups[1], 1);
	//m_Tree.SetItemState(groups[1], TVIS_BOLD, TVIS_BOLD);
	groups[2] = m_Tree.InsertItem("Пользователи",0,0);
	m_Tree.SetItemData(groups[2], 2);
	//m_Tree.SetItemState(groups[2], TVIS_BOLD, TVIS_BOLD);
	m_Tree.SetImageList(&img,TVSIL_NORMAL);
	// Users definitions
	POSITION pos = Users.GetStartPosition();
	for (int i=0; i<Users.GetCount(); i++)
	{
		CObject *ob;
		WORD id;
		Users.GetNextAssoc(pos, id, ob);
		CUserInfo *us = (CUserInfo *)ob;
		HTREEITEM ins = groups[us->Info.Type];
		int curentimg;
		if (us->Info.Active) 
			curentimg = 1;
		else
			curentimg = 2;
		m_Tree.SetItemData(m_Tree.InsertItem(us->Info.Fio, curentimg,curentimg,ins), id);
	}

	m_Tree.SortChildren(groups[0]);
	m_Tree.SortChildren(groups[1]);
	m_Tree.SortChildren(groups[2]);
	m_Tree.UnlockWindowUpdate();
}

void CAdminDlg::OnOK() 
{
	// TODO: Add extra validation here
	theApp.SaveUsers();
	CDialog::OnOK();
}

void CAdminDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	theApp.LoadUsers();	
	CDialog::OnCancel();
}

void CAdminDlg::OnActive() 
{
	// TODO: Add your control notification handler code here
	HTREEITEM ti = m_Tree.GetSelectedItem();
	DWORD Id;
	CUserInfo *ui = (CUserInfo *)Users[Id=m_Tree.GetItemData(ti)];
	if (Id==0) 
	{
		MessageBox("Текущий суперпользователь является системным!\nВы не можете его отключить.", "Ошибка", MB_OK|MB_ICONERROR);
		return;
	};
	ui->Info.Active = !ui->Info.Active;
	if (ui->Info.Active)
		m_Tree.SetItemImage(ti, 1, 1);
	else
		m_Tree.SetItemImage(ti, 2, 2);
}

void CAdminDlg::OnDel() 
{
	// TODO: Add your control notification handler code here
	
	HTREEITEM It = m_Tree.GetSelectedItem();
	DWORD Id = m_Tree.GetItemData(It);
	if (Id==0) 
	{
		MessageBox("Текущий суперпользователь является системным!\nВы не можете его удалить.", "Ошибка", MB_OK|MB_ICONERROR);
		return;
	};
	Users.RemoveKey(Id);
	m_Tree.DeleteItem(It);
}



void CAdminDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	m_Tree.Expand(m_Tree.GetRootItem(), TVE_COLLAPSE);		
}

void CAdminDlg::OnDblclkTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CButton *Btn = (CButton *)GetDlgItem(IDEDIT);
	if (Btn->IsWindowEnabled())	OnEdit();
	*pResult = 0;
}
