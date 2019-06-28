function Controller() {
}

Controller.prototype.IntroductionPageCallback = function() {
  if (!installer.isInstaller()) {
	gui.currentPageWidget().findChild("PackageManagerRadioButton").visible = false;
	gui.currentPageWidget().findChild("UpdaterRadioButton").visible = false;
  }
}
