param(
    [string]$TargetDir,
    [string]$AllUsers = "false"
)

if (-not $TargetDir) {
    throw "TargetDir is empty"
}

$extension = ".qrs"
$progId = "qrs_auto_file"
$description = "TRIK Studio Project"
$contentType = "application/octet-stream"

$vbs = Join-Path $TargetDir "trik-studio.vbs"
$icon = Join-Path $TargetDir "trik-studio.ico"

$command = "C:\Windows\System32\wscript.exe //nologo //b // `"$vbs`" `"%1`""

$allUsersEnabled = $AllUsers -eq "true"

if ($allUsersEnabled) {
    $root = "HKLM:"
} else {
    $root = "HKCU:"
}

$classes = "$root\Software\Classes"

# Register file extension
$extensionPath = "$classes\$extension"

New-Item -Path $extensionPath -Force | Out-Null

Set-ItemProperty `
    -Path $extensionPath `
    -Name "(default)" `
    -Value $progId

Set-ItemProperty `
    -Path $extensionPath `
    -Name "Content Type" `
    -Value $contentType

# Register ProgId
$progIdPath = "$classes\$progId"

New-Item -Path $progIdPath -Force | Out-Null

Set-ItemProperty `
    -Path $progIdPath `
    -Name "(default)" `
    -Value $description

# Register OpenWithProgIds
$openWith = "$extensionPath\OpenWithProgIds\$progId"

New-Item -Path $openWith -Force | Out-Null

Set-ItemProperty `
    -Path $openWith `
    -Name "(default)" `
    -Value ""

# Register open command
$commandPath = "$progIdPath\shell\open\command"

New-Item `
    -Path $commandPath `
    -Force | Out-Null

Set-ItemProperty `
    -Path $commandPath `
    -Name "(default)" `
    -Value $command

# Register icon
$iconPath = "$progIdPath\DefaultIcon"

New-Item `
    -Path $iconPath `
    -Force | Out-Null

Set-ItemProperty `
    -Path $iconPath `
    -Name "(default)" `
    -Value $icon
