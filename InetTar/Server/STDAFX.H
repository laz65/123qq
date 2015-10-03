// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__78696A72_83ED_11D4_945E_0050044D962D__INCLUDED_)
#define AFX_STDAFX_H__78696A72_83ED_11D4_945E_0050044D962D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define _CRT_SECURE_NO_WARNINGS

#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#include <afxtempl.h>
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include "TipDlg.h"
#include "MD5.h"
#include <afxdao.h>
#include <afxdisp.h>
#include <list>
#include <iostream>
#include <math.h>
#include <vector>
#include <afxdhtml.h>
// Убрать предупреждения об устаревших классах DAO
#pragma warning(disable : 4995)
// Убрать предупреждения об устаревших функциях
#pragma warning(disable : 4996)
// Если объявлено - записывать сообщения ПП в журнал
//#define _LOG_ITAR
//Максимальное к-во рабочих станций
#define MAX_WORKSTATION	100
// Пользователи приложения
struct _UInfo
{
char Fio[50];
DWORD Type, Admin;
bool Active;
unsigned char Hash[16];
char Creator[50];
};

typedef struct Dopusl
{
	int nomusl;
	char name[40];
	float tarif;
	int rf_code;
	char rf_name[20];
	int rf_rate;
	int tar_type;
} hDopusl;

typedef struct Setup
{
	char INomer[200]; //Код ПКПИ
	char IName[200]; // Наименование ПКПИ
	char Lock[200];  // Команда для блокировки
	char UnLock[200];  // Команда для разблокировки
	//
	int nDopList; // К-во доп.услуг в файле usl.ini
	//
	bool UseCassa;  // Печатать кассовый чек
	bool UseRF2160; // true - кассовый чек на РФ, false - на Самсунг
	bool UseBoth;  // Выдача залогового чека
	char PathBill [200]; //Куда формировать файлы чеков кассового аппарата
	//
	int CountComp; // К-во рабочих станций
	char CompName    [MAX_WORKSTATION] [70]; // Массив имен рабочих станций
	bool bActiv	[MAX_WORKSTATION]; // true - рабочей станцией можно пользоваться, false - нет (отключена, неисправна)
	bool BlockInet; // Блокировать Интернет
	bool CloseExplorer; // Блокировать эксплорер
	char GateWayName [200]; // IP Gateway
	bool Pipe; // Признак использования Pipes, иначе - Socket
	// Тарифы работы на станциях
	double Tarif1;  //Internet обычный 8-21
	double Tarif2;  //Computer обычный 8-21
	//
	double Tarif3;  //Internet льготный 21-8
	double Tarif4;  //Computer льготный 21-8
	//
	double Tarif5;  //Internet праздничный
	double Tarif6;  //Computer праздничный
	//
	double Tarif7;  //Student Internet обычный
	double Tarif8;  //Student Internet праздничный
	//
	char SharePath [200]; // Путь к общей папке
	char PathName [200]; // Путь к приложению и установкам (заполняется автоматич.)
//!!! Для изменения НДС 
	double CurNds; // Текущий ндс
	//
	MD5_CTX m_md5;
} hSetup;

typedef struct OldSetup
{
/*
	int CountComPort; // К-во ком-портов на серверной ЭВМ
	int CountComp;
	bool UseBoth;  // Выдача залогового чека
	CList <hDopusl, hDopusl&> *DopList;
	int nDopList;
	bool UseCassa;  // Печатать кассовый чек
	bool UseRF2160; // true - кассовый чек на РФ, false - на Самсунг
	char CassComPort[5];
	char PathBill [200];
	char IName[200];
	char INomer[200];
	char  CompComPort[50] [6]; //
	char  CompComPortSecond [50] [4];
	bool UseCOM; //
	char CompName    [50] [70];
	char Lock[200];
	char UnLock[200];
	char SharePath [200];
	bool Pipe;
	bool but_Type;
	bool but_Zalog;
	bool but_Raschet;
	bool but_Edit;
	bool CloseExplorer;
	bool BlockInet;
	char GateWayName [200];
	double Tarif1;
	double Tarif2;
	double Tarif3;
	double Tarif4;
	double Tarif5;
	double Tarif6;
	double Tarif7;
	double Tarif8;
	char PathName [200];
	MD5_CTX m_md5;
*/
	char INomer[200]; //Код ПКПИ
	char IName[200]; // Наименование ПКПИ
	char Lock[200];  // Команда для блокировки
	char UnLock[200];  // Команда для разблокировки
	//
	int nDopList; // К-во доп.услуг в файле usl.ini
	//
	bool UseCassa;  // Печатать кассовый чек
	bool UseRF2160; // true - кассовый чек на РФ, false - на Самсунг
	bool UseBoth;  // Выдача залогового чека
	char PathBill [200]; //Куда формировать файлы чеков кассового аппарата
	//
	int CountComp; // К-во рабочих станций
	char CompName    [MAX_WORKSTATION] [70]; // Массив имен рабочих станций
	bool bActiv	[MAX_WORKSTATION]; // true - рабочей станцией можно пользоваться, false - нет (отключена, неисправна)
	bool BlockInet; // Блокировать Интернет
	bool CloseExplorer; // Блокировать эксплорер
	char GateWayName [200]; // IP Gateway
	bool Pipe; // Признак использования Pipes, иначе - Socket
	// Тарифы работы на станциях
	double Tarif1;  //Internet обычный 8-21
	double Tarif2;  //Computer обычный 8-21
	//
	double Tarif3;  //Internet льготный 21-8
	double Tarif4;  //Computer льготный 21-8
	//
	double Tarif5;  //Internet праздничный
	double Tarif6;  //Computer праздничный
	//
	double Tarif7;  //Student Internet обычный
	double Tarif8;  //Student Internet праздничный
	//
	char SharePath [200]; // Путь к общей папке
	char PathName [200]; // Путь к приложению и установкам (заполняется автоматич.)
	//
	MD5_CTX m_md5;
} hOldSetup;

struct Bill
{
	SYSTEMTIME TimeBeg;
	double Tarif;
	int Time;
	double Sum;
};

typedef struct CompInfo
{
	HANDLE hCom;
	int NumbComp;  // Номер станции из стр-ры hSetup
	char CompName [70]; // Наименование станции из стр-ры hSetup
	SYSTEMTIME DateTimeBeg; // Дата начала учета сеанса по текущему тарифу
	int Elapce;		// Отработано времени по текущему тарифу
	int TPos;		// Тип текущего тарифа
	bool bTarif;	// Работа на ЭВМ без выхода в Интернет
	bool sTarif;	// Выхода в Интернет - студентческий
	bool cTarif;	// Работа на ЭВМ без выхода в Интернет - студентческий
	double Tarif;	// Текущий тариф
	bool Start;		// Признак работы станции (t - занята, f - свободна или закончился залог)
	bool Rasch;		// Признак расчета с клиентом (t - не рассчитан, f - расчет завершен)
	bool Connected;	// Признак доступности рабочей станции
	double AllZalog;	// Всего принято залога
	double Zalog;		// Реальный остаток залога баз текущего расчета
	int Time;			// Текущий остаток секунд работы	
	double Ostatok;		// Текущий остаток залога
	CString sStudFio;	// Для студ.тарифа - ФИО
	CString sStudNum;	// Для студ.тарифа - номер справки, билета
	int nBills;			//К-во расчетов по другим тарифам 
	Bill * Bills;		// Расчеты по другим тарифам (при автосмене тарифа)
} hCompInfo;

double Round(double dSum, long lPrec=2);
//
void ClearComp(CompInfo *Comp);
//
void LogWrite(char *text);
// Для перехвата ошибок
int Except (unsigned int code, struct _EXCEPTION_POINTERS *ep, CString ProcName);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__78696A72_83ED_11D4_945E_0050044D962D__INCLUDED_)
