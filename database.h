#ifndef DATABASE_H
#define DATABASE_H
#include <QByteArray>
#include <QFile>
#include "common.h"
#include "jsontransform.h"
//#include "alg.h"
//#define GET_FUN_DEF(type)   static  bool    get_##type(int  no,QByteArray *p_data) {        QString file_path;\
//    file_path.append("cfg_dir/");\
//    file_path.append(#type);\
//    file_path.append("_");\
//    file_path+=QString("%1").arg(no);\
//    file_path.append(".");\
//    file_path.append("json");\
//    QFile file( file_path);\
//    bool ret=file.open(QIODevice::ReadWrite);\
//    if(ret==true){*p_data=file.readAll();\
//    file.close();}return ret;}






//#define G_GET_FUN_DEF(type)   static  bool    get_##type(int no,type &type##_struct){        QByteArray json_data;\
//bool ret=Database::get_##type(no,&json_data);\
//JsonTransform::type##_qarray_2_struct(json_data,type##_struct);return ret;}


//#define DEF_ARRAY_2_STRUCT(type)   static  bool    get_##type(int no,type &type##_struct){        QByteArray json_data;\
//bool ret=Database::get_##type(no,&json_data);\
//JsonTransform::type##_qarray_2_struct(json_data,type##_struct);return ret;}


//#define SET_FUN_DEF(type)   static  void    set_##type(int  no,QByteArray *p_data) {             QString file_path;\
//file_path.append("cfg_dir/");\
//file_path.append(#type);\
//file_path.append("_");\
//file_path+=QString("%1").arg(no);\
//file_path.append(".");\
//file_path.append("json");\
//QFile file( file_path);\
//file.open(QIODevice::ReadWrite);\
//file.write(*p_data);\
//file.close();}

//#define G_SET_FUN_DEF(type)   static  void    set_##type(int no,type &type##_struct){                QByteArray json_data;\
//JsonTransform::type##_struct_2_qarray(json_data,type##_struct);\
//set_##type(no,&json_data);}


#define DEF_READ_FILE(type)   static  bool    get_##type(int  no, type &type##_struct) {      QByteArray json_data;  \
    QByteArray *p_data=&json_data;\
    QString file_path;\
    file_path.append("cfg_dir/");\
    file_path+=QString("camera%1/").arg(no);\
    file_path.append(#type).append(".").append("json");\
    QFile file( file_path);\
    bool ret=file.open(QIODevice::ReadWrite);\
    if(ret==true){*p_data=file.readAll();\
    file.close();JsonTransform::type##_qarray_2_struct(json_data,type##_struct);}return ret;}

#define DEF_WRITE_FILE(type)   static  void    set_##type(int  no,type &type##_struct) {   QByteArray json_data; \
    JsonTransform::type##_struct_2_qarray(json_data,type##_struct);\
    QByteArray *p_data =&json_data;          QString file_path;\
    file_path.append("cfg_dir/");\
    file_path+=QString("camera%1/").arg(no);\
    file_path.append(#type).append(".").append("json");\
QFile file( file_path);\
file.open(QIODevice::ReadWrite);\
file.write(*p_data);\
file.close();}



#define DEF_READ_FILE_CLIENT(type)   static  bool    get_##type(int dev_no,int  no, type &type##_struct) {      QByteArray json_data;  \
    QByteArray *p_data=&json_data;\
    QString file_path;\
    file_path+=QString("device%1/").arg(dev_no);\
    file_path.append("cfg_dir/");\
    file_path+=QString("camera%1/").arg(no);\
    file_path.append(#type).append(".").append("json");\
    QFile file( file_path);\
    bool ret=file.open(QIODevice::ReadWrite);\
    if(ret==true){*p_data=file.readAll();\
    file.close();JsonTransform::type##_qarray_2_struct(json_data,type##_struct);}return ret;}

#define DEF_WRITE_FILE_CLIENT(type)   static  void    set_##type(int dev_no,int  no,type &type##_struct) {   QByteArray json_data; \
    JsonTransform::type##_struct_2_qarray(json_data,type##_struct);\
    QByteArray *p_data =&json_data;          QString file_path;\
    file_path+=QString("device%1/").arg(dev_no);\
    file_path.append("cfg_dir/");\
    file_path+=QString("camera%1/").arg(no);\
    file_path.append(#type).append(".").append("json");\
QFile file( file_path);\
file.open(QIODevice::ReadWrite);\
file.write(*p_data);\
file.close();}
class Database
{
public:
    Database();

//    static void get_mDetectDeviceConfig()
//    {

//    }

//    static void set_mDetectDeviceConfig()
//    {

//    }
//    static void get_mCamDetectParam(){

//    }

//    static void get_mCamParam(int no,QByteArray *p_data)
//    {
//     //   QString file_path("cfg_dir/mCamParam_3.json");
//        QString file_path;
//        file_path.append("cfg_dir/");
//        file_path.append("mCamParam_");
//        file_path+=QString("%1").arg(no);
//        file_path.append(".");
//        file_path.append("json");
//        QFile file( file_path);
//        file.open(QIODevice::ReadWrite);
//        *p_data=file.readAll();
//        file.close();
//    }


    DEF_READ_FILE_CLIENT(mCamParam)
    DEF_READ_FILE_CLIENT(mDetectDeviceConfig)
    DEF_READ_FILE_CLIENT(mCamDetectParam)

    DEF_WRITE_FILE_CLIENT(mCamParam)
    DEF_WRITE_FILE_CLIENT(mDetectDeviceConfig)
    DEF_WRITE_FILE_CLIENT(mCamDetectParam)

//    DEF_READ_FILE(mCamParam)
//    DEF_READ_FILE(mDetectDeviceConfig)
//    DEF_READ_FILE(mCamDetectParam)

//    DEF_WRITE_FILE(mCamParam)
//    DEF_WRITE_FILE(mDetectDeviceConfig)
//    DEF_WRITE_FILE(mCamDetectParam)

// GET_FUN_DEF(mCamParam)
// G_GET_FUN_DEF(mCamParam)

// SET_FUN_DEF(mCamParam)
// G_SET_FUN_DEF(mCamParam)

// GET_FUN_DEF(mDetectDeviceConfig)
// G_GET_FUN_DEF(mDetectDeviceConfig)
// SET_FUN_DEF(mDetectDeviceConfig)
// G_SET_FUN_DEF(mDetectDeviceConfig)

// GET_FUN_DEF(mCamDetectParam)
// G_GET_FUN_DEF(mCamDetectParam)
// SET_FUN_DEF(mCamDetectParam)
// G_SET_FUN_DEF(mCamDetectParam)
// static      void get_mCamParam(int no,mCamParam &mCamParam_struct)
//    {
//        QByteArray json_data;
//        Database::get_mCamParam(no,&json_data);
//        JsonTransform::mCamParam_qarray_2_struct(json_data,mCamParam_struct);
//    }
// static void set_mCamParam(int no,QByteArray *p_data)
//    {
//     //   QString file_path("cfg_dir/mCamParam_3.json");
//        QString file_path;
//        file_path.append("cfg_dir/");
//        file_path.append("mCamParam_");
//        file_path+=QString("%1").arg(no);
//        file_path.append(".");
//        file_path.append("json");
//        QFile file( file_path);
//        file.open(QIODevice::ReadWrite);
//        file.write(*p_data);
//        file.close();
//   }
//    static      void set_mCamParam(int no,mCamParam &mCamParam_struct)
//       {
//           QByteArray json_data;
//          JsonTransform::mCamParam_struct_2_qarray(json_data,mCamParam_struct);
//         set_mCamParam(no,&json_data);
//       }
};

#endif // DATABASE_H
