@echo off
echo  ______________________________________
echo                 ����⠭������� ����ᮢ            
echo  ______________________________________
echo �� ����⢨⥫쭮 ��� ����⠭����� �।��騥 
set /p "ANSWER= ���祭�� ����ᮢ (�⬥���� ��᫥���� ������)? <Y/N> "

if /I "%ANSWER%" NEQ "Y" goto :failure

taskkill /f /im InetTarif.exe
copy /Y /Z "C:\Program Files\Ukrtelecom\InetTarif\avans.bac" "C:\Program Files\Ukrtelecom\InetTarif\avans.ini"
echo ��⮢�!
pause:
:failure
