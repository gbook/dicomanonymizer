QT += core
QT -= gui

CONFIG += c++11

TARGET = DicomAnonymizer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

HEADERS += \
    main.h

INCLUDEPATH += $$PWD/gdcm/Source/Attribute
INCLUDEPATH += $$PWD/gdcm/Source/Common
INCLUDEPATH += $$PWD/gdcm/Source/DataDictionary
INCLUDEPATH += $$PWD/gdcm/Source/DataStructureAndEncodingDefinition
INCLUDEPATH += $$PWD/gdcm/Source/InformationObjectDefinition
INCLUDEPATH += $$PWD/gdcm/Source/MediaStorageAndFileFormat
INCLUDEPATH += $$PWD/gdcm/Source/MessageExchangeDefinition
INCLUDEPATH += $$PWD/gdcmbin/Source/Common # for gdcmConfigure.h

linux-g++: {
    LIBS += -L$$PWD/gdcmbin/bin
}
else {
    win32:CONFIG(release, debug|release): LIBS += -L$$PWD/gdcmbin/bin/Release/
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/gdcmbin/bin/Debug/
}

LIBS += \
    -lgdcmMSFF \
    -lgdcmCommon \
    -lgdcmDICT \
    -lgdcmDSED \
    -lgdcmIOD \
    -lgdcmMEXD \
    -lgdcmcharls \
    -lgdcmexpat \
    -lgdcmjpeg12 \
    -lgdcmjpeg16 \
    -lgdcmjpeg8 \
    -lgdcmopenjpeg \
    -lgdcmzlib
    -lsocketxx
