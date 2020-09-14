function Component()
{
}

Component.prototype.createOperations = function()
{
    component.createOperations();

    if (installer.value("os") === "win") {
        component.addOperation("RegisterFileType",
                               "tsj",
                               "C:\\Windows\\System32\\wscript.exe //nologo //b // \"@TargetDir@\\" +
                                    installer.executableName + installer.execExtension + "\"  \"%1\"",
                               "@ProductName@ Project",
                               "application/octet-stream",
                               "@TargetDir@/trik-studio-jr.ico");
    }
}
