// Stud.cpp : implementation file
//

#include "stdafx.h"
#include "InetTarif.h"
#include "Stud.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStud dialog
extern char fio[50], num[50]; 
						   

CStud::CStud(CWnd* pParent /*=NULL*/)
	: CDialog(CStud::IDD, pParent)
{

	//{{AFX_DATA_INIT(CStud)
	//}}AFX_DATA_INIT
}


void CStud::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStud)
	DDX_Control(pDX, IDC_EDIT2, m_num);
	DDX_Control(pDX, IDC_EDIT1, m_fio);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStud, CDialog)
	//{{AFX_MSG_MAP(CStud)
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_EDIT1, &CStud::OnEnChangeEdit1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStud message handlers

void CStud::OnOK() 
{
	// TODO: Add extra validation here
	m_fio.GetWindowText(fio,90);
	m_num.GetWindowText(num,40);
	if (strcmp(fio, "")==0 ) fio[0] = '1';
//		MessageBox("Не заполнено поле фамилии студента/ученика!", "Внимание");
	if (strcmp(num, "")==0 ) num[0] = '1',0;
//		MessageBox("Не заполнено поле номера студенческого билета/справки!", "Внимание");
	
	CDialog::OnOK();
}

void CStud::OnEnChangeEdit1()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}
