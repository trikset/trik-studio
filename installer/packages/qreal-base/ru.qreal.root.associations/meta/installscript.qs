function Component()
{
}

Component.prototype.createOperations = function()
{
    component.createOperations();

    if (installer.value("os") === "win") {
        component.addOperation("RegisterFileType",
                               "qrs",
                               "C:\\Windows\\System32\\wscript.exe //nologo //b // \"@TargetDir@\\" +
                                    installer.executableName + ".vbs\" \"%1\"",
                               "@ProductName@ Project",
                               "application/octet-stream",
                               "iconPath=@TargetDir@/trik-studio.ico");
    }
}
