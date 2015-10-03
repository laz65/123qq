// UserInfo.cpp: implementation of the CUserInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <memory.h>
#include "UserInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CMapWordToOb Users;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUserInfo::CUserInfo(_UInfo *UInfo)
{
	memcpy(&Info, UInfo, sizeof(_UInfo));
}


CUserInfo::~CUserInfo()
{

}

CUserInfo::CUserInfo(LPCTSTR UserFio, DWORD UserType, DWORD AdminType, LPCTSTR UserCreator, 
					 const unsigned char Hash[16], bool Active)
{
	memset(&Info, 0, sizeof(_UInfo));
	strcpy(Info.Fio, UserFio);
	if (Info.Type = UserType == UT_ADMIN)
	{
		Info.Admin = AdminType;
	}
	else
	{
		Info.Admin = AT_NONE;
	}
	memcpy(Info.Hash, Hash, 16);
	strcpy(Info.Creator, UserCreator);
	Info.Active = Active;
}
