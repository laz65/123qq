@echo off 
echo  ______________________________________
echo          �����襭�� ����� ��䨪���           
echo  ______________________________________
echo �� ����⢨⥫쭮 ��� ���਩�� �������� 
set /p "ANSWER= ࠡ��� ���୥� ��䨪���? <Y/N> "

if /I "%ANSWER%" NEQ "Y" goto :failure

taskkill /f /im InetTarif.exe

:failure