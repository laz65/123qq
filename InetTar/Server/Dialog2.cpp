// Dialog2.cpp: файл реализации
//

#include "stdafx.h"
#include "InetTarif.h"
#include "Dialog2.h"

extern void PrintChek(CString);
// диалоговое окно CDialog2

IMPLEMENT_DYNAMIC(CDialog2, CDialog)

CDialog2::CDialog2(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog2::IDD, pParent)
{

}

CDialog2::~CDialog2()
{
}

void CDialog2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DTFROM, m_DtFrom);
	DDX_Control(pDX, IDC_DTTO, m_DtTo);
}


BEGIN_MESSAGE_MAP(CDialog2, CDialog)
	ON_BN_CLICKED(IDOK, &CDialog2::OnBnClickedOk)
END_MESSAGE_MAP()


// обработчики сообщений CDialog2

void CDialog2::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	FormOtchet();
	OnOK();
}


bool CDialog2::FormOtchet()
{	
	m_zvit = IsDlgButtonChecked(IDC_CASSACHECK); 
	CTime pDtFrom, pDtTo;
	m_DtFrom.GetTime(pDtFrom);
	m_DtTo.GetTime(pDtTo);
	COleDateTime m_OleDtTmFrom, m_OleDtTmTo;
	m_OleDtTmFrom.SetDate( pDtFrom.GetYear(), pDtFrom.GetMonth(), pDtFrom.GetDay() );
	m_OleDtTmTo.SetDate(pDtTo.GetYear(), pDtTo.GetMonth(), pDtTo.GetDay() );
	char Buffer[200];
	try
	{	
		CString chek;
		if(m_zvit)
			sprintf(Buffer, "J$X$%s%s\n", pDtFrom.Format(_T("%d%m%y")), pDtTo.Format(_T("%d%m%y")) );
		else
			sprintf(Buffer, "J$S$%s%s\n", pDtFrom.Format(_T("%d%m%y")), pDtTo.Format(_T("%d%m%y")) );
		chek = Buffer;
		//chek.AnsiToOem();
		PrintChek(chek);
	}
	catch(...)
	{
		DWORD err = GetLastError();
		if (err)
			sprintf(Buffer,"Ошибка в PrintChek(CInetTarifApp::OnXotchet) # %d", err);
		else
			sprintf(Buffer,"Ошибка в PrintChek(CInetTarifApp::OnXotchet)");
		LogWrite(Buffer);
	}


	return true;
}