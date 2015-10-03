// ComSetupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "InetTarif.h"
#include "ComSetupDlg.h"
#include "CName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern void LogWrite(char *text);
extern hSetup m_Setup;
extern CInetTarifApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CComSetupDlg dialog


CComSetupDlg::CComSetupDlg(CWnd* pParent /*=NULL*/)
        : CDialog(CComSetupDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CComSetupDlg)
	//}}AFX_DATA_INIT
}


void CComSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CComSetupDlg)
	DDX_Control(pDX, IDC_GRID, m_Grid);
	DDX_Control(pDX, IDC_INAME, m_IName);
	DDX_Control(pDX, IDC_INOMER, m_INomer);
	DDX_Control(pDX, IDC_LOCKEDIT, m_Lock);
	DDX_Control(pDX, IDC_UNLOCKEDIT, m_UnLock);
	DDX_Control(pDX, IDC_BILLPATH, m_BillPath);
	DDX_Control(pDX, IDC_SHAREPATH, m_SharePath);
	DDX_Control(pDX, IDC_GATEWAYNAME, m_GateWayName);
	DDX_Control(pDX, IDC_CHECKINET, m_CheckInet);
	DDX_Control(pDX, IDC_CHECKEXPLORER, m_CheckExplorer);
	DDX_Control(pDX, IDC_CASSACHECK, m_CassaCheck);
	DDX_Control(pDX, IDC_BOTH, m_Both);
	DDX_Control(pDX, IDC_RF2160, m_UseRF2160);
	DDX_Control(pDX, IDC_CHECKPIPES, m_CheckPipes);
	DDX_Control(pDX, IDC_COUNTCOMP, m_CountComp);
	DDX_Control(pDX, IDC_COMPSPIN, m_CompSpin);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CComSetupDlg, CDialog)
	//{{AFX_MSG_MAP(CComSetupDlg)
	ON_BN_CLICKED(IDC_CASSACHECK, OnCassacheck)
	ON_EN_CHANGE(IDC_COUNTCOMP, OnChangeCountcomp)
	ON_NOTIFY(NM_DBLCLK, IDC_GRID, OnDblclkGrid)
	ON_NOTIFY(HDN_ITEMDBLCLICK, IDC_GRID, OnItemdblclickGrid)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComSetupDlg message handlers

BOOL CComSetupDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	#ifdef _LOG_ITAR
		char LogBuffer[200];
		sprintf (LogBuffer, "Enter Setup Dialog");
		LogWrite (LogBuffer);
	#endif
	//
	memcpy ((void*) &m_TempSetup, (void*) &m_Setup, sizeof(hSetup));
	//
	m_IName.SetWindowText(m_TempSetup.IName);
	m_INomer.SetWindowText(m_TempSetup.INomer);

	m_Lock.SetWindowText(m_TempSetup.Lock);
	m_UnLock.SetWindowText(m_TempSetup.UnLock);

	m_SharePath.SetWindowText(m_TempSetup.SharePath);
	m_BillPath.SetWindowText(m_TempSetup.PathBill);

	m_GateWayName.SetWindowText(m_TempSetup.GateWayName);
	m_CheckExplorer.SetCheck(m_TempSetup.CloseExplorer);
	m_CheckInet.SetCheck(m_TempSetup.BlockInet);
	m_CheckPipes.SetCheck(m_TempSetup.Pipe);

	m_CassaCheck.SetCheck(m_TempSetup.UseCassa);
	m_Both.SetCheck(m_TempSetup.UseBoth);
	m_UseRF2160.SetCheck(m_TempSetup.UseRF2160);
	// Delete all of the columns.
	int i;
	for (i=0;i < m_Grid.GetHeaderCtrl()->GetItemCount();i++)
		m_Grid.DeleteColumn(0);
	const char *head[]={"Компьютер", "Состояние", "Имя или IP"};
	const int width[] = {110, 90, 90};
	for (i=0; i<3; i++)
		m_Grid.InsertColumn(i, head[i], LVCFMT_LEFT, width[i], i);
	m_Grid.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	char TempStr[80];
	// Данные в таблицу добавятся с установкой числа станций
	m_CountComp.SetWindowText(itoa(m_TempSetup.CountComp, TempStr, 10));
	m_CompSpin.SetRange(1,100);
	//
	return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CComSetupDlg::OnOK() 
{
	// TODO: Add extra validation here
	m_IName.GetWindowText(m_TempSetup.IName, 200 );
	m_INomer.GetWindowText(m_TempSetup.INomer, 200 );

	m_Lock.GetWindowText(m_TempSetup.Lock, 200 );
	m_UnLock.GetWindowText(m_TempSetup.UnLock, 200 );

	m_SharePath.GetWindowText(m_TempSetup.SharePath, 200 );
	m_BillPath.GetWindowText(m_TempSetup.PathBill, 200 );

	m_GateWayName.GetWindowText(m_TempSetup.GateWayName, 200);
	m_TempSetup.CloseExplorer = m_CheckExplorer.GetCheck();
	m_TempSetup.BlockInet = (bool) m_CheckInet.GetCheck();
//!!!!!!
	m_TempSetup.Pipe =  false; //(bool) m_CheckPipes.GetCheck();

	m_TempSetup.UseBoth = (bool) m_Both.GetCheck();
	m_TempSetup.UseRF2160 = (bool) m_UseRF2160.GetCheck();
	//
	memcpy ((void*) &m_Setup, (void*) &m_TempSetup, sizeof(hSetup));
	theApp.SaveProfiles();
	//
	#ifdef _LOG_ITAR
		char LogBuffer[200];
		sprintf (LogBuffer, "Saved and leaved Setup Dialog");
		LogWrite (LogBuffer);
	#endif
	CDialog::OnOK();
}

void CComSetupDlg::OnChangeCountcomp() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	if (m_CountComp)
	{
		CString TempStr;
		m_CountComp.GetWindowText(TempStr);
		m_TempSetup.CountComp = atoi((LPCSTR)TempStr);
		//m_Grid.LockWindowUpdate();
		m_Grid.DeleteAllItems();
		for (int i=0; i<m_TempSetup.CountComp; i++)
		{
			TempStr = "Компьютер №";
			char Numb[3];
			TempStr += itoa(i+1, Numb, 10);
			m_Grid.InsertItem(i, TempStr);
			//bActiv
			if(m_TempSetup.bActiv[i])
				TempStr = "Активный";
			else
				TempStr = "Скрыт";
			m_Grid.SetItemText(i, 1, TempStr);
			m_Grid.SetItemText(i, 2, m_TempSetup.CompName[i]);
		}
		//m_Grid.UnlockWindowUpdate();
	}
	// TODO: Add your control notification handler code here
}

BEGIN_EVENTSINK_MAP(CComSetupDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CComSetupDlg)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CComSetupDlg::OnCassacheck() 
{
	// TODO: Add your control notification handler code here
	m_TempSetup.UseCassa^=1;
}


BOOL CComSetupDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	return CDialog::DestroyWindow();
}

void CComSetupDlg::OnDblclkGrid(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) pNMHDR;
	//{"Компьютер", "Активный", "Имя"}
	//int Col = lpnmitem->iSubItem;
	int Row = lpnmitem->iItem;
	CCName NameDlg;
	NameDlg.sTitle = m_Grid.GetItemText(Row, 0);
	if (m_Grid.GetItemText(Row, 1) == "Активный")
		NameDlg.m_CmStatVal = 1;
	else
		NameDlg.m_CmStatVal = 0;
	NameDlg.m_NameEditVal =  m_Grid.GetItemText(Row, 2);
	if (NameDlg.DoModal()==IDOK)
	{
		// Состояние
		if (NameDlg.m_CmStatVal == 1)
		{
			m_Grid.SetItemText(Row, 1, "Активный");
			m_TempSetup.bActiv[Row] = true;
		}
		else
		{
			m_Grid.SetItemText(Row, 1, "Скрыт");
			m_TempSetup.bActiv[Row] = false;
		}
		// Наименование
		m_Grid.SetItemText(Row, 2, NameDlg.m_NameEditVal);
		strcpy(m_TempSetup.CompName[Row], NameDlg.m_NameEditVal);
	}
	*pResult = 0;
}

void CComSetupDlg::OnItemdblclickGrid(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	// TODO: Add your control notification handler code here
	*pResult = 0;
}
