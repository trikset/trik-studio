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
            "cmd.exe",
            "/c",
            "@TargetDir@\\install-qrs-association.cmd",
            "@TargetDir@",
            allUsers.toString(),
            "true"
        );
    }
}