function Component()
{
}

Component.prototype.createOperations = function()
{
    component.createOperations();

    if (installer.value("os") === "win") {
        var allUsers = installer.hasAdminRights();

        component.addOperation(
            "Execute",
            "powershell.exe",
            "-NoProfile",
            "-NonInteractive",
            "-ExecutionPolicy",
            "Bypass",
            "-File",
            "@TargetDir@\\install-qrs-association.ps1",
            "@TargetDir@",
            allUsers.toString()
        );
    }
}
