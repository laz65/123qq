// HolidaysDlg.cpp : implementation file
//

#include "stdafx.h"
#include "InetTarif.h"
#include "HolidaysDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHolidaysDlg dialog


CHolidaysDlg::CHolidaysDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHolidaysDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHolidaysDlg)
	m_Cal = 0;
	m_Date = _T("");
	m_Rem = _T("");
	//}}AFX_DATA_INIT
}


void CHolidaysDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHolidaysDlg)
	DDX_Control(pDX, IDC_REM, m_CRem);
	DDX_Control(pDX, IDC_DATE, m_CDate);
	DDX_Control(pDX, IDC_CALENDAR, m_CCal);
	DDX_Control(pDX, IDC_INS, m_Ins);
	DDX_Control(pDX, IDC_HOLIDAYS, m_Holidays);
	DDX_Control(pDX, IDC_DEL, m_Del);
	DDX_MonthCalCtrl(pDX, IDC_CALENDAR, m_Cal);
	DDX_Text(pDX, IDC_DATE, m_Date);
	DDX_Text(pDX, IDC_REM, m_Rem);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHolidaysDlg, CDialog)
	//{{AFX_MSG_MAP(CHolidaysDlg)
	ON_NOTIFY(MCN_SELCHANGE, IDC_CALENDAR, OnSelchangeCalendar)
	ON_NOTIFY(NM_CLICK, IDC_HOLIDAYS, OnClickHolidays)
	ON_NOTIFY(MCN_GETDAYSTATE, IDC_CALENDAR, OnGetdaystateCalendar)
	ON_BN_CLICKED(IDC_INS, OnIns)
	ON_BN_CLICKED(IDC_DEL, OnDel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHolidaysDlg message handlers

extern char BigTextTime[300][11];
extern char BigTextRem[300][100];
extern int CountTime;

BOOL CHolidaysDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	HICON hicon;
	hicon = AfxGetApp()->LoadIcon(IDI_MINUS);
	m_Del.SetIcon(hicon);
	hicon = AfxGetApp()->LoadIcon(IDI_PLUS);
	m_Ins.SetIcon(hicon);
	m_Holidays.InsertColumn(0, "Дата", LVCFMT_LEFT, 100, 0);
	m_Holidays.InsertColumn(1, "Коментарий", LVCFMT_LEFT, 200, 1);
	m_Holidays.SetExtendedStyle(LVS_EX_GRIDLINES);
	m_Cal = CTime::GetCurrentTime();
	m_CCal.SetCurSel(m_Cal);
	m_Holidays.DeleteAllItems();
	for (int i=0;i<CountTime;i++)
	{
		LVITEM lvi;
		lvi.iItem = i;
		lvi.iSubItem = 0;
		lvi.mask = LVIF_TEXT;
		lvi.pszText = BigTextTime[i];
		lvi.iItem = m_Holidays.InsertItem(&lvi);
		lvi.iSubItem = 1;
		lvi.mask = LVIF_DI_SETITEM|LVIF_TEXT;
		lvi.pszText = BigTextRem[i];
		m_Holidays.SetItem(&lvi);
	}
	memcpy(&BTT, &BigTextTime, sizeof(BigTextTime));
	memcpy(&BTR, &BigTextRem, sizeof(BigTextRem));
	CT = CountTime;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CHolidaysDlg::OnSelchangeCalendar(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	SYSTEMTIME sys;
	m_CCal.GetCurSel(&sys);
	char csys[20];
	sprintf(csys, "%02d.%02d.%04d", sys.wDay, sys.wMonth, sys.wYear); //ctime(m_Cal.Format("%d.%m.%Y");
	m_Date = csys;
	m_Cal = sys;
	m_CDate.SetWindowText(csys);

	//UpdateData(FALSE);
	
	*pResult = 0;
}

void CHolidaysDlg::OnClickHolidays(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nItem;
	POSITION pos = m_Holidays.GetFirstSelectedItemPosition();
	m_Date = m_Holidays.GetItemText(nItem = m_Holidays.GetNextSelectedItem(pos),0); 
	m_Rem = m_Holidays.GetItemText(nItem, 1); 
	m_CDate.SetWindowText(m_Date);
	m_CRem.SetWindowText(m_Rem);
	*pResult = 0;
}

void CHolidaysDlg::OnGetdaystateCalendar(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
		
	*pResult = 0;
}

void CHolidaysDlg::OnIns() 
{
	// TODO: Add your control notification handler code here
	bool f = false;
	m_CDate.GetWindowText(m_Date);
	for (int i=0; i<CT; i++)
		if (strncmp(BTT[i], m_Date, 5)==0)
		{
			f = true;
			break;
		};
	if (f)
	{
		MessageBox("Такой праздник уже есть!", "Повторение", MB_OK|MB_ICONINFORMATION);
		return;
	}
	else
	{
		m_CRem.GetWindowText(m_Rem);
		strcpy(BTT[CT], m_Date);
		strcpy(BTR[CT], m_Rem);
		LVITEM lvi;
		lvi.iItem = CT;
		lvi.iSubItem = 0;
		lvi.mask = LVIF_TEXT;
		lvi.pszText = BTT[CT];
		lvi.iItem = m_Holidays.InsertItem(&lvi);
		lvi.iSubItem = 1;
		lvi.mask = LVIF_DI_SETITEM|LVIF_TEXT;
		lvi.pszText = BTR[CT];
		m_Holidays.SetItem(&lvi);
		CT++;
	}
}

void CHolidaysDlg::OnDel() 
{
	// TODO: Add your control notification handler code here
	bool f = false;
	m_CDate.GetWindowText(m_Date);
	int i, j;
	for (i=0; i<CT; i++)
		if (strncmp(BTT[i], m_Date, 5)==0)
		{
			for (j=0; j<m_Holidays.GetItemCount(); j++)
				if (strncmp(m_Holidays.GetItemText(j, 0), m_Date, 5)==0)
				{
					m_Holidays.DeleteItem(j);
					break;
				}

			for (j=i; j<CT-1; j++)
			{
				strcpy(BTT[j], BTT[j+1]);
				strcpy(BTR[j], BTR[j+1]);
			}
			CT--;
			f = true;
			break;
		};
	if (!f)
	{
		MessageBox("Праздник с указанной датой не найден!", "Ошибка", MB_OK|MB_ICONERROR);
		return;
	}
}

void CHolidaysDlg::OnOK() 
{
	// TODO: Add extra validation here
	memcpy(&BigTextTime, &BTT, sizeof(BTT));
	memcpy(&BigTextRem, &BTR, sizeof(BTR));
	CountTime = CT;

	FILE *fp = fopen("holiday.txt", "w");
	for (int i=0; i<CountTime; i++)
	{
		char ts[120];
		strcpy(ts, BigTextTime[i]);
		strcat(ts, " ");
		strcat(ts, BigTextRem[i]);
		strcat(ts, "\n");
		fputs(ts, fp);
	};

	fclose(fp);
	
	CDialog::OnOK();
}
