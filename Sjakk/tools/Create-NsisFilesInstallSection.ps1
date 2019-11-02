﻿param(
     [Parameter(Mandatory=$false)][String]$PackageDir,
     [Parameter(Mandatory=$false)][String]$InstallFilesHdr,
     [Parameter(Mandatory=$false)][String]$UninstallFilesHdr
)

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

$chop_path = $PackageDir
$dlist = Get-ChildItem -Path $PackageDir
$inst_list = Build-Install-List $PackageDir
$uninst_list = Build-Uninstall-List $PackageDir

$stream = [System.IO.StreamWriter] $("$PackageDir" + '\' + "$($InstallFilesHdr)")
foreach ($id in $inst_list)
{
    $stream.WriteLine($id)
}
$stream.Close()

$stream = [System.IO.StreamWriter] $("$PackageDir" + '\' + "$($UninstallFilesHdr)")
foreach ($id in $uninst_list)
{
    $stream.WriteLine($id)
}
$stream.Close()

