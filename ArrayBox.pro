#-------------------------------------------------
#
# Project created by QtCreator 2018-12-03T11:21:08
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ArrayBox
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
#QMAKE_CXXFLAGS += -Wweak-vtables

SOURCES += \
    main.cpp \
    arraydatabasemodel.cpp \
    sortfilterproxymodel.cpp \
    detailrelationaldelegate.cpp \
    abmainwindow.cpp \
    swarm/swarmtools.cpp \
    swarm/swarmimpl.cpp \
    swarm/qtwebrequestimpl.cpp \
    swarm/webrequestadapter.cpp \
    swarm/swarmreply.cpp

HEADERS += \
    abmainwindow.h \
    arraydatabasemodel.h \
    sortfilterproxymodel.h \
    detailrelationaldelegate.h \
    swarm/swarmtools.h \
    swarm/iswarmtools.h \
    swarm/iswarm.h \
    swarm/swarmimpl.h \
    swarm/webrequestadapter.h \
    swarm/iwebrequestadapter.h \
    swarm/qtwebrequestimpl.h \
    swarm/iswarmreply.h \
    swarm/swarmreply.h \
    ioipsmodel.h

FORMS += \
        abmainwindow.ui \
    swarmfinddialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
