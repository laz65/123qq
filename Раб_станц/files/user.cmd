@echo off
taskkill /f /im wLocker.exe
ping -w 1000 127.0.0.1 >> null
xcopy /Y  /S   "C:\Documents and Settings\guest\Рабочий стол\*.*"  "C:\Documents and Settings\All Users\Рабочий стол\*.*"
del /Q /S  "C:\Documents and Settings\guest\Рабочий стол\*.*"
powercfg /s "Включен постоянно"
powercfg /x "Включен постоянно" /monitor-timeout-ac 0
powercfg /x "Включен постоянно" /standby-timeout-ac 0
powercfg /x "Включен постоянно" /disk-timeout-ac 20
instsrv wLocker "c:\Windows\srvany.exe"
reg delete "HKEY_CURRENT_USER\Control Panel\Desktop" /v SCRNSAVE.EXE /f
reg delete "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\SafeBoot\Network" /f
regedit /s C:\Windows\user.reg
net localgroup Администраторы guest /DELETE
shutdown -r -t 02
exit 0