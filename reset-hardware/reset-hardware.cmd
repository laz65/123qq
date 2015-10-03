@echo off 

echo  ______________________________________
echo          Очистка оборудования          
echo  ______________________________________
echo Вы действительно хотите очистить все даные 
set /p "ANSWER= о оборудовании? <Y/N> "

if /I "%ANSWER%" NEQ "Y" goto :failure

:: Остановка служб обнаружения устройств
net stop "Plug and Play"
net stop "Определение оборудования оболочки"

:: CPU 
devcon remove ACPI\Processor 
 
::GAME Port 
devcon remove PCI\CC_09* 
 
::Network adapter 
devcon remove PCI\CC_02* 
 
::Sound card 
devcon remove PCI\CC_04* 
 
:: USB HOST and SMBus 
devcon remove PCI\CC_0C* 
 
:: Monitor 
devcon remove DISPLAY\* 
 
:: Video adapter 
devcon remove PCI\CC_03* 
 
:: Chipset 
devcon remove PCI\CC_0604* 
 
:: Type storage (?) 
devcon remove @STORAGE\* 
 
:: USB storage 
devcon remove @USBSTOR\* 
 
:: USB devices 
devcon remove @USB\* 
 
:: Ports (?) 
devcon remove @HID\* 
 
:: IDE devices 
devcon remove @ide\* 
 
:: IDE Channel 
devcon remove @PCIIDE\*

:: Чистка сетевых записей реестра
reg delete "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Network\{4d36e972-e325-11ce-bfc1-08002be10318}" /f

:failure