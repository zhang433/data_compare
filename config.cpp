#include "config.h"
#include <QSettings>

Config::Config()
{
    ConfigFile = "config.ini";
    CurrentIndex = 0;
    IntervalMS = 300;
    TcpServerIP = "127.0.0.1";
    TcpServerPort = 6000;
}

void Config::readConfig()
{
    QSettings setting(this->ConfigFile, QSettings::IniFormat);
    this->IntervalMS = setting.value("IntervalMS").toInt();
    this->TcpServerIP = setting.value("TcpServerIP").toString();
    this->TcpServerPort = setting.value("TcpServerPort").toInt();
}

void Config::writeConfig()
{
    QSettings setting(this->ConfigFile, QSettings::IniFormat);
    setting.setValue("IntervalMS",this->IntervalMS);
    setting.setValue("TcpServerIP",this->TcpServerIP);
    setting.setValue("TcpServerPort",this->TcpServerPort);
}
