ARCHITECTURE=Darwin
USEFAKEDEVICES="X1"

LIBS += -L/Users/keaveney/assembly_dev/cmstkmodlab/devices/lib -lTkModLabLang -lTkModLabConrad -lTkModLabArduino
LIBS += -L/Users/keaveney/assembly_dev/cmstkmodlab/common -lCommon

equals(USEFAKEDEVICES,"X0") {
LIBS += -lueye_api
}

macx {
  CONFIG+=x86_64
  QMAKE_CXXFLAGS += -stdlib=libc++
  #QMAKE_MAC_SDK = macosx10.11
  QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.11
  #LIBS += -framework AppKit
  #LIBS += -framework QuartzCore
  #LIBS += -framework QTKit
  #LIBS += -framework Cocoa
}

CONFIG += link_pkgconfig
PKGCONFIG += opencv

QMAKE = qmake

QMAKE_CXXFLAGS += -std=c++11

macx {
  QMAKE_CXXFLAGS += -DAPPLICATIONVERSIONSTR=\\\"unknown\\\"
}
else {
  QMAKE_CXXFLAGS += -DAPPLICATIONVERSIONSTR=\\\"`git describe --dirty --always --tags`\\\"
}

DEFINES += USE_FAKEIO NO_TWITTER

QT += core gui xml network script svg
greaterThan(QT_MAJOR_VERSION, 4) {
  QT += widgets
} 

TARGET = AssemblyCommon
TEMPLATE = lib

macx {
  QMAKE_POST_LINK = install_name_tool -change libCommon.1.dylib /Users/keaveney/assembly_dev/cmstkmodlab/common/libCommon.1.dylib $(TARGET)
}

DEPENDPATH += /Users/keaveney/assembly_dev/cmstkmodlab/common
INCLUDEPATH += .
INCLUDEPATH += ..
INCLUDEPATH += /Users/keaveney/assembly_dev/cmstkmodlab
INCLUDEPATH += /Users/keaveney/assembly_dev/cmstkmodlab/common

greaterThan(QT_MAJOR_VERSION, 4) {
  cache()
}

# Input
HEADERS += AssemblyVUEyeCamera.h \
           AssemblyVUEyeModel.h \
           AssemblyUEyeCameraThread.h \
           AssemblyUEyeWidget.h \
           AssemblyUEyeCameraWidget.h \
           AssemblyUEyeView.h \
           AssemblyUEyeSnapShooter.h \
           AssemblyModuleAssembler.h \
           AssemblyPlasmaCleaner.h \
           AssemblyMarkerFinderThread.h \
           AssemblyVMarkerFinder.h \
           AssemblySensorMarkerFinder.h \
           AssemblySensorMarkerFinderWidget.h \
           LStepExpressModel.h \
           LStepExpressSettings.h \
           LStepExpressMotion.h \
           LStepExpressMotionManager.h \
           LStepExpressMotionThread.h \
           LStepExpressWidget.h \
           LStepExpressJoystickWidget.h \
           LStepExpressSettingsWidget.h

equals(USEFAKEDEVICES,"X0") {
HEADERS += AssemblyUEyeCamera.h \
           AssemblyUEyeModel.h
} else {
HEADERS += AssemblyUEyeFakeCamera.h \
           AssemblyUEyeFakeModel.h
}

SOURCES += AssemblyVUEyeCamera.cc \
           AssemblyVUEyeModel.cc \
           AssemblyUEyeCameraThread.cc \
           AssemblyUEyeWidget.cc \
           AssemblyUEyeCameraWidget.cc \
           AssemblyUEyeView.cc \
           AssemblyUEyeSnapShooter.cc \
           AssemblyModuleAssembler.cc \
           AssemblyPlasmaCleaner.cc \
           AssemblyMarkerFinderThread.cc \
           AssemblyVMarkerFinder.cc \
           AssemblySensorMarkerFinder.cc \
           AssemblySensorMarkerFinderWidget.cc \
           LStepExpressModel.cc \
           LStepExpressSettings.cc \
           LStepExpressMotion.cc \
           LStepExpressMotionManager.cc \
           LStepExpressMotionThread.cc \
           LStepExpressWidget.cc \
           LStepExpressJoystickWidget.cc \
           LStepExpressSettingsWidget.cc

equals(USEFAKEDEVICES,"X0") {
SOURCES += AssemblyUEyeCamera.cc \
           AssemblyUEyeModel.cc
} else {
SOURCES += AssemblyUEyeFakeCamera.cc \
           AssemblyUEyeFakeModel.cc
}
