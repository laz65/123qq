// ShowRep.cpp : implementation file
//

#include "stdafx.h"
#include "InetTarif.h"
#include "ShowRep.h"
#include <stdio.h>

// CShowRep dialog

//IMPLEMENT_DYNAMIC(CShowRep, CDialog)
CShowRep::CShowRep(CWnd* pParent /*=NULL*/)
	: CDialog(CShowRep::IDD, pParent)
{
}

CShowRep::~CShowRep()
{
}

void CShowRep::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDREPLOG, m_EdRepLog);
}


BEGIN_MESSAGE_MAP(CShowRep, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


BOOL CShowRep::OnInitDialog()
{
	CDialog::OnInitDialog();
	/*/
	CFont* font=new CFont();
	VERIFY(font->CreateFont(
		10,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		"Courier"));               // lpszFacename
	//
	VERIFY(font->CreatePointFont(100, "Courier", NULL));
	/*/
	CFile cFile;
	if( cFile.Open(sFile, CFile::modeRead | CFile::shareDenyNone, NULL) == NULL)
	{
		MessageBox("Не могу открыть файл отчета", "Ошибка", MB_OK|MB_ICONERROR);
		return FALSE;
	}
	ULONGLONG dwLength = cFile.GetLength();
	char* pbuf;
	pbuf = (char *)malloc( dwLength);
	memset(pbuf, 0, dwLength);
	UINT nBytesRead = cFile.Read( pbuf, dwLength );
	cFile.Close();

	CString str1, str2;
	str1.Format("%s", pbuf);
	str2 = str1.Mid(0, dwLength);
	int len=str2.GetLength();
	//
	//m_EdRepLog.SetFont(font);
	m_EdRepLog.SetWindowText(str2);
	free(pbuf);
	//font->DeleteObject();
	//
	return TRUE;	
}

// CShowRep message handlers

void CShowRep::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}
