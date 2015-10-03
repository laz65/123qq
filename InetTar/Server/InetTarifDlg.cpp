// InetTarifDlg.cpp : implementation file
//
#include "stdafx.h"
#include <math.h>
#include <dos.h>
#include <direct.h>
#include <winsock2.h>
#include <process.h> 

#include "InetTarif.h"
#include "InetTarifDlg.h"
#include "ComSetupDlg.h"
#include "ClientRaschet.h"
#include "NewSeans.h"
#include "ChekDlg.h"
#include "SessMove.h"
//#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only CInetTarifApp object
extern CInetTarifApp theApp;
/////////////////////////////////////////////////////////////////////////////
FILE *HlpGlobal; // hlp?
char fio[50], num[50];
char cClientZalog[100];
double nds;
/////////////////////////////////////////////////////////////////////////////
CWnd* pParentWnd;
HWND m_Main;
int GLT, mx, my, off, m_Time, TimeHistory, TimeCur;
bool SendAll=true, resiz, thr, thr360, thr77;
char WhoSend[100],  card_flag;
/////////////////////////////////////////////////////////////////////////////
int iActivComp, LinkComp; // К-во доступных станций
hCompInfo Computers[MAX_WORKSTATION];
char *TarifName[40] = {"Интернет", "Компьютер","СтудИнтернет","СтудКомпьютер"};
/////////////////////////////////////////////////////////////////////////////
extern void PrintChek(CString strChek);
extern hSetup m_Setup;
extern CList <hDopusl, hDopusl&> UslList;
//extern hDopusl tempusl;
// Код оператора
extern int User; 
extern _UInfo UInfo;
/////////////////////////////////////////////////////////////////////////////
//extern void Except (unsigned int code, char *ProcName);
char LogBuffer[500];
extern void LogWrite(char *text);
/////////////////////////////////////////////////////////////////////////////

//////////////////////////
// Added from SysUtils.cpp
//////////////////////////
#define DEFAULT_PORT 16661
#define DEFAULT_PROTO SOCK_STREAM // TCP
unsigned short port=DEFAULT_PORT;
int socket_type = DEFAULT_PROTO;
char TempStr[100];
/////////////////////////////////////////////////////////////////////////////
#define IDC_STATUS_BAR		600
#define MESSAGE_ZALOG		601
#define MESSAGE_RASCHET     602
// ID таймера
#define IDT_TIMER			660
#define MESSAGE_ZALOG1           666
// wParam - порядковый номер
// lParam - порядковый номер 

/////////////////////////////////////////////////////////////////////////////
#define MAX_PIPE_INSTANCES 100
#define NAME_SIZE  25
#define IN_BUF_SIZE        1000
#define OUT_BUF_SIZE       1000
#define TIME_OUT           0
#define PLEASE_READ        1000
#define PLEASE_WRITE       1000

#define LINE_LEN   80
#define NAME_SIZE  25

// Structure used to hold information about a pipe client.
// They're used as array elements.
typedef struct { HANDLE     hPipe;
                 HANDLE     hEvent;
                 OVERLAPPED overLap;
                 BOOL       live;
                 CHAR Name[NAME_SIZE];
               } WRTHANDLE;

WRTHANDLE clients[MAX_PIPE_INSTANCES];
DWORD     clientCount = 0;             // Global count of connected clients.

typedef struct toPipe 
{
        int    uMsg;
        WPARAM wParam;
        LPARAM lParam;

        bool CText;
        char ZalogText[20];
} _toPipe;
_toPipe m_toPipe;

LONG           lpServerThreadID;
/////////////////////////////////////////////////////////////////////////////
//
char BigTextTime[300][11];
char BigTextRem[300][100];
int CountTime=0;
bool Holiday;
//
double GetTarif (int Type)
{
	double RetVal=0.01;

	SYSTEMTIME SystemTime;
	GetLocalTime(&SystemTime);
	//SystemTime.wHour = 21;
	char TextTime[11];
	sprintf (TextTime, "%02d.%02d.%04d", SystemTime.wDay, SystemTime.wMonth,SystemTime.wYear);
	nds = (m_Setup.CurNds + 100) / 100;
	int f1 = 8;
	int b1 = 21;

	Holiday=false;
	for (int i=0; i<CountTime;i++)
	{
		if (strncmp(TextTime, BigTextTime[i],5)==0)
		{
			Holiday = true;
			break;
		}
	}
	
	switch (Type)
	{
		//Internet Глобальный
		case 0:
			if ((SystemTime.wDayOfWeek==6)||(SystemTime.wDayOfWeek==0)||(Holiday==true))
			    RetVal = m_Setup.Tarif5;
			else if (((SystemTime.wHour>=0) && (SystemTime.wHour< f1)) || ((SystemTime.wHour>= b1) && (SystemTime.wHour<24)))
				RetVal = m_Setup.Tarif3;
			else
				RetVal = m_Setup.Tarif1;
			break;
		//Computer Глобальный
		case 1:
			if ((SystemTime.wDayOfWeek==6)||(SystemTime.wDayOfWeek==0)||(Holiday==true))
			    RetVal = m_Setup.Tarif6;
			else if (((SystemTime.wHour>=0) && (SystemTime.wHour< f1)) || ((SystemTime.wHour>= b1) && (SystemTime.wHour<24)))
				RetVal = m_Setup.Tarif4;
			else
				RetVal = m_Setup.Tarif2;
			break;
		//02.06.2010 old
		//Student
		/*case 2:
			if ((SystemTime.wDayOfWeek==6)||(SystemTime.wDayOfWeek==0)||(Holiday==true))
				RetVal = m_Setup.Tarif8;
			else
	  		  RetVal = m_Setup.Tarif7;
			break;
		*/
		//Интернет Student
		case 2:
			RetVal = m_Setup.Tarif7;
			break;
		//Компьютер Student
		case 3:
			RetVal = m_Setup.Tarif8;
			break;
	}
	return RetVal;
}
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
BOOL LockStation (int Comp);
BOOL UnLockStation (int Comp);
BOOL DisableExplorer(int Comp);
BOOL EnableExplorer (int Comp);
/////////////////////////////////////////////////////////////////////////////
VOID          ServerProc (HWND *);
VOID          TellAll    ();
/////////////////////////////////////////////////////////////////////////////
extern CInetTarifDlg *m_tdlg; //VOID ServerProc(HWND *hWnd)
/////////////////////////////////////////////////////////////////////////////




BOOL Zapros (int Comp)
{
        unsigned short port = DEFAULT_PORT;
        int retval, loopflag=0;
        unsigned int addr;
		BOOL bConn;
        int socket_type = DEFAULT_PROTO;
        struct sockaddr_in server;
        struct hostent *hp;
        WSADATA wsaData;
        SOCKET  conn_socket;
        char Buffer[300];
		char err[200];
		char  TimeLeft[200];
		int m_TimeLeft=0;	
		double dZalog;
		double tarif;
		struct timeval tv;
		tv.tv_sec = 10;  /* 10 Secs Timeout */
		tv.tv_usec = 0;  // Not init'ing this can cause strange errors
        strcpy(Buffer, "sta1k AS,");

        if (WSAStartup(0x202,&wsaData) == SOCKET_ERROR) 
		{
			sprintf(err,"ZaprosSock: WSAStartup failed with error %d",WSAGetLastError());
			LogWrite(err);
			WSACleanup();
			return FALSE;
        }

        if (isalpha(Computers[Comp].CompName[0])) {   // server address is a name 
                hp = gethostbyname(Computers[Comp].CompName);
        }
        else  { // Convert nnn.nnn address to a usable one 
                addr = inet_addr(Computers[Comp].CompName);
                hp = gethostbyaddr((char *)&addr,4,AF_INET);
        }

        if (hp == NULL ) 
		{
			sprintf(err,"ZaprosSock: Client: Cannot resolve address [%s]: Error %d",
				Computers[Comp].CompName,WSAGetLastError());
			LogWrite(err);
			WSACleanup();
			return FALSE;
        }

        memset(&server,0,sizeof(server));
        memcpy(&(server.sin_addr),hp->h_addr,hp->h_length);
        server.sin_family = hp->h_addrtype;
        server.sin_port = htons(port);

        conn_socket = socket(AF_INET,socket_type,0); /* Open a socket */
        if (conn_socket <0 ) 
		{
			sprintf(err,"ZaprosSock: Client: Error Opening socket: Error %d, comp %d", WSAGetLastError(),Comp);
			LogWrite(err);
			WSACleanup();
			return FALSE;
        }

        if (connect(conn_socket,(struct sockaddr*)&server,sizeof(server)) == SOCKET_ERROR) 
		{
			sprintf(err,"ZaprosSock: connect() failed: %d, comp %d",WSAGetLastError(),Comp);
			LogWrite(err);
			closesocket(conn_socket);
            WSACleanup();
            return FALSE;
        }
        retval = send(conn_socket,Buffer,sizeof(Buffer),0);
        if (retval == SOCKET_ERROR) 
		{
			sprintf(err,"ZaprosSock: send() failed: error %d, comp %d",WSAGetLastError(),Comp);
			LogWrite(err);
			closesocket(conn_socket);
            WSACleanup();
            return FALSE;
        }

//!!!!!!!!
// Прием информации из раб.места
		setsockopt(conn_socket, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,sizeof(struct timeval));
		retval = recv(conn_socket,Buffer,sizeof(Buffer),0);        
        if (retval == SOCKET_ERROR) 
		{
			sprintf(err,"ZaprosSock: recv() failed: error %d, comp %d",WSAGetLastError(),Comp);
			LogWrite(err);
			closesocket(conn_socket);
            WSACleanup();
            return FALSE;
        }
		closesocket(conn_socket);
		char szIn[300];
        strcpy (szIn, Buffer);
          char  Count=0;
      char      Begin=0;
                if (strlen(szIn)<5)
                        return FALSE;
                if (memcmp (szIn, "ser1k", 5)!=0)
                        return FALSE;
                memcpy (szIn, Buffer+5, strlen(szIn)-4);
//                sprintf (LogBuffer, "Proccess with string - %s", szIn);
//                LogWrite (LogBuffer);
			while (_tcscmp(szIn, "")!=0)
			{
                        while (((Buffer[Count]==' ')||(Buffer[Count]==','))&&(Count<(int)_tcslen(Buffer))) 
                                Count++;
                        Begin=Count;    
                        while ((Buffer[Count]!=' ')&&(Buffer[Count]!=',')&&(Count<(int)_tcslen(Buffer)))  
                                Count++;

                        memcpy (szIn, Buffer+Begin, Count-Begin);
                        szIn[Count-Begin]='\0';

                if ((_tcscmp(szIn, "DG")==0) || (_tcscmp(szIn, "AG")==0))
				{
					while (((Buffer[Count]==' ')||(Buffer[Count]==','))&&(Count<(int)_tcslen(Buffer))) 
                                        Count++;
                                	Begin=Count;    
                                	while ((Buffer[Count]!=' ')&&(Buffer[Count]!=',')&&(Count<(int)_tcslen(Buffer)))  
                                        Count++;
                                	memcpy (TimeLeft, Buffer+Begin, Count-Begin);
                                	TimeLeft[Count-Begin]='\0';
                                	m_TimeLeft = atoi(TimeLeft);
									    Count++;
									memcpy (TimeLeft, Buffer+Count, 1);
                                	TimeLeft[1]='\0';
                                	off = atoi(TimeLeft);

                                	//Sleep (3000);
					//exit(0);
				}
			}
			m_TimeLeft = m_TimeLeft * 60 + 59;
			if(thr77 == 0)
			{
					if (Computers[Comp].Time < (m_TimeLeft - 119))
					{
						if(m_TimeLeft < 60) m_TimeLeft = 0;
						Computers[Comp].Time = m_TimeLeft;
						Computers[Comp].Ostatok = Computers[Comp].Time * (Computers[Comp].Tarif  *  nds );
						Computers[Comp].Elapce = (Computers[Comp].Zalog - Computers[Comp].Ostatok)/(Computers[Comp].Tarif *  nds );
						if (Computers[Comp].Elapce < 0) Computers[Comp].Ostatok += (Computers[Comp].Tarif  *  nds ) * Computers[Comp].Elapce;
						int time0 = Computers[Comp].Elapce / 60;
/*						while(time0-- >= 0) if (Computers[Comp].DateTimeBeg.wMinute-- == 0) 
						{
							Computers[Comp].DateTimeBeg.wMinute = 59;
							if (Computers[Comp].DateTimeBeg.wHour-- == 0) 
							{
								Computers[Comp].DateTimeBeg.wHour = 23;
							}
						}
*/
					if(off == 0) UnLockStation(Comp);
					}
					if (Computers[Comp].AllZalog == 0)
					{
						char cStr[100];
						Computers[Comp].Time = m_TimeLeft;
						Computers[Comp].bTarif = false;
						Computers[Comp].sTarif = false;
						Computers[Comp].cTarif = false;
					}
					/*					bConn = EnableExplorer(Comp);
					if (bConn)
					{
						Computers[Comp].Start = true;
						Computers[Comp].Rasch = true;
						Computers[Comp].Connected=true;
					}
*/
//				}
//				else 
//				if(Computers[Comp].Time > 60) Computers[Comp].Time = 0;
				if(off == 1) 
				{
					if (Computers[Comp].Rasch)
					{
						Computers[Comp].Rasch = false;
						LockStation(Comp);
						Beep(1000,100);
						#ifdef _LOG_ITAR
							sprintf (LogBuffer, "На машине № %i пользователем досрочно прерван сеанс", Computers[Comp].NumbComp+1);
							LogWrite (LogBuffer);
						#endif
//						sprintf (TempStr, "На машине № %i пользователем досрочно прерван сеанс", Computers[Comp].NumbComp+1);
//						MessageBox(GetActiveWindow(), TempStr, "Внимание", MB_OK|MB_ICONINFORMATION);
						
					}
				}
				else Computers[Comp].Rasch = true;
			}
			else m_Time = (m_TimeLeft-1)/60; 
        WSACleanup();
/*
		#ifdef _LOG_ITAR
			sprintf (LogBuffer, "Lock Workstation number %d", Comp);
			LogWrite (LogBuffer);
		#endif
*/
        return TRUE;

}


BOOL LockStationSock (int Comp)
{
        unsigned short port = DEFAULT_PORT;
        int retval, loopflag=0;
        unsigned int addr;
        int socket_type = DEFAULT_PROTO;
        struct sockaddr_in server;
        struct hostent *hp;
        WSADATA wsaData;
        SOCKET  conn_socket;
        char Buffer[300];
		char err[200];
        strcpy(Buffer, "sta1k HZ,");

        if (WSAStartup(0x202,&wsaData) == SOCKET_ERROR) 
		{
			sprintf(err,"LockStationSock: WSAStartup failed with error %d, comp %d",WSAGetLastError(),Comp);
			LogWrite(err);
			WSACleanup();
			return false;
        }

        if (isalpha(Computers[Comp].CompName[0])) {   /* server address is a name */
                hp = gethostbyname(Computers[Comp].CompName);
        }
        else  { /* Convert nnn.nnn address to a usable one */
                addr = inet_addr(Computers[Comp].CompName);
                hp = gethostbyaddr((char *)&addr,4,AF_INET);
        }

        if (hp == NULL ) 
		{
			sprintf(err,"LockStationSock: Client: Cannot resolve address [%s]: Error %d",
				Computers[Comp].CompName,WSAGetLastError());
			LogWrite(err);
			WSACleanup();
			return false;
        }

        memset(&server,0,sizeof(server));
        memcpy(&(server.sin_addr),hp->h_addr,hp->h_length);
        server.sin_family = hp->h_addrtype;
        server.sin_port = htons(port);

        conn_socket = socket(AF_INET,socket_type,0); /* Open a socket */
        if (conn_socket <0 ) 
		{
			sprintf(err,"LockStationSock: Client: Error Opening socket: Error %d, comp %d",WSAGetLastError(),Comp);
			LogWrite(err);
			WSACleanup();
			return false;
        }

        if (connect(conn_socket,(struct sockaddr*)&server,sizeof(server)) == SOCKET_ERROR) 
		{
			sprintf(err,"LockStationSock: connect() failed: %d, comp %d",WSAGetLastError(),Comp);
			LogWrite(err);
			closesocket(conn_socket);
            WSACleanup();
			if (WSAGetLastError() == 10061) return true;
            return false;
        }
        if (Computers[Comp].TPos!=1){
			strcat(Buffer, "DG,");
		}	   
        strcat  (Buffer, m_Setup.Lock);
        retval = send(conn_socket,Buffer,sizeof(Buffer),0);
        if (retval == SOCKET_ERROR) 
		{
			sprintf(err,"LockStationSock: send() failed: error %d, comp %d",WSAGetLastError(),Comp);
			LogWrite(err);
			closesocket(conn_socket);
            WSACleanup();
            return false;
        }

/*
//==========================
// Прием информации из раб.места
		retval = recv(conn_socket,Buffer,sizeof(Buffer),0);        
        if (retval == SOCKET_ERROR) 
		{
			sprintf(err,"Lock Workstation: recv() failed: error %d",WSAGetLastError());
			LogWrite(err);
			closesocket(conn_socket);
            WSACleanup();
            return FALSE;
        }

//===========================
*/


		closesocket(conn_socket);
        WSACleanup();
		#ifdef _LOG_ITAR
			sprintf (LogBuffer, "Lock Workstation number %d", Comp);
			LogWrite (LogBuffer);
		#endif
        return true;
}


BOOL UnLockStationSock (int Comp)
{
        unsigned short port = DEFAULT_PORT;
        int retval, loopflag=0;
        unsigned int addr;
        int socket_type = DEFAULT_PROTO;
        struct sockaddr_in server;
        struct hostent *hp;
        WSADATA wsaData;
        SOCKET  conn_socket;
        char Buffer[300];
        strcpy(Buffer, "sta1k SZ ");
        strcat(Buffer, TarifName[Computers[Comp].TPos]);
		char tar[100];
		sprintf(tar, " (тариф: %.5f)", Computers[Comp].Tarif);
		strcat(Buffer, tar);
        strcat(Buffer, "-");
        int tTime = int ((Computers[Comp].Time-1)/60);
        char cTime [100];
        sprintf (cTime, "%d", tTime);
        strcat (Buffer, cTime);
        strcat (Buffer, ",");
		char err[100];

        if (WSAStartup(0x202,&wsaData) == SOCKET_ERROR) 
		{
			sprintf(err,"UnLockStationSock: WSAStartup failed with error %d, comp %d",WSAGetLastError(),Comp);
			LogWrite(err);
            WSACleanup();
            return false;
        }

        if (isalpha(Computers[Comp].CompName[0])) {   /* server address is a name */
                hp = gethostbyname(Computers[Comp].CompName);
        }
        else  { /* Convert nnn.nnn address to a usable one */
                addr = inet_addr(Computers[Comp].CompName);
                hp = gethostbyaddr((char *)&addr,4,AF_INET);
        }

        if (hp == NULL ) 
		{
			sprintf(err,"UnLockStationSock: Client: Cannot resolve address [%s]: Error %d",
			Computers[Comp].CompName,WSAGetLastError());
			LogWrite(err);
            WSACleanup();
            return false;
        }

        memset(&server,0,sizeof(server));
        memcpy(&(server.sin_addr),hp->h_addr,hp->h_length);
        server.sin_family = hp->h_addrtype;
        server.sin_port = htons(port);

        conn_socket = socket(AF_INET,socket_type,0); /* Open a socket */
        if (conn_socket <0 ) 
		{
			sprintf(err,"UnLockStationSock: Client: Error Opening socket: Error %d, comp %d",WSAGetLastError(),Comp);
			LogWrite(err);
            WSACleanup();
            return false;
        }

        if (connect(conn_socket,(struct sockaddr*)&server,sizeof(server))
                == SOCKET_ERROR) 
		{
			sprintf(err,"UnLockStationSock: connect() failed: %d, comp %d",WSAGetLastError(),Comp);
			LogWrite(err);
			closesocket(conn_socket);
            WSACleanup();
            return false;
        }
        if ((Computers[Comp].TPos!=1)&&(Computers[Comp].TPos!=3))
		{
			strcat(Buffer, "AG ");
			strcat(Buffer, m_Setup.GateWayName);
			strcat(Buffer, ",");
		}   
        strcat  (Buffer, m_Setup.UnLock);
        retval = send(conn_socket,Buffer,sizeof(Buffer),0);
        if (retval == SOCKET_ERROR) 
		{
			sprintf(err,"UnLockStationSock: send() failed: error %d, comp %d",WSAGetLastError(),Comp);
			LogWrite(err);
			closesocket(conn_socket);
			WSACleanup();
            return false;
        }
/*
//==========================
// Прием информации из раб.места
		retval = recv(conn_socket,Buffer,sizeof(Buffer),0);        
        if (retval == SOCKET_ERROR) 
		{
			sprintf(err,"ZaprosSock: recv() failed: error %d",WSAGetLastError());
			LogWrite(err);
			closesocket(conn_socket);
            WSACleanup();
            return FALSE;
        }

//===========================
*/
		closesocket(conn_socket);
		m_Time = tTime;
        WSACleanup();
		sprintf (LogBuffer, "UnLockStationSock: UnLock Workstation number %d", Comp);
		LogWrite (LogBuffer);
        return true;
}
// Fedorov
BOOL ShutdownStationSock (int Comp)
{
	unsigned short port = DEFAULT_PORT;
	int retval, loopflag=0;
	unsigned int addr;
	int socket_type = DEFAULT_PROTO;
	struct sockaddr_in server;
	struct hostent *hp;
	WSADATA wsaData;
	SOCKET  conn_socket;
	char Buffer[300];
	strcpy(Buffer, "sta1k SZ ");
	//
	char err[200];
	//
	if (WSAStartup(0x202,&wsaData) == SOCKET_ERROR) 
	{
		sprintf(err,"ShutdownStationSock: WSAStartup failed with error %d",WSAGetLastError());
		LogWrite(err);
		WSACleanup();
		return false;
	}
	if (isalpha(Computers[Comp].CompName[0])) 
	{   
		// server address is a name
		hp = gethostbyname(Computers[Comp].CompName);
	}
	else  
	{ 
		// Convert nnn.nnn address to a usable one
		addr = inet_addr(Computers[Comp].CompName);
		hp = gethostbyaddr((char *)&addr,4,AF_INET);
	}
	if (hp == NULL ) 
	{
		sprintf(err,"ShutdownStationSock: Client: Cannot resolve address [%s]: Error %d",
			Computers[Comp].CompName,WSAGetLastError());
		LogWrite(err);
		WSACleanup();
		return false;
	}
	//
	memset(&server,0,sizeof(server));
	memcpy(&(server.sin_addr),hp->h_addr,hp->h_length);
	server.sin_family = hp->h_addrtype;
	server.sin_port = htons(port);
	//
	conn_socket = socket(AF_INET,socket_type,0); 
	// Open a socket 
	if (conn_socket <0 ) 
	{
		sprintf(err,"ShutdownStationSock: Client: Error Opening socket: Error %d, comp %d", WSAGetLastError(),Comp);
		LogWrite(err);
		WSACleanup();
		return false;
	}
	//
	if (connect(conn_socket,(struct sockaddr*)&server,sizeof(server)) == SOCKET_ERROR) 
	{
		sprintf(err,"ShutdownStationSock: connect() failed: %d, comp %d",WSAGetLastError(),Comp);
		LogWrite(err);
		closesocket(conn_socket);
		WSACleanup();
		return false;
	}
	//
	int tTime = int ((Computers[Comp].Time-1)/60);
	char tar[300];
	sprintf(tar, "%s (тариф: %.5f)-%d,", TarifName[Computers[Comp].TPos], Computers[Comp].Tarif, tTime);
	strncat(Buffer, tar, strlen(tar));
	//
	strcat(Buffer, "AG ");
	strcat(Buffer, m_Setup.GateWayName);
	strcat(Buffer, ",");
	strcat  (Buffer, "PO");
	//
	retval = send(conn_socket,Buffer,sizeof(Buffer),0);
	if (retval == SOCKET_ERROR) 
	{
		sprintf(err,"ShutdownStationSock: send() failed: error %d, comp %d",WSAGetLastError(),Comp);
		LogWrite(err);
		closesocket(conn_socket);
		WSACleanup();
		return false;
	}
	closesocket(conn_socket);
	WSACleanup();
	#ifdef _LOG_ITAR
		sprintf (LogBuffer, "ShutdownStationSock: Shutdown Workstation # %i", Comp);
		LogWrite (LogBuffer);
	#endif
	//
	return true;
}
BOOL ResetStationSock (int Comp)
{
        unsigned short port = DEFAULT_PORT;
        int retval, loopflag=0;
        unsigned int addr;
        int socket_type = DEFAULT_PROTO;
        struct sockaddr_in server;
        struct hostent *hp;
        WSADATA wsaData;
        SOCKET  conn_socket;
        char Buffer[300];
        strcpy(Buffer, "sta1k SZ ");
        strcat(Buffer, TarifName[Computers[Comp].TPos]);
		char tar[100];
		sprintf(tar, " (тариф: %.5f)", Computers[Comp].Tarif);
		strcat(Buffer, tar);
        strcat(Buffer, "-");
        int tTime = int ((Computers[Comp].Time-1)/60);
        char cTime [100];
        sprintf (cTime, "%d", tTime);
        strcat (Buffer, cTime);
        strcat (Buffer, ",");
		char err[200];


        if (WSAStartup(0x202,&wsaData) == SOCKET_ERROR) 
		{
			sprintf(err,"ResetStationSock: WSAStartup failed with error %d",WSAGetLastError());
			LogWrite(err);
            WSACleanup();
            return false;
        }

        if (isalpha(Computers[Comp].CompName[0])) {   /* server address is a name */
                hp = gethostbyname(Computers[Comp].CompName);
        }
        else  { /* Convert nnn.nnn address to a usable one */
                addr = inet_addr(Computers[Comp].CompName);
                hp = gethostbyaddr((char *)&addr,4,AF_INET);
        }

        if (hp == NULL ) 
		{
			sprintf(err,"ResetStationSock: Client: Cannot resolve address [%s]: Error %d",
				Computers[Comp].CompName,WSAGetLastError());
			LogWrite(err);
            WSACleanup();
            return false;
        }

        memset(&server,0,sizeof(server));
        memcpy(&(server.sin_addr),hp->h_addr,hp->h_length);
        server.sin_family = hp->h_addrtype;
        server.sin_port = htons(port);

        conn_socket = socket(AF_INET,socket_type,0); /* Open a socket */
        if (conn_socket <0 ) 
		{
			sprintf(err,"ResetStationSock: Client: Error Opening socket: Error %d",
				WSAGetLastError());
			LogWrite(err);
            WSACleanup();
            return false;
        }

        if (connect(conn_socket,(struct sockaddr*)&server,sizeof(server)) == SOCKET_ERROR) 
		{
			sprintf(err,"ResetStationSock: connect() failed: %d, comp %d",WSAGetLastError(),Comp);
			LogWrite(err);
			closesocket(conn_socket);
            WSACleanup();
            return false;
        }
        strcat(Buffer, "AG ");
		strcat(Buffer, m_Setup.GateWayName);
		strcat(Buffer, ",");
        strcat  (Buffer, "RS");
        retval = send(conn_socket,Buffer,sizeof(Buffer),0);
        if (retval == SOCKET_ERROR) 
		{
			sprintf(err,"ResetStationSock: send() failed: error %d, comp %d",WSAGetLastError(),Comp);
			LogWrite(err);
			closesocket(conn_socket);
            WSACleanup();
            return false;
        }

        closesocket(conn_socket);
        WSACleanup();
		#ifdef _LOG_ITAR
			sprintf (LogBuffer, "Reset Workstation number %d", Comp);
			LogWrite (LogBuffer);
		#endif
        return true;
}

BOOL StopInetStationSock (int Comp)
{
        unsigned short port = DEFAULT_PORT;
        int retval, loopflag=0;
        unsigned int addr;
        int socket_type = DEFAULT_PROTO;
        struct sockaddr_in server;
        struct hostent *hp;
        WSADATA wsaData;
        SOCKET  conn_socket;
        char Buffer[300];
        strcpy(Buffer, "sta1k DG");
        char err[200];


        if (WSAStartup(0x202,&wsaData) == SOCKET_ERROR) 
		{
			sprintf(err,"StopInetStationSock: WSAStartup failed with error %d",WSAGetLastError());
			LogWrite(err);
            WSACleanup();
            return false;
        }

        if (isalpha(Computers[Comp].CompName[0])) {   /* server address is a name */
                hp = gethostbyname(Computers[Comp].CompName);
        }
        else  { /* Convert nnn.nnn address to a usable one */
                addr = inet_addr(Computers[Comp].CompName);
                hp = gethostbyaddr((char *)&addr,4,AF_INET);
        }

        if (hp == NULL ) 
		{
			sprintf(err,"StopInetStationSock: Client: Cannot resolve address [%s]: Error %d",
				Computers[Comp].CompName,WSAGetLastError());
			LogWrite(err);
            WSACleanup();
            return false;
        }

        memset(&server,0,sizeof(server));
        memcpy(&(server.sin_addr),hp->h_addr,hp->h_length);
        server.sin_family = hp->h_addrtype;
        server.sin_port = htons(port);

        conn_socket = socket(AF_INET,socket_type,0); /* Open a socket */
        if (conn_socket <0 ) 
		{
			sprintf(err,"StopInetStationSock: Client: Error Opening socket: Error %d",
				WSAGetLastError());
			LogWrite(err);
            WSACleanup();
            return false;
        }

        if (connect(conn_socket,(struct sockaddr*)&server,sizeof(server)) == SOCKET_ERROR) 
		{
			sprintf(err,"StopInetStationSock: connect() failed: %d, comp %d",WSAGetLastError(),Comp);
			LogWrite(err);
			closesocket(conn_socket);
            WSACleanup();
            return false;
        }
        retval = send(conn_socket,Buffer,sizeof(Buffer),0);
        if (retval == SOCKET_ERROR) 
		{
			sprintf(err,"StopInetStationSock: send() failed: error %d, comp %d",WSAGetLastError(),Comp);
			LogWrite(err);
			closesocket(conn_socket);
            WSACleanup();
            return false;
        }

        closesocket(conn_socket);
        WSACleanup();
		#ifdef _LOG_ITAR
			sprintf (LogBuffer, "Stop Inet Workstation number %d", Comp);
			LogWrite (LogBuffer);
		#endif
        return true;
}
BOOL StopStationSock (int Comp)
{
        unsigned short port = DEFAULT_PORT;
        int retval, loopflag=0;
        unsigned int addr;
        int socket_type = DEFAULT_PROTO;
        struct sockaddr_in server;
        struct hostent *hp;
        WSADATA wsaData;
        SOCKET  conn_socket;
        char Buffer[300];
        strcpy(Buffer, "sta1k EX");
        char err[200];

        if (WSAStartup(0x202,&wsaData) == SOCKET_ERROR) 
		{
			sprintf(err,"StopStationSock: WSAStartup failed with error %d",WSAGetLastError());
			LogWrite(err);
            WSACleanup();
            return false;
        }

        if (isalpha(Computers[Comp].CompName[0])) {   /* server address is a name */
                hp = gethostbyname(Computers[Comp].CompName);
        }
        else  { /* Convert nnn.nnn address to a usable one */
                addr = inet_addr(Computers[Comp].CompName);
                hp = gethostbyaddr((char *)&addr,4,AF_INET);
        }

        if (hp == NULL ) 
		{
			sprintf(err,"StopStationSock: Client: Cannot resolve address [%s]: Error %d",
				Computers[Comp].CompName,WSAGetLastError());
			LogWrite(err);
            WSACleanup();
            return false;
        }

        memset(&server,0,sizeof(server));
        memcpy(&(server.sin_addr),hp->h_addr,hp->h_length);
        server.sin_family = hp->h_addrtype;
        server.sin_port = htons(port);

        conn_socket = socket(AF_INET,socket_type,0); /* Open a socket */
        if (conn_socket <0 ) 
		{
			sprintf(err,"StopStationSock: Client: Error Opening socket: Error %d",
				WSAGetLastError());
			LogWrite(err);
            WSACleanup();
            return false;
        }

        if (connect(conn_socket,(struct sockaddr*)&server,sizeof(server)) == SOCKET_ERROR) 
		{
			sprintf(err,"StopStationSock: connect() failed: %d, comp %d",WSAGetLastError(),Comp);
			LogWrite(err);
			closesocket(conn_socket);
            WSACleanup();
            return false;
        }
        retval = send(conn_socket,Buffer,sizeof(Buffer),0);
        if (retval == SOCKET_ERROR) 
		{
			sprintf(err,"StopStationSock: send() failed: error %d, comp %d",WSAGetLastError(),Comp);
			LogWrite(err);
			closesocket(conn_socket);
            WSACleanup();
            return false;
        }

        closesocket(conn_socket);
        WSACleanup();
		#ifdef _LOG_ITAR
			sprintf (LogBuffer, "Stop Workstation number %d", Comp);
			LogWrite (LogBuffer);
		#endif
        return true;
}

BOOL StartInetStationSock (int Comp)
{
        unsigned short port = DEFAULT_PORT;
        int retval, loopflag=0;
        unsigned int addr;
        int socket_type = DEFAULT_PROTO;
        struct sockaddr_in server;
        struct hostent *hp;
        WSADATA wsaData;
        SOCKET  conn_socket;
        char Buffer[300];
        strcpy(Buffer, "sta1k ");
        char err[200];

        if (WSAStartup(0x202,&wsaData) == SOCKET_ERROR) 
		{
			sprintf(err,"StartInetStationSock: WSAStartup failed with error %d",WSAGetLastError());
			LogWrite(err);
            WSACleanup();
            return false;
        }

        if (isalpha(Computers[Comp].CompName[0])) {   /* server address is a name */
                hp = gethostbyname(Computers[Comp].CompName);
        }
        else  { /* Convert nnn.nnn address to a usable one */
                addr = inet_addr(Computers[Comp].CompName);
                hp = gethostbyaddr((char *)&addr,4,AF_INET);
        }

        if (hp == NULL ) 
		{
			sprintf(err,"StartInetStationSock: Client: Cannot resolve address [%s]: Error %d",
				Computers[Comp].CompName,WSAGetLastError());
			LogWrite(err);
            WSACleanup();
            return false;
        }

        memset(&server,0,sizeof(server));
        memcpy(&(server.sin_addr),hp->h_addr,hp->h_length);
        server.sin_family = hp->h_addrtype;
        server.sin_port = htons(port);

        conn_socket = socket(AF_INET,socket_type,0); /* Open a socket */
        if (conn_socket <0 ) 
		{
			sprintf(err,"StartInetStationSock: Client: Error Opening socket: Error %d",
				WSAGetLastError());
			LogWrite(err);
            WSACleanup();
            return false;
        }

        if (connect(conn_socket,(struct sockaddr*)&server,sizeof(server)) == SOCKET_ERROR) 
		{
			sprintf(err,"StartInetStationSock: connect() failed: %d, comp %d",WSAGetLastError(),Comp);
			LogWrite(err);
			closesocket(conn_socket);
            WSACleanup();
            return false;
        }
        strcat(Buffer, "AG ");
		strcat(Buffer, m_Setup.GateWayName);
		retval = send(conn_socket,Buffer,sizeof(Buffer),0);
        if (retval == SOCKET_ERROR) 
		{
			sprintf(err,"StartInetStationSock: send() failed: error %d, comp %d",WSAGetLastError(),Comp);
			LogWrite(err);
			closesocket(conn_socket);
            WSACleanup();
            return false;
        }

        closesocket(conn_socket);
        WSACleanup();
		#ifdef _LOG_ITAR
			sprintf (LogBuffer, "Start Inet number %d", Comp);
			LogWrite (LogBuffer);
		#endif
        return true;
}

/////////////////////////////////////////////////////////////////////////////
BOOL DisableExplorerSock (int Comp)
{
        unsigned short port = DEFAULT_PORT;
        int retval, loopflag=0;
        unsigned int addr;
        int socket_type = DEFAULT_PROTO;
        struct sockaddr_in server;
        struct hostent *hp;
        WSADATA wsaData;
        SOCKET  conn_socket;
        char Buffer[300];       
        strcpy(Buffer, "sta1k HZ,");


        if (WSAStartup(0x202,&wsaData) == SOCKET_ERROR) 
		{
			sprintf (LogBuffer,"DisableExplorerSock: WSAStartup failed with error %d\n",WSAGetLastError());
			LogWrite (LogBuffer);
            WSACleanup();
            return false;
        }

        if (isalpha(Computers[Comp].CompName[0])) {   /* server address is a name */
                hp = gethostbyname(Computers[Comp].CompName);
        }
        else  { /* Convert nnn.nnn address to a usable one */
                addr = inet_addr(Computers[Comp].CompName);
                hp = gethostbyaddr((char *)&addr,4,AF_INET);
        }

        if (hp == NULL ) 
		{
			sprintf (LogBuffer,"DisableExplorerSock: Client: Cannot resolve address [%s]: Error %d\n",
				Computers[Comp].CompName,WSAGetLastError());
			LogWrite (LogBuffer);
            WSACleanup();
            return false;
        }

        memset(&server,0,sizeof(server));
        memcpy(&(server.sin_addr),hp->h_addr,hp->h_length);
        server.sin_family = hp->h_addrtype;
        server.sin_port = htons(port);

        conn_socket = socket(AF_INET,socket_type,0); /* Open a socket */
        if (conn_socket <0 ) 
		{
			sprintf (LogBuffer,"DisableExplorerSock: Client: Error Opening socket: Error %d\n",
				WSAGetLastError());
			LogWrite (LogBuffer);
            WSACleanup();
            return false;
        }

        if (connect(conn_socket,(struct sockaddr*)&server,sizeof(server)) == SOCKET_ERROR) 
		{
			sprintf (LogBuffer,"DisableExplorerSock: connect() failed: %d\n",WSAGetLastError());
			LogWrite (LogBuffer);
			closesocket(conn_socket);
            WSACleanup();
            return false;
        }
		//
        if (m_Setup.CloseExplorer)
        {
                strcat  (Buffer, "ED");
                retval = send(conn_socket,Buffer,sizeof(Buffer),0);
                if (retval == SOCKET_ERROR) 
				{
					sprintf (LogBuffer,"DisableExplorerSock: send() failed: error %d\n",WSAGetLastError());
					LogWrite (LogBuffer);
					closesocket(conn_socket);
                    WSACleanup();
                    return false;
                }
				if (!m_Setup.BlockInet){
					closesocket(conn_socket);
					WSACleanup();
				}
				#ifdef _LOG_ITAR
					sprintf (LogBuffer, "Disable Explorer in station number %d", Comp);
					LogWrite (LogBuffer);
				#endif
        }

        if (m_Setup.BlockInet)
        {
			strcat  (Buffer, "DG");
			retval = send(conn_socket,Buffer,sizeof(Buffer),0);
			if (retval == SOCKET_ERROR) 
			{
				fprintf(stderr,"DisableExplorerSock: send() failed: error %d\n",WSAGetLastError());
				closesocket(conn_socket);
				WSACleanup();
				return false;
			}
			closesocket(conn_socket);
			WSACleanup();
			#ifdef _LOG_ITAR
				sprintf (LogBuffer, "Block internet in station number %d", Comp);
				LogWrite (LogBuffer);
			#endif
		}
        closesocket(conn_socket);
        WSACleanup();
        return true;
}



BOOL EnableExplorerSock (int Comp)
{
        unsigned short port = DEFAULT_PORT;
        int retval, loopflag=0;
        unsigned int addr;
        int socket_type = DEFAULT_PROTO;
        struct sockaddr_in server;
        struct hostent *hp;
        WSADATA wsaData;
        SOCKET  conn_socket;
        char Buffer[300];
        strcpy(Buffer, "sta1k ");


	if (WSAStartup(0x202,&wsaData) == SOCKET_ERROR) 
	{
		sprintf (LogBuffer,"EnableExplorerSock: WSAStartup failed with error %d\n",WSAGetLastError());
		LogWrite (LogBuffer);
		WSACleanup();
		return false;
	}
	if (isalpha(Computers[Comp].CompName[0])) 
	{   /* server address is a name */
		hp = gethostbyname(Computers[Comp].CompName);
	}
	else  
	{ /* Convert nnn.nnn address to a usable one */
		addr = inet_addr(Computers[Comp].CompName);
		hp = gethostbyaddr((char *)&addr,4,AF_INET);
	}
	if (hp == NULL ) 
	{
		sprintf (LogBuffer,"EnableExplorerSock: Client: Cannot resolve address [%s]: Error %d\n",
			Computers[Comp].CompName,WSAGetLastError());
		LogWrite (LogBuffer);
		WSACleanup();
		return false;
	}
	memset(&server,0,sizeof(server));
	memcpy(&(server.sin_addr),hp->h_addr,hp->h_length);
	server.sin_family = hp->h_addrtype;
	server.sin_port = htons(port);
	//
	conn_socket = socket(AF_INET,socket_type,0); /* Open a socket */
	if (conn_socket <0 ) 
	{
		sprintf (LogBuffer,"EnableExplorerSock: Client: Error Opening socket: Error %d\n", WSAGetLastError());
		LogWrite (LogBuffer);
        WSACleanup();
        return false;
	}
	//
	if (connect(conn_socket,(struct sockaddr*)&server,sizeof(server)) == SOCKET_ERROR) 
	{
		sprintf (LogBuffer,"EnableExplorerSock: connect() failed: %d\n",WSAGetLastError());
		LogWrite (LogBuffer);
		closesocket(conn_socket);
        WSACleanup();
        return false;
	}
	//
	if (m_Setup.CloseExplorer)
	{
		strcat  (Buffer, "EE");
		retval = send(conn_socket,Buffer,sizeof(Buffer),0);
		if (retval == SOCKET_ERROR) 
		{
			sprintf (LogBuffer,"EnableExplorerSock: send() failed: error %d\n",WSAGetLastError());
			LogWrite (LogBuffer);
			closesocket(conn_socket);
			WSACleanup();
			return false;
		}
		if (!m_Setup.BlockInet)
		{
			closesocket(conn_socket);
			WSACleanup();
		}
		#ifdef _LOG_ITAR
			sprintf (LogBuffer, "EnableExplorerSock: Enable Explorer in station number %d", Comp);
			LogWrite (LogBuffer);
		#endif
	}
	//
	if (m_Setup.BlockInet)
	{
		char Name[200];
		sprintf (Name, "AG %s", m_Setup.GateWayName);
		strcat  (Buffer, Name);
        retval = send(conn_socket,Buffer,sizeof(Buffer),0);
		if (retval == SOCKET_ERROR) 
		{
			sprintf (LogBuffer,"EnableExplorerSock: send() failed: error %d\n",WSAGetLastError());
			LogWrite (LogBuffer);
			closesocket(conn_socket);
			WSACleanup();
			return false;
		}
		closesocket(conn_socket);
		WSACleanup();
		#ifdef _LOG_ITAR
			sprintf (LogBuffer, "EnableExplorerSock: Start internet in station number %d", Comp);
			LogWrite (LogBuffer);
		#endif
	}
	closesocket(conn_socket);
	WSACleanup();
	return true;
}

/////////////////////////////////////////////////////////////////////////////
BOOL LockStationPipe (int Comp)
{
    LPSTR   lpszPipeName = "\\\\%s\\pipe\\%s";
    char    PipeName[200];
    char    inbuf[300];
    char    outbuf[300];
    strcpy (outbuf, "sta1k HZ,");
    DWORD   bytesRead;
    BOOL    ret;
	//
	sprintf (PipeName, lpszPipeName, Computers[Comp].CompName, "friglays");
	if (Computers[Comp].TPos!=1)
	{
		strcat(outbuf, "DG,");
	}
	strcat  (outbuf, m_Setup.Lock);
	//
	ret = CallNamedPipeA(PipeName,
                         outbuf, sizeof(outbuf),
                         inbuf, sizeof(inbuf),
                         &bytesRead, NMPWAIT_WAIT_FOREVER);
	//
	#ifdef _LOG_ITAR
		char LogBuffer[200];
		sprintf (LogBuffer, "LockStationPipe: Lock Workstation number %d", Comp);
		LogWrite (LogBuffer);
	#endif
	return ret;
}


BOOL UnLockStationPipe (int Comp)
{
    LPSTR   lpszPipeName = "\\\\%s\\pipe\\%s";
    char    PipeName[200];
    char    inbuf[300];
    char outbuf[300];
    DWORD   bytesRead;
    BOOL    ret;

    strcpy(outbuf, "sta1k SZ ");
    strcat(outbuf, TarifName[Computers[Comp].TPos]);
    strcat(outbuf, "-");
    int tTime = int ((Computers[Comp].Time-1)/60);
    char cTime [100];
    sprintf (cTime, "%d", tTime);
    strcat (outbuf, cTime);
    strcat (outbuf, ",");
        
    sprintf (PipeName, lpszPipeName, Computers[Comp].CompName, "friglays");
	if (Computers[Comp].TPos!=1){
		strcat(outbuf, "AG ");
		strcat(outbuf, m_Setup.GateWayName);
		strcat(outbuf, ",");
	}
    strcat  (outbuf, m_Setup.UnLock);

    ret = CallNamedPipeA(PipeName,
                         outbuf, sizeof(outbuf),
                         inbuf, sizeof(inbuf),
                         &bytesRead, NMPWAIT_WAIT_FOREVER);
	#ifdef _LOG_ITAR
        char LogBuffer[200];
		sprintf (LogBuffer, "UnLockStationPipe: UnLock Workstation number %d", Comp);
        LogWrite (LogBuffer);
	#endif
	return ret;
}
//Fedorov
BOOL ShutdownStationPipe (int Comp)
{
    LPSTR   lpszPipeName = "\\\\%s\\pipe\\%s";
    char    PipeName[200];
    char    inbuf[300];
    char    outbuf[300];
    DWORD   bytesRead;
    BOOL    ret;
	//
    strcpy(outbuf, "sta1k SZ ");
	//
	int tTime = int ((Computers[Comp].Time-1)/60);
	char tar[300];
	sprintf(tar, "%s (тариф: %.5f)-%d,", TarifName[Computers[Comp].TPos], Computers[Comp].Tarif, tTime);
	strncat(outbuf, tar, strlen(tar));
	//
	sprintf (PipeName, lpszPipeName, Computers[Comp].CompName, "friglays");
	strcat(outbuf, "AG ");
	strcat(outbuf, m_Setup.GateWayName);
	strcat(outbuf, ",");
	strcat  (outbuf, "PO");
	//
	ret = CallNamedPipeA(PipeName,
		outbuf, sizeof(outbuf),
		inbuf, sizeof(inbuf),
		&bytesRead, NMPWAIT_WAIT_FOREVER);
	//
	#ifdef _LOG_ITAR
		char LogBuffer[200];
		sprintf (LogBuffer, "ShutdownStationPipe: Shutdown Workstation # %i", Comp);
		LogWrite (LogBuffer);
	#endif
	return ret;
}
BOOL ResetStationPipe (int Comp)
{
    LPSTR   lpszPipeName = "\\\\%s\\pipe\\%s";
    char    PipeName[200];
    char    inbuf[300];
    char outbuf[300];
    DWORD   bytesRead;
    BOOL    ret;

    strcpy(outbuf, "sta1k SZ ");
    strcat(outbuf, TarifName[Computers[Comp].TPos]);
    strcat(outbuf, "-");
    int tTime = int ((Computers[Comp].Time-1)/60);
    char cTime [100];
    sprintf (cTime, "%d", tTime);
    strcat (outbuf, cTime);
    strcat (outbuf, ",");
        
    sprintf (PipeName, lpszPipeName, Computers[Comp].CompName, "friglays");
	strcat(outbuf, "AG ");
	strcat(outbuf, m_Setup.GateWayName);
	strcat(outbuf, ",");
    strcat  (outbuf, "RS");

    ret = CallNamedPipeA(PipeName,
                         outbuf, sizeof(outbuf),
                         inbuf, sizeof(inbuf),
                         &bytesRead, NMPWAIT_WAIT_FOREVER);
	#ifdef _LOG_ITAR
		char LogBuffer[200];
		sprintf (LogBuffer, "ResetStationPipe: Reset Workstation number %d", Comp);
        LogWrite (LogBuffer);
	#endif
	return ret;
}
BOOL StartInetStationPipe (int Comp)
{
    LPSTR   lpszPipeName = "\\\\%s\\pipe\\%s";
    char    PipeName[200];
    char    inbuf[300];
    char outbuf[300];
    DWORD   bytesRead;
    BOOL    ret;

    strcpy(outbuf, "sta1k ");
    sprintf (PipeName, lpszPipeName, Computers[Comp].CompName, "friglays");
	strcat(outbuf, "AG ");
	strcat(outbuf, m_Setup.GateWayName);

    ret = CallNamedPipeA(PipeName,
                         outbuf, sizeof(outbuf),
                         inbuf, sizeof(inbuf),
                         &bytesRead, NMPWAIT_WAIT_FOREVER);
	#ifdef _LOG_ITAR
		char LogBuffer[200];
		sprintf (LogBuffer, "StartInetStationPipe: Start Inet Workstation number %d", Comp);
		LogWrite (LogBuffer);
	#endif
	return ret;
}
BOOL StopInetStationPipe (int Comp)
{
    LPSTR   lpszPipeName = "\\\\%s\\pipe\\%s";
    char    PipeName[200];
    char    inbuf[300];
    char outbuf[300];
    DWORD   bytesRead;
    BOOL    ret;

    strcpy(outbuf, "sta1k DG ");
    sprintf (PipeName, lpszPipeName, Computers[Comp].CompName, "friglays");
	
    ret = CallNamedPipeA(PipeName,
                         outbuf, sizeof(outbuf),
                         inbuf, sizeof(inbuf),
                         &bytesRead, NMPWAIT_WAIT_FOREVER);
	#ifdef _LOG_ITAR
		char LogBuffer[200];
		sprintf (LogBuffer, "StopInetStationPipe: Stop Inet Workstation number %d", Comp);
		LogWrite (LogBuffer);
	#endif
	return ret;
}
BOOL StopStationPipe (int Comp)
{
    LPSTR   lpszPipeName = "\\\\%s\\pipe\\%s";
    char    PipeName[200];
    char    inbuf[300];
    char outbuf[300];
    DWORD   bytesRead;
    BOOL    ret;

    strcpy(outbuf, "sta1k SZ ");
    strcat(outbuf, TarifName[Computers[Comp].TPos]);
    strcat(outbuf, "-");
    int tTime = int ((Computers[Comp].Time-1)/60);
    char cTime [100];
    sprintf (cTime, "%d", tTime);
    strcat (outbuf, cTime);
    strcat (outbuf, ",");
        
    sprintf (PipeName, lpszPipeName, Computers[Comp].CompName, "friglays");
	strcat(outbuf, "AG ");
	strcat(outbuf, m_Setup.GateWayName);
	strcat(outbuf, ",");
    strcat  (outbuf, "EX");

    ret = CallNamedPipeA(PipeName,
                         outbuf, sizeof(outbuf),
                         inbuf, sizeof(inbuf),
                         &bytesRead, NMPWAIT_WAIT_FOREVER);
	#ifdef _LOG_ITAR
		char LogBuffer[200];
		sprintf (LogBuffer, "StopStationPipe: Stop Workstation number %d", Comp);
		LogWrite (LogBuffer);
	#endif
	return ret;
}
/////////////////////////////////////////////////////////////////////////////
BOOL DisableExplorerPipe (int Comp)
{
    LPSTR   lpszPipeName = "\\\\%s\\pipe\\%s";
        char    PipeName[200];
    char    inbuf[300];
    char    outbuf[300];
        strcpy (outbuf, "sta1k ");
    DWORD   bytesRead;
    BOOL    ret;

        
	if (m_Setup.CloseExplorer)
	{
                sprintf (PipeName, lpszPipeName, Computers[Comp].CompName, "friglays");
                strcat  (outbuf, "ED");

                ret = CallNamedPipeA(PipeName,
                                         outbuf, sizeof(outbuf),
                                             inbuf, sizeof(inbuf),
                                                 &bytesRead, NMPWAIT_WAIT_FOREVER);
		#ifdef _LOG_ITAR
			char LogBuffer[200];
			sprintf (LogBuffer, "DisableExplorerPipe: Disable Explorer in station number %d", Comp);
			LogWrite (LogBuffer);
		#endif
	}
	if (m_Setup.BlockInet)
	{
		char Name[200];
		sprintf (Name, "DG");
		strcat  (outbuf, Name);
		sprintf (PipeName, lpszPipeName, Computers[Comp].CompName);
		ret = CallNamedPipeA(PipeName,
			outbuf, sizeof(outbuf),
			inbuf, sizeof(inbuf),
			&bytesRead, NMPWAIT_WAIT_FOREVER);
		#ifdef _LOG_ITAR
			char LogBuffer[200];
			sprintf (LogBuffer, "DisableExplorerPipe: Block internet in station number %d", Comp);
			LogWrite (LogBuffer);
		#endif
		ret = true;
	}
	return ret;
}
//
BOOL EnableExplorerPipe (int Comp)
{
	LPSTR   lpszPipeName = "\\\\%s\\pipe\\%s";
	char    PipeName[200];
	char    inbuf[300];
	char    outbuf[300];
	strcpy (outbuf, "sta1k ");
	DWORD   bytesRead;
	BOOL    ret;
	//



	if (m_Setup.CloseExplorer)
	{
		sprintf (PipeName, lpszPipeName, Computers[Comp].CompName, "friglays");
		strcat  (outbuf, "EE");
		//
		ret = CallNamedPipeA(PipeName,
			outbuf, sizeof(outbuf),
			inbuf, sizeof(inbuf),
			&bytesRead, NMPWAIT_WAIT_FOREVER);
		#ifdef _LOG_ITAR
			char LogBuffer[200];
			sprintf (LogBuffer, "EnableExplorerPipe: Enable Explorer in station number %d", Comp);
			LogWrite (LogBuffer);
		#endif
	}
	//
	if (m_Setup.BlockInet)
	{
		char cName[200];
		sprintf (cName, "AG %s", m_Setup.GateWayName);
		strncat  (outbuf, cName, strlen(cName));
		//
		sprintf (PipeName, lpszPipeName, Computers[Comp].CompName);
		//
		ret = CallNamedPipeA(PipeName,
			outbuf, sizeof(outbuf),
			inbuf, sizeof(inbuf),
			&bytesRead, NMPWAIT_WAIT_FOREVER);
		#ifdef _LOG_ITAR
			char LogBuffer[200];
			sprintf (LogBuffer, "EnableExplorerPipe: Start internet in station number %d", Comp);
			LogWrite (LogBuffer);
		#endif
		ret = true;
	}
	return ret;
}

/////////////////////////////////////////////////////////////////////////////
BOOL LockStation (int Comp)
{
	if (m_Setup.Pipe)
		return LockStationPipe (Comp);
	else
		return LockStationSock (Comp);
}

BOOL UnLockStation (int Comp)
{
        if (m_Setup.Pipe)
             return UnLockStationPipe (Comp);
        else
             return UnLockStationSock (Comp);
}
//Fedorov
BOOL ShutdownStation (int Comp)
{
	if (m_Setup.Pipe)
		return ShutdownStationPipe (Comp);
	else
		return ShutdownStationSock (Comp);
}
BOOL ResetStation (int Comp)
{
        if (m_Setup.Pipe)
             return ResetStationPipe (Comp);
        else
             return ResetStationSock (Comp);
}
BOOL StartInetStation (int Comp)
{
        if (m_Setup.Pipe)
             return StartInetStationPipe (Comp);
        else
             return StartInetStationSock (Comp);
}
BOOL StopInetStation (int Comp)
{
        if (m_Setup.Pipe)
             return StopInetStationPipe (Comp);
        else
             return StopInetStationSock (Comp);
}

BOOL StopStation (int Comp)
{
        if (m_Setup.Pipe)
             return StopStationPipe (Comp);
        else
             return StopStationSock (Comp);
}

BOOL DisableExplorer(int Comp)
{
        if (m_Setup.Pipe)
             return DisableExplorerPipe (Comp);
        else
             return DisableExplorerSock (Comp);
}

BOOL EnableExplorer (int Comp)
{
	//sprintf (LogBuffer, "Try to enable explorer on Workstation %d", Comp);
	//LogWrite (LogBuffer);

//!!!!!!!!!!!!!!!




	if (m_Setup.Pipe)
		return EnableExplorerPipe (Comp);
	else
		return EnableExplorerSock (Comp);
}
//////////////////////////////////////////////////////////////////////////////////////////////
// End of SysUtils.cpp
/*************************************************************************\
*
*  PROCEDURE: ServerProc (HWND *hWnd)
*
*  PURPOSE:
*
*    A thread procedure, which creates an instance of the server side of
*    the named pipe, and then blocks waiting for a client to connect.
*    Once the client connects, a global array is updated with the specific
*    clients information, and this procedure is called again
*    to launch another waiting server thread.  After launching the new
*    thread, this thread begins to loop, reading the named pipe.  When
*    a message comes from it's client, it uses TellAll() to broadcast
*    the message to the other clients in the array.
*
*  CALLED BY:
*
*    ServerProc();
*    WinMain();
*
*  CALLS TO:
*
*    TellAll();
*    ServerProc().
*
*  COMMENTS:
*
*    Clients is a global array which hold information on each client
*    connected to the named pipe.  This procedure recieves a buffer.
*    It then steps through this global array, and for each client it
*    writes the buffer.
*
\*************************************************************************/
VOID ServerProc(HWND *hWnd)
{
	HANDLE hPipe;                      // Pipe handle.
	CHAR   inBuf[IN_BUF_SIZE] = "";    // Input buffer for pipe.
	DWORD  ServerThreadID;             // Used for CreateThread().
	//
	CHAR   errorBuf[LINE_LEN] = "";    // Used for error messages.
	DWORD  bytesRead;                  // Used in ReadFile().
	DWORD  retCode;                    // Used to trap return codes.
	DWORD  clientIndex;                // Index into global array, for this instances client.
	//
	DWORD  lastError;                   // Traps returns from GetLastError().
	BOOL   ExitLoop = FALSE;            // Boolean Flag to exit loop.
	//
	OVERLAPPED OverLapWrt;              // Overlapped structure for writing.
	HANDLE     hEventWrt;               // Event handle for overlapped write.
	//
	OVERLAPPED OverLapRd;               // Overlapped structure for reading.
	HANDLE     hEventRd;                // Event handle for overlapped reads.
	DWORD        bytesTransRd;          // Bytes transferred by overlapped.
	PSECURITY_DESCRIPTOR    pSD;
	SECURITY_ATTRIBUTES     sa;
	// create a security NULL security
	// descriptor, one that allows anyone
	// to write to the pipe... WARNING
	// entering NULL as the last attribute
	// of the CreateNamedPipe() will
	// indicate that you wish all
	// clients connecting to it to have
	// all of the same security attributes
	// as the user that started the
	// pipe server.
	pSD = (PSECURITY_DESCRIPTOR) LocalAlloc(LPTR, SECURITY_DESCRIPTOR_MIN_LENGTH);
	if (pSD == NULL)
	{
		MessageBox (*hWnd, "Error in LocalAlloc for pSD", "Debug: ServerProc()", MB_OK);
		return;
	}
	if (!InitializeSecurityDescriptor(pSD, SECURITY_DESCRIPTOR_REVISION))
	{
		wsprintf (errorBuf, "Error: InitializeSecurityDescriptor() %d", GetLastError());
		MessageBox (*hWnd, errorBuf, "Debug: ServerProc()", MB_OK);
		LocalFree((HLOCAL)pSD);
		return;
	}
	// add a NULL disc. ACL to the
	// security descriptor.
	if (!SetSecurityDescriptorDacl(pSD, TRUE, (PACL) NULL, FALSE))
	{
		wsprintf (errorBuf, "Error: SetSecurityDescriptorDacl() %d", GetLastError());
		MessageBox (*hWnd, errorBuf, "Debug: ServerProc()", MB_OK);
		LocalFree((HLOCAL)pSD);
		return;
	}
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = pSD;
	sa.bInheritHandle = TRUE;
	// Create a local named pipe with
	// the name '\\.\PIPE\test'.  The
	// '.' signifies local pipe.
	hPipe = CreateNamedPipe ("\\\\.\\PIPE\\inetServer", // Pipe name = 'test'.
		PIPE_ACCESS_DUPLEX                // 2 way pipe.
		| FILE_FLAG_OVERLAPPED,           // Use overlapped structure.
		PIPE_WAIT                         // Wait on messages.
		| PIPE_READMODE_MESSAGE           // Specify message mode pipe.
		| PIPE_TYPE_MESSAGE,
		MAX_PIPE_INSTANCES,               // Maximum instance limit.
		OUT_BUF_SIZE,                     // Buffer sizes.
		IN_BUF_SIZE,
		TIME_OUT,                         // Specify time out.
		&sa);                             // Security attributes.
	// Check Errors.
	if ((DWORD)hPipe == 0xFFFFFFFF)
	{
		retCode = GetLastError();         // Report any error, it should always succeed.
		//LoadString(hInst, IDS_ERRORCODE, lpBuffer, sizeof(lpBuffer));
		//wsprintf (errorBuf, lpBuffer, retCode);
		//LoadString(hInst, IDS_DEBUGTITLE, lpBuffer, sizeof(lpBuffer));
		//MessageBox (*hWnd, errorBuf, lpBuffer,
		//            MB_ICONINFORMATION | MB_OK | MB_APPLMODAL);
	};
	// Block until a client connects.
	ConnectNamedPipe(hPipe, NULL);
	// Create and init overlap for writing.
	hEventWrt = CreateEvent (NULL, TRUE, FALSE, NULL);
	memset (&OverLapWrt, 0, sizeof(OVERLAPPED));
	OverLapWrt.hEvent = hEventWrt;
	// Set the clientIndex, then increment
	// the count.  Fill in the structure
	// for this client in the array.
	clientIndex = clientCount++;
	clients[clientIndex].hPipe   = hPipe;
	clients[clientIndex].live    = TRUE;
	clients[clientIndex].overLap = OverLapWrt;
	clients[clientIndex].hEvent  = hEventWrt;
	// Create and init overlap for reading.
	hEventRd = CreateEvent(NULL,TRUE,FALSE,NULL);
	memset (&OverLapRd, 0, sizeof(OVERLAPPED));
	OverLapRd.hEvent = hEventRd;
	// Read from the client, the first
	// first message should always be
	// the clients user name.
	retCode = ReadFile (hPipe, inBuf, PLEASE_READ, &bytesRead, &OverLapRd);
	if (!retCode)
		lastError = GetLastError();
	if (lastError == ERROR_IO_PENDING)  // Wait on read if need be.
		WaitForSingleObject (hEventRd, (DWORD)-1);
	// Put client's name in the array.
	strcpy (clients[clientIndex].Name, inBuf);
	// Create a thread which will make
	// another server instance of the
	// named pipe.
	CreateThread ((LPSECURITY_ATTRIBUTES)NULL,        // No security attributes.
				(DWORD)0,                           // Use same stack size.
				(LPTHREAD_START_ROUTINE)ServerProc, // Thread procedure.
				(LPVOID)hWnd,                       // Parameter to pass.
				(DWORD)0,                           // Run immediately.
				(LPDWORD)&ServerThreadID);          // Thread identifier.
	TellAll();                        // Forces a paint, draws a red spool and name for this client.
	// Do loop which basically reads from
	// this specific client, and then
	// uses TellAll() to broadcast the
	// message to all the connected
	// clients.
	do
	{
		// Read the pipe.
		_toPipe tm_toPipe;
		retCode = ReadFile (hPipe, &tm_toPipe, sizeof(_toPipe), &bytesRead, &OverLapRd);
		// Check for three kinds of errors:
		// If Error = IO_PENDING, wait til
		// the event handle signals success,
		// If BROKEN_PIPE, exit the do loop.
		// Any other error, flag it to the
		// user and exit the do loop.
		if (!retCode)
		{
			lastError = GetLastError();
			switch (lastError)
			{
				// IO_PENDING, wait on the event.
				case ERROR_IO_PENDING:
					WaitForSingleObject (hEventRd, (DWORD)-1);
					break;
				// Pipe is broken, exit the loop.
				case ERROR_BROKEN_PIPE:
					ExitLoop = TRUE;
					break;
				// Something else is wrong, exit the
				// the loop after telling the user.
				default:
					//LoadString(hInst, IDS_READERROR, lpBuffer, sizeof(lpBuffer));
					//wsprintf (errorBuf, lpBuffer, lastError);
					//LoadString(hInst, IDS_DEBUGINFO, lpBuffer, sizeof(lpBuffer));
					//MessageBox (*hWnd, errorBuf, lpBuffer, MB_OK);
					ExitLoop = TRUE;
					break;
			}
		}
		if (!ExitLoop)
		{
			GetOverlappedResult (hPipe, &OverLapRd, &bytesTransRd, FALSE);
			strcpy (WhoSend, clients[clientIndex].Name);
            // Use TellAll to broadcast the message.
			if (bytesTransRd)
			{
				SendAll=false;
				switch (tm_toPipe.uMsg)
				{
					case WM_COMMAND:
						#ifdef _LOG_ITAR
							sprintf (LogBuffer, "ServerProc.WM_COMMAND: Next command was received.");
							LogWrite (LogBuffer);
						#endif
						m_tdlg->OnCommand(tm_toPipe.wParam, tm_toPipe.lParam);
						break;
					case WM_SYSCOMMAND:
						//m_tdlg->OnCmdMsg(tm_toPipe.lParam, 0, NULL, NULL) ;
						#ifdef _LOG_ITAR
							sprintf (LogBuffer, "ServerProc.WM_SYSCOMMAND: Next command was received.");
							LogWrite (LogBuffer);
						#endif
						break;
				}
				SendAll=true;
			}
		} 
	}while(!ExitLoop);
	clients[clientIndex].live = FALSE;  // Turns spool gray.
//	CloseHandle (hPipe);                // Close handles.
	CloseHandle (hEventRd);
	CloseHandle (hEventWrt);
//	DisconnectNamedPipe (hPipe);        // Close pipe instance.
	ExitThread(0);                      // Clean up and die.
}

/*************************************************************************\
*
*  PROCEDURE: TellAll ()
*
*  PURPOSE:
*
*    To write the buffer (input parameter) to all of the clients listed
*    in the global array "clients".
*
*  CALLED BY:
*
*    ServerProc();
*
*  COMMENTS:
*
*    Clients is a global array which hold information on each client
*    connected to the named pipe.  This procedure recieves a buffer.
*    It then steps through this global array, and for each client it
*    writes the buffer.
*
\*************************************************************************/

VOID TellAll()
{
	DWORD i;                           // Index through array.
	DWORD bytesWritten;                // Used in WriteFile().
	DWORD retCode;                     // Traps return codes.
	DWORD lastError;                   // Traps returns from GetLastError().
	for(i=0; i < clientCount; i++)     // For all clients in the array.
	{
		// If client isn't alive, don't waste
		// time writing to it.
		if (clients[i].live)
		{
			if (strcmp(WhoSend,clients[i].Name)!=0)
			{
				retCode = WriteFile (clients[i].hPipe, &m_toPipe, sizeof (_toPipe),
					&bytesWritten, &clients[i].overLap);
				// Check 3 kinds of errors: IO_PENDING,
				// NO_DATA, or other.  Wait on event
				// handle if IO_PENDING, else, if it's
				// anything other than NO_DATA (pipe
				// client disconnected), flag the user.
				// In any case, if it's not IO_PENDING,
				// clients[i].live = FALSE, spool turns
				// gray.
				if (!retCode)
				{
					lastError = GetLastError();
					// IO_PENDING, wait on event handle.
					if (lastError == ERROR_IO_PENDING)
					{
						WaitForSingleObject (clients[i].hEvent, (DWORD)-1);
					}
					else
					{
						// If not NO_DATA, flag user.
						char tLogBuffer[300];
						FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,0, lastError, 0, tLogBuffer,200, 0 );
							tLogBuffer[strlen(tLogBuffer)-1] = '\0';
						#ifdef _LOG_ITAR
							sprintf (LogBuffer, "Error №%d (%s).", lastError, tLogBuffer);
							LogWrite (LogBuffer);
						#endif
						if ((lastError == ERROR_NO_DATA)||(lastError == ERROR_TIMEOUT))
						{
							//LoadString(hInst, IDS_DEBUGLAST, lpBuffer, sizeof(lpBuffer));
							//wsprintf (Buf, "%s = %d", buffer, GetLastError());
							MessageBox(NULL, "Не могу связаться с клиентом", "Ошибка.", MB_RETRYCANCEL);
						}
						clients[i].live = FALSE;
					}
				}
			}
		} //if client.live
	} // for loop
	strcpy (WhoSend, "");
}

/////////////////////////////////////////////////////////////////////////////
// CInetTarifDlg dialog
CInetTarifDlg::CInetTarifDlg(CWnd* pParent /*=NULL*/)
        : CDialog(CInetTarifDlg::IDD, pParent)
{
        //{{AFX_DATA_INIT(CInetTarifDlg)
        //}}AFX_DATA_INIT
        // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	pParentWnd = pParent;
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	GlobalWTime=0;
}

void CInetTarifDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInetTarifDlg)
	//DDX_Control(pDX, IDC_PRIN_UAH, cPrinUah);
	//DDX_Control(pDX, IDC_ZALOG_UAH, cZalogUah);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInetTarifDlg, CDialog)
        ON_WM_CONTEXTMENU()
        //{{AFX_MSG_MAP(CInetTarifDlg)
        ON_WM_SYSCOMMAND()
        ON_WM_DESTROY()
        ON_WM_PAINT()
        ON_WM_QUERYDRAGICON()
        ON_WM_TIMER()
//        ON_WM_MOVING()
//		ON_WM_SHOWWINDOW()
        ON_COMMAND(ID_COM, OnCom)
		ON_COMMAND(ID_LOGOFF, OnLogoff)
		ON_COMMAND(ID_SMENA, OnSmena)
		ON_COMMAND(ID_CHEK, OnChek)
		ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST, OnLvnGetdispinfoList)
		ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST, OnNMCustomdrawLvCustomDraw)
		// Function prototype - afx_msg HBRUSH OnCtlColor(CDC*, CWnd*, UINT); 
		ON_WM_CTLCOLOR()
		ON_COMMAND(ID_REMOVEPSSBR, OnRemovepssbr)
	//}}AFX_MSG_MAP
//	ON_STN_CLICKED(IDC_ZALOG_UAH, &CInetTarifDlg::OnStnClickedZalogUah)
//	ON_STN_CLICKED(IDC_PRIN_UAH, &CInetTarifDlg::OnStnClickedPrinUah)
//	ON_WM_SIZING()
//	ON_WM_SIZE()
//	ON_WM_EXITSIZEMOVE()
//	ON_WM_SETTINGCHANGE()
//ON_WM_SIZING()
ON_WM_SIZE()
ON_STN_CLICKED(IDC_PRIN_UAH, &CInetTarifDlg::OnStnClickedPrinUah)
ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInetTarifDlg message handlers



BOOL CInetTarifDlg::OnInitDialog()
{
	// Перечень праздничных дат

/*	SYSTEMTIME SystemTime;
	GetLocalTime(&SystemTime);
	//SystemTime.wHour = 21;
	char TextTime[11];
	sprintf (TextTime, "%02d.%02d.%04d", SystemTime.wDay, SystemTime.wMonth,SystemTime.wYear);
	if (strncmp(TextTime, BigTextTime[i],5)==0)
	CTime tCurrTime = CTime::GetCurrentTime();
 atoi(sDate.Mid(6,4)), atoi(sDate.Mid(3,2)), atoi(sDate.Mid(0,2)) );
 CString sDate = m_Grid.GetItemText(iRow, 1);
*/


	FILE *fp;
	FILE *fp0;
	char Record[100];
	fp = fopen ("holiday.txt",  "r");
	int Now=0;
	if (fp)
	{
		while (!feof(fp))
		{
			memset(&Record, 0, sizeof(Record));
			if (fgets(Record, 100, fp) == NULL) break;
			Record[10]='\0';
			strcpy(BigTextTime[Now], Record);
			int ch = '\n';
			char *c = strchr( &Record[11], ch );
			if (c) *c = '\0';
			strcpy(BigTextRem[Now], &Record[11]);
			Now++;
			CountTime++;
		}
		fclose(fp);
		
	}
	//
	SystemParametersInfo (SPI_GETWORKAREA, 0, &m_desktop, 0);
//	nds = 1.2;
	strcpy (WhoSend, "");
	m_Main = this->m_hWnd;

	// Create the first instance of a server side of the pipe.

	CreateThread ((LPSECURITY_ATTRIBUTES)NULL,       // No security.
                  (DWORD)0,                          // Same stack size.
                  (LPTHREAD_START_ROUTINE)ServerProc,// Thread procedure.
                  (LPVOID)&this->m_hWnd,         // Parameter.
                  (DWORD)0,                          // Start immediatly.
                  (LPDWORD)&lpServerThreadID);       // Thread ID.
	// Установка таймера на 1 сек
	// 1 nIDEvent Specifies a nonzero timer identifier. 
	// 2 nElapse Specifies the time-out value, in milliseconds. 
	// 3 lpfnTimer Specifies the address of the application-supplied TimerProc callback function 
	// that processes the WM_TIMER messages. 
	// If this parameter is NULL, the WM_TIMER messages are placed in the application's message queue 
	// and handled by the CWnd object. 
	CInetTarifDlg::SetTimer(IDT_TIMER, 1000, NULL);
	//Линейка статуса из 3-х частей
	CRect rect;
	//


//!!!!!
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);                 // Set big icon
	SetIcon(m_hIcon, FALSE);                // Set small icon

    // TODO: Add extra initialization here

	// CG: The following block was added by the ToolTips component.
	{
		// Create the ToolTip control.
		m_tooltip.Create(this);
		m_tooltip.Activate(TRUE);
		// TODO: Use one of the following forms to add controls:
		// m_tooltip.AddTool(GetDlgItem(IDC_<name>), <string-table-id>);
		// m_tooltip.AddTool(GetDlgItem(IDC_<name>), "<text>");    
	}
	// Инициализация контекстного меню <InitList()>
	//CRect rect;
	VERIFY(Listmn.CreatePopupMenu());
	VERIFY(Mengmn.CreatePopupMenu());
	//
	CMenu* pMengmn = CMenu::FromHandle(Mengmn);
	pMengmn->InsertMenu(0,MF_BYPOSITION,BREAKST,"Недоступен");
	pMengmn->InsertMenu(1,MF_BYPOSITION,WORKST,"Рабочий");
	pMengmn->InsertMenu(2,MF_BYPOSITION,RESET,"Перезагрузить");
	pMengmn->InsertMenu(3,MF_BYPOSITION,SHUTDOWN,"Выключить");
	//
	CMenu* pListmn = CMenu::FromHandle(Listmn);
	pListmn->InsertMenu(0,MF_BYPOSITION, PUSK,"Залог Ctrl+Z");
	pListmn->InsertMenu(1,MF_BYPOSITION, RASCH,"Расчёт Ctrl+R");
	pListmn->InsertMenu(2,MF_BYPOSITION, OSTANOV,"Остановить");
	pListmn->InsertMenu(2,MF_BYPOSITION, PROLONG,"Продлить сеанс");
	pListmn->InsertMenu(2,MF_BYPOSITION, MOVE,"Перенос сеанса");
	pListmn->AppendMenu(MF_POPUP, (UINT)pMengmn->m_hMenu, "Управление");
	pListmn->InsertMenu(6,MF_BYPOSITION, RASCH_CARD,"Расчет карточкой");
	ASSERT(Listmn);
	// Инициализация списка рабочих станций
	InitWorkstation();
//@@@@@@@@@@@@@@@@@@@@@@@@@@
	ShowWindow(SW_MAXIMIZE);

	//UpdateWindow();
	char UserName[100],Name[200];
	unsigned long nSize = 100;
	GetComputerName( UserName, &nSize);
	sprintf( Name, "Internet Tarificator Server (%s) - %s", UserName, UInfo.Fio);
	SetWindowText (Name);
	SetMenu(&theApp.TempMenu);
	DrawMenuBar();


	// Инициализация списка доступных станций в IDC_LIST
	GetClientRect(&rect);
	//CRect ListRct;
	//
	ListRct.SetRect(3,100,rect.Width()-3,rect.Height()-21);
	VERIFY( m_List.Create(WS_CHILD|WS_VISIBLE|LVS_REPORT|LVS_OWNERDATA|LVS_SINGLESEL|LVS_NOSORTHEADER, 
		ListRct, this, IDC_LIST) );
	// К-во строк
	m_List.SetItemCount(iActivComp);
	//
	m_List.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_TWOCLICKACTIVATE, //dwMask
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_TWOCLICKACTIVATE); 
	//
 	m_List.GetClientRect(rect);
		m_List.InsertColumn(0,_T("№"), LVCFMT_LEFT, 0.4*rect.Width()/10);
 		m_List.InsertColumn(1,_T(""), LVCFMT_LEFT, 0*rect.Width()/20);
		m_List.InsertColumn(2,_T("Состояние"), LVCFMT_LEFT, 4.6*rect.Width()/10);
 		//m_List.InsertColumn(3,_T("Тариф"), LVCFMT_LEFT, 2+2*rect.Width()/10);
		m_List.InsertColumn(3,_T("Тариф"), LVCFMT_LEFT, 1.9*rect.Width()/10);
		m_List.InsertColumn(4,_T("Начало"), LVCFMT_LEFT, 1.3*rect.Width()/10);
 		m_List.InsertColumn(5,_T("Осталось"), LVCFMT_LEFT, 1.5*rect.Width()/10);

	//
	// Инициализация линейки для каждого компа
	//myProgInit();
	// По умолчанию - показывать линейку выполнения для каждого компа
	IsShowPrgss = true;
	//
	//hWnd [in] Handle to the window that will receive WM_HOTKEY messages 
	//id [in] Specifies the identifier of the hot key.
	//An application must specify a value in the range 0x0000 through 0xBFFF. 
	//fsModifiers [in] Specifies keys that must be pressed in combination 
	//with the key specified by the uVirtKey parameter in order to generate the WM_HOTKEY message. 
	//The fsModifiers parameter can be a combination of the following values.
	//MOD_ALT Either ALT key must be held down.
    //MOD_CONTROL Either CTRL key must be held down.
	//MOD_SHIFT Either SHIFT key must be held down.
	//MOD_WIN Either WINDOWS key was held down. These keys are labeled with the Microsoft® Windows® logo.
	//vk [in] Specifies the virtual-key code of the hot key. 
	//Внесение залога Ctrl+Z, Ctrl+z
	RegisterHotKey (this->m_hWnd, MESSAGE_ZALOG,     MOD_CONTROL, 0x5A);
	RegisterHotKey (this->m_hWnd, MESSAGE_ZALOG,     MOD_CONTROL, 0x7A);
	//Расчет Ctrl+R, Ctrl+r
	RegisterHotKey (this->m_hWnd, MESSAGE_RASCHET,      MOD_CONTROL, 0x52);
	RegisterHotKey (this->m_hWnd, MESSAGE_RASCHET,      MOD_CONTROL, 0x72);
	//	RegisterHotKey (this->m_hWnd, MESSAGE_RASCHET,   MOD_ALT|MOD_CONTROL, 0x53);
	//TellAll(NULL);
	
	// 20.05.2009
	CFont *font = new CFont();
	VERIFY(font->CreateFont(
	rect.Width()/32,                        // nHeight
	0,                         // nWidth
	0,                         // nEscapement
	0,                         // nOrientation
	FW_NORMAL,                 // nWeight
	TRUE,                     // bItalic
	FALSE,                     // bUnderline
	0,                         // cStrikeOut
	DEFAULT_CHARSET,              // nCharSet
	OUT_DEFAULT_PRECIS,        // nOutPrecision
	CLIP_DEFAULT_PRECIS,       // nClipPrecision
	DEFAULT_QUALITY,           // nQuality
	DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
	"Arial"));                 // lpszFacename
	//

	CFont *font0 = new CFont();
	VERIFY(font0->CreateFont(
	32,           // nHeight
	0,                         // nWidth
	0,                         // nEscapement
	0,                         // nOrientation
	FW_NORMAL,                 // nWeight
	TRUE,                     // bItalic
	FALSE,                     // bUnderline
	0,                         // cStrikeOut
	DEFAULT_CHARSET,              // nCharSet
	OUT_DEFAULT_PRECIS,        // nOutPrecision
	CLIP_DEFAULT_PRECIS,       // nClipPrecision
	DEFAULT_QUALITY,           // nQuality
	DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
	"Arial"));                 // lpszFacename
	//





	CWnd* pWnd1 = GetDlgItem(IDC_ZALOG_UAH);
	pWnd1->SetFont(font0);
	//
	CWnd* pWnd2 = GetDlgItem(IDC_PRIN_UAH);
	pWnd2->SetFont(font0);
	//
	m_List.SetFont(font);
	myProgInit(rect.Width()/32);
//	rect.bottom-=50;

	
	
	
//	VERIFY( m_StatusBar.Create(WS_CHILD|WS_VISIBLE|CCS_BOTTOM, CRect(0,0,0,0), this, IDC_STATUS_BAR) );
//	m_StatusBar.GetClientRect(&rect);
	//const int nParts = 2;
	//int widths[nParts] = { (int) floor((double) rect.right/nParts), (int) floor((double) rect.right*2/nParts), -1 };
//	const int nParts = 2;
//	int widths[nParts] = { (int) floor((double) rect.right/nParts), -1 };
//	VERIFY( m_StatusBar.SetParts(nParts, widths) );



	//

	CTime tCurrTime = CTime::GetCurrentTime();
	CString sDate = tCurrTime.Format(_T("%d/%m/%Y"));
	COleDateTime m_OleDtTm;
	m_OleDtTm.SetDate( atoi(sDate.Mid(6,4)), atoi(sDate.Mid(3,2)), atoi(sDate.Mid(0,2)) );
	//
	CDaoQueryDef QdInetLog( &theApp.m_database );
	CDaoRecordset pRsData(&theApp.m_database);
	COleVariant m_OleVariant;
	CString strSQL;
	//
	CString strParam = "PARAMETERS [parDate] DATETIME;";
	strSQL = strParam + " SELECT  Round(Sum(PayLog.CalcSum), 2) AS CalcSum "
		"FROM PayLog WHERE DateValue(PayLog.PayDate) = [parDate]";
	double dTmp;
	long lSum = 0;
	try
	{
		// Temporary
		QdInetLog.Create( "", strSQL );
		// Заполнить параметры ( дата)
		m_OleVariant = m_OleDtTm;
		QdInetLog.SetParamValue( "[parDate]", m_OleVariant );
		//
		pRsData.Open(&QdInetLog);
		while ( !pRsData.IsEOF( ) )
		{
			// Сумма оплаты
			pRsData.GetFieldValue("CalcSum", m_OleVariant);
			if (m_OleVariant.vt == VT_DECIMAL)
			{
				if (m_OleVariant.decVal.sign == '-')
					dTmp = Round( 0-m_OleVariant.decVal.Lo64/pow((double) 10, m_OleVariant.decVal.scale), 2 );
				else
					dTmp = Round( m_OleVariant.decVal.Lo64/pow((double) 10, m_OleVariant.decVal.scale), 2 );
			}
			else
				dTmp = Round( m_OleVariant.dblVal, 2 );
			lSum += Round( dTmp*100, 0 );
			pRsData.MoveNext( );
		}
	}
	catch (CDaoException* e)
	{
		AfxMessageBox("Ошибка открытия БД: " + e->m_pErrorInfo->m_strDescription);
		e->Delete();
	}
	if (pRsData.IsOpen()) 
		pRsData.Close();
	if (QdInetLog.IsOpen())
		QdInetLog.Close();
	ShowRaschSum(0, lSum);
	//
	//
	//***** ICON
	NOTIFYICONDATA nid;
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = m_hWnd;
	nid.hIcon = AfxGetApp()->LoadIcon(IDI_STATUS);
	strcpy(nid.szTip, "Заголовок\nInternet тарификатор");
	/*strcpy(nid.szInfo, "Internet тарификатор");
	strcpy(nid.szInfoTitle, "Заголовок");
	nid.uTimeout = 500;
	nid.dwInfoFlags = NIIF_INFO;*/
	nid.uID = 0;
	nid.uFlags = NIF_ICON|NIF_TIP;
	Shell_NotifyIcon(NIM_ADD, &nid);
	//***** ICON
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}



// Для красного и зеленого цветов
HBRUSH CInetTarifDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd->GetDlgCtrlID() == IDC_PRIN_UAH)
	{
		// Set the text color to 
		pDC->SetTextColor(RGB(0, 128, 0));
	}
	if (pWnd->GetDlgCtrlID() == IDC_ZALOG_UAH)
	{
		// Set the text color to red
		pDC->SetTextColor(RGB(255, 0, 0));
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CInetTarifDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
/*	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{*/
		CDialog::OnSysCommand(nID, lParam);
	//}
}

void CInetTarifDlg::OnDestroy()
{
    //WinHelp(0L, HELP_QUIT);
	//Contains information that the system needs to process taskbar status area messages.
	NOTIFYICONDATA nid; 
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = m_hWnd;
	nid.uID = 0;
	//Deletes an icon from the status area.
	Shell_NotifyIcon(NIM_DELETE, &nid);
	//TellAll(NULL);
	//hel theApp.SaveProfiles();
	//Отключить hotkey
	UnregisterHotKey (this->m_hWnd, MESSAGE_ZALOG);
	UnregisterHotKey (this->m_hWnd, MESSAGE_RASCHET);
	// Убрать таймер
   KillTimer(IDT_TIMER);
	// Помощь
	if (HlpGlobal) 
		fclose (HlpGlobal);
	CDialog::OnDestroy();
}

// The framework calls this member function when Windows or an application makes a request 
//to repaint a portion of an application's window.
// The WM_PAINT message is sent when the UpdateWindow or RedrawWindow member function is called.

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CInetTarifDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		m_List.GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		CBrush brushBlue(RGB(0, 0, 255));
		CPen penBlack;
		penBlack.CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
		dc.SelectObject(&penBlack);
		dc.Rectangle(&ListRct);
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CInetTarifDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CInetTarifDlg::OnOK() 
{
	// Иначе по Enter закрывается
	//CDialog::OnOK();




}

// При вызове всплывающего меню
void CInetTarifDlg::OnContextMenu(CWnd*, CPoint point)
{
	CRect rect;
	GetClientRect(rect);
	ClientToScreen(rect);
	POSITION pos1 = m_List.GetFirstSelectedItemPosition();
	POINT my_point;
	my_point.x = point.x - rect.TopLeft().x;
	my_point.y = point.y - rect.TopLeft().y;
	if (pos1!=NULL && ListRct.PtInRect(my_point))
	{
		int ListItm = m_List.GetNextSelectedItem(pos1);
		if(Computers[ListItm].Start==false)
		{
			Listmn.EnableMenuItem((UINT)Listmn.GetSubMenu(5)->m_hMenu, MF_BYCOMMAND | MF_ENABLED);
			if(Computers[ListItm].Connected==false)
			{
				Listmn.EnableMenuItem(PUSK, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
				Listmn.EnableMenuItem(RASCH,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
				Listmn.EnableMenuItem(OSTANOV,MF_BYCOMMAND | MF_DISABLED  | MF_GRAYED);				
				Listmn.EnableMenuItem(PROLONG,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
				Listmn.EnableMenuItem(MOVE,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
				Listmn.EnableMenuItem(RASCH_CARD,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
				//
				Mengmn.EnableMenuItem(WORKST, MF_BYCOMMAND | MF_ENABLED);
				Mengmn.EnableMenuItem(BREAKST, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
				Mengmn.EnableMenuItem(RESET, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
				Mengmn.EnableMenuItem(SHUTDOWN, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
			}
			else
			{
				Listmn.EnableMenuItem(PUSK, MF_BYCOMMAND | MF_ENABLED);
				Listmn.EnableMenuItem(RASCH,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
				Listmn.EnableMenuItem(OSTANOV,MF_BYCOMMAND | MF_DISABLED  | MF_GRAYED);				
				Listmn.EnableMenuItem(PROLONG,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
				Listmn.EnableMenuItem(MOVE,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
				Listmn.EnableMenuItem(RASCH_CARD,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
				//
				Mengmn.EnableMenuItem(WORKST, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
				Mengmn.EnableMenuItem(BREAKST, MF_BYCOMMAND | MF_ENABLED);
				Mengmn.EnableMenuItem(RESET, MF_BYCOMMAND | MF_ENABLED);
				Mengmn.EnableMenuItem(SHUTDOWN, MF_BYCOMMAND | MF_ENABLED);
			}
		}
		else
		{
			Listmn.EnableMenuItem(PUSK, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
			Listmn.EnableMenuItem(RASCH,MF_BYCOMMAND | MF_ENABLED);
			if (Computers[ListItm].Rasch)
				Listmn.EnableMenuItem(OSTANOV,MF_BYCOMMAND | MF_ENABLED );
			else
				Listmn.EnableMenuItem(OSTANOV,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
			if (Computers[ListItm].Connected)
				Listmn.EnableMenuItem(PROLONG,MF_BYCOMMAND | MF_ENABLED );
			else
				Listmn.EnableMenuItem(PROLONG,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
			Listmn.EnableMenuItem(MOVE,MF_BYCOMMAND | MF_ENABLED );
			Listmn.EnableMenuItem((UINT)Listmn.GetSubMenu(5)->m_hMenu, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED );
			Listmn.EnableMenuItem(RASCH_CARD,MF_BYCOMMAND | MF_ENABLED);
		}
		Listmn.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
	else
	{
		// CG: This block was added by the Pop-up Menu component
		{
            if (point.x == -1 && point.y == -1)
			{
				//keystroke invocation
				point = rect.TopLeft();
				point.Offset(5, 5);
			}
			CMenu* menu;
			menu = GetMenu();
			CMenu* pPopup = menu->GetSubMenu(1);
			//pPopup->InsertMenu(0,MF_BYPOSITION, PUSK,str);
			ASSERT(pPopup != NULL);
			CWnd* pWndPopupOwner = this;
			while (pWndPopupOwner->GetStyle() & WS_CHILD)
				pWndPopupOwner = pWndPopupOwner->GetParent();
			pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, pWndPopupOwner);
		}
	}
}

BOOL CInetTarifDlg::PreTranslateMessage(MSG* pMsg)
{
	// CG: The following block was added by the ToolTips component.
	{
		// Let the ToolTip process this message.
		m_tooltip.RelayEvent(pMsg);
	}
	return CDialog::PreTranslateMessage(pMsg);      // CG: This was added by the ToolTips component.
}

//
bool CInetTarifDlg::StartInet(int Comp)
{
	//UnLock
	if (!UnLockStation(Comp))
		return false;
	return true;
}

bool CInetTarifDlg::StopInet(int Comp)
{
	// Lock
	if (!LockStation(Comp))
		return false;
	return true;
}


void ProbConn(void* Params) 
{ 
// int *Com = (int*)Params, Comp;
// Comp = *Com;
int Comp = LinkComp;
if (LockStation(Comp)) Computers[Comp].Connected = true; 
else Computers[Comp].Connected = false;
_endthread(); 
} 


//wParam The low-order word of wParam identifies the command ID of the menu item, control, or accelerator. 
//The high-order word of wParam specifies the notification message if the message is from a control. 
//If the message is from an accelerator, the high-order word is 1. 
//If the message is from a menu, the high-order word is 0. 
//
//lParam Identifies the control that sends the message if the message is from a control. Otherwise, lParam is 0. 

BOOL CInetTarifDlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class

	//HIWORD macro retrieves the high-order word from the given 32-bit value
	//LOWORD macro retrieves the low-order word from the specified value

	// 1 The window procedure of the new window receives this message after the window is created, 
	// but before the window becomes visible
	//if ((wParam==WM_CREATE)&&(lParam==0))
	//	return false;
	// 2 Выход из приложения
    if (wParam==WM_DESTROY)
    {
		for (int i=0; i<iActivComp; i++)
		{
			if (Computers[i].Start == true)
			{
				MessageBox("У Вас есть нерассчитанные станции.\nРассчитайте их перед выходом из программы.",
					"Завершение работы приложения", MB_OK|MB_ICONINFORMATION);
				return false;
			}
		}
		if (MessageBox("Вы собираетесь закрыть приложение. Вы уверены?", "Предупреждение", 
			MB_YESNO|MB_ICONQUESTION|MB_TOPMOST|MB_SETFOREGROUND )==IDYES)
		{
			// UnLock
/*
			for (int i=0; i<iActivComp; i++)
			{
				StartInet(i);
				EnableExplorer(i);
			}
*/
			if(MessageBox("Выключить станции?","Вопрос",MB_ICONQUESTION|MB_YESNO)==IDYES)
			{
				for (int i=0; i<iActivComp; i++)
					ShutdownStation(i);
			}
			return CDialog::OnCommand(wParam, lParam);
		}
		else
			return false;
	}
	// 3 Пункт меню "Выход"
	if ((int)wParam==ID_EXIT) 
		return OnCommand(WM_DESTROY, lParam);
	//
	POSITION pTemp = m_List.GetFirstSelectedItemPosition();
	// 4 Пункты всплывающего меню
	int iComp;
	iComp = m_List.GetNextSelectedItem(pTemp);
	switch(wParam)
	{
		case RASCH:
			card_flag = 0;
			OnPressMenuRasch();
			break;
		case RESET:
			//iComp = m_List.GetNextSelectedItem(pTemp);
			if (Computers[iComp].Connected) ResetStation(iComp);
			break;
		case OSTANOV:
			if (Computers[iComp].Connected) StopInet(iComp);
			Computers[iComp].Rasch = false;
			break;
		case SHUTDOWN:
			//iComp = m_List.GetNextSelectedItem(pTemp);
			if (Computers[iComp].Connected) ShutdownStation(iComp);
			break;
		case PUSK:
			OnPressMenuZalog(wParam, lParam);
			break;
		case BREAKST:
			Computers[iComp].Connected = false;
			break;
		case WORKST:
			// 28.04.11 Пока без всяких проверок	
			// 19.03.13 C проверкой
		
			LinkComp = iComp;
			//_beginthread (ProbConn,1024,&LinkComp);
			_beginthread (ProbConn, 0, NULL);
			break;
		case PROLONG:
			// 28.04.11 Для пункта меню Продление сеанса
			OnPressMenuProlong();
			break;
		case MOVE:
			// 28.04.11 Для пункта меню Перенос сеанса
			OnPressMenuMove();
			break;
		case RASCH_CARD:
			card_flag = 1;
			OnPressMenuRasch();
			card_flag = 0;
			break;
	}
	return CDialog::OnCommand(wParam, lParam);
}
// Обработка событий по таймеру (1 сек.)


void myThread(void* pParams) 
{ 
	int Comp;
	for (Comp=0; Comp<iActivComp; Comp++)
	{
		if (thr77 == 0)
		{
			if (Computers[Comp].Start)
			{
				if (Zapros(Comp))						
					Computers[Comp].Connected=true;
				else
					Computers[Comp].Connected=false;
			}
			else 
			{
				if(thr360 && Computers[Comp].Connected)
				{
					if (LockStation(Comp)) 
						Computers[Comp].Connected = true; 
					else 
						Computers[Comp].Connected = false;
				}
			}			
		}
	}
	thr = 0;
	thr360 = 0;
_endthread(); 
} 

void CInetTarifDlg::OnTimer(UINT nIDEvent) 
{
	int Comp = 0;
	bool bConn;
	GLT++;
//!!!!!!!!!!!!!!!!!!!!!!!
	GlobalWTime++;
	if(resiz) 
	{
		m_List.RedrawWindow();

		resiz = 0;
	}

/*
		for (Comp=0; Comp<iActivComp; Comp++)
		{
			// 26.04.2011 Только для подключенных
			if (Computers[Comp].Connected)
			{
				if (!Computers[Comp].Start)
				{
					StopInet(Comp);
		

					if (Computers[Comp].bTarif || Computers[Comp].cTarif)
					{
						EnableExplorer(Comp);
						DisableExplorer(Comp);



					}

				}

				else
				{
					if (Computers[Comp].Rasch) StartInet(Comp);
					if (Computers[Comp].bTarif || Computers[Comp].cTarif)
						EnableExplorer(Comp);
				}

			}
		}
*/

	if (GLT>9)
	{
		GLT = 0;
		
		if (thr == 0 && GlobalWTime>359)
		{
			#ifdef _LOG_ITAR
			sprintf (LogBuffer, "OnTimer GlobalWTime=%i, thr=%i, thr360=%i, thr77=%i: Reinstall All station.", GlobalWTime, thr, thr360, thr77);
			LogWrite (LogBuffer);
			#endif
			GlobalWTime=0;
			thr360 = 1;
		}
		if(thr == 0 )
		{
			thr = 1;
			_beginthread(myThread, 0, NULL); 
		}
		
	}

	//
	SYSTEMTIME lpSystemTime;
	GetLocalTime(&lpSystemTime);
	//char TempStr[100];
	for (Comp=0; Comp<iActivComp; Comp++)
	{
		if (Computers[Comp].Start==true)
		{
			double oldTarif, newt;
            oldTarif = Computers[Comp].Tarif;
			if (Computers[Comp].bTarif)
				newt = GetTarif(1);
			else if (Computers[Comp].sTarif)
				newt = GetTarif(2);
			else if (Computers[Comp].cTarif)
				newt = GetTarif(3);
			else
				newt = GetTarif(0);
				//newt = GetTarif(2);
			if (oldTarif!=0 && oldTarif!=newt)
			{
				ChangeTarif(Computers[Comp], oldTarif, newt);
				#ifdef _LOG_ITAR
					char LogBuffer[100];
					sprintf (LogBuffer, "Autochange tarif from %2.6f to %2.6f on station %i", oldTarif, newt, Computers[Comp].NumbComp+1);
					LogWrite (LogBuffer);
				#endif
				if (!StartInet(Comp))
				{
					sprintf (LogBuffer, "Ошибка автосмены тарифа для станции %i", Computers[Comp].NumbComp+1);
					LogWrite (LogBuffer);
					MessageBox(LogBuffer, "Ошибка", MB_OK | MB_ICONERROR);
					StopSeance(Comp);
				}
			}
			if (Computers[Comp].Rasch == true)	
			{
				if (Computers[Comp].Ostatok < 0) 
				{
					Computers[Comp].Ostatok = 0;
					Computers[Comp].Time = 0;
					//Computers[Comp].Start = false;
					StopInet(Comp);
					Beep(1000,100);
					Computers[Comp].Rasch = false; // признак остановки и расчета, но не выполнять расчет
	
		//			if(Computers[Comp].Ostatok < 0.005)
					sprintf (TempStr, "У машины № %i закончился залог", Computers[Comp].NumbComp+1);
		/*			else
						sprintf (TempStr, "На машине № %i пользователем досрочно прерван сеанс", Computers[Comp].NumbComp+1);
		*/
						MessageBox(TempStr, "Внимание", MB_OK|MB_ICONINFORMATION);
					//iCompPar = Comp;
	               
		//			StopSeance(Comp);
		

					resiz = 1;
					#ifdef _LOG_ITAR
					sprintf (LogBuffer, "Закончилось время. Station #%i", Computers[Comp].NumbComp+1);
						LogWrite (LogBuffer);
					#endif
				}
				else
				{
	//!!!!!!!
					Computers[Comp].Time--;
					Computers[Comp].Elapce++;
					if(Computers[Comp].Elapce > 1800) 
					Computers[Comp].Ostatok -= (Computers[Comp].Tarif * nds);
					else Computers[Comp].Ostatok = Computers[Comp].AllZalog - Computers[Comp].Tarif * nds * 1800;

				}
			}

			//22.05.2009
			CString log;
			float n, res;
			// res=целая часть числа n=дробная 0.xx
			n = modf((float)(GlobalWTime+Comp)/5, &res);
			if (n < 0.01)
			{
				m_List.RedrawItems(Comp, Comp);
				//m_List.Update(Comp);
				log.Format("GlobalWTime = %d, n = %.3f, res = %d", GlobalWTime, n, res);
				TRACE(log+"\n");
			}
			//
			//m_List.RedrawItems(Comp,Comp);
		}
	}
	CDialog::OnTimer(nIDEvent);
}

// Called by the framework to route and dispatch command messages 
// and to handle the update of command user-interface objects.
BOOL CInetTarifDlg::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	// nID - Contains the command ID. 
    // nCode - Identifies the command notification code.
	return CDialog::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

// Обработка сообщений приложения
LRESULT CInetTarifDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if( message == WM_HOTKEY)
	{
		switch (wParam)
		{
			// Внести залог
            case MESSAGE_ZALOG:
				//MessageBox("Нажата горячая клавиша Ctrl+Z.","Информация", MB_OK|MB_ICONINFORMATION);
				OnPressMenuZalog(wParam, lParam);
				break;
			//Расчет
			case MESSAGE_RASCHET:
				//MessageBox("Нажата горячая клавиша Ctrl+R.","Информация", MB_OK|MB_ICONINFORMATION);
				OnPressMenuRasch();
				break;
		}
	}
	if(message == WM_QUERYENDSESSION)
	{
	}
	//wParam If the session is being ended, this parameter is TRUE; otherwise, it is FALSE
	//If the wParam parameter is TRUE, the session can end any time after all applications have returned 
	//from processing this message. Therefore, an application should perform all tasks required for termination 
	//before returning from this message.
	//The application need not call the DestroyWindow or PostQuitMessage function when the session is ending.
	if(message == WM_ENDSESSION)
	{
		//The PostQuitMessage function indicates to the system that a thread has made a request to terminate (quit). 
		//It is typically used in response to a WM_DESTROY message.
        PostQuitMessage(0);
	}
	return CDialog::DefWindowProc(message, wParam, lParam);
}

// Для пункта меню Залог
void CInetTarifDlg::OnPressMenuZalog(WPARAM wParam, LPARAM lParam)
{
	POSITION pTemp = m_List.GetFirstSelectedItemPosition();
	int iComp = m_List.GetNextSelectedItem(pTemp);
	if ( iComp >= 0 && iComp < iActivComp && Computers[iComp].Start==false )
	{
		//m_toPipe.uMsg = WM_COMMAND;
		//m_toPipe.lParam = lParam;
		//m_toPipe.wParam = MESSAGE_ZALOG1+iComp;
		//m_toPipe.CText = false;
		//TellAll();
		#ifdef _LOG_ITAR
			sprintf (LogBuffer, "Show station number %d", Computers[iComp].NumbComp+1);
			LogWrite (LogBuffer);
		#endif
	
		// Приостановка опросов

		thr77 = 1;


		CNewSeans seans;
		//По умолчанию
		int iTarCode = 0;
		seans.tarn = iTarCode;
		seans.iComp=Computers[iComp].NumbComp+1;
		if(seans.DoModal()==IDOK)
		{
			iTarCode=seans.tarn;
			// Запустить предоставление услуг и учет
			GetLocalTime(&Computers[iComp].DateTimeBeg);
			AtertSeance(iComp, iTarCode);
		}

		// Продолжение опросов
		thr77 = 0;

	}
}
//Для пункта меню Расчет
void CInetTarifDlg::OnPressMenuRasch()
{
	POSITION pTemp = m_List.GetFirstSelectedItemPosition();
	int iComp = m_List.GetNextSelectedItem(pTemp);
	// Если попали в диапазон станций и станция запущена
	if ( iComp >= 0 && iComp < iActivComp && Computers[iComp].Start==true )
	{
		// Остановить предоставление услуг и учет

//		bool bConn = StopInet(iComp);
//!!!!!
		if (Computers[iComp].Connected) StopInet(iComp);

		if (Computers[iComp].bTarif || Computers[iComp].cTarif)
//!!!!
			if (Computers[iComp].Connected) EnableExplorer(iComp);
			//bConn&=EnableExplorer(iComp);
		if(!Computers[iComp].Connected)
		{
			char msg[100];
			sprintf(msg,"Не удалось связаться со станцией №%i", Computers[iComp].NumbComp+1);
			MessageBox(msg,"Ошибка",MB_OK|MB_ICONERROR);
		}
		Computers[iComp].Start = false;
		#ifdef _LOG_ITAR
			sprintf (LogBuffer, "Stop session in station #%i",  Computers[iComp].NumbComp+1);
			LogWrite (LogBuffer);
		#endif
		// Рассказать всем
		//m_toPipe.uMsg = WM_SYSCOMMAND; 
	    //m_toPipe.lParam = iComp+1300;  
	    //m_toPipe.wParam = 0;  
	    //m_toPipe.CText = false;
		//if (SendAll) TellAll();
		// закрыто 19,05,2009 - путаются
		/*
		// Предложить внести дополнительный залог
		CNewSeans seans;
		// Используемый тип пакета
		int iTarCode = 99*(Computers[iComp].TPos+1);
		seans.tarn = iTarCode;
		seans.iComp=Computers[iComp].NumbComp+1;
		seans.sTitle = "Продление сеанса";
		seans.sButTitle = "Продолжить сеанс";
		if(seans.DoModal()==IDOK)
		{
			iTarCode=seans.tarn;
			// Запустить предоставление услуг и учет
			AtertSeance(iComp, iTarCode);
		}
		else
		{
			// Остановить предоставление услуг и учет, выполнить расчет
			Computers[iComp].Start = false;
			StopInet(iComp);
			StopSeance(iComp);
		}
		*/
		// 19.05.2009 Остановить предоставление услуг и учет, выполнить расчет
//		StopInet(iComp);
		StopSeance(iComp);
	}
}

// 28.04.11 Для пункта меню Продление сеанса
void CInetTarifDlg::OnPressMenuProlong()
{
	POSITION pTemp = m_List.GetFirstSelectedItemPosition();
	int iComp = m_List.GetNextSelectedItem(pTemp);
	// Если попали в диапазон станций и станция запущена
	if ( iComp >= 0 && iComp < iActivComp && Computers[iComp].Start==true )
	{
		// Остановить предоставление услуг и учет
//!!!!!!!!!!!!!!!!!
		// Приостановка опросов

		thr77 = 1;

		bool bConn;
		if(Computers[iComp].Rasch) bConn = StartInet(iComp);
		else  bConn = StopInet(iComp);
		if (Computers[iComp].bTarif || Computers[iComp].cTarif)
		if(Computers[iComp].Rasch) bConn&=EnableExplorer(iComp);
		if(!bConn)
		{
			char msg[100];
			sprintf(msg,"Не удалось связаться со станцией №%i", Computers[iComp].NumbComp+1);
			MessageBox(msg,"Ошибка",MB_OK|MB_ICONERROR);
		}
//		Computers[iComp].Start = false;
		#ifdef _LOG_ITAR
			sprintf (LogBuffer, "Stop session in station #%i",  Computers[iComp].NumbComp+1);
			LogWrite (LogBuffer);
		#endif
		sprintf(fio, "%s", Computers[iComp].sStudFio);
		sprintf(num, "%s", Computers[iComp].sStudNum);
		// Предложить внести дополнительный залог
		CNewSeans seans;
		// Используемый тип пакета
		int iTarCode = 99*(Computers[iComp].TPos+1);
		seans.tarn = iTarCode;
		seans.iComp=Computers[iComp].NumbComp+1;
		seans.sTitle = "Продление сеанса";
		seans.sButTitle = "Продолжить сеанс";
		if(seans.DoModal()==IDOK)
		{
			iTarCode=seans.tarn;
		}
		else
		{
			// Остановить предоставление услуг и учет, выполнить расчет
			//Computers[iComp].Start = false;
			//StopInet(iComp);
			//StopSeance(iComp);
			// Всего лишь обнулить новый залог
			sprintf(cClientZalog, "%i", 0);
			iTarCode=Computers[iComp].TPos;
		}
		// StopInet(iComp);
		// Запустить предоставление услуг и учет
		AtertSeance(iComp, iTarCode);
		// Продолжение опросов
		thr77 = 0;
	}
}

// 28.04.11 Для пункта меню Перенос сеанса
void CInetTarifDlg::OnPressMenuMove()
{
	POSITION pTemp = m_List.GetFirstSelectedItemPosition();
	int iComp = m_List.GetNextSelectedItem(pTemp);
	// Если попали в диапазон станций и станция запущена
	if ( iComp >= 0 && iComp < iActivComp && Computers[iComp].Start==true )
	{
		// Остановить предоставление услуг и учет
//!!!!!!
//		bool bConn = StopInet(iComp);
		// Приостановка опросов
		thr77 = 1;



		bool bConn;
		if (Computers[iComp].Connected) bConn = StartInet(iComp);
		if (Computers[iComp].bTarif || Computers[iComp].cTarif)
			bConn&=EnableExplorer(iComp);
		if(!bConn)
		{
			char msg[100];
			sprintf(msg,"Не удалось связаться со станцией №%i", Computers[iComp].NumbComp+1);
			MessageBox(msg,"Ошибка",MB_OK|MB_ICONERROR);
		}
//		Computers[iComp].Start = false;
		#ifdef _LOG_ITAR
			sprintf (LogBuffer, "Stop session in station #%i",  Computers[iComp].NumbComp+1);
			LogWrite (LogBuffer);
		#endif
		// Окно выбора станций
		CSessMove sessmove;
		// Используемый тип пакета
		int iTarCode = Computers[iComp].TPos;
		// Нового залога нет
		sprintf(cClientZalog, "%i", 0);
		//
		sessmove.iCurrComp = iComp;
		if(sessmove.DoModal()==IDOK)
		{
			if (sessmove.NewNumbComp != -1)
			{
				// Найти номер станции по списку
				for (int Comp=0; Comp<iActivComp; Comp++)
				{
					if (Computers[Comp].NumbComp==sessmove.NewNumbComp)
					{
						// Перенести данные со старой станции на новую
						// Дата начала учета сеанса по текущему тарифу
						Computers[Comp].DateTimeBeg = Computers[iComp].DateTimeBeg;
						// Отработано времени по текущему тарифу
						Computers[Comp].Elapce = Computers[iComp].Elapce;
						// Тип текущего тарифа
						Computers[Comp].TPos = Computers[iComp].TPos;
						// Работа на ЭВМ без выхода в Интернет
						Computers[Comp].bTarif = Computers[iComp].bTarif;
						// Выхода в Интернет - студентческий
						Computers[Comp].sTarif = Computers[iComp].sTarif;
						// Работа на ЭВМ без выхода в Интернет - студентческий
						Computers[Comp].cTarif = Computers[iComp].cTarif;
						// Текущий тариф
						Computers[Comp].Tarif = Computers[iComp].Tarif;
						// Признак работы станции (t - занята, f - свободна или закончился залог)
						Computers[Comp].Start = Computers[iComp].Start;
						// Признак расчета с клиентом (t - не рассчитан, f - расчет завершен)
						Computers[Comp].Rasch = Computers[iComp].Rasch;
						// Признак доступности рабочей станции
						Computers[Comp].Connected = Computers[iComp].Connected;
						// Всего принято залога
						Computers[Comp].AllZalog = Computers[iComp].AllZalog;
						// Реальный остаток залога баз текущего расчета
						Computers[Comp].Zalog = Computers[iComp].Zalog;
						// Текущий остаток секунд работы	
						Computers[Comp].Time = Computers[iComp].Time;
						// Текущий остаток залога
						Computers[Comp].Ostatok = Computers[iComp].Ostatok;
						// Для студ.тарифа - ФИО
						//Computers[Comp].sStudFio = Computers[iComp].sStudFio;
						// Для студ.тарифа - номер справки, билета
						//Computers[Comp].sStudNum = Computers[iComp].sStudNum;
						//К-во расчетов по другим тарифам 
						Computers[Comp].nBills = Computers[iComp].nBills;
						// Расчеты по другим тарифам (при автосмене тарифа)
						if (Computers[iComp].nBills > 0)
						{
							Computers[Comp].Bills = new Bill[Computers[Comp].nBills];
							memcpy(Computers[Comp].Bills, Computers[iComp].Bills,(Computers[iComp].nBills)*sizeof(Bill));
						}
						//
//!!!!!!
						if (Computers[iComp].Connected) StopInet(iComp);

						sprintf(fio, "%s", Computers[iComp].sStudFio);
						sprintf(num, "%s", Computers[iComp].sStudNum);
						sprintf(cClientZalog, "%i", 0);
						// Очистить старую
						ClearComp(&Computers[iComp]);
						// Запустить предоставление услуг и учет
						AtertSeance(Comp, iTarCode);
						break;
					}
				}
			}
			else
			{
				// Запустить предоставление услуг и учет на старой станции
				AtertSeance(iComp, iTarCode);
			}
		}
		else
		{
			// Запустить предоставление услуг и учет на старой станции
			AtertSeance(iComp, iTarCode);
		}
		// Продолжение опросов
		thr77 = 0;

	}
}

// The framework calls this member function while a user is moving a CWnd object.
// nSide - The edge of window to be moved. 
// lpRect - Address of the CRect or RECT structure that will contain the item's coordinates. 
//void CInetTarifDlg::OnMoving( UINT nSide, LPRECT lpRect )
//{
//	if (lpRect->left<=0) 
//	{
//		lpRect->left=1;
//		lpRect->right=669;
//	}
//	if (lpRect->top<=0)
//	{
//		lpRect->top = 1;
//		lpRect->bottom=400;
//	}
///*	if (lpRect->left>=m_desktop.right-668)
//	{
//		lpRect->left=m_desktop.right-668;
//		lpRect->right=m_desktop.right;
//	}
//	if (lpRect->top>=m_desktop.bottom-399)
//	{
//		lpRect->top=m_desktop.bottom-399;
//		lpRect->bottom=m_desktop.bottom;
//	}
//*/
//
//
//
//
//	CDialog::OnMoving(  nSide,  lpRect );
//}


// The framework calls this member function when the CWnd object is about to be hidden or shown.
// bShow - Specifies whether a window is being shown. It is TRUE if the window is being shown; it is FALSE if the window is being hidden. 
// nStatus - Specifies the status of the window being shown. It is 0 if the message is sent because of a ShowWindow member function call; otherwise nStatus is one of the following: 
// SW_PARENTCLOSING   Parent window is closing (being made iconic) or a pop-up window is being hidden. 
// SW_PARENTOPENING   Parent window is opening (being displayed) or a pop-up window is being shown. 
//void CInetTarifDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
//{
//	CString pn = m_Setup.PathName;
//	if (pn.IsEmpty()) pn = ".";
//	pn +=	"\\inettarif.hlp";
//	HlpGlobal = fopen ((char*)(LPCSTR) pn, "ab");
//	if (!HlpGlobal)
//	{
//		MessageBox("Не удалось открыть файл помощи.","Ошибка", MB_OK|MB_ICONERROR);
//  	    OnOK();
//	    return;
//	}
//	//UpdateWindow();
//	char UserName[100],Name[200];
//	unsigned long nSize = 100;
//	GetComputerName( UserName, &nSize);
//	sprintf( Name, "Internet Tarificator Server (%s) - %s", UserName, UInfo.Fio);
//	SetWindowText (Name);
//	SetMenu(&theApp.TempMenu);
//	DrawMenuBar();
//}
// Updates the client area by sending a WM_PAINT message if the update region is not empty.
/*/??
void CInetTarifDlg::UpdateWindow()
{
	char UserName[100],Name[200];
	unsigned long nSize = 100;
	GetComputerName( UserName, &nSize);
	sprintf( Name, "Internet Tarificator Server (%s) - %s", UserName, UInfo.Fio);
	SetWindowText (Name);
	SetMenu(&theApp.TempMenu);
	DrawMenuBar();
}
/*/
void CInetTarifDlg::ChangeTarif(CompInfo &Comp, double oldt, double newt)
{
	double fSum = 0;
	if ( oldt > 0 || Comp.Elapce > 0) //Перенести данные в список частей сеанса
	{
		// Увеличить массив Bills на 1 элемент
		Bill * TempBills = Comp.Bills;
		Comp.Bills = new Bill[++Comp.nBills];
		if(TempBills) 
			memcpy(Comp.Bills, TempBills, (Comp.nBills-1)*sizeof(Bill));
		delete TempBills;
		// Сохранить данные в новый элемент
		Comp.Bills[Comp.nBills-1].TimeBeg = Comp.DateTimeBeg;
		Comp.Bills[Comp.nBills-1].Tarif = oldt;	
		Comp.Bills[Comp.nBills-1].Time = Comp.Elapce;
		// Всего с НДС начислено
		fSum = Round(oldt * Comp.Elapce *  nds , 2);
		Comp.Bills[Comp.nBills-1].Sum = fSum;
	}
	// Учет по новому тарифу

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//	GetLocalTime(&Comp.DateTimeBeg);
	Comp.Tarif = newt;
	Comp.Elapce = Comp.Elapce - 10;  //Добавим время для начала сеанса (пока пользователь дойдет);
	//Реальный остаток залога
	Comp.Zalog = Comp.AllZalog - fSum;
	// Изменяющийся по таймеру остаток залога
	Comp.Ostatok = Comp.Zalog + Comp.Tarif * nds * 10 ; // Добавим денег на 10 секунд 
	Comp.Time = (int) floor( Comp.Ostatok/(Comp.Tarif* nds ) );  
}
// Новый сеанс
void CInetTarifDlg::AtertSeance(int iComp, int iTarCode)
{



	double dZalog = atof (cClientZalog);
//!!!!!!!**  	if ( ( dZalog > 0) || (Computers[iComp].Ostatok > 0) )
	if ( ( dZalog != 0) || (Computers[iComp].Ostatok > 0) )
	{
		// 20.05.2009 Новые деньги в залог
		long lZalog = Round(dZalog*100, 0);
		ShowRaschSum(lZalog, 0);
		//
//

		
//
		BOOL bConn;
		char cStr[100];
		sprintf(cStr, "Станция № %i - новый сеанс", Computers[iComp].NumbComp+1);
//		m_StatusBar.SetText(cStr, 1, 0);
		Computers[iComp].Zalog+=dZalog;
		Computers[iComp].Ostatok+=dZalog;
		Computers[iComp].AllZalog+=dZalog;
		Computers[iComp].bTarif = false;
		Computers[iComp].sTarif = false;
		Computers[iComp].cTarif = false;
//**		bConn = EnableExplorer(iComp);
		//
		double oldTarif, newTarif;
		oldTarif = Computers[iComp].Tarif;
		newTarif=GetTarif(iTarCode);
		//
		Computers[iComp].TPos = iTarCode;
		if (iTarCode == 1) // Без выхода в Интернет
			Computers[iComp].bTarif = true;
		else if (iTarCode == 2) // Интернет студ.
		{
			Computers[iComp].sTarif = true;
			Computers[iComp].sStudFio = fio;
			Computers[iComp].sStudNum = num;
		}
		else if (iTarCode == 3) // Компьютер без выхода в Интернет студ.
		{
			Computers[iComp].cTarif = true;
			Computers[iComp].sStudFio = fio;
			Computers[iComp].sStudNum = num;
		}
		// Если были данные учета - перенести в в список, иначе - просто обновить данные стр-ры
		// DateTimeBeg, Tarif, Elapce, Zalog, Ostatok, Time
		ChangeTarif(Computers[iComp], oldTarif, newTarif);
		//
		#ifdef _LOG_ITAR
			sprintf (LogBuffer, "Start session in station #%i. Тарифный пакет #%i"
				"\n          Statistics: Залог - %.2f, Осталось времени - %d, Тариф - %.2f, Использовано сек. - %d", 
				Computers[iComp].NumbComp+1, Computers[iComp].TPos,
				Computers[iComp].AllZalog, Computers[iComp].Time, Computers[iComp].Tarif, 
				Computers[iComp].Elapce);
			LogWrite (LogBuffer);
		#endif
		//m_Progress->SetRange(0,Computers[Comp].AllZalog*100);
		//m_Progress->SetPos(Computers[Comp].Ostatok*100);
		if (Computers[iComp].Time<=0)
		{
			Computers[iComp].Time=0;
			return;
		}
		if (StartInet(iComp))//if (bConn && StartInet(iComp))
		{
/*			int tTime = m_Time;
			if (!Zapros(iComp)) // c помощью получается время с раб. станции
			{
				sprintf(LogBuffer,"UnLockStationSock: send() failed: error receiving time %d", iComp);
				LogWrite(LogBuffer);
				WSACleanup();
				StopSeance(iComp);
				return;
			}
			if (tTime != m_Time) // сравнивается полученое время с расчитанным 
			{
				LockStation(iComp);
				sprintf(LogBuffer,"UnLockStationSock: send() failed: error time %d", iComp);
				LogWrite(LogBuffer);
				WSACleanup();
				StopSeance(iComp);
				return;
			}
*/
			Computers[iComp].Start = true;
			Computers[iComp].Rasch = true;
			Computers[iComp].Connected=true;
		}
		else //bConn && StartInet(Comp)
		{
			Computers[iComp].Start = false;
			Computers[iComp].Rasch = false;
			Computers[iComp].Connected = false;
			char msg[100];
			sprintf(msg,"Не удалось связаться со станцией №%i", Computers[iComp].NumbComp+1);
			MessageBox(msg,"Ошибка",MB_OK|MB_ICONERROR);
			// 20.05.2009
			StopSeance(iComp);
			//return;
		}
		//m_toPipe.uMsg = WM_SYSCOMMAND; 
		//m_toPipe.lParam = iComp+1300;  
		//m_toPipe.wParam = 0;  
		//m_toPipe.CText = false;
		//Heres
		//if (SendAll) TellAll();
	}// ( dZalog > 0) || (Computers[Comp].Ostatok > 0) 


char zalog[9];
int m;
		CopyFile("avans.ini","avans.bac",false);
		FILE* fp0 = fopen ("avans.ini", "wb");
		if (!fp0)
		{
			#ifdef _LOG_ITAR
				LogWrite ("Error writing avans.ini");
			#endif
			
		}
		CWnd* pWnd = GetDlgItem(IDC_ZALOG_UAH);
		CString sStr;
		pWnd->GetWindowText(sStr);
        memcpy (zalog, sStr, strlen(sStr));
		zalog[strlen(sStr)]='\0';
	m = fwrite (zalog, 9, 1, fp0);
				if (m!=1)
				{
					#ifdef _LOG_ITAR
						LogWrite("Error writing avans.ini");
					#endif
		
				}

		for (int i=0; i<m_Setup.CountComp; i++)
		{
			if(Computers[i].Start == true)
			{
				TimeHistory = Computers[i].DateTimeBeg.wSecond + Computers[i].DateTimeBeg.wMinute*60 + Computers[i].DateTimeBeg.wHour*3600;
				m = fwrite (&i, sizeof (INT), 1, fp0);
				m += fwrite (&Computers[i].TPos, sizeof (INT), 1, fp0);
				m += fwrite (&Computers[i].AllZalog, sizeof (DOUBLE), 1, fp0);
				m += fwrite (&TimeHistory, sizeof (INT), 1, fp0);
				if (m!=4)
				{
					#ifdef _LOG_ITAR
						LogWrite("Error writing avans.ini");
					#endif
					
				}


				
				;
			}
		}

	
	fclose(fp0);

	#ifdef _LOG_ITAR
		LogWrite("Writing avans.ini");
	#endif



}

void CInetTarifDlg::StopSeance(int iComp)
{



	//m_toPipe.uMsg = WM_SYSCOMMAND; 
	//m_toPipe.lParam = iComp+1400;  
	//m_toPipe.wParam = 0;  
	//m_toPipe.CText = false;
	//Heres
	//if (SendAll) TellAll();
	// Окончательный расчет
	#ifdef _LOG_ITAR
		sprintf (LogBuffer, "Calculate station number %i",  Computers[iComp].NumbComp+1);
		LogWrite (LogBuffer);
	#endif
	//
	char cStr[100];
	sprintf(cStr, "Станция № %i - сеанс окончен", Computers[iComp].NumbComp+1);
//	m_StatusBar.SetText(cStr, 1, 0);
	//
	CClientRaschet dlg;
	dlg.Comp = &Computers[iComp];
	dlg.DoModal();
	// 20.05.2009
	long lZalog = 0 - dlg.AllZalog;
	long lPriem = dlg.PriemCops;
	ShowRaschSum(lZalog, lPriem);
	//
	ClearComp(&Computers[iComp]);
	//Computers[iComp].Rasch = false;


char zalog[9];
int m;
		CopyFile("avans.ini","avans.bac",false);
		FILE* fp0 = fopen ("avans.ini", "wb");
		if (!fp0)
		{
			#ifdef _LOG_ITAR
				LogWrite ("Error writing avans.ini");
			#endif
			
		}

		CWnd* pWnd = GetDlgItem(IDC_ZALOG_UAH);
		CString sStr;
		pWnd->GetWindowText(sStr);
	    memcpy (zalog, sStr, strlen(sStr));
		zalog[strlen(sStr)]='\0';
		sprintf(zalog,sStr);
	m = fwrite (zalog, 9, 1, fp0);
				if (m!=1)
				{
					#ifdef _LOG_ITAR
						LogWrite("Error writing avans.ini");
					#endif

				}


		for (int i=0; i<m_Setup.CountComp; i++)
		{
			if(Computers[i].Start == true)
			{
				TimeHistory = Computers[i].DateTimeBeg.wSecond + Computers[i].DateTimeBeg.wMinute*60 + Computers[i].DateTimeBeg.wHour*3600;
				m = fwrite (&i, sizeof (INT), 1, fp0);
				m += fwrite (&Computers[i].TPos, sizeof (INT), 1, fp0);
				m += fwrite (&Computers[i].AllZalog, sizeof (DOUBLE), 1, fp0);
				m += fwrite (&TimeHistory, sizeof (INT), 1, fp0);
				if (m!=4)
				{
					#ifdef _LOG_ITAR
						LogWrite("Error writing avans.ini");
					#endif

				}


				
				;
			}
		}

	fclose(fp0);




}
// 20.05.2009
void CInetTarifDlg::ShowRaschSum(long lZalog, long lPriem)
{
	if (lZalog != 0)
	{
		CWnd* pWnd = GetDlgItem(IDC_ZALOG_UAH);
		CString sStr;
		pWnd->GetWindowText(sStr);
		float dSum =  Round( (lZalog + atof(sStr)*100)/100,2);
		sStr.Format("%.2f", dSum);
		pWnd->SetWindowText(sStr);
	}
	if (lPriem != 0)
	{
		CWnd* pWnd = GetDlgItem(IDC_PRIN_UAH);
		CString sStr;
		pWnd->GetWindowText(sStr);
		float dSum = Round( (lPriem + atof(sStr)*100)/100,2);
		sStr.Format("%.2f", dSum);
		pWnd->SetWindowText(sStr);
	}
}

// LVN_GETDISPINFO
void CInetTarifDlg::OnLvnGetdispinfoList(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pInfo = (NMLVDISPINFO*)pNMHDR;
	LV_ITEM lvItem;
	LV_ITEM*	plvItem = &lvItem;
	plvItem = &(pInfo)->item; // сразу получим указатель на LV_ITEM
	int index = plvItem->iItem;// и индекс, для наглядности
	CString str;
	str.Format("%s",Computers[index].CompName);
	switch(plvItem->iSubItem)
	{
	// Номер по порядку
	case 0:
		if (plvItem->mask & LVIF_TEXT)
		{
			// hel itoa(index+1,plvItem->pszText,10);
			itoa(Computers[index].NumbComp+1, plvItem->pszText,10);
		}
		break;
	// Наименование станции
	case 1:
		if (str == ""){
			plvItem->pszText = "Не установлен";
		}
		else{
			//pItem->mask = LVIF_TEXT;
			plvItem->pszText = Computers[index].CompName;
		}
		break;
	// Информация + Бегунок 
	case 2:	
		if (Computers[index].Start)
		{
			if (IsShowPrgss)
			{
//				m_vectPrgssCtrl[index]->SetPos( (int) floor((double) Computers[index].Ostatok*100/Computers[index].AllZalog) );
//				if (Computers[index].Ostatok < 2) m_vectPrgssCtrl[index]->SetPos( (int) floor((double) Computers[index].Ostatok*100/2) );
//				else m_vectPrgssCtrl[index]->SetPos(100);
				if (Computers[index].Time < 1800) m_vectPrgssCtrl[index]->SetPos((int)(Computers[index].Time*100/1800));
				else m_vectPrgssCtrl[index]->SetPos(100);

			}
			sprintf(plvItem->pszText,"Залог:%.2f. Остаток:%.2f",Computers[index].AllZalog,Computers[index].Ostatok);
		}
		else
		{
			if (IsShowPrgss)
			{
				m_vectPrgssCtrl[index]->SetPos(0);
			}
			if ( Computers[index].Connected )
				sprintf(plvItem->pszText,"Свободен");
			else
				sprintf(plvItem->pszText,"Недоступен");
		}
		break;
	// Тариф
	case 3:
		sprintf(plvItem->pszText,"%.5f грн/c.",Computers[index].Tarif);
		break;
	// Время начала
	case 4:
		if (Computers[index].Start)
			sprintf(plvItem->pszText,"%02d:%02d:%02d", Computers[index].DateTimeBeg.wHour, Computers[index].DateTimeBeg.wMinute, Computers[index].DateTimeBeg.wSecond);
		break;
	// Осталось работать времени
	case 5:
		if (Computers[index].Start)
		{
			int Temp1, Temp2, Temp3;
			// Часы
			Temp1 = (int) floor( (double) Computers[index].Time/3600 );
			// Минуты
			Temp2 = (int) floor( (double) (Computers[index].Time- Temp1*3600)/60 ) ;
			// Секунды
			Temp3 = Computers[index].Time - Temp1*3600 - Temp2*60 ;
			//
			sprintf(plvItem->pszText,"%02d:%02d:%02d", Temp1, Temp2, Temp3);
		}
		break;
	}
	*pResult = 0;
}
// NM_CUSTOMDRAW
void CInetTarifDlg::OnNMCustomdrawLvCustomDraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVCUSTOMDRAW pNmlv = (LPNMLVCUSTOMDRAW)pNMHDR;
	*pResult = CDRF_DODEFAULT;
	CString log;
	DWORD iItemIdx = pNmlv->nmcd.dwItemSpec;
	switch(pNmlv->nmcd.dwDrawStage)
	{
	case CDDS_POSTERASE:
		log+="CDDS_POSTERASE ";
		break;
	case CDDS_POSTPAINT:
		log+="CDDS_POSTPAINT ";
		*pResult = CDRF_NOTIFYITEMDRAW;
		break;
	case CDDS_PREERASE:
		log+="CDDS_PREERASE ";
		break;
	case CDDS_PREPAINT:
		log.Format("CDDS_PREPAINT %i", pNmlv->nmcd.dwItemSpec);
		*pResult = CDRF_NOTIFYITEMDRAW|CDRF_NOTIFYPOSTPAINT;
		break;
	case CDDS_ITEM:
		log+="CDDS_ITEM ";
		break;
	case CDDS_ITEMPOSTERASE:
		log+="CDDS_ITEMPOSTERASE ";
		break;
	case CDDS_ITEMPOSTPAINT:
		log+="CDDS_ITEMPOSTPAINT ";
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
		break;
	case CDDS_ITEMPREERASE:
		log+="CDDS_ITEMPREERASE ";
		break;
	case CDDS_ITEMPREPAINT:
		if (Computers[iItemIdx].Connected)
			if (Computers[iItemIdx].Start)
			{
				// Зеленый RGB(66,174,97)
				if (Computers[iItemIdx].Rasch) pNmlv->clrTextBk = RGB(200, 255, 200); //прозрачный зеленый
				else  
				{ 
					pNmlv->clrTextBk = RGB(255, 200, 255);
					//прозрачный красный
				}
				// Белый RGB( 255, 255,255)
				if (Computers[iItemIdx].Rasch)
				pNmlv->clrText = RGB( 0, 0, 0); // черный
			}
			else
			{
				// Белый фон
				pNmlv->clrTextBk = RGB(255, 255, 255);
				// Черные буквы
				pNmlv->clrText = RGB(0, 0, 0);
			}
		else
		{
			// Белый фон
			pNmlv->clrTextBk = RGB(255, 255, 255);
			// Красные буквы
			pNmlv->clrText = RGB(255, 0, 0);
		}
		log.Format("CDDS_ITEMPREPAINT %i", iItemIdx);
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
		break;
	case CDDS_ITEMPREPAINT | CDDS_SUBITEM:
		log.Format("CDDS_ITEMPREPAINT %i | CDDS_SUBITEM %i", pNmlv->nmcd.dwItemSpec,pNmlv->iSubItem);
		*pResult = CDRF_NOTIFYPOSTPAINT;
		break;
	case CDDS_ITEMPOSTPAINT | CDDS_SUBITEM:

		if(pNmlv->iSubItem == 2)
		{
			/*
			CRect crProg;
			m_List.GetSubItemRect(iItemIdx,2,LVIR_BOUNDS,crProg);
			crProg.OffsetRect(1,100);
			crProg.bottom-=1;
			//	crProg.top+=1;
			//crProg.left+=137;
			crProg.left+=140;
			crProg.DeflateRect(1,1);
			m_vectPrgssCtrl[iItemIdx]->MoveWindow(&crProg, false);
			*/
			if (!Computers[iItemIdx].Start || !Computers[iItemIdx].Rasch || !IsShowPrgss)
				m_vectPrgssCtrl[iItemIdx]->ShowWindow(SW_HIDE);
			else 
			{
				m_vectPrgssCtrl[iItemIdx]->ShowWindow(SW_NORMAL);
			}
				m_vectPrgssCtrl[iItemIdx]->RedrawWindow();

		}
		log.Format("CDDS_ITEMPOSTPAINT %i | CDDS_SUBITEM %i", iItemIdx,pNmlv->iSubItem);
		break;
	}
	TRACE(log+"\n");
}
// Инициализация списка рабочих станций



void CInetTarifDlg::InitWorkstation()
{
	// Lock all, установить все значения в default, определить к-во "живых" станций с непустыми именами
	CString str;
	iActivComp = 0;
	bool bConn;
	thr = 1;
//	double m_TimeLeft;
	for (int i=0; i<m_Setup.CountComp; i++)
	{
		str.Format("%s", m_Setup.CompName[i]);
		ClearComp(&Computers[i]);
		if ( m_Setup.bActiv[i] && str != "" )
		{
			Computers[iActivComp].NumbComp=i;
			sprintf (Computers[iActivComp].CompName, m_Setup.CompName[i]);


//!!!!!!!!!!!!!!!!!!!!!!!!
// Здесь запрашивается информация из рабочей станции

/*
			bConn = Zapros(iActivComp);//StopInet(iActivComp);
			if (bConn) // && EnableExplorer(iActivComp))
				Computers[iActivComp].Connected=true;
			else
				Computers[iActivComp].Connected=false;
			//LockStation(iActivComp);
*/			
			Computers[iActivComp].Connected=true;
			iActivComp++;

		}
	}

//!!!!!!!!!!!!!!!!!


char zalog[9];
// double tarif;

int m, comp, endfile;
		FILE* fp0 = fopen ("avans.ini", "rb");
		if (!fp0)
		{
			#ifdef _LOG_ITAR
				LogWrite ("Error writing avans.ini");
			#endif
			return;
		}
		fseek(fp0, 0, SEEK_END);
		endfile = ftell(fp0);
		CWnd* pWnd = GetDlgItem(IDC_ZALOG_UAH);
		CString sStr;
	if (endfile < 10) 
	{
		sStr = "0.00";
		pWnd->SetWindowText(sStr);
	}
	else
	{
		fseek(fp0, 0, SEEK_SET);
		Beep(1000,100);Sleep(50);
		Beep(1000,100);Sleep(50);
		Beep(1000,100);
		m = fread (zalog, 9, 1, fp0);
		if (m!=1)
		{
			#ifdef _LOG_ITAR
				LogWrite("avans.ini is corrupted");
			#endif
		}

	 	sStr = zalog;
		pWnd->SetWindowText(sStr);
	
	
		while (ftell(fp0) < endfile)
	{
//		TimeHistory = Computers[comp].DateTimeBeg.wSecond + Computers[comp].DateTimeBeg.wMinute*60 + Computers[comp].DateTimeBeg.wHour*3600
		m = fread (&comp, sizeof (INT), 1, fp0);
		m += fread (&Computers[comp].TPos, sizeof (INT), 1, fp0);
		m += fread (&Computers[comp].Zalog, sizeof (DOUBLE), 1, fp0);
		m += fread (&TimeHistory, sizeof (INT), 1, fp0);

		if (m!=4)
		{
			#ifdef _LOG_ITAR
				LogWrite("Avans.ini is corrupted");
			#endif
			break;
		}
//		bool t1 = Beep(3000,1000);
		
		GetLocalTime(&Computers[comp].DateTimeBeg);
		TimeCur = Computers[comp].DateTimeBeg.wSecond + Computers[comp].DateTimeBeg.wMinute*60 + Computers[comp].DateTimeBeg.wHour*3600;
		Computers[comp].DateTimeBeg.wHour = TimeHistory / 3600;
		Computers[comp].DateTimeBeg.wMinute = TimeHistory / 60 - Computers[comp].DateTimeBeg.wHour * 60;
		Computers[comp].DateTimeBeg.wSecond = TimeHistory - Computers[comp].DateTimeBeg.wMinute * 60 - Computers[comp].DateTimeBeg.wHour * 3600;
		Computers[comp].AllZalog = Computers[comp].Zalog;
		Computers[comp].Tarif = GetTarif (Computers[comp].TPos);
		int ElapceFull = Computers[comp].AllZalog / (Computers[comp].Tarif *  nds );
		Computers[comp].Elapce = TimeCur - TimeHistory;
		if (ElapceFull < Computers[comp].Elapce) Computers[comp].Elapce = ElapceFull;
		Computers[comp].Time = ElapceFull - Computers[comp].Elapce; 
		Computers[comp].Ostatok = Computers[comp].Time * (Computers[comp].Tarif  *  nds );
		if (Computers[comp].Elapce < 0) Computers[comp].Ostatok += (Computers[comp].Tarif  *  nds ) * Computers[comp].Elapce;
//		int time0 = Computers[comp].Elapce / 60;
/*		while(time0-- >= 0) if (Computers[comp].DateTimeBeg.wMinute-- == 0) 
		{
			Computers[comp].DateTimeBeg.wMinute = 59;
			if (Computers[comp].DateTimeBeg.wHour-- == 0) 
			{
				Computers[comp].DateTimeBeg.wHour = 23;
			}
		}
*/
// Передача для синхронизации сеанса:
/*
		if(Computers[comp].Rasch == true)	
			if(!StartInet(comp))
			{
				char msg[100];
				sprintf(msg,"Не удалось связаться со станцией №%i", Computers[comp].NumbComp+1);
				MessageBox(msg,"Ошибка",MB_OK|MB_ICONERROR);
				// 20.05.2009
//				StopSeance(comp);
			}
*/
//			if(Computers[comp].Rasch == 0) StopSeance(comp);
		

		Computers[comp].Start = true;
		Computers[comp].Rasch = true;
		Computers[comp].Connected=true;
	}
	}
	fclose(fp0);


	thr = 0;

	GlobalWTime = 360;
	GLT = 10;


}
// Инициализация линейки для каждого компа
bool CInetTarifDlg::myProgInit(int vis)
{
	m_vectPrgssCtrl.clear();
	m_vectPrgssCtrl.reserve(m_List.GetItemCount());
	for (int i=0; i<m_List.GetItemCount(); i++)
	{
		// push_back adds an element to the end of the vector
		m_vectPrgssCtrl.push_back(new CProgressCtrl());
		//Creates a progress bar control and attaches it to a CProgressCtrl object m_vectPrgssCtrl[i]
		// 300+i Specifies the progress bar control's ID. 
		m_vectPrgssCtrl[i]->Create(WS_CHILD|PBS_SMOOTH, CRect(0,0,0,0), this, 300+i);
//!!!!!!!!!!!		
		//m_vectPrgssCtrl[i]->SetPos(i*2);
		//27.05.2009
		m_vectPrgssCtrl[i]->ShowWindow(SW_HIDE);
		CRect rectPrgss;
		m_List.GetSubItemRect(i, 2, LVIR_BOUNDS, rectPrgss);
		rectPrgss.OffsetRect(1,100);
		rectPrgss.bottom-=1;
		rectPrgss.left+=vis*12;
		rectPrgss.DeflateRect(1,1);
		m_vectPrgssCtrl[i]->MoveWindow(&rectPrgss, false);
		//
//		m_vectPrgssCtrl[i]->ShowWindow(SW_HIDE);
		//m_vectPrgssCtrl[i]->SetPos(0);
		//m_vectPrgssCtrl[i]->ShowWindow(SW_SHOWNORMAL);
		//m_vectPrgssCtrl[i]->RedrawWindow();
		//
	}
	return true;
}

// MENU: Выход оператора без закрытия приложения
void CInetTarifDlg::OnLogoff() 
{
	try
	{
		for (int i=0; i<iActivComp; i++) 
		{
			if ( Computers[i].Rasch == true )
			{
				MessageBox("У Вас есть нерассчитанные станции.\nРассчитайте их перед приостановкой работы.",
					"Завершение работы Тарификатора",MB_OK|MB_ICONINFORMATION);
				return;
			}
		}
		if (MessageBox("Вы собираетесь приостановить работу. Вы уверены?", 
			"Предупреждение", MB_YESNO|MB_ICONQUESTION|MB_TOPMOST|MB_SETFOREGROUND )==IDYES)
		{
			// UnLock 
			for (int i=0; i<iActivComp; i++)
			{
				StopInet(i);
				//UnLockStation(i);
				DisableExplorer(i);
				//ShootDown(i);
			}
			#ifdef _LOG_ITAR
				LogWrite ("Inet Tarificator is paused.\n");
			#endif
			// Destroys a modal dialog box.
			// nRetCode - [in] The value to be returned by CDialogImpl::DoModal. 
			EndDialog(5);	                  
		}
	}
	catch(...)
	{
		MessageBox("Возникла ошибка при выполнении пункта меню.\nОтправьте журнал работы ПП разработчику.",
			"Ошибка",MB_OK|MB_ICONSTOP);
		char Buffer[200];
		DWORD err = GetLastError();
		if (err)
			sprintf(Buffer,"Ошибка в CInetTarifDlg::OnLogoff # %d", err);
		else
			sprintf(Buffer,"Ошибка в CInetTarifDlg::OnLogoff");
		LogWrite(Buffer);
	}
	return;
}

// MENU Смена оператора без завершения работы станций
void CInetTarifDlg::OnSmena() 
{
	try
	{
		char TempFio[50];
		strcpy(TempFio, UInfo.Fio);
		if (theApp.EnterSystem())
		{
			#ifdef _LOG_ITAR
				sprintf (LogBuffer, "Changing operator from %s to %s", TempFio, UInfo.Fio);
				LogWrite (LogBuffer);
			#endif
			UpdateWindow();

			char UserName[100],Name[200];
			unsigned long nSize = 100;
			GetComputerName( UserName, &nSize);
			sprintf( Name, "Internet Tarificator Server (%s) - %s", UserName, UInfo.Fio);
			SetWindowText (Name);



			// 08.12.2009
			SetMenu(&theApp.TempMenu);
			DrawMenuBar();
		}
	}
	catch(...)
	{
		MessageBox("Возникла ошибка при выполнении пункта меню.\nОтправьте журнал работы ПП разработчику.",
			"Ошибка",MB_OK|MB_ICONSTOP);
		char Buffer[200];
		DWORD err = GetLastError();
		if (err)
			sprintf(Buffer,"Ошибка в CInetTarifDlg::OnSmena # %d", err);
		else
			sprintf(Buffer,"Ошибка в CInetTarifDlg::OnSmena");
		LogWrite(Buffer);
	}
}
// MENU: ID_COM Настройка параметров, в т.ч. описания станций
void CInetTarifDlg::OnCom() 
{
	// Проверка
	for (int i=0; i<iActivComp; i++) 
	{
		if (Computers[i].Start == true)
		{
			MessageBox("У Вас есть нерассчитанные станции.\nРассчитайте их перед настройкой параметров.",
				"Настройка параметров",MB_OK|MB_ICONINFORMATION);
			return;
		}
	}
	//
	for (int Comp=0; Comp<iActivComp; Comp++)
	{
		StartInet(Comp);
		//EnableExplorer(Comp);
	}
	try
	{
		CComSetupDlg ComDlg;
		ComDlg.DoModal();
	}
	catch(...)
	{
		MessageBox("Возникла ошибка при выполнении пункта меню.\nОтправьте журнал работы ПП разработчику.",
			"Ошибка",MB_OK|MB_ICONSTOP);
		char Buffer[200];
		DWORD err = GetLastError();
		if (err)
			sprintf(Buffer,"Ошибка в классе CComSetupDlg(CInetTarifDlg::OnCom) # %d", err);
		else
			sprintf(Buffer,"Ошибка в классе CComSetupDlg(CInetTarifDlg::OnCom)");
		LogWrite(Buffer);
	}
	// Lock
	for (int  i=0; i<iActivComp; i++)
		LockStation(i);

	// Инициализация списка рабочих станций
	InitWorkstation();
	// Установить к-во строк списка станций
	m_List.SetItemCount(iActivComp);
	// Инициализация линейки для каждого компа
	CRect rect;
	GetClientRect(&rect);
	myProgInit(rect.Width()/32);
}
// MENU Продажа доп.услуг
void CInetTarifDlg::OnChek()
{
	long lSum = 0;
	try
	{
		ChekDlg Chek;
		Chek.DoModal();
		lSum = Chek.SumOpl;
		if (lSum != 0)
			ShowRaschSum(0, lSum);
	}
	catch(...)
	{
		MessageBox("Возникла ошибка при выполнении пункта меню.\nОтправьте журнал работы ПП разработчику.",
			"Ошибка",MB_OK|MB_ICONSTOP);
		char Buffer[200];
		DWORD err = GetLastError();
		if (err)
			sprintf(Buffer,"Ошибка в классе ChekDlg # %d", err);
		else
			sprintf(Buffer,"Ошибка в классе ChekDlg");
		LogWrite(Buffer);
	}
	char cStr[100];
	sprintf(cStr, "Продана дополнительная услуга на сумму %.2f грн.", (float)lSum/100 );
//	m_StatusBar.SetText(cStr, 1, 0);
}
// MENU 
void CInetTarifDlg::OnRemovepssbr()
{
	// Get the popup menu which contains the "Toggle State" menu item.
	CMenu* mmenu = GetMenu();
	CMenu* submenu = mmenu->GetSubMenu(2);
	// Check the state of the "Toggle State" menu item. Check the menu item
	// if it is currently unchecked. Otherwise, uncheck the menu item
	// if it is not currently checked.
	UINT state = submenu->GetMenuState(ID_REMOVEPSSBR, MF_BYCOMMAND);
	ASSERT(state != 0xFFFFFFFF);
	if (state & MF_CHECKED)
	{
		submenu->CheckMenuItem(ID_REMOVEPSSBR, MF_UNCHECKED | MF_BYCOMMAND);
		IsShowPrgss = true;
	}
	else
	{
		submenu->CheckMenuItem(ID_REMOVEPSSBR, MF_CHECKED | MF_BYCOMMAND);
		IsShowPrgss = false;
	}
}



//void CInetTarifDlg::OnStnClickedZalogUah()
//{
//	// TODO: добавьте свой код обработчика уведомлений
//}

//void CInetTarifDlg::OnStnClickedPrinUah()
//{
//	// TODO: добавьте свой код обработчика уведомлений
//}


void CInetTarifDlg::OnSize(UINT nType, int cx, int cy)
{
 CDialog::OnSize(nType, cx, cy);
 
	if(cx < 570) 
		SetWindowPos(GetActiveWindow(),0,0,580,my,SWP_NOMOVE|SWP_NOZORDER);

	if(abs(cx-mx)>10 || abs(cy-my)>10)  
	if (m_List)
	{
		int myW;
		resiz = 0;

		mx = cx;
		my = cy; 
		CRect rect;
		m_List.ShowWindow(SW_HIDE);
		GetClientRect(&rect);
		ListRct.SetRect(3,100,rect.Width()-3,rect.Height()-3);
		m_List.MoveWindow(ListRct);
		myW = ListRct.Width();
		
		m_List.SetColumnWidth(0,0.4*myW/10);
		m_List.SetColumnWidth(2,4.6*myW/10);
		m_List.SetColumnWidth(3, 1.9*myW/10);
		m_List.SetColumnWidth(4,1.3*myW/10);
		m_List.SetColumnWidth(5, 1.5*myW/10);
		CFont *font = new CFont();
		VERIFY(font->CreateFont(
		myW/32,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		TRUE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		DEFAULT_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		"Arial"));                 // lpszFacename
		m_List.SetFont(font);
		m_List.ShowWindow(SW_SHOW);


	for (int i=0; i<m_List.GetItemCount(); i++)
	{

		m_vectPrgssCtrl[i]->ShowWindow(SW_HIDE);
		CRect rectPrgss;
		m_List.GetSubItemRect(i, 2, LVIR_BOUNDS, rectPrgss);
		rectPrgss.OffsetRect(1,100);
		rectPrgss.bottom-=1;
		rectPrgss.left+=myW*12/32;
		rectPrgss.DeflateRect(1,1);
		m_vectPrgssCtrl[i]->MoveWindow(&rectPrgss, false);
		//
//		m_vectPrgssCtrl[i]->ShowWindow(SW_HIDE);
		//m_vectPrgssCtrl[i]->SetPos(0);
		//m_vectPrgssCtrl[i]->ShowWindow(SW_SHOWNORMAL);
		//m_vectPrgssCtrl[i]->RedrawWindow();
		//
	}




		resiz = 1;


	}
	// TODO: добавьте свой код обработчика сообщений
}

void CInetTarifDlg::OnStnClickedPrinUah()
{
	// TODO: добавьте свой код обработчика уведомлений
}

void CInetTarifDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
//	CDialog::OnShowWindow(bShow, nStatus);
	CString pn = m_Setup.PathName;
	if (pn.IsEmpty()) pn = ".";
	pn +=	"\\inettarif.hlp";
	HlpGlobal = fopen ((char*)(LPCSTR) pn, "ab");
	if (!HlpGlobal)
	{
		MessageBox("Не удалось открыть файл помощи.","Ошибка", MB_OK|MB_ICONERROR);
  	    OnOK();
	    return;
	}
/*	//UpdateWindow();
	char UserName[100],Name[200];
	unsigned long nSize = 100;
	GetComputerName( UserName, &nSize);
	sprintf( Name, "Internet Tarificator Server (%s) - %s", UserName, UInfo.Fio);
	SetWindowText (Name);
	SetMenu(&theApp.TempMenu);
	DrawMenuBar();
*/
	// TODO: добавьте свой код обработчика сообщений
}
