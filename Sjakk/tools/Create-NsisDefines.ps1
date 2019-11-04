param(
    [Parameter(Mandatory=$false)][String]$IniPath,
    [Parameter(Mandatory=$false)][String]$PackageDir,
    [Parameter(Mandatory=$false)][String]$DefinesHdr
)

. .\Ini-Files.ps1
. .\Get-FolderSize.ps1

if (-not($PSBoundParameters.ContainsKey('IniPath')))
{
    Write-Output "-IniPath is required"
    exit 1
}
if (-not($PSBoundParameters.ContainsKey('PackageDir')))
{
    Write-Output "-PackageDir is required"
    exit 1
}


$ini = Get-IniContent $("$IniPath")

# Count package size
$dirsize = Get-FolderSize -Path $("$PackageDir")

$stream = [System.IO.StreamWriter] $("$PackageDir" + '\' + "$DefinesHdr")
$stream.WriteLine()
foreach ($key in $ini.General.Keys)
{
    $stream.WriteLine("!define MY_$($key.ToUpper()) " + '"' + "$($ini.General[$key])" + '"')
}
foreach ($key in $ini.Version.Keys)
{
    $stream.WriteLine("!define MY_$($key.ToUpper()) " + '"' + "$($ini.Version[$key])" + '"')
}
foreach ($key in $ini.NSIS.Keys)
{
    $stream.WriteLine("!define MY_$($key.ToUpper()) " + '"' + "$($ini.NSIS[$key])" + '"')
}
$stream.WriteLine("!define MY_INSTALLSIZE " + '"' + "$($dirsize.TotalBytes / 1024)" + '"')
$stream.WriteLine()
$stream.Close()
