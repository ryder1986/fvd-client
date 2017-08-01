#include "datamanager.h"

DataManager::DataManager(int dev_no,int cam_no,QObject *parent) : dev_no(dev_no),QObject(parent)
{
    for(int i=0;i<16;i++)
    {
        dev_struct[i].camera_number=cam_no;
    }
    //init_flag=0;
}

