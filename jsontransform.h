#ifndef JSONTRANSFORM_H
#define JSONTRANSFORM_H
//#include "alg.h"
#include "common.h"
#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#define  WRITE_JSON_ARRAY_MEMBER(ob,dat,tp,n,nm)\
{   int var;QJsonArray   js_array_##nm;\
    for(var=0;var<n;var++){\
    QJsonObject obj_##nm;\
    write_##tp(obj_##nm,dat.nm[var]);\
    js_array_##nm.append(obj_##nm);\
    } \
    ob[#nm]=js_array_##nm; \
    }

#define  READ_JSON_ARRAY_MEMBER(ob,dat,tp,n,nm)\
{   int var;QJsonArray   js_array_##nm=ob[#nm].toArray();\
    for(var=0;var<n;var++){\
    QJsonObject obj_##nm= js_array_##nm[var].toObject();\
    read_##tp(obj_##nm,dat.nm[var]);\
    } \
    }//TODO

#define  WRITE_JSON_ARRAY_MEMBER_VALUE(ob,dat,n,nm)\
{   int var;QJsonArray   js_array_##nm;\
    for(var=0;var<n;var++){\
    QJsonValue obj_##nm((int)dat.nm[var]);\
    js_array_##nm.append(obj_##nm);\
    } \
    ob[#nm]=js_array_##nm; \
    }
#define  READ_JSON_ARRAY_MEMBER_VALUE(ob,dat,n,nm)\
{   int var;QJsonArray   js_array_##nm=ob[#nm].toArray();\
    for(var=0;var<n;var++){\
    dat.nm[var]=  js_array_##nm[var].toInt();\
    } \
    }//TODO

#define  WRITE_JSON_OBJ_MEMBER(ob,dat,tp,nm)\
{   \
    QJsonObject obj_##nm;\
    write_##tp(obj_##nm,dat.nm);\
    ob[#nm]=obj_##nm; \
    }
#define  READ_JSON_OBJ_MEMBER(ob,dat,tp,nm)\
{   \
    read_##tp(ob[#nm].toObject(),dat.nm);\
    }//TODO


#define  WRITE_JSON_INT_MEMBER(ob,dat,x)      ob[#x]=(int)dat.x;
#define  READ_JSON_INT_MEMBER(ob,dat,x)        dat.x=ob[#x].toInt();

#define  WRITE_JSON_STR_MEMBER(ob,dat,x)      ob[#x]=(char *)dat.x;
//#define  READ_JSON_STR_MEMBER(ob,dat,x)      strcpy((char *)dat.x ,ob[#x].toString().toLatin1().data());//TODO check
#define  READ_JSON_STR_MEMBER(ob,dat,x)      strcpy((char *)dat.x ,ob[#x].toString().toUtf8().data());//TODO check


#define WRITE_FUN_DEF(key,rts)   void  inline write_##key(QJsonObject &obj,const key data) {rts;}
#define READ_FUN_DEF(key,rts)   void inline  read_##key(const QJsonObject obj, key &data) {rts;}




///
WRITE_FUN_DEF(
        mCamAttributes,
        WRITE_JSON_INT_MEMBER(obj,data,direction);
WRITE_JSON_INT_MEMBER(obj,data,camID);
WRITE_JSON_INT_MEMBER(obj,data,cammerport);
WRITE_JSON_INT_MEMBER(obj,data,adjustport);
WRITE_JSON_INT_MEMBER(obj,data,signalport);
WRITE_JSON_STR_MEMBER(obj,data,urlname);
WRITE_JSON_STR_MEMBER(obj,data,username);
WRITE_JSON_STR_MEMBER(obj,data,passwd);
WRITE_JSON_STR_MEMBER(obj,data,cammerIp);
WRITE_JSON_STR_MEMBER(obj,data,adjustIp);
WRITE_JSON_STR_MEMBER(obj,data,signalIp);
)
READ_FUN_DEF(
        mCamAttributes,
        READ_JSON_INT_MEMBER(obj,data,direction);
READ_JSON_INT_MEMBER(obj,data,camID);
READ_JSON_INT_MEMBER(obj,data,cammerport);
READ_JSON_INT_MEMBER(obj,data,adjustport);
READ_JSON_INT_MEMBER(obj,data,signalport);
READ_JSON_STR_MEMBER(obj,data,urlname);
READ_JSON_STR_MEMBER(obj,data,username);
READ_JSON_STR_MEMBER(obj,data,passwd);
READ_JSON_STR_MEMBER(obj,data,cammerIp);
READ_JSON_STR_MEMBER(obj,data,adjustIp);
READ_JSON_STR_MEMBER(obj,data,signalIp);
)
WRITE_FUN_DEF(
        mCamDemarcateParam,
        WRITE_JSON_INT_MEMBER(obj,data,cam2stop);
WRITE_JSON_INT_MEMBER(obj,data,camheight);
WRITE_JSON_INT_MEMBER(obj,data,lannum);
WRITE_JSON_INT_MEMBER(obj,data,number);
WRITE_JSON_INT_MEMBER(obj,data,baselinelen);
WRITE_JSON_INT_MEMBER(obj,data,farth2stop);
WRITE_JSON_INT_MEMBER(obj,data,recent2stop);

)
READ_FUN_DEF(
        mCamDemarcateParam,
        READ_JSON_INT_MEMBER(obj,data,cam2stop);
READ_JSON_INT_MEMBER(obj,data,camheight);
READ_JSON_INT_MEMBER(obj,data,lannum);
READ_JSON_INT_MEMBER(obj,data,number);
READ_JSON_INT_MEMBER(obj,data,baselinelen);
READ_JSON_INT_MEMBER(obj,data,farth2stop);
READ_JSON_INT_MEMBER(obj,data,recent2stop);

)
WRITE_FUN_DEF(
        mChannelVirtualcoil,
        WRITE_JSON_INT_MEMBER(obj,data,number);
WRITE_JSON_INT_MEMBER(obj,data,farthCoillen);
WRITE_JSON_INT_MEMBER(obj,data,recentCoillen);
)
READ_FUN_DEF(
        mChannelVirtualcoil,
        READ_JSON_INT_MEMBER(obj,data,number);
READ_JSON_INT_MEMBER(obj,data,farthCoillen);
READ_JSON_INT_MEMBER(obj,data,recentCoillen);
)
//typedef struct CamParam {
//    unsigned char coilnum;
//    mCamAttributes camattr;
//    mCamDemarcateParam camdem;
//    mChannelVirtualcoil channelcoil[DETECTLANENUMMAX];
//} mCamParam;
WRITE_FUN_DEF(
        mCamParam,
        WRITE_JSON_INT_MEMBER(obj,data,coilnum);
WRITE_JSON_OBJ_MEMBER(obj,data,mCamAttributes,camattr);
WRITE_JSON_OBJ_MEMBER(obj,data,mCamDemarcateParam,camdem);
WRITE_JSON_ARRAY_MEMBER(obj,data,mChannelVirtualcoil,DETECTLANENUMMAX,channelcoil);
)
READ_FUN_DEF(
        mCamParam,
        READ_JSON_INT_MEMBER(obj,data,coilnum);
READ_JSON_OBJ_MEMBER(obj,data,mCamAttributes,camattr);
READ_JSON_OBJ_MEMBER(obj,data,mCamDemarcateParam,camdem);
READ_JSON_ARRAY_MEMBER(obj,data,mChannelVirtualcoil,DETECTLANENUMMAX,channelcoil);
)
WRITE_FUN_DEF(
        mPoint,
        WRITE_JSON_INT_MEMBER(obj,data,x);
WRITE_JSON_INT_MEMBER(obj,data,y);
)
READ_FUN_DEF(
        mPoint,
        READ_JSON_INT_MEMBER(obj,data,x);
READ_JSON_INT_MEMBER(obj,data,y);
)

WRITE_FUN_DEF(
        mChannelCoil,
        WRITE_JSON_ARRAY_MEMBER(obj,data,mPoint,COILPOINTMAX,Rear);
WRITE_JSON_ARRAY_MEMBER(obj,data,mPoint,COILPOINTMAX,Front);
)

READ_FUN_DEF(
        mChannelCoil,
        READ_JSON_ARRAY_MEMBER(obj,data,mPoint,COILPOINTMAX,Rear);
READ_JSON_ARRAY_MEMBER(obj,data,mPoint,COILPOINTMAX,Front);
)


WRITE_FUN_DEF(
        mCamDetectLane,
        WRITE_JSON_INT_MEMBER(obj,data,lanenum);
WRITE_JSON_ARRAY_MEMBER(obj,data,mChannelCoil,DETECTLANENUMMAX,virtuallane);
)
READ_FUN_DEF(
        mCamDetectLane,
        READ_JSON_INT_MEMBER(obj,data,lanenum);
READ_JSON_ARRAY_MEMBER(obj,data,mChannelCoil,DETECTLANENUMMAX,virtuallane);
)

WRITE_FUN_DEF(
        mLine,
        WRITE_JSON_INT_MEMBER(obj,data,startx);
WRITE_JSON_INT_MEMBER(obj,data,starty);
WRITE_JSON_INT_MEMBER(obj,data,endx);
WRITE_JSON_INT_MEMBER(obj,data,endy);
)

READ_FUN_DEF(
        mLine,
        READ_JSON_INT_MEMBER(obj,data,startx);
READ_JSON_INT_MEMBER(obj,data,starty);
READ_JSON_INT_MEMBER(obj,data,endx);
READ_JSON_INT_MEMBER(obj,data,endy);
)
WRITE_FUN_DEF(
        mVirtualLaneLine,
        WRITE_JSON_INT_MEMBER(obj,data,lanelinenum);
WRITE_JSON_ARRAY_MEMBER(obj,data,mLine,LANELINEMAX,laneline);
)

READ_FUN_DEF(
        mVirtualLaneLine,
        READ_JSON_INT_MEMBER(obj,data,lanelinenum);
READ_JSON_ARRAY_MEMBER(obj,data,mLine,LANELINEMAX,laneline);
)
WRITE_FUN_DEF(
        mStandardPoint,
        WRITE_JSON_OBJ_MEMBER(obj,data,mPoint,coordinate);
WRITE_JSON_INT_MEMBER(obj,data,value);
)
READ_FUN_DEF(
        mStandardPoint,
        READ_JSON_OBJ_MEMBER(obj,data,mPoint,coordinate);
READ_JSON_INT_MEMBER(obj,data,value);
)


WRITE_FUN_DEF(
        mDemDetectArea,
        WRITE_JSON_ARRAY_MEMBER(obj,data,mPoint,STANDPOINT,vircoordinate);
WRITE_JSON_ARRAY_MEMBER(obj,data,mPoint,STANDPOINT,realcoordinate);
)\

WRITE_FUN_DEF(
        mDetectParam,
        WRITE_JSON_INT_MEMBER(obj,data,uTransFactor);
WRITE_JSON_INT_MEMBER(obj,data,uGraySubThreshold);
WRITE_JSON_INT_MEMBER(obj,data,uSpeedCounterChangedThreshold);
WRITE_JSON_INT_MEMBER(obj,data,uSpeedCounterChangedThreshold1);
WRITE_JSON_INT_MEMBER(obj,data,uSpeedCounterChangedThreshold2);
WRITE_JSON_INT_MEMBER(obj,data,uDayNightJudgeMinContiuFrame);
WRITE_JSON_INT_MEMBER(obj,data,uComprehensiveSens);
WRITE_JSON_INT_MEMBER(obj,data,uDetectSens1);
WRITE_JSON_INT_MEMBER(obj,data,uDetectSens2);
WRITE_JSON_INT_MEMBER(obj,data,uStatisticsSens1);
WRITE_JSON_INT_MEMBER(obj,data,uStatisticsSens2);
WRITE_JSON_INT_MEMBER(obj,data,uSobelThreshold);
WRITE_JSON_INT_MEMBER(obj,data,shutterMax);
WRITE_JSON_INT_MEMBER(obj,data,shutterMin);
)
WRITE_FUN_DEF(
        mCamDetectParam,
        WRITE_JSON_ARRAY_MEMBER_VALUE(obj,data,4,timep);
WRITE_JSON_OBJ_MEMBER(obj,data,mCamDetectLane,detectlane);
WRITE_JSON_OBJ_MEMBER(obj,data,mVirtualLaneLine,laneline);
WRITE_JSON_ARRAY_MEMBER(obj,data,mStandardPoint,STANDARDVAULEMAX,standpoint);
WRITE_JSON_OBJ_MEMBER(obj,data,mDemDetectArea,area);
WRITE_JSON_ARRAY_MEMBER(obj,data,mDetectParam,ALGMAX,detectparam);
)



READ_FUN_DEF(
        mDemDetectArea,
        READ_JSON_ARRAY_MEMBER(obj,data,mPoint,STANDPOINT,vircoordinate);
READ_JSON_ARRAY_MEMBER(obj,data,mPoint,STANDPOINT,realcoordinate);
)\

READ_FUN_DEF(
        mDetectParam,
        READ_JSON_INT_MEMBER(obj,data,uTransFactor);
READ_JSON_INT_MEMBER(obj,data,uGraySubThreshold);
READ_JSON_INT_MEMBER(obj,data,uSpeedCounterChangedThreshold);
READ_JSON_INT_MEMBER(obj,data,uSpeedCounterChangedThreshold1);
READ_JSON_INT_MEMBER(obj,data,uSpeedCounterChangedThreshold2);
READ_JSON_INT_MEMBER(obj,data,uDayNightJudgeMinContiuFrame);
READ_JSON_INT_MEMBER(obj,data,uComprehensiveSens);
READ_JSON_INT_MEMBER(obj,data,uDetectSens1);
READ_JSON_INT_MEMBER(obj,data,uDetectSens2);
READ_JSON_INT_MEMBER(obj,data,uStatisticsSens1);
READ_JSON_INT_MEMBER(obj,data,uStatisticsSens2);
READ_JSON_INT_MEMBER(obj,data,uSobelThreshold);
READ_JSON_INT_MEMBER(obj,data,shutterMax);
READ_JSON_INT_MEMBER(obj,data,shutterMin);
)
READ_FUN_DEF(
        mCamDetectParam,
        READ_JSON_ARRAY_MEMBER_VALUE(obj,data,4,timep);
READ_JSON_OBJ_MEMBER(obj,data,mCamDetectLane,detectlane);
READ_JSON_OBJ_MEMBER(obj,data,mVirtualLaneLine,laneline);
READ_JSON_ARRAY_MEMBER(obj,data,mStandardPoint,STANDARDVAULEMAX,standpoint);
READ_JSON_OBJ_MEMBER(obj,data,mDemDetectArea,area);
READ_JSON_ARRAY_MEMBER(obj,data,mDetectParam,ALGMAX,detectparam);
)



WRITE_FUN_DEF(
        m_caminfo,
        WRITE_JSON_INT_MEMBER(obj,data,camstatus);
WRITE_JSON_INT_MEMBER(obj,data,camdirect);
WRITE_JSON_STR_MEMBER(obj,data,cammerIp);
)
READ_FUN_DEF(
        m_caminfo,
        READ_JSON_INT_MEMBER(obj,data,camstatus);
READ_JSON_INT_MEMBER(obj,data,camdirect);
READ_JSON_STR_MEMBER(obj,data,cammerIp);
)
WRITE_FUN_DEF(
        mDetectDeviceConfig,
        WRITE_JSON_INT_MEMBER(obj,data,deviceID);
WRITE_JSON_INT_MEMBER(obj,data,detectport);
WRITE_JSON_INT_MEMBER(obj,data,camnum);
WRITE_JSON_STR_MEMBER(obj,data,detectip);
WRITE_JSON_STR_MEMBER(obj,data,detectname);
WRITE_JSON_ARRAY_MEMBER(obj,data,m_caminfo,CAM_NUM_MAX,cam_info);
)
READ_FUN_DEF(
        mDetectDeviceConfig,
        READ_JSON_INT_MEMBER(obj,data,deviceID);
READ_JSON_INT_MEMBER(obj,data,detectport);
READ_JSON_INT_MEMBER(obj,data,camnum);
READ_JSON_STR_MEMBER(obj,data,detectip);
READ_JSON_STR_MEMBER(obj,data,detectname);
READ_JSON_ARRAY_MEMBER(obj,data,m_caminfo,CAM_NUM_MAX,cam_info);
)

class JsonTransform
{
public:

    JsonTransform();
//    static void mDetectDeviceConfig_json_2_struct(   QJsonObject js_obj_mDetectDeviceConfig,mDetectDeviceConfig &obj_mDetectDeviceConfig)
//    {
//           read_mDetectDeviceConfig(js_obj_mDetectDeviceConfig,obj_mDetectDeviceConfig);
//    }
//    static void mDetectDeviceConfig_qarray_2_struct(   QByteArray js_obj_mDetectDeviceConfig,mDetectDeviceConfig &obj_mDetectDeviceConfig)
//    {
//        QJsonDocument doc1(QJsonDocument::fromJson(js_obj_mDetectDeviceConfig_data));
//        QJsonObject    js_obj_mDetectDeviceConfig=doc1.object()["mDetectDeviceConfig"].toObject(); ;
//        read_mDetectDeviceConfig(js_obj_mDetectDeviceConfig,obj_mDetectDeviceConfig);
//    }
//    static void mDetectDeviceConfig_qarray_2_struct(   QByteArray js_obj_mDetectDeviceConfig_data,mDetectDeviceConfig &obj_mDetectDeviceConfig)
//    {
//          QJsonDocument doc1(QJsonDocument::fromJson(js_obj_mDetectDeviceConfig_data));
//          QJsonObject    js_obj_mDetectDeviceConfig=doc1.object()["mDetectDeviceConfig"].toObject(); ;
//          read_mDetectDeviceConfig(js_obj_mDetectDeviceConfig,obj_mDetectDeviceConfig);
//    }






// #--> string
    // ## --> string cat
   //   -->type




//    static void mCamParam_json_2_struct(   QJsonObject js_obj_mCamParam,mCamParam &obj_mCamParam)
//    {
//           read_mDetectDeviceConfig(js_obj_mCamParam,obj_mCamParam);
//    }

#define ARRAY_2_STRUCT(type)    static void type##_qarray_2_struct( QByteArray js_obj_##type##_data,type &obj_##type){\
           QJsonDocument doc1(QJsonDocument::fromJson(js_obj_##type##_data));\
            QJsonObject    js_obj_##type=doc1.object()[#type].toObject(); \
           read_##type(js_obj_##type,obj_##type);};
#define STRUCT_2_ARRAY(type)    static void type##_struct_2_qarray( QByteArray js_obj_##type##_data,type &obj_##type){\
              QJsonObject    js_obj_##type;\
              write_##type(js_obj_##type,obj_##type);\
             QJsonDocument doc1;\
             doc1.setObject(js_obj_##type);\
            js_obj_##type##_data=  doc1.toJson();\
};

    ARRAY_2_STRUCT(mCamParam)
    STRUCT_2_ARRAY(mCamParam)

    ARRAY_2_STRUCT(mCamDetectParam)
    STRUCT_2_ARRAY(mCamDetectParam)

    ARRAY_2_STRUCT(mDetectDeviceConfig)
    STRUCT_2_ARRAY(mDetectDeviceConfig)
 //    static void mCamParam_qarray_2_struct(   QByteArray js_obj_mCamParam_data,mCamParam &obj_mCamParam)
//    {
//          QJsonDocument doc1(QJsonDocument::fromJson(js_obj_mCamParam_data));
//          QJsonObject    js_obj_mCamParam=doc1.object()["mCamParam"].toObject(); ;
//          read_mCamParam(js_obj_mCamParam,obj_mCamParam);
//    }
//    static void mCamParam_struct_2_qarray(   QByteArray &js_obj_mCamParam_data,mCamParam obj_mCamParam)
//    {
//       //   QJsonDocument doc1(QJsonDocument::fromJson(js_obj_mCamParam_data));
//      //    QJsonObject    js_obj_mCamParam=doc1.object()["mCamParam"].toObject(); ;
//    //      read_mCamParam(js_obj_mCamParam,obj_mCamParam);

//          QJsonObject    js_obj_mCamParam;
//          write_mCamParam(js_obj_mCamParam,obj_mCamParam);

//         QJsonDocument doc1;
//         doc1.setObject(js_obj_mCamParam);
//        js_obj_mCamParam_data=  doc1.toJson();

//    }

//    static void mCamDetectParam_json_2_struct(   QJsonObject js_obj_mCamDetectParam,mCamDetectParam &obj_mCamDetectParam)
//    {
//           read_mCamDetectParam(js_obj_mCamDetectParam,obj_mCamDetectParam);
//    }

//     static void mCamDetectParam_qarray_2_struct(   QJsonObject js_obj_mCamDetectParam,mCamDetectParam &obj_mCamDetectParam)
//       {
//           read_mCamDetectParam(js_obj_mCamDetectParam,obj_mCamDetectParam);
//    }
//    static void mCamDetectParam_qarray_2_struct(   QByteArray js_obj_mCamDetectParam_data,mCamDetectParam &obj_mCamDetectParam)
//    {
//          QJsonDocument doc1(QJsonDocument::fromJson(js_obj_mCamDetectParam_data));
//          QJsonObject    js_obj_mCamDetectParam=doc1.object()["mCamDetectParam"].toObject(); ;
//          read_mCamDetectParam(js_obj_mCamDetectParam,obj_mCamDetectParam);
//    }


};

#endif // JSONTRANSFORM_H
