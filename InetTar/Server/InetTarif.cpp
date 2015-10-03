// InetTarif.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "InetTarif.h"
#include <io.h>
#include <eh.h>

#include "UserInfo.h"
#include "PasswDlg.h"
#include "InetTarifDlg.h"

#include "AdminDlg.h"
#include "HolidaysDlg.h"
#include "TarifDlg.h"
#include "ChangePasDlg.h"
#include "ManageDlg.h"
#include "ReportDlg.h"
#include "RepDelDlg.h"
#include "SvRep.h"
#include "Dialog2.h"


#include "Tarif.h"
#include "Vnesenie.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
//extern int Except (unsigned int code, struct _EXCEPTION_POINTERS *ep, CString ProcName);
extern void LogWrite(char *text);

extern CMapWordToOb Users;
/////////////////////////////////////////////////////////////////////////////
CInetTarifDlg *m_tdlg;

int User;
_UInfo UInfo;
/////////////////////////////////////////////////////////////////////////////
hSetup m_Setup;
CList <hDopusl, hDopusl&> UslList;
//char BasePath[200];
//char PathIni[200];

//bool RFon;
/////////////////////////////////////////////////////////////////////////////
void PrintChek(CString strChek)
{
	int pLen = strlen(m_Setup.PathBill);
	char billName[300];
	strcpy (billName, m_Setup.PathBill);
	// ���� ���� �� ������������� �������
	if (m_Setup.PathBill[pLen-2]!='\\')
 		strncat (billName, "\\", 1);
	if (m_Setup.PathBill[pLen-1]!='\\')
 		strncat (billName, "\\", 1);
	//
	char tbuffer [9];
	char *fillname;
	// �������� ���.����� hh:mm:ss � ���������� 
	_strtime( tbuffer );
	//char *strtok(   char *strToken,   const char *strDelimit );
	//Returns a pointer to the next token found in strToken. They return NULL when no more tokens are found. 
	//Each call modifies strToken by substituting a NULL character for each delimiter that is encountered.
	fillname = strtok(tbuffer, ":");
	while( fillname != NULL )
	{
		strcat (billName, fillname);
		fillname = strtok( NULL, ":" );
	}
	strcat (billName, ".fil");
	//
	FILE *Stream;
	Stream = fopen("temp.fil", "w");
	fprintf (Stream , strChek);
	fclose (Stream);
	CopyFile( "temp.fil", billName, false );
	//
	#ifdef _LOG_ITAR
		char LogBuffer[500];
		if (strChek.GetLength() > 400)
		{
			strChek.Delete(400, strChek.GetLength() - 400);
			int i=strChek.GetLength();
			sprintf (LogBuffer, "������ ���� %s", strChek);
		}
		else
			sprintf (LogBuffer, "������ ���� %s", strChek);
		LogWrite (LogBuffer);
	#endif
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
class CAboutDlg : public CDialog
{
public:
        virtual BOOL PreTranslateMessage(MSG* pMsg);
        CAboutDlg();

// Dialog Data
        //{{AFX_DATA(CAboutDlg)
        enum { IDD = IDD_ABOUTBOX };
        //}}AFX_DATA

        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(CAboutDlg)
        protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        //}}AFX_VIRTUAL

// Implementation
protected:
        CToolTipCtrl m_tooltip;
        virtual BOOL OnInitDialog();
        //{{AFX_MSG(CAboutDlg)
        afx_msg void OnWww();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// CInetTarifApp

BEGIN_MESSAGE_MAP(CInetTarifApp, CWinApp)
	ON_COMMAND(CG_IDS_TIPOFTHEDAY, ShowTipOfTheDay)
	//{{AFX_MSG_MAP(CInetTarifApp)
	ON_COMMAND(ID_ADMIN, OnAdmin)
	ON_COMMAND(ID_HOLIDAYS, OnHolidays)
	ON_COMMAND(ID_MANAGE, OnManage)
	ON_COMMAND(ID_CHANGEPASS, OnChangepass)
	ON_COMMAND(ID_DAYOFF, OnDayoff)
	ON_COMMAND(ID_TARIF, OnTarif)
	ON_COMMAND(ID_SETTARIF, OnSetUsl)
	ON_COMMAND(ID_ABOUT, OnAbout)
	ON_COMMAND(ID_TIP, OnTip)
	ON_COMMAND(ID_XOTCHET, OnXotchet)
	ON_COMMAND(ID_XOTCHET_T, OnXotchetT)
	ON_COMMAND(ID_ZOTCHET, OnZotchet)
	ON_COMMAND(ID_ZOTCHET_T, OnZotchetT)
	ON_COMMAND(ID_MOTCHET, OnMotchet)
	ON_COMMAND(ID_OTKR, OnOtkr)
	ON_COMMAND(ID_VNESENIE, OnVnesenie)
	ON_COMMAND(ID_IZYATIE, OnIzyatie)
	ON_COMMAND(ID_INTERNET, OnInternet)
	//ON_COMMAND(ID_HELP, OnHelp)
	ON_COMMAND(ID_PAYMENT, OnPayment)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_DELREP, OnDelrep)
	ON_COMMAND(IDD_SVPAYREP, &CInetTarifApp::OnSvpayrep)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInetTarifApp construction

CInetTarifApp::CInetTarifApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CInetTarifApp object
CInetTarifApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CInetTarifApp initialization

BOOL CInetTarifApp::InitInstance()
{
	// CG: This line inserted by 'Tip of the Day' component.
	//set_terminate( for_terminate );
	ATOM m_atom = GlobalFindAtom ("myfnjv");
	// ��� �������
	HANDLE hnd = CreateMutex(NULL, TRUE, m_pszAppName);
	if ( GetLastError() == ERROR_ALREADY_EXISTS && 
	WAIT_ABANDONED != WaitForSingleObject(hnd, 1000))
	{
		AfxMessageBox("���������� ��� ��������! ");
		return FALSE;
	}
	//if (m_atom)
	//	GlobalDeleteAtom(m_atom);
	if (m_atom)
	{
		MessageBox(NULL, "���������� ������ ��������-������������ ���������� �������. ����� �������� ��������� ���������, ��� �� ������� ����� ������.", 
			"������", MB_OK|MB_ICONERROR);
		return FALSE;
	}
	m_atom = GlobalAddAtom( "myfnjv");
	if (!m_atom)
		return FALSE;
	#ifdef _LOG_ITAR
		char ComputerName[100];
		ULONG Size=100;
		GetComputerName(ComputerName, &Size);
		char LogBuffer[200];
		sprintf (LogBuffer, "Inet Tarificator (Server) started on %s.", ComputerName);
		LogWrite (LogBuffer);
	#endif
		char LogBuffer[200];
		sprintf (LogBuffer, "Inet Tarificator (Server) started on.");
		LogWrite (LogBuffer);
	LoadUsers();
begin:
	// ������������� ��������� � ��������� ����
	if(!EnterSystem()) return FALSE;
//	#ifdef _LOG_ITAR
		sprintf (LogBuffer, "Operator - %s", UInfo.Fio);
		LogWrite (LogBuffer);
//	#endif
	/*/ ���������� ������������ ������
	LoadProfiles();
	/*/
	// �������� �� ������ ��� ���������� ������� � ����������� ������ ������ ������ ��
	if (!OpenDatabase()) return FALSE;
	// ���������� ������ �� ���.�������
	LoadDopusl();

	ShowTipAtStartup();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
	//#ifdef _AFXDLL
	//Enable3dControls();			// Call this when using MFC in a shared DLL
	//#else
	//Enable3dControlsStatic();	// Call this when linking to MFC statically
	//#endif
	//������� ������� ����
	CInetTarifDlg dlg;
	//m_pMainWnd = &dlg;
	m_tdlg     = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
    else if (nResponse == 5)		// ����� ������������
	{
		// �������� �� ������ ��� ���������� ������� � ����������� ������ ������ ������ ��
		CloseDatabase();
		SaveProfiles();

		goto begin;
	}
	// ���������� ������
	SaveProfiles();
	// �������� �� ������ ��� ���������� ������� � ����������� ������ ������ ������ ��
	CloseDatabase();

	m_atom = GlobalFindAtom ("myfnjv");
	if (m_atom)
		GlobalDeleteAtom(m_atom);
//	#ifdef _LOG_ITAR
		LogWrite ("Inet Tarificator is stopped.\n");
//	#endif
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
//Called by the framework from within the Run member function to exit this instance of the application.
//Do not call this member function from anywhere but within the Run member function.
//The default implementation of this function writes framework options to the application's .INI file. 
//Override this function to clean up when your application terminates.
int CInetTarifApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	// ��� ������� ��-�� ������
	ATOM m_atom;
	m_atom = GlobalFindAtom ("myfnjv");
	if (m_atom)
		GlobalDeleteAtom(m_atom);

	return CWinApp::ExitInstance();
}

void CInetTarifApp::LoadProfiles ()
{
	hSetup m_SaveSetup;
	char pDirectory[200];
	FILE* fp = fopen ("setup.ini", "rb");
	if (!fp)
	{
		GetCurrentDirectory(200, pDirectory);
		memset (&m_Setup, 0, sizeof(hSetup));
		memcpy (m_Setup.PathName, pDirectory, 200);	
		#ifdef _LOG_ITAR
			LogWrite ("Not found Setup.ini");
		#endif
		return;
	}
	fread (&m_SaveSetup, sizeof (hSetup), 1, fp);
	fclose(fp);
	//
	int Code=0;
	int Pos=0;
	char *t_Setup = (char*)&m_SaveSetup;
	char *psw = "a3f45<2F6~";
	while (Pos<sizeof(hSetup))
	{
		t_Setup[Pos] ^= psw[Code];
		Code++;
		if (Code>9) Code=0;
		Pos++;
	}
	memcpy (&m_Setup, &m_SaveSetup, sizeof(hSetup));
	MD5_CTX context;
	MD5Init (&context);
	MD5Update (&context, (unsigned char *)&m_Setup, sizeof (hSetup)-sizeof(MD5_CTX)-1);
	MD5Final (&context);
	if (memcmp(&context.digest, m_Setup.m_md5.digest, 16)!=0)
	{
		// ���������� ������� �� ������ ���������
		fp = fopen ("setup.ini", "rb");
		if (!fp)
		{
			GetCurrentDirectory(200, pDirectory);
			memset (&m_Setup, 0, sizeof(hSetup));
			memcpy (m_Setup.PathName, pDirectory, 200);	
			#ifdef _LOG_ITAR
				LogWrite ("Not found Setup.ini");
			#endif
			return;
		}
		hOldSetup m_OldSetup, m_TmpSetup;
		fread (&m_TmpSetup, sizeof (hOldSetup), 1, fp);
		fclose(fp);
		// ���������
		Code=0;
		Pos=0;
		t_Setup = (char*)&m_TmpSetup;
		psw = "a3f45<2F6~";
		while (Pos<sizeof(hOldSetup))
		{
			t_Setup[Pos] ^= psw[Code];
			Code++;
			if (Code>9) Code=0;
			Pos++;
		}
		memcpy (&m_OldSetup, &m_TmpSetup, sizeof(hOldSetup));
		MD5_CTX context;
		MD5Init (&context);
		MD5Update (&context, (unsigned char *)&m_OldSetup, sizeof (hOldSetup)-sizeof(MD5_CTX)-1);
		MD5Final (&context);
		if (memcmp(&context.digest, m_OldSetup.m_md5.digest, 16)!=0)
		{
			GetCurrentDirectory(200, pDirectory);
			memset (&m_Setup, 0, sizeof(hSetup));
			memcpy (m_Setup.PathName, pDirectory, 200);	
			#ifdef _LOG_ITAR
				LogWrite ("������ ��������. ��������� ���������");
			#endif
			MessageBox(NULL, "��������� ��������� ����������.\n ���������� � �������������� ��� ����������� ������.", 
				"������", MB_OK|MB_ICONERROR);
		}
		else // ��������� ��������� � ����� ���������
		{
			sprintf (m_Setup.INomer, m_OldSetup.INomer); //��� ����
			sprintf (m_Setup.IName, m_OldSetup.IName); // ������������ ����
			sprintf (m_Setup.Lock, m_OldSetup.Lock);  // ������� ��� ����������
			sprintf (m_Setup.UnLock, m_OldSetup.UnLock);  // ������� ��� �������������
			m_Setup.nDopList = m_OldSetup.nDopList; // �-�� ���.����� � ����� usl.ini
			m_Setup.UseCassa = m_OldSetup.UseCassa;  // �������� �������� ���
			m_Setup.UseRF2160 = m_OldSetup.UseRF2160; // true - �������� ��� �� ��, false - �� �������
			m_Setup.UseBoth   = m_OldSetup.UseBoth;  // ������ ���������� ����
			sprintf (m_Setup.PathBill, m_OldSetup.PathBill); //���� ����������� ����� ����� ��������� ��������
			m_Setup.CountComp = m_OldSetup.CountComp; // �-�� ������� �������
			for (int i=0; i< m_OldSetup.CountComp; i++)
			{
				// ������ ���� ������� �������
				sprintf (m_Setup.CompName[i], m_OldSetup.CompName[i]);
				// true - ������� �������� ����� ������������, false - ��� (���������, ����������)
				m_Setup.bActiv[i] = m_OldSetup.bActiv[i]; 
			}
			m_Setup.BlockInet = m_OldSetup.BlockInet; // ����������� ��������
			m_Setup.CloseExplorer = m_OldSetup.CloseExplorer; // ����������� ���������
			sprintf (m_Setup.GateWayName, m_OldSetup.GateWayName); // IP Gateway
			m_Setup.Pipe = false; // ������� ������������� Pipes, ����� - Socket
			m_Setup.Tarif1 = m_OldSetup.Tarif1;  //Internet �������
			m_Setup.Tarif2 = m_OldSetup.Tarif2;  //Computer �������
			m_Setup.Tarif3 = m_OldSetup.Tarif3;  //Internet ��������
			m_Setup.Tarif4 = m_OldSetup.Tarif4;  //Computer ��������
			m_Setup.Tarif5 = m_OldSetup.Tarif5;  //Internet �����������
			m_Setup.Tarif6 = m_OldSetup.Tarif6;  //Computer �����������
			m_Setup.Tarif7 = m_OldSetup.Tarif7;  //Student Internet �������
			m_Setup.Tarif8 = m_OldSetup.Tarif8;  //Student Internet �����������
			sprintf (m_Setup.SharePath, m_OldSetup.SharePath); // ���� � ����� �����
			sprintf (m_Setup.PathName, m_OldSetup.PathName); // ���� � ���������� � ���������� (����������� ���������.)
			m_Setup.CurNds = 20.0;
		}
	}
	//
	GetCurrentDirectory(200, pDirectory);
	if (strcmp(m_Setup.PathName, pDirectory)!=0)
	{
		#ifdef _LOG_ITAR
			char LogBuffer[200];
			sprintf (LogBuffer, "����������� ������ ���� ��� �������� ��������");
			LogWrite (LogBuffer);
		#endif
		strcpy(m_Setup.PathName, ".");//pDirectory;
	}
	if (m_Setup.UseRF2160 == false)
	{
		/*/
		TempMenu.RemoveMenu(ID_SETTARIF, MF_BYCOMMAND);
		TempMenu.RemoveMenu(ID_CHEK, MF_BYCOMMAND);
		CMenu *submenu = TempMenu.GetSubMenu(0);
		submenu->RemoveMenu(2, MF_BYPOSITION);
		//TempMenu.EnableMenuItem(0, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		/*/
		CMenu *submenu = TempMenu.GetSubMenu(0);
		submenu->RemoveMenu(3, MF_BYPOSITION);
	}
	#ifdef _LOG_ITAR
		char LogBuffer[200];
		sprintf (LogBuffer, "Profiles loaded.");
		LogWrite (LogBuffer); 
	#endif
}
//
void CInetTarifApp::SaveProfiles ()
{
	hSetup m_SaveSetup;
	memcpy (&m_SaveSetup, &m_Setup, sizeof(hSetup));
	//
	MD5_CTX context;
	MD5Init (&context);
	MD5Update (&context, (unsigned char *)&m_Setup, sizeof (hSetup)-sizeof(MD5_CTX)-1);
	MD5Final (&context);
	memcpy(&m_SaveSetup.m_md5.digest,  &context.digest, 16);
	//
	int Code=0;
	int Pos=0;
	char *t_Setup = (char*)&m_SaveSetup;
	char *psw = "a3f45<2F6~";
	while (Pos<sizeof(hSetup))
	{
		t_Setup[Pos] ^= psw[Code];
		Code++;
		if (Code>9) Code=0;
		Pos++;
	}
	//
	FILE* fp = fopen ("setup.ini", "wb");
	fwrite (&m_SaveSetup, sizeof (hSetup), 1, fp);
	fclose(fp);
	#ifdef _LOG_ITAR
		char LogBuffer[200];
		sprintf (LogBuffer, "Save Profiles1.");
		LogWrite (LogBuffer);
	#endif
}

//
void CInetTarifApp::LoadDopusl ()
{
	try
	{
		pTdExtTarif = new CDaoTableDef(&m_database);
		pTdExtTarif->Open("ExtTar");
		pRsExtTarif = new CDaoRecordset;
		pRsExtTarif->Open(pTdExtTarif);
		pRsExtTarif->SetCurrentIndex("PrimaryKey");
	}
	catch (CDaoException* e)
	{
		AfxMessageBox("������ �������� ��: " + e->m_pErrorInfo->m_strDescription);
		e->Delete();
		return;
	}
	if( !pRsExtTarif->IsOpen())
	{
		//#ifdef _LOG_ITAR
			LogWrite ("��� ������� �� ������� �������");
		//#endif
		return;
	}
	UslList.RemoveAll();
	POSITION posList = UslList.GetTailPosition();
	hDopusl tempusl;
	COleVariant m_OleVariant;
	int iRows = 0;
	pRsExtTarif->MoveFirst();
	while ( !pRsExtTarif->IsEOF( ) )
	{
		// ID
		pRsExtTarif->GetFieldValue("ID", m_OleVariant);
		tempusl.nomusl = GetAccInteger(m_OleVariant);
		//code_reg
		pRsExtTarif->GetFieldValue("code_reg", m_OleVariant);
		tempusl.rf_code = GetAccInteger(m_OleVariant);
		// info
		pRsExtTarif->GetFieldValue("info", m_OleVariant);
		sprintf(tempusl.name, "%s", m_OleVariant.bstrVal);
		// tarif
		pRsExtTarif->GetFieldValue("tarif", m_OleVariant);
		tempusl.tarif = GetAccDouble(m_OleVariant);
		//code_info
		pRsExtTarif->GetFieldValue("code_info", m_OleVariant);
		sprintf(tempusl.rf_name, "%s", m_OleVariant.bstrVal);
		// 08.12.2009 rf_rate
		pRsExtTarif->GetFieldValue("rf_rate", m_OleVariant);
		tempusl.rf_rate = GetAccInteger(m_OleVariant);
		// 08.12.2009 rf_rate
		pRsExtTarif->GetFieldValue("tarif_type", m_OleVariant);
		tempusl.tar_type = GetAccInteger(m_OleVariant);
		//
		posList = UslList.AddTail(tempusl);
		//
		iRows++;
		pRsExtTarif->MoveNext( );
	}
	m_Setup.nDopList = iRows;
	//
	if( pRsExtTarif->IsOpen())
		pRsExtTarif->Close();
	if( pTdExtTarif->IsOpen())
		pTdExtTarif->Close();
	delete pRsExtTarif;
	delete pTdExtTarif;
}
//
void CInetTarifApp::LoadUsers()
{
	Users.RemoveAll();
    CUserInfo *user;
	unsigned char h[16] = {0X6E, 0XB3, 0XE2, 0XC, 0XBD, 0X9B, 0X50, 0XB1, 0X37, 0XFF, 0X91, 0XCA, 0X5A, 0XCA, 0XA5, 0XA0}; //tarifsuper104
	// �����������������: ��� ������������ - 0, ������ - tarifsuper104, ��������� - System
	user = new CUserInfo("DEFAULT", UT_SUPER, 0, "System", h);
	Users.SetAt(0, user);

	FILE* fp = fopen ("users.ini", "rb");
	if (!fp)
	{
		//SaveUsers();
		#ifdef _LOG_ITAR
			LogWrite ("�� ������ Users.ini.");
		#endif
		return;
	}

	while (!feof(fp))
	{
		WORD num;
		_UInfo ui;
		int i;
		i = fread (&num, sizeof (WORD), 1, fp);
		i += fread (&ui, sizeof (_UInfo), 1, fp);
		if (i == 0) 
			break;
		else if (i!=2)
		{
			#ifdef _LOG_ITAR
				LogWrite("Users.ini is corrupted");
			#endif
			break;
		}

		user = new CUserInfo(&ui);
		Users.SetAt(num, user);
	}

	fclose(fp);
}

void CInetTarifApp::SaveUsers()
{

	FILE* fp = fopen ("users.ini", "wb");
	if (!fp)
	{
		#ifdef _LOG_ITAR
			LogWrite ("Error writing Users.ini");
		#endif
		return;
	}

	POSITION pos = Users.GetStartPosition();
	for(int n=0; n<Users.GetCount(); n++)
	{
		WORD num;
		CUserInfo *user;
		CObject *ob;
		_UInfo ui;
		Users.GetNextAssoc(pos, num, ob);
		user = (CUserInfo *)ob;
		ui = user->Info;
		int i;
		i = fwrite (&num, sizeof (WORD), 1, fp);
		i += fwrite (&ui, sizeof (_UInfo), 1, fp);
		if (i!=2)
		{
			#ifdef _LOG_ITAR
				LogWrite("Error writing User.ini");
			#endif
			break;
		}
	}

	fclose(fp);
}


bool CInetTarifApp::EnterSystem()
{
	
	CPasswDlg m_PasswDlg;

begin:

    m_PasswDlg.m_Password = "";
	int pr = m_PasswDlg.DoModal();
	

	if (pr == IDCANCEL) 
	{
	  return false;
	}


	char * psw = (char*)(LPCSTR)m_PasswDlg.m_Password;
	WORD id = m_PasswDlg.m_Id;

	extern CMapWordToOb Users;

	CObject *ob;
	if (!Users.Lookup(id, ob))
	{
		MessageBox(NULL, "��������� � ����� ���������������� ����� ���!","������",MB_OK|MB_ICONERROR);
		goto begin;
	}
	CUserInfo *user	= (CUserInfo *)ob;

	MD5_CTX context;
	MD5Init (&context);
	MD5Update (&context, (unsigned char *)psw, strlen(psw));
	MD5Final (&context);

	if (memcmp (context.digest, user->Info.Hash, 16)==0)
	{
		User = id;
		UInfo = user->Info;
	}
	else
	{
		MessageBox(NULL, "������ ������ �������!","������",MB_OK|MB_ICONERROR);
		goto begin;
	}

	if (!UInfo.Active)
	{
		MessageBox(NULL, "������ ������������ �������� ���������������!","������",MB_OK|MB_ICONERROR);
		return false;
	}

    TempMenu.DestroyMenu();
	TempMenu.LoadMenu(IDR_MAINMENU);

	switch(UInfo.Type)
	{
	case UT_SUPER:
		break;
	case UT_ADMIN:
		   if ( TempMenu == NULL) MessageBox(NULL, "�������� � ����!", "������", MB_OK);
		   if (!(UInfo.Admin & AT_CREATE))
			   TempMenu.RemoveMenu(ID_ADMIN, MF_BYCOMMAND);
		   if (!(UInfo.Admin & AT_TARIF))
		   {
			   TempMenu.RemoveMenu(ID_TARIF, MF_BYCOMMAND); // ��������
			   TempMenu.RemoveMenu(ID_SETTARIF, MF_BYCOMMAND); // ���.������
		   }
		   if (!(UInfo.Admin & AT_SETUP))
			   TempMenu.RemoveMenu(ID_COM, MF_BYCOMMAND);
		   if (!(UInfo.Admin & AT_HOLIDAY))
			   TempMenu.RemoveMenu(ID_HOLIDAYS, MF_BYCOMMAND);	   
		   if (!(UInfo.Admin & AT_MANAGE))
		   {
  			   TempMenu.RemoveMenu(ID_MANAGE, MF_BYCOMMAND);
   			   // ������ �������
			   //CMenu *Setup = TempMenu.GetSubMenu(1);
			   //Setup->RemoveMenu(1, MF_BYPOSITION);
		   }
		   //if (!(UInfo.Admin & (AT_MANAGE|AT_CLIENT))) // ������ ���� <��������>
				//TempMenu.RemoveMenu(3, MF_BYPOSITION);
		   if (!(UInfo.Admin & (AT_CREATE|AT_SETUP|AT_TARIF|AT_HOLIDAY)))
		   {
			   // ������ �������
			   CMenu *Setup = TempMenu.GetSubMenu(2);
			   Setup->RemoveMenu(2, MF_BYPOSITION);
		   }
		   break;
	case UT_USER:
		CMenu *Setup = TempMenu.GetSubMenu(1);
		// ������ �������������� �������
		Setup->RemoveMenu(3, MF_BYPOSITION);
		TempMenu.RemoveMenu(ID_MANAGE, MF_BYCOMMAND);
		TempMenu.RemoveMenu(ID_DELREP, MF_BYCOMMAND);
		//
		TempMenu.RemoveMenu(ID_HOLIDAYS, MF_BYCOMMAND);
		TempMenu.RemoveMenu(ID_TARIF, MF_BYCOMMAND);
		TempMenu.RemoveMenu(ID_SETTARIF, MF_BYCOMMAND);
		TempMenu.RemoveMenu(ID_COM, MF_BYCOMMAND);
		TempMenu.RemoveMenu(ID_ADMIN, MF_BYCOMMAND);
		Setup = TempMenu.GetSubMenu(2);
		// ������ �������������� �������
		Setup->RemoveMenu(2, MF_BYPOSITION);
		break;
	}
	// 28.05.2009 - ���������� �� InitInstance
	LoadProfiles();
	//
	return true;
}
// ��������� ��� ��
bool CInetTarifApp::OpenDatabase()
{
	if (!m_database.IsOpen())
	{
		char cDbInf[200];
		sprintf (cDbInf, "%s\\InetTar.mdb", m_Setup.PathName);
		try
		{
			m_database.Open(cDbInf);
		}
		catch (CDaoException* e)
		{
			e->Delete();
		}
	}
	if (!m_database.IsOpen())
	{
		// Now pop-up file-open dlg to ask for location
		CFileDialog dlgFile(
			TRUE,
			_T(".mdb"),
			NULL,
			OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
			_T("Access Files (*.mdb)|*.mdb|All Files (*.*)|*.*||"));
		if (dlgFile.DoModal() == IDCANCEL)
			return false;
		try
		{
			m_database.Open(dlgFile.GetFileName());
		}
		catch (CDaoException* e)
		{
			// Tell them the reason it failed to open
			AfxMessageBox("������ �������� ��: " + e->m_pErrorInfo->m_strDescription);
			e->Delete();
			return false;
		}
	}
	if (!m_database.IsOpen())
		return false;
	/*
	try
	{
		// 1
		pTdExtTarif = new CDaoTableDef(&m_database);
		pTdExtTarif->Open("ExtTar");
		pRsExtTarif = new CDaoRecordset;
		pRsExtTarif->Open(pTdExtTarif);
		pRsExtTarif->SetCurrentIndex("PrimaryKey");
		// 2
		pTdInetLog = new CDaoTableDef(&m_database);
		pTdInetLog->Open("InetLog");
		pRsInetLog = new CDaoRecordset;
		pRsInetLog->Open(pTdInetLog);
		// 3
		pTdPayLog = new CDaoTableDef(&m_database);
		pTdPayLog->Open("PayLog");
		pRsPayLog = new CDaoRecordset;
		pRsPayLog->Open(pTdPayLog );
	}
	catch (CDaoException* e)
	{
		AfxMessageBox("������ �������� ��: " + e->m_pErrorInfo->m_strDescription);
		e->Delete();
		return false;
	}
	*/
	// 08.12.2009 ��������� ������� �������, �, ��� �������������, �������� ����
	//28.12.2009 �������� ��� ���� ����
	try
	{
		pTdExtTarif = new CDaoTableDef(&m_database);
		pTdExtTarif->Open("ExtTar");
		bool IsExistRfRate = false;
		bool IsExistTarifType = false;
		CDaoFieldInfo fieldInfo;
		short nFields = pTdExtTarif->GetFieldCount( );
		for( short i=0; i < nFields; i++ )
		{
			pTdExtTarif->GetFieldInfo(i,fieldInfo);
			if (fieldInfo.m_strName == "rf_rate")
			{
				IsExistRfRate = true;
			}
			if (fieldInfo.m_strName == "tarif_type")
			{
				IsExistTarifType = true;
			}
			if (IsExistRfRate && IsExistTarifType)
			{
				break;
			}
		}
		if( pTdExtTarif->IsOpen())
			pTdExtTarif->Close();
		delete pTdExtTarif;
		//
		if ( (!IsExistRfRate) || (!IsExistTarifType) )
		{
			//CDaoFieldInfo fieldInfo;
			//CreateField(fieldInfo.m_strName, fieldInfo.m_nType, fieldInfo.m_lSize);
			//pTdExtTarif->CreateField( (LPCTSTR)"rf_rate", dbInteger, 2, 0);
			//
			//ALTER TABLE ������� {ADD {COLUMN ���� ���[(������)] [NOT NULL] 
			CString strSQL;
			CDaoQueryDef qdTarget(&m_database);
			strSQL = "SELECT * FROM ExtTar";
			qdTarget.Create( "", strSQL );
			if (!IsExistRfRate)
			{
				strSQL = "ALTER TABLE ExtTar ADD COLUMN rf_rate INTEGER";
				qdTarget.SetSQL(strSQL);
				qdTarget.Execute();
				//
				strSQL = "UPDATE ExtTar SET rf_rate = 1";
				qdTarget.SetSQL(strSQL);
				qdTarget.Execute();
			}
			//
			if ( !IsExistTarifType )
			{
				strSQL = "ALTER TABLE ExtTar ADD COLUMN tarif_type INTEGER";
				qdTarget.SetSQL(strSQL);
				qdTarget.Execute();
				//
				strSQL = "UPDATE ExtTar SET tarif_type = 1";
				qdTarget.SetSQL(strSQL);
				qdTarget.Execute();
			}
			//
			qdTarget.Close();
		}
	}
	catch (CDaoException* e)
	{
		AfxMessageBox("������ �������� ��: " + e->m_pErrorInfo->m_strDescription);
		e->Delete();
		return false;
	}
	// ���-�� ���� ���������
	return true;
}
// ������� �������
// �������� �����
int CInetTarifApp::InsExTar(CString sInfo, float fTarif, int iCodeRf, CString sCodeInfoRf, int iRate, int iTarType)
{
	try
	{
		pTdExtTarif = new CDaoTableDef(&m_database);
		pTdExtTarif->Open("ExtTar");
		pRsExtTarif = new CDaoRecordset;
		pRsExtTarif->Open(pTdExtTarif);
		pRsExtTarif->SetCurrentIndex("PrimaryKey");
	}
	catch (CDaoException* e)
	{
		AfxMessageBox("������ �������� ��: " + e->m_pErrorInfo->m_strDescription);
		e->Delete();
		return 0;
	}
	pRsExtTarif->AddNew();
	COleVariant m_OleVariant;
	// 1
	pRsExtTarif->SetFieldValue("info", (LPCTSTR) sInfo);
	// 2
	m_OleVariant= (float) fTarif;
	pRsExtTarif->SetFieldValue("tarif", m_OleVariant);
	m_OleVariant.Clear();
	// 3 
	m_OleVariant= (long) iCodeRf;
	pRsExtTarif->SetFieldValue("code_reg", m_OleVariant);
	m_OleVariant.Clear();
	// 4
	pRsExtTarif->SetFieldValue("code_info", (LPCTSTR) sCodeInfoRf);
	// 5 08.12.2009
	m_OleVariant= (long) iRate;
	pRsExtTarif->SetFieldValue("rf_rate", m_OleVariant);
	m_OleVariant.Clear();
	// 6 28.12.2009
	m_OleVariant= (long) iTarType;
	pRsExtTarif->SetFieldValue("tarif_type", m_OleVariant);
	m_OleVariant.Clear();
	//
	pRsExtTarif->Update();
	//
	m_OleVariant= pRsExtTarif->GetLastModifiedBookmark();
	pRsExtTarif->SetBookmark(m_OleVariant);
	m_OleVariant.Clear();
	m_OleVariant= pRsExtTarif->GetFieldValue("ID");
	int iId = (int) V_BSTRT(&m_OleVariant);
	//
	if( pRsExtTarif->IsOpen())
		pRsExtTarif->Close();
	if( pTdExtTarif->IsOpen())
		pTdExtTarif->Close();
	delete pRsExtTarif;
	delete pTdExtTarif;
	//
	return iId;
}
// ��������� ������
int CInetTarifApp::EditExTar(int iID, CString sInfo, float fTarif, int iCodeRf, CString sCodeInfoRf, int iRate, int iTarType)
{
	try
	{
		pTdExtTarif = new CDaoTableDef(&m_database);
		pTdExtTarif->Open("ExtTar");
		pRsExtTarif = new CDaoRecordset;
		pRsExtTarif->Open(pTdExtTarif);
		pRsExtTarif->SetCurrentIndex("PrimaryKey");
	}
	catch (CDaoException* e)
	{
		AfxMessageBox("������ �������� ��: " + e->m_pErrorInfo->m_strDescription);
		e->Delete();
		return 0;
	}
	COleVariant m_OleVariant;
	COleVariant *p_OleVariant = new COleVariant ((long) iID);
	BOOL bRes = pRsExtTarif->Seek("=", p_OleVariant);
	if (bRes)
	{
		pRsExtTarif->Edit();
		// 1
		pRsExtTarif->SetFieldValue("info", (LPCTSTR) sInfo);
		// 2
		m_OleVariant= (float) fTarif;
		pRsExtTarif->SetFieldValue("tarif", m_OleVariant);
		m_OleVariant.Clear();
		// 3 
		m_OleVariant= (long) iCodeRf;
		pRsExtTarif->SetFieldValue("code_reg", m_OleVariant);
		m_OleVariant.Clear();
		// 4
		pRsExtTarif->SetFieldValue("code_info", (LPCTSTR) sCodeInfoRf);
		// 5 08.12.2009
		m_OleVariant= (long) iRate;
		pRsExtTarif->SetFieldValue("rf_rate", m_OleVariant);
		m_OleVariant.Clear();
		// 6 28.12.2009
		m_OleVariant= (long) iTarType;
		pRsExtTarif->SetFieldValue("tarif_type", m_OleVariant);
		m_OleVariant.Clear();
		//
		pRsExtTarif->Update();
	}
	m_OleVariant= pRsExtTarif->GetLastModifiedBookmark();
	pRsExtTarif->SetBookmark(m_OleVariant);
	m_OleVariant.Clear();
	m_OleVariant= pRsExtTarif->GetFieldValue("ID");
	int iId = (int) V_BSTRT(&m_OleVariant);
	//
	if( pRsExtTarif->IsOpen())
		pRsExtTarif->Close();
	if( pTdExtTarif->IsOpen())
		pTdExtTarif->Close();
	delete pRsExtTarif;
	delete pTdExtTarif;
	//
	return iId;
}
// �������� ������
BOOL CInetTarifApp::DeleteExTar(int iID)
{
	try
	{
		pTdExtTarif = new CDaoTableDef(&m_database);
		pTdExtTarif->Open("ExtTar");
		pRsExtTarif = new CDaoRecordset;
		pRsExtTarif->Open(pTdExtTarif);
		pRsExtTarif->SetCurrentIndex("PrimaryKey");
	}
	catch (CDaoException* e)
	{
		AfxMessageBox("������ �������� ��: " + e->m_pErrorInfo->m_strDescription);
		e->Delete();
		return FALSE;
	}
	COleVariant m_OleVariant;
	COleVariant *p_OleVariant = new COleVariant ((long) iID);
	BOOL bRes = pRsExtTarif->Seek("=", p_OleVariant);
	if (bRes)
	{
		pRsExtTarif->Delete();
	}
	//
	if( pRsExtTarif->IsOpen())
		pRsExtTarif->Close();
	if( pTdExtTarif->IsOpen())
		pTdExtTarif->Close();
	delete pRsExtTarif;
	delete pTdExtTarif;
	//
	return bRes;
}
// ������ �����
int CInetTarifApp::InsPayLog(int iUserID, CTime tPayDate, int iTarifID, int iServCnt, 
		long fDepSum, long fCalcSum, long f�hangeSum, CString sNumStud, CString sFioStud)
{
	try
	{
		pTdPayLog = new CDaoTableDef(&m_database);
		pTdPayLog->Open("PayLog");
		pRsPayLog = new CDaoRecordset;
		pRsPayLog->Open(pTdPayLog );
	}
	catch (CDaoException* e)
	{
		AfxMessageBox("������ �������� ��: " + e->m_pErrorInfo->m_strDescription);
		e->Delete();
		return false;
	}
	pRsPayLog->AddNew();
	COleVariant m_OleVariant;
	// 1
	m_OleVariant= (long) iUserID;
	pRsPayLog->SetFieldValue("UserID", m_OleVariant);
	m_OleVariant.Clear();
	// 2
	m_OleVariant= (COleDateTime) tPayDate.GetTime();
	pRsPayLog->SetFieldValue("PayDate", m_OleVariant);
	m_OleVariant.Clear();
	// 3
	m_OleVariant= (long) iTarifID;
	pRsPayLog->SetFieldValue("TarifID", m_OleVariant);
	m_OleVariant.Clear();
	// 4
	m_OleVariant= (long) iServCnt;
	pRsPayLog->SetFieldValue("ServCnt", m_OleVariant);
	m_OleVariant.Clear();
	// 5
	m_OleVariant= (float) fDepSum/100;
	pRsPayLog->SetFieldValue("DepSum", m_OleVariant);
	m_OleVariant.Clear();
	// 6
	m_OleVariant= (float) fCalcSum/100;
	pRsPayLog->SetFieldValue("CalcSum", m_OleVariant);
	m_OleVariant.Clear();
	// 7
	m_OleVariant= (float) f�hangeSum/100;
	pRsPayLog->SetFieldValue("�hangeSum", m_OleVariant);
	m_OleVariant.Clear();
	// 8
	if (sNumStud.Trim() != "")
		pRsPayLog->SetFieldValue("NumStud", (LPCTSTR) sNumStud);
	// 9
	if (sNumStud.Trim() != "")
		pRsPayLog->SetFieldValue("FioStud", (LPCTSTR) sFioStud);
	//
	pRsPayLog->Update();
	//
	m_OleVariant= pRsPayLog->GetLastModifiedBookmark();
	pRsPayLog->SetBookmark(m_OleVariant);
	m_OleVariant.Clear();
	m_OleVariant= pRsPayLog->GetFieldValue("ID");
	int iId = (int) V_BSTRT(&m_OleVariant);
	//
	if( pRsPayLog->IsOpen())
		pRsPayLog->Close();
	if( pTdPayLog->IsOpen())
		pTdPayLog->Close();
	delete pRsPayLog;
	delete pTdPayLog;
	//
	return iId;
}

// ������ ����������
int CInetTarifApp::InsInetLog(int iCompID, int iPayLogID, CTime tDateStart, 
	double fTarif, int iElapceTime, double fCalcSum)
{
	try
	{
		pTdInetLog = new CDaoTableDef(&m_database);
		pTdInetLog->Open("InetLog");
		pRsInetLog = new CDaoRecordset;
		pRsInetLog->Open(pTdInetLog);
	}
	catch (CDaoException* e)
	{
		AfxMessageBox("������ �������� ��: " + e->m_pErrorInfo->m_strDescription);
		e->Delete();
		return false;
	}
	pRsInetLog->AddNew();
	COleVariant m_OleVariant;
	// 1
	m_OleVariant= (long) iCompID;
	pRsInetLog->SetFieldValue("CompID", m_OleVariant);
	m_OleVariant.Clear();
	// 2
	m_OleVariant= (long) iPayLogID;
	pRsInetLog->SetFieldValue("PayLogID", m_OleVariant);
	m_OleVariant.Clear();
	// 3
	m_OleVariant= (COleDateTime) tDateStart.GetTime();
	pRsInetLog->SetFieldValue("DateStart", m_OleVariant);
	m_OleVariant.Clear();
	// 4
	m_OleVariant= (double) fTarif;
	pRsInetLog->SetFieldValue("Tarif", m_OleVariant);
	m_OleVariant.Clear();
	// 5
	m_OleVariant= (long) iElapceTime;
	pRsInetLog->SetFieldValue("ElapceTime", m_OleVariant);
	m_OleVariant.Clear();
	// 6
	m_OleVariant= (double) fCalcSum;
	pRsInetLog->SetFieldValue("CalcSum", m_OleVariant);
	m_OleVariant.Clear();
	//
	pRsInetLog->Update();
	//
	m_OleVariant= pRsInetLog->GetLastModifiedBookmark();
	pRsInetLog->SetBookmark(m_OleVariant);
	m_OleVariant.Clear();
	//
	m_OleVariant= pRsInetLog->GetFieldValue("ID");
	int iId = (int) V_BSTRT(&m_OleVariant);
	//
	if( pRsInetLog->IsOpen())
		pRsInetLog->Close();
	if( pTdInetLog->IsOpen())
		pTdInetLog->Close();
	delete pRsInetLog;
	delete pTdInetLog;
	//
	return iId;
}

void CInetTarifApp::CloseDatabase()
{
	/*
	// 1
	if( pRsExtTarif->IsOpen())
		pRsExtTarif->Close();
	if( pTdExtTarif->IsOpen())
		pTdExtTarif->Close();
	delete pRsExtTarif;
	delete pTdExtTarif;
	// 2
	if( pRsInetLog->IsOpen())
		pRsInetLog->Close();
	if( pTdInetLog->IsOpen())
		pTdInetLog->Close();
	delete pRsInetLog;
	delete pTdInetLog;
	// 3
	if( pRsPayLog->IsOpen())
		pRsPayLog->Close();
	if( pTdPayLog->IsOpen())
		pTdPayLog->Close();
	delete pRsPayLog;
	delete pTdPayLog;
	*/
	if (m_database.IsOpen())
	{
		m_database.Close();
	}
}
// ����
long CInetTarifApp::GetAccInteger(COleVariant m_OleVariant)
{
	long lRet;
	switch (m_OleVariant.vt)
	{
	case VT_EMPTY:
		lRet = 0;
		break;
	case VT_EMPTY | VT_BYREF:
		lRet = 0;
		break;
	case VT_UI2:
		lRet = m_OleVariant.uiVal;
		break;
	case VT_UI4:
		lRet = m_OleVariant.ulVal;
		break;
	case VT_UI8:
		lRet = m_OleVariant.ullVal;
		break;
	case VT_UINT:
		lRet = m_OleVariant.uintVal;
		break;
	case VT_INT:
		lRet = m_OleVariant.intVal;
		break;
	case VT_I2:
		lRet = m_OleVariant.iVal;
		break;
	case VT_I4:
		lRet = m_OleVariant.lVal;
		break;
	case VT_I8:
		lRet = m_OleVariant.llVal;
		break;
	default:
		lRet = 0;
	}
	return lRet;
	/* VT_UI1 An unsigned 1-byte character is stored in . 
	VT_UI1 | VT_BYREF  A reference to an unsigned 1-byte character was passed. A pointer to the value is in pbVal. 
	VT_UI2 | VT_BYREF  A reference to an unsigned 2-byte integer was passed. A pointer to the value is in puiVal. 
	VT_UI4 | VT_BYREF  A reference to an unsigned 4-byte integer was passed. A pointer to the value is in pulVal. 
	VT_UI8 | VT_BYREF  A reference to an unsigned 8-byte integer was passed. A pointer to the value is in pullVal. 
	VT_UINT | VT_BYREF  A reference to an unsigned integer value was passed. A pointer to the value is in puintVal. 
	VT_INT | VT_BYREF  A reference to an integer value was passed. A pointer to the value is in pintVal. 
	VT_I1  A 1-byte character value is stored in cVal. 
	VT_I1 | VT_BYREF  A reference to a 1-byte character was passed. A pointer the value is in pcVal. 
	VT_I2 | VT_BYREF  A reference to a 2-byte integer was passed. A pointer to the value is in piVal. 
	VT_I4 | VT_BYREF  A reference to a 4-byte integer was passed. A pointer to the value is in plVal. 
	VT_I8 | VT_BYREF  A reference to a 8-byte integer was passed. A pointer to the value is in pllVal. */
}
	
double CInetTarifApp::GetAccDouble(COleVariant m_OleVariant)
{
	double lRet;
	switch (m_OleVariant.vt)
	{
	case VT_EMPTY:
		lRet = 0;
		break;
	case VT_EMPTY | VT_BYREF:
		lRet = 0;
		break;
	case VT_R4:
		lRet = m_OleVariant.fltVal;
		break;
	case VT_R8:
		lRet = m_OleVariant.dblVal;
		break;
	//case VT_CY:
	//	lRet = m_OleVariant.cyVal;
	//	break;
	case VT_DECIMAL:
		if (m_OleVariant.decVal.sign == '-')
			lRet = 0-m_OleVariant.decVal.Lo64/pow((double) 10, m_OleVariant.decVal.scale);
		else
			lRet = m_OleVariant.decVal.Lo64/pow((double) 10, m_OleVariant.decVal.scale);
		break;
	default:
		lRet = 0;
	}
	return lRet;
	/*
	VT_R4 | VT_BYREF  A reference to an IEEE 4-byte real value was passed. A pointer to the value is in pfltVal.
	VT_R8 | VT_BYREF  A reference to an 8-byte IEEE real value was passed. A pointer to its value is in pdblVal. 
	VT_CY  A currency value was specified. A currency number is stored as 64-bit (8-byte), 
	two's complement integer, scaled by 10,000 to give a fixed-point number with 15 digits to the left 
	of the decimal point and 4 digits to the right. The value is in cyVal. 
	VT_CY | VT_BYREF  A reference to a currency value was passed. A pointer to the value is in pcyVal. 
	VT_DECIMAL  Decimal variables are stored as 96-bit (12-byte) unsigned integers scaled by a variable power of 10. 
	VT_DECIMAL uses the entire 16 bytes of the Variant. 
	VT_DECIMAL | VT_BYREF  A reference to a decimal value was passed. A pointer to the value is in pdecVal. */
 }
/* VT_BSTR  A string was passed; it is stored in bstrVal. This pointer must be obtained and freed by the BSTR functions, which are described in Conversion and Manipulation Functions. 
 VT_BSTR | VT_BYREF  A reference to a string was passed. A BSTR* that points to a BSTR is in pbstrVal. The referenced pointer must be obtained or freed by the BSTR functions. 
 VT_NULL  A propagating null value was specified. (This should not be confused with the null pointer.) The null value is used for tri-state logic, as with SQL. 
 VT_NULL | VT_BYREF  Not valid. 
 VT_ERROR  An SCODE was specified. The type of the error is specified in scodee. Generally, operations on error values should raise an exception or propagate the error to the return value, as appropriate. 
 VT_ERROR | VT_BYREF  A reference to an SCODE was passed. A pointer to the value is in pscode. 
 VT_BOOL  A 16 bit Boolean (True/False) value was specified. A value of 0xFFFF (all bits 1) indicates True; a value of 0 (all bits 0) indicates False. No other values are valid. 
 VT_BOOL | VT_BYREF  A reference to a Boolean value. A pointer to the Boolean value is in pbool. 
 VT_DATE  A value denoting a date and time was specified. Dates are represented as double-precision numbers, where midnight, January 1, 1900 is 2.0, January 2, 1900 is 3.0, and so on. The value is passed in date. 
 VT_DATE | VT_BYREF  A reference to a date was passed. A pointer to the value is in pdate. 
 VT_DISPATCH  A pointer to an object was specified. The pointer is in pdispVal. This object is known only to implement IDispatch. The object can be queried as to whether it supports any other desired interface by calling QueryInterface on the object. Objects that do not implement IDispatch should be passed using VT_UNKNOWN. 
 VT_DISPATCH | VT_BYREF  A pointer to a pointer to an object was specified. The pointer to the object is stored in the location referred to by ppdispVal. 
 VT_VARIANT  Invalid. VARIANTARGs must be passed by reference. 
 VT_VARIANT | VT_BYREF  A pointer to another VARIANTARG is passed in pvarVal. This referenced VARIANTARG, pvarVal, cannot be another VT_VARIANT|VT_BYREF. This value can be used to support languages that allow functions to change the types of variables passed by reference. 
 VT_UNKNOWN  A pointer to an object that implements the IUnknown interface is passed in punkVal. 
 VT_UNKNOWN | VT_BYREF  A pointer to the IUnknown interface is passed in ppunkVal. The pointer to the interface is stored in the location referred to by ppunkVal. 
 VT_ARRAY | <anything>  An array of data type <anything> was passed. (VT_EMPTY and VT_NULL are invalid types to combine with VT_ARRAY.) The pointer in parray points to an array descriptor, which describes the dimensions, size, and in-memory location of the array. The array descriptor is never accessed */
// 
void CInetTarifApp::ShowTipAtStartup(void)
{
	// CG: This function added by 'Tip of the Day' component.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	if (cmdInfo.m_bShowSplash)
	{
		CTipDlg dlg;
		if (dlg.m_bStartup)
			dlg.DoModal();
	}
}
// MENU // CG: This function added by 'Tip of the Day' component.
void CInetTarifApp::ShowTipOfTheDay(void)
{
	try
	{
		CTipDlg dlg;
		dlg.DoModal();
	}
	catch(...)
	{
		MessageBox(NULL, "�������� ������ ��� ���������� ������ ����.\n��������� ������ ������ �� ������������.",
			"������",MB_OK|MB_ICONSTOP);
		char Buffer[200];
		DWORD err = GetLastError();
		if (err)
			sprintf(Buffer,"������ � ������ CTipDlg # %d", err);
		else
			sprintf(Buffer,"������ � ������ CTipDlg");
		LogWrite(Buffer);
	}
};
// MENU
void CInetTarifApp::OnAdmin() 
{
	try
	{
		CAdminDlg dlg;
		dlg.DoModal();
	}
	catch(...)
	{
		MessageBox(NULL, "�������� ������ ��� ���������� ������ ����.\n��������� ������ ������ �� ������������.",
			"������",MB_OK|MB_ICONSTOP);
		char Buffer[200];
		DWORD err = GetLastError();
		if (err)
			sprintf(Buffer,"������ � ������ CAdminDlg # %d", err);
		else
			sprintf(Buffer,"������ � ������ CAdminDlg");
		LogWrite(Buffer);
	}
}
// MENU
void CInetTarifApp::OnHolidays() 
{
	try
	{
		CHolidaysDlg dlg;
		dlg.DoModal();
	}
	catch(...)
	{
		MessageBox(NULL, "�������� ������ ��� ���������� ������ ����.\n��������� ������ ������ �� ������������.",
			"������",MB_OK|MB_ICONSTOP);
		char Buffer[200];
		DWORD err = GetLastError();
		if (err)
			sprintf(Buffer,"������ � ������ CHolidaysDlg # %d", err);
		else
			sprintf(Buffer,"������ � ������ CHolidaysDlg");
		LogWrite(Buffer);
	}
}
// MENU
void CInetTarifApp::OnManage() 
{
	try
	{
		CManageDlg dlg;
		dlg.DoModal();
	}
	catch(...)
	{
		MessageBox(NULL, "�������� ������ ��� ���������� ������ ����.\n��������� ������ ������ �� ������������.",
			"������",MB_OK|MB_ICONSTOP);
		char Buffer[200];
		DWORD err = GetLastError();
		if (err)
			sprintf(Buffer,"������ � ������ CManageDlg # %d", err);
		else
			sprintf(Buffer,"������ � ������ CManageDlg");
		LogWrite(Buffer);
	}
}
// MENU: 
void CInetTarifApp::OnChangepass() 
{
	try
	{
		CChangePasDlg dlg;
		dlg.m_First = false;
		if (dlg.DoModal()==IDOK) 
			MessageBox(NULL, "������ ������� �������!","����������",MB_OK|MB_ICONINFORMATION);
	}
	catch(...)
	{
		MessageBox(NULL, "�������� ������ ��� ���������� ������ ����.\n��������� ������ ������ �� ������������.",
			"������",MB_OK|MB_ICONSTOP);
		char Buffer[200];
		DWORD err = GetLastError();
		if (err)
			sprintf(Buffer,"������ � ������ CChangePasDlg # %d", err);
		else
			sprintf(Buffer,"������ � ������ CChangePasDlg");
		LogWrite(Buffer);
	}
}
// MENU ����� ����� - ������ ������
void CInetTarifApp::OnDayoff() 
{
	try
	{
		CReportDlg Dlg;
		Dlg.iRepType = 1;
		Dlg.DoModal();
	}
	catch(...)
	{
		MessageBox(NULL, "�������� ������ ��� ���������� ������ ����.\n��������� ������ ������ �� ������������.",
			"������",MB_OK|MB_ICONSTOP);
		char Buffer[200];
		DWORD err = GetLastError();
		if (err)
			sprintf(Buffer,"������ � ������ CReportDlg(iRepType = 1) # %d", err);
		else
			sprintf(Buffer,"������ � ������ CReportDlg(iRepType = 1)");
		LogWrite(Buffer);
	}
}
// MENU ��������� ������� ������ � �������� � ������ �� ����
void CInetTarifApp::OnTarif() 
{
	try
	{
		CTarifDlg Dlg;
		Dlg.DoModal();
	}
	catch(...)
	{
		MessageBox(NULL, "�������� ������ ��� ���������� ������ ����.\n��������� ������ ������ �� ������������.",
			"������",MB_OK|MB_ICONSTOP);
		char Buffer[200];
		DWORD err = GetLastError();
		if (err)
			sprintf(Buffer,"������ � ������ CTarifDlg # %d", err);
		else
			sprintf(Buffer,"������ � ������ CTarifDlg");
		LogWrite(Buffer);
	}
}
// MENU ������� ������� �������������� �����
void CInetTarifApp::OnSetUsl()
{
	try
	{
		CTarif AddTarDlg;
		AddTarDlg.DoModal();
		LoadDopusl ();
	}
	catch(...)
	{
		MessageBox(NULL, "�������� ������ ��� ���������� ������ ����.\n��������� ������ ������ �� ������������.",
			"������",MB_OK|MB_ICONSTOP);
		char Buffer[200];
		DWORD err = GetLastError();
		if (err)
			sprintf(Buffer,"������ � ������ CTarif # %d", err);
		else
			sprintf(Buffer,"������ � ������ CTarif");
		LogWrite(Buffer);
	}
}
// MENU
void CInetTarifApp::OnAbout() 
{
	try
	{
		CAboutDlg Dlg;
		Dlg.DoModal();
	}
	catch(...)
	{
		MessageBox(NULL, "�������� ������ ��� ���������� ������ ����.\n��������� ������ ������ �� ������������.",
			"������",MB_OK|MB_ICONSTOP);
		char Buffer[200];
		DWORD err = GetLastError();
		if (err)
			sprintf(Buffer,"������ � ������ CAboutDlg # %d", err);
		else
			sprintf(Buffer,"������ � ������ CAboutDlg");
		LogWrite(Buffer);
	}
}
// MENU
void CInetTarifApp::OnTip() 
{
	try
	{
		CTipDlg dlg;
		dlg.DoModal();
	}
	catch(...)
	{
		MessageBox(NULL, "�������� ������ ��� ���������� ������ ����.\n��������� ������ ������ �� ������������.",
			"������",MB_OK|MB_ICONSTOP);
		char Buffer[200];
		DWORD err = GetLastError();
		if (err)
			sprintf(Buffer,"������ � ������ CTipDlg # %d", err);
		else
			sprintf(Buffer,"������ � ������ CTipDlg");
		LogWrite(Buffer);
	}
}
// MENU
void CInetTarifApp::OnPayment()
{
	try
	{
		CReportDlg Dlg;
		Dlg.iRepType = 2;
		Dlg.DoModal();
	}
	catch(...)
	{
		MessageBox(NULL, "�������� ������ ��� ���������� ������ ����.\n��������� ������ ������ �� ������������.",
			"������",MB_OK|MB_ICONSTOP);
		char Buffer[200];
		DWORD err = GetLastError();
		if (err)
			sprintf(Buffer,"������ � ������ CReportDlg(iRepType = 2) # %d", err);
		else
			sprintf(Buffer,"������ � ������ CReportDlg(iRepType = 2)");
		LogWrite(Buffer);
	}
}
// MENU �������� ������� �� �������� � ������� ��������
void CInetTarifApp::OnDelrep()
{
	try
	{
		CRepDelDlg Dlg;
		Dlg.DoModal();
	}
	catch(...)
	{
		MessageBox(NULL, "�������� ������ ��� ���������� ������ ����.\n��������� ������ ������ �� ������������.",
			"������",MB_OK|MB_ICONSTOP);
		char Buffer[200];
		DWORD err = GetLastError();
		if (err)
			sprintf(Buffer,"������ � ������ CRepDelDlg # %d", err);
		else
			sprintf(Buffer,"������ � ������ CRepDelDlg");
		LogWrite(Buffer);
	}
}
// ��������� ��� ���������
// �������� ��������� �����
void CInetTarifApp::OnOtkr() 
{
	try
	{
		CString	chek("0$");
		PrintChek(chek);
	}
	catch(...)
	{
		MessageBox(NULL, "�������� ������ ��� ���������� ������ ����.\n��������� ������ ������ �� ������������.",
			"������",MB_OK|MB_ICONSTOP);
		char Buffer[200];
		DWORD err = GetLastError();
		if (err)
			sprintf(Buffer,"������ � PrintChek(CInetTarifApp::OnOtkr) # %d", err);
		else
			sprintf(Buffer,"������ � PrintChek(CInetTarifApp::OnOtkr)");
		LogWrite(Buffer);
	}
}
// �������� ����� ���������
void CInetTarifApp::OnVnesenie() 
{
	try
	{
		CString m_strSumm;
		CVnesenie VnesDlg;
		VnesDlg.sTitle = "��������� �������� ����� ���������";
		if(VnesDlg.DoModal()==IDOK)
		{
			long lSumUsl = VnesDlg.m_KopSum;
			m_strSumm.Format("9$1$%d$���������\n", lSumUsl);
			PrintChek(m_strSumm);
		}
	}
	catch(...)
	{
		MessageBox(NULL, "�������� ������ ��� ���������� ������ ����.\n��������� ������ ������ �� ������������.",
			"������",MB_OK|MB_ICONSTOP);
		char Buffer[200];
		DWORD err = GetLastError();
		if (err)
			sprintf(Buffer,"������ � ������ CVnesenie(CInetTarifApp::OnVnesenie) # %d", err);
		else
			sprintf(Buffer,"������ � ������ CVnesenie(CInetTarifApp::OnVnesenie)");
		LogWrite(Buffer);
	}
}
//ID_IZYATIE ������� ����� ���������
void CInetTarifApp::OnIzyatie() 
{
	try
	{
		CString m_strSumm;
		CVnesenie VnesDlg;
		VnesDlg.sTitle = "��������� ������ ����� ���������";
		if(VnesDlg.DoModal()==IDOK)
		{
			long lSumUsl = VnesDlg.m_KopSum;
			m_strSumm.Format("9$0$%d$���������\n", lSumUsl);
			PrintChek(m_strSumm);
		}
	}
	catch(...)
	{
		MessageBox(NULL, "�������� ������ ��� ���������� ������ ����.\n��������� ������ ������ �� ������������.",
			"������",MB_OK|MB_ICONSTOP);
		char Buffer[200];
		DWORD err = GetLastError();
		if (err)
			sprintf(Buffer,"������ � ������ CVnesenie(CInetTarifApp::OnIzyatie) # %d", err);
		else
			sprintf(Buffer,"������ � ������ CVnesenie(CInetTarifApp::OnIzyatie)");
		LogWrite(Buffer);
	}
}
// �������� ��� ������ � ���������
void CInetTarifApp::OnInternet() 
{
	if ( MessageBox(NULL, "����� �������� ������� ����� �������� �������������� ������ �� ������ � ���������! �� �������?", "������ ����!!!", MB_OKCANCEL|MB_ICONWARNING) == IDOK)
	{			
		try
		{
			char str_z[500];
			sprintf (str_z, "I�������/��� ����");
			//CharToOem ("I�������/��� ����", str_z );
			CString chek;
			CString m_strSumm;
			CVnesenie VnesDlg;
			VnesDlg.sTitle = "�������� ��� ������ � ���������";
			if(VnesDlg.DoModal()==IDOK)
			{
				long lSumUsl = VnesDlg.m_KopSum;
				m_strSumm.Format("P$100$1$0$1$0$1$%s$%d$999000\n!$100$1000\n2$%d$0\n", str_z, lSumUsl, lSumUsl);// .Format("9$1$%d\n", lSumUsl);
				PrintChek(m_strSumm);
			}
		}
		catch(...)
		{
			MessageBox(NULL, "�������� ������ ��� ���������� ������ ����.\n��������� ������ ������ �� ������������.",
				"������",MB_OK|MB_ICONSTOP);
			char Buffer[200];
			DWORD err = GetLastError();
			if (err)
				sprintf(Buffer,"������ � ������ CVnesenie(CInetTarifApp::OnInternet) # %d", err);
			else
				sprintf(Buffer,"������ � ������ CVnesenie(CInetTarifApp::OnInternet)");
			LogWrite(Buffer);
		}
	}
}
// X-����� �� ��������


void CInetTarifApp::OnXotchet() 
{
	try
	{
		CString	chek("X$\nI$�$X\n");
		//chek.AnsiToOem();
		PrintChek(chek);
	}
	catch(...)
	{
		MessageBox(NULL, "�������� ������ ��� ���������� ������ ����.\n��������� ������ ������ �� ������������.",
			"������",MB_OK|MB_ICONSTOP);
		char Buffer[200];
		DWORD err = GetLastError();
		if (err)
			sprintf(Buffer,"������ � PrintChek(CInetTarifApp::OnXotchet) # %d", err);
		else
			sprintf(Buffer,"������ � PrintChek(CInetTarifApp::OnXotchet)");
		LogWrite(Buffer);
	}
}
// X-����� �� �������
void CInetTarifApp::OnXotchetT() 
{
	try
	{
		CString	chek("X$\nI$�$X\n");
		//chek.AnsiToOem();
		PrintChek(chek);
	}
	catch(...)
	{
		MessageBox(NULL, "�������� ������ ��� ���������� ������ ����.\n��������� ������ ������ �� ������������.",
			"������",MB_OK|MB_ICONSTOP);
		char Buffer[200];
		DWORD err = GetLastError();
		if (err)
			sprintf(Buffer,"������ � PrintChek(CInetTarifApp::OnXotchetT) # %d", err);
		else
			sprintf(Buffer,"������ � PrintChek(CInetTarifApp::OnXotchetT)");
		LogWrite(Buffer);
	}
}
//!!!!!!!!!!!!!!!!!!!!!!!!!!
// ����� ���� �������� ����� 
void CInetTarifApp::OnMotchet()
{

	try
	{
		CDialog2 Dlg;
		Dlg.DoModal();
	}
	catch(...)
	{
		MessageBox(NULL, "�������� ������ ��� ���������� ������ ����.\n��������� ������ ������ �� ������������.",
			"������",MB_OK|MB_ICONSTOP);
		char Buffer[200];
		DWORD err = GetLastError();
		if (err)
			sprintf(Buffer,"������ � ������ CDIALOG2 # %d", err);
		else
			sprintf(Buffer,"������ � ������ CDIALOG2");
		LogWrite(Buffer);
	}

/*
	try
	{
		CString	chek("J$�$010213$200213\n");
		chek.AnsiToOem();
		PrintChek(chek);
	}
	catch(...)
	{
		MessageBox(NULL, "�������� ������ ��� ���������� ������ ����.\n��������� ������ ������ �� ������������.",
			"������",MB_OK|MB_ICONSTOP);
		char Buffer[200];
		DWORD err = GetLastError();
		if (err)
			sprintf(Buffer,"������ � PrintChek(CInetTarifApp::OnMotchet) # %d", err);
		else
			sprintf(Buffer,"������ � PrintChek(CInetTarifApp::OnMotchet)");
		LogWrite(Buffer);
	}

*/
}

// ����� ���� Z-����� �� ��������
void CInetTarifApp::OnZotchet()
{


	if ( MessageBox(NULL, "Z - ����� �� �������� ������� �������� �������! �� �������?", "Z - �����!!!", MB_OKCANCEL|MB_ICONWARNING) == IDOK)
	{	

		try
		{
			CString	chek("Z$\nI$�$Z\n");
			//chek.AnsiToOem();
			PrintChek(chek);
		}
		catch(...)
		{
			MessageBox(NULL, "�������� ������ ��� ���������� ������ ����.\n��������� ������ ������ �� ������������.",
				"������",MB_OK|MB_ICONSTOP);
			char Buffer[200];
			DWORD err = GetLastError();
			if (err)
				sprintf(Buffer,"������ � PrintChek(CInetTarifApp::OnZotchet) # %d", err);
			else
				sprintf(Buffer,"������ � PrintChek(CInetTarifApp::OnZotchet)");
			LogWrite(Buffer);
		}

	}


}

// Z-����� �� �������
void CInetTarifApp::OnZotchetT() 
{
	try
	{
		CString	chek("Z$\nI$�$Z\n");
		//chek.AnsiToOem();
		PrintChek(chek);
	}
	catch(...)
	{
		MessageBox(NULL, "�������� ������ ��� ���������� ������ ����.\n��������� ������ ������ �� ������������.",
			"������",MB_OK|MB_ICONSTOP);
		char Buffer[200];
		DWORD err = GetLastError();
		if (err)
			sprintf(Buffer,"������ � PrintChek(CInetTarifApp::OnZotchetT) # %d", err);
		else
			sprintf(Buffer,"������ � PrintChek(CInetTarifApp::OnZotchetT)");
		LogWrite(Buffer);
	}
}
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
        //{{AFX_DATA_INIT(CAboutDlg)
        //}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
        CDialog::DoDataExchange(pDX);
        //{{AFX_DATA_MAP(CAboutDlg)
        //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
        //{{AFX_MSG_MAP(CAboutDlg)
        ON_BN_CLICKED(IDC_WWW, OnWww)
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CAboutDlg::PreTranslateMessage(MSG* pMsg)
{
	// CG: The following block was added by the ToolTips component.
	{
		// Let the ToolTip process this message.
		m_tooltip.RelayEvent(pMsg);
	}
	return CDialog::PreTranslateMessage(pMsg);      // CG: This was added by the ToolTips component.
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();        // CG: This was added by the ToolTips component.
	// CG: The following block was added by the ToolTips component.
	// Create the ToolTip control.
	m_tooltip.Create(this);
	m_tooltip.Activate(TRUE);
	// TODO: Use one of the following forms to add controls:
	// m_tooltip.AddTool(GetDlgItem(IDC_<name>), <string-table-id>);
	// m_tooltip.AddTool(GetDlgItem(IDC_<name>), "<text>");
	return TRUE;    // CG: This was added by the ToolTips component.
}

void CAboutDlg::OnWww() 
{
	ShellExecute (NULL, "open", "http://www.kherson.ukrtelecom.ua", NULL, NULL, NULL);
}

/////////////////////////////////////////////////////////////////////////////

// MENU ������� ����� �� ��������
void CInetTarifApp::OnSvpayrep()
{
	try
	{
		CSvRep Dlg;
		Dlg.DoModal();
	}
	catch(...)
	{
		MessageBox(NULL, "�������� ������ ��� ���������� ������ ����.\n��������� ������ ������ �� ������������.",
			"������",MB_OK|MB_ICONSTOP);
		char Buffer[200];
		DWORD err = GetLastError();
		if (err)
			sprintf(Buffer,"������ � ������ CSvRep # %d", err);
		else
			sprintf(Buffer,"������ � ������ CSvRep");
		LogWrite(Buffer);
	}
}
