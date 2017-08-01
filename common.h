#ifndef COMMON_H
#define COMMON_H

#ifndef PUBLIC_H
#define PUBLIC_H
#include <iostream>
#include <cstring>
#include <ctime>
#include <stdio.h>
#define PATH_LEN 100
//#define FILE_NAME_LEN 100
#define IP_LEN 16
#define DATA_MAX 300000
#define VIDEO_WIDTH 640
#define VIDEO_HEIGHT 480
typedef unsigned char  ui8;
using namespace std;
class Tools{
public:
    static void prtinfo(ui8 *str){
        cout<<str;
        fflush(stdout);
    }
};

#define BUFSIZE 200
inline void add_title(char *label,char *str,int line,char *src_file)
{
    char tmp_str[BUFSIZE]={};
    char time_label[BUFSIZE]={};
    char title_label[BUFSIZE]={};
    char line_label[BUFSIZE]={};

    struct tm *p_tm;
    time_t timer;
    /* gets time of day */
    timer = time(NULL);
    /* converts date/time to a structure */
    p_tm = localtime(&timer);
    sprintf(time_label, "[%d:%d:%d]", p_tm->tm_hour,p_tm->tm_min,p_tm->tm_sec);
    sprintf(title_label, "[%s]", label);
    sprintf(line_label, "(%s:%d)====>", src_file,line);
//	if(strcmp(label,"cam_state")==0){
//		print_stacktrace();
//	}
#if defined( LOG_NONE)
    if(strcmp(label,"info---1")==0\
            ||strcmp(label,"err--1")==0 \
            ||strcmp(label,"exit--1")==0 \
            ||strcmp(label,"net---1")==0 \
            ||strcmp(label,"in_loop---1")==0 \
            ||strcmp(label,"config_change---1")==0 \
            ||strcmp(label,"stack")==0 \
            ||strcmp(label,"config---1")==0 \
            ||strcmp(label,"cam_info---1")==0 \
            ||strcmp(label,"check_setting--1")==0 \
            ||strcmp(label,"check_client_cmd--1")==0 \
            ||strcmp(label,"cam_state--1")==0 \
            ||strcmp(label,"sig_state--1")==0 \
            ||strcmp(label,"alg---1")==0 \
            ||strcmp(label,"clients_msg---1")==0 \
            ||strcmp(label,"camera_msg---1")==0 \
            ||strcmp(label,"debug_sig----1")==0 )
#elif defined( LOG_LEVEL1)
        if(strcmp(label,"info---1")==0\
                ||strcmp(label,"err")==0 \
                ||strcmp(label,"exit")==0 \
                ||strcmp(label,"net---1")==0 \
                ||strcmp(label,"in_loop---1")==0 \
                ||strcmp(label,"config_change---1")==0 \
                ||strcmp(label,"stack")==0 \
                ||strcmp(label,"config---1")==0 \
                ||strcmp(label,"cam_info---1")==0 \
                ||strcmp(label,"check_setting--1")==0 \
                ||strcmp(label,"check_client_cmd--1")==0 \
                ||strcmp(label,"cam_state--1")==0 \
                ||strcmp(label,"sig_state--1")==0 \
                ||strcmp(label,"alg---1")==0 \
                ||strcmp(label,"clients_msg")==0 \
                ||strcmp(label,"camera_msg")==0 \
                ||strcmp(label,"debug_sig----1")==0 )
#elif defined( LOG_LEVEL2)
        if(strcmp(label,"info")==0\
                ||strcmp(label,"err")==0 \
                ||strcmp(label,"exit")==0 \
                ||strcmp(label,"net")==0 \
                ||strcmp(label,"in_loop---1")==0 \
                ||strcmp(label,"config_change---1")==0 \
                ||strcmp(label,"stack")==0 \
                ||strcmp(label,"config---1")==0 \
                ||strcmp(label,"cam_info---1")==0 \
                ||strcmp(label,"check_setting--1")==0 \
                ||strcmp(label,"check_client_cmd--1")==0 \
                ||strcmp(label,"cam_state--1")==0 \
                ||strcmp(label,"sig_state--1")==0 \
                ||strcmp(label,"server")==0 \
                        ||strcmp(label,"alg---1")==0 \
                ||strcmp(label,"clients_msg")==0 \
                ||strcmp(label,"camera_msg")==0 \
                ||strcmp(label,"debug_sig")==0 )
#else defined( LOG_LEVEL3)
        if(strcmp(label,"info")==0\
                ||strcmp(label,"err")==0 \
                ||strcmp(label,"exit")==0 \
                ||strcmp(label,"net---1")==0 \
                ||strcmp(label,"in_loop---1")==0 \
                ||strcmp(label,"config_change---1")==0 \
                ||strcmp(label,"stack")==0 \
                ||strcmp(label,"config---1")==0 \
                ||strcmp(label,"cam_info---1")==0 \
                ||strcmp(label,"check_setting--1")==0 \
                ||strcmp(label,"check_client_cmd--1")==0 \
                ||strcmp(label,"cam_state--1")==0 \
                ||strcmp(label,"sig_state--1")==0 \
                ||strcmp(label,"alg---1")==0 \
                ||strcmp(label,"clients_msg")==0 \
                ||strcmp(label,"camera_msg")==0 \
                ||strcmp(label,"debug_sig----1")==0 )
#endif
    {
        strcpy(tmp_str,str);
        strcpy(str,time_label);
        strcat(str,title_label);
        strcat(str,line_label);
        strcat(str,tmp_str);

            strcat(str,"\n");
            if(!strcmp(label,"stack")){
         //       print_stacktrace();
            }
    }else{
        memset(str,0,BUFSIZE);
 //	sprintf(str, "ignoring unknown label [%s]\n", label);
    }

}
inline void print_str(char *str) {
    printf("%s", str);
    fflush(NULL);
}
#define prt(label,... ) {\
        char tmp_string[BUFSIZE] ;	\
        sprintf(tmp_string,__VA_ARGS__);	\
        add_title(#label,tmp_string,__LINE__,__FILE__);  	\
        print_str(tmp_string);   \
}


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

typedef struct Command {
    unsigned char version;
    unsigned char prottype;
    unsigned short objnumber;
    unsigned short objtype;
    unsigned int objlen;
} mCommand;

typedef struct {
    unsigned short x;
    unsigned short y;
} IVDPoint;

typedef struct {
    unsigned char state;
    unsigned char isCarInTail;
    unsigned short queueLength;
    unsigned int vehnum;
    //unsigned int    speed;
    unsigned short uActualDetectLength;
    unsigned short uActualTailLength;
    IVDPoint LineUp[2];
} mRealLaneInfo;

typedef struct {
    unsigned char flag;
    unsigned char laneNum;
    unsigned char curstatus;
    unsigned char fuzzyflag;
    unsigned char visibility;
    unsigned short uDegreePoint[20][2];
    //unsigned short 	uDegreePoint[4][2];
    mRealLaneInfo lane[DETECTLANENUMMAX];  //16
} mRealStaticInfo;

#if 0
typedef struct CammerControl {
    unsigned char start;
    unsigned char camdirect;
    unsigned char cammerIp[IPADDRMAX];
}mCammerControl;

typedef struct DetectDeviceConfig {
    unsigned int detectport;
    unsigned char camnum;
    unsigned char detectip[IPADDRMAX];
    unsigned char detectname[DEVNAMEMAX];
    mCammerControl camcontrol[CAMMERNUM];
}mDetectDeviceConfig;
#endif

#define CAM_CLOSED_STATUS 0
#define CAM_OPENED_STATUS 1
typedef struct caminfo {

    unsigned char camstatus;
    unsigned char camdirect;
    unsigned char cammerIp[IPADDRMAX];
} m_caminfo;

typedef struct DetectDeviceConfig {
    unsigned int deviceID;
    unsigned int detectport;
    unsigned char camnum;
    unsigned char detectip[IPADDRMAX];
    unsigned char detectname[DEVNAMEMAX];
    m_caminfo cam_info[CAM_NUM_MAX];

} mDetectDeviceConfig;
typedef struct CamAttributes {
    unsigned char direction;
    unsigned int camID;
    unsigned int cammerport;
    unsigned int adjustport;
    unsigned int signalport;
    unsigned char urlname[USERNAMEMAX];
    unsigned char username[USERNAMEMAX];
    unsigned char passwd[USERNAMEMAX];
    unsigned char cammerIp[IPADDRMAX];
    unsigned char adjustIp[IPADDRMAX];
    unsigned char signalIp[IPADDRMAX];
} mCamAttributes;
typedef struct CamDemarcateParam {
    unsigned short cam2stop;
    unsigned short camheight;
    unsigned short lannum;
    unsigned short number;
    unsigned short baselinelen;
    unsigned short farth2stop;
    unsigned short recent2stop;
} mCamDemarcateParam;
typedef struct ChannelVirtualcoil {
    unsigned short number;
    unsigned short farthCoillen;
    unsigned short recentCoillen;
} mChannelVirtualcoil;
typedef struct CamParam {
    unsigned char coilnum;
    mCamAttributes camattr;
    mCamDemarcateParam camdem;
    mChannelVirtualcoil channelcoil[DETECTLANENUMMAX];
} mCamParam;
typedef struct Point {
    unsigned short x;
    unsigned short y;
} mPoint;
typedef struct Line {
    unsigned short startx;
    unsigned short starty;
    unsigned short endx;
    unsigned short endy;
} mLine;
typedef struct RearCoil {
    mPoint Rear[COILPOINTMAX];
    mPoint Front[COILPOINTMAX];
} mChannelCoil;

typedef struct CamDetectLane
{
    unsigned char lanenum;
    mChannelCoil virtuallane[DETECTLANENUMMAX];
} mCamDetectLane;

typedef struct VirtualLaneLine {
    unsigned char lanelinenum;         //
    mLine laneline[LANELINEMAX];
} mVirtualLaneLine;

typedef struct StandardPoint {
    mPoint coordinate;
    unsigned short value;
} mStandardPoint;

typedef struct DemDetectArea {
    mPoint vircoordinate[STANDPOINT];
    mPoint realcoordinate[STANDPOINT];
} mDemDetectArea;

typedef struct DetectParam {
    unsigned short uTransFactor;
    unsigned int uGraySubThreshold;
    unsigned int uSpeedCounterChangedThreshold;
    unsigned int uSpeedCounterChangedThreshold1;
    unsigned int uSpeedCounterChangedThreshold2;
    unsigned short uDayNightJudgeMinContiuFrame;
    unsigned short uComprehensiveSens;
    unsigned short uDetectSens1;
    unsigned short uDetectSens2;
    unsigned short uStatisticsSens1;
    unsigned short uStatisticsSens2;
    unsigned short uSobelThreshold;
    unsigned short shutterMax;        // 1 2 3 4 5 6 7 8
    unsigned short shutterMin;        // 1 2 3 4 5 6 7 8
} mDetectParam;

typedef struct CamDetectParam {
    unsigned int timep[4];
    mCamDetectLane detectlane;
    mVirtualLaneLine laneline;
    mStandardPoint standpoint[STANDARDVAULEMAX];
    mDemDetectArea area;
    mDetectParam detectparam[ALGMAX];
} mCamDetectParam;


#endif // PUBLIC_H



#endif // COMMON_H
