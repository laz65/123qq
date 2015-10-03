// wLocker.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include "ipdll.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <shellapi.h>
#include <winuser.h>

//#include <h.h>

//extern HANDLE hDrv;

#define MAX_LOADSTRING 100

// Fedorov I.L.14.11.07
#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))


PMIB_IPFORWARDTABLE pIpForwardTable;
DWORD dwSize = 0;
DWORD dwRetVal = 0;
bool fl;
struct in_addr IpAddr;

// End 14.11.07

// Global Variables:
HINSTANCE hInst;                                                                // current instance
TCHAR szTitle[MAX_LOADSTRING];                                                          // The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];                                                            // The title bar text
char Text2Out[200];

HWND hWnd;
HWND hTarifWnd;
DWORD  threadID;                     // Used for CreateThread().
MIB_IPFORWARDROW pRoute;
IpDLL IP("iphlpapi.dll");

RECT lpRect;
int Count, off;
int Begin;


TCHAR                                   GateWay[200];
bool									GateWayOn;
TCHAR                                   TimeLeft[200];
TCHAR                                   TarifName[200];
TCHAR                                   cmdLine[200];

int m_TimeLeft=0;

STARTUPINFO             killer_si;    
PROCESS_INFORMATION     killer_pi;    
STARTUPINFO             window_si;    
PROCESS_INFORMATION     window_pi;    

#define DEFAULT_PORT 16661
#define DEFAULT_PROTO SOCK_STREAM // TCP

char *_interface= NULL;
unsigned short port=DEFAULT_PORT;
int retval;
int fromlen;
int i;
int socket_type = DEFAULT_PROTO;
struct sockaddr_in local, from;
WSADATA wsaData;
SOCKET listen_socket, msgsock;
////////////////////////////////////////////////////////////////////
RECT gl_rt;
RECT Rect;
RECT rt;

////////////////////////////////////////////////////////////////////
BOOL MySystemShutdown(UINT uFlags)
{
//	StopDriver();
	HANDLE hToken;
   TOKEN_PRIVILEGES tkp;

   // Получаем маркер текущего процесса.

   if (!OpenProcessToken(GetCurrentProcess(),
        TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
      return( FALSE );

   // Получаем LUID для привелегии завершения работы.

   LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,
        &tkp.Privileges[0].Luid);
 
   tkp.PrivilegeCount = 1;  // будет установлена одна привелегия
   tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

   // Получаем привелегию завершения работы для этого процесса.

   AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,
        (PTOKEN_PRIVILEGES)NULL, 0);

   if (GetLastError() != ERROR_SUCCESS)
      return FALSE;

   // Шутдауним систему и заставляем все приложения закрыться.

   if (!ExitWindowsEx(uFlags, 0))
      return FALSE;

   return TRUE;
}
void PowerOFF(void)
  {
    HANDLE hToken;
    TOKEN_PRIVILEGES* NewState;
    OSVERSIONINFO OSVersionInfo;

    OSVersionInfo.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
    GetVersionEx (&OSVersionInfo);
    if (OSVersionInfo.dwPlatformId == VER_PLATFORM_WIN32_NT)
    {
        OpenProcessToken (GetCurrentProcess (), TOKEN_ADJUST_PRIVILEGES, &hToken);
        NewState = (TOKEN_PRIVILEGES*) malloc (sizeof (TOKEN_PRIVILEGES) + sizeof (LUID_AND_ATTRIBUTES));
        NewState->PrivilegeCount = 1;
        LookupPrivilegeValue (NULL, SE_SHUTDOWN_NAME, &NewState->Privileges[0].Luid);
        NewState->Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
        AdjustTokenPrivileges (hToken, FALSE, NewState, NULL, NULL, NULL);
        free (NewState);
        CloseHandle (hToken);
      }

    ExitWindowsEx (EWX_POWEROFF , 0);
	PostQuitMessage(0);
    //ExitWindowsEx (EWX_SHUTDOWN , 0);
  }



/*
*/
/////////////////////////////////////////////////////////////////////////
void Proccess (char *);
void CALLBACK TimerFunc(HWND hwnd,UINT uMsg,UINT_PTR idEvent, DWORD dwTime)

{

        if (idEvent==6666)//Disable Mouse
        {
                Rect.left=GetSystemMetrics(SM_CXSCREEN)/2;
                Rect.right=Rect.left;
                Rect.top=GetSystemMetrics(SM_CYSCREEN)/2;
                Rect.bottom=Rect.top;

                ClipCursor (&Rect);
                ShowCursor(false);
        }

        if (idEvent==6667)//Show Window
        {

		
                Rect.left=0;
                Rect.right=GetSystemMetrics(SM_CXSCREEN);
                Rect.top=0;
                Rect.bottom=GetSystemMetrics(SM_CYSCREEN);

                EnableWindow (hwnd, false);
                SetWindowPos (hwnd, HWND_TOPMOST, 0 ,0 ,Rect.right , Rect.bottom, 0);
                UpdateWindow(hwnd);
				InvalidateRect(hwnd, NULL, false);

        }


        if (idEvent==6668)// Tarif Window
        {


                m_TimeLeft --;
                if (m_TimeLeft <= 0 ) m_TimeLeft = 0;
				if (!GateWayOn)
				{
				    IP.DeleteIpForwardEntry(&pRoute);
				};
				if((off == 1) || (off == 2))
				{
					Proccess("sta1k HZ,DG,SW");
				}
//				if (off == 2) off = 1;
//!!!!!!!!!!!!!!!!!!!!!!!!
								int m;
								FILE* fp = fopen ("vrem.ini", "wb");
								if (!fp)
								{
									#ifdef _LOG_ITAR
										LogWrite ("Error writing Users.ini");
									#endif
									
								}
								else
								{
								m = fwrite (&m_TimeLeft, sizeof (INT), 1, fp);
								m += fwrite (&off, sizeof (INT), 1, fp);
								m += fwrite (&TarifName, 200, 1, fp);
								m += fwrite (&GateWayOn, sizeof (BOOL), 1, fp);

								if (m!=4)
								{
									#ifdef _LOG_ITAR
										LogWrite("Error writing avans.ini");
									#endif
									
								}
								fclose(fp);
								}

//!!!!!!!!!!!!!!!!!!!!
								
								if (m_TimeLeft <= 0 )
								{
									Beep(1600,100); Sleep(50);
									Beep(1500,100); Sleep(50);
									Beep(1400,100); Sleep(50);
									Beep(1300,100); Sleep(50);
									Beep(1200,100); Sleep(50);
									Beep(1100,100); Sleep(50);
									Beep(1000,100); Sleep(50);
									Beep(900,100); Sleep(50);
									Beep(800,100);
								}
								else
								{
									if (m_TimeLeft <= 5 )  
									{
										Beep(1200,200);	
										Beep(1100,200);
									}
									if (m_TimeLeft <= 3 )  
									{
										Beep(1000,200);	
										Beep(900,200);
									}
									if (m_TimeLeft <= 1 )  
									{
										Beep(800,200);	
										Beep(700,200);
									}
								}
                
                UpdateWindow(hwnd);
				InvalidateRect(hwnd, NULL, false);


        }

}

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
char LogBuffer[300];

/////////////////////////////////////////////////////////////////////////////
void LogWrite(char *text)
{

        FILE *log;
        log = fopen ("wlocker.log" , "at");
        char LogBuffer[200];
        SYSTEMTIME lpSystemTime;
        GetLocalTime(&lpSystemTime);

        sprintf (LogBuffer, "%02d:%02d:%02d. %s\n", lpSystemTime.wHour, lpSystemTime.wMinute, lpSystemTime.wSecond, text);
        fprintf (log, "%s", LogBuffer);
        fclose (log);

}
//bool status;
							
/////////////////////////////////////////////////////////////////////////////
void Proccess (char *Buffer)
{

        char szIn[300];
	
        strcpy (szIn, Buffer);


/*
DK - Disable Keyboard
EK - Enable Keyboard

DM - Disable Mouse
EM - Enable Mouse

DW - Disable Windows (Program Manager, Shell_Tray)
EW - Enable Windows

SW - Show Window
HW - Hide Window

ED - Run Killer.exe
EE - Close Killer.exe

AG Name - Add GateWay 
DG - Disable GateWay

EB - Show MessageBox
DB - Close MessageBox

SZ - Show Zalog Window
HZ - Hide Zalog Window

PO - Power OFF

RN - Run file (*.cmd, *.bat, *.exe) Изменение от 27.10.2007 Фёдоров И.Л.
*/


                Count=0;
                Begin=0;

                if (strlen(szIn)<5)
                        return;

                if (memcmp (szIn, "sta1k", 5)!=0)
                        return;


                memcpy (szIn, Buffer+5, strlen(szIn)-4);
                sprintf (LogBuffer, "Proccess with string - %s", szIn);
                LogWrite (LogBuffer);

                while (_tcscmp(szIn, "")!=0)
                {

                        while (((Buffer[Count]==' ')||(Buffer[Count]==','))&&(Count<(int)_tcslen(Buffer))) 
                                Count++;
        
                        Begin=Count;    

                        while ((Buffer[Count]!=' ')&&(Buffer[Count]!=',')&&(Count<(int)_tcslen(Buffer)))  
                                Count++;

                        memcpy (szIn, Buffer+Begin, Count-Begin);
                        szIn[Count-Begin]='\0';

                        if (_tcscmp(szIn, "EX")==0)
						{
							sprintf (LogBuffer, "Выгрузка локера!!!");
							LogWrite (LogBuffer);
							exit(0);
						}
						else
						if (_tcscmp(szIn, "PO")==0)
						{
							//PowerOFF();
							if(MySystemShutdown(EWX_SHUTDOWN | EWX_FORCE)){
								sprintf (LogBuffer, "Выключение станции!!!");
							}else sprintf (LogBuffer, "Oшибка выключения станции: %i", GetLastError());
							LogWrite (LogBuffer);
						}
						else
						if (_tcscmp(szIn, "RS")==0)
						{						
							if(MySystemShutdown(EWX_REBOOT | EWX_FORCE)){
								sprintf (LogBuffer, "Перезагрузка станции!!!");
							}else sprintf (LogBuffer, "Oшибка перезгрузки станции: %i", GetLastError());
							LogWrite (LogBuffer);

						}
						else
                        if (_tcscmp(szIn, "DK")==0)
                        {
                                LogWrite ("Disable Keyboard.");
                                
                                int alt,vk;
                                for(alt=0;alt<16;alt++) {
                                        for(vk=0x5;vk<=0x5D;vk++) {
                                                RegisterHotKey(NULL,1000+(alt*0x100)+vk,alt,vk);
                                        }
                                }
                        }
                        else
                        if (_tcscmp(szIn, "EK")==0)
                        {
                                LogWrite ("Enable Keyboard.");
                                int alt, vk;
                                for(alt=0;alt<16;alt++) {
                                        for(vk=0x5;vk<=0x5D;vk++) {
                                                UnregisterHotKey(NULL,1000+(alt*0x100)+vk);
                                        }
                                }
                        }
                        else
                        if (_tcscmp(szIn, "DM")==0)
                        {
                                LogWrite ("Disable Mouse.");
                                ShowCursor(false);
								SetTimer(hWnd, 6666, 100, (TIMERPROC )TimerFunc);
                        }
                        else
                        if (_tcscmp(szIn, "EM")==0)
                        {
                                LogWrite ("Enable Mouse.");
        
                                RECT Rect;
                                Rect.left=0;
                                Rect.right=GetSystemMetrics(SM_CXSCREEN);
                                Rect.top=0;
                                Rect.bottom=GetSystemMetrics(SM_CYSCREEN);
                                KillTimer (hWnd, 6666);

                                ShowCursor(true);
                                ClipCursor (NULL);
                                ShowCursor(true);
                                ClipCursor (NULL);

                                //keybd_event (VK_CONTROL, 0,0,0);
                                //keybd_event (VK_ESCAPE, 0,0,0);
                                //keybd_event (VK_ESCAPE, 0,KEYEVENTF_KEYUP,0);
                                //keybd_event (VK_CONTROL, 0,KEYEVENTF_KEYUP,0);

                                //mouse_event (MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_ABSOLUTE, 10,10,0,0);
                                //mouse_event (MOUSEEVENTF_LEFTUP|MOUSEEVENTF_ABSOLUTE, 10,10,0,0);
                        }
                        else
                        if (_tcscmp(szIn, "EW")==0)
                        {
                                LogWrite ("Enable Windows.");
                                HWND hWnd_DeskTop=FindWindow(NULL,"Program Manager");
                                HWND hWnd_Tray=FindWindow("Shell_TrayWnd",NULL);
                                EnableWindow (hWnd_Tray, TRUE);
                                EnableWindow (hWnd_DeskTop, TRUE);
                        }
                        else
                        if (_tcscmp(szIn, "DW")==0)
                        {
                                LogWrite ("Disable Windows.");
                                HWND hWnd_DeskTop=FindWindow(NULL,"Program Manager");
                                HWND hWnd_Tray=FindWindow("Shell_TrayWnd",NULL);
                                EnableWindow (hWnd_Tray, FALSE);
                                EnableWindow (hWnd_DeskTop, FALSE);
                        }
                        else
                        if (_tcscmp(szIn, "AG")==0)
                        {
                                
							while (((Buffer[Count]==' ')||(Buffer[Count]==','))&&(Count<(int)_tcslen(Buffer)))
                                        Count++;

                                Begin=Count;

                                while ((Buffer[Count]!=' ')&&(Buffer[Count]!=',')&&(Count<(int)_tcslen(Buffer)))
                                        Count++;

                                memcpy (GateWay, Buffer+Begin, Count-Begin);
                                GateWay[Count-Begin]='\0';
								GateWayOn = TRUE;

                                //sprintf (cmdLine, "add 0.0.0.0 mask 0.0.0.0 %s", GateWay);
                                //ShellExecute (NULL, NULL, "route.exe", cmdLine, NULL, SW_HIDE);
								
								pRoute.dwForwardNextHop = inet_addr(GateWay);
								char log[100];
								LPVOID lpMsgBuf;
								FormatMessage(
								FORMAT_MESSAGE_ALLOCATE_BUFFER |
								FORMAT_MESSAGE_FROM_SYSTEM |
								FORMAT_MESSAGE_IGNORE_INSERTS,
								NULL,
								IP.CreateIpForwardEntry(&pRoute),
								MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
								(LPTSTR) &lpMsgBuf, 0, NULL);

								sprintf(log, "Add GateWay. Message:%s", lpMsgBuf);
                                LogWrite (log);
								LocalFree(lpMsgBuf);

                        }
                        else
                        if (_tcscmp(szIn, "DG")==0)
                        {
							
								char log[100];
								LPVOID lpMsgBuf;
								FormatMessage(
								FORMAT_MESSAGE_ALLOCATE_BUFFER |
								FORMAT_MESSAGE_FROM_SYSTEM |
								FORMAT_MESSAGE_IGNORE_INSERTS,
								NULL,
								IP.DeleteIpForwardEntry(&pRoute),
								MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
								(LPTSTR) &lpMsgBuf, 0, NULL);

								sprintf(log, "Disable GateWay. Message:%s", lpMsgBuf);
                                LogWrite (log);
								LocalFree(lpMsgBuf);
								GateWayOn = FALSE;
                                //ShellExecute (NULL, NULL, "route.exe", "delete 0.0.0.0", NULL, SW_HIDE);
						}
                        else
                        if (_tcscmp(szIn, "SW")==0)
                        {

                                LogWrite ("Show Window.");
/*                                keybd_event (VK_CONTROL, 0,0,0);
                                keybd_event (VK_ESCAPE, 0,0,0);
                                keybd_event (VK_ESCAPE, 0,KEYEVENTF_KEYUP,0);
                                keybd_event (VK_CONTROL, 0,KEYEVENTF_KEYUP,0);
*/
                                //Sleep (3000);
								ShellExecute (NULL, "open", "cmd.exe", "/K bat.cmd", NULL, SW_HIDE);
								fl = 0;
								ShowWindow (hWnd , SW_SHOW);
								UpdateWindow(hWnd);
								InvalidateRect(hWnd, NULL, false);
                                SetTimer(hWnd, 6667, 1000, (TIMERPROC)TimerFunc);
								SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, 1);

                        }
                        else
                        if (_tcscmp(szIn, "HW")==0)
                        {       
								//off = 0;
                                LogWrite ("Hide Window.");
                                ShowWindow (hWnd , SW_HIDE);
                                KillTimer (hWnd, 6667);

                        }
                        else
                    /*if (_tcscmp(szIn, "DL")==0)
                        {
							int Address=888;
							if (status==false)
							{
								LogWrite("Error! Can't open driver LPT !");
							}else{
								WriteToPort(Address, 0);
								LogWrite("Write 0 to LPT !");
							}
                        }
                        else
                        if (_tcscmp(szIn, "EL")==0)
                        {
							int Address=888;
							if (status==false)
							{
								LogWrite("Error! Can't open driver LPT !");
							}else{
								WriteToPort(Address, 1);
								LogWrite("Write 1 to LPT !");
							}
                        }
                        else*/
                        if (_tcscmp(szIn, "EB")==0)
                        {
                                LogWrite ("Message Box.");
                                MessageBox (NULL , "Ваш лимит заканчивается! Заплатите в кассу залог.", "Inet Warning", MB_OK);
                        }
                        else
                        if (_tcscmp(szIn, "DB")==0)
                        {
                                LogWrite ("Message Box.");
                                HWND hWnd_Window1=FindWindow(NULL,"Inet Warning");
                                HWND hWnd_Window2=FindWindow("Inet Warning",NULL);      

                                EnableWindow (hWnd_Window1, TRUE);
                                EnableWindow (hWnd_Window2, TRUE);

                                DestroyWindow(hWnd_Window1);
                                DestroyWindow(hWnd_Window2);

                                SendMessage (hWnd_Window1, WM_CLOSE, 0,0);
                                SendMessage (hWnd_Window2, WM_CLOSE, 0,0);
                        }
                        else
                        if (_tcscmp(szIn, "SZ")==0)
                        {

                                LogWrite ("Show Tarif Window.");
//                              keybd_event (VK_CONTROL, 0,0,0);
//                              keybd_event (VK_ESCAPE, 0,0,0);
//                              keybd_event (VK_ESCAPE, 0,KEYEVENTF_KEYUP,0);
//                              keybd_event (VK_CONTROL, 0,KEYEVENTF_KEYUP,0);
								off = 0;

                                while (((Buffer[Count]==' ')||(Buffer[Count]==','))&&(Count<(int)_tcslen(Buffer))) 
                                        Count++;
        
                                Begin=Count;    
        
                                while ((Buffer[Count]!='-')&&(Count<(int)_tcslen(Buffer)))  
                                        Count++;

                                memcpy (TarifName, Buffer+Begin, Count-Begin);
                                TarifName[Count-Begin]='\0';

                                while (((Buffer[Count]==' ')||(Buffer[Count]==','))&&(Count<(int)_tcslen(Buffer))) 
                                        Count++;
        
                                Begin=Count+1;    
        
                                while ((Buffer[Count]!=' ')&&(Buffer[Count]!=',')&&(Count<(int)_tcslen(Buffer)))  
                                        Count++;

                                memcpy (TimeLeft, Buffer+Begin, Count-Begin);
                                TimeLeft[Count-Begin]='\0';

                                m_TimeLeft = atoi (TimeLeft);

                                //Sleep (3000);

                                ShowWindow (hTarifWnd , SW_SHOW);
                                SetWindowPos (hTarifWnd , HWND_TOPMOST, 100 ,0 , 600 , 20, 0);

                                
								UpdateWindow(hTarifWnd);
								InvalidateRect(hTarifWnd, NULL, false);

                               
                                SetTimer(hTarifWnd, 6668, 60000, (TIMERPROC)TimerFunc);
								Beep(800,100);
								//!!!!!!!!!!!!!!!!!!!!!!!!
								int m;
								FILE* fp = fopen ("vrem.ini", "wb");
								if (!fp)
								{
									#ifdef _LOG_ITAR
										LogWrite ("Error writing Users.ini");
									#endif
									
								}
								else
								{
								m = fwrite (&m_TimeLeft, sizeof (INT), 1, fp);
								m += fwrite (&off, sizeof (INT), 1, fp);
								m += fwrite (&TarifName, 200, 1, fp);
								m += fwrite (&GateWayOn, sizeof (BOOL), 1, fp);

								if (m!=4)
								{
									#ifdef _LOG_ITAR
										LogWrite("Error writing avans.ini");
									#endif
									
								}
								fclose(fp);
								}
								Beep(1200,100);

                        }
                        else
                        if (_tcscmp(szIn, "HZ")==0)
                        {       

                                LogWrite ("Hide Tarif Window.");
                                ShowWindow (hTarifWnd , SW_HIDE);
                                KillTimer (hTarifWnd, 6668);
//!!!!!
								off = 1;
								//m_TimeLeft = 0;
								int m;
								FILE* fp = fopen ("vrem.ini", "wb");
								if (!fp)
								{
									#ifdef _LOG_ITAR
										LogWrite ("Error writing Users.ini");
									#endif
									
								}
								else
								{
								m = fwrite (&m_TimeLeft, sizeof (INT), 1, fp);
								m += fwrite (&off, sizeof (INT), 1, fp);
								m += fwrite (&TarifName, 200, 1, fp);
								m += fwrite (&GateWayOn, sizeof (BOOL), 1, fp);

								if (m!=4)
								{
									#ifdef _LOG_ITAR
										LogWrite("Error writing avans.ini");
									#endif
									
								}
								fclose(fp);
								}
								Beep(1200,100);
								Beep(800,100);

                        }
						else
							//Изменение от 27.10.2007 Фёдоров И.Л.
						if (_tcscmp(szIn, "RN")==0)
                        {
                                while (((Buffer[Count]==' ')||(Buffer[Count]==','))&&(Count<(int)_tcslen(Buffer))) 
                                        Count++;
        
                                Begin=Count;    
        
                                while ((Buffer[Count]!=' ')&&(Buffer[Count]!=',')&&(Count<(int)_tcslen(Buffer)))  
                                        Count++;

                                memcpy (GateWay, Buffer+Begin, Count-Begin);
                                GateWay[Count-Begin]='\0';
								GateWayOn = TRUE;
									//Изменения от 26,10,07 Фёдоров И.Л.
                                sprintf (cmdLine, "%s", GateWay);
                                char log[100];
								sprintf (log, "Запуск %s", cmdLine);
								ShellExecute (NULL, NULL, cmdLine, "", NULL, SW_HIDE);
									//
								//pRoute.dwForwardNextHop = inet_addr(GateWay);
								
								//LPVOID lpMsgBuf;
								//FormatMessage( 
								//FORMAT_MESSAGE_ALLOCATE_BUFFER | 
								//FORMAT_MESSAGE_FROM_SYSTEM | 
								//FORMAT_MESSAGE_IGNORE_INSERTS,
								//NULL,
								//IP.CreateIpForwardEntry(&pRoute),
								//MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
								//(LPTSTR) &lpMsgBuf, 0, NULL);

								//sprintf(log, "Add GateWay. Message:%s", lpMsgBuf);
                                LogWrite (log);							
								//LocalFree(lpMsgBuf);

                        }
						else
//!!!!!!!!						// Изменения от 16.02.2013 Лазебник
						if (_tcscmp(szIn, "AS")==0)
                        {
							if(GateWayOn)
								sprintf(Buffer,"ser1k AG %d,%d",m_TimeLeft, off); //
							else sprintf(Buffer,"ser1k DG %d,%d",m_TimeLeft, off);//
                        }

                        
                       


                }

}

/**************************************************************/

LPTSTR                  lpszPipeName = TEXT("friglays");
HANDLE                  hPipe = INVALID_HANDLE_VALUE;
HANDLE                  hEvents[2] = {NULL, NULL};
OVERLAPPED              os;
PSECURITY_DESCRIPTOR    pSD = NULL;
SECURITY_ATTRIBUTES     sa;
TCHAR                   szIn[80];
TCHAR                   szOut[80];
LPTSTR                  lpszPipePath = TEXT("\\\\.\\pipe\\");
BOOL                    bRet;
DWORD                   cbRead;
DWORD                   cbWritten;
DWORD                   dwWait;
UINT                    ndx;
HANDLE  hServerStopEvent = NULL;

/**************************************************************/

/*
int CiclePipe ()
{
	
    char Buffer[300];
    while ( 1 )
    {
        // init the overlapped structure
        //
        memset( &os, 0, sizeof(OVERLAPPED) );
        os.hEvent = hEvents[1];
        ResetEvent( hEvents[1] );

        // wait for a connection...
        //
        ConnectNamedPipe(hPipe, &os);

        if ( GetLastError() == ERROR_IO_PENDING )
        {
            dwWait = WaitForMultipleObjects( 2, hEvents, FALSE, INFINITE );
            if ( dwWait != WAIT_OBJECT_0+1 )     // not overlapped i/o event - error occurred,
                continue;                           // or server stop signaled
        }

        // init the overlapped structure
        //
        memset( &os, 0, sizeof(OVERLAPPED) );
        os.hEvent = hEvents[1];
        ResetEvent( hEvents[1] );

        // grab whatever's coming through the pipe...
        //
        bRet = ReadFile(
                    hPipe,          // file to read from
                    Buffer,           // address of input buffer
                    sizeof(Buffer),   // number of bytes to read
                    &cbRead,        // number of bytes read
                    &os);           // overlapped stuff, not needed

        if ( !bRet && ( GetLastError() == ERROR_IO_PENDING ) )
        {
            dwWait = WaitForMultipleObjects( 2, hEvents, FALSE, INFINITE );
            if ( dwWait != WAIT_OBJECT_0+1 )     // not overlapped i/o event - error occurred,
                continue;                           // or server stop signaled
        }



        Proccess (Buffer);


        // init the overlapped structure
        //
        memset( &os, 0, sizeof(OVERLAPPED) );
        os.hEvent = hEvents[1];
        ResetEvent( hEvents[1] );

        // send it back out...
        //
        bRet = WriteFile(
                    hPipe,          // file to write to
                    szOut,          // address of output buffer
                    sizeof(szOut),  // number of bytes to write
                    &cbWritten,     // number of bytes written
                    &os);           // overlapped stuff, not needed

        if ( !bRet && ( GetLastError() == ERROR_IO_PENDING ) )
        {
            dwWait = WaitForMultipleObjects( 2, hEvents, FALSE, INFINITE );
            if ( dwWait != WAIT_OBJECT_0+1 )     // not overlapped i/o event - error occurred,
                continue;                           // or server stop signaled
        }

        // drop the connection...
        //
        DisconnectNamedPipe(hPipe);
        
	}


    return true;
}

*/
/**************************************************************/

int Cicle ()
{

	    char Buffer[300];
		struct timeval tv;
		tv.tv_sec = 10;  /* 10 Secs Timeout */
		tv.tv_usec = 0;  // Not init'ing this can cause strange errors

        while(1) 
		{
                fromlen =sizeof(from);
                //
                // accept() doesn't make sense on UDP, since we do not listen()
                //
                msgsock = accept(listen_socket,(struct sockaddr*)&from, &fromlen);
                if (msgsock == INVALID_SOCKET) 
				{
                       //fprintf(stderr,"accept() error %d\n",WSAGetLastError());
                       WSACleanup();
                       continue;
                }



				setsockopt(msgsock, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,sizeof(struct timeval));
//**********************				
				LogWrite ("Begin receive.");           
//***********************

                retval = recv(msgsock,Buffer,sizeof (Buffer),0 );

//**********************				
				LogWrite ("End receive.");                    
//***********************

                if (retval == SOCKET_ERROR) 
				{
                        //fprintf(stderr,"recv() failed: error %d\n",WSAGetLastError());
                        closesocket(msgsock);
                        continue;
                }



				if (retval == 0) 
				{
                        printf("Client closed connection\n");
                        closesocket(msgsock);
                        continue;
                }
//!!!!!!!!!!!!!                
                Proccess (Buffer);
                if (Buffer[1]=='e')
                {
						retval = send(msgsock,Buffer,sizeof(Buffer),0);
						if (retval == SOCKET_ERROR) 
							{
							closesocket(msgsock);
							continue;
							}
                }
					   
				//printf("Received %d bytes, data [%s] from client\n",retval,Buffer);

                //retval = send(msgsock,Buffer,sizeof(Buffer),0);

                //if (retval == SOCKET_ERROR) 
				//{
                //      fprintf(stderr,"send() failed: error %d\n",WSAGetLastError());
                //}

                closesocket(msgsock);
                continue;
        }

		return 1;
}

/**************************************************************/

// Foward declarations of functions included in this code module:
ATOM                            MyRegisterClass(HINSTANCE hInstance);
BOOL                            InitInstance(HINSTANCE, int);
LRESULT CALLBACK        WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
		MSG msg;
        HACCEL hAccelTable;
		
		memset(&pRoute, 0, sizeof(pRoute));
        // Fedorov I.L.14.11.07
		pIpForwardTable = (MIB_IPFORWARDTABLE*) MALLOC(sizeof(MIB_IPFORWARDTABLE));
							
		if (IP.GetIpForwardTable(pIpForwardTable, &dwSize, 0) == ERROR_INSUFFICIENT_BUFFER) {
			FREE(pIpForwardTable);
			pIpForwardTable = (MIB_IPFORWARDTABLE*) MALLOC(dwSize);								
		}
		if ((dwRetVal = IP.GetIpForwardTable(pIpForwardTable, &dwSize, 0)) == NO_ERROR) {
			for (i = 0; i < (int) pIpForwardTable->dwNumEntries; i++) {
				/*Convert IPv4 addresses to strings  */
				IpAddr.S_un.S_addr =  (u_long) pIpForwardTable->table[i].dwForwardDest;
				if ((u_long) pIpForwardTable->table[i].dwForwardDest == inet_addr("0.0.0.0")){
					pRoute = pIpForwardTable->table[i];
				}
			}
			FREE(pIpForwardTable);
		   // return 0;
		}
		/*/// TODO: Place code here.
        pRoute.dwForwardDest=inet_addr("0.0.0.0");
		pRoute.dwForwardIfIndex = 65539;//sInterfaceIndex;
		pRoute.dwForwardMask=inet_addr("0.0.0.0");
		pRoute.dwForwardType = 4;
		pRoute.dwForwardProto = 3;//PROTO_IP_NETMGMT;
		pRoute.dwForwardNextHop = inet_addr("10.12.200.1");
		pRoute.dwForwardMetric1 = 1;*/
		//end (разремить заременое 8))
        // Initialize global strings
        LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
        LoadString(hInstance, IDC_WLOCKER, szWindowClass, MAX_LOADSTRING);
        MyRegisterClass(hInstance);

        // Perform application initialization:
        if (!InitInstance (hInstance, nCmdShow)) 
        {
                return FALSE;
        }

        hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_WLOCKER);

//!!!!!!!!!!!!!!!!!!!!!!
								int m;
								FILE* fp = fopen ("vrem.ini", "rb");
								if (!fp)
								{
									#ifdef _LOG_ITAR
										LogWrite ("Error writing Users.ini");
									#endif
								}
								else
								{
								m = fread (&m_TimeLeft, sizeof (INT), 1, fp);
								m += fread (&off, sizeof (INT), 1, fp);
								m += fread (&TarifName, 200, 1, fp);
								m += fread (&GateWayOn, sizeof (BOOL), 1, fp);
								if (m!=4)
								{
									#ifdef _LOG_ITAR
										LogWrite("Error reading avans.ini");
									#endif
									
								}
								fclose(fp);
								}
char buffer[222];
						Proccess ("sta1k SW");
						if (m_TimeLeft > 0 && off == 0)   
						{
							sprintf(buffer,"sta1k SZ %s-%d, HW",TarifName,m_TimeLeft);
							Proccess ("sta1k EE");
							Proccess (buffer);

						}


        // Main message loop:
        while (GetMessage(&msg, NULL, 0, 0)) 
        {
	            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
                {
                        TranslateMessage(&msg);
                        DispatchMessage(&msg);
                }

        }

        return msg.wParam;
}


/**************************************************************/

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
        WNDCLASSEX wcex;

        wcex.cbSize = sizeof(WNDCLASSEX); 

        wcex.style              = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc        = (WNDPROC)WndProc;
        wcex.cbClsExtra         = 0;
        wcex.cbWndExtra         = 0;
        wcex.hInstance          = hInstance;
        wcex.hIcon              = NULL;//LoadIcon(hInstance, (LPCTSTR)IDI_LOGO);
        wcex.hCursor            = LoadCursor(NULL, IDC_ARROW);
        wcex.hbrBackground      = (HBRUSH) (24);
        wcex.lpszMenuName       = NULL;
        wcex.lpszClassName      = szWindowClass;
        wcex.hIconSm            = NULL;//LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

        return RegisterClassEx(&wcex);
}


/**************************************************************/
//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
//	status=InstallDriverWithSCManager();
								
   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, szWindowClass, NULL, WS_POPUP,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   RECT Rect;
   Rect.left=0;
   Rect.right=GetSystemMetrics(SM_CXSCREEN);
   Rect.top=0;
   Rect.bottom=GetSystemMetrics(SM_CYSCREEN);

   EnableWindow (hWnd, false);


   SetWindowPos (hWnd, HWND_BOTTOM, 0 ,0 ,Rect.right , Rect.bottom, 0);
   ShowWindow(hWnd, SW_HIDE);
   UpdateWindow(hWnd);

   
  
   hTarifWnd = CreateWindowEx(WS_EX_TOOLWINDOW, szWindowClass, "Tarif Info", WS_POPUP|WS_BORDER, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hTarifWnd )
   {
      return FALSE;
   }

  
   SetWindowPos (hTarifWnd , HWND_TOPMOST, 100 ,0 ,600, 20, 0);
   ShowWindow(hTarifWnd , SW_HIDE);
   UpdateWindow(hTarifWnd );


    #define RSP_SIMPLE_SERVICE        0x00000001
    #define RSP_UNREGISTER_SERVICE    0x00000000


    HINSTANCE hInstKernel;
    DWORD (__stdcall *pRegisterServiceProcess) (DWORD, DWORD);

    hInstKernel = LoadLibrary ("KERNEL32.DLL");

    if (hInstKernel)
    {
        pRegisterServiceProcess = (DWORD (__stdcall *) (DWORD, DWORD))  GetProcAddress (hInstKernel, "RegisterServiceProcess");

        if (pRegisterServiceProcess)
          {
            pRegisterServiceProcess (NULL, RSP_SIMPLE_SERVICE);
          }

        FreeLibrary (hInstKernel);
    }


/********************************************************************/

        if (WSAStartup(0x202,&wsaData) == SOCKET_ERROR) {
                LogWrite ("Not WSock 2.2.");
                fprintf(stderr,"WSAStartup failed with error %d\n",WSAGetLastError());
                WSACleanup();
                return -1;
        }

        local.sin_family = AF_INET;
        local.sin_addr.s_addr = (!_interface)?INADDR_ANY:inet_addr(_interface); 

        local.sin_port = htons(port);

        listen_socket = socket(AF_INET, socket_type,0); // TCP socket
        
        if (listen_socket == INVALID_SOCKET){
                LogWrite ("Failed socket.");
                fprintf(stderr,"socket() failed with error %d\n",WSAGetLastError());
                WSACleanup();
                return -1;
        }


        if (bind(listen_socket,(struct sockaddr*)&local,sizeof(local) ) 
                == SOCKET_ERROR) {
                LogWrite ("Failed Bind.");
                fprintf(stderr,"bind() failed with error %d\n",WSAGetLastError());
                WSACleanup();
                return -1;
        }


        if (socket_type != SOCK_DGRAM) {
                if (listen(listen_socket,5) == SOCKET_ERROR) {
                    LogWrite ("Failed Listen.");
                        fprintf(stderr,"listen() failed with error %d\n",WSAGetLastError());
                        WSACleanup();
                        return -1;
                }
        }

       CreateThread (NULL,
                     0,
                     (LPTHREAD_START_ROUTINE)Cicle,
//                     (LPVOID)&hPipe,
                                         NULL,
                     0,
                     &threadID);



/********************************************************************/

    // create the event object. The control handler function signals
    // this event when it receives the "stop" control code.
    //
    hServerStopEvent = CreateEvent(
        NULL,    // no security attributes
        TRUE,    // manual reset event
        FALSE,   // not-signalled
        NULL);   // no name

    if ( hServerStopEvent == NULL)
        goto cleanup;

    hEvents[0] = hServerStopEvent;

    hEvents[1] = CreateEvent(
        NULL,    // no security attributes
        TRUE,    // manual reset event
        FALSE,   // not-signalled
        NULL);   // no name

    if ( hEvents[1] == NULL)
        goto cleanup;


    // create a security descriptor that allows anyone to write to
    //  the pipe...
    //
    pSD = (PSECURITY_DESCRIPTOR) malloc( SECURITY_DESCRIPTOR_MIN_LENGTH );

    if (pSD == NULL)
        goto cleanup;

    if (!InitializeSecurityDescriptor(pSD, SECURITY_DESCRIPTOR_REVISION))
        goto cleanup;

    // add a NULL disc. ACL to the security descriptor.
    //
    if (!SetSecurityDescriptorDacl(pSD, TRUE, (PACL) NULL, FALSE))
        goto cleanup;

    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = pSD;
    sa.bInheritHandle = TRUE;

    // open our named pipe...
    //
/*
        char LongName[300];
        strcpy (LongName, lpszPipePath);
        strcat (LongName, lpszPipeName);
    hPipe = CreateNamedPipe(
                    LongName         ,  // name of pipe
                    FILE_FLAG_OVERLAPPED |
                    PIPE_ACCESS_DUPLEX,     // pipe open mode
                    PIPE_TYPE_MESSAGE |
                    PIPE_READMODE_MESSAGE |
                    PIPE_WAIT,              // pipe IO type
                    1,                      // number of instances
                    0,                      // size of outbuf (0 == allocate as necessary)
                    0,                      // size of inbuf
                    1000,                   // default time-out value
                    &sa);                   // security attributes


       CreateThread (NULL,
                     0,
                     (LPTHREAD_START_ROUTINE)CiclePipe,
//                     (LPVOID)&hPipe,
                                         NULL,
                     0,
                     &threadID);
*/

           return TRUE;

  cleanup:

    if (hPipe != INVALID_HANDLE_VALUE )
        CloseHandle(hPipe);

    if (hServerStopEvent)
        CloseHandle(hServerStopEvent);

    if (hEvents[1]) // overlapped i/o event
        CloseHandle(hEvents[1]);

    if ( pSD )
        free( pSD );


return FALSE;
}

/**************************************************************/

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
        PAINTSTRUCT ps;
        HDC hdc;
        TCHAR szHello[MAX_LOADSTRING];
        LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

        switch (message) 
        {

				case 163:
				case WM_LBUTTONDBLCLK:
						if (hWnd == hTarifWnd)
						{
							if(fl) 
								off = 1;
							else 
							{	
								ShowWindow(hTarifWnd,SW_HIDE);
								ShowWindow(hTarifWnd,SW_SHOW);
								hdc = BeginPaint(hTarifWnd, &ps);
								RECT rt;
                                FillRect(hdc, &gl_rt, (HBRUSH)GetStockObject(BLACK_BRUSH)); 
                                GetClientRect(hTarifWnd, &rt);
								SetTextColor(hdc, RGB(255,255,255));
								SetBkColor(hdc, RGB(255,0,0));
								sprintf (Text2Out, "ПОСЛЕ СЛЕДУЮЩЕГО ДВОЙНОГО ЩЕЛЧКА СЕАНС БУДЕТ ПРЕРВАН!", TarifName);
                                DrawText(hdc, Text2Out, strlen(Text2Out), &rt, DT_CENTER|DT_TOP);                
                                memcpy (&gl_rt, &rt, sizeof(RECT));
                                EndPaint(hTarifWnd, &ps);
								
								Beep(800,100); Sleep(100);

							}
						}
						if (!fl) 
						{
							fl = 1;
							break;			
						}
						else 
						{
								ShowWindow(hTarifWnd,SW_HIDE);
								ShowWindow(hTarifWnd,SW_SHOW);
						}
                case WM_PAINT:
                        if (hWnd == hTarifWnd)
                        {
								SendMessage(HWND_BROADCAST, WM_SYSCOMMAND,SC_MONITORPOWER, 0);
								SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, -1);
                                hdc = BeginPaint(hTarifWnd, &ps);
                                // TODO: Add any drawing code here...
                                RECT rt;
                                FillRect(hdc, &gl_rt, (HBRUSH)GetStockObject(BLACK_BRUSH)); 
                                GetClientRect(hTarifWnd, &rt);
								

//                                rt.bottom -= 26;
//								rt.top +=2;
//                                sprintf (Text2Out, "Тип работы - %s", TarifName);
//                                DrawText(hdc, Text2Out, strlen(Text2Out), &rt, DT_CENTER|DT_TOP);
                                
//                                rt.bottom += 35;
//                                rt.top +=22;
								if(off == 1)
								{
									Beep(1600,100); Sleep(50);
									Beep(1500,100); Sleep(50);
									Beep(1400,100); Sleep(50);
									Beep(1300,100); Sleep(50);
									Beep(1200,100); Sleep(50);
									Beep(1100,100); Sleep(50);
									Beep(1000,100); Sleep(50);
									Beep(900,100); Sleep(50);
									Beep(800,100);
									SetTextColor(hdc, RGB(255,255,255));
									SetBkColor(hdc, RGB(255,0,0));
									sprintf (Text2Out, "ВРЕМЯ НА ИСХОДЕ!  СЕАНС БУДЕТ ПРЕРВАН ЧЕРЕЗ НЕСКОЛЬКО СЕКУНД!", TarifName);
                                DrawText(hdc, Text2Out, strlen(Text2Out), &rt, DT_CENTER|DT_TOP);                
									
								}
                                if (m_TimeLeft <= 0)
								{
//!!!!!!!!!!!!!!!!!!!
									if (off == 0) off = 2;

									SetTextColor(hdc, RGB(255,255,255));
									SetBkColor(hdc, RGB(255,0,0));
									sprintf (Text2Out, "ВРЕМЯ НА ИСХОДЕ!  СЕАНС БУДЕТ ПРЕРВАН ЧЕРЕЗ НЕСКОЛЬКО СЕКУНД!", TarifName);
                                DrawText(hdc, Text2Out, strlen(Text2Out), &rt, DT_CENTER|DT_TOP);                
								
								}
                                else if (off == 0)
								{
									sprintf (Text2Out, "Тип работы - %s До окончания примерно %d минут(ы)", TarifName, m_TimeLeft );
									fl = 0;
									if (m_TimeLeft <= 1 )  
									{
									SetTextColor(hdc, RGB(255,255,255));
									SetBkColor(hdc, RGB(255,0,0));
                                DrawText(hdc, Text2Out, strlen(Text2Out), &rt, DT_CENTER|DT_TOP); 
									}
									else
									if (m_TimeLeft <= 3 )  
									{
								    SetBkColor(hdc, RGB(255,255,0));
									SetTextColor(hdc, RGB(0,0,0));
                                DrawText(hdc, Text2Out, strlen(Text2Out), &rt, DT_CENTER|DT_TOP);   
									}
									else
									if (m_TimeLeft <= 5 )  
									{						
								    SetBkColor(hdc, RGB(255,255,255));
									SetTextColor(hdc, RGB(0,0,0));
                                DrawText(hdc, Text2Out, strlen(Text2Out), &rt, DT_CENTER|DT_TOP); 
									}
									else
									{
										SetTextColor( hdc, RGB(255, 255, 255));
										SetBkColor (hdc, RGB(0,0,0));
										DrawText(hdc, Text2Out, strlen(Text2Out), &rt, DT_CENTER|DT_TOP);                
									}
								}
                                memcpy (&gl_rt, &rt, sizeof(RECT));
                                EndPaint(hTarifWnd, &ps);
                        }
                        else
                        {
                                hdc = BeginPaint(hWnd, &ps);
                                // TODO: Add any drawing code here...
                                RECT rt;
                                GetClientRect(hWnd, &rt);
                                FillRect(hdc, &gl_rt, (HBRUSH)GetStockObject(BLACK_BRUSH)); 
								GetClientRect(hWnd, &rt);
								rt.top = rand()%480;
								rt.left = rand()%640;
                                SetTextColor( hdc, RGB(255, 255, 255));
                                SetBkColor (hdc, RGB(0,0,0));
                                DrawText(hdc, "Внесите залог.", 14, &rt, DT_CENTER);
                                memcpy (&gl_rt, &rt, sizeof(RECT));
                                EndPaint(hWnd, &ps);
                        }
                        break;
                case WM_QUIT:
                case WM_CLOSE:
                case WM_DESTROY:
					return false;
                    //PostQuitMessage(0);
                    break;

                case WM_QUERYENDSESSION:
                case WM_ENDSESSION:
					return false;
					//PostQuitMessage(0);
					break;


                case WM_NCHITTEST:
                        if (hWnd == hTarifWnd)
                                return HTCAPTION;
                        break;
                default:

                        return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

/**************************************************************/

/*
   void hTarifWnd_Click(System::Object ^ sender, 
      System::EventArgs ^ e)
   {
      // Add event handler code here.
   }
hTarifWnd->Click += gcnew System::EventHandler(this, &hTarifWnd_Click);
*/