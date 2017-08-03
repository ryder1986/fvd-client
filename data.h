#ifndef DATA_H
#define DATA_H

#include <QObject>

#pragma pack(push)
#pragma pack(1)

#define  VERSION    0x01
#define  PROTTYPE    0x02


#define  SETCAMPARAM    0x0001
#define  GETCAMPARAM    0x0002
#define  REPCAMPARAM    0x0003

#define  SETDETECTDEVICE    0x0004
#define  GETDETECTDEVICE    0x0005
#define  REPDETECTDEVICE    0x0006

#define  SETCHECHPARAM    0x0007
#define  GETCHECHPARAM    0x0008
#define  REPCHECHPARAM    0x0009

#define  HEART    0x1000
#define  SHUTDOWN    0x1001
#define  REPHEART    0x1002

#define  REBOOTZEN   0x2001

#define  FORKEXIT    0x3001

#define   HEARTTIME     60

#define  USERNAMEMAX   20
#define  IPADDRMAX     16
#define  DEVNAMEMAX    50


#define Z_NONE 0x0
#define Z_NORTH 0x1
#define Z_NORTHEAST 0x2
#define Z_EAST 0x3
#define Z_SOUTHEAST 0x4
#define Z_SOUTH 0x5
#define Z_SOUTHWEST 0x6
#define Z_WEST 0x7
#define Z_NORTHWEST 0x8

#define  COILPOINTMAX       4
#define  DETECTLANENUMMAX   4
#define  LANELINEMAX         8
#define  STANDPOINT          8
#define  STANDARDVAULEMAX    4
#define  ALGMAX               2
#define  MAXSUBSYSTEM         4
#define CAM_NUM_MAX 8
//#define  CAMMERNUM           4

//typedef struct Command {
//    quint8 version;
//    quint8 prottype;
//    quint16 objnumber;
//    quint16 objtype;
//    quint32 objlen;
//} mCommand;

typedef struct {
    quint16 x;
    quint16 y;
} FvdPoint;

typedef struct {
    quint8 state;
    quint8 isCarInTail;
    quint16 queueLength;
    quint32 vehnum;
    //quint32    speed;
    quint16 uActualDetectLength;
    quint16 uActualTailLength;
    FvdPoint LineUp[2];
} FvdRealLaneInfo;

typedef struct {
    quint8 flag;
    quint8 laneNum;
    quint8 curstatus;
    quint8 fuzzyflag;
    quint8 visibility;
    quint16 uDegreePoint[20][2];
    //quint16 	uDegreePoint[4][2];
    FvdRealLaneInfo lane[DETECTLANENUMMAX];  //16
} FvdRealStaticInfo;

typedef struct  {
    quint32 deviceID;
    quint32 detectport;
    quint32 camnum;
    QString detectip;
    QString detectname;
} FvdDetectDeviceConfig;
typedef struct {
    bool camera_enabled;
    quint8 direction;
    quint32 camID;
    quint32 cammerport;
    quint32 adjustport;
    quint32 signalport;
    quint8 urlname[USERNAMEMAX];
    quint8 username[USERNAMEMAX];
    quint8 passwd[USERNAMEMAX];
    quint8 cammerIp[IPADDRMAX];
    quint8 adjustIp[IPADDRMAX];
    quint8 signalIp[IPADDRMAX];
} FvdCamAttributes;
typedef struct {
    quint16 cam2stop;
    quint16 camheight;
    quint16 lannum;
    quint16 number;
    quint16 baselinelen;
    quint16 farth2stop;
    quint16 recent2stop;
} FvdCamDemarcateParam;
typedef struct {
    quint16 number;
    quint16 farthCoillen;
    quint16 recentCoillen;
} FvdChannelVirtualcoil;
typedef struct   {
    quint8 coilnum;
    FvdCamAttributes camattr;
    FvdCamDemarcateParam camdem;
    FvdChannelVirtualcoil channelcoil[DETECTLANENUMMAX];
} FvdCamParam;
typedef struct {
    quint16 startx;
    quint16 starty;
    quint16 endx;
    quint16 endy;
} FvdLine;
typedef struct   {
    FvdPoint Rear[COILPOINTMAX];
    FvdPoint Front[COILPOINTMAX];
} FvdChannelCoil;

typedef struct
{
    quint8 lanenum;
    FvdChannelCoil virtuallane[DETECTLANENUMMAX];
} FvdCamDetectLane;

typedef struct   {
    quint8 lanelinenum;         //
    FvdLine laneline[LANELINEMAX];
} FvdVirtualLaneLine;

typedef struct   {
    FvdPoint coordinate;
    quint16 value;
} FvdStandardPoint;

typedef struct   {
    FvdPoint vircoordinate[STANDPOINT];
    FvdPoint realcoordinate[STANDPOINT];
} FvdDemDetectArea;

typedef struct   {
    quint16 uTransFactor;
    quint32 uGraySubThreshold;
    quint32 uSpeedCounterChangedThreshold;
    quint32 uSpeedCounterChangedThreshold1;
    quint32 uSpeedCounterChangedThreshold2;
    quint16 uDayNightJudgeMinContiuFrame;
    quint16 uComprehensiveSens;
    quint16 uDetectSens1;
    quint16 uDetectSens2;
    quint16 uStatisticsSens1;
    quint16 uStatisticsSens2;
    quint16 uSobelThreshold;
    quint16 shutterMax;        // 1 2 3 4 5 6 7 8
    quint16 shutterMin;        // 1 2 3 4 5 6 7 8
} FvdDetectParam;

typedef struct   {
    quint32 timep[4];
    FvdCamDetectLane detectlane;
    FvdVirtualLaneLine laneline;
    FvdStandardPoint standpoint[STANDARDVAULEMAX];
    FvdDemDetectArea area;
    FvdDetectParam detectparam[ALGMAX];
} FvdCamDetectParam;

typedef struct common_data{
    QList <FvdCamParam> cam_param;
    QList <FvdCamDetectParam> det_param;
    FvdDetectDeviceConfig dev_cfg;
}FvdComonData;
#include <QtCore>
#include <QDir>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
class Data : public QObject
{
    Q_OBJECT
public:

    static Data &get_instance()
    {
        static Data dat;
        return dat;
    }
    void ba_2_d(QByteArray &b,FvdComonData &d){
        QJsonDocument json_src=QJsonDocument::fromJson(b);




        QJsonObject obj_dev_info=json_src.object()["dev_info"].toObject();
     //   QString ip=obj_dev_info["detectip"].toString();
        int camera_total_number= d.dev_cfg.camnum=obj_dev_info["camnum"].toInt();
        d.dev_cfg.detectip=obj_dev_info["detectip"].toString();
        d.dev_cfg.detectname=obj_dev_info["detectname"].toString();
        d.dev_cfg.detectport=obj_dev_info["detectport"].toInt();
        d.dev_cfg.deviceID=obj_dev_info["deviceID"].toInt();



   //     QJsonObject obj_cam_param=json_src.object()["cam_param"].toObject();
//        QJsonArray array_cam_param=json_src.object()["cam_param"].toArray();
//        for(int i=0;i<road_total_number;i++){
//           FvdCamParam cam_param;

//           for(int j=0;j<camera_total_number;j++)
//            {
//               cam_param.camattr.camera_enabled=array_cam_param["camattr"].toObject()["camera_enabled"].toInt();
//            }
//           d.cam_param.append(cam_param);
//        }
      }

    void init()
    {
        QDir *dir=new QDir(QString("cfg_dir"));
        QString path=  dir->absoluteFilePath(QString("nonglinlu.json"));
        QStringList list=dir->entryList();

        foreach (QString a, list) {
              QString b=a;
               if(a.remove(0,a.length()-4)=="json")
               {
                  road_total_number++;
                  QFile f(QString(dir->absoluteFilePath(b)));
                  //  QFile f(QString().append(QString("cfg_dir")).append(b));
                  f.open(QIODevice::ReadOnly);
                      QByteArray json_data;
                      FvdComonData data;
                      json_data=f.readAll();
                      ba_2_d(json_data,data);
                      d.append(data);
                      qDebug()<<b;
               }

        }
  //      qDebug()<<"reading msg";
        qDebug()<<path;
    }

signals:

public slots:
private:
    explicit Data(QObject *parent = 0);
    QList <FvdComonData> d;
    int road_total_number;
};

#endif // DATA_H
