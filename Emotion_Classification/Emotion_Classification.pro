#-------------------------------------------------
#
# Project created by QtCreator 2018-11-14T22:46:11
#
#-------------------------------------------------

QT       += core gui
QT       += core gui sql
QT       += serialport
QT       += multimediawidgets
QT       += multimedia
QT       += network
QT       += charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Emotion_Classification
TEMPLATE = app


SOURCES +=\
        widget.cpp \
    login.cpp \
    success_warning.cpp \
    svm.cpp \
    wavelet.cpp \
    iir_i.cpp \
    iir_ii.cpp \
    user_filter.cpp \
    mainwindow.cpp \
    main.cpp \
    result.cpp \
    summary.cpp \
    mulplayer.cpp \
    change_datebase.cpp \
    student_score.cpp \
    teacher_dialog.cpp \
    teacher_score.cpp \
    uart_class.cpp \
    student_setting.cpp \
    topwin.cpp \
    classwin.cpp \
    date_accquire.cpp \
    drive.cpp \
    dr_monitor.cpp \
    dr_result.cpp \
    bar.cpp \
    standby.cpp

HEADERS  += \
    login.h \
    success_warning.h \
    svm.h \
    wavelet.h \
    iir_i.h \
    iir_ii.h \
    user_filter.h \
    filter_co.h \
    change_datebase.h \
    student_score.h \
    teacher_dialog.h \
    teacher_score.h \
    uart_class.h \
    student_setting.h \
    topwin.h \
    classwin.h \
    date_accquire.h \
    dr_monitor.h \
    dr_result.h \
    testwin.h \
    drivewin.h \
    test_start.h \
    test_film.h \
    result.h \
    test_summary.h \
    bar.h \
    standby.h

FORMS    += widget.ui \
    login.ui \
    success_warning.ui \
    mainwindow.ui \
    result.ui \
    summary.ui \
    mulplayer.ui \
    student_score.ui \
    teacher_dialog.ui \
    teacher_score.ui \
    student_setting.ui \
    topwin.ui \
    classwin.ui \
    drive.ui \
    dr_monitor.ui \
    dr_result.ui \
    standby.ui

RESOURCES += \
    resource.qrc \
    res.qrc

static{
QTPLUGIN+=qtvirtualkeyboardplugin
QT+=svg
}

#INCLUDEPATH += /usr/local/qwt-6.1.3/include
#LIBS += -L"/usr/local/qwt-6.1.3/lib/" -lqwt
INCLUDEPATH += /usr/local/qwt-6.1.3-arm/include
LIBS += -L"/usr/local/qwt-6.1.3-arm/lib/" -lqwt

#LIBS += -L/home/syb/Downloads/gstreamer-1.0/lib -lgstreamer-1.0

DISTFILES +=
