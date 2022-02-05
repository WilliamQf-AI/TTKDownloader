# ***************************************************************************
# * This file is part of the TTK Downloader project
# * Copyright (C) 2015 - 2022 Greedysky Studio
#
# * This program is free software; you can redistribute it and/or modify
# * it under the terms of the GNU General Public License as published by
# * the Free Software Foundation; either version 3 of the License, or
# * (at your option) any later version.
#
# * This program is distributed in the hope that it will be useful,
# * but WITHOUT ANY WARRANTY; without even the implied warranty of
# * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# * GNU General Public License for more details.
#
# * You should have received a copy of the GNU General Public License along
# * with this program; If not, see <http://www.gnu.org/licenses/>.
# ***************************************************************************

QT += core gui network
greaterThan(QT_MAJOR_VERSION, 4):QT += widgets

include($$PWD/../../TTKVersion.pri)

DESTDIR = $$OUT_PWD/../../bin
TARGET = TTKDownloader

TEMPLATE = app
DEFINES += TTK_LIBRARY

win32:msvc{
    CONFIG += c++11
}else{
    equals(QT_MAJOR_VERSION, 6){ #Qt6
        QMAKE_CXXFLAGS += -std=c++17
    }else{
        QMAKE_CXXFLAGS += -std=c++11
    }
}

INCLUDEPATH += \
    $$PWD/../ \
    $$PWD/../TTKInit \
    $$PWD/../../TTKCommon \
    $$PWD/../../TTKThirdParty \
    $$PWD/../../TTKThirdParty/TTKDumper \
    $$PWD/../../TTKModule/TTKCore/downloadCoreKits

HEADERS += \
    $$PWD/../TTKInit/downloadinitobject.h \
    $$PWD/ttkrunobject.h \
    $$PWD/ttklocalpeer.h \
    $$PWD/ttkrunapplication.h

SOURCES += \
    $$PWD/../TTKInit/downloadinitobject.cpp \
    $$PWD/ttkrunmain.cpp \
    $$PWD/ttklocalpeer.cpp \
    $$PWD/ttkrunapplication.cpp \
    $$PWD/ttkrunobject.cpp

RESOURCES += $$PWD/../../TTKUi/DownloaderApp.qrc

win32:RC_FILE = $$PWD/TTKApp.rc
