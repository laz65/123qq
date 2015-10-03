@echo off
echo  ______________________________________
echo                 Восстановление авансов            
echo  ______________________________________
echo Вы действительно хотите восстановить предыдущие 
set /p "ANSWER= значения авансов (отменить последнюю операцию)? <Y/N> "

if /I "%ANSWER%" NEQ "Y" goto :failure

taskkill /f /im InetTarif.exe
copy /Y /Z "C:\Program Files\Ukrtelecom\InetTarif\avans.bac" "C:\Program Files\Ukrtelecom\InetTarif\avans.ini"
echo Готово!
pause:
:failure
