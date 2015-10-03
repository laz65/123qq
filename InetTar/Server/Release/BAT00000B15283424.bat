@echo off
start /wait /C /E /M "hlp\InetTarif.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\InetTarif.hlp" goto :Error
copy "hlp\InetTarif.hlp" ".\Release"
goto :done
:Error
echo hlp\"InetTarif".hpj(1) : error:
type "hlp\InetTarif.log"
:done

if errorlevel 1 goto VCReportError
goto VCEnd
:VCReportError
echo Project : error PRJ0019: Инструмент вернул код ошибки из "Making help file..."
exit 1
:VCEnd