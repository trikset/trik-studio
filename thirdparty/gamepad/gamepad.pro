TARGET = gamepad

include (../../global.pri)

TEMPLATE = app

CONFIG -= debug_and_release_target build_all debug_and_release
CONFIG+=object_parallel_to_source

include (gamepad/trikDesktopGamepad.pri)
