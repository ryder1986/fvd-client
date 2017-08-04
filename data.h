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
#define TIME_CHECKPOINT 4
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
    quint32 direction;
    quint32 camID;
    quint32 cammerport;
    quint32 adjustport;
    quint32 signalport;
    QString urlname;
    QString username;
    QString passwd;
    QString cammerIp;
    QString adjustIp;
    QString signalIp;
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
    quint32 timep[TIME_CHECKPOINT];
    FvdCamDetectLane detectlane;
    FvdVirtualLaneLine laneline;
    FvdStandardPoint standpoint[STANDARDVAULEMAX];
    FvdDemDetectArea area;
    FvdDetectParam detectparam[ALGMAX];
} FvdDetParam;

typedef struct common_data{
    QList <FvdCamParam> cam_param;
    QList <FvdDetParam> det_param;
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
    QList <FvdComonData> d;
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

        QJsonArray array_cam_param=json_src.object()["cam_param"].toArray();
     //   for(int i=0;i<road_total_number;i++){
        QJsonArray array_det_param=json_src.object()["det_param"].toArray();

            for(int j=0;j<camera_total_number;j++)
            {
                FvdCamParam cam_param;
                FvdDetParam det_param;


                cam_param.coilnum=array_cam_param[j].toObject()["coilnum"].toInt();

                cam_param.camattr.camera_enabled=array_cam_param[j].toObject()["camattr"].toObject()["camera_enabled"].toBool();
                cam_param.camattr.adjustIp=array_cam_param[j].toObject()["camattr"].toObject()["adjustIp"].toString();
                cam_param.camattr.adjustport=array_cam_param[j].toObject()["camattr"].toObject()["adjustport"].toInt();
                cam_param.camattr.camID=array_cam_param[j].toObject()["camattr"].toObject()["camID"].toInt();
                cam_param.camattr.cammerIp=array_cam_param[j].toObject()["camattr"].toObject()["cammerIp"].toString();
                cam_param.camattr.cammerport=array_cam_param[j].toObject()["camattr"].toObject()["cammerport"].toInt();
                cam_param.camattr.direction=array_cam_param[j].toObject()["camattr"].toObject()["direction"].toInt();
                cam_param.camattr.passwd=array_cam_param[j].toObject()["camattr"].toObject()["passwd"].toString();
                cam_param.camattr.signalIp=array_cam_param[j].toObject()["camattr"].toObject()["signalIp"].toString();
                cam_param.camattr.signalport=array_cam_param[j].toObject()["camattr"].toObject()["signalport"].toInt();
                cam_param.camattr.urlname=array_cam_param[j].toObject()["camattr"].toObject()["urlname"].toString();
                cam_param.camattr.username=array_cam_param[j].toObject()["camattr"].toObject()["username"].toString();


                cam_param.camdem.baselinelen=array_cam_param[j].toObject()["camdem"].toObject()["baselinelen"].toInt();
                cam_param.camdem.cam2stop=array_cam_param[j].toObject()["camdem"].toObject()["cam2stop"].toInt();
                cam_param.camdem.camheight=array_cam_param[j].toObject()["camdem"].toObject()["camheight"].toInt();
                cam_param.camdem.farth2stop=array_cam_param[j].toObject()["camdem"].toObject()["farth2stop"].toInt();
                cam_param.camdem.lannum=array_cam_param[j].toObject()["camdem"].toObject()["lannum"].toInt();
                cam_param.camdem.number=array_cam_param[j].toObject()["camdem"].toObject()["number"].toInt();
                cam_param.camdem.recent2stop=array_cam_param[j].toObject()["camdem"].toObject()["recent2stop"].toInt();


                for(int p=0;p<DETECTLANENUMMAX;p++){
                    cam_param.channelcoil[p].number=array_cam_param[j].toObject()["channelcoil"].toArray()[p].toObject()["number"].toInt();
                    cam_param.channelcoil[p].farthCoillen=array_cam_param[j].toObject()["channelcoil"].toArray()[p].toObject()["farthCoillen"].toInt();
                    cam_param.channelcoil[p].recentCoillen=array_cam_param[j].toObject()["channelcoil"].toArray()[p].toObject()["recentCoillen"].toInt();
               //       cam_param.channelcoil[p].number=array_cam_param[j].toObject()["channelcoil"].toArray()[p].toInt();
                }
                d.cam_param.append(cam_param);

                //////////////////////
                det_param.detectlane.lanenum=array_det_param[j].toObject()["detectlane"].toObject()["lanenum"].toInt();
                for(int k=0;k<DETECTLANENUMMAX;k++){
                     for(int l=0;l<COILPOINTMAX;l++){
                        det_param.detectlane.virtuallane[k].Front[l].x=array_det_param[j].toObject()["detectlane"].\
                                toObject()["virtuallane"].toArray()[k].toObject()["Front"].toArray()[l].toObject()["x"].toInt();
                        det_param.detectlane.virtuallane[k].Front[l].y=array_det_param[j].toObject()["detectlane"].\
                                toObject()["virtuallane"].toArray()[k].toObject()["Front"].toArray()[l].toObject()["y"].toInt();

                        det_param.detectlane.virtuallane[k].Rear[l].x=array_det_param[j].toObject()["detectlane"].\
                                toObject()["virtuallane"].toArray()[k].toObject()["Rear"].toArray()[l].toObject()["x"].toInt();
                        det_param.detectlane.virtuallane[k].Rear[l].y=array_det_param[j].toObject()["detectlane"].\
                                toObject()["virtuallane"].toArray()[k].toObject()["Rear"].toArray()[l].toObject()["y"].toInt();

                     }

                }
                for(int k=0;k<STANDPOINT;k++){

                    det_param.area.realcoordinate[k].x=array_det_param[j].toObject()["area"].toObject()["realcoordinate"].toArray()[k].toObject()["x"].toInt();
                    det_param.area.realcoordinate[k].y=array_det_param[j].toObject()["area"].toObject()["realcoordinate"].toArray()[k].toObject()["y"].toInt();
                    det_param.area.vircoordinate[k].x=array_det_param[j].toObject()["area"].toObject()["vircoordinate"].toArray()[k].toObject()["x"].toInt();
                    det_param.area.vircoordinate[k].y=array_det_param[j].toObject()["area"].toObject()["vircoordinate"].toArray()[k].toObject()["y"].toInt();

                }



                    for(int k=0;k<ALGMAX;k++){
                        det_param.detectparam[k].uTransFactor=array_det_param[j].toObject()["detectparam"].toArray()[k].toObject()["uTransFactor"].toInt();
                        det_param.detectparam[k].uGraySubThreshold=array_det_param[j].toObject()["detectparam"].toArray()[k].toObject()["uGraySubThreshold"].toInt();
                        det_param.detectparam[k].uSpeedCounterChangedThreshold=array_det_param[j].toObject()["detectparam"].toArray()[k].toObject()["uSpeedCounterChangedThreshold"].toInt();
                        det_param.detectparam[k].uSpeedCounterChangedThreshold1=array_det_param[j].toObject()["detectparam"].toArray()[k].toObject()["uSpeedCounterChangedThreshold1"].toInt();
                        det_param.detectparam[k].uSpeedCounterChangedThreshold2=array_det_param[j].toObject()["detectparam"].toArray()[k].toObject()["uSpeedCounterChangedThreshold2"].toInt();
                        det_param.detectparam[k].uDayNightJudgeMinContiuFrame=array_det_param[j].toObject()["detectparam"].toArray()[k].toObject()["uDayNightJudgeMinContiuFrame"].toInt();
                        det_param.detectparam[k].uDetectSens1=array_det_param[j].toObject()["detectparam"].toArray()[k].toObject()["uDetectSens1"].toInt();
                        det_param.detectparam[k].uDetectSens2=array_det_param[j].toObject()["detectparam"].toArray()[k].toObject()["uDetectSens2"].toInt();
                        det_param.detectparam[k].uComprehensiveSens=array_det_param[j].toObject()["detectparam"].toArray()[k].toObject()["uComprehensiveSens"].toInt();
                        det_param.detectparam[k].uStatisticsSens1=array_det_param[j].toObject()["detectparam"].toArray()[k].toObject()["uStatisticsSens1"].toInt();
                        det_param.detectparam[k].uStatisticsSens2=array_det_param[j].toObject()["detectparam"].toArray()[k].toObject()["uStatisticsSens2"].toInt();
                        det_param.detectparam[k].uSobelThreshold=array_det_param[j].toObject()["detectparam"].toArray()[k].toObject()["uSobelThreshold"].toInt();
                        det_param.detectparam[k].shutterMax=array_det_param[j].toObject()["detectparam"].toArray()[k].toObject()["shutterMax"].toInt();
                        det_param.detectparam[k].shutterMin=array_det_param[j].toObject()["detectparam"].toArray()[k].toObject()["shutterMin"].toInt();
                     }

                    det_param.laneline.lanelinenum=array_det_param[j].toObject()["laneline"].toObject()["lanelinenum"].toInt();
                    for(int k=0;k<LANELINEMAX;k++){
                        det_param.laneline.laneline[k].startx=array_det_param[j].toObject()["laneline"].toObject()["laneline"].toArray()[k]\
                                .toObject()["startx"].toInt();

                        det_param.laneline.laneline[k].starty=array_det_param[j].toObject()["laneline"].toObject()["laneline"].toArray()[k]\
                                .toObject()["starty"].toInt();
                        det_param.laneline.laneline[k].endx=array_det_param[j].toObject()["laneline"].toObject()["laneline"].toArray()[k]\
                                .toObject()["endx"].toInt();

                        det_param.laneline.laneline[k].endy=array_det_param[j].toObject()["laneline"].toObject()["laneline"].toArray()[k]\
                                .toObject()["endy"].toInt();



                    }


                    for(int k=0;k<STANDARDVAULEMAX;k++){
                                det_param.standpoint[k].coordinate.x=array_det_param[j].toObject()["standpoint"].toArray()[k].toObject()["coordinate"].toObject()\
                                        ["x"].toInt();
                                det_param.standpoint[k].coordinate.y=array_det_param[j].toObject()["standpoint"].toArray()[k].toObject()["coordinate"].toObject()\
                                        ["y"].toInt();
                                det_param.standpoint[k].value=array_det_param[j].toObject()["standpoint"].toArray()[k].toObject()["value"].toInt();

                    }

                    for(int k=0;k<TIME_CHECKPOINT;k++)
                         det_param.timep[k]=array_det_param[j].toObject()["timep"].toArray()[k].toInt();



                d.det_param.append(det_param);





                ////


                // cam_param..recent2stop=array_cam_param[j].toObject()["camdem"].toObject()["recent2stop"].toInt();


//                QJsonObject obj_cam_param=array_cam_param[j].toObject();
//                bool test=(bool)obj_cam_param["camattr"].toObject()["camera_enabled"].toBool();

                //        cam_param.camattr.camera_enabled=array_cam_param["camattr"].toObject()["camera_enabled"].toInt();
            }

  //      }




    }

    void init()
    {
        QDir *dir=new QDir(QString("cfg_dir"));
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
                qDebug()<<"parsing"<<b;
            }

        }
        //      qDebug()<<"reading msg";
        //   qDebug()<<path;
    }

signals:

public slots:
private:
    explicit Data(QObject *parent = 0);

    int road_total_number;
};

#endif // DATA_H
