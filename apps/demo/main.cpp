
#include <QApplication>
#include "mainwindow.h"
#include "logger.h"

int main(int argc, char *argv[]) {
    int logType = wl::Logger::LogTarget::eLogFile;

#if defined(_WINDOWS)
    logType |= wl::Logger::LogTarget::eLogSys;
    logType |= wl::Logger::LogTarget::eLogMSVC;
#else
    logType |= SRSLogger::eLogSys;
#endif
    wl::Logger::instance().init("occt", static_cast<wl::Logger::LogTarget>(logType), wl::Logger::LogLevel::eLogInfo, "occt");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}