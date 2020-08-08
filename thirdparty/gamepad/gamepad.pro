TARGET = gamepad
TEMPLATE = app
CONFIG -= app_bundle
include (../../global.pri)

include (gamepad/trikDesktopGamepad.pri)
LIBS -= -lqslog
