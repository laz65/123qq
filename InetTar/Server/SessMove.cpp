// SessMove.cpp: ���� ����������
//

#include "stdafx.h"
#include "InetTarif.h"
#include "InetTarifDlg.h"
#include "SessMove.h"

//
extern int iActivComp; // �-�� ��������� �������
extern hCompInfo Computers[MAX_WORKSTATION];


// ���������� ���� CSessMove

IMPLEMENT_DYNAMIC(CSessMove, CDialog)

CSessMove::CSessMove(CWnd* pParent /*=NULL*/)
	: CDialog(CSessMove::IDD, pParent)
{
	iCurrComp = -1;
	NewNumbComp = -1;
}

CSessMove::~CSessMove()
{
}

void CSessMove::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRID, m_Grid);
}


BEGIN_MESSAGE_MAP(CSessMove, CDialog)
	ON_BN_CLICKED(IDCANCEL, &CSessMove::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CSessMove::OnBnClickedOk)
END_MESSAGE_MAP()


BOOL CSessMove::OnInitDialog() 
{
	CDialog::OnInitDialog();
	//��������� ������� ������� ������� � ������ �������
	// Delete all of the columns.
	for (int i=0;i < m_Grid.GetHeaderCtrl()->GetItemCount();i++)
		m_Grid.DeleteColumn(0);
	// ��������� ������
	char *head[]={"�����", "���������"};
	const int width[] = { 50, 120 };
	for (int i=0; i<2; i++)
		m_Grid.InsertColumn(i, head[i], LVCFMT_LEFT, width[i], i);
	CHeaderCtrl *h = m_Grid.GetHeaderCtrl();
	// ��� �������� �����
	HDITEM hi;
	hi.fmt = HDF_RIGHT|HDF_STRING;
	hi.mask = HDI_FORMAT;
	h->SetItem(0, &hi);
	m_Grid.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	//
	m_Grid.SetRedraw(false);
	m_Grid.DeleteAllItems();
	//
	int iRows = 0;
	int iIndex;
	char cStr[100];
	for (int Comp=0; Comp<iActivComp; Comp++)
	{
		if (Computers[Comp].Start==false && Computers[Comp].Connected==true && Comp!=iCurrComp)
		{
			sprintf(cStr, "%i", Computers[Comp].NumbComp+1);
			iIndex = m_Grid.InsertItem(iRows, cStr, 0);  
			//
			m_Grid.SetItem(iIndex, 1, LVIF_TEXT, Computers[Comp].CompName, 0,0,0,0);
			iRows++;
		}
	}
	m_Grid.SetRedraw(true);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


// ����������� ��������� CSessMove


void CSessMove::OnBnClickedCancel()
{
	// TODO: �������� ���� ��� ����������� �����������
	OnCancel();
}

void CSessMove::OnBnClickedOk()
{
	// TODO: �������� ���� ��� ����������� �����������
	POSITION pos = m_Grid.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox("�� ������ �� ���� ������� ������.",
			"��������", MB_OK|MB_ICONINFORMATION);
		OnCancel();
	}
	else
	{
		// Gets the index of the list item identified by pos, then sets pos to the POSITION value
		int nItem = m_Grid.GetNextSelectedItem(pos);
		NewNumbComp = atoi(m_Grid.GetItemText(nItem, 0)) - 1;
		OnOK();
	}
}
