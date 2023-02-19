#ifndef __ICE_COMDEF_H__ 
#define __ICE_COMDEF_H__ 

#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------
// The common data type, will be used in the whole project.
//----------------------------------------------

typedef unsigned char           UINT8;
typedef unsigned short          UINT16;
typedef unsigned int            UINT32;
#ifndef _WIN32
typedef unsigned long			UINT64;
#endif
typedef signed char                    INT8;

typedef short                   INT16;
typedef int                     INT32;
typedef float 					FLOAT;
#ifndef _WIN32
typedef long					INT64;
#endif

typedef void*                   ICE_HANDLE;

typedef enum {
	ICE_STATUS_NOERROR = 0,		//成功
	ICE_STATUS_INVALID_HANDLE,	//handle为空
	ICE_STATUS_INVALID_PARAM,	//参数不正确
	ICE_STATUS_INIT_FAILED,		//初始化失败
	ICE_STATUS_SEND_FAILURE,	//发送失败
	ICE_STATUS_TIMEOUT,			//请求超时，未接收到相机返回数据
	ICE_STATUS_RECV_FAILURE,	//相机操作失败
	ICE_STATUS_CONN_ERROR,		//连接信息验证失败
	ICE_STATUS_CONN_FAILED,		//连接不成功
	ICE_STATUS_ANALYSIS_ERROR,	//数据解析错误
	ICE_STATUS_FILE_NOT_EXIST,	//文件不存在
	ICE_STATUS_FILE_OPEN_ERROR,	//打开文件失败
	ICE_STATUS_FILE_NOT_COMPLIANT,//文件不符合规范
	ICE_STATUS_NOT_SUPPORT		//不支持
}E_ICE_SDK_STATUS;

#if 0
typedef enum
{
	ICE_DEVICE_OFFLINE,		//离线
	ICE_DEVICE_ONLINE,		//在线
} ICE_DEVICE_STATUS_TYPE;

typedef struct
{
	int year;		
	int month;
	int day;		
	int hour;		
	int min;		
	int sec;		
}ICE_DATE_TIME_INFO_S;

typedef struct {
	int enable;			//NTP使能
	int period;			//同步间隔，多少秒同步一次，单位秒（10-3600）
	int diff;			//同步差值条件，相机与服务器时间相差多少秒以上才同步，单位秒（大于1）
	int port;			//NTP服务器端口（0-65535）
	char serverIp[128];	//NTP服务器地址
	char resv[256];
}ICE_NTPCFG_S;

//----------------------------------------------
// 车牌识别输出结构定义
//----------------------------------------------
//! 车牌类型定义
typedef enum 
{
	ICE_PLATE_UNCERTAIN			= 0,	//!< 不确定的
	ICE_PLATE_BLUE				= 1,	//!< 蓝牌车
	ICE_PLATE_YELLOW			= 2,	//!< 单层黄牌车
	ICE_PLATE_POLICE			= 4,    //!< 警车
	ICE_PLATE_WUJING			= 8,	//!< 武警车辆
	ICE_PLATE_DBYELLOW			= 16,	//!< 双层黄牌
	ICE_PLATE_MOTOR				= 32,	//!< 摩托车
	ICE_PLATE_INSTRUCTIONCAR	= 64,	//!< 教练车
	ICE_PLATE_MILITARY			= 128,	//!< 军车
	ICE_PLATE_PERSONAL			= 256,	//!< 个性化车
	ICE_PLATE_GANGAO			= 512,	//!< 港澳车
	ICE_PLATE_EMBASSY			= 1024,			//!< 使馆车
	ICE_PLATE_NONGLARE			= 2048,			//!< 老式车牌(不反光)
	ICE_PLATE_AVIATION			= 4096,			//!< 民航车牌
	ICE_PLATE_NEWENERGY			= 8192,			//!< 新能源车牌
	ICE_PLATE_NEWENERGYBIG		= 0x00004000,	//!< 新能源车牌大车；
	ICE_PLATE_WHITE_TWOTWO		= 0x10000001,	//!< 2+2模型；
	ICE_PLATE_WHITE_TWOTHR		= 0x10000002,	//!< 2+3模型；
	ICE_PLATE_WHITE_THRTWO		= 0x10000004,	//!< 3+2模型；
	ICE_PLATE_WHITE_THRTHR		= 0x10000008,	//!< 3+3模型；
	ICE_PLATE_WHITE_THRFOR		= 0x10000010,	//!< 3+4模型；
	ICE_PLATE_BLACK_THRTWO		= 0x10000020,	//!< 3+2模型；
	ICE_PLATE_BLACK_TWOTHR		= 0x10000040,	//!< 2+3模型；
	ICE_PLATE_BLACK_THRTHR		= 0x10000080,	//!< 3+3模型；
	ICE_PLATE_BLACK_TWOFOR		= 0x10000100,	//!< 2+4模型；
	ICE_PLATE_BLACK_FORTWO		= 0x10000200,	//!< 4+2模型；
	ICE_PLATE_BLACK_THRFOR		= 0x10000400,	//!< 3+4模型；
}ICE_PLATETYPE_E;

typedef struct
{
	short s16Left;            //!< letf x
	short s16Top;             //!< top y
	short s16Right;           //!< right x
	short s16Bottom;          //!< bottom y
} ICE_RECT_S;

typedef struct 
{
	char	plateNum[128];		//车牌号，UTF-8编码
	char	plateColor[32];		//车牌颜色，UTF-8编码
	int		flasePlate;			//是否为虚假车牌
	float	confidence;			//打分值
	ICE_PLATETYPE_E	plateType;	//车牌类型
	ICE_RECT_S	stPlateRect;	//车牌矩形框
	char	resv[256];			//预留
}ICE_PLATEINFO_S;

typedef enum
{
	ICE_VDC_VEHICLE_TYPE_UNKOWN				= 0,			//!<  未知
	ICE_VDC_VEHICLE_TYPE_NORMAL_CAR			= 1,			//!<  轿车
	ICE_VDC_VEHICLE_TYPE_MINIBUS			= 2,			//!<  面包车
	ICE_VDC_VEHICLE_TYPE_BUS				= 3,			//!<  大型客车
	ICE_VDC_VEHICLE_TYPE_MEDIUMBUS			= 4,			//!<  中型客车
	ICE_VDC_VEHICLE_TYPE_PICK_UP_TRUCK		= 5,			//!<  皮卡
	ICE_VDC_VEHICLE_TYPE_NONMOTORIZED	    = 6,			//!<  非机动车
	ICE_VDC_VEHICLE_TYPE_SUV				= 7,			//!<  SUV
	ICE_VDC_VEHICLE_TYPE_MPV				= 8,			//!<  MPV
	ICE_VDC_VEHICLE_TYPE_MINITRUCK			= 9,			//!<  微型货车
	ICE_VDC_VEHICLE_TYPE_PICKUPTRUCK		= 10,			//!<  轻型货车
	ICE_VDC_VEHICLE_TYPE_MEDIUMTRUCK		= 11,			//!<  中型货车
	ICE_VDC_VEHICLE_TYPE_HEAVYTRUCK			= 12,			//!<  重型货车
}ICE_VDC_VEHICLETYPE_E;

typedef enum
{
	ICE_VCR_VEHICLE_COLOR_UNKOWN 	= -1,	 //!<  未知
	ICE_VCR_VEHICLE_COLOR_BLACK 	= 0,	 //!<  黑色
	ICE_VCR_VEHICLE_COLOR_BLUE 		= 1,	 //!<  蓝色

	ICE_VCR_VEHICLE_COLOR_GRAY 		= 2,	 //!<  灰色	
	ICE_VCR_VEHICLE_COLOR_BROWN 	= 3,	 //!<  棕色
	ICE_VCR_VEHICLE_COLOR_GREEN 	= 4,	 //!<  绿色
	ICE_VCR_VEHICLE_COLOR_NIGHTDARK	= 5,   	 //!<  夜间深色
	ICE_VCR_VEHICLE_COLOR_PURPLE	= 6,	 //!<  紫色
	ICE_VCR_VEHICLE_COLOR_RED 		= 7,	 //!<  红色
	ICE_VCR_VEHICLE_COLOR_WHITE 	= 8,	 //!<  白色
	ICE_VCR_VEHICLE_COLOR_YELLOW 	= 9,	 //!<  黄色

}ICE_VCR_VEHICLECOLOR_E;

typedef enum 
{
	ICE_VDC_VERHICLE_DIR_HEAD			 = 0,				//!<  车头方向 			
	ICE_VDC_VERHICLE_DIR_TAIL			 = 1,				//!<  车尾方向 			
	ICE_VDC_VERHICLE_DIR_HEAD_AND_TAIL	 = 2				//!<  车头和车尾方向 	
}ICE_VDC_VERHICLE_DIR_E;

typedef struct
{
	ICE_VDC_VEHICLETYPE_E	vehicleType;	//车辆类型
	ICE_VCR_VEHICLECOLOR_E	vehicleColor;	//车身颜色
	ICE_VDC_VERHICLE_DIR_E	vehicleDir;		//车辆方向
	char	logName[128];					//品牌，UTF-8编码
	char	subLogName[128];				//子品牌，UTF-8编码
	char	productYearName[32];			//生产年代
	char	resv[256];						//预留				
}ICE_VEHICLEINFO_S;

//触发类型
typedef enum
{
	ICE_VDC_VIDEO_TRIGGER, 					//视频触发
	ICE_VDC_HD_TRIGGER,						//硬触发
	ICE_VDC_SOFT_TRIGGER,					//软触发
	ICE_VDC_TRIGGER_UNKOWN,
}ICE_VDC_TRIGGER_TYPE_E;

typedef struct  
{
	ICE_PLATEINFO_S				plateInfo;		//车牌信息
	ICE_VEHICLEINFO_S			vehicleInfo;	//车辆信息
	ICE_VDC_TRIGGER_TYPE_E		triggerType;	//触发类型 
	ICE_DATE_TIME_INFO_S		capTime;		//抓拍时间
	char	resv[256];							//预留
}ICE_LPRRESULT_S;
#endif

#define MAX_LINEOSD_TEXT 256
#define MAX_PLATE_OSD_TEXT 64
#define MAX_CUSTOM_OSD_LINE_NUM 6

typedef struct T_LineTextOsd
{
	UINT32 uiTextSize;//字体大小 0大 1中 2小
	UINT32 uiTextColor;//文字颜色，RGB888，低8位表示蓝色分量，中8位表示绿色分量，高8位表示红色分量
	UINT32 uiAlignMode;//对齐方式（强制居中对齐，不再使用）
	UINT8 ucTextStr[MAX_LINEOSD_TEXT];//叠加内容，字体为小时，目前最多支持128byte；字体为中时，目前最多支持84byte;字体为大时，最多支持64byte；UTF8编码
	UINT8 ucResvr[256];//预留
}T_LineTextOsd;

typedef struct T_TextOsd
{
	T_LineTextOsd tLineTextOsd[MAX_CUSTOM_OSD_LINE_NUM];//目前最大支持2行，数组下标0表示第一行 下标1表示第二行
	UINT8 ucResvr[128];//预留
}T_TextOsd;

typedef struct T_PlateOsd
{
	UINT32 uiTextColor;//文字颜色，RGB888，低8位表示蓝色分量，中8位表示绿色分量，高8位表示红色分量
	UINT8  ucPlateStr[MAX_PLATE_OSD_TEXT];//车牌信息，目前最多支持18byte,UTF8编码
	UINT8 ucResvr[128];//预留
}T_PlateOsd;

typedef struct T_LcdParam
{
	UINT32 uiPicSwitchTime;//图片切换频率（图片显示时长），单位：秒，范围1-300
	UINT32 uiPlateShowTime;//车牌信息显示时长（主动模式有效），单位：秒，范围1-100
	UINT32 uiScreenDisplayDir;//屏幕显示方向，0 正显， 1倒显
	UINT32 uiQrCodeBgColor;//二维码背景颜色，RGB888，低8位表示蓝色分量，中8位表示绿色分量，高8位表示红色分量
	UINT8 ucResvr[120];//预留
}T_LcdParam;

typedef struct T_AdPicPlayParam
{
	UINT32 uiEnable;//0停止轮播，1开始轮播
	UINT32 uiAdPicType;//1全屏广告 2半屏广告
	UINT8 ucResvr[128];//预留
}T_AdPicPlayParam;

#if 0
typedef struct 
{
	UINT32	u32Size;							//!<  数据包长度
	UINT32	u32Type;							//!<  类型
	UINT32	u32Status;							//!<  状态
	UINT32	u32Channel;							//!<  通道号
	UINT32	u32Time;							//!<  时间
	UINT32	u32Date;							//!<  日期
	UINT32	u32Id;								//!<  标识
	UINT32	u32Level;							//!<  警报级别
} ICE_OPER_DATA_S;

typedef struct
{
	char	id[64];
} Dev_ID;

typedef struct
{
	unsigned char ucUID[32];
	unsigned char ucReserved[32];
}T_UidParam;

typedef struct
{
	int InVolume; //0- 10
	int OutVolume;//0- 10
	int as32Reserved[4]; //预留参数
} T_TalkBackVolumeParam;
#endif

typedef struct  
{
	UINT32 uiTextType;		//文字行显示类型，0表示车牌专用区域+2行自定义内容类型，1表示4行定义内容类型
	T_PlateOsd tPlateOsd;	//车牌专用区域的车牌文字信息
	T_TextOsd tTextOsd;		//自定义行文字信息（文字行显示类型为0时，取前2行自定义内容；文字行显示类型为1时，取前4行自定义内容）
	UINT8 ucResvr[256];//预留
}T_LcdShowInfo;

typedef struct  
{
	UINT32 uiLightLevel;//亮度等级，范围1-5
	UINT32 uiScrollSpeed;//滚动速度，范围1-3；1-慢，2-中，3-快
	UINT32 uiLineMode;//接线模式，范围0-1；0-2线，1-1线
	UINT32 uiScanNums; //扫描模式，范围0-1；0-32扫，1-16扫
	UINT32 uiScreenDir;//屏显方向，范围0-1；0-横屏，1-竖屏
	UINT32 uiScreenMode;//屏模式，范围0-1；0-单屏，1-双屏
	UINT32 uiVolume;//音量，范围0-10,0为静音
	UINT32 uiVoiceSpeed;//语速（预留，暂不支持）
	UINT32 uiVoiceType;//声音类型（预留，暂不支持）
	UINT8 ucResvr[244];//预留
}T_LedCfgInfo;

typedef struct  
{
	UINT8 ucLineText[MAX_LINEOSD_TEXT];//自定义显示文字，目前长度最大120字节，utf8编码
	UINT32 uiColor;//文字颜色，范围0-2；0-红色，1-绿色，2-黄色
	UINT8 ucResvr[256];//预留
}T_LedLineInfo;

typedef struct
{
	UINT32 uiSetQRCodeUrl;//是否设置二维码url，范围0-1
	UINT8 ucUrl[MAX_LINEOSD_TEXT];//二维码url，目前长度最大180字节，utf8编码
	UINT32 uiColor;//文字颜色，范围0-2；0-红色，1-绿色，2-黄色
	UINT8 ucResvr[256];//预留
}T_QRCodeInfo;

#define MAX_LED_LINE_NUM 8
typedef struct  
{
	T_LedLineInfo tLedLineInfo[MAX_LED_LINE_NUM];//自定义行文字信息，目前最大支持4行
	T_QRCodeInfo tQrCodeInfo;//二维码图片信息
	UINT8 ucResvr[256];//预留
}T_LedShowInfo;

#ifdef __cplusplus
}
#endif
#endif