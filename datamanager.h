#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include "database.h"
#include <QDebug>
typedef struct device_struct{
    int camera_number;
    mCamParam cam_param[CAM_NUM_MAX];
    mCamDetectParam det_param[CAM_NUM_MAX];
    mDetectDeviceConfig dev_cfg;
}ds;

typedef struct road{
     QString road_name;
     QString device_names[16];
     int device_num;
}m_road;

class DataManager : public QObject
{
    Q_OBJECT
public:
//    int camera_number;
//    mCamParam cam_param[CAM_NUM_MAX];
//    mCamDetectParam det_param[CAM_NUM_MAX];
//    mDetectDeviceConfig dev_cfg;
      ds dev_struct[16];
      int dev_no;
      QList <m_road> roads;
//    static int init_flag;
//    static   DataManager *dm_ret;
//    static DataManager *get_instance(int total_cam_no)
//    {
//        if(DataManager::init_flag==0)
//            dm_ret=new DataManager(total_cam_no);

//        init_flag=1;
//        return dm_ret;
//    }

    static DataManager &get_instance(int dev_num=0,int cam_num=0)
    {
        static DataManager dm(dev_num,cam_num);
        return dm;
    }

    bool read_file()
    {
        bool ret;

        for(int var=0;var<dev_no;var++){
            ret=Database::get_mDetectDeviceConfig(var,0,dev_struct[var].dev_cfg);
            if(ret==false)
                return false;
            for(int i=0;i<dev_struct[var].camera_number;i++)
            {
                ret=Database::get_mCamParam(var,i,dev_struct[var].cam_param[i]);
                if(ret==false)
                    return false;
                else
                    qDebug()<<"read"<<i<<"ok";
                ret=Database::get_mCamDetectParam(var,i,dev_struct[var].det_param[i]);
                if(ret==false)
                    return false;
                else
                    qDebug()<<"read"<<i<<"ok";
            }
        }
        return ret;
    }
    void wirte_file()
    {

        for(int var=0;var<dev_no;var++){
            Database::set_mDetectDeviceConfig(var,0,dev_struct[var].dev_cfg);
            for(int i=0;i<dev_struct[var].camera_number;i++)
            {
                Database::set_mCamParam(var,i,dev_struct[var].cam_param[i]);
                Database::set_mCamDetectParam(var,i,dev_struct[var].det_param[i]);
            }
        }
    }

signals:

public slots:
private:

    DataManager(int dev_no,int cam_no,QObject *parent = 0);


};

#endif // DATAMANAGER_H
