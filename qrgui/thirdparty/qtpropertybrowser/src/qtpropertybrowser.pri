# include(../common.pri)
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

CONFIG += warn_off

qtpropertybrowser-uselib:!qtpropertybrowser-buildlib {
	LIBS += -L$$QTPROPERTYBROWSER_LIBDIR -l$$QTPROPERTYBROWSER_LIBNAME
} else {
	SOURCES += $$PWD/qtpropertybrowser.cpp \
			$$PWD/qtpropertymanager.cpp \
			$$PWD/qteditorfactory.cpp \
			$$PWD/qtvariantproperty.cpp \
			$$PWD/qttreepropertybrowser.cpp \
			$$PWD/qtbuttonpropertybrowser.cpp \
			$$PWD/qtgroupboxpropertybrowser.cpp \
			$$PWD/qtpropertybrowserutils.cpp
	HEADERS += $$PWD/qtpropertybrowser.h \
			$$PWD/qtpropertymanager.h \
			$$PWD/qteditorfactory.h \
			$$PWD/qtvariantproperty.h \
			$$PWD/qttreepropertybrowser.h \
			$$PWD/qtbuttonpropertybrowser.h \
			$$PWD/qtgroupboxpropertybrowser.h \
			$$PWD/qtpropertybrowserutils_p.h
	RESOURCES += $$PWD/qtpropertybrowser.qrc
}

win32 {
	contains(TEMPLATE, lib):contains(CONFIG, shared):DEFINES += QT_QTPROPERTYBROWSER_EXPORT
	else:qtpropertybrowser-uselib:DEFINES += QT_QTPROPERTYBROWSER_IMPORT
}
