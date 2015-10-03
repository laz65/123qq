@echo off 
echo  ______________________________________
echo          Завершение задачи тарификатора           
echo  ______________________________________
echo Вы действительно хотите аварийно завершить 
set /p "ANSWER= работу Интернет тарификатора? <Y/N> "

if /I "%ANSWER%" NEQ "Y" goto :failure

taskkill /f /im InetTarif.exe

:failure