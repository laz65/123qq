@echo off
:nachalo
runas  /env /user:�����������  "cmd  /K RUN_ME.cmd"
if ERRORLEVEL 1 goto :nachalo
pause