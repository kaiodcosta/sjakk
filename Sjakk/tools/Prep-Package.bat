@echo on
if %1.==. goto invalidargs
if %2.==. goto invalidargs
if %3.==. goto invalidargs
if %4.==. goto invalidargs

set sourcedir=%~1
set safedir=%~2
set packagedir=%~3
set executable=%~4

set pwshelltools="%sourcedir%\Sjakk\tools"
set nsis-fileslist="%sourcedir%\Sjakk\tools\Create-NsisFilesList.ps1"
set nsis-defines="%sourcedir%\Sjakk\tools\Create-NsisDefines.ps1"
set nsis-ini="%sourcedir%\Sjakk\installer\sjakk-nsis.ini"
set nsis-nsi="%sourcedir%\Sjakk\installer\windows-installer.nsi"

set cwd=%CD%

@rem Clean the package directory
cd "%safedir%"
rmdir /s /q "%safedir%\%packagedir%"
mkdir "%safedir%\%packagedir%"

@rem Deploy dependent Qt libraries
windeployqt --dir "%safedir%\%packagedir%" "%executable%"

@rem Deploy executable
copy "%executable%" "%safedir%\%packagedir%"

@rem Copy additional files needed for package
copy "%sourcedir%\Sjakk\license-notice.txt" "%safedir%\%packagedir%"
copy "%sourcedir%\Sjakk\COPYING" "%safedir%\%packagedir%"
copy "%sourcedir%\Sjakk\media\icons\Sjakk.ico" "%safedir%\%packagedir%"

@rem Build install hdr and uninstall hdr
cd "%pwshelltools%"
powershell.exe -File "%nsis-fileslist%" -PackageDir "%safedir%\%packagedir%" -InstallHdr "install-files.nsh" -UninstallHdr "uninstall-files.nsh"

@rem Build defines hdr
powershell.exe -File "%nsis-defines%" -PackageDir "%safedir%\%packagedir%" -IniPath "%nsis-ini%" -DefinesHdr "nsis-helper.nsh"

@rem Copy NSIS installer script
copy "%nsis-nsi%" "%safedir%\%packagedir%"

@rem Create NSIS Package
cd "%safedir%\%packagedir%"
makensis windows-installer.nsi
goto finished

:invalidargs
echo Empty arguments not allowed
exit /B

:finished
cd "%cwd%"
exit /B
