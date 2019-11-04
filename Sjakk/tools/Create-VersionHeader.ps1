# Use this to build version header file
#
# Provide source path which contains both the .ini file and the output header location.  INI path and OutHeaderPath
# are relative path to the Sourcepath.  Create "General" section and add any number of settings, these will be 
# prepended with "MY_".  Create "Version" section with at least "versionbuild" and "versionyear" setting. These 
# will be updated, the versionyear to the current year, versionbuild will be incremented by one.
#
# Example input file:
#
# [General]
# appname=Sjakk
# orgdomain=snorkelbuckle.net
# orgname=SnorkelBuckle
#
# [Version]
# versionbuild=84
# versionmajor=0
# versionminor=1
# versionyear=2019
#
# Example output:
#
# #ifndef CONFIG_H
# define CONFIG_H
#
# define MY_ORGDOMAIN "snorkelbuckle.net"
# define MY_APPNAME "Sjakk"
# define MY_ORGNAME "SnorkelBuckle"
# define MY_VERSIONYEAR "2019"
# define MY_VERSIONMINOR "1"
# define MY_VERSIONMAJOR "0"
# define MY_VERSIONBUILD "85"
#
# #endif // CONFIG_H
#

param(
#    [Parameter(Mandatory=$false)][String]$SourcePath,
    [Parameter(Mandatory=$false)][String]$IniPath,
    [Parameter(Mandatory=$false)][String]$OutHeaderPath
)

. .\Ini-Files.ps1

#if (-not($PSBoundParameters.ContainsKey('SourcePath')))
#{
    #Write-Output "-SourcePath is required"
    #exit 1
#}
if (-not($PSBoundParameters.ContainsKey('IniPath')))
{
    Write-Output "-IniPath is required"
    exit 1
}
if (-not($PSBoundParameters.ContainsKey('OutHeaderPath')))
{
    Write-Output "-OutHeaderPath is required"
    exit 1
}

#$ini = Get-IniContent $("$SourcePath" + '\' + "$IniPath")
$ini = Get-IniContent $("$IniPath")
$ini.Version.versionbuild = [string]([int]$ini.Version.versionbuild + 1)
$ini.Version.versionyear = (Get-Date).Year
$sb = [System.Text.StringBuilder]::new()
[void]$sb.Append($ini.General.appname)
[void]$sb.Append($ini.Version.versionyear)
[void]$sb.Append("-")
[void]$sb.Append($ini.General.releasetype)
[void]$sb.Append("-v")
[void]$sb.Append($ini.Version.versionmajor)
[void]$sb.Append(".")
[void]$sb.Append($ini.Version.versionminor)
[void]$sb.Append(".")
[void]$sb.Append($ini.Version.versionbuild)
[void]$sb.Append(".exe")
$ini.NSIS.nsisinstaller = $sb.ToString()

#$stream = [System.IO.StreamWriter] $("$SourcePath" + '\' + "$OutHeaderPath")
$stream = [System.IO.StreamWriter] $("$OutHeaderPath")
$stream.WriteLine("#ifndef CONFIG_H")
$stream.WriteLine("#define CONFIG_H")
$stream.WriteLine()
foreach ($key in $ini.General.Keys)
{
    $stream.WriteLine("#define MY_$($key.ToUpper()) " + '"' + "$($ini.General[$key])" + '"')
}
foreach ($key in $ini.Version.Keys)
{
    $stream.WriteLine("#define MY_$($key.ToUpper()) " + '"' + "$($ini.Version[$key])" + '"')
}
$stream.WriteLine()
$stream.WriteLine("#endif // CONFIG_H")
$stream.Close()

#Out-IniFile -InputObject $ini -FilePath $("$SourcePath" + '\' + "$IniPath")
Out-IniFile -InputObject $ini -FilePath $("$IniPath")
exit 0

