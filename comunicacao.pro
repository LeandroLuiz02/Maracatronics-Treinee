QT -= gui
QT += network

TEMPLATE = app
DESTDIR = ../bin
TARGET = Comunicacao
VERSION = 1.0.0

CONFIG += c++11 console
CONFIG -= app_bundle

LIBS *= -lprotobuf

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

system(cd protobufs/proto && protoc --cpp_out=../ *.proto && cd ../..)

SOURCES += \
        actions/actions.cpp \
        actuator/actuator.cpp \
        main.cpp \
        protobufs/grSim_Commands.pb.cc \
        protobufs/grSim_Packet.pb.cc \
        protobufs/grSim_Replacement.pb.cc \
        protobufs/ssl_gc_common.pb.cc \
        protobufs/ssl_gc_geometry.pb.cc \
        protobufs/ssl_vision_detection.pb.cc \
        protobufs/ssl_vision_detection_tracked.pb.cc \
        protobufs/ssl_vision_geometry.pb.cc \
        protobufs/ssl_vision_wrapper.pb.cc \
        protobufs/ssl_vision_wrapper_tracked.pb.cc \
        vision/vision.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    actions/actions.h \
    actuator/actuator.h \
    protobufs/grSim_Commands.pb.h \
    protobufs/grSim_Packet.pb.h \
    protobufs/grSim_Replacement.pb.h \
    protobufs/ssl_gc_common.pb.h \
    protobufs/ssl_gc_geometry.pb.h \
    protobufs/ssl_vision_detection.pb.h \
    protobufs/ssl_vision_detection_tracked.pb.h \
    protobufs/ssl_vision_geometry.pb.h \
    protobufs/ssl_vision_wrapper.pb.h \
    protobufs/ssl_vision_wrapper_tracked.pb.h \
    vision/vision.h
