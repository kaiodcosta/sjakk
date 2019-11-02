!include nsis-helper.nsh

RequestExecutionLevel admin
InstallDir "$PROGRAMFILES\${MY_ORGNAME}\${MY_APPNAME}"

LicenseData "${MY_LICENSENOTICE}"

Name "${MY_APPNAME} ${MY_VERSIONYEAR}"
Icon "${MY_LOGOICO}"
OutFile "${MY_NSISINSTALLER}"

!include LogicLib.nsh

# Just three pages - license agreement, install location, and installation
page license
page directory
Page instfiles

!macro VerifyUserIsAdmin
UserInfo::GetAccountType
pop $0
${If} $0 != "admin" ;Require admin rights on NT4+
        messageBox mb_iconstop "Administrator rights required!"
        setErrorLevel 740 ;ERROR_ELEVATION_REQUIRED
        quit
${EndIf}
!macroend

function .onInit
        setShellVarContext all
        !insertmacro VerifyUserIsAdmin
functionEnd

section "install"
        # Files for the install directory - to build the installer, these should be in the same directory as the install script (this file)
		!include install-files.nsh

        # Uninstaller - See function un.onInit and section "uninstall" for configuration
        writeUninstaller "$INSTDIR\uninstall.exe"

        # Start Menu
        createDirectory "$SMPROGRAMS\${MY_ORGNAME}"
        createShortCut "$SMPROGRAMS\${MY_ORGNAME}\${MY_APPNAME}.lnk" "$INSTDIR\${MY_APPEXE}" "" "$INSTDIR\${MY_LOGOICO}"

        # Registry information for add/remove programs
        WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${MY_ORGNAME} ${MY_APPNAME}" "DisplayName" "${MY_APPNAME} ${MY_VERSIONYEAR} - ${MY_DESCRIPTION}"
        WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${MY_ORGNAME} ${MY_APPNAME}" "UninstallString" "$\"$INSTDIR\uninstall.exe$\""
        WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${MY_ORGNAME} ${MY_APPNAME}" "QuietUninstallString" "$\"$INSTDIR\uninstall.exe$\" /S"
        WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${MY_ORGNAME} ${MY_APPNAME}" "InstallLocation" "$\"$INSTDIR$\""
        WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${MY_ORGNAME} ${MY_APPNAME}" "DisplayIcon" "$\"$INSTDIR\${MY_LOGOICO}$\""
        WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${MY_ORGNAME} ${MY_APPNAME}" "Publisher" "$\"${MY_ORGNAME}$\""
        WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${MY_ORGNAME} ${MY_APPNAME}" "HelpLink" "$\"${MY_HELPURL}$\""
        WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${MY_ORGNAME} ${MY_APPNAME}" "URLUpdateInfo" "$\"${MY_UPDATEURL}$\""
        WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${MY_ORGNAME} ${MY_APPNAME}" "URLInfoAbout" "$\"${MY_ABOUTURL}$\""
        WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${MY_ORGNAME} ${MY_APPNAME}" "DisplayVersion" "$\"${MY_VERSIONMAJOR}.${MY_VERSIONMINOR}.${MY_VERSIONBUILD}$\""
        WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${MY_ORGNAME} ${MY_APPNAME}" "VersionMajor" ${MY_VERSIONMAJOR}
        WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${MY_ORGNAME} ${MY_APPNAME}" "VersionMinor" ${MY_VERSIONMINOR}
        WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${MY_ORGNAME} ${MY_APPNAME}" "VersionBuild" ${MY_VERSIONBUILD}
        WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${MY_ORGNAME} ${MY_APPNAME}" "VersionYear" ${MY_VERSIONYEAR}
        # There is no option for modifying or repairing the install
        WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${MY_ORGNAME} ${MY_APPNAME}" "NoModify" 1
        WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${MY_ORGNAME} ${MY_APPNAME}" "NoRepair" 1
        # Set the installsize constant (!defined at the top of this script) so Add/Remove Programs can accurately report the size
        WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${MY_ORGNAME} ${MY_APPNAME}" "EstimatedSize" ${MY_INSTALLSIZE}
sectionEnd

# Uninstaller

function un.onInit
        SetShellVarContext all

        #Verify the uninstaller - last chance to back out
        MessageBox MB_OKCANCEL "Permanantly remove ${MY_APPNAME}?" IDOK next
                Abort
        next:
        !insertmacro VerifyUserIsAdmin
functionEnd

section "uninstall"
        # Remove Start Menu launcher
        delete "$SMPROGRAMS\${MY_ORGNAME}\${MY_APPNAME}.lnk"
        # Try to remove the Start Menu folder - this will only happen if it is empty
        rmDir "$SMPROGRAMS\${MY_ORGNAME}"

        # Remove files
		!include uninstall-files.nsh

        # Always delete uninstaller as the last action
        delete $INSTDIR\uninstall.exe

        # Try to remove the install directory - this will only happen if it is empty
        rmDir $INSTDIR

        # Remove uninstaller information from the registry
        DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${MY_ORGNAME} ${MY_APPNAME}"
sectionEnd
