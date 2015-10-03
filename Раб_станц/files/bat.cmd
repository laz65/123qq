xcopy /Y  /S   "C:\Documents and Settings\guest\Рабочий стол\*.*" D:\Public\*.* 
xcopy /Y  /S   "C:\Documents and Settings\guest\Мои документы\*.*" D:\Public\*.* 
del /Q /S  "C:\Documents and Settings\guest\Рабочий стол\*.*"
del /Q /S  "C:\Documents and Settings\guest\Мои документы\*.*"
del /Q /S  "C:\Documents and Settings\guest\Local Settings\Temp\*.*"
taskkill /f /im iexplore.exe
taskkill /f /im chrome.exe
goto start
:REFcmd
for /d %%i in ("%~1\*") do (call :REFcmd "%%i" & rd /s /q "%%i")
exit /b
:start
call :REFcmd "C:\Documents and Settings\guest\Рабочий стол"
call :REFcmd "C:\Documents and Settings\guest\Мои документы"
call :REFcmd "C:\Documents and Settings\guest\Local Settings\Temp"
copy /Y  /Z  "D:\Public\Ukrtelecom_777_.bmp" C:\Windows\2.bmp
copy /Y  /Z  "D:\Public\Soglashenie_777_.txt" C:\Windows\my.txt
del /Q /S  "D:\Public\Ukrtelecom_777_.bmp"
del /Q /S  "D:\Public\Soglashenie_777_.txt"
reg add "HKCU\Control Panel\Desktop" /v "Wallpaper" /t REG_SZ /d "c:\Windows\2.bmp" /f
reg add "HKCU\Control Panel\Desktop" /v "WallpaperStyle" /t REG_SZ /d "2" /f
RUNDLL32.EXE user32.dll,UpdatePerUserSystemParameters
c:
cd c:\Windows
view.exe
exit 0
