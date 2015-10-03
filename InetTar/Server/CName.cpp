// CName.cpp : implementation file
//

#include "stdafx.h"
#include "InetTarif.h"
#include "CName.h"
//#include ".\cname.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCName dialog


CCName::CCName(CWnd* pParent /*=NULL*/)
	: CDialog(CCName::IDD, pParent)
{
	sTitle = "Рабочая станция";
	//{{AFX_DATA_INIT(CCName)
	m_NameEditVal = _T("");
	m_CmStatVal = 0;
	//}}AFX_DATA_INIT
}


void CCName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCName)
	DDX_Control(pDX, IDC_NAMEEDIT, m_NameEdit);
	DDX_Text(pDX, IDC_NAMEEDIT, m_NameEditVal);
	DDX_Control(pDX, IDC_STATCOMBO, m_CmStat);
	DDX_CBIndex(pDX, IDC_STATCOMBO, m_CmStatVal);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCName, CDialog)
	//{{AFX_MSG_MAP(CCName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCName message handlers

BOOL CCName::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	SetWindowText( sTitle );
	m_NameEdit.SetWindowText (m_NameEditVal);
	m_CmStat.SetTopIndex(m_CmStatVal);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCName::OnOK() 
{
	// TODO: Add extra validation here
	CDialog::OnOK();
}
