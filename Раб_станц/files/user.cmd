@echo off
taskkill /f /im wLocker.exe
ping -w 1000 127.0.0.1 >> null
xcopy /Y  /S   "C:\Documents and Settings\guest\����稩 �⮫\*.*"  "C:\Documents and Settings\All Users\����稩 �⮫\*.*"
del /Q /S  "C:\Documents and Settings\guest\����稩 �⮫\*.*"
powercfg /s "����祭 ����ﭭ�"
powercfg /x "����祭 ����ﭭ�" /monitor-timeout-ac 0
powercfg /x "����祭 ����ﭭ�" /standby-timeout-ac 0
powercfg /x "����祭 ����ﭭ�" /disk-timeout-ac 20
instsrv wLocker "c:\Windows\srvany.exe"
reg delete "HKEY_CURRENT_USER\Control Panel\Desktop" /v SCRNSAVE.EXE /f
reg delete "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\SafeBoot\Network" /f
regedit /s C:\Windows\user.reg
net localgroup ������������ guest /DELETE
shutdown -r -t 02
exit 0