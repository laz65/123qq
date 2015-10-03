// stdafx.cpp : source file that includes just the standard includes
//	InetTarif.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

void ClearComp(CompInfo *Comp)
{
    Comp->Elapce=0;
	Comp->TPos=0;
	Comp->bTarif=false;
	Comp->sTarif=false;
	Comp->cTarif=false;
	Comp->Tarif=0.0;
    Comp->Start=false;
    Comp->Rasch=false;
	// 21.04.2011
	//Comp->Connected=true;
	Comp->AllZalog=0.0;
    Comp->Zalog=0.0;
    Comp->Time=0;
    Comp->Ostatok=0.0;
	Comp->sStudFio=" ";
	Comp->sStudNum=" ";
	delete[] Comp->Bills;
	Comp->Bills = NULL;
	Comp->nBills = 0;
}

double Round(double dSum, long lPrec)
{
	double n, res;
	int dl;
	dl = (int) pow((double)10, lPrec);
	// res=цела€ часть числа n=дробна€ 0.xx
	n = modf(dSum* dl, &res);
	if (fabs(n)>=0.5) res++;
	res = res/dl;
	return res;
}


void LogWrite(char *text)
{
	FILE *log;
	log = fopen ("inet.log" , "at");
	char LogBuffer[500];
	SYSTEMTIME lpSystemTime;
	GetLocalTime(&lpSystemTime);

	sprintf (LogBuffer, "%02d.%02d.%04d %02d:%02d:%02d -> %s\n", lpSystemTime.wDay, lpSystemTime.wMonth, lpSystemTime.wYear, lpSystemTime.wHour, lpSystemTime.wMinute, lpSystemTime.wSecond, text);
	fprintf (log, "%s", LogBuffer);
	fclose (log);
}
// ƒл€ перехвата ошибок
/*
	__try 
	{
	dfdf
	}
	__except(Except(GetExceptionCode(), GetExceptionInformation(), _T("CTipDlg")))
	{ 
     ; 
	} 

*/
int Except (unsigned int code, struct _EXCEPTION_POINTERS *ep, CString ProcName)
{
	FILE *log;
	log = fopen ("inet.err" , "at");
	char LogBuffer[300];
	SYSTEMTIME lpSystemTime;
	GetLocalTime(&lpSystemTime);
	char ErrName[100];
	switch (code)
	{
		case EXCEPTION_ACCESS_VIOLATION:
			strcpy (ErrName, "EXCEPTION_ACCESS_VIOLATION");
			break;
		case EXCEPTION_BREAKPOINT:
			strcpy (ErrName, "EXCEPTION_BREAKPOINT");
			break;
		case EXCEPTION_DATATYPE_MISALIGNMENT:
			strcpy (ErrName, "EXCEPTION_DATATYPE_MISALIGNMENT");
			break;
		case EXCEPTION_SINGLE_STEP:
			strcpy (ErrName, "EXCEPTION_SINGLE_STEP");
			break;
		case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
			strcpy (ErrName, "EXCEPTION_ARRAY_BOUNDS_EXCEEDED");
			break;
		case EXCEPTION_FLT_DENORMAL_OPERAND:
			strcpy (ErrName, "EXCEPTION_FLT_DENORMAL_OPERAND");
			break;
		case EXCEPTION_FLT_DIVIDE_BY_ZERO:
			strcpy (ErrName, "EXCEPTION_FLT_DIVIDE_BY_ZERO");
			break;
		case EXCEPTION_FLT_INEXACT_RESULT:
			strcpy (ErrName, "EXCEPTION_FLT_INEXACT_RESULT");
			break;
		case EXCEPTION_FLT_INVALID_OPERATION:
			strcpy (ErrName, "EXCEPTION_FLT_INVALID_OPERATION");
			break;
		case EXCEPTION_FLT_OVERFLOW:
			strcpy (ErrName, "EXCEPTION_FLT_OVERFLOW");
			break;
		case EXCEPTION_FLT_STACK_CHECK:
			strcpy (ErrName, "EXCEPTION_FLT_STACK_CHECK");
			break;
		case EXCEPTION_FLT_UNDERFLOW:
			strcpy (ErrName, "EXCEPTION_FLT_UNDERFLOW");
			break;
		case EXCEPTION_INT_DIVIDE_BY_ZERO:
			strcpy (ErrName, "EXCEPTION_INT_DIVIDE_BY_ZERO");
			break;
		case EXCEPTION_INT_OVERFLOW:
			strcpy (ErrName, "EXCEPTION_INT_OVERFLOW");
			break;
		case EXCEPTION_PRIV_INSTRUCTION:
			strcpy (ErrName, "EXCEPTION_PRIV_INSTRUCTION");
			break;
		case EXCEPTION_NONCONTINUABLE_EXCEPTION:
			strcpy (ErrName, "EXCEPTION_NONCONTINUABLE_EXCEPTION");
			break;
		default:
			strcpy (ErrName, "!!UNKNOWN EXCEPTION!!");
			break;
	}
	sprintf (LogBuffer, "02d.%02d.%04d %02d:%02d:%02d. Error (%d:%s) in proc: (%s) \n", 
		lpSystemTime.wDay, lpSystemTime.wMonth, lpSystemTime.wYear,
		lpSystemTime.wHour, lpSystemTime.wMinute, lpSystemTime.wSecond, code, ErrName, ProcName);
	fprintf (log, "%s", LogBuffer);
	fclose (log);
	return EXCEPTION_EXECUTE_HANDLER; 
}
