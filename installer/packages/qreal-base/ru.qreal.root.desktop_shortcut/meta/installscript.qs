function Component()
{
}

Component.prototype.createOperations = function()
{
    component.createOperations();
    if (installer.value("os") === "win") {
        component.addOperation("CreateShortcut", "C:\\Windows\\System32\\wscript.exe //nologo //e:vbscript //b // \"@TargetDir@\\" +
                                    installer.executableName + installer.execExtension +"\""
            , "@DesktopDir@\\@ProductName@ @Version@" + installer.linkExtension, "iconPath=@TargetDir@\\trik-studio.ico");
    }
}
