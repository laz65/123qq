# Microsoft Developer Studio Generated NMAKE File, Based on InetTarif.dsp
!IF "$(CFG)" == ""
CFG=InetTarif - Win32 Debug
!MESSAGE No configuration specified. Defaulting to InetTarif - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "InetTarif - Win32 Release" && "$(CFG)" != "InetTarif - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "InetTarif.mak" CFG="InetTarif - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "InetTarif - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "InetTarif - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "InetTarif - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : ".\hlp\InetTarif.hm" ".\Release\InetTarif.hlp" ".\Release\InetTarif.cnt" "$(OUTDIR)\InetTarif.exe"


CLEAN :
	-@erase "$(INTDIR)\Cloak.obj"
	-@erase "$(INTDIR)\ButtonBlock.obj"
	-@erase "$(INTDIR)\ClientRaschet.obj"
	-@erase "$(INTDIR)\CName.obj"
	-@erase "$(INTDIR)\ComPortDlg.obj"
	-@erase "$(INTDIR)\ComputerInet.obj"
	-@erase "$(INTDIR)\ComSetupDlg.obj"
	-@erase "$(INTDIR)\InetTarif.obj"
	-@erase "$(INTDIR)\InetTarif.pch"
	-@erase "$(INTDIR)\InetTarif.res"
	-@erase "$(INTDIR)\InetTarifDlg.obj"
	-@erase "$(INTDIR)\msflexgrid.obj"
	-@erase "$(INTDIR)\PasswDlg.obj"
	-@erase "$(INTDIR)\picture.obj"
	-@erase "$(INTDIR)\ReportDlg.obj"
	-@erase "$(INTDIR)\rowcursor.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TarifDlg.obj"
	-@erase "$(INTDIR)\TipDlg.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\InetTarif.exe"
	-@erase ".\Release\InetTarif.cnt"
	-@erase ".\Release\InetTarif.hlp"
	-@erase "hlp\InetTarif.hm"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\InetTarif.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x419 /fo"$(INTDIR)\InetTarif.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\InetTarif.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\InetTarif.pdb" /machine:I386 /out:"$(OUTDIR)\InetTarif.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Cloak.obj" \
	"$(INTDIR)\ClientRaschet.obj" \
	"$(INTDIR)\CName.obj" \
	"$(INTDIR)\ComPortDlg.obj" \
	"$(INTDIR)\ComputerInet.obj" \
	"$(INTDIR)\ComSetupDlg.obj" \
	"$(INTDIR)\InetTarif.obj" \
	"$(INTDIR)\InetTarifDlg.obj" \
	"$(INTDIR)\msflexgrid.obj" \
	"$(INTDIR)\PasswDlg.obj" \
	"$(INTDIR)\picture.obj" \
	"$(INTDIR)\ReportDlg.obj" \
	"$(INTDIR)\rowcursor.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TarifDlg.obj" \
	"$(INTDIR)\TipDlg.obj" \
	"$(INTDIR)\InetTarif.res" \
	"$(INTDIR)\ButtonBlock.obj"

"$(OUTDIR)\InetTarif.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "InetTarif - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\hlp\InetTarif.hm" ".\Debug\InetTarif.hlp" ".\Debug\InetTarif.cnt" "$(OUTDIR)\InetTarif.exe" "$(OUTDIR)\InetTarif.bsc"


CLEAN :
	-@erase "$(INTDIR)\Cloak.obj"
	-@erase "$(INTDIR)\Cloak.sbr"
	-@erase "$(INTDIR)\ButtonBlock.obj"
	-@erase "$(INTDIR)\ButtonBlock.sbr"
	-@erase "$(INTDIR)\ClientRaschet.obj"
	-@erase "$(INTDIR)\ClientRaschet.sbr"
	-@erase "$(INTDIR)\CName.obj"
	-@erase "$(INTDIR)\CName.sbr"
	-@erase "$(INTDIR)\ComPortDlg.obj"
	-@erase "$(INTDIR)\ComPortDlg.sbr"
	-@erase "$(INTDIR)\ComputerInet.obj"
	-@erase "$(INTDIR)\ComputerInet.sbr"
	-@erase "$(INTDIR)\ComSetupDlg.obj"
	-@erase "$(INTDIR)\ComSetupDlg.sbr"
	-@erase "$(INTDIR)\InetTarif.obj"
	-@erase "$(INTDIR)\InetTarif.pch"
	-@erase "$(INTDIR)\InetTarif.res"
	-@erase "$(INTDIR)\InetTarif.sbr"
	-@erase "$(INTDIR)\InetTarifDlg.obj"
	-@erase "$(INTDIR)\InetTarifDlg.sbr"
	-@erase "$(INTDIR)\msflexgrid.obj"
	-@erase "$(INTDIR)\msflexgrid.sbr"
	-@erase "$(INTDIR)\PasswDlg.obj"
	-@erase "$(INTDIR)\PasswDlg.sbr"
	-@erase "$(INTDIR)\picture.obj"
	-@erase "$(INTDIR)\picture.sbr"
	-@erase "$(INTDIR)\ReportDlg.obj"
	-@erase "$(INTDIR)\ReportDlg.sbr"
	-@erase "$(INTDIR)\rowcursor.obj"
	-@erase "$(INTDIR)\rowcursor.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\TarifDlg.obj"
	-@erase "$(INTDIR)\TarifDlg.sbr"
	-@erase "$(INTDIR)\TipDlg.obj"
	-@erase "$(INTDIR)\TipDlg.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\InetTarif.bsc"
	-@erase "$(OUTDIR)\InetTarif.exe"
	-@erase "$(OUTDIR)\InetTarif.ilk"
	-@erase "$(OUTDIR)\InetTarif.pdb"
	-@erase ".\Debug\InetTarif.cnt"
	-@erase ".\Debug\InetTarif.hlp"
	-@erase "hlp\InetTarif.hm"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\InetTarif.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x419 /fo"$(INTDIR)\InetTarif.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\InetTarif.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Cloak.sbr" \
	"$(INTDIR)\ClientRaschet.sbr" \
	"$(INTDIR)\CName.sbr" \
	"$(INTDIR)\ComPortDlg.sbr" \
	"$(INTDIR)\ComputerInet.sbr" \
	"$(INTDIR)\ComSetupDlg.sbr" \
	"$(INTDIR)\InetTarif.sbr" \
	"$(INTDIR)\InetTarifDlg.sbr" \
	"$(INTDIR)\msflexgrid.sbr" \
	"$(INTDIR)\PasswDlg.sbr" \
	"$(INTDIR)\picture.sbr" \
	"$(INTDIR)\ReportDlg.sbr" \
	"$(INTDIR)\rowcursor.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\TarifDlg.sbr" \
	"$(INTDIR)\TipDlg.sbr" \
	"$(INTDIR)\ButtonBlock.sbr"

"$(OUTDIR)\InetTarif.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\InetTarif.pdb" /debug /machine:I386 /out:"$(OUTDIR)\InetTarif.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\Cloak.obj" \
	"$(INTDIR)\ClientRaschet.obj" \
	"$(INTDIR)\CName.obj" \
	"$(INTDIR)\ComPortDlg.obj" \
	"$(INTDIR)\ComputerInet.obj" \
	"$(INTDIR)\ComSetupDlg.obj" \
	"$(INTDIR)\InetTarif.obj" \
	"$(INTDIR)\InetTarifDlg.obj" \
	"$(INTDIR)\msflexgrid.obj" \
	"$(INTDIR)\PasswDlg.obj" \
	"$(INTDIR)\picture.obj" \
	"$(INTDIR)\ReportDlg.obj" \
	"$(INTDIR)\rowcursor.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TarifDlg.obj" \
	"$(INTDIR)\TipDlg.obj" \
	"$(INTDIR)\InetTarif.res" \
	"$(INTDIR)\ButtonBlock.obj"

"$(OUTDIR)\InetTarif.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("InetTarif.dep")
!INCLUDE "InetTarif.dep"
!ELSE 
!MESSAGE Warning: cannot find "InetTarif.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "InetTarif - Win32 Release" || "$(CFG)" == "InetTarif - Win32 Debug"
SOURCE=.\Cloak.cpp

!IF  "$(CFG)" == "InetTarif - Win32 Release"


"$(INTDIR)\Cloak.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\InetTarif.pch"


!ELSEIF  "$(CFG)" == "InetTarif - Win32 Debug"


"$(INTDIR)\Cloak.obj"	"$(INTDIR)\Cloak.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\InetTarif.pch"


!ENDIF 

SOURCE=.\ButtonBlock.cpp

!IF  "$(CFG)" == "InetTarif - Win32 Release"


"$(INTDIR)\ButtonBlock.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\InetTarif.pch"


!ELSEIF  "$(CFG)" == "InetTarif - Win32 Debug"


"$(INTDIR)\ButtonBlock.obj"	"$(INTDIR)\ButtonBlock.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\InetTarif.pch"


!ENDIF 

SOURCE=.\ClientRaschet.cpp

!IF  "$(CFG)" == "InetTarif - Win32 Release"


"$(INTDIR)\ClientRaschet.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\InetTarif.pch"


!ELSEIF  "$(CFG)" == "InetTarif - Win32 Debug"


"$(INTDIR)\ClientRaschet.obj"	"$(INTDIR)\ClientRaschet.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\InetTarif.pch"


!ENDIF 

SOURCE=.\CName.cpp

!IF  "$(CFG)" == "InetTarif - Win32 Release"


"$(INTDIR)\CName.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\InetTarif.pch"


!ELSEIF  "$(CFG)" == "InetTarif - Win32 Debug"


"$(INTDIR)\CName.obj"	"$(INTDIR)\CName.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\InetTarif.pch"


!ENDIF 

SOURCE=.\ComPortDlg.cpp

!IF  "$(CFG)" == "InetTarif - Win32 Release"


"$(INTDIR)\ComPortDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\InetTarif.pch"


!ELSEIF  "$(CFG)" == "InetTarif - Win32 Debug"


"$(INTDIR)\ComPortDlg.obj"	"$(INTDIR)\ComPortDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\InetTarif.pch"


!ENDIF 

SOURCE=.\ComputerInet.cpp

!IF  "$(CFG)" == "InetTarif - Win32 Release"


"$(INTDIR)\ComputerInet.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\InetTarif.pch"


!ELSEIF  "$(CFG)" == "InetTarif - Win32 Debug"


"$(INTDIR)\ComputerInet.obj"	"$(INTDIR)\ComputerInet.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\InetTarif.pch"


!ENDIF 

SOURCE=.\ComSetupDlg.cpp

!IF  "$(CFG)" == "InetTarif - Win32 Release"


"$(INTDIR)\ComSetupDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\InetTarif.pch"


!ELSEIF  "$(CFG)" == "InetTarif - Win32 Debug"


"$(INTDIR)\ComSetupDlg.obj"	"$(INTDIR)\ComSetupDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\InetTarif.pch"


!ENDIF 

SOURCE=.\InetTarif.cpp

!IF  "$(CFG)" == "InetTarif - Win32 Release"


"$(INTDIR)\InetTarif.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\InetTarif.pch"


!ELSEIF  "$(CFG)" == "InetTarif - Win32 Debug"


"$(INTDIR)\InetTarif.obj"	"$(INTDIR)\InetTarif.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\InetTarif.pch"


!ENDIF 

SOURCE=.\hlp\InetTarif.hpj

!IF  "$(CFG)" == "InetTarif - Win32 Release"

OutDir=.\Release
InputPath=.\hlp\InetTarif.hpj
InputName=InetTarif

"$(INTDIR)\InetTarif.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	start /wait /C /E /M "hlp\$(InputName).hpj" 
	if errorlevel 1 goto :Error 
	if not exist "hlp\$(InputName).hlp" goto :Error 
	copy "hlp\$(InputName).hlp" $(OutDir) 
	goto :done 
	:Error 
	echo hlp\$(InputName).hpj(1) : error: 
	type "hlp\$(InputName).log" 
	:done 
<< 
	

!ELSEIF  "$(CFG)" == "InetTarif - Win32 Debug"

OutDir=.\Debug
InputPath=.\hlp\InetTarif.hpj
InputName=InetTarif

"$(INTDIR)\InetTarif.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	start /wait /C /E /M "hlp\$(InputName).hpj" 
	if errorlevel 1 goto :Error 
	if not exist "hlp\$(InputName).hlp" goto :Error 
	copy "hlp\$(InputName).hlp" $(OutDir) 
	goto :done 
	:Error 
	echo hlp\$(InputName).hpj(1) : error: 
	type "hlp\$(InputName).log" 
	:done 
<< 
	

!ENDIF 

SOURCE=.\InetTarif.rc

"$(INTDIR)\InetTarif.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\InetTarifDlg.cpp

!IF  "$(CFG)" == "InetTarif - Win32 Release"


"$(INTDIR)\InetTarifDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\InetTarif.pch"


!ELSEIF  "$(CFG)" == "InetTarif - Win32 Debug"


"$(INTDIR)\InetTarifDlg.obj"	"$(INTDIR)\InetTarifDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\InetTarif.pch"


!ENDIF 

SOURCE=.\msflexgrid.cpp

!IF  "$(CFG)" == "InetTarif - Win32 Release"


"$(INTDIR)\msflexgrid.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\InetTarif.pch"


!ELSEIF  "$(CFG)" == "InetTarif - Win32 Debug"


"$(INTDIR)\msflexgrid.obj"	"$(INTDIR)\msflexgrid.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\InetTarif.pch"


!ENDIF 

SOURCE=.\PasswDlg.cpp

!IF  "$(CFG)" == "InetTarif - Win32 Release"


"$(INTDIR)\PasswDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\InetTarif.pch"


!ELSEIF  "$(CFG)" == "InetTarif - Win32 Debug"


"$(INTDIR)\PasswDlg.obj"	"$(INTDIR)\PasswDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\InetTarif.pch"


!ENDIF 

SOURCE=.\picture.cpp

!IF  "$(CFG)" == "InetTarif - Win32 Release"


"$(INTDIR)\picture.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\InetTarif.pch"


!ELSEIF  "$(CFG)" == "InetTarif - Win32 Debug"


"$(INTDIR)\picture.obj"	"$(INTDIR)\picture.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\InetTarif.pch"


!ENDIF 

SOURCE=.\ReportDlg.cpp

!IF  "$(CFG)" == "InetTarif - Win32 Release"


"$(INTDIR)\ReportDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\InetTarif.pch"


!ELSEIF  "$(CFG)" == "InetTarif - Win32 Debug"


"$(INTDIR)\ReportDlg.obj"	"$(INTDIR)\ReportDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\InetTarif.pch"


!ENDIF 

SOURCE=.\rowcursor.cpp

!IF  "$(CFG)" == "InetTarif - Win32 Release"


"$(INTDIR)\rowcursor.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\InetTarif.pch"


!ELSEIF  "$(CFG)" == "InetTarif - Win32 Debug"


"$(INTDIR)\rowcursor.obj"	"$(INTDIR)\rowcursor.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\InetTarif.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "InetTarif - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\InetTarif.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\InetTarif.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "InetTarif - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\InetTarif.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\InetTarif.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\TarifDlg.cpp

!IF  "$(CFG)" == "InetTarif - Win32 Release"


"$(INTDIR)\TarifDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\InetTarif.pch"


!ELSEIF  "$(CFG)" == "InetTarif - Win32 Debug"


"$(INTDIR)\TarifDlg.obj"	"$(INTDIR)\TarifDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\InetTarif.pch"


!ENDIF 

SOURCE=.\TipDlg.cpp

!IF  "$(CFG)" == "InetTarif - Win32 Release"


"$(INTDIR)\TipDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\InetTarif.pch"


!ELSEIF  "$(CFG)" == "InetTarif - Win32 Debug"


"$(INTDIR)\TipDlg.obj"	"$(INTDIR)\TipDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\InetTarif.pch"


!ENDIF 

SOURCE=.\Resource.h

!IF  "$(CFG)" == "InetTarif - Win32 Release"

TargetName=InetTarif
InputPath=.\Resource.h

".\hlp\InetTarif.hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
<< 
	

!ELSEIF  "$(CFG)" == "InetTarif - Win32 Debug"

TargetName=InetTarif
InputPath=.\Resource.h

".\hlp\InetTarif.hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
<< 
	

!ENDIF 

SOURCE=.\hlp\InetTarif.cnt

!IF  "$(CFG)" == "InetTarif - Win32 Release"

OutDir=.\Release
InputPath=.\hlp\InetTarif.cnt
InputName=InetTarif

"$(INTDIR)\InetTarif.cnt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy "hlp\$(InputName).cnt" $(OutDir)
<< 
	

!ELSEIF  "$(CFG)" == "InetTarif - Win32 Debug"

OutDir=.\Debug
InputPath=.\hlp\InetTarif.cnt
InputName=InetTarif

"$(INTDIR)\InetTarif.cnt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy "hlp\$(InputName).cnt" $(OutDir)
<< 
	

!ENDIF 


!ENDIF 

