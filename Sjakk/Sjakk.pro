QT       += core gui network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    commandhistory.cpp \
    configsettings.cpp \
    dialogs/aboutdialog.cpp \
    dialogs/advancedconnectdialog.cpp \
    dialogs/connectdialog.cpp \
    dialogs/fulllicensedialog.cpp \
    dialogs/modifyconnectiondialog.cpp \
    dialogs/preferencesdialog.cpp \
    dialogs/seekdialog.cpp \
    fics/ficsbannerinfo.cpp \
    fics/ficsgameinfo.cpp \
    fics/ficsgametablemodel.cpp \
    fics/ficsparser.cpp \
    fics/ficsseeker.cpp \
    fics/ficsseekertablemodel.cpp \
    fics/ficsstyle12.cpp \
    game/chessboard.cpp \
    game/chessclock.cpp \
    game/chesssquare.cpp \
    game/gameboard.cpp \
    game/gameflags.cpp \
    game/gamemanager.cpp \
    historylineedit.cpp \
    infomanager.cpp \
    main.cpp \
    sjakkwindow.cpp \
    soundmanager.cpp \
    timeseal/timeseal.cpp

HEADERS += \
    commandhistory.h \
    config.h \
    configsettings.h \
    dialogs/aboutdialog.h \
    dialogs/advancedconnectdialog.h \
    dialogs/connectdialog.h \
    dialogs/fulllicensedialog.h \
    dialogs/modifyconnectiondialog.h \
    dialogs/preferencesdialog.h \
    dialogs/seekdialog.h \
    fics/ficsbannerinfo.h \
    fics/ficsgameinfo.h \
    fics/ficsgametablemodel.h \
    fics/ficsparser.h \
    fics/ficsseeker.h \
    fics/ficsseekertablemodel.h \
    fics/ficsstyle12.h \
    game/chessboard.h \
    game/chessclock.h \
    game/chesssquare.h \
    game/gameboard.h \
    game/gameflags.h \
    game/gamemanager.h \
    historylineedit.h \
    infomanager.h \
    sjakkwindow.h \
    soundmanager.h \ \
    timeseal/timeseal.h


FORMS += \
    dialogs/aboutdialog.ui \
    dialogs/advancedconnectdialog.ui \
    dialogs/connectdialog.ui \
    dialogs/fulllicensedialog.ui \
    dialogs/modifyconnectiondialog.ui \
    dialogs/preferencesdialog.ui \
    dialogs/seekdialog.ui \
    game/gameboard.ui \
    sjakkwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .astylerc \
    COPYING \
    installer/build-installer-windows.bat \
    installer/nsis-helper.nsh \
    installer/sjakk-nsis.ini \
    installer/windows-installer.nsi \
    reference/gameinfo-spec.txt \
    reference/games-listing-spec.txt \
    reference/notes.txt \
    reference/sample-input-gamelisting.txt \
    reference/seekinfo-spec.txt \
    reference/style12-spec.txt \
    tools/Create-NsisFilesInstallSection.ps1 \
    tools/Create-NsisPackage.ps1 \
    tools/Get-FolderSize.ps1 \
    tools/Create-VersionHeader.ps1 \
    tools/Ini-Files.ps1 \
    tools/Prep-Package.bat

RESOURCES += \
    media.qrc
