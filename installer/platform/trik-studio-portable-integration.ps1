[CmdletBinding(SupportsShouldProcess = $true, ConfirmImpact = "Medium")]
param(
	[Parameter(Mandatory = $true)]
	[ValidateSet("install", "uninstall")]
	[string]$Action,

	[string]$InstallDirectory = $PSScriptRoot
)

$ErrorActionPreference = "Stop"
$installRoot = (Resolve-Path -LiteralPath $InstallDirectory).Path
$programsDirectory = [Environment]::GetFolderPath([Environment+SpecialFolder]::Programs)
$startMenuGroup = Join-Path $programsDirectory "TRIK Studio Portable"
$studioProgId = "TRIKStudioPortable.QrsEditor"
$playerProgId = "TRIKStudioPortable.QrsPlayer"

function Set-RegistryString {
	param(
		[Microsoft.Win32.RegistryKey]$Root,
		[string]$SubKey,
		[string]$Name,
		[string]$Value
	)

	$key = $Root.CreateSubKey($SubKey)
	try {
		$key.SetValue($Name, $Value, [Microsoft.Win32.RegistryValueKind]::String)
	} finally {
		$key.Dispose()
	}
}

function New-StartMenuShortcut {
	param(
		[object]$Shell,
		[string]$Path,
		[string]$Target,
		[string]$WorkingDirectory,
		[string]$Description,
		[string]$IconPath
	)

	$shortcut = $Shell.CreateShortcut($Path)
	$shortcut.TargetPath = $Target
	$shortcut.WorkingDirectory = $WorkingDirectory
	$shortcut.Description = $Description
	$shortcut.IconLocation = "$IconPath,0"
	$shortcut.Save()
}

function Notify-ShellAssociationChanged {
	if (-not ("TrikStudioShellNotify" -as [type])) {
		$typeDefinition = 'using System; using System.Runtime.InteropServices; public static class TrikStudioShellNotify { [DllImport("shell32.dll")] public static extern void SHChangeNotify(uint eventId, uint flags, IntPtr item1, IntPtr item2); }'
		Add-Type -TypeDefinition $typeDefinition
	}

	[TrikStudioShellNotify]::SHChangeNotify(0x08000000, 0x1000, [IntPtr]::Zero, [IntPtr]::Zero)
}

if ($Action -eq "install") {
	$studioExecutable = @("trik-studio.exe", "trik-studio.bin") |
		ForEach-Object { Join-Path $installRoot $_ } |
		Where-Object { Test-Path -LiteralPath $_ -PathType Leaf } |
		Select-Object -First 1
	$playerExecutable = Join-Path $installRoot "2D-model.exe"

	if (-not $studioExecutable) {
		throw "Could not find trik-studio.exe or trik-studio.bin in $installRoot"
	}

	if (-not (Test-Path -LiteralPath $playerExecutable -PathType Leaf)) {
		throw "Could not find 2D-model.exe in $installRoot"
	}

	$studioShortcutTarget = Join-Path $installRoot "trik-studio-safe.cmd"
	if (-not (Test-Path -LiteralPath $studioShortcutTarget -PathType Leaf)) {
		$studioShortcutTarget = $studioExecutable
	}
}

if (-not $PSCmdlet.ShouldProcess($installRoot, "$Action portable TRIK Studio integration")) {
	return
}

$classes = [Microsoft.Win32.Registry]::CurrentUser.CreateSubKey("Software\Classes")
try {
	if ($Action -eq "install") {
		$studioCommand = '"' + $studioExecutable + '" "%1"'
		$playerCommand = '"' + $playerExecutable + '" "%1"'
		$extensionKey = $classes.CreateSubKey(".qrs")
		try {
			$openWith = $extensionKey.CreateSubKey("OpenWithProgids")
			try {
				$openWith.SetValue($studioProgId, "", [Microsoft.Win32.RegistryValueKind]::String)
				$openWith.SetValue($playerProgId, "", [Microsoft.Win32.RegistryValueKind]::String)
			} finally {
				$openWith.Dispose()
			}
		} finally {
			$extensionKey.Dispose()
		}

		Set-RegistryString $classes $studioProgId "" "TRIK Studio Project"
		Set-RegistryString $classes "$studioProgId\DefaultIcon" "" "$studioExecutable,0"
		Set-RegistryString $classes "$studioProgId\shell\open\command" "" $studioCommand
		Set-RegistryString $classes "$studioProgId\shell\edit" "MUIVerb" "Edit with TRIK Studio"
		Set-RegistryString $classes "$studioProgId\shell\edit\command" "" $studioCommand
		Set-RegistryString $classes "$playerProgId" "" "2D-model Player Project"
		Set-RegistryString $classes "$playerProgId\DefaultIcon" "" "$playerExecutable,0"
		Set-RegistryString $classes "$playerProgId\shell\open\command" "" $playerCommand
		Set-RegistryString $classes ".qrs\shell\OpenWithTrikStudio" "MUIVerb" "Open with TRIK Studio"
		Set-RegistryString $classes ".qrs\shell\OpenWithTrikStudio\command" "" $studioCommand
		Set-RegistryString $classes ".qrs\shell\EditWithTrikStudio" "MUIVerb" "Edit with TRIK Studio"
		Set-RegistryString $classes ".qrs\shell\EditWithTrikStudio\command" "" $studioCommand

		New-Item -ItemType Directory -Path $startMenuGroup -Force | Out-Null
		$shell = New-Object -ComObject WScript.Shell
		try {
			New-StartMenuShortcut $shell (Join-Path $startMenuGroup "TRIK Studio.lnk") `
				$studioShortcutTarget $installRoot "Launch TRIK Studio" $studioExecutable
			New-StartMenuShortcut $shell (Join-Path $startMenuGroup "2D-model Player.lnk") `
				$playerExecutable $installRoot "Launch the 2D-model Player" $playerExecutable
		} finally {
			[void][Runtime.InteropServices.Marshal]::FinalReleaseComObject($shell)
		}
		Notify-ShellAssociationChanged
	} else {
		$extensionKey = $classes.OpenSubKey(".qrs", $true)
		if ($extensionKey) {
			try {
				$openWith = $extensionKey.OpenSubKey("OpenWithProgids", $true)
				if ($openWith) {
					try {
						foreach ($progId in @($studioProgId, $playerProgId)) {
							if ($openWith.GetValueNames() -contains $progId) {
								$openWith.DeleteValue($progId, $false)
							}
						}
					} finally {
						$openWith.Dispose()
					}
				}
			} finally {
				$extensionKey.Dispose()
			}
		}

		foreach ($subKey in @(
				"$studioProgId",
				"$playerProgId",
				".qrs\shell\OpenWithTrikStudio",
				".qrs\shell\EditWithTrikStudio")) {
			$classes.DeleteSubKeyTree($subKey, $false)
		}

		foreach ($shortcut in @("TRIK Studio.lnk", "2D-model Player.lnk")) {
			$shortcutPath = Join-Path $startMenuGroup $shortcut
			if (Test-Path -LiteralPath $shortcutPath -PathType Leaf) {
				Remove-Item -LiteralPath $shortcutPath
			}
		}

		if (Test-Path -LiteralPath $startMenuGroup -PathType Container) {
			$remainingItems = Get-ChildItem -LiteralPath $startMenuGroup -Force
			if (-not $remainingItems) {
				Remove-Item -LiteralPath $startMenuGroup
			}
		}
		Notify-ShellAssociationChanged
	}
} finally {
	$classes.Dispose()
}
