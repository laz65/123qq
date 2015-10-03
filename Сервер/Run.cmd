@echo off
taskkill /f /im InetTarif.exe
taskkill /f /im RF2160.exe
cls
set /p "ANSWER= Установить ПО кассового аппарата?<Y/N>"
if /I "%ANSWER%" NEQ "Y" goto :failure
start eqlecr.msi
copy /Y /Z Rf2160.exe "C:\Documents and Settings\All Users\Рабочий стол\RF2160.exe"
:failure
copy /Y /Z Reset.cmd "C:\Documents and Settings\All Users\Рабочий стол\Аварийное завершение.cmd"
copy /Y /Z vosst.cmd "C:\Documents and Settings\All Users\Рабочий стол\Восстановление авансов.cmd"
copy /Y /Z Pay.lnk "C:\Documents and Settings\All Users\Рабочий стол\Платежи.lnk"
copy /Y /Z chistka.cmd "C:\Documents and Settings\All Users\Рабочий стол\Чистка базы.cmd"
copy /Y /Z InetTarif.exe "C:\Program Files\Ukrtelecom\InetTarif\InetTarif.exe"
del /Q "C:\Documents and Settings\All Users\Рабочий стол\Kassa.exe"
if ERRORLEVEL 1 goto :nachalo
ping -n 6 127.0.0.1 >> nul
exit 0
 :nachalo
echo Не удалось обновить программу. Попробуйте еще раз!
pause
