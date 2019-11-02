@echo on
if %1.==. goto invalidargs
if %2.==. goto invalidargs
if %3.==. goto invalidargs

set pwshelltools=D:\Development\Projects\cpp\sjakk-chess-client-qt\Sjakk\tools
set nsis-creator=D:\Development\Projects\cpp\sjakk-chess-client-qt\Sjakk\tools\Create-NsisPackage.ps1
set nsis-fileshdr=D:\Development\Projects\cpp\sjakk-chess-client-qt\Sjakk\tools\Create-NsisFilesInstallSection.ps1
set nsis-ini=D:\Development\Projects\cpp\sjakk-chess-client-qt\Sjakk\installer\sjakk-nsis.ini
set safedir=D:\Development\Projects\cpp\sjakk-chess-client-qt\build-Sjakk-Qt-Desktop_Qt_5_13_0_MinGW_32_bit-Release
set packagedir=%~1
set executable=%~2
set externaldlls=%~3

set cwd=%CD%

@rem Clean the package directory
cd "%safedir%"
rmdir /s /q "%safedir%\%packagedir%"
mkdir "%safedir%\%packagedir%"

@rem Deploy dependent Qt libraries
windeployqt --dir "%safedir%\%packagedir%" "%executable%"

@rem Deploy executable and additional libraries
copy "%executable%" "%safedir%\%packagedir%"
copy "%externaldlls%" "%safedir%\%packagedir%"

@rem Create NSIS header for file install and uninstall
@rem cd "%pwshelltools%"
@rem powershell.exe -File "%nsis-fileshdr%" -PackageDir "%safedir%\%packagedir%" -UninstallFilesHdr uninstall-files.nsh -InstallFilesHdr install-files.nsh

@rem Create NSIS Package
cd "%pwshelltools%"
powershell.exe -File "%nsis-creator%" -IniPath "%nsis-ini%" -PackageDir "%safedir%\%packagedir%"
goto finished

:invalidargs
echo Empty arguments not allowed
exit /B

:finished
cd "%cwd%"
exit /B
