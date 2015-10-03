@echo off
echo. >"hlp\InetTarif.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\InetTarif.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\InetTarif.hm"
echo. >>"hlp\InetTarif.hm"
echo // Prompts (IDP_*) >>"hlp\InetTarif.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\InetTarif.hm"
echo. >>"hlp\InetTarif.hm"
echo // Resources (IDR_*) >>"hlp\InetTarif.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\InetTarif.hm"
echo. >>"hlp\InetTarif.hm"
echo // Dialogs (IDD_*) >>"hlp\InetTarif.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\InetTarif.hm"
echo. >>"hlp\InetTarif.hm"
echo // Frame Controls (IDW_*) >>"hlp\InetTarif.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\InetTarif.hm"

if errorlevel 1 goto VCReportError
goto VCEnd
:VCReportError
echo Project : error PRJ0019: Инструмент вернул код ошибки из "Making help include file..."
exit 1
:VCEnd