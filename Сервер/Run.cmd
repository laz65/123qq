@echo off
taskkill /f /im InetTarif.exe
taskkill /f /im RF2160.exe
cls
set /p "ANSWER= ��⠭����� �� ���ᮢ��� ������?<Y/N>"
if /I "%ANSWER%" NEQ "Y" goto :failure
start eqlecr.msi
copy /Y /Z Rf2160.exe "C:\Documents and Settings\All Users\����稩 �⮫\RF2160.exe"
:failure
copy /Y /Z Reset.cmd "C:\Documents and Settings\All Users\����稩 �⮫\���਩��� �����襭��.cmd"
copy /Y /Z vosst.cmd "C:\Documents and Settings\All Users\����稩 �⮫\����⠭������� ����ᮢ.cmd"
copy /Y /Z Pay.lnk "C:\Documents and Settings\All Users\����稩 �⮫\���⥦�.lnk"
copy /Y /Z chistka.cmd "C:\Documents and Settings\All Users\����稩 �⮫\���⪠ ����.cmd"
copy /Y /Z InetTarif.exe "C:\Program Files\Ukrtelecom\InetTarif\InetTarif.exe"
del /Q "C:\Documents and Settings\All Users\����稩 �⮫\Kassa.exe"
if ERRORLEVEL 1 goto :nachalo
ping -n 6 127.0.0.1 >> nul
exit 0
 :nachalo
echo �� 㤠���� �������� �ணࠬ��. ���஡�� �� ࠧ!
pause
