TEMPLATE = lib
CONFIG += plugin c++11
DESTDIR = ../../bin/plugins/tools/
MOC_DIR = .moc
RCC_DIR = .moc

INCLUDEPATH += \
	$$PWD/../.. \
	$$PWD/../../qrgui/ \

QT += widgets

HEADERS = \
	generationRulesPlugin.h \

SOURCES = \
	generationRulesPlugin.cpp \
