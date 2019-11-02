param(
    [Parameter(Mandatory=$false)][String]$IniPath,
    [Parameter(Mandatory=$false)][String]$PackageDir
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

Function Build-Install-List
{
    param([string]$Folder)

    $file_list = New-Object System.Collections.Generic.List[string]
    $dlist = Get-ChildItem -Path $Folder
    foreach ($ditem in $dlist)
    {
        if ($ditem.PSIscontainer)
        {
            Build-Install-List -Folder $ditem.FullName
        }
        else
        {
            $file_list.Add($ditem.FullName)
        }
    }
    $chopped_folder = $Folder.Remove(0,$chop_path.Length)
    "setOutPath `$INSTDIR{0}" -f $chopped_folder
    foreach ($fitem in $file_list)
    {
        $chopped_file = $fitem.Remove(0,$chop_path.Length + 1)
        "file {0}" -f $chopped_file
    }
    " "
}

Function Build-Uninstall-List
{
    param([string]$Folder)

    $file_list = New-Object System.Collections.Generic.List[string]
    $dlist = Get-ChildItem -Path $Folder
    foreach ($ditem in $dlist)
    {
        if ($ditem.PSIscontainer)
        {
            Build-Uninstall-List -Folder $ditem.FullName
        }
        else
        {
            $file_list.Add($ditem.FullName)
        }
    }
    foreach ($fitem in $file_list)
    {
        $chopped_file = $fitem.Remove(0,$chop_path.Length + 1)
        "delete {0}" -f $chopped_file
    }
    
    if ($Folder -ne $PackageDir)
    {
        $chopped_folder = $Folder.Remove(0,$chop_path.Length)
        "rmDir `$INSTDIR{0}" -f $chopped_folder
    }
    " "
}

$ini = Get-IniContent $("$IniPath")

# Copy additional files to package directory
foreach ($key in $ini.CopyToPackageDir.Keys)
{
    Write-Host "key=" $key "path=" $ini.CopyToPackageDir[$key]
    Copy-Item -Path $ini.CopyToPackageDir[$key] -Destination $("$PackageDir") -Verbose
}

# Build installation file listing and uninstall listing
$chop_path = $PackageDir
$dlist = Get-ChildItem -Path $PackageDir
$inst_list = Build-Install-List $PackageDir
$uninst_list = Build-Uninstall-List $PackageDir

$stream = [System.IO.StreamWriter] $("$PackageDir" + '\' + "$($ini.NSIS.nsisinstallfiles)")
foreach ($id in $inst_list)
{
    $stream.WriteLine($id)
}
$stream.Close()

$stream = [System.IO.StreamWriter] $("$PackageDir" + '\' + "$($ini.NSIS.nsisuninstallfiles)")
foreach ($id in $uninst_list)
{
    $stream.WriteLine($id)
}
$stream.Close()


# Count package size
$dirsize = Get-FolderSize -Path $("$PackageDir")

# Write the NSIS header
#   The NSI file should reference $NsisHeader which will reside in $PackageDir
$stream = [System.IO.StreamWriter] $("$PackageDir" + '\' + "$($ini.NSIS.nsisheader)")
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

# Copy the installer script
Copy-Item -Path $ini.NSIS.nsiscriptpath -Destination $("$PackageDir") -Verbose

$cwd = Get-Location
Set-Location -Path $("$PackageDir")
makensis $ini.NSIS.nsiscript
Set-Location -Path $cwd.Path
exit 0
