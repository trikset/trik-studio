TEMPLATE = lib

include($$PWD/trikRuntime/global.pri)

DEFINES += TRIKCONTROL_LIBRARY

TRIK_CONTROL_ROOT = $$PWD/trikRuntime/trikControl

HEADERS += \
    $$TRIK_CONTROL_ROOT/include/trikControl/trikControlDeclSpec.h \
    $$TRIK_CONTROL_ROOT/include/trikControl/batteryInterface.h \
    $$TRIK_CONTROL_ROOT/include/trikControl/brickFactory.h \
    $$TRIK_CONTROL_ROOT/include/trikControl/brickInterface.h \
    $$TRIK_CONTROL_ROOT/include/trikControl/cameraDeviceInterface.h \
    $$TRIK_CONTROL_ROOT/include/trikControl/colorSensorInterface.h \
    $$TRIK_CONTROL_ROOT/include/trikControl/deviceInterface.h \
    $$TRIK_CONTROL_ROOT/include/trikControl/displayInterface.h \
    $$TRIK_CONTROL_ROOT/include/trikControl/encoderInterface.h \
    $$TRIK_CONTROL_ROOT/include/trikControl/eventCodeInterface.h \
    $$TRIK_CONTROL_ROOT/include/trikControl/eventDeviceInterface.h \
    $$TRIK_CONTROL_ROOT/include/trikControl/eventInterface.h \
    $$TRIK_CONTROL_ROOT/include/trikControl/fifoInterface.h \
    $$TRIK_CONTROL_ROOT/include/trikControl/gamepadInterface.h \
    $$TRIK_CONTROL_ROOT/include/trikControl/keysInterface.h \
    $$TRIK_CONTROL_ROOT/include/trikControl/ledInterface.h \
    $$TRIK_CONTROL_ROOT/include/trikControl/lineSensorInterface.h \
    $$TRIK_CONTROL_ROOT/include/trikControl/motorInterface.h \
    $$TRIK_CONTROL_ROOT/include/trikControl/objectSensorInterface.h \
    $$TRIK_CONTROL_ROOT/include/trikControl/pwmCaptureInterface.h \
    $$TRIK_CONTROL_ROOT/include/trikControl/sensorInterface.h \
    $$TRIK_CONTROL_ROOT/include/trikControl/soundSensorInterface.h \
    $$TRIK_CONTROL_ROOT/include/trikControl/vectorSensorInterface.h \
    $$TRIK_CONTROL_ROOT/include/trikControl/gyroSensorInterface.h \
    $$TRIK_CONTROL_ROOT/include/trikControl/markerInterface.h \
    $$TRIK_CONTROL_ROOT/include/trikControl/i2cDeviceInterface.h \
    $$TRIK_CONTROL_ROOT/include/trikControl/utilities.h \
    $$TRIK_CONTROL_ROOT/include/trikControl/lidarInterface.h \
    $$TRIK_CONTROL_ROOT/include/trikControl/irCameraInterface.h \
    $$TRIK_CONTROL_ROOT/src/qtCameraImplementation.h \
    $$TRIK_CONTROL_ROOT/src/imitationCameraImplementation.h \

SOURCES += \
    $$TRIK_CONTROL_ROOT/src/utilities.cpp \
    $$TRIK_CONTROL_ROOT/src/brickInterface.cpp \
    $$TRIK_CONTROL_ROOT/src/qtCameraImplementation.cpp \
    $$TRIK_CONTROL_ROOT/src/cameraDeviceInterface.cpp \
    $$TRIK_CONTROL_ROOT/src/imitationCameraImplementation.cpp \

INCLUDEPATH += \
    $$TRIK_CONTROL_ROOT/include/ \
    $$TRIK_CONTROL_ROOT/include/trikControl/ \

QT += multimedia gui

links(trikRuntimeQsLog trikKernel)
implementationIncludes(trikKernel)
