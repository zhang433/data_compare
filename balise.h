#ifndef BALISE_H
#define BALISE_H
#include <QtGlobal>

struct BaliseHead
{
    quint8 q_updown:    1;//信息传送的方向 (0=车对地，1=地对车)
    quint8 m_version:   7;//语言/代码版本编号 (0010000=V1.0)
    quint8 m_media:     1;//信息传输媒介 (0=应答器，1=环线)
    quint8 n_pig:       3;//本应答器在应答器组中的位置 (000=1,111=8)
    quint8 n_total:     3;//应答器组中所包含的应答器数量 (000=1,111=8)
    quint8 m_dup:       2;//本应答器信息与前/后应答器信息的关系(00不同，01与后一个相同，10与前一个相同) 
    quint8 m_mcount:    8;//报文计数器(0～255)
    quint8 nid_c_reg:   7;//地区编号，高7位=大区编号
    quint8 nid_c_part:  3;//地区编号，低3位=分区编号
    quint8 nid_bg_sta:  6;//应答器标识号，高6位=车站编号
    quint8 nid_bg_bal:  8;//应答器标识号，低8位=应答器编号)
    quint8 q_link:      1;//应答器组的链接关系 (0=不被链接，1=被链接)
    quint8 nid_packet:  8;//信息包标识码
    quint8 q_dir:       2;//验证方向 (00=反向有效，01=正向有效，10=双向有效，11=备用)
};

struct ETCS5Head{
    quint16 l_packet:   13;
    quint8 q_scale:     2;
    quint16 d_link:     15;
    quint8 q_newcountry:1;
    quint16 nid_c:      10;
    quint16 nid_bg:     14;
    quint8 q_linkort:   1;
    quint8 q_linkreact: 2;
    quint8 q_locaac:    6;
    quint8 n_iter:      5;
    quint16 d_link1:    15;
    quint8 q_newcountry1:1;
    quint16 nid_c1:      10;
    quint16 nid_bg1:     14;
    quint8 q_linkort1:   1;
    quint8 q_linkreact1: 2;
    quint8 q_locaac1:    6;


};

#endif // BALISE_H
