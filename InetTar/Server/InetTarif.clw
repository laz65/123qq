; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CComSetupDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "InetTarif.h"

ClassCount=29
Class1=CInetTarifApp
Class2=CInetTarifDlg
Class3=CAboutDlg

ResourceCount=44
Resource1=IDD_DIALOGBAR (English (U.S.))
Resource2=IDR_MAINFRAME
Resource3=IDD_CLOAK
Resource4=IDD_HOLIDAYS
Resource5=IDD_VNESENIE
Resource6=IDD_REPORTDLG
Class5=CButtonBlock
Class6=CCName
Class7=CTipDlg
Resource7=IDD_NAMECOMPUTER
Resource8=IDD_DIALOG1
Resource9=IDD_PSWDIALOG
Resource10=IDD_TIP
Class4=CCloak
Class8=CComputerInet
Class9=CPasswDlg
Class10=CComSetupDlg
Class11=CComPortDlg
Class12=CTarifDlg
Class13=CReportDlg
Resource11=IDD_CHANGEPAS
Class14=CClientRaschet
Resource12=IDR_MAINMENU
Resource13=IDD_NAMECOMPUTER (Russian)
Resource14=IDD_INETTARIF_DIALOG (Russian)
Resource15=IDD_PSWDIALOG (Russian)
Resource16=IDD_COMPINET (Russian)
Resource17=IDD_BUTTONBLOCK (Russian)
Resource18=IDD_COMDIALOG (Russian)
Resource19=IDD_TIP (Russian)
Resource20=IDD_REPORTDLG (Russian)
Resource21=IDD_ABOUTBOX (Russian)
Resource22=IDD_SETUPDIALOG (Russian)
Resource23=IDD_TARIFDLG (Russian)
Resource24=IDD_Cloak (Russian)
Resource25=IDD_RASCHDIALOG (Russian)
Resource26=IDR_MAINMENU (Russian)
Resource27="IDD_Cloak"
Resource28=IDD_USER
Resource29=IDD_INETTARIF_DIALOG
Class15=CCmCloak
Class16=CChangePasDlg
Resource30=IDD_COMPINET
Resource31=IDD_CDIALOG
Resource32=IDD_SETUPDIALOG
Class17=CAdminDlg
Resource33=IDD_TARIF
Class18=CUserDlg
Resource34=IDD_ADMIN
Class19=CHolidaysDlg
Resource35=IDD_RASCHDIALOG
Class20=CManageDlg
Class21=CStat
Resource36=IDD_TARIFDLG
Class22=CTarif
Resource37=IDD_SETSEANS
Class23=CNewEdit
Resource38=IDD_COMDIALOG
Class24=ChekDlg
Resource39=IDD_NEW_EDIT
Class25=CSetUsl
Resource40=IDD_MENAGE
Class26=CVnesenie
Resource41=IDD_ABOUTBOX
Class27=CNewSeans
Resource42=IDD_SETUSL
Class28=CStud
Resource43=IDD_CHEK
Class29=CIzya
Resource44=IDR_LISTMNU

[CLS:CInetTarifApp]
Type=0
HeaderFile=InetTarif.h
ImplementationFile=InetTarif.cpp
Filter=N
LastObject=CInetTarifApp
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CInetTarifDlg]
Type=0
HeaderFile=InetTarifDlg.h
ImplementationFile=InetTarifDlg.cpp
Filter=W
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CInetTarifDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=InetTarifDlg.h
ImplementationFile=InetTarifDlg.cpp
Filter=D
LastObject=CAboutDlg
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=8
Control1=IDOK,button,1342373889
Control2=IDC_STATIC,static,1342308353
Control3=IDC_STATIC,static,1342308353
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1476395022
Control6=IDC_WWW1,static,1342177550
Control7=IDC_STATIC,static,1342308353
Control8=IDC_WWW,static,1342177550

[DLG:IDD_INETTARIF_DIALOG]
Type=1
Class=CInetTarifDlg
ControlCount=9
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308353
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308353
Control6=IDC_STATIC,static,1342308865
Control7=IDC_STATIC,static,1342308355
Control8=IDC_STATIC,static,1342177294
Control9=IDC_STATIC,static,1342308353

[DLG:IDD_TIP]
Type=1
Class=?
ControlCount=6
Control1=65535,static,1342177287
Control2=IDC_TIPSTRING,static,1342308352
Control3=IDC_STARTUP,button,1342373891
Control4=IDC_NEXTTIP,button,1342373888
Control5=IDOK,button,1342373889
Control6=IDC_BULB,static,1342177294

[CLS:CTipDlg]
Type=0
HeaderFile=TipDlg.h
ImplementationFile=TipDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CTipDlg

[CLS:CComputerInet]
Type=0
HeaderFile=ComputerInet.h
ImplementationFile=ComputerInet.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_RASBUTTON

[DLG:IDD_COMPINET]
Type=1
Class=CComputerInet
ControlCount=11
Control1=IDC_ZALOGEDIT,edit,1082327168
Control2=IDC_STATIC1,static,1073872896
Control3=IDC_ZALOGBUTTON,button,1073938432
Control4=IDC_RASBUTTON,button,1073938432
Control5=IDC_PROGRESS,msctls_progress32,1082327041
Control6=IDC_STATICPANEL,button,1073741831
Control7=IDC_CHECK,button,1073807363
Control8=IDC_COUNTTIME,static,1073872897
Control9=IDC_CHECKS,button,1342242819
Control10=IDC_FIO,edit,1350631552
Control11=IDC_NUM,edit,1350631552

[MNU:IDR_MAINMENU]
Type=1
Class=?
Command1=ID_SMENA
Command2=ID_LOGOFF
Command3=ID_CHEK
Command4=ID_XOTCHET
Command5=ID_XOTCHET_T
Command6=ID_ZOTCHET
Command7=ID_ZOTCHET_T
Command8=ID_OTKR
Command9=ID_VNESENIE
Command10=ID_IZYATIE
Command11=ID_EXIT
Command12=ID_DAYOFF
Command13=ID_CHANGEPASS
Command14=ID_HOLIDAYS
Command15=ID_TARIF
Command16=ID_SETTARIF
Command17=ID_COM
Command18=ID_ADMIN
Command19=ID_MANAGE
Command20=ID_MANIP
Command21=ID_TIP
Command22=ID_ABOUT
CommandCount=22

[CLS:CPasswDlg]
Type=0
HeaderFile=PasswDlg.h
ImplementationFile=PasswDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_PASSWEDIT
VirtualFilter=dWC

[DLG:IDD_PSWDIALOG]
Type=1
Class=CPasswDlg
ControlCount=7
Control1=IDC_IDEDIT,edit,1350631552
Control2=IDC_PASSWEDIT,edit,1350631584
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342177283

[DLG:IDD_SETUPDIALOG]
Type=1
Class=CComSetupDlg
ControlCount=32
Control1=IDC_INAME,edit,1350631552
Control2=IDC_INOMER,edit,1350631552
Control3=IDC_LOCKEDIT,edit,1350631552
Control4=IDC_UNLOCKEDIT,edit,1350631552
Control5=IDC_USECOMCHECK,button,1073807363
Control6=IDC_COUNTCOMPORT,edit,1082196096
Control7=IDC_COMPORTSPIN,msctls_updown32,1073742006
Control8=IDC_COUNTCOMP,edit,1350631552
Control9=IDC_COMPSPIN,msctls_updown32,1342177462
Control10=IDC_BOTH,button,1342242819
Control11=IDC_CASSACHECK,button,1342242819
Control12=IDC_CASSACOMBO,combobox,1075904515
Control13=IDC_CHECKINET,button,1342242819
Control14=IDC_CHECKEXPLORER,button,1342242819
Control15=IDC_GATEWAYNAME,edit,1350631552
Control16=IDC_BILLPATH,edit,1350631552
Control17=IDC_SHAREPATH,edit,1350631552
Control18=IDC_CHECKPIPES,button,1342242819
Control19=IDOK,button,1342242817
Control20=IDCANCEL,button,1342242816
Control21=IDC_STATIC,button,1342177287
Control22=IDC_STATIC,static,1073872896
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,static,1342308352
Control28=IDC_STATIC,static,1342308352
Control29=IDC_STATIC,static,1342308352
Control30=IDC_STATIC,static,1342308352
Control31=IDC_GRID,SysListView32,1342275585
Control32=IDC_RF2160,button,1342242819

[CLS:CComSetupDlg]
Type=0
HeaderFile=ComSetupDlg.h
ImplementationFile=ComSetupDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDOK
VirtualFilter=dWC

[DLG:IDD_COMDIALOG]
Type=1
Class=CComPortDlg
ControlCount=4
Control1=IDC_COMBO,combobox,1344339971
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_NAME,static,1342308352

[CLS:CComPortDlg]
Type=0
HeaderFile=ComPortDlg.h
ImplementationFile=ComPortDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CComPortDlg

[DLG:IDD_TARIFDLG]
Type=1
Class=CTarifDlg
ControlCount=27
Control1=IDC_TARIF1,edit,1350631552
Control2=IDC_SPIN1,msctls_updown32,1342177462
Control3=IDC_TARIF2,edit,1350631552
Control4=IDC_SPIN2,msctls_updown32,1342177462
Control5=IDC_TARIF3,edit,1350631552
Control6=IDC_SPIN3,msctls_updown32,1342177462
Control7=IDC_TARIF4,edit,1350631552
Control8=IDC_SPIN4,msctls_updown32,1342177462
Control9=IDC_TARIF5,edit,1350631552
Control10=IDC_SPIN5,msctls_updown32,1342177462
Control11=IDC_TARIF6,edit,1350631552
Control12=IDC_SPIN6,msctls_updown32,1342177462
Control13=IDC_STATIC,static,1342308353
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_TARIF7,edit,1350631552
Control21=IDC_SPIN7,msctls_updown32,1342177462
Control22=IDC_TARIF8,edit,1350631552
Control23=IDC_SPIN8,msctls_updown32,1342177462
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDOK,button,1342242817
Control27=IDCANCEL,button,1342242816

[CLS:CTarifDlg]
Type=0
HeaderFile=TarifDlg.h
ImplementationFile=TarifDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_LOGOFF
VirtualFilter=dWC

[CLS:CReportDlg]
Type=0
HeaderFile=ReportDlg.h
ImplementationFile=ReportDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_SHOW

[DLG:IDD_REPORTDLG]
Type=1
Class=CReportDlg
ControlCount=9
Control1=IDC_FROM,SysDateTimePick32,1342242852
Control2=IDC_TO,SysDateTimePick32,1342242852
Control3=IDC_SHOW,button,1342242816
Control4=IDC_PRINT,button,1342242816
Control5=IDOK,button,1342242816
Control6=IDCANCEL,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_GRID,SysListView32,1342275585

[DLG:IDD_RASCHDIALOG]
Type=1
Class=CClientRaschet
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308864
Control3=IDC_ISPTIME,edit,1350633600
Control4=IDC_STATIC,static,1342308864
Control5=IDC_ZALOG,edit,1350633600
Control6=IDC_STATIC,static,1342308864
Control7=IDC_INUSE,edit,1350633600
Control8=IDC_OST,static,1350697473
Control9=IDC_OSTATOK,edit,1350633600

[CLS:CClientRaschet]
Type=0
HeaderFile=ClientRaschet.h
ImplementationFile=ClientRaschet.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=ID_SMENA

[DLG:IDD_INETTARIF_DIALOG (Russian)]
Type=1
Class=CInetTarifDlg
ControlCount=91
Control1=IDC_ZALOGEDIT,edit,1082327168
Control2=IDC_STATIC1,static,1073872896
Control3=IDC_ZALOGBUTTON,button,1073938432
Control4=IDC_RASBUTTON,button,1073938432
Control5=IDC_PROGRESS,msctls_progress32,1082327041
Control6=IDC_STATICPANEL,button,1073741831
Control7=IDC_ZALOGEDIT2,edit,1082327168
Control8=IDC_STATIC2,static,1073872896
Control9=IDC_ZALOGBUTTON2,button,1073938432
Control10=IDC_RASBUTTON2,button,1073938432
Control11=IDC_PROGRESS2,msctls_progress32,1082327041
Control12=IDC_STATICPANEL2,button,1073741831
Control13=IDC_ZALOGEDIT3,edit,1082327168
Control14=IDC_STATIC3,static,1073872896
Control15=IDC_ZALOGBUTTON3,button,1073938432
Control16=IDC_RASBUTTON3,button,1073938432
Control17=IDC_PROGRESS3,msctls_progress32,1082327041
Control18=IDC_STATICPANEL3,button,1073741831
Control19=IDC_ZALOGEDIT4,edit,1082327168
Control20=IDC_STATIC4,static,1073872896
Control21=IDC_ZALOGBUTTON4,button,1073938432
Control22=IDC_RASBUTTON4,button,1073938432
Control23=IDC_PROGRESS4,msctls_progress32,1082327041
Control24=IDC_STATICPANEL4,button,1073741831
Control25=IDC_ZALOGEDIT5,edit,1082327168
Control26=IDC_STATIC5,static,1073872896
Control27=IDC_ZALOGBUTTON5,button,1073938432
Control28=IDC_RASBUTTON5,button,1073938432
Control29=IDC_PROGRESS5,msctls_progress32,1082327041
Control30=IDC_STATICPANEL5,button,1073741831
Control31=IDC_ZALOGEDIT6,edit,1082327168
Control32=IDC_STATIC6,static,1073872896
Control33=IDC_ZALOGBUTTON6,button,1073938432
Control34=IDC_RASBUTTON6,button,1073938432
Control35=IDC_PROGRESS6,msctls_progress32,1082327041
Control36=IDC_STATICPANEL6,button,1073741831
Control37=IDC_ZALOGEDIT7,edit,1082327168
Control38=IDC_STATIC7,static,1073872896
Control39=IDC_ZALOGBUTTON7,button,1073938432
Control40=IDC_RASBUTTON7,button,1073938432
Control41=IDC_PROGRESS7,msctls_progress32,1082327041
Control42=IDC_STATICPANEL7,button,1073741831
Control43=IDC_ZALOGEDIT8,edit,1082327168
Control44=IDC_STATIC8,static,1073872896
Control45=IDC_ZALOGBUTTON8,button,1073938432
Control46=IDC_RASBUTTON8,button,1073938432
Control47=IDC_PROGRESS8,msctls_progress32,1082327041
Control48=IDC_STATICPANEL8,button,1073741831
Control49=IDC_ZALOGEDIT9,edit,1082327168
Control50=IDC_STATIC9,static,1073872896
Control51=IDC_ZALOGBUTTON9,button,1073938432
Control52=IDC_RASBUTTON9,button,1073938432
Control53=IDC_PROGRESS9,msctls_progress32,1082327041
Control54=IDC_STATICPANEL9,button,1073741831
Control55=IDC_ZALOGEDIT10,edit,1082327168
Control56=IDC_STATIC10,static,1073872896
Control57=IDC_ZALOGBUTTON10,button,1073938432
Control58=IDC_RASBUTTON10,button,1073938432
Control59=IDC_PROGRESS10,msctls_progress32,1082327041
Control60=IDC_STATICPANEL10,button,1073741831
Control61=IDC_COUNTTIME,edit,1476593665
Control62=IDC_COUNTTIME2,edit,1476593793
Control63=IDC_COUNTTIME3,edit,1476593793
Control64=IDC_COUNTTIME4,edit,1476593793
Control65=IDC_COUNTTIME5,edit,1476593793
Control66=IDC_COUNTTIME6,edit,1476593793
Control67=IDC_COUNTTIME7,edit,1476593793
Control68=IDC_COUNTTIME8,edit,1476593793
Control69=IDC_COUNTTIME9,edit,1476593793
Control70=IDC_COUNTTIME10,edit,1476593793
Control71=IDC_STATIC,button,1342177287
Control72=IDC_STATIC,static,1342308352
Control73=IDC_STATIC,static,1342308352
Control74=IDC_STATIC,static,1342308352
Control75=IDC_STATIC,static,1342308352
Control76=IDC_STATIC,static,1342308352
Control77=IDC_STATIC,static,1342308352
Control78=IDC_STATIC,static,1342308352
Control79=IDC_STATIC,static,1476395022
Control80=IDC_STATIC,static,1342177294
Control81=IDC_STATIC,static,1342308352
Control82=IDC_CHECK1,button,1073807363
Control83=IDC_CHECK2,button,1073807363
Control84=IDC_CHECK3,button,1073807363
Control85=IDC_CHECK4,button,1073807363
Control86=IDC_CHECK5,button,1073807363
Control87=IDC_CHECK6,button,1073807363
Control88=IDC_CHECK7,button,1073807363
Control89=IDC_CHECK8,button,1073807363
Control90=IDC_CHECK9,button,1073807363
Control91=IDC_CHECK10,button,1073807363

[DLG:IDD_TIP (Russian)]
Type=1
Class=?
ControlCount=6
Control1=65535,static,1342177287
Control2=IDC_TIPSTRING,static,1342308352
Control3=IDC_STARTUP,button,1342373891
Control4=IDC_NEXTTIP,button,1342373888
Control5=IDOK,button,1342373889
Control6=IDC_BULB,static,1342177294

[DLG:IDD_COMPINET (Russian)]
Type=1
Class=CComputerInet
ControlCount=6
Control1=IDC_ZALOGEDIT,edit,1350762624
Control2=IDC_STATIC,static,1342308352
Control3=IDC_ZALOGBUTTON,button,1342373888
Control4=IDC_RASBUTTON,button,1342373888
Control5=IDC_PROGRESS,msctls_progress32,1350762497
Control6=IDC_STATICPANEL,button,1342177287

[DLG:IDD_PSWDIALOG (Russian)]
Type=1
Class=CPasswDlg
ControlCount=4
Control1=IDC_PASSWEDIT,edit,1350631584
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC,static,1342308352

[DLG:IDD_SETUPDIALOG (Russian)]
Type=1
Class=CComSetupDlg
ControlCount=26
Control1=IDC_INAME,edit,1350631552
Control2=IDC_INOMER,edit,1350631552
Control3=IDC_LOCKEDIT,edit,1350631552
Control4=IDC_UNLOCKEDIT,edit,1350631552
Control5=IDC_USECOMCHECK,button,1342242819
Control6=IDC_COUNTCOMPORT,edit,1350631552
Control7=IDC_COMPORTSPIN,msctls_updown32,1342177462
Control8=IDC_COUNTCOMP,edit,1350631552
Control9=IDC_COMPSPIN,msctls_updown32,1342177462
Control10=IDC_BOTH,button,1342242819
Control11=IDC_CASSACHECK,button,1342242819
Control12=IDC_CASSACOMBO,combobox,1344339971
Control13=IDC_BILLPATH,edit,1350631552
Control14=IDC_SHAREPATH,edit,1350631552
Control15=IDC_MSFLEXGRID,{6262D3A0-531B-11CF-91F6-C2863C385E30},1342242816
Control16=IDOK,button,1342242817
Control17=IDCANCEL,button,1342242816
Control18=IDC_STATIC,button,1342177287
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352

[DLG:IDD_COMDIALOG (Russian)]
Type=1
Class=CComPortDlg
ControlCount=4
Control1=IDC_COMBO,combobox,1344339971
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_NAME,static,1342308352

[DLG:IDD_TARIFDLG (Russian)]
Type=1
Class=CTarifDlg
ControlCount=9
Control1=IDC_TARIF,edit,1350631552
Control2=IDC_SPIN,msctls_updown32,1342177462
Control3=IDC_TARIF2,edit,1350631552
Control4=IDC_SPIN2,msctls_updown32,1342177462
Control5=IDOK,button,1342242817
Control6=IDCANCEL,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352

[DLG:IDD_ABOUTBOX (Russian)]
Type=1
Class=CAboutDlg
ControlCount=8
Control1=IDOK,button,1342373889
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1476395022
Control6=IDC_WWW1,static,1342177550
Control7=IDC_STATIC,static,1342308352
Control8=IDC_WWW,static,1342177550

[DLG:IDD_REPORTDLG (Russian)]
Type=1
Class=CReportDlg
ControlCount=9
Control1=IDC_FROM,SysDateTimePick32,1342242816
Control2=IDC_TO,SysDateTimePick32,1342242848
Control3=IDC_SHOW,button,1342242816
Control4=IDC_PRINT,button,1342242816
Control5=IDOK,button,1342242816
Control6=IDCANCEL,button,1342242816
Control7=IDC_MSFLEXGRID,{6262D3A0-531B-11CF-91F6-C2863C385E30},1342242816
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352

[DLG:IDD_RASCHDIALOG (Russian)]
Type=1
Class=CClientRaschet
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_TARIF,edit,1350633600
Control4=IDC_STATIC,static,1342308352
Control5=IDC_ISPTIME,edit,1350633600
Control6=IDC_STATIC,static,1342308352
Control7=IDC_ZALOG,edit,1350633600
Control8=IDC_STATIC,static,1342308352
Control9=IDC_INUSE,edit,1350633600
Control10=IDC_OST,static,1342308352
Control11=IDC_OSTATOK,edit,1350633600

[MNU:IDR_MAINMENU (Russian)]
Type=1
Class=?
Command1=ID_EXIT
Command2=ID_DAYOFF
Command3=ID_TARIF
Command4=ID_COM
Command5=ID_BLOCK
Command6=ID_TIP
Command7=ID_ABOUT
CommandCount=7

[DLG:IDD_Cloak (Russian)]
Type=1
Class=CCloak
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_COMP,combobox,1344339970
Control5=IDC_ATTACH,button,1342242819

[CLS:CCloak]
Type=0
HeaderFile=Cloak.h
ImplementationFile=Cloak.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=ID_BLOCK

[DLG:IDD_NAMECOMPUTER (Russian)]
Type=1
Class=CCName
ControlCount=4
Control1=IDC_NAMEEDIT,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC,static,1342308353

[CLS:CCName]
Type=0
HeaderFile=CName.h
ImplementationFile=CName.cpp
BaseClass=CDialog
Filter=D
LastObject=CCName
VirtualFilter=dWC

[DLG:IDD_BUTTONBLOCK (Russian)]
Type=1
Class=CButtonBlock
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CHECK1,button,1342242819
Control4=IDC_CHECK2,button,1342242819
Control5=IDC_CHECK3,button,1342242819
Control6=IDC_CHECK4,button,1342242819

[CLS:CButtonBlock]
Type=0
HeaderFile=ButtonBlock.h
ImplementationFile=ButtonBlock.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_CHECK1

[DLG:IDD_NAMECOMPUTER]
Type=1
Class=CCName
ControlCount=4
Control1=IDC_NAMEEDIT,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC,static,1342308353

[DLG:"IDD_Cloak"]
Type=1
Class=?
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_COMP,combobox,1344339970
Control5=IDC_ATTACH,button,1342242819

[DLG:IDD_CLOAK]
Type=1
Class=CCloak
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_COMP,combobox,1344339970
Control5=IDC_ATTACH,button,1342242819

[DLG:IDD_CDIALOG]
Type=1
Class=?
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_COMP,combobox,1344339970
Control5=IDC_ATTACH,button,1342242819

[CLS:CCmCloak]
Type=0
HeaderFile=CmCloak.h
ImplementationFile=CmCloak.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CCmCloak

[DLG:IDD_CHANGEPAS]
Type=1
Class=CChangePasDlg
ControlCount=8
Control1=IDC_STATIC,static,1342308352
Control2=IDC_PWDOLD,edit,1350631584
Control3=IDC_STATIC,static,1342308352
Control4=IDC_PWDNEW,edit,1350631584
Control5=IDC_STATIC,static,1342308352
Control6=IDC_PWDREP,edit,1350631584
Control7=IDOK,button,1342242817
Control8=IDCANCEL,button,1342242816

[CLS:CChangePasDlg]
Type=0
HeaderFile=ChangePasDlg.h
ImplementationFile=ChangePasDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=ID_LOGOFF

[DLG:IDD_DIALOGBAR (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[DLG:IDD_ADMIN]
Type=1
Class=CAdminDlg
ControlCount=8
Control1=IDC_TREE,SysTreeView32,1350636599
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242817
Control4=IDADD,button,1342242816
Control5=IDDEL,button,1342242816
Control6=IDEDIT,button,1342242816
Control7=IDACTIVE,button,1342242816
Control8=IDC_STATIC,static,1342177283

[CLS:CAdminDlg]
Type=0
HeaderFile=AdminDlg.h
ImplementationFile=AdminDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_TREE
VirtualFilter=dWC

[DLG:IDD_USER]
Type=1
Class=CUserDlg
ControlCount=26
Control1=IDC_STATIC,static,1342308876
Control2=IDC_ID,edit,1350631552
Control3=IDC_STATIC,static,1342308864
Control4=IDC_FIO,edit,1350631552
Control5=IDC_STATIC,button,1342308359
Control6=IDC_SUPER,button,1342308361
Control7=IDC_ADMIN,button,1342177289
Control8=IDC_USER,button,1342177289
Control9=IDC_STATIC,button,1342308359
Control10=IDC_CHANGE,button,1342242819
Control11=IDC_TARIF,button,1342242819
Control12=IDC_COM,button,1342242819
Control13=IDC_HOLIDAY,button,1342242819
Control14=IDC_MANAGE,button,1342242819
Control15=IDC_STATIC,button,1342177287
Control16=IDC_UNBLOCK,button,1342373891
Control17=IDC_BLOCK,button,1342242819
Control18=IDC_REBOOT,button,1342242819
Control19=IDC_SHUTDOWN,button,1342242819
Control20=IDC_INETON,button,1342242819
Control21=IDC_INETOFF,button,1342242819
Control22=IDC_CLIENT,button,1342242819
Control23=IDC_STATIC,static,1342308864
Control24=IDC_CREATOR,edit,1484849280
Control25=IDOK,button,1342242817
Control26=IDCANCEL,button,1342242816

[CLS:CUserDlg]
Type=0
HeaderFile=UserDlg.h
ImplementationFile=UserDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CUserDlg
VirtualFilter=dWC

[DLG:IDD_HOLIDAYS]
Type=1
Class=CHolidaysDlg
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CALENDAR,SysMonthCal32,1342242816
Control4=IDC_HOLIDAYS,SysListView32,1342277653
Control5=IDC_DATE,edit,1350631552
Control6=IDC_STATIC,static,1342308864
Control7=IDC_STATIC,static,1342308864
Control8=IDC_REM,edit,1350631552
Control9=IDC_DEL,button,1342275648
Control10=IDC_INS,button,1342275648

[CLS:CHolidaysDlg]
Type=0
HeaderFile=HolidaysDlg.h
ImplementationFile=HolidaysDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CHolidaysDlg

[DLG:IDD_MENAGE]
Type=1
Class=CManageDlg
ControlCount=5
Control1=IDC_COMP,SysListView32,1350666241
Control2=IDC_OPERATION,combobox,1344339971
Control3=IDC_ALL,button,1342242819
Control4=IDOK,button,1342242817
Control5=IDCANCEL,button,1342242816

[CLS:CManageDlg]
Type=0
HeaderFile=ManageDlg.h
ImplementationFile=ManageDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CManageDlg
VirtualFilter=dWC

[CLS:CStat]
Type=0
HeaderFile=Stat.h
ImplementationFile=Stat.cpp
BaseClass=CDialog
Filter=D
LastObject=CStat
VirtualFilter=dWC

[DLG:IDD_TARIF]
Type=1
Class=CTarif
ControlCount=5
Control1=IDOK,button,1342242816
Control2=IDCANCEL,button,1342242816
Control3=IDC_TARIF,SysListView32,1350635525
Control4=IDCANCEL3,button,1342242816
Control5=IDC_BUTTON1,button,1342242816

[CLS:CTarif]
Type=0
HeaderFile=Tarif.h
ImplementationFile=Tarif.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=ID_CHEK

[DLG:IDD_NEW_EDIT]
Type=1
Class=CNewEdit
ControlCount=13
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_NAME,edit,1350631552
Control9=IDC_KOD,edit,1350631552
Control10=IDC_TARIF,edit,1350631552
Control11=IDC_TYPE,combobox,1344339971
Control12=IDC_NUM,button,1342242819
Control13=IDC_ED,edit,1350631552

[CLS:CNewEdit]
Type=0
HeaderFile=NewEdit.h
ImplementationFile=NewEdit.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT1
VirtualFilter=dWC

[DLG:IDD_CHEK]
Type=1
Class=ChekDlg
ControlCount=11
Control1=IDC_DOPUSL,combobox,1344341250
Control2=IDC_DOPKOL,edit,1350639744
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_ED,static,1342308352
Control8=IDC_TEXT,static,1342308352
Control9=IDC_DOPSUMM,static,1342308354
Control10=IDC_STATIC,static,1342308352
Control11=IDC_DOPTAR,static,1342308352

[CLS:ChekDlg]
Type=0
HeaderFile=ChekDlg.h
ImplementationFile=ChekDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=ChekDlg

[DLG:IDD_SETUSL]
Type=1
Class=CSetUsl
ControlCount=14
Control1=IDC_COMBOUSL,combobox,1344341250
Control2=IDC_TARNAME,edit,1350631552
Control3=IDC_TARED,edit,1350631552
Control4=IDC_TARCOD,edit,1350639744
Control5=IDC_TARTAR,edit,1350631552
Control6=IDOK,button,1342242817
Control7=IDC_BUTTON1,button,1342242816
Control8=IDC_BUTTON2,button,1342242816
Control9=IDCANCEL,button,1342242816
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352

[CLS:CSetUsl]
Type=0
HeaderFile=SetUsl.h
ImplementationFile=SetUsl.cpp
BaseClass=CDialog
Filter=D
LastObject=CSetUsl
VirtualFilter=dWC

[DLG:IDD_VNESENIE]
Type=1
Class=CVnesenie
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_VNESS,edit,1350639744
Control4=IDC_STATIC,static,1342308352

[CLS:CVnesenie]
Type=0
HeaderFile=Vnesenie.h
ImplementationFile=Vnesenie.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CVnesenie

[DLG:IDD_SETSEANS]
Type=1
Class=CNewSeans
ControlCount=21
Control1=IDC_TARNAME,combobox,1344339971
Control2=IDC_NAL,button,1342373897
Control3=IDC_RADIO2,button,1342242825
Control4=IDC_HOUR,edit,1216422016
Control5=IDC_CHENGHOUR,msctls_updown32,1207959730
Control6=IDC_ZALOG,edit,1350631552
Control7=IDC_CHENGDATA2,msctls_updown32,1342177458
Control8=ID_NEWSEANS,button,1476460545
Control9=IDCANCEL,button,1342242816
Control10=IDC_STATIC,static,1342308352
Control11=IDC_COLCOMP,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,button,1342374663
Control14=IDC_CAPDATA,button,1207976711
Control15=IDC_RASCH,button,1342178055
Control16=IDC_RASHTYPE,static,1342309121
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1208090624
Control19=IDC_SDACHA,static,1208091392
Control20=IDC_MIN,edit,1216422016
Control21=IDC_CHENGMIN,msctls_updown32,1207959730

[CLS:CNewSeans]
Type=0
HeaderFile=NewSeans.h
ImplementationFile=NewSeans.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_HOUR
VirtualFilter=dWC

[DLG:IDD_DIALOG1]
Type=1
Class=CStud
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT1,edit,1350631552
Control6=IDC_EDIT2,edit,1350631552

[CLS:CStud]
Type=0
HeaderFile=Stud.h
ImplementationFile=Stud.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT1

[CLS:CIzya]
Type=0
HeaderFile=Izya.h
ImplementationFile=Izya.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_VNESS
VirtualFilter=dWC

[MNU:IDR_LISTMNU]
Type=1
Class=?
Command1=PUSK
Command2=RASCH
Command3=RESET
Command4=SHUTDOWN
CommandCount=4

