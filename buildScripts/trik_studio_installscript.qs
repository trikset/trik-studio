function Controller() {
}

Controller.prototype.IntroductionPageCallback = function() {
  gui.clickButton(buttons.NextButton);
}

Controller.prototype.DynamicTargetWidgetCallback = function() {
  gui.clickButton(buttons.NextButton);
}

Controller.prototype.StartMenuDirectoryPageCallback = function() {
  gui.clickButton(buttons.NextButton);
}

Controller.prototype.ComponentSelectionPageCallback = function() {
  var widget = gui.currentPageWidget();
  
//  widget.deselectAll();
  
//  widget.selectComponent("ru.qreal.root.trik");
//    widget.selectComponent("ru.qreal.root.trik.core");
//      widget.selectComponent("ru.qreal.root.trik.core.v6");
//      widget.selectComponent("ru.qreal.root.trik.core.v62");
//    widget.selectComponent("ru.qreal.root.trik.examples");
//    widget.selectComponent("ru.qreal.root.trik.f_sharp");
//      widget.selectComponent("ru.qreal.root.trik.f_sharp.v6");
//      widget.selectComponent("ru.qreal.root.trik.f_sharp.v62");
//    widget.selectComponent("ru.qreal.root.trik.pascal");
//    widget.selectComponent("ru.qreal.root.trik.python");
//    widget.selectComponent("ru.qreal.root.trik.gamepad");
    

//  widget.selectComponent("ru.qreal.root.nxt");
//    widget.selectComponent("ru.qreal.root.nxt.core");
//    widget.selectComponent("ru.qreal.root.nxt.examples");
//    widget.selectComponent("ru.qreal.root.nxt.tools");

//  widget.selectComponent("ru.qreal.root.ev3");
//    widget.selectComponent("ru.qreal.root.ev3.examples");
    
//  widget.selectComponent("ru.qreal.root.pioneer");
//    widget.selectComponent("ru.qreal.root.pioneer.examples");
    
//  widget.selectComponent("ru.qreal.root.languages");
//   widget.selectComponent("ru.qreal.root.languages.russian");
//    widget.selectComponent("ru.qreal.root.languages.french");
//  widget.selectComponent("ru.qreal.root.desktop_shortcut");
//  widget.selectComponent("ru.qreal.root.associations");

  gui.clickButton(buttons.NextButton);
}

Controller.prototype.LicenseAgreementPageCallback = function() {
  gui.currentPageWidget().AcceptLicenseRadioButton.setChecked(true);
  gui.clickButton(buttons.NextButton);  
}

Controller.prototype.ReadyForInstallationPageCallback = function() {
  gui.clickButton(buttons.CommitButton);
}

Controller.prototype.FinishedPageCallback = function() {
  gui.currentPageWidget().RunItCheckBox.setChecked(false);
  gui.clickButton(buttons.FinishButton);
}
