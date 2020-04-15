function Component()
{
}

Component.prototype.createOperations = function()
{
    component.createOperations();

    if (installer.value("os") === "win") {
        component.addOperation("RegisterFileType",
                               "qrs",
                               // Possible solution is:
                               // C:\Windows\System32\wscript.exe "@TargetDir@\\" +
                               // installer.executableName + ".vbs \"%1\""
                               "@TargetDir@\\" + installer.executableName + installer.execExtension + " \"%1\"",
                               "@ProductName@ Project",
                               "application/octet-stream");
    }
}
