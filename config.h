#ifndef CONFIG_H
#define CONFIG_H
#include <QString>

#define LOG_SIZE_MAX     (1024*1024*10)

class Config
{
public:
    Config();

    int CurrentIndex;                //tab页面索引

    QString ConfigFile;              //配置文件路径
    //TCP客户端配置参数
    int IntervalMS;                  //发送心跳时间间隔
    QString TcpServerIP;             //服务器端IP地址
    quint16 TcpServerPort;               //服务器端口号

    //读写配置参数
    void readConfig();               //读取配置参数
    void writeConfig();              //写入配置参数
};

#endif // CONFIG_H
