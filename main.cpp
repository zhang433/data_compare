#include "mainwidget.h"
#include <QApplication>
#include "config.h"
#include <QDebug>
#include <stdio.h>
#include <stdlib.h>
//#include "log.h"
#include <QFile>
#include <QDateTime>
#include <QMutex>
#include <QDir>
#include "enventcontrol.h"

void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QMutex mutex;
    mutex.lock();

    QString text;
    switch(type)
    {
    case QtDebugMsg:
       text = QString("Debug:");
       break;

    case QtWarningMsg:
       text = QString("Warning:");
       break;

    case QtCriticalMsg:
       text = QString("Critical:");
       break;

    case QtFatalMsg:
       text = QString("Fatal:");
    }

    QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
    QString current_date = QString("(%1)").arg(current_date_time);
    QString message = QString("%1 %2 %3 %4").arg(text).arg(context_info).arg(msg).arg(current_date);

    static QString filename = "";
    if(filename == "")
    {
        filename = QString("%1.log").arg(QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));
    }
    QFile file(filename);
    if(file.size()>LOG_SIZE_MAX) //大于100M，另存一个文件
    {
        filename = "";
    }
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);
    text_stream << message << "\r\n";
    file.flush();
    file.close();

    mutex.unlock();
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(outputMessage); //注册MessageHandler
    QApplication a(argc, argv);
    //配置文件加载和读取
    QString runPath = QCoreApplication::applicationDirPath();
//    Config congfigInfo;
//    //congfigInfo.ConfigFile = runPath+"/"+congfigInfo.ConfigFile;
//    congfigInfo.ConfigFile = congfigInfo.ConfigFile;
//    congfigInfo.readConfig();
//    qDebug()<<congfigInfo.TcpServerIP<<congfigInfo.TcpServerPort<<congfigInfo.IntervalMS;
//    //控制管理收包和处理包
//    qDebug()<<"From main thread: "<<QThread::currentThreadId();
//    EnventControl eventcontrol;
//    eventcontrol.start(congfigInfo.TcpServerIP, congfigInfo.TcpServerPort, congfigInfo.IntervalMS);

    MainWidget w;
    w.show();

    return a.exec();
}
