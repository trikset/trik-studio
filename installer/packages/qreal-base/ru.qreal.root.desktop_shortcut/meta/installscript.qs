function Component()
{
}

Component.prototype.createOperations = function()
{
    component.createOperations();
    if (installer.value("os") === "win") {
        var wscript = installer.environmentVariable("windir")+"\\system32\\wscript.exe"
        component.addOperation("CreateShortcut", wscript, "@DesktopDir@\\@ProductName@ @Version@" + installer.linkExtension,
            "//nologo //e:vbscript //b // \"@TargetDir@\\" + installer.executableName + installer.execExtension +"\"",
            "iconPath=@TargetDir@\\trik-studio.ico");
    }
}
