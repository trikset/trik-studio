function Component()
{
}

Component.prototype.createOperations = function()
{
    component.createOperations();

    if (installer.value("os") === "win") {
        component.addOperation("RegisterFileType",
                               "tsj",
                               "@TargetDir@\\" + installer.executableName + installer.execExtension + " \"%1\"",
                               "@ProductName@ Project",
                               "application/octet-stream");
    }
}
