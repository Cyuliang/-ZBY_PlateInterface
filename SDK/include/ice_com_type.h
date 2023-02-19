/*! \file ice_com_type.h
\brief ice_com_type.h document.
*/
#ifndef _ICE_COM_TYPE_H_
#define _ICE_COM_TYPE_H_

#include "ice_base_type.h"

//! \defgroup group_communication 通信协议
//!  通信协议数据类型
//! \{
//! \}

#ifdef __cplusplus
extern "C"
{
#endif


#define ICE_BUF_SIZE_CONTROL	(64-32)
#define ICE_BUF_SIZE_EVENT		(64-32)
#define ICE_BUF_SIZE_VPRO		(16*1024-32)
#define ICE_BUF_SIZE_CONFIG		(128*1024-32)

#define ICE_BUFLEN_PACKET	(1024*512)

#define ICE_EVENT_ID_SLAVE_MIN	0x00000000
#define ICE_EVENT_ID_SLAVE_MAX	0xFFFFFFFF

#define ICE_BUF_SIZE_FRAME		(1920*1080*2 + 128)

typedef struct 
{
	int enable;   //0 光敏, 1 图像 default 1   
	int defalut_state;    //0 off ,1 on, default 1
	int dayJudgeCnt;   //100 cnt
	int nightJudgeCnt;    //10 cnt
	int day_to_night_delay;  // 5s
	int night_to_day_delay; // 90s
	int photosensitive_day_limit;  //75
	int photosensitive_night_limit; //40
	int  reserved[5];
} ISP_light_switch_param;


//! \ingroup group_communication
//! 状态码
typedef enum
{
	ICE_STATUS_SUCCESS				= 0x00000000,		//!<  成功
	ICE_STATUS_COMMAND				= 0x00010000,		//!<  命令
	ICE_STATUS_ERROR2				= 0x00080000,		//!<  错误
	ICE_STATUS_ERROR_NOT_FOUND		= 0x00080001,		//!<  没有查找到
	ICE_STATUS_ERROR_NOT_SUPPORTED	= 0x00080002,		//!<  不支持
} ICE_COM_STATUS_E;

//! \ingroup group_communication
//! 操作通用数据
typedef struct 
{
	ICE_U32	u32Size;							//!<  数据包长度
	ICE_U32	u32Type;							//!<  类型
	ICE_U32	u32Status;							//!<  状态
	ICE_U32	u32Channel;							//!<  通道号
	ICE_U32	u32Time;							//!<  时间
	ICE_U32	u32Date;							//!<  日期
	ICE_U32	u32Id;								//!<  标识
	ICE_U32	u32Level;							//!<  警报级别
} ICE_OPER_DATA_S;

///////////////////////////////////////////////////////////////////////////////////////////////////
// 控制相关数据类型

// 语音播报
typedef struct
{
	char filename[128];		//语音播报的文件名，.g711a
	int index;				//成组播放语音的索引

	char reserved[124];
	
} Broadcast_Param;

typedef struct
{
	unsigned char idle_state;
	unsigned int delay_time;
	
} relay_output;


typedef struct
{
	unsigned int IPaddr;
	unsigned int netmaskAddr;
	unsigned int gatewayAddr;
}NET_BASE_PARAM;

typedef enum
{
	ICE_NET_CONN_STAT_PC_SDK_OFFLINE = 0x00,
	ICE_NET_CONN_STAT_PC_SDK_ONLINE = 0x01,
	ICE_NET_CONN_STAT_BOARD_SDK_OFFLINE = 0x02,
	ICE_NET_CONN_STAT_BOARD_SDK_ONLINE = 0x03,
	ICE_NET_CONN_STAT_UNKNOW
}ICE_NET_CONN_STAT_TYPE_E;

typedef struct 
{
	ICE_NET_CONN_STAT_TYPE_E eNetStat;
	ICE_S32	s32Reserved[8];
}ICE_NET_CONN_STAT_S;

//! \ingroup group_communication
//! 控制类数据类型
typedef enum
{		
	ICE_CONTROL_TYPE_BASE 						= 0x1000,			//!< 控制基础字段
	ICE_CONTROL_TYPE_VDR_ARM					= 0x1001,			//!< 启动警戒
	ICE_CONTROL_TYPE_VDR_ARM_RSP				= 0x1002,			//!< 启动警戒应答
	ICE_CONTROL_TYPE_VDR_DISARM					= 0x1003,			//!< 解除警戒
	ICE_CONTROL_TYPE_VDR_DISARM_RSP			    = 0x1004,			//!< 解除警戒应答
	ICE_CONTROL_TYPE_VDR_CLEAR_ALARAM			= 0x1005,			//!< 清除警报
	ICE_CONTROL_TYPE_VDR_CLEAR_ALARAM_RSP     	= 0x1006,			//!< 清除警报应答
	ICE_CONTROL_TYPE_VDR_REQUEST_ALARM_DATA		= 0x1007,			//!< 请求报警数据
	ICE_CONTROL_TYPE_VDR_REQUEST_ALARM_DATA_RSP = 0x1008,			//!< 请求报警数据应答	
	ICE_CONTROL_TYPE_STREAM_CONNECT			    = 0x1010,			//!< 请求视频连接
	ICE_CONTROL_TYPE_STREAM_CONNECT_RSP     	= 0x1011,			//!< 请求视频连接应答
	ICE_CONTROL_TYPE_STREAM_DISCONNECT			= 0x1012,			//!< 断开视频连接
	ICE_CONTROL_TYPE_STREAM_DISCONNECT_RSP     	= 0x1013,			//!< 断开视频连接应答
	ICE_CONTROL_TYPE_RESTART					= 0x1020,			//!< 重启设备
	ICE_CONTROL_TYPE_RESTART_RSP     			= 0x1021,			//!< 重启设备应答	
	ICE_CONTROL_TYPE_HEART_BEAT					= 0x1022,			//!< 设备心跳
	ICE_CONTROL_TYPE_HEART_BEAT_RSP     		= 0x1023,			//!< 设备心跳应答	
	ICE_CONTROL_TYPE_ERROR_REPORT				= 0x1024,			//!< 设备错误上报
	ICE_CONTROL_TYPE_ERROR_REPORT_RSP     		= 0x1025,			//!< 设备错误上报应答	
	ICE_CONTROL_TYPE_REQUEST_COUNT				= 0x1026,			//!< 请求计数统计结果
	ICE_CONTROL_TYPE_REQUEST_COUNT_RSP     		= 0x1027,			//!< 请求计数统计结果应答
	ICE_CONTROL_TYPE_TALK_DATA					= 0x1028,			//!< 语音对讲
	ICE_CONTROL_TYPE_TALK_BEGIN					= 0x1029,			//!< 语音对讲开始
	ICE_CONTROL_TYPE_TALK_END					= 0x1030,			//!< 语音对讲结束
	ICE_CONTROL_TYPE_SDCARD_FORMAT              = 0x1031,           //!<sd卡格式化	
	ICE_CONTROL_TYPE_SDCARD_FORMAT_RSP          = 0x1032,           //!<sd卡格式化应答	
	ICE_CONTROL_TYPE_CAPTURE					= 0x1033,           //!< 抓拍（不做车牌识别）
	ICE_CONTROL_TYPE_CAPTURE_RSP				= 0x1034,           //!< 抓拍（不做车牌识别）应答
	ICE_CONTROL_TYPE_SDCARD_UNLOAD				= 0x1035,			//!< SD卡卸载
	ICE_CONTROL_TYPE_SDCARD_UNLOAD_RSP			= 0x1036,			//!<SD 卡卸载应答
	
	ICE_CONTROL_TYPE_TRANS_SERIAL_PORT			= 0x1037,           //!< 透传串口数据请求
	ICE_CONTROL_TYPE_TRANS_SERIAL_PORT_RSP		= 0x1038,           //!< 透传串口数据请求应答
	
	ICE_CONTROL_TYPE_BROADCSAT					= 0x1039,           //!< 语音播报请求
	ICE_CONTROL_TYPE_BROADCSAT_RSP				= 0x1040,           //!< 语音播报请求应答
	
	ICE_CONTROL_TYPE_BROADCSAT_WAV				= 0x104A,			//!< wav语音播报请求
	ICE_CONTROL_TYPE_BROADCSAT_WAV_RSP			= 0x104B,			//!< wav语音播报请求应答

	ICE_CONTROL_TYPE_VDR_REQUEST_ALARM_DATA_PASSWD		= 0x1041,			//!< 请求报警数据（带密码）
	ICE_CONTROL_TYPE_VDR_REQUEST_ALARM_DATA_PASSWD_RSP	= 0x1042,			//!< 请求报警数据（带密码）应答	
	
	ICE_CONTROL_TYPE_TRANS_SERIAL_PORT_RS232			= 0x1043,           //!< 透传串口数据请求
	ICE_CONTROL_TYPE_TRANS_SERIAL_PORT_RS232_RSP		= 0x1044,           //!< 透传串口数据请求应答
	
	ICE_CONTROL_TYPE_GET_IO_IN_STATE							= 0x1045,		//!<IO 输入状态获取请求
	ICE_CONTROL_TYPE_GET_IO_IN_STATE_RSP					= 0x1046,			//!<IO 输入状态获取请求应答

	ICE_CONTROL_TYPE_VDR_REQUEST_ALARM_DATA_NO_PIC	= 0x1047,			//!< 请求报警数据(无图片数据)
	ICE_CONTROL_TYPE_VDR_REQUEST_ALARM_DATA_NO_PIC_RSP = 0x1048,			//!< 请求报警数据应答(无图片数据)	

	ICE_CONTROL_TYPE_VDR_REQUEST_ALARM_DATA_NO_PIC_PASSWD = 0x1049,			//!< 请求报警数据(无图片数据)
	ICE_CONTROL_TYPE_VDR_REQUEST_ALARM_DATA_NO_PIC_PASSWD_RSP = 0x1050,			//!< 请求报警数据应答(无图片数据)
	ICE_CONTROL_TYPE_GET_CAMERA_HARDWARE_INFO	= 0x1051,			//!< 请求相机硬件信息
	ICE_CONTROL_TYPE_GET_CAMERA_HARDWARE_INFO_RSP = 0x1052,			//!< 请求相机硬件信息应答
	
	ICE_CONTROL_TYPE_GET_CAMERA_SOFTWARE_INFO	= 0x1053,			//!< 请求相机软件信息
	ICE_CONTROL_TYPE_GET_CAMERA_SOFTWARE_INFO_RSP = 0x1054,			//!< 请求相机软件信息应答

	ICE_CONTROL_TYPE_SDCARD_FORMAT_ONLY              = 0x1055,           //!<sd卡格式化不分区	
	ICE_CONTROL_TYPE_SDCARD_FORMAT_ONLY_RSP          = 0x1056,           //!<sd卡格式化应答	不分区

	ICE_CONTROL_TYPE_GET_OFFLINE_STATE_INFO	= 0x1057,			//!< 获取相机脱机信息
	ICE_CONTROL_TYPE_GET_OFFLINE_STATE_INFO_RSP	= 0x1058,		//!< 获取相机脱机信息应答

	ICE_CONTROL_TYPE_GET_CAMERA_INFO_JSON	= 0x1059,			//!< 获取相机脱机信息
	ICE_CONTROL_TYPE_GET_CAMERA_INFO_JSON_RSP	= 0x105a,		//!< 获取相机脱机信息应答

	ICE_CONTROL_TYPE_TALK_REFUSE = 0x105b,							//!< 管理终端拒绝接听对讲
	ICE_CONTROL_TYPE_TALK_REFUSE_RSP = 0x105c,						//!< 管理终端拒绝接听对讲应答

	ICE_CONTROL_TYPE_TALK_IGNORE = 0x105d,       //!< 管理终端忽略接听对讲
	ICE_CONTROL_TYPE_TALK_IGNORE_RSP = 0x105e,      //!< 管理终端忽略接听对讲应答

	ICE_CONTROL_TYPE_WJ_ETC_CHARGE = 0x105F,       //!< ETC 扣费请求
	ICE_CONTROL_TYPE_WJ_ETC_CHARGE_RSP = 0x1060,      //!< ETC 扣费请求应答

	ICE_CONTROL_TYPE_END						= 0x106F,		
} ICE_CONTROL_TYPE_E;


//! 控制类数据缓存
typedef union 
{
	ICE_U8 au8Buffer[ICE_BUF_SIZE_CONTROL];
} ICE_CONTROL_DATA_INTERNAL_U;

//! \ingroup group_communication
//! 控制类数据头和数据缓存
typedef struct 
{
	ICE_OPER_DATA_S stHead;						
	ICE_CONTROL_DATA_INTERNAL_U unData;			
} ICE_CONTROL_DATA_S;

//!获取相机硬件信息
typedef struct
{
	ICE_U32 u32FlashSize;
	ICE_U32 u32AlpuIcType;
	ICE_U32 reserved[14];

} ICE_CAMERA_HW_INFO_S;

// 控制操作相关数据类型
///////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////
// 事件相关数据类型

//! \ingroup group_communication
//! 事件数据类型
typedef enum
{
	ICE_EVENT_TYPE_BASE			= 0x2000,		//!< 事件基础字段
	ICE_EVENT_TYPE_DTCA_EVENT	= 0x2001,		//!< 周界事件集合
	ICE_EVENT_TYPE_VLPR_EVENT	= 0x2002,		//!< 卡口事件集合
	ICE_EVENT_TYPE_FAST_VLPR_EVENT	= 0x2003,        //!< 车牌识别快速事件
    ICE_EVENT_TYPE_SFDV_EVENT	= 0x2004,		//!< 行车事件集合
	ICE_EVENT_TYPE_VLPREXT_EVENT	= 0x2005,	//!< 车牌扩展事件集合
	ICE_EVENT_TYPE_HCNT_EVENT	= 0x2006,		//!< 人数事件集合
	ICE_EVENT_TYPE_IPG_EVENT	= 0x2007,		//!< 车位事件集合
	ICE_EVENT_TYPE_VLPR_CFG_NOTIFY_EVENT = 0x20fd,	//!< 卡口事件配置变化通知事件
	ICE_EVENT_TYPE_IO_EVENT     = 0x20fe,		//!< 透明IO状态回调
	ICE_EVENT_TYPE_RS232_EVENT	= 0x20ff,		//!< 透明串口(rs232)回传数据
	ICE_EVENT_TYPE_RS485_EVENT	= 0x2100,		//!< 透明串口(rs485)回传数据
	ICE_EVENT_TYPE_IO_EVENT_EXPIRED     = 0x2101,		//!< 透明IO状态回调!!存在兼容性问题需要移除，SDK目前使用rtsp接收
	TYPE_TALK_STATE				= 0x2102,//对讲状态
	ICE_EVENT_TYPE_REMCTRL_EVENT = 0x2103,//遥控器事件
	ICE_EVENT_TYPE_END			= 0x2104,		
} ICE_EVENT_TYPE_E;




//! 事件数据缓存
typedef union 
{
	ICE_U8 au8Buffer[ICE_BUF_SIZE_EVENT];			//!< 事件数据缓存
} ICE_EVENT_DATA_INTERNAL_U;

//! \ingroup group_communication
//! 事件数据头和数据缓存
typedef struct 
{
	ICE_OPER_DATA_S stHead;							//!< 操作头
	ICE_EVENT_DATA_INTERNAL_U unData;				//!< 事件数据
} ICE_EVENT_DATA_S;

// 事件相关数据类型
///////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////
// 视频处理相关数据类型

//! \ingroup group_communication
//! 目标处理数据类型
typedef enum
{
	ICE_VPRO_TYPE_BASE 				= 0x3000,		//!< 目标数据基础字段
	ICE_VPRO_TYPE_DTCA_TARGET_SET	= 0x3001,		//!< 周界算法目标
	ICE_VPRO_TYPE_VLPR_TARGET_SET	= 0x3002,		//!< 卡口算法目标
	ICE_VPRO_TYPE_SFDV_TARGET_SET	= 0x3004,		//!< 行车算法目标
	ICE_VPRO_TYPE_SNAP				= 0x3100,		//!< 抓拍数据
	ICE_VPRO_TYPE_END				= 0x3101,		
} ICE_VPRO_TYPE_E;


//! 目标处理数据缓存
typedef union 
{
	ICE_U8 au8Buffer[ICE_BUF_SIZE_VPRO];			//!< 目标数据缓存
} ICE_VPRO_DATA_INTERNAL_U;

//! \ingroup group_communication
//! 目标处理数据头和数据缓存
typedef struct 
{
	ICE_OPER_DATA_S stHead;							//!< 操作头
	ICE_VPRO_DATA_INTERNAL_U unData;				//!< 目标数据
} ICE_VPRO_DATA_S;

// 视频处理相关数据类型
///////////////////////////////////////////////////////////////////////////////////////////////////


//! \ingroup group_communication
//! 算法配置相关数据类型
typedef enum
{
	ICE_ALGO_CONFIG_TYPE_BASE 						= 0x4000,		//!< 算法配置类型基础字段

	ICE_ALGO_CONFIG_TYPE_SET_AGLO_MODULE			= 0x4001,		//!< 设置算法模块
	ICE_ALGO_CONFIG_TYPE_SET_AGLO_MODULE_RSP		= 0x4002,		//!< 设置算法模块应答	
	ICE_ALGO_CONFIG_TYPE_GET_AGLO_MODULE			= 0x4003,		//!< 获取算法模块
	ICE_ALGO_CONFIG_TYPE_GET_AGLO_MODULE_RSP		= 0x4004,		//!< 获取算法模块应答

	ICE_ALGO_CONFIG_TYPE_SET_VIDEO_SOURCE_MODE		= 0x4100,		//!< 设置视频输入制式
	ICE_ALGO_CONFIG_TYPE_SET_VIDEO_SOURCE_MODE_RSP	= 0x4101,		//!< 设置视频输入制式应答
	
	ICE_ALGO_CONFIG_TYPE_GET_VIDEO_SOURCE_MODE		= 0x4102,		//!< 获取视频输入制式
	ICE_ALGO_CONFIG_TYPE_GET_VIDEO_SOURCE_MODE_RSP	= 0x4103,		//!< 获取视频输入制式应答
	

	ICE_ALGO_CONFIG_TYPE_SET_DTCA_ALGO_LIB_INFO		= 0x4200,		//!< 设置周界算法库信息(功能码 )
	ICE_ALGO_CONFIG_TYPE_SET_DTCA_ALGO_LIB_INFO_RSP	= 0x4201,		//!< 设置周界算法库信息应答	
	ICE_ALGO_CONFIG_TYPE_GET_DTCA_ALGO_LIB_INFO		= 0x4202,		//!< 获取周界算法库信息（功能码、版本号、最大输出目标能力等）
	ICE_ALGO_CONFIG_TYPE_GET_DTCA_ALGO_LIB_INFO_RSP	= 0x4203,		//!< 获取周界算法库信息应答
	
	ICE_ALGO_CONFIG_TYPE_SET_VLPR_ALGO_LIB_INFO		= 0x4204,		//!< 设置卡口算法库信息(功能码 )
	ICE_ALGO_CONFIG_TYPE_SET_VLPR_ALGO_LIB_INFO_RSP	= 0x4205,		//!< 设置卡口算法库信息应答	
	ICE_ALGO_CONFIG_TYPE_GET_VLPR_ALGO_LIB_INFO		= 0x4206,		//!< 获取卡口算法库信息（功能码、版本号、最大输出目标能力等）
	ICE_ALGO_CONFIG_TYPE_GET_VLPR_ALGO_LIB_INFO_RSP	= 0x4207,		//!< 获取卡口算法库信息应答
	
	ICE_ALGO_CONFIG_TYPE_SET_SFDV_ALGO_LIB_INFO		= 0x4208,		//!< 设置行车算法库信息(功能码 )
	ICE_ALGO_CONFIG_TYPE_SET_SFDV_ALGO_LIB_INFO_RSP	= 0x4209,		//!< 设置行车算法库信息应答	
	ICE_ALGO_CONFIG_TYPE_GET_SFDV_ALGO_LIB_INFO		= 0x4210,		//!< 获取行车算法库信息（功能码、版本号、最大输出目标能力等）
	ICE_ALGO_CONFIG_TYPE_GET_SFDV_ALGO_LIB_INFO_RSP	= 0x4211,		//!< 获取行车算法库信息应答
	
	ICE_ALGO_CONFIG_TYPE_SET_ITSE_ALGO_LIB_INFO		= 0x4212,		//!< 设置交通事件算法库信息(功能码 )
	ICE_ALGO_CONFIG_TYPE_SET_ITSE_ALGO_LIB_INFO_RSP	= 0x4213,		//!< 设置交通事件算法库信息应答	
	ICE_ALGO_CONFIG_TYPE_GET_ITSE_ALGO_LIB_INFO		= 0x4214,		//!< 获取交通事件算法库信息（功能码、版本号、最大输出目标能力等）
	ICE_ALGO_CONFIG_TYPE_GET_ITSE_ALGO_LIB_INFO_RSP	= 0x4215,		//!< 获取交通事件算法库信息应答

	ICE_ALGO_CONFIG_TYPE_SET_DTCA_RULE_PARAM		= 0x4300,		//!< 设置周界算法分析规则
	ICE_ALGO_CONFIG_TYPE_SET_DTCA_RULE_PARAM_RSP	= 0x4301,		//!< 设置周界算法分析规则应答
	ICE_ALGO_CONFIG_TYPE_GET_DTCA_RULE_PARAM		= 0x4302, 		//!< 获取周界算法分析规则
	ICE_ALGO_CONFIG_TYPE_GET_DTCA_RULE_PARAM_RSP	= 0x4303, 		//!< 获取周界算法分析规则应答
	
	ICE_ALGO_CONFIG_TYPE_SET_VLPR_RULE_PARAM		= 0x4304,		//!< 设置卡口算法分析规则
	ICE_ALGO_CONFIG_TYPE_SET_VLPR_RULE_PARAM_RSP	= 0x4305,		//!< 设置卡口算法分析规则应答
	ICE_ALGO_CONFIG_TYPE_GET_VLPR_RULE_PARAM		= 0x4305,		//!< 获取卡口算法分析规则
	ICE_ALGO_CONFIG_TYPE_GET_VLPR_RULE_PARAM_RSP	= 0x4306,		//!< 获取卡口算法分析规则应答
	
	ICE_ALGO_CONFIG_TYPE_SET_SFDV_RULE_PARAM		= 0x4307,		//!< 设置行车算法分析规则
	ICE_ALGO_CONFIG_TYPE_SET_SFDV_RULE_PARAM_RSP	= 0x4308,		//!< 设置行车算法分析规则应答
	ICE_ALGO_CONFIG_TYPE_GET_SFDV_RULE_PARAM		= 0x4309, 		//!< 获取行车算法分析规则
	ICE_ALGO_CONFIG_TYPE_GET_SFDV_RULE_PARAM_RSP	= 0x4310, 		//!< 获取行车算法分析规则应答
	
	ICE_ALGO_CONFIG_TYPE_SET_HCNT_RULE_PARAM		= 0x4311,		//!< 设置计数算法分析规则
	ICE_ALGO_CONFIG_TYPE_SET_HCNT_RULE_PARAM_RSP	= 0x4312,		//!< 设置计数算法分析规则应答
	ICE_ALGO_CONFIG_TYPE_GET_HCNT_RULE_PARAM		= 0x4313, 		//!< 获取计数算法分析规则
	ICE_ALGO_CONFIG_TYPE_GET_HCNT_RULE_PARAM_RSP	= 0x4314, 		//!< 获取计数算法分析规则应答
	
	ICE_ALGO_CONFIG_TYPE_END						= 0x4315,		
} ICE_ALGO_CONFIG_TYPE_E;

///////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct __NET_ONVIF_CONFIG{
	ICE_U32 version;  //当前版本1
	ICE_U32 enable;  //onvif是否使能0 关闭 1开启 默认关闭
	ICE_U8 aucReserved[128]; // 保留字节
}NET_ONVIF_CONFIG;

typedef struct
{
	ICE_U32 u32Expline;			//手动曝光时间
	ICE_S32 s32AGain;			//手动模拟增益
	ICE_S32 s32DGain;			//手动数字增益

	ICE_U32 u32Mode;			//模式：0自动，1定时，2手动

	ICE_U32 u32DayBegin;		//白天开始时间（分钟为单位，例如8点为480）
	ICE_U32 u32DayEnd;			//白天结束时间（分钟为单位，例如18点为1080）
	ICE_U32 u32DayExplineMin;	//白天最小曝光时间（0-40000）
	ICE_U32 u32DayExplineMax;	//白天最大曝光时间（0-40000）
	ICE_S32 s32DayAGainMin;		//白天最小模拟增益（1-16）
	ICE_S32 s32DayAGainMax;		//白天最大模拟增益（1-16）
	ICE_S32 s32DayDGainMin;		//白天最小数字增益（1-4）
	ICE_S32 s32DayDGainMax;		//白天最大数字增益（1-4）

	ICE_U32 u32NightBegin;		//晚上开始时间（分钟为单位，例如20点为1200）
	ICE_U32 u32NightEnd;		//晚上结束时间（分钟为单位，例如6点为360）
	ICE_U32 u32NightExplineMin;	//晚上最小曝光时间
	ICE_U32 u32NightExplineMax;	//晚上最大曝光时间
	ICE_S32 s32NightAGainMin;	//晚上最小模拟增益
	ICE_S32 s32NightAGainMax;	//晚上最大模拟增益
	ICE_S32 s32NightDGainMin;	//晚上最小数字增益
	ICE_S32 s32NightDGainMax;	//晚上最大数字增益

	ICE_U32 u32OtherExplineMin;	//其他时间最小曝光时间
	ICE_U32 u32Focus;			//焦距
	ICE_S32 s32Height;			//安装高度
	ICE_S32 s32HeightAlgo;		//安装高度自动关联
	ICE_S32 s32Distance;		//安装距离
	ICE_S32 s32DistAlgo;		//安装距离自动关联

	ICE_U32 u32LightMode;		//补光灯模式
	ICE_U32 u32ColorMode;		//彩转黑模式

	ICE_U32 u32AlgoWidth;
	ICE_U32 u32AlgoHeight;

} ICE_ExpAttr_S;

//红外灯控制模式
typedef enum
{
	ICE_LIGHT_MODE_AUTO = 0,		//光敏自动检测
	ICE_LIGHT_MODE_BY_TIME,			//时间控制
	ICE_LIGHT_MODE_BY_TMLS,			//光敏与时间综合控制，白天是光敏，其他为时间控制
} ICE_LIGHT_MODE_TYPE_E;

typedef enum
{
	ICE_COLOR_MODE_AUTO = 0,		//光敏自动检测
	ICE_COLOR_MODE_COLOR,			//彩色
	ICE_COLOR_MODE_NOCOLOR,			//黑白
	
} ICE_COLOR_MODE_TYPE_E;


typedef enum
{
	ICE_RS485_PROTOCOL_HN = 1,		
	ICE_RS485_PROTOCOL_HL,			
	ICE_RS485_PROTOCOL_BA,			
	ICE_RS485_PROTOCOL_ICE,		
	ICE_RS485_PROTOCOL_AJS,     
	
} ICE_RS485_PROTOCOL_TYPE_E;

typedef enum
{
	ICE_HCNT_DOOR_FRONT = 0,		//前门
	ICE_HCNT_DOOR_MID,				//中门
	ICE_HCNT_DOOR_BACK				//后门
	
} ICE_HCNT_DOOR_TYPE_E;

typedef enum
{
	ICE_HCNT_LINK_SERVER_NET = 0,		//与服务器连接采用以太网模式
	ICE_HCNT_LINK_SERVER_RS485,			//与服务器连接采用人生rs485 模式
	
} ICE_HCNT_IPC_LINK_SERVER_MODE_E;

typedef enum
{
	ICE_HCNT_CLEAR_PERIOD = 0,		//周期
	ICE_HCNT_CLEAR_TRIGGER,			//外触发
	
} ICE_HCNT_CLEAR_MODE_E;

typedef enum
{
	ICE_HCNT_TRIGGER_RELAYIN = 0,		//开关量触发
	ICE_HCNT_TRIGGER_RS485,				//RS485触发
	ICE_HCNT_TRIGGER_PROGRAM,			//软件触发
	
} ICE_HCNT_TRIGGER_MODE_E;

typedef enum
{
	ICE_HCNT_RELAYIN_OFF = 0,		//闭合触发清零
	ICE_HCNT_RELAYIN_ON,			//打开触发清零
	
} ICE_HCNT_RELAYIN_MODE_E;

typedef enum
{
	ICE_HCNT_STORE_FLASH = 0,		//FLASH存储
	ICE_HCNT_STORE_SDCARD,			//SD卡存储

} ICE_HCNT_STORE_MODE;

typedef enum
{
	ICE_HCNT_COLLECT_HOUR = 0,		//小时汇总
	ICE_HCNT_COLLECT_DAY,			//天汇总

} ICE_HCNT_COLLECT_MODE;

#define MAX_HCNT_TEXT 64
typedef struct
{
	ICE_S32 s32RS485Type;
	ICE_U32 u32DoorType;
	ICE_U32 u32Railway;
	
	ICE_S8 as8ServerIP[16];
	ICE_S8 as8Username[MAX_HCNT_TEXT];
	ICE_S8 as8Password[MAX_HCNT_TEXT];
	ICE_S8 as8CameraID[MAX_HCNT_TEXT];
	ICE_U32 u32HBInterval;			//心跳周期
	
	ICE_U32 u32ClearMode;			//清零模式
	ICE_U32 u32ClearInterval;		//清零周期
	ICE_U32 u32TriggerMode;			//外触发模式
	ICE_U32 u32RelayinMode;			//开关量触发模式
	
	ICE_U32 u32DataStore;			//是否数据存储
	ICE_U32 u32StoreMode;			//数据存储模式
	ICE_U32 u32StoreSize;			//存储空间
	ICE_U32 u32StoreStat;			//是否统计存储
	ICE_U32 u32StatCollect;			//是否数据汇总
	ICE_U32 u32CollectMode;			//汇总模式
	
	ICE_U32 au32Reserved[32];

} ICE_HCNTAttr_S;


//图像里OSD位置类型

typedef enum
{
	ICE_OSD_LOCATION_LEFT_TOP = 0,	//左上
	ICE_OSD_LOCATION_RIGHT_TOP,		//右上
	ICE_OSD_LOCATION_LEFT_BOTTOM,	//左下
	ICE_OSD_LOCATION_RIGHT_BOTTOM,	//右下
	ICE_OSD_LOCATION_TOP_MID,		//上居中
	ICE_OSD_LOCATION_BOTTOM_MID,		//下居中
} ICE_OSD_LOCATION_TYPE_E;

//图像里外OSD位置类型
typedef enum
{
	ICE_OSD_LOCATION_IN_IMAGE = 0,
	ICE_OSD_LOCATION_OUT_TOP,	   //图像上方
	ICE_OSD_LOCATION_OUT_BOTTOM,   //图像下方
} ICE_OSD_BIG_LOCATION_TYPE_E;



typedef enum
{
	ICE_CAMERA_DIRECTION_NORTH = 0,	//由南向北
	ICE_CAMERA_DIRECTION_WEST,		//由东向西
	ICE_CAMERA_DIRECTION_EAST,		//由西向东
	ICE_CAMERA_DIRECTION_SOUTH		//由北向南
	
} ICE_CAMERA_DIRECTION_TYPE_E;


typedef enum
{
	ICE_OSD_FONTSIZE_SMALL= 0,	//小
	ICE_OSD_FONTSIZE_MEDIUM,		//中
	ICE_OSD_FONTSIZE_LARGE,		//大
} ICE_OSD_FONTSIZE_TYPE_E;


#define MAX_OSD_TEXT 64
#define MAX_CUSTOM_OSD_LINE_NUM 6

#define MAX_OSD_TEXT_SFM 32
#define MAX_CUSTOM_OSD_LINE_NUM_SFM 4


typedef struct
{
	//video
	ICE_U32 u32OSDLocationVideo;		//叠加位置
	ICE_U32 u32ColorVideo;				//颜色

	ICE_U32 u32DateVideo;				//是否叠加日期时间
	ICE_U32 u32License;					//是否叠加授权信息

	ICE_U32 u32CustomVideo;				//是否叠加自定义信息
	char szCustomVideo[MAX_OSD_TEXT];	//自定义信息

	//jpeg
	ICE_U32 u32OSDLocationJpeg;			//叠加位置
	ICE_U32 u32ColorJpeg;				//颜色

	ICE_U32 u32DateJpeg;				//是否叠加日期时间
	ICE_U32 u32Algo;					//是否叠加算法信息

	ICE_U32 u32DeviceID;				//是否叠加设备ID
	char szDeviceID[MAX_OSD_TEXT];		//设备ID

	ICE_U32 u32DeviceName;				//是否叠加设备名称
	char szDeviceName[MAX_OSD_TEXT];	//设备名称

	ICE_U32 u32CamreaLocation;			//是否叠加地点信息
	char szCamreaLocation[MAX_OSD_TEXT];	//地点信息

	ICE_U32 u32SubLocation;				//是否叠加子地点信息
	char szSubLocation[MAX_OSD_TEXT];	//子地点信息

	ICE_U32 u32ShowDirection;			//是否叠加相机方向
	ICE_U32 u32CameraDirection;			//相机方向

	ICE_U32 u32CustomJpeg;				//是否叠加自定义信息

	ICE_U32 u32ItemDisplayMode;             //图片信息显示模式，0，多行显示，1，单行显示,默认0
	ICE_U32 u32DateMode;                 //日期显示模式，0，xxxx/xx/xx   1，xxxx年xx月xx日，默认0
	ICE_U32 u32BgColor;                  //OSD 背景色，0背景全透明，1，背景黑色，默认0
	ICE_U32 u32FontSize;				//字体大小，0:小，1:中 2:大,默认为中，在540P 以下，中会转换为小
	ICE_U32 u32ExpandMode;				//扩张模式，0:不扩张，1:图像上扩张，2:图像下扩张
	char szCustomJpeg[MAX_OSD_TEXT - 20];	//自定义信息
	
	char szCustomVideo6[MAX_CUSTOM_OSD_LINE_NUM * MAX_OSD_TEXT];	//自定义信息
	char szCustomJpeg6[MAX_CUSTOM_OSD_LINE_NUM * MAX_OSD_TEXT];	//自定义信息

} ICE_OSDAttr_S;

typedef struct T_VideoOsdAttr 
{
	ICE_U32 u32OSDLocationVideo;		//叠加位置
	ICE_U32 u32ColorVideo;				//颜色

	ICE_U32 u32DateVideo;				//是否叠加日期时间
	ICE_U32 u32License;					//是否叠加授权信息
	ICE_U32 u32FontSize;				//字体大小，0:小，1:中 2:大,默认为中，在540P 以下，中会转换为小

	ICE_U32 u32CustomVideo;				//是否叠加自定义信息
	char szCustomVideo6[MAX_CUSTOM_OSD_LINE_NUM * MAX_OSD_TEXT];	//自定义信息
}T_VideoOsdAttr;


#define ICE_SCHED_TASK_MASK_ARM		0x00000003
#define ICE_SCHED_TASK_MASK_RELAY	0x0000000C
#define ICE_SCHED_TASK_MASK_COLOR	0x00000030

typedef enum
{
	ICE_SCHED_TASK_TYPE_ARM			= 0x00000001, 	//布防
	ICE_SCHED_TASK_TYPE_DISARM		= 0x00000002, 	//撤防
	ICE_SCHED_TASK_TYPE_RELAY_ON	= 0x00000004, 	//开关量闭合
	ICE_SCHED_TASK_TYPE_RELAY_OFF	= 0x00000008, 	//开关量打开
	ICE_SCHED_TASK_TYPE_GRAY		= 0x00000010,	//彩转黑
	ICE_SCHED_TASK_TYPE_COLOR		= 0x00000020, 	//黑转彩
	
} ICE_SCHED_TASK_TYPE_E;

typedef struct
{
	ICE_U32 u32Time;		//时间（分钟为单位，例如20点为1200）
	ICE_U32 u32Type;		//任务类型：布撤防或者开关量输出
	ICE_U32 u32TimeEnd;		//时间（分钟为单位，例如20点为1200）
	ICE_U32 u32Reserved[7];	//保留字段
	
} ICE_SCHED_TASK_S;

typedef struct
{
	ICE_U8 u8UseSnapCamera;
	ICE_U32 u32IP;
	ICE_U32 u32Delay;
	ICE_U32 u32SnapCount;
	ICE_U32 u32SnapInterval;
	ICE_U32 u32Reserved[8];
	
} ICE_SNAP_CAMERA_S;

typedef enum
{
	ICE_PHYCHN_MODE_SUB_VENC = 0,		//子码流
	ICE_PHYCHN_MODE_VO,					//vo输出
	
} ICE_PHYCHN_MODE_TYPE_E;


typedef struct
{
	ICE_U32 u32PhyChn;
	ICE_U32 u32RCMain;
	ICE_U32 u32RCSub;
	ICE_U32 u32CloseupEn; //是否输出车牌特写图像
	ICE_U32 u32Qfactor;//抓拍图片画质1~99,默认90
	ICE_U32 u32FullEn;//是否抓拍车牌全景图
	ICE_U32 u32CloseupInFullEn; //是否在全景图上叠加车牌特写图
	ICE_U16 u16Width;//抓拍分辨率 宽度
	ICE_U16 u16Height;//抓拍分辨率高度
	ICE_U32 u32PlateSize;	//车牌图放大倍数，1 2 3
	ICE_U32 u32Reserved[2];
	
} ICE_PHYCHN_CFG_S;


typedef struct
{
	ICE_U32 u32VFDRelayout;			//火焰关联开关量输出
	ICE_U32 u32DTCARelayout;		//周界关联开关量输出
	
	ICE_U32 u32Expline;			//从相机手动曝光时间
	ICE_S32 s32AGain;			//从相机手动模拟增益
	ICE_S32 s32DGain;			//从相机手动数字增益
	ICE_U32 u32Mode;			//从相机曝光模式：0完全自动，1自动，2手动
	ICE_U32 u32ExplineMin;		//从相机最小曝光时间
	ICE_U32 u32ExplineMax;		//从相机最大曝光时间
	ICE_S32 s32AGainMin;		//从相机最小模拟增益
	ICE_S32 s32AGainMax;		//从相机最大模拟增益
	ICE_S32 s32DGainMin;		//从相机最小数字增益
	ICE_S32 s32DGainMax;		//从相机最大数字增益
	
	ICE_U32 u32Reserved[1024];			//保留字段
	
} ICE_VFD_PARAM_S;


//自动曝光自调节参数
typedef struct
{
	int expARegulateEn;//是否开启曝光自调节，0关闭，1开启，默认为：1 开启
	int dayOrNightJudgeCnt; //白天判断的连续次数，一次大概一秒；默认为：10
	int lumLimitForDay; //白天亮度分界线，默认为：75
	int lumLimitForNight; //夜晚亮度分界线，默认为：65
	int maxValidBright; //车牌识别效果亮度上限，默认为：120
	int minValidBright; //车牌识别效果亮度下限，默认为：80
	int maxValidForEnvBright; //针对无牌车环境的亮度上限，默认为：110
	int minValidForEnvBright; //针对无牌车环境的亮度下限，默认为：90
	int maxExpCompensation; //曝光补偿量的最大值，默认为：160
	int minExpCompensation;//曝光补偿量的最小值，默认为：30
	int initExpCompensation;//曝光补偿值初始值，默认为：70
	int expReguateInterval;//对于正常车牌曝光补偿量的调整间隔，默认为：5
	
	int antiflickerEn;  //ISP抗闪烁是否使能 0 关闭， 1使能，默认值为：0 关闭
	int antiflickerFrequency; //ISP 抗闪频率值，当电源频率为 50Hz 时，抗闪频率值设置为 50；当电源频率为 60Hz 时，抗闪频率值设置为 60，默认为： 50HZ
	int antiflickerMode; //ISP 抗闪模式 0，1， 默认为：1
	int s32PowerFrequencyCompensation; //工频补偿

	int u32HighLightMode;    //是否为亮光环境；
	int maxExpCompensationHL; //亮光环境下，曝光补偿量的最大值，默认为：100
	int minExpCompensationHL;//亮光环境下，曝光补偿量的最小值，默认为：20
	int initExpCompensationHL;//亮光环境下，曝光补偿值初始值，默认为：56

	int as32Reserved[5]; //预留参数
}ICE_EXP_AREGULATE_PARAM;

//注：自动曝光自调节参数界面上只需要显示开启和关闭即可，ISP抗闪烁参数要暴露出来，其他参数如果需要调试，可用下载参数文件手动修改，然后再导入到相机


//HTTP post 参数：


typedef struct
{
	int httpPostEn; //是否打开http post 功能，默认关闭
	int directionFalg; //出口入口方向标志，0 入口，1 出口默认值为：0 入口
	int parkID; //停车场ID，默认为：13
	char ipStr[20]; //服务器IP地址，默认为：123.57.136.148
	int port; //服务器访问端口，默认为：80
	char domainName[44]; //服务器IP对应的域名，默认为：service.tigmall.com
	char ipStr_bak[20]; //备用服务器IP地址
	char path[64]; //路径，会结合出入口方向标志，停车场序号处理，默认为: /parking/count
	int maxSendCnt; //发送最大次数, 默认为：3
	int mode; // 2代表工作模式2 ，   1和3代表工作模式1
	int autoAlarmoutEn; //是否启用入口自动开闸,默认不启用
	int autoAlarmoutMode;//  模式1：识别成功开闸；（默认）,模式2：全部开闸；
	int snap_full;//  是否发送全景图；
	int snap_closeup;//  是否发送车牌特写图；
	int enable_baksvr; //是否启用备用服务器
	short offlinePostEn;   //是否启用断网续传 default 0 ,unable 
	short interval;  // 5~30s  
	int ssl_enable;

	char ioPostEn;
	char ioNum;
	char rsv1;
	char rsv2;
	int as32Reserved[1]; //预留参数

}ICE_HTTP_POST_PARAM;

typedef struct 
{
	int identify;  //新POST配置标记，固定字符串"POEX"
	int httpPostEn; //是否打开http post 功能，默认关闭
	int mode; //1和3代表工作模式1，其它数值代表各自模式，模式2是老POST协议，模式5是最新HXPOST V2.0协议
	int sslEn;  //SSL使能，默认不使能
	int sslPort;  //SSL端口，默认443
	int bakServerEn; //是否启用备用服务器
	int serverPostMode;  //主备服务器都有效时推送模式:0=全推送，1=主优先（主推不成功再推备）
	int serverPort; //服务器访问端口，默认为：80

	char serverIpStr[32]; //服务器IP地址，默认为：123.57.136.148
	char serverDomian[64]; //服务器域名，默认为：service.tigmall.com
	char bakServerIpStr[32]; //备用服务器IP地址，默认为：123.57.136.148
	char bakServerDomian[64]; //备用服务器域名，默认为：service.tigmall.com
	char path[64]; //路径，会结合出入口方向标志，停车场序号处理，默认为: /parking/count
	char parkIdStr[64]; //停车场ID，字符串，只支持英文、数字、-

	int maxSendCnt; //发送最大次数, 1-3，默认为:3
	int snapFull;//  是否发送全景图；
	int snapCloseup;//  是否发送车牌特写图；
	int camIdType;   //ID号，0使用相机MAC地址，1使用相机UUID
	int directionFalg; //出口入口方向标志，0=入口，1=出口，默认0
	int offlinePostEn;  //default 0,断网续传使能 -----本版本起，该使用和心跳分开，各是独立的，互不影响
	int interval;  //心跳间隔 1~30s，0表示无心跳 -----本版本起，该使用和心跳分开，各是独立的，互不影响
	int autoAlarmOutEn;  //入口自动开闸使能,默认不使能
	int autoAlarmOutMode;//入口自动开闸 模式1=识别成功开闸（默认），模式2=全部开闸，模式3=反馈开闸
	int ioInPostEn;  //输入IO状态上报使能
	char ioInNum[4];  //指定上报输入IO，真有效，ioInNum[0]对应输入IO1，ioInNum[1]=IO2,ioInNum[2]=IO3,ioInNum[3]=IO4

	char iUnderwayExt;   //是否进行扩展，0=不进行，1=进行
	char reserve[63];   //预留主参数
	int extParamSize;   //ICE_HTTP_POST_NEW_PARAM 为主参数，辅助参数全部放在后面，每个模式如有需要，均可配套辅助参数，达到不动主参数，同时又支持额外定制
}ICE_HTTP_POST_NEW_PARAM;

//模式6 辅助参数
typedef struct 
{
	char userID[32]; //用户ID
	char address[64]; //地址
}ICE_HTTP_POST_MODE6_EXT_PARAM;

//模式5 辅助参数
typedef struct ICE_HTTP_POST5_EXTPARAM
{
	char serverDomian[128]; //服务器域名
	char path[128]; //路径
	char acReserved[256];//预留
} ICE_HTTP_POST5_EXTPARAM;

#define MAX_USEABLE_UART_CNT 2  //最大可配置的串口个数

typedef enum{
	UART_PLATENUM_PROTOCOL_ONE =0,	//车牌协议1
	UART_TRANS_TRANSMIT,	//透明串口
	UART_LED_CONTROL,	//LED屏控制
	UART_MIX_MODE,		//混合模式
	UART_PLATENUM_PROTOCOL_TWO,   //车牌协议2
	UART_PLATENUM_PROTOCOL_THR,   //车牌协议3  
	UART_PLATENUM_PROTOCOL_FOUR,	 // 车牌协议4 
	UART_RS232_GETPHONEMAC     // rs232  wifi 探针协议
}ICE_UART_WORK_MODE_E;

//强制相机脱机工作参数
typedef struct {
	int force_offline_enable;
	int reserved[15];
}Force_camera_offline_cfg_param;

typedef enum
{
	LED_CARD_SERIAL_PROTOL1 = 0x00,		//led 控制卡协议1
	LED_CARD_SERIAL_PROTOL2 = 0x01,		//led 控制卡协议2
	LED_CARD_SERIAL_MAX_VALUE
}LED_CARD_SERIAL_TYPE_PROTOL;

typedef struct
{
	int uartEn;					 //串口是否使能0 不适用，1使用，默认为1使用
	int uartWorkMode;			 //串口工作模式，0:车牌协议，1:透明串口，默认为0 车牌协议
	int baudRate;				 //波特率，默认值为9600，常用波特率 1200、2400、4800、9600、19200、38400、115200
	int dataBits;				 //数据位，默认值为 8，可选值为： 5、6、7、8
	int parity;					 //校验位，默认值为 无，可选值为：无、奇校验、偶校验、标记、空格
	int stopBits;				 //停止位，默认值为 1，可选值为：1、2
	int flowControl;			 //流控模式，默认值为 无，可选值为：  无、硬件，Xon/Xoff
	int LEDControlCardType;		 //串口LED 工作模式下，控制卡的类型
	int LEDBusinessType;		 //某一种LED控制卡的业务类型，什么条件下点屏，打印哪些信息
	int u32UartProcOneReSendCnt; //车牌协议重发次数    默认值0， 取值范围[0~2]
	char screen_mode;            //屏显模式 1屏显 2透传 3道闸控制 4蓝牙控制
	char as32Reserved[7]; //预留参数
}ice_uart;


typedef struct{
	ice_uart uart_param[MAX_USEABLE_UART_CNT];//多个串口数组
	int as32Reserved[10]; //预留参数
}ICE_UART_PARAM;

//SD 卡相关参数

typedef enum{
	SDS_NO =1,	//SD卡不存在
	SDS_ERROR,	//SD卡出现错误
	SDS_ENOUGH,	//SD卡容量没有满，可用
	SDS_FULL,		//SD卡已满
	SDS_UNFORMATTED   //SD卡未格式化
}DISK_STATUS;

typedef enum{
	STORE_NO_CLIENT_CONNET =0,	//SD卡断网存储
	STORE_ALWAYS,	//SD卡实时存储
	STORE_NEVER	//SD card not store
}DISK_STORE_MODE;

typedef struct
{
	int status; //SD 卡状态，
	int totalSize; //总空间大小
	int usedSize;//已用空间大小
	int availableSize; //可用空间大小
	int SDStoreMode; //sd 存储模式，断网存储，实时存储，默认断网
	int SDFormatFlag; //sd 卡是否处于格式化中
	int SDUnloadFlag; //SD 卡正在卸载
	int SDUmountFlag;//SD 是否可以解挂，用于格式化和卸载
	int u32Reserved[6];
}SD_card_param;

#define	MAX_DISK_NAME_LEN		128	//磁盘名称最长长度
#define MAX_DISK_MOUNT_PATH_LEN	128	//磁盘Mount路径的最长长度
#define DISK_DEV_NODE_LEN			12	// EX: /dev/sda	


typedef struct
{
	int SDTotalNum;
	SD_card_param SDCard_param;
	char	MountPoint[MAX_DISK_MOUNT_PATH_LEN];	//如果有磁盘，Mount的目录名称，注意最后加上最后的"/"符号
	char	DevNode[DISK_DEV_NODE_LEN];	// EX: /dev/mmcblk0
}SD_CARD;

typedef struct
{
	int EnUserExtPartModel;
	int UserExtPartSize;
	char UserExtPartMountPath[MAX_DISK_MOUNT_PATH_LEN];
	int u32Reserved[32];
}SD_CARD_USER_EXT_CFG;

typedef struct
{
	char	id[64];

} Dev_ID;



//typedef struct
//{
//	int mode;		//0表示断网关联，1表示实时工作,2 不关联开闸或不工作
//	int match;		//白名单匹配相似，范围（60%-100%），默认：80%
//	int black_mode; //黑名单关联道闸模式，0 不关联开闸，1 开闸
//	int black_match; //黑名单匹配相似，范围（60%-100%），默认：80%
//	int temp_mode;  //临时车关联道闸模式，0 不关联开闸，1 开闸
//	char reserved[112];
//	
//} WhiteList_Param;

typedef struct
{
	int mode;  //0表示断网关联，1表示实时工作,2 不关联开闸或不工作
	int match;  //白名单匹配相似，范围（60%-100%），默认：80%
	int black_mode; //黑名单关联道闸模式，0 不关联开闸，1 开闸
	int black_match; //黑名单匹配相似，范围（60%-100%），默认：80%
	int temp_mode;  //临时车关联道闸模式，0 不关联开闸，1 开闸
	int ignoreHZ_flag;//忽略汉字标志，0 不忽略，1 忽略
	int allow_unmatch_chars_cnt;// 运行不匹配的字符个数范围【0 ~3】
	int new_version; //  new or old WhiteList flag, new:1, old:other.
	int Jing_mode;  //警车模式关联道闸模式，0 不关联开闸，1 开闸
	int Army_mode;  //军车模式关联道闸模式，0 不关联开闸，1 开闸
	int Antifake_mode;  //防虚假车牌模式 0  正常开闸, 1 不开闸(脱机模式下)
	int NewEnergy_mode; //新能源车牌模式 0 不关联开闸  1关联开闸

	int EmergencyMode; //应急车牌模式 0 不关联开闸  1关联开闸
	char reserved[80]; 
} WhiteList_Param;



typedef struct
{
	int alarm_in_delay;
	int alarm_in_stable_frame;   
	int alarm_in_check_interval; //地感线圈模式下，触发延时参数0~2000ms,默认0
	int max_again_process_cnt;   //地感线圈模式下，无牌车二次处理次数0~30,默认10
	int u32Reserved[10];  
} HDTrigger_Param;

#define WHITELIST_VALID_TIME_LEN 10
typedef struct{
	char plate_number[16];
	char valid_sdate[WHITELIST_VALID_TIME_LEN+1];
	char valid_edate[WHITELIST_VALID_TIME_LEN+1];	
	char valid_stime[WHITELIST_VALID_TIME_LEN+1];
	char valid_etime[WHITELIST_VALID_TIME_LEN+1];	
	char type[WHITELIST_VALID_TIME_LEN+1];	
	char reserved[64];	
}WHITELIST_ITEM;

typedef struct{
	char plate_number[128];
	char valid_sdate[WHITELIST_VALID_TIME_LEN+1];
	char valid_edate[WHITELIST_VALID_TIME_LEN+1];	
	char valid_stime[WHITELIST_VALID_TIME_LEN+1];
	char valid_etime[WHITELIST_VALID_TIME_LEN+1];	
	char type[WHITELIST_VALID_TIME_LEN+1];	
	char reserved[64];	
}WHITELIST_ITEM_NEW;

typedef struct
{
	ICE_U32 u32Enable;		//是否开启
	ICE_U32 u32Time;		//分钟为单位，例如8点为480
	ICE_U32 u32Reserved[16];
	
} AutoRebootParam;

typedef struct
{
	char passwd[16];
	ICE_U32 u32Enable;
	ICE_U32 u32Reserved[64];
	
} EncryptParam;


typedef struct
{
	ICE_U32 rs485_1;	//0:相机控制1:软件控制
	ICE_U32 rs485_2;	//0:相机控制1:软件控制
	ICE_U32 u32Reserved[16];
}SFM_RS485TransTypeParam;//485串口透传模式配置

typedef struct
{
	char old_passwd[16];
	char new_passwd[16];
	ICE_U32 u32Reserved[64];
	
} PasswdParam;

typedef struct
{
	ICE_U32 u32DNS;		//首选DNS
	ICE_U32 u32DNS2;	//备用DNS
	ICE_U32 u32Reserved[6];
	
} DNSParam;

typedef struct
{
	ICE_U32 u32Luminance;		//亮度
	ICE_U32 u32AlwaysOn;		//敞亮模式: 开启:1 关闭:0
	ICE_U32 u32Reserved[6];
	
} LightParam;

typedef struct
{
	ICE_U8 u8Endivisor;
	ICE_U8 u8Lightlevel;
	ICE_U8 u8Shh;
	ICE_U8 u8Smm;
	ICE_U8 u8Ehh;
	ICE_U8 u8Emm;
	ICE_U8 u8Reserved[62];
}IntervalCtlLightDivisor;

typedef struct T_DivLightCtrl
{
	IntervalCtlLightDivisor tLightDiv[3];
	ICE_U8 aucReserved[256];
}T_DivLightCtrl;

typedef struct
{
	ICE_U32 u32Enable;			//是否开启
	ICE_U32 u32Interval;		//二次开闸周期
	ICE_U32 u32Reserved[16];
	
} ReOpenParam;

typedef struct
{
	ICE_U8 io_in_0;
	ICE_U8 io_in_1;
	ICE_U8 io_in_2;
	ICE_U8 io_in_3;
}IoInState;

typedef struct
{
	ICE_U8 isOpen;
}TimerReboot;

typedef struct
{
	ICE_U32 u32IP;		//FTP server ip
	char szUserName[64];		//user name
	char szPasswd[64];		//passwd
	ICE_U32 u32HeartBeatInt;		//heart inverval
	ICE_U32 u32Enable;  //FTP upload open or close
	ICE_U32 u32Plate; // 文件名是否包含车牌号
	ICE_U32 u32XML; //是否上传XML 文件
	char s8Path[100]; //上传路径
	ICE_U32 u32Reserved[2];
	
}FTPParam;

typedef struct
{
	int enable;	//是否使能
	char ledip[16];//led的ip
	int ledport;//led的端口号
	int as32Reserved[4]; //预留参数

} ICE_LED_PARAM;


typedef struct
{
	ICE_U16 u16EnStrobeCtl;			//是否开启爆闪灯配置
	ICE_U16 u16TriggerDelay;			//爆闪-识别延时
	ICE_U16 u16StrobeLastTime;		//爆闪灯持续时间
	ICE_U16 u16StrobeMode;				//0:爆闪模式；1:常亮模式
	ICE_U16 u16StrobeCtlMode;			//0:相机不控制模式；1:相机白天夜晚检测模式
	ICE_U32 reserved[7];				//保留位
}strobe_light_param_st;//爆闪灯配置

//镜头AF ZOOM操作
typedef struct _IPC_AF_ZOOM
{
	ICE_U8	num;		//1变倍，2聚焦
	ICE_U8	direction;	//1:放大，拉远, 2:缩小，拉近
	ICE_U8  speed;		//速度： 0-1；0为停止,1为操作
	ICE_U16 step;		//步数
	ICE_U8	reserved[18];
}ICE_IPC_AF_ZOOM;

#define ISP_CFG_FILE "ISP_param.cfg"
#define UART_CFG_FILE "uart_param.cfg"
#define SD_CFG_FILE "SD_param.cfg"
#define WHITELIST_CFG_FILE "whitelist_param.cfg"
#define WHITELIST_FILE "whitelist.txt"
#define USER_DATA_FILE "user_data.cfg"
#define HDTRIGGER_CFG_FILE "alarm_in_stable.txt"
#define UAER_PASSWD_FILE "user_passwd.cfg"
#define FILE_LIGHT_FILE "fill_light.cfg"
#define LED_CFG_FILE "Led_Param.cfg"
#define STROBE_LIGHT_CFG "strobe_light.cfg"




//! \ingroup group_communication
//! 相机配置相关数据类型
typedef enum
{
	ICE_CAMERA_CONFIG_TYPE_BASE 					= 0x5000,		//!< 相机配置类型基础字段

	ICE_CAMERA_CONFIG_TYPE_SET_BASE_PARAM			= 0x5001,		//!< 设置相机基本参数（名称、IP地址、设备编号等）
	ICE_CAMERA_CONFIG_TYPE_SET_BASE_PARAM_RSP		= 0x5002,		//!< 设置相机基本参数应答
	ICE_CAMERA_CONFIG_TYPE_GET_BASE_PARAM			= 0x5003,		//!< 获取相机基本参数
	ICE_CAMERA_CONFIG_TYPE_GET_BASE_PARAM_RSP		= 0x5004,		//!< 获取相机基本参数应答
	
	ICE_CAMERA_CONFIG_TYPE_SET_SYSTEM_TIME			= 0x5005,		//!< 设置相机系统时间
	ICE_CAMERA_CONFIG_TYPE_SET_SYSTEM_TIME_RSP		= 0x5006,		//!< 设置相机系统时间应答
	ICE_CAMERA_CONFIG_TYPE_GET_SYSTEM_TIME			= 0x5007,		//!< 获取相机系统时间
	ICE_CAMERA_CONFIG_TYPE_GET_SYSTEM_TIME_RSP		= 0x5008,		//!< 获取相机系统时间应答
	
	ICE_CAMERA_CONFIG_TYPE_SET_ISP_PARAM			= 0x5009,		//!< 设置ISP参数（曝光、增益、白平衡)
	ICE_CAMERA_CONFIG_TYPE_SET_ISP_PARAM_RSP		= 0x5010,		//!< 设置ISP参数应!答
	ICE_CAMERA_CONFIG_TYPE_GET_ISP_PARAM			= 0x5011,		//!< 获取ISP参数
	ICE_CAMERA_CONFIG_TYPE_GET_ISP_PARAM_RSP		= 0x5012,		//!< 获取ISP参数应答
	
	ICE_CAMERA_CONFIG_TYPE_SET_VENC_PARAM			= 0x5013,		//!< 设置编码参数（码流、分辨率、码率控制方式等）
	ICE_CAMERA_CONFIG_TYPE_SET_VENC_PARAM_RSP		= 0x5014,		//!< 设置编码参数应答
	ICE_CAMERA_CONFIG_TYPE_GET_VENC_PARAM			= 0x5015,		//!< 获取编码参数
	ICE_CAMERA_CONFIG_TYPE_GET_VENC_PARAM_RSP		= 0x5016,		//!< 设置编码参数应答
	
	ICE_CAMERA_CONFIG_TYPE_SET_IO_PARAM				= 0x5017,		//!< 设置IO参数（电平输出（高、低、上升沿、下降沿）、光耦输出）
	ICE_CAMERA_CONFIG_TYPE_SET_IO_PARAM_RSP			= 0x5018,		//!< 设置IO参数应答
	ICE_CAMERA_CONFIG_TYPE_GET_IO_PARAM				= 0x5019,		//!< 获取IO参数
	ICE_CAMERA_CONFIG_TYPE_GET_IO_PARAM_RSP			= 0x5020,		//!< 设置IO参数应答
	
	ICE_CAMERA_CONFIG_TYPE_SET_COM_PARAM			= 0x5021,		//!< 设置串口参数（232/485 波特率 ）
	ICE_CAMERA_CONFIG_TYPE_SET_COM_PARAM_RSP		= 0x5022,		//!< 设置串口参数应答
	ICE_CAMERA_CONFIG_TYPE_GET_COM_PARAM			= 0x5023,		//!< 获取串口参数
	ICE_CAMERA_CONFIG_TYPE_GET_COM_PARAM_RSP		= 0x5024,		//!< 设置串口参数应答
	
	ICE_CAMERA_CONFIG_TYPE_UPDATE_PROGRAM			= 0x5025,		//!< 升级程序
	ICE_CAMERA_CONFIG_TYPE_UPDATE_PROGRAM_RSP		= 0x5026,		//!< 升级程序应答
	
	ICE_CAMERA_CONFIG_TYPE_DEFAULT_PROGRAM			= 0x5027,		//!< 恢复出厂默认程序
	ICE_CAMERA_CONFIG_TYPE_DEFAULT_PROGRAM_RSP		= 0x5028,		//!< 恢复出厂默认应答
	
	ICE_CAMERA_CONFIG_TYPE_DEFAULT_PARAM			= 0x5029,		//!< 恢复默认参数
	ICE_CAMERA_CONFIG_TYPE_DEFAULT_PARAM_RSP		= 0x5030,		//!< 恢复默认参数应答
	
	ICE_CAMERA_CONFIG_TYPE_DEFAULT_PARAM_EXP_IP		= 0x5031,		//!< 恢复除IP外的默认参数
	ICE_CAMERA_CONFIG_TYPE_DEFAULT_PARAM_EXP_IP_RSP	= 0x5032,		//!< 恢复除IP外的默认参数应答
	
	ICE_CAMERA_CONFIG_TYPE_SET_FTP_PARAM			= 0x5033,		//!< 设置FTP参数（FTP地址、用户名、密码）
	ICE_CAMERA_CONFIG_TYPE_SET_FTP_PARAM_RSP		= 0x5034,		//!< 设置FTP参数应答
	ICE_CAMERA_CONFIG_TYPE_GET_FTP_PARAM			= 0x5035,		//!< 获取FTP参数
	ICE_CAMERA_CONFIG_TYPE_GET_FTP_PARAM_RSP		= 0x5036,		//!< 获取FTP参数应答
	
	ICE_CAMERA_CONFIG_TYPE_SET_SNAP_PARAM			= 0x5037,		//!< 设置抓拍机参数（是否启用抓拍机、抓拍机地址、抓拍延时）
	ICE_CAMERA_CONFIG_TYPE_SET_SNAP_PARAM_RSP		= 0x5038,		//!< 设置抓拍机参数应答
	ICE_CAMERA_CONFIG_TYPE_GET_SNAP_PARAM			= 0x5039,		//!< 获取抓拍机参数
	ICE_CAMERA_CONFIG_TYPE_GET_SNAP_PARAM_RSP		= 0x5040,		//!< 获取抓拍机参数应答
	
	ICE_CAMERA_CONFIG_TYPE_SET_HCNT_PARAM			= 0x5041,		//!< 设置人数统计参数（rs485协议类型、车门类型）
	ICE_CAMERA_CONFIG_TYPE_SET_HCNT_PARAM_RSP		= 0x5042,		//!< 设置人数统计参数应答
	ICE_CAMERA_CONFIG_TYPE_GET_HCNT_PARAM			= 0x5043,		//!< 获取人数统计参数
	ICE_CAMERA_CONFIG_TYPE_GET_HCNT_PARAM_RSP		= 0x5044,		//!< 获取人数统计参数应答
	
	ICE_CAMERA_CONFIG_TYPE_SET_ALARM_IN_CFG			= 0x5045,		//!< 设置告警输入配置（常开或常闭）
	ICE_CAMERA_CONFIG_TYPE_SET_ALARM_IN_CFG_RSP		= 0x5046,		//!< 设置告警输入配置应答
	ICE_CAMERA_CONFIG_TYPE_GET_ALARM_IN_CFG			= 0x5047,		//!< 获取告警输入配置
	ICE_CAMERA_CONFIG_TYPE_GET_ALARM_IN_CFG_RSP		= 0x5048,		//!< 获取告警输入配置应答
	
	ICE_CAMERA_CONFIG_TYPE_SET_TMSYNC_CFG				= 0x5049,		//!< 设置时间同步配置
	ICE_CAMERA_CONFIG_TYPE_SET_TMSYNC_CFG_RSP			= 0x5050,		//!< 设置时间同步配置应答
	ICE_CAMERA_CONFIG_TYPE_GET_TMSYNC_CFG				= 0x5051,		//!< 获取时间同步配置
	ICE_CAMERA_CONFIG_TYPE_GET_TMSYNC_CFG_RSP			= 0x5052,		//!< 获取时间同步配置应答
	
	ICE_CAMERA_CONFIG_TYPE_SET_OSD_CFG				= 0x5053,		//!< 设置OSD配置
	ICE_CAMERA_CONFIG_TYPE_SET_OSD_CFG_RSP			= 0x5054,		//!< 设置OSD配置应答
	ICE_CAMERA_CONFIG_TYPE_GET_OSD_CFG				= 0x5055,		//!< 获取OSD配置
	ICE_CAMERA_CONFIG_TYPE_GET_OSD_CFG_RSP			= 0x5056,		//!< 获取OSD配置应答
	
	ICE_CAMERA_CONFIG_TYPE_SET_SCHED_TASK_CFG		= 0x5061,		//!< 设置计划任务配置
	ICE_CAMERA_CONFIG_TYPE_SET_SCHED_TASK_CFG_RSP	= 0x5062,		//!< 设置计划任务配置应答
	ICE_CAMERA_CONFIG_TYPE_GET_SCHED_TASK_CFG		= 0x5063,		//!< 获取计划任务配置
	ICE_CAMERA_CONFIG_TYPE_GET_SCHED_TASK_CFG_RSP	= 0x5064,		//!< 获取计划任务配置应答
	
	ICE_CAMERA_CONFIG_TYPE_SET_RELAY_OUT		= 0x5065,		//!< 设置开关量输出
	ICE_CAMERA_CONFIG_TYPE_SET_RELAY_OUT_RSP	= 0x5066,		//!< 设置开关量输出应答
	
	ICE_CAMERA_CONFIG_TYPE_SET_PHYCHN_CFG				= 0x5067,		//!< 设置物理通道配置
	ICE_CAMERA_CONFIG_TYPE_SET_PHYCHN_CFG_RSP			= 0x5068,		//!< 设置物理通道配置应答
	ICE_CAMERA_CONFIG_TYPE_GET_PHYCHN_CFG				= 0x5069,		//!< 获取物理通道配置
	ICE_CAMERA_CONFIG_TYPE_GET_PHYCHN_CFG_RSP			= 0x5070,		//!< 获取物理通道配置应答

	
	ICE_CAMERA_CONFIG_TYPE_CHECK_VFD_COMM			= 0x5071,		//!< 验证火焰相机主从通讯
	ICE_CAMERA_CONFIG_TYPE_CHECK_VFD_COMM_RSP		= 0x5072,		//!< 验证火焰相机主从通讯应答
	
	ICE_CAMERA_CONFIG_TYPE_SET_VFD_PARAM		= 0x5073,		//!< 设置火焰相机参数
	ICE_CAMERA_CONFIG_TYPE_SET_VFD_PARAM_RSP	= 0x5074,		//!< 设置火焰相机参数应答
	ICE_CAMERA_CONFIG_TYPE_GET_VFD_PARAM		= 0x5075,		//!< 获取火焰相机参数
	ICE_CAMERA_CONFIG_TYPE_GET_VFD_PARAM_RSP	= 0x5076,		//!< 获取火焰相机参数应答

	ICE_CAMERA_CONFIG_TYPE_SET_UART_PARAM		= 0x5077,		//!< 设置相机串口参数
	ICE_CAMERA_CONFIG_TYPE_SET_UART_PARAM_RSP	= 0x5078,		//!< 设置相机串口参数应答
	ICE_CAMERA_CONFIG_TYPE_GET_UART_PARAM		= 0x5079,		//!< 获取相机串口参数
	ICE_CAMERA_CONFIG_TYPE_GET_UART_PARAM_RSP	= 0x5080,		//!< 获取相机串口参数应答

	ICE_CAMERA_CONFIG_TYPE_SET_HTTP_POST_PARAM		= 0x5081,		//!< 设置HTTP POST参数
	ICE_CAMERA_CONFIG_TYPE_SET_HTTP_POST_PARAM_RSP	= 0x5082,		//!< 设置HTTP POST参数应答
	ICE_CAMERA_CONFIG_TYPE_GET_HTTP_POST_PARAM		= 0x5083,		//!< 获取HTTP POST参数
	ICE_CAMERA_CONFIG_TYPE_GET_HTTP_POST_PARAM_RSP	= 0x5084,		//!< 获取HTTP POST参数应答

	ICE_CAMERA_CONFIG_TYPE_SET_EXP_AREGULATE_PARAM		= 0x5085,		//!< 设置曝光自动调节参数
	ICE_CAMERA_CONFIG_TYPE_SET_EXP_AREGULATE_PARAM_RSP	= 0x5086,		//!< 设置曝光自动调节参数应答
	ICE_CAMERA_CONFIG_TYPE_GET_EXP_AREGULATE_PARAM		= 0x5087,		//!< 获取曝光自动调节参数
	ICE_CAMERA_CONFIG_TYPE_GET_EXP_AREGULATE_PARAM_RSP	= 0x5088,		//!< 获取曝光自动调节参数应答


	ICE_CAMERA_CONFIG_TYPE_SET_SDCARD_PARAM		= 0x5089,		//!< 设置VDC SD卡存储参数
	ICE_CAMERA_CONFIG_TYPE_SET_SDCARD_PARAM_RSP	= 0x5090,		//!< 设置VDC SD卡存储参数应答
	ICE_CAMERA_CONFIG_TYPE_GET_SDCARD_PARAM		= 0x5091,		//!< 获取VDC SD卡存储参数
	ICE_CAMERA_CONFIG_TYPE_GET_SDCARD_PARAM_RSP	= 0x5092,		//!< 获取VDC SD卡存储参数应答

	ICE_CAMERA_CONFIG_TYPE_GET_DEV_ID		= 0x5093,		//!< 获取设备唯一ID
	ICE_CAMERA_CONFIG_TYPE_GET_DEV_ID_RSP	= 0x5094,		//!< 获取设备唯一ID应答

	ICE_CAMERA_CONFIG_TYPE_SET_WHITELIST_PARAM		= 0x5095,		//!< 设置白名单参数
	ICE_CAMERA_CONFIG_TYPE_SET_WHITELIST_PARAM_RSP	= 0x5096,		//!< 设置白名单参数应答
	ICE_CAMERA_CONFIG_TYPE_GET_WHITELIST_PARAM		= 0x5097,		//!< 获取白名单参数
	ICE_CAMERA_CONFIG_TYPE_GET_WHITELIST_PARAM_RSP	= 0x5098,		//!< 获取白名单参数应答

	ICE_CAMERA_CONFIG_TYPE_WRITE_USER_DATA		= 0x5099,		//!< 写入用户数据
	ICE_CAMERA_CONFIG_TYPE_WRITE_USER_DATA_RSP	= 0x5100,		//!< 写入用户数据应答
	ICE_CAMERA_CONFIG_TYPE_READ_USER_DATA		= 0x5101,		//!< 读出用户数据
	ICE_CAMERA_CONFIG_TYPE_READ_USER_DATA_RSP	= 0x5102,		//!< 读出用户数据应答

	ICE_CAMERA_CONFIG_TYPE_WRITE_WHITE_LIST		= 0x5103,		//!< 写入白名单
	ICE_CAMERA_CONFIG_TYPE_WRITE_WHITE_LIST_RSP	= 0x5104,		//!< 写入白名单应答
	ICE_CAMERA_CONFIG_TYPE_READ_WHITE_LIST		= 0x5105,		//!< 读出白名单
	ICE_CAMERA_CONFIG_TYPE_READ_WHITE_LIST_RSP	= 0x5106,		//!< 读出白名单应答
	

	ICE_CAMERA_CONFIG_TYPE_SET_HDTRIGGER_PARAM		= 0x5107,		//!< 设置硬触发参数
	ICE_CAMERA_CONFIG_TYPE_SET_HDTRIGGER_PARAM_RSP	= 0x5108,		//!< 设置硬触发参数应答
	ICE_CAMERA_CONFIG_TYPE_GET_HDTRIGGER_PARAM		= 0x5109,		//!< 获取硬触发参数
	ICE_CAMERA_CONFIG_TYPE_GET_HDTRIGGER_PARAM_RSP	= 0x5110,		//!< 获取硬触发参数应答

	ICE_CAMERA_CONFIG_TYPE_ADD_WHITE_LIST		= 0x5111,		//!< 增加白名单
	ICE_CAMERA_CONFIG_TYPE_ADD_WHITE_LIST_RSP	= 0x5112,		//!< 增加白名单应答
	ICE_CAMERA_CONFIG_TYPE_DEL_WHITE_LIST		= 0x5113,		//!< 删除白名单
	ICE_CAMERA_CONFIG_TYPE_DEL_WHITE_LIST_RSP	= 0x5114,		//!< 删除白名单应答
	ICE_CAMERA_CONFIG_TYPE_EDIT_WHITE_LIST		= 0x5115,		//!< 编辑白名单
	ICE_CAMERA_CONFIG_TYPE_EDIT_WHITE_LIST_RSP	= 0x5116,		//!< 编辑白名单应答
	ICE_CAMERA_CONFIG_TYPE_FIND_WHITE_LIST		= 0x5117,		//!< 查找白名单
	ICE_CAMERA_CONFIG_TYPE_FIND_WHITE_LIST_RSP	= 0x5118,		//!< 查找白名单应答
	ICE_CAMERA_CONFIG_TYPE_DELALL_WHITE_LIST		= 0x5119,		//!< 删除所有白名单
	ICE_CAMERA_CONFIG_TYPE_DELALL_WHITE_LIST_RSP	= 0x5120,		//!< 删除所有白名单应答

	ICE_CAMERA_CONFIG_TYPE_SET_AUTO_REBOOT_PARAM		= 0x5121,		//!< 设置自动重启参数
	ICE_CAMERA_CONFIG_TYPE_SET_AUTO_REBOOT_PARAM_RSP	= 0x5122,		//!< 设置自动重启参数应答
	ICE_CAMERA_CONFIG_TYPE_GET_AUTO_REBOOT_PARAM		= 0x5123,		//!< 获取自动重启参数
	ICE_CAMERA_CONFIG_TYPE_GET_AUTO_REBOOT_PARAM_RSP	= 0x5124,		//!< 获取自动重启参数应答

	ICE_CAMERA_CONFIG_TYPE_SET_PASSWD_PARAM		= 0x5125,		//!< 设置密码参数
	ICE_CAMERA_CONFIG_TYPE_SET_PASSWD_PARAM_RSP	= 0x5126,		//!< 设置密码参数应答
	ICE_CAMERA_CONFIG_TYPE_RM_LOG_FILE		= 0x5127,		//!< 删除日志文件
	ICE_CAMERA_CONFIG_TYPE_RM_LOG_FILE_RSP	= 0x5128,		//!<  删除日志文件应答
	
	ICE_CAMERA_CONFIG_TYPE_SET_DNS_PARAM			= 0x5129,		//!< 设置相机DNS参数
	ICE_CAMERA_CONFIG_TYPE_SET_DNS_PARAM_RSP		= 0x5130,		//!< 设置相机DNS参数应答
	ICE_CAMERA_CONFIG_TYPE_GET_DNS_PARAM			= 0x5131,		//!< 获取相机DNS参数
	ICE_CAMERA_CONFIG_TYPE_GET_DNS_PARAM_RSP		= 0x5132,		//!< 获取相机DNS参数应答
	
	ICE_CAMERA_CONFIG_TYPE_SET_LIGHT_PARAM			= 0x5133,		//!< 设置补光灯参数
	ICE_CAMERA_CONFIG_TYPE_SET_LIGHT_PARAM_RSP		= 0x5134,		//!< 设置补光灯参数应答
	ICE_CAMERA_CONFIG_TYPE_GET_LIGHT_PARAM			= 0x5135,		//!< 获取补光灯参数
	ICE_CAMERA_CONFIG_TYPE_GET_LIGHT_PARAM_RSP		= 0x5136,		//!< 获取补光灯参数应答
	
	ICE_CAMERA_CONFIG_TYPE_SET_RELAY_OUT2		= 0x5137,		//!< 设置开关量2输出
	ICE_CAMERA_CONFIG_TYPE_SET_RELAY_OUT2_RSP	= 0x5138,		//!< 设置开关量2输出应答

	ICE_CAMERA_CONFIG_TYPE_SET_REOPEN_PARAM		= 0x5139,		//!< 设置二次开闸参数
	ICE_CAMERA_CONFIG_TYPE_SET_REOPEN_PARAM_RSP	= 0x5140,		//!< 设置二次开闸参数应答
	ICE_CAMERA_CONFIG_TYPE_GET_REOPEN_PARAM		= 0x5141,		//!< 获取二次开闸参数
	ICE_CAMERA_CONFIG_TYPE_GET_REOPEN_PARAM_RSP	= 0x5142,		//!< 获取二次开闸参数应答

	ICE_CAMERA_CONFIG_TYPE_SET_OFFLINE_AO_PLAY_PARAM = 0x5143, //!<设置脱机语音播报类型
	ICE_CAMERA_CONFIG_TYPE_SET_OFFLINE_AO_PLAY_PARAM_RSP = 0x5144,//!>设置脱机语音播报类型应答
	ICE_CAMERA_CONFIG_TYPE_GET_OFFLINE_AO_PLAY_PARAM = 0x5145, //!> 获取脱机语音播报类型
	ICE_CAMERA_CONFIG_TYPE_GET_OFFLINE_AO_PLAY_PARAM_RSP = 0x5146,//!>获取脱机语音播报类型应答

	ICE_CAMERA_CONFIG_TYPE_SET_LED_PARAM		= 0x5147,		//!< 设置LED参数
	ICE_CAMERA_CONFIG_TYPE_SET_LED_PARAM_RSP	= 0x5148,		//!< 设置LED参数应答
	ICE_CAMERA_CONFIG_TYPE_GET_LED_PARAM		= 0x5149,		//!< 获取LED参数
	ICE_CAMERA_CONFIG_TYPE_GET_LED_PARAM_RSP	= 0x514A,		//!< 获取LED参数应答

	ICE_CAMERA_CONFIG_TYPE_SET_CGI_PARAM		= 0x514B,		//!< 设置CGI参数
	ICE_CAMERA_CONFIG_TYPE_SET_CGI_PARAM_RSP	= 0x514C,		//!< 设置CGI参数应答
	ICE_CAMERA_CONFIG_TYPE_GET_CGI_PARAM		= 0x514D,		//!< 获取CGI参数
	ICE_CAMERA_CONFIG_TYPE_GET_CGI_PARAM_RSP	= 0x514E,		//!< 获取CGI参数应答

	ICE_CAMERA_CONFIG_TYPE_SET_LED_PROTOCOL1    = 0x5150,       //设置led协议1参数
	ICE_CAMERA_CONFIG_TYPE_SET_LED_PROTOCOL1_RSP    = 0x5151,   // 设置led协议1参数应答
	ICE_CAMERA_CONFIG_TYPE_GET_LED_PROTOCOL1    = 0x5152,       //获取led协议1参数
	ICE_CAMERA_CONFIG_TYPE_GET_LED_PROTOCOL1_RSP    = 0x5153,   // 获取led协议1参数应答
	
	ICE_CAMERA_CONFIG_TYPE_SET_CAMERA_OFFLINE_PARAM		 = 0x5154,       //!<设置相机强制脱机工作的参数
	ICE_CAMERA_CONFIG_TYPE_SET_CAMERA_OFFLINE_PARAM_RSP  = 0x5155,   //!<设置相机强制脱机工作的参数应答	
	ICE_CAMERA_CONFIG_TYPE_GET_CAMERA_OFFLINE_PARAM		 = 0x5156,       //!<获取相机强制脱机工作的参数
	ICE_CAMERA_CONFIG_TYPE_GET_CAMERA_OFFLINE_PARAM_RSP  = 0x5157,   //!<获取相机强制脱机工作的参数应答

	ICE_CAMERA_CONFIG_TYPE_SET_STROBE_LIGHT_PARAM		= 0x5158,       //!<设置爆闪灯参数
	ICE_CAMERA_CONFIG_TYPE_SET_STROBE_LIGHT_PARAM_RSP   = 0x5159,   //!<设置爆闪灯参数应答
	ICE_CAMERA_CONFIG_TYPE_GET_STROBE_LIGHT_PARAM		= 0x5160,       //!<获取爆闪灯参数
	ICE_CAMERA_CONFIG_TYPE_GET_STROBE_LIGHT_PARAM_RSP   = 0x5161,   //!<获取爆闪灯参数应答

	ICE_CAMERA_CONFIG_TYPE_SET_LED_CARD_2_SERIAL_PROTOCOL		 = 0x5162,       //!<设置led控制卡协议2参数
	ICE_CAMERA_CONFIG_TYPE_SET_LED_CARD_2_SERIAL_PROTOCOL_RSP    = 0x5163,   //!<设置led控制卡协议2参数应答
	ICE_CAMERA_CONFIG_TYPE_GET_LED_CARD_2_SERIAL_PROTOCOL		 = 0x5164,       //!<获取led控制卡协议2参数
	ICE_CAMERA_CONFIG_TYPE_GET_LED_CARD_2_SERIAL_PROTOCOL_RSP    = 0x5165,   //!<获取led控制卡协议2参数应答

	ICE_CAMERA_CONFIG_TYPE_SERIAL_LED_CARD_COMMON_TIME_CFG_PARAM	= 0x5166,	//!<设置串口led控制卡手动校时参数
	ICE_CAMERA_CONFIG_TYPE_SERIAL_LED_CARD_COMMON_TIME_CFG_PARAM_RSP	= 0x5167,	//!<设置串口led控制卡手动校时参数应答

	ICE_CAMERA_CONFIG_TYPE_CONTROL_SERIAL_CARD_COMMON_BASE_PARAM  = 0x5168,			//!< 串口控制卡公共基本参数设定
	ICE_CAMERA_CONFIG_TYPE_CONTROL_SERIAL_CARD_COMMON_BASE_PARAM_RSP  = 0x5169,		//!<  串口控制卡公共基本参数设定应答
	
	ICE_CAMERA_CONFIG_TYPE_SET_ENCRYPT_PARAM		= 0x516A,		//!< 设置启用密码参数
	ICE_CAMERA_CONFIG_TYPE_SET_ENCRYPT_PARAM_RSP	= 0x516B,		//!< 设置启用密码参数应答

	ICE_CAMERA_CONFIG_TYPE_SET_RS485_TRANS_TYPE_SFM = 0x516C,		//!<设置 485串口透传类型
	ICE_CAMERA_CONFIG_TYPE_SET_RS485_TRANS_TYPE_SFM_RSP = 0x516D, //!<设置 485串口透传类型应答

	ICE_CAMERA_CONFIG_TYPE_GET_RS485_TRANS_TYPE_SFM = 0x516E,		//!<获取 485串口透传类型
	ICE_CAMERA_CONFIG_TYPE_GET_RS485_TRANS_TYPE_SFM_RSP = 0x516F, //!<获取 485串口透传类型应答


	ICE_CAMERA_CONFIG_TYPE_SET_DEVICE_PARAM		= 0x5170,		//!< 设置设备信息参数	
	ICE_CAMERA_CONFIG_TYPE_SET_DEVICE_PARAM_RSP	= 0x5171,		//!< 设置设备信息参数应答
	ICE_CAMERA_CONFIG_TYPE_GET_DEVICE_PARAM		= 0x5172,		//!< 获取设备信息参数	
	ICE_CAMERA_CONFIG_TYPE_GET_DEVICE_PARAM_RSP	= 0x5173,		//!< 获取设备信息参数应答

	ICE_CAMERA_CONFIG_TYPE_SET_ALARM_IN_EXT_PARAM		= 0x5174,		//!< 设置额外的报警输入参数	
	ICE_CAMERA_CONFIG_TYPE_SET_ALARM_IN_EXT_PARAM_RSP	= 0x5175,		//!< 设置额外的报警输入参数应答
	ICE_CAMERA_CONFIG_TYPE_GET_ALARM_IN_EXT_PARAM		= 0x5176,		//!< 获取额外的报警输入参数	
	ICE_CAMERA_CONFIG_TYPE_GET_ALARM_IN_EXT_PARAM_RSP	= 0x5177,		//!< 获取额外的报警输入参数应答

	ICE_CAMERA_CONFIG_TYPE_SET_FAC_MODE = 0x5178,			//!<设置工厂模式
	ICE_CAMERA_CONFIG_TYPE_SET_FAC_MODE_RSP = 0x5179,		//!<设置工厂模式应答



	//up to 0x5300 for 83C reserved
	ICE_CAMERA_CONFIG_TYPE_SET_USER_LICENSE	= 0x5300,                //!< 设置自定义校验信息
	ICE_CAMERA_CONFIG_TYPE_SET_USER_LICENSE_RSP	= 0x5301,            //!< 设置自定义校验信息应答
	ICE_CAMERA_CONFIG_TYPE_CHECK_USER_LICENSE	= 0x5302,            //!< 校验自定义校验信息
	ICE_CAMERA_CONFIG_TYPE_CHECK_USER_LICENSE_RSP	= 0x5303,	     //!< 校验自定义校验信息应答
	ICE_CAMERA_CONFIG_TYPE_GET_RTSP_SESSION_COUNT = 0x5304,		//!<获取视频连接路数
	ICE_CAMERA_CONFIG_TYPE_GET_RTSP_SESSION_COUNT_RSP = 0x5305,	//!<获取视频连接路数应答

	ICE_CAMERA_CONFIG_TYPE_RESET_USER_LICENSE = 0x5306,			//!<复位用户自定义校验信息
	ICE_CAMERA_CONFIG_TYPE_RESET_USER_LICENSE_RSP = 0x5307,		//!<复位用户自定义校验信息应答

	ICE_CAMERA_CONFIG_TYPE_HAS_USER_LICENSE = 0x5308,			//!<是否开启用户自定义校验
	ICE_CAMERA_CONFIG_TYPE_HAS_USER_LICENSE_RSP = 0x5309,		//!<是否开启用户自定义校验应答


	ICE_CAMERA_CONFIG_TYPE_GET_DIVISOR_CTL_LIGHT_CONFIG = 0x530a,		//!<获取时段控灯参数
	ICE_CAMERA_CONFIG_TYPE_GET_DIVISOR_CTL_LIGHT_CONFIG_RSP = 0x530b,	//!<获取时段控灯参数应答

	ICE_CAMERA_CONFIG_TYPE_SET_DIVISOR_CTL_LIGHT_CONFIG = 0x530c,		//!<设置时段控灯参数
	ICE_CAMERA_CONFIG_TYPE_SET_DIVISOR_CTL_LIGHT_CONFIG_RSP = 0x530d,	//!<设置时段控灯参数应答

	ICE_CAMERA_CONFIG_TYPE_SET_NORMAL_AF_ZOOM = 0x530e,		//!<设置调焦 变倍
	ICE_CAMERA_CONFIG_TYPE_SET_NORMAL_AF_ZOOM_RSP = 0x530f,	//!<设置调焦应答

	ICE_CAMERA_CONFIG_TYPE_SET_NORMAL_AF_RESET	= 0x5310,// 聚焦复位
	ICE_CAMERA_CONFIG_TYPE_SET_NORMAL_AF_RESET_RSP	= 0x5311,

	ICE_CAMERA_CONFIG_TYPE_SET_NORMAL_FOCUS_FAR	= 0x5312,// 拉到最远
	ICE_CAMERA_CONFIG_TYPE_SET_NORMAL_FOCUS_FAR_RSP	= 0x5313,

	ICE_CAMERA_CONFIG_TYPE_SET_NORMAL_FOCUS_NEAR	= 0x5314,// 拉到 最近
	ICE_CAMERA_CONFIG_TYPE_SET_NORMAL_FOCUS_NEAR_RSP = 0x5315,

	ICE_CAMERA_CONFIG_TYPE_GET_SCENE_MODE = 0x5316, 	//!<获取场景模式
	ICE_CAMERA_CONFIG_TYPE_GET_SCENE_MODE_RSP = 0x5317, //!<获取场景模式应答

	ICE_CAMERA_CONFIG_TYPE_SET_SCENE_MODE = 0x5318, 	//!<设置场景模式
	ICE_CAMERA_CONFIG_TYPE_SET_SCENE_MODE_RSP = 0x5319, //!<设置场景模式应答

	ICE_CAMERA_CONFIG_TYPE_AUDIO_TEST = 0x531a, 	// 音频回环测试
	ICE_CAMERA_CONFIG_TYPE_AUDIO_TEST_RSP = 0x531b, //  音频回环测试  应答


	ICE_CAMERA_CONFIG_TYPE_GET_LOG_CONFIG = 0x531c,		//!<获取日志配置
	ICE_CAMERA_CONFIG_TYPE_GET_LOG_CONFIG_RSP = 0x531d,	//!<获取日志配置应答

	ICE_CAMERA_CONFIG_TYPE_SET_LOG_CONFIG = 0x531e,		//!<设置日志配置
	ICE_CAMERA_CONFIG_TYPE_SET_LOG_CONFIG_RSP = 0x531f,	//!<设置日志配置应答

	ICE_CAMERA_CONFIG_TYPE_SET_OFFLINE_LED_CONFIG = 0x5320,             //!<设置脱机LED配置信息
	ICE_CAMERA_CONFIG_TYPE_SET_OFFLINE_LED_CONFIG_RSP = 0x5321,         //!>设置脱机LED配置信息应答
	ICE_CAMERA_CONFIG_TYPE_GET_OFFLINE_LED_CONFIG = 0x5322,             //!> 获取脱机LED配置信息
	ICE_CAMERA_CONFIG_TYPE_GET_OFFLINE_LED_CONFIG_RSP = 0x5323,         //!>获取脱机LED配置信息应答

	ICE_CAMERA_CONFIG_TYPE_SET_OFFLINE_CHARGE_RULE = 0x5324,             //!<设置脱机计费规则
	ICE_CAMERA_CONFIG_TYPE_SET_OFFLINE_CHARGE_RULE_RSP = 0x5325,         //!>设置脱机计费规则应答
	ICE_CAMERA_CONFIG_TYPE_GET_OFFLINE_CHARGE_RULE = 0x5326,             //!> 获取脱机计费规则
	ICE_CAMERA_CONFIG_TYPE_GET_OFFLINE_CHARGE_RULE_RSP = 0x5327,         //!>获取脱机计费规则应答

	ICE_CAMERA_CONFIG_TYPE_SET_OFFLINE_MULTICAST = 0x5328,             //!<设置脱机计费组播信息
	ICE_CAMERA_CONFIG_TYPE_SET_OFFLINE_MULTICAST_RSP = 0x5329,         //!>设置脱机计费组播信息应答
	ICE_CAMERA_CONFIG_TYPE_GET_OFFLINE_MULTICAST = 0x532a,             //!> 获取脱机计费组播信息
	ICE_CAMERA_CONFIG_TYPE_GET_OFFLINE_MULTICAST_RSP = 0x532b,         //!>获取脱机计费组播信息应答

	ICE_CAMERA_CONFIG_TYPE_READ_OFFLINE_VEHICLE_INFO_LIST		= 0x532c,		//!< 读出车辆在场信息
	ICE_CAMERA_CONFIG_TYPE_READ_OFFLINE_VEHICLE_INFO_LIST_RSP	= 0x532d,		//!< 读出车辆在场信息应答

	ICE_CAMERA_CONFIG_TYPE_GET_DEVICE_INFO  = 0x532e,                  //获取定制化版本信息
	ICE_CAMERA_CONFIG_TYPE_GET_DEVICE_INFO_RSP = 0x532f,               //获取定制化版本信息应答

	ICE_CAMERA_CONFIG_TYPE_OCD_RMALLDB	= 0x5331,						//!< 删除所有数据
	ICE_CAMERA_CONFIG_TYPE_OCD_RMALLDB_RSP	= 0x5332,					//!<  删除所有数据应答

	ICE_CAMERA_CONFIG_TYPE_GET_ICE_OCD_TO_LED	= 0x5333,			    //!<获取计费消息
	ICE_CAMERA_CONFIG_TYPE_GET_ICE_OCD_TO_LED_RSP	= 0x5334,			//!<获取计费消息应答

	ICE_CAMERA_CONFIG_TYPE_READ_OFFLINE_COST_LIST	= 0x5337,				//!<导出收费记录
	ICE_CAMERA_CONFIG_TYPE_READ_OFFLINE_COST_LIST_RSP	= 0x5338,			//!<导出收费记录应答

	ICE_CAMERA_CONFIG_TYPE_GET_MAIN_SUB_MODE_CFG	= 0x5339,			//!<获取主从模式配置
	ICE_CAMERA_CONFIG_TYPE_GET_MAIN_SUB_MODE_CFG_RSP	= 0x533a,		//!<获取主从模式配置应答

	ICE_CAMERA_CONFIG_TYPE_SET_MAIN_SUB_MODE_CFG	= 0x533b,			//!<设置主从模式配置
	ICE_CAMERA_CONFIG_TYPE_SET_MAIN_SUB_MODE_CFG_RSP	= 0x533c,		//!<设置主从模式配置应答

	ICE_CAMERA_CONFIG_TYPE_SET_ICE_OCD_TO_VDC	= 0x533d,				//!<脱机计费上报消息
	ICE_CAMERA_CONFIG_TYPE_SET_ICE_OCD_TO_VDC_RSP	= 0x533e,           //!<脱机计费上报消息应答



	ICE_CAMERA_CONFIG_TYPE_SET_RELAY_OUT3		= 0x533f,				//!< 设置开关量3输出
	ICE_CAMERA_CONFIG_TYPE_SET_RELAY_OUT3_RSP	= 0x5340,				//!< 设置开关量3输出应答

	ICE_CAMERA_CONFIG_TYPE_SET_RELAY_OUT4		= 0x5341,				//!< 设置开关量4输出
	ICE_CAMERA_CONFIG_TYPE_SET_RELAY_OUT4_RSP	= 0x5342,				//!< 设置开关量4输出应答

	ICE_CAMERA_CONFIG_TYPE_READ_LOCAL_OFFLINE_COST_LIST	= 0x5343,		//!<导出本地收费记录
	ICE_CAMERA_CONFIG_TYPE_READ_LOCAL_OFFLINE_COST_LIST_RSP= 0x5344,		//!<导出本地收费记录应答


	ICE_CAMERA_CONFIG_TYPE_UPDATE_VACANCIES = 0x5354,                                     //!<剩余车位数更新
	ICE_CAMERA_CONFIG_TYPE_UPDATE_VACANCIES_RSP = 0x5355,			 //!<剩余车位数更新应答

	ICE_CAMERA_CONFIG_TYPE_SET_TALK_BACK_VOLUME = 0x5356,			  //!<set talk back volume
	ICE_CAMERA_CONFIG_TYPE_SET_TALK_BACK_VOLUME_RSP = 0x5357,			 //!<

	ICE_CAMERA_CONFIG_TYPE_GET_TALK_BACK_VOLUME = 0x5358,			  //!<get talk back volume
	ICE_CAMERA_CONFIG_TYPE_GET_TALK_BACK_VOLUME_RSP = 0x5359,			 //!<		


	ICE_CAMERA_CONFIG_TYPE_SET_UID = 0x5360,			  //!<set UID
	ICE_CAMERA_CONFIG_TYPE_SET_UID_RSP = 0x5361,			 //!<

	ICE_CAMERA_CONFIG_TYPE_GET_UID = 0x5362,			  //!<get
	ICE_CAMERA_CONFIG_TYPE_GET_UID_RSP = 0x5363,			 //!<		


	//xinjiang
	ICE_CAMERA_CONFIG_TYPE_SET_HTTP_POST2_PARAM		= 0x5366,		//!< 设置HTTP POST参数
	ICE_CAMERA_CONFIG_TYPE_SET_HTTP_POST2_PARAM_RSP	= 0x5367,		//!< 设置HTTP POST参数应答
	ICE_CAMERA_CONFIG_TYPE_GET_HTTP_POST2_PARAM		= 0x5368,		//!< 获取HTTP POST参数
	ICE_CAMERA_CONFIG_TYPE_GET_HTTP_POST2_PARAM_RSP	= 0x5369,		//!< 获取HTTP POST参数应答

	ICE_CAMERA_CONFIG_TYPE_SET_CTP_CFG = 0x536A,			 //!<设置CTP配置
	ICE_CAMERA_CONFIG_TYPE_SET_CTP_CFG_RSP = 0x536B,		 //!>设置CTP配置应答
	ICE_CAMERA_CONFIG_TYPE_GET_CTP_CFG = 0x536C,			 //!> 获取CTP配置
	ICE_CAMERA_CONFIG_TYPE_GET_CTP_CFG_RSP = 0x536D,		 //!>获取CTP配置应答

	ICE_CAMERA_CONFIG_TYPE_SET_NETWORK_DHCP = 0x5370,  		   //!< DHCP 使能开启或关闭
	ICE_CAMERA_CONFIG_TYPE_SET_NETWORK_DHCP_RSP = 0x5371,   	   //!<DHCP 使能开启关闭应答
	ICE_CAMERA_CONFIG_TYPE_GET_NETWORK_DHCP = 0x5372,		   //!<获取使能状态
	ICE_CAMERA_CONFIG_TYPE_GET_NETWORK_DHCP_RSP = 0x5373,	   //!<获取使能状态应答

	ICE_CAMERA_CONFIG_TYPE_SET_CAMERA_4G_PARAM	= 0x5374,		//!<设置相机4G信息参数
	ICE_CAMERA_CONFIG_TYPE_SET_CAMERA_4G_PARAM_RSP	= 0x5375,	//!<设置相机4G信息参数参数应答	
	ICE_CAMERA_CONFIG_TYPE_GET_CAMERA_4G_PARAM	= 0x5376,		//!<获取相机4G参数
	ICE_CAMERA_CONFIG_TYPE_GET_CAMERA_4G_PARAM_RSP	= 0x5377,	//!<获取相机4G参数参数应答	

	ICE_CAMERA_CONFIG_TYPE_SET_CAMERA_ONVIF_CONFIG	= 0x5378,  	     //!<ONVIF 功能开启/关闭
	ICE_CAMERA_CONFIG_TYPE_SET_CAMERA_ONVIF_CONFIG_RSP	= 0x5379,	     //!<ONVIF功能开启/关闭应答
	ICE_CAMERA_CONFIG_TYPE_GET_CAMERA_ONVIF_CONFIG	= 0x537A,             //!<获取ONVIF使能状态
	ICE_CAMERA_CONFIG_TYPE_GET_CAMERA_ONVIF_CONFIG_RSP	= 0x537B,             //!<获取ONVIF使能状态应答	


	ICE_CAMERA_CONFIG_TYPE_SET_HTTP_POST_NEW_PARAM		= 0x5380,		//!< 设置ICE_HTTP_POST_NEW_PARAM
	ICE_CAMERA_CONFIG_TYPE_SET_HTTP_POST_NEW_PARAM_RSP	= 0x5381,		//!< 设置ICE_HTTP_POST_NEW_PARAM应答
	ICE_CAMERA_CONFIG_TYPE_GET_HTTP_POST_NEW_PARAM		= 0x5382,		//!< 获取ICE_HTTP_POST_NEW_PARAM
	ICE_CAMERA_CONFIG_TYPE_GET_HTTP_POST_NEW_PARAM_RSP	= 0x5383,		//!< 获取ICE_HTTP_POST_NEW_PARAM应答


	ICE_NEW_CAMERA_SET_OLD_UPDATE_MODE_ENABLE  = 0x5384,  //!< 设置ICE_NEW_CAMERA_SET_OLD_UPDATE_MODE_ENABLE
	ICE_NEW_CAMERA_SET_OLD_UPDATE_MODE_ENABLE_RSP = 0x5385,  //!< 
	ICE_NEW_CAMERA_GET_OLD_UPDATE_MODE_ENABLE  = 0x5386,  //!< 
	ICE_NEW_CAMERA_GET_OLD_UPDATE_MODE_ENABLE_RSP = 0x5387,  //!< 

	ICE_NEW_CAMERA_SET_USER_MODEL                = 0x5388,  //!< 设置相机用户型号
	ICE_NEW_CAMERA_SET_USER_MODEL_RSP            = 0x5389,  //!< 
	ICE_NEW_CAMERA_GET_USER_MODEL				 = 0x538A,  //!< 
	ICE_NEW_CAMERA_GET_USER_MODEL_RSP            = 0x538B,  //!< 

	ICE_SET_PING_SERVER_ACTION                = 0x538C,		//!< 设置 ping 服务器 动作
	ICE_SET_PING_SERVER_ACTION_RSP            = 0x538D,		//!< 
	ICE_GET_PING_SERVER_ACTION		        = 0x538E,		//!< 
	ICE_GET_PING_SERVER_ACTION_RSP	        = 0x538F,		//!< 

	ICE_CAMERA_CONFIG_TYPE_SET_CLOUD_PARAM = 0x5390,           //!< 设置云平台参数
	ICE_CAMERA_CONFIG_TYPE_SET_CLOUD_PARAM_RSP = 0x5391,       //!< 设置云平台参数应答
	ICE_CAMERA_CONFIG_TYPE_GET_CLOUD_PARAM = 0x5392,           //!< 获取云平台参数
	ICE_CAMERA_CONFIG_TYPE_GET_CLOUD_PARAM_RSP = 0x5393,       //!< 获取云平台参数应答

	ICE_CAMERA_CONFIG_TYPE_SET_NETWORK_DIAGNOSTICS  = 0x5394,  //!< 设置 网络诊断 network diagnostics 
	ICE_CAMERA_CONFIG_TYPE_SET_NETWORK_DIAGNOSTICS_RSP = 0x5395,  //!< 
	ICE_CAMERA_CONFIG_TYPE_STOP_NETWORK_DIAGNOSTICS  = 0x5396,  //!< 停止 网络诊断 network diagnostics 
	ICE_CAMERA_CONFIG_TYPE_STOP_NETWORK_DIAGNOSTICS_RSP = 0x5397,  //!< 
	ICE_CAMERA_CONFIG_TYPE_GET_NETWORK_DIAGNOSTICS  = 0x5398,  //!< 
	ICE_CAMERA_CONFIG_TYPE_GET_NETWORK_DIAGNOSTICS_RSP = 0x5399,  //!< 

	ICE_CAMERA_CONFIG_TYPE_SET_CAMERA_ALIVETIME = 0x539A,  //!<设置试用时间
	ICE_CAMERA_CONFIG_TYPE_SET_CAMERA_ALIVETIME_RSP = 0x539B, //!<设置试用时间应答

	ICE_CAMERA_CONFIG_TYPE_GET_CAMERA_ALIVETIME = 0x539C,  //!<获取当前使用信息
	ICE_CAMERA_CONFIG_TYPE_GET_CAMERA_ALIVETIME_RSP = 0x539D, //!<获取当前使用信息应答

	ICE_CAMERA_CONFIG_TYPE_SET_TLDGATE_PARAM = 0x53AA,     //!<设置特来电道闸配置 
	ICE_CAMERA_CONFIG_TYPE_SET_TLDGATE_PARAM_RSP = 0x53AB,   //!<设置特来电道闸配置应答
	ICE_CAMERA_CONFIG_TYPE_GET_TLDGATE_PARAM = 0x53AC,     //!<获取特来电道闸配置
	ICE_CAMERA_CONFIG_TYPE_GET_TLDGATE_PARAM_RSP = 0x53AD,    //!<获取特来电道闸配置应答

	ICE_CAMERA_CONFIG_TYPE_SET_TIMEZONE = 0x53AE,                   //!<设置相机时区
	ICE_CAMERA_CONFIG_TYPE_SET_TIMEZONE_RSP = 0x53AF,
	ICE_CAMERA_CONFIG_TYPE_GET_TIMEZONE = 0x53B0,                   //!<获取相机时区
	ICE_CAMERA_CONFIG_TYPE_GET_TIMEZONE_RSP = 0x53B1,

	ICE_CAMERA_CONFIG_TYPE_SET_NTP_PARAM = 0x53B2,                  //!<设置NTP参数
	ICE_CAMERA_CONFIG_TYPE_SET_NTP_PARAM_RSP = 0x53B3,
	ICE_CAMERA_CONFIG_TYPE_GET_NTP_PARAM = 0x53B4,                  //!<获取NTP参数
	ICE_CAMERA_CONFIG_TYPE_GET_NTP_PARAM_RSP = 0x53B5,

	ICE_CAMERA_CONFIG_TYPE_SET_DISPLAY_PARAM = 0x53B6,     //!<设置V88屏显一体机屏显配置参数
	ICE_CAMERA_CONFIG_TYPE_SET_DISPLAY_PARAM_RSP = 0x53B7,
	ICE_CAMERA_CONFIG_TYPE_GET_DISPLAY_PARAM = 0x53B8,     //!<获取V88屏显一体机屏显配置参数
	ICE_CAMERA_CONFIG_TYPE_GET_DISPLAY_PARAM_RSP = 0x53B9,

	ICE_CAMERA_CONFIG_TYPE_CLEAR_ADVERT_PIC = 0x53BA,     //!<清空V88  广告图片
	ICE_CAMERA_CONFIG_TYPE_CLEAR_ADVERT_PIC_RSP = 0x53BB,
	
	ICE_CAMERA_CONFIG_TYPE_GET_SUPPORT_NEW_INTERFACE = 0x53BC, //获取支持新接口的功能模块
	ICE_CAMERA_CONFIG_TYPE_GET_SUPPORT_NEW_INTERFACE_RSP = 0x53BD, //获取支持新接口的功能模块回复

	ICE_CAMERA_CONFIG_TYPE_SET_NEW_SYSTEM_TIME			= 0x53BE,		//!< 设置相机系统时间
	ICE_CAMERA_CONFIG_TYPE_SET_NEW_SYSTEM_TIME_RSP		= 0x53BF,		//!< 设置相机系统时间应答
	ICE_CAMERA_CONFIG_TYPE_GET_NEW_SYSTEM_TIME			= 0x53C0,		//!< 获取相机系统时间
	ICE_CAMERA_CONFIG_TYPE_GET_NEW_SYSTEM_TIME_RSP		= 0x53C1,		//!< 获取相机系统时间应答
	ICE_CAMERA_CONFIG_TYPE_SET_SNAPOSD_CFG				= 0x53CE,		//!< 设置截图图片OSD参数
	ICE_CAMERA_CONFIG_TYPE_SET_SNAPOSD_CFG_RSP			= 0x53CF,		//!< 设置截图图片OSD参数应答
	ICE_CAMERA_CONFIG_TYPE_GET_SNAPOSD_CFG				= 0x53D0,		//!< 获取截图图片OSD参数
	ICE_CAMERA_CONFIG_TYPE_GET_SNAPOSD_CFG_RSP			= 0x53D1,		//!< 获取截图图片OSD参数应答
	ICE_CAMERA_CONFIG_TYPE_GET_AUDIO_DIR_FREE_SPACE 	= 0x53D6,		//!< 获取音频存放文件夹剩余空间，KB
	ICE_CAMERA_CONFIG_TYPE_GET_AUDIO_DIR_FREE_SPACE_RSP = 0x53D7,       //!< 获取音频存放文件夹剩余空间应答	
	ICE_CAMERA_CONFIG_TYPE_CLEAN_AUDIO_DIR       	= 0x53D8,			//!< 清除音频文件
	ICE_CAMERA_CONFIG_TYPE_CLEAN_AUDIO_DIR_RSP     	= 0x53D9,			//!< 清除音频文件应答	
	ICE_CAMERA_CONFIG_TYPE_UPLOAD_AUDIO_FILE       	= 0x53DA,			//!< 上传音频文件
	ICE_CAMERA_CONFIG_TYPE_UPLOAD_AUDIO_FILE_RSP    = 0x53DB,	    	//!< 上传音频文件返回

	ICE_CAMERA_CONFIG_TYPE_GET_MQTT_CFG = 0x540C, //!<获取mqtt协议
	ICE_CAMERA_CONFIG_TYPE_GET_MQTT_CFG_RSP = 0x540D,
	ICE_CAMERA_CONFIG_TYPE_SET_MQTT_CFG = 0x540E, //!<设置mqtt协议
	ICE_CAMERA_CONFIG_TYPE_SET_MQTT_CFG_RSP = 0x540F,
	ICE_CAMERA_CONFIG_TYPE_GET_MQTT_CFG_DEF = 0x5410, //!<获取默认mqtt协议参数
	ICE_CAMERA_CONFIG_TYPE_GET_MQTT_CFG_DEF_RSP = 0x5411,

	ICE_CAMERA_CONFIG_TYPE_FS_GET_TALKBACK_CFG = 0X550A,				//获取对讲配置
	ICE_CAMERA_CONFIG_TYPE_FS_GET_TALKBACK_CFG_RSP = 0X550B,			//获取对讲配置应答
	ICE_CAMERA_CONFIG_TYPE_FS_SET_TALKBACK_CFG = 0X550C,				//设置对讲配置
	ICE_CAMERA_CONFIG_TYPE_FS_SET_TALKBACK_CFG_RSP = 0X550D,			//设置对讲配置应答

	/***************以下命令号不知道为什么都从0x6001开始了***********************/
	ICE_CAMERA_CONFIG_TYPE_SET_PRODUCT_MODEL = 0x6001,//设置产品型号
	ICE_CAMERA_CONFIG_TYPE_SET_PRODUCT_MODEL_RSP = 0x6002,//设置产品型号回复
	ICE_CAMERA_CONFIG_TYPE_GET_PRODUCT_MODEL = 0x6003,//获取产品型号
	ICE_CAMERA_CONFIG_TYPE_GET_PRODUCT_MODEL_RSP = 0x6004,//获取产品型号回复

	ICE_CAMERA_CONFIG_TYPE_BIND_IO_IN_PRO = 0x6007,//绑定IO输入
	ICE_CAMERA_CONFIG_TYPE_BIND_IO_IN_PRO_RSP = 0x6008,//绑定IO输入回复
	ICE_CAMERA_CONFIG_TYPE_BIND_IO_OUT_PRO = 0x6009,//绑定IO输出
	ICE_CAMERA_CONFIG_TYPE_BIND_IO_OUT_PRO_RSP = 0x600a,//绑定IO输出回复

	ICE_CAMERA_CONFIG_TYPE_ADD_SERAIL_PRO = 0x600b,	//增加串口协议
	ICE_CAMERA_CONFIG_TYPE_ADD_SERAIL_PRO_RSP = 0x600c,	//增加串口协议回复
	ICE_CAMERA_CONFIG_TYPE_DEL_SERAIL_PRO = 0x600d,//删除串口协议
	ICE_CAMERA_CONFIG_TYPE_DEL_SERAIL_PRO_RSP = 0x600e,//删除串口协议回复
	ICE_CAMERA_CONFIG_TYPE_BIND_SERAIL_PRO = 0x6010,//绑定串口协议	
	ICE_CAMERA_CONFIG_TYPE_BIND_SERAIL_PRO_RSP = 0x6011,//绑定串口协议回复
	ICE_CAMERA_CONFIG_TYPE_GET_SERIAL_PRO_LIST = 0x6012,//获取串口协议列表
	ICE_CAMERA_CONFIG_TYPE_GET_SERIAL_PRO_LIST_RSP = 0x6013,//获取串口协议列表回复

	ICE_CAMERA_CONFIG_TYPE_GET_TIME_SYNC_CFG						= 0x61B0,//获取校时开关配置
	ICE_CAMERA_CONFIG_TYPE_GET_TIME_SYNC_CFG_RSP 					= 0x61B1,//获取校时开关配置回复
	ICE_CAMERA_CONFIG_TYPE_SET_TIME_SYNC_CFG						= 0x61B2,//获取校时开关配置
	ICE_CAMERA_CONFIG_TYPE_SET_TIME_SYNC_CFG_RSP 					= 0x61B3,//设置校时开关配置
	ICE_CAMERA_CONFIG_TYPE_GET_TIME_SYNC_CFG_DEF					= 0x61B4,//设置校时开关配置
	ICE_CAMERA_CONFIG_TYPE_GET_TIME_SYNC_CFG_DEF_RSP 				= 0x61B5,//获取校时开关默认配置
	ICE_CAMERA_CONFIG_TYPE_SET_REMCTRL_KEYFUNCTION					= 0x6204,//设置遥控器键值
	ICE_CAMERA_CONFIG_TYPE_SET_REMCTRL_KEYFUNCTION_RSP				= 0x6205,//设置遥控器键值回复
	ICE_CAMERA_CONFIG_TYPE_GET_REMCTRL_KEYFUNCTION					= 0x6206,//获取遥控器键值
	ICE_CAMERA_CONFIG_TYPE_GET_REMCTRL_KEYFUNCTION_RSP				= 0x6207,//获取遥控器键值回复

	/***************以下相机程序之间内部命令不和客户端相机冲突***********************/
	ICE_CAMERA_INNER_CONFIG_TYPE_SET_ICE_OCD_TO_VDC	= 0x9001,				//!<脱机计费上报消息
	ICE_CAMERA_INNER_CONFIG_TYPE_SET_ICE_OCD_TO_VDC_RSP	= 0x9002,		//!<?脱机计费上报消息应答

	ICE_CAMERA_CONFIG_TYPE_END                      = 0x941f,

} ICE_CAMERA_CONFIG_TYPE_E;


//NTP配置结构体
typedef struct T_SntpCfg{
	ICE_S32   iEn;            //NTP使能
	ICE_S32   iSyncPeriod;    //同步间隔，多少秒同步一次，单位秒
	ICE_S32   iSyncDiff;      //同步差值条件，相机与服务器时间相差多少秒以上才同步，单位秒
	ICE_S32   iSrvPort;       //NTP服务器端口
	ICE_S8    acSrvAddr[128]; //NTP服务器地址
	ICE_S8    acResearve[256]; 
}T_SntpCfg;

typedef struct tagT_TimeZone
{
	ICE_S8 acTimeZoneStr[32];
	ICE_S8 acResearve[256];
} T_TimeZone;

//时间信息结构体
//正常的日历日期时间表示
typedef struct T_TimeInfo{
	ICE_S32 iYear;   //年，正常年份，如2019年取值为2019
	ICE_S32 iMon;    //月，取值范围：1-12
	ICE_S32 iDay;    //日，取值范围：1-31
	ICE_S32 iHour;   //时，24小时制，取值范围：0-23
	ICE_S32 iMin;    //分，取值范围：0-59
	ICE_S32 iSec;    //秒，取值范围：0-59
}T_TimeInfo;

typedef struct T_TimeCfgInfo{
	ICE_S8 acReqSrcIp[16];//请求源IP地址串
	ICE_S8 acReqSrcDesc[16];//请求源描述串，"HX-CGI""HX-SDK""HX-USERAPP""HX-CLIENT"，其它全是客户输入
	T_TimeInfo tLocalTimeInfo;//本地时间信息
	ICE_S8 acResearve[256];
}T_TimeCfgInfo;


typedef struct{
	ICE_S32 time_sync_mode; //0 手动，1ntp,2 心跳
	ICE_S8 ntp_server[124]; 
	ICE_S32 time_sync_intervel; 
	ICE_S32 time_zone;
	ICE_S8 researve[120];
}TIME_PARAM;

//////////////////////////////////////////////////////////////////////////
#define TLD_GATE_KEY_LEN 64
#define TLD_GATE_NET_LEN 128
#define TLD_GATE_ROUTEURLLEN 256

#define TLD_GATE_MAX_ROUTESERVER_NUM 8

//配置路径
#define TLD_GATE_CONFIG "/data/config/TldGateCfg.json"

typedef struct T_TldGateCfg
{
	ICE_S32 iEn;                     //是否使能特来电道闸协议.[0,1] 0:不使能 1:使能 
	ICE_S32 iInterval;               //心跳周期,单位:秒 ，默认10s
	ICE_S32 iResendInterval;       //应急数据重传间隔,分钟数  默认30 - 1320 min，默认120min(2h)
	ICE_U8 aucDeviceKey[TLD_GATE_KEY_LEN];        //设备key
	ICE_U8 aucDeviceSecret[TLD_GATE_KEY_LEN];     //设备秘钥
	ICE_U8 aucProductKey[TLD_GATE_KEY_LEN];       //产品key
	ICE_U8 aucProductSecret[TLD_GATE_KEY_LEN];    //产品秘钥
	ICE_U8 aucRouteUrl[TLD_GATE_MAX_ROUTESERVER_NUM][TLD_GATE_ROUTEURLLEN];  // 路由服务器地址 支持多个路由地址，以|形式分隔
	ICE_S32 iOpenGateTimeout;      //开到位超时 0-600 单位s  
	ICE_S32 iCloseGateTimeout;     //关到位超时 0-600 单位s
	ICE_S32 iMode;				  //0 普通模式 1 地感模式
	ICE_S32 iCoilCheckTimeout;   //地感模式检测超时时间 范围 0-30s
	ICE_U8 aucReserved[240];             // 预留参数
}T_TldGateCfg;
//////////////////////////////////////////////////////////////////////////

#define DIAG_RESU_MAXLEN  4096*2
/*网络诊断相关参数*/
typedef struct
{
	unsigned char ucNetworkDiagCmd[100];         //客户下发网络诊断的指令 
	unsigned char ucDiagResuBuff[DIAG_RESU_MAXLEN];    //网络诊断结果输出
	unsigned char ucReserved[10];
}NETWORK_DIAGNOSTICS_PARAM;

#define CLOUD_ID_LEN 64
#define CLOUD_NET_LEN 128

typedef struct _CLOUD_CFG_PARAM_S
{
	ICE_S32 cloudEn;			//是否打开cloud 功能，默认关闭.[0,1] 0:关闭 1:开启
	ICE_S32 mode;				//工作模式.现在只有模式1=YDT
	ICE_S32 sslEn;			//SSL使能，默认不使能
	ICE_S32 sslPort;			//SSL端口，默认443
	ICE_S32 camIdType;		//camId类型.[0,1] 0:使用相机MAC地址 1:使用相机UUID
	ICE_S32 interval;			//心跳周期,单位:秒.[0,300]，0=无心跳
	ICE_S32 maxSendCnt;		//发送最大次数, 1-3，默认为:2
	ICE_S32 fullImgEn;		//是否发送全景图；
	ICE_S32 miniImgEn;		//是否发送车牌特写图；
	ICE_S32 ioInEn;			//输入IO状态上报使能
	ICE_U8 ioInNum[8];		//指定上报输入IO，真有效，ioInNum[0]对应输入IO1，ioInNum[1]=IO2,ioInNum[2]=IO3,ioInNum[3]=IO4，4-7预留的
	ICE_U8 parkId[CLOUD_ID_LEN];		//停车场id,只支持英文、数字、'-',like:GD-SZ-A000001

	ICE_U8 cloudDomain[CLOUD_NET_LEN];	// 云平台的域名，like:www.baidu.com
	ICE_U8 path[CLOUD_NET_LEN];		// 云平台跟随的路径
	ICE_S32 port;				// 云平台访问端口，默认为：80
	ICE_S32 syncTimeEn;		// 云平台时间校时使能
	ICE_S32 syncTimeOffset;	// 校时偏差条件，单位秒，1-900,偏差大于该值则校时

	ICE_S32 osEn;				// 是否打开对象存储功能，默认关闭.[0,1] 0:关闭 1:开启
	ICE_S32 osType;			// 储存协议类型，0=aliyun,1=tencentyun,2=baiduyun,3=。。。。
	ICE_U8 osDomain[CLOUD_NET_LEN];	// 对象存储的域名，like:bucket.endpoint
	ICE_S32 iPicUploadType;             // 图片上传方式 0:分开上传  1:一起上传

	ICE_U8 reserved[252];	// 预留参数
	ICE_S32 extParamSize;		// CLOUD_CFG_PARAM_S 为主参数，辅助参数全部放在后面，每个模式如有需要，均可配套辅助参数，达到不动主参数，同时又支持额外定制。默认:0
} CLOUD_CFG_PARAM_S;

typedef struct tagT_CloudM2CfgParam
{
	ICE_S8 key[64];
	ICE_U8 reserved[128]; // 预留参数
} T_CloudM2CfgParam;

typedef struct tagT_CloudM3CfgParam
{
	ICE_S8 accessKey[CLOUD_ID_LEN]; // 模式3时，OSS_ACCESS_KEY
	ICE_S8 accessSecret[CLOUD_ID_LEN];// 模式3时，OSS_ACCESS_KEY_SECRET
	ICE_U8 reserved[128]; // 预留参数
} T_CloudM3CfgParam;

typedef struct T_CloudM4CfgParamV1
{
	ICE_S8 acAccessKey[CLOUD_ID_LEN];	   // 模式4时，OSS_ACCESS_KEY
	ICE_S8 acAccessSecret[CLOUD_ID_LEN]; // 模式4时，OSS_ACCESS_KEY_SECRET
} T_CloudM4CfgParamV1;

typedef struct
{
	int InVolume; //0- 10
	int OutVolume;//0- 10
	int as32Reserved[4]; //预留参数

} ICE_TALK_BACK_VOLUME_PARAM;

//!配置脱机语音播报类型 
typedef struct
{
	ICE_U32 u32Mode;             //播报模式： 0 不播报, 1 播报(原来的欢迎光临/一路顺风), 2 播报+匹配白名单   默认 2
	ICE_U32 u32Broadcast_order;     //播报顺序   0 不播报车牌  1后播报车牌  2 先播报车牌再播报其他信息  默认 2
	ICE_U32 u32Reserved[15];           
} OfflineAoParam;

//接收存储的终端mac list 类型
typedef struct {
  ICE_S32 mac_list_size;  //  list数量
  ICE_S8 phone_mac_list[100][18];
  ICE_S8 reserved[50*18];
} ICE_Phone_Mac_List;


//! 配置数据缓存
typedef union
{
	ICE_U8 au8Buffer[ICE_BUF_SIZE_CONFIG];		//!< 配置数据缓存
} ICE_CONFIG_DATA_INTERNAL_U;

//! \ingroup group_communication
//! 配置数据头和数据缓存
typedef struct  
{
	ICE_OPER_DATA_S stHead;					//!< 操作头
	ICE_CONFIG_DATA_INTERNAL_U unData;		//!< 配置数据
} ICE_CONFIG_DATA_S;

typedef struct
{
 ICE_U8 u8ModeNo;
 ICE_U8 u8Reserved[3];
 ICE_U32 u32BeginTime;//该值是每天00:00:00到设置当天生效时刻的分钟数
 ICE_U32 u32Interval;//有效时间差
 ICE_U8 u8Reserved1[52];
}ICE_SCENE_MODE_ST;

///////////////////////////////////////////////////////////////////////////////////////////////////
//! \ingroup group_communication
//! 编码视频流数据类型
typedef enum
{
	ICE_VIDEO_STREAM_TYPE_BASE 						= 0x6000,		//!< 编码视频流数据类型基础字段
	ICE_VIDEO_STREAM_TYPE_VENC_H264					= 0x6001,		//!< H264编码
	ICE_VIDEO_STREAM_TYPE_VENC_MJPEG				= 0x6002,		//!< MJPEG编码
	ICE_VIDEO_STREAM_TYPE_VENC_MPEG2				= 0x6004,		//!< MPEG2编码
	ICE_VIDEO_STREAM_TYPE_VENC_MPEG4				= 0x6008,		//!< MPEG4编码
	ICE_VIDEO_STREAM_TYPE_END						= 0x6009,		
}ICE_VIDEO_STREAM_E;

//led显示用户自定义信息 结构体
typedef struct{
	char default_data[64];  //无车辆时
	char blacklist_data[64]; //黑名单
	char tmp_data[64];      // 临时车辆
	char reserve[256];
} Led_Display_Pro1_Param;

// 串口控制卡公共基本参数
typedef struct {
	int serial_card_type;		//屏的类型Led 屏，语音屏，0 表示led，1表示语音屏
	int serial_card_addr;		//具体控制卡地址1~255
	int reserved[16];
}Led_Card_Serial_Common_param;

//led控制卡子协议2之led屏参数结构体
typedef struct {
	int address;			//led屏的地址
	int mainsection;		//主扇区地址，范围00~199
	int subsection;			//子扇区地址，范围201~219
	int subsection_nor;		//子扇区地址，范围201~219，主要用于非授权车
	int enter_mode;			//进入模式，范围00~23 
	int stop_time;			//停留时间
	int stop_mode;			//停留模式	范围00~13
	int exit_mode;			//退出模式	范围00~23
	unsigned char maintext[64];		//主策略某个扇区的显示，主扇区存放内容
	unsigned char subtext[64];		//子策略某个扇区的显示，子扇区存放内容
	unsigned char subtext_nor[64];   //主要用于非授权车显示内容
	int reserved[16];
} Led_Card_2_Display_Cfg_param;

//led控制卡子协议2之附属的语音屏结构体
typedef struct {
	int address;			//语音屏地址 1~255
	int modify_addr_enable;	//修改语音屏地址使能，默认 0，不修改
	int modify_addr;		//修改语音屏地址
	unsigned char whitelist_broadcasttext[50]; //授权车，语音屏播报内容 协议规定最大50字节
	unsigned char normal_broadcasttext[50];	  //非授权车语音屏播报内容	
	unsigned char reserved[20];
}Led_Card_2_attach_broadcast_cfg_param;

//led控制卡子协议2 结构体
typedef struct {
	int relay_time;											//白名单时继电器闭合时间 客户350-2000
	int change_addr_enable;									//修改led屏地址使能，默认 0，不修改
	int change_addr_led;										//修改led屏的地址
	Led_Card_2_Display_Cfg_param led_protol_2_card[3];		//0 欢送用语led屏参数,//1 日期时间led屏参数,// 2车牌号码led屏参数
	Led_Card_2_attach_broadcast_cfg_param broadcast_card;	//附属语音屏参数
	int reserved[20];
}Led_Card_2_total_cfg_param;

//led控制卡子协议2 进入模式
typedef enum {
	LED_CARD_2_IN_INSTANT_DISPLAY			= 0x00,		//立即显示
	LED_CARD_2_IN_RIGHT_TO_LEFT				= 0x01,		//从右向左移
	LED_CARD_2_IN_LEFT_TO_RIGHT				= 0x02,		//从左向右移
	LED_CARD_2_IN_DOWN_TO_UP				= 0x03,		//从下向上移
	LED_CARD_2_IN_UP_TO_DOWN				= 0x04,		//从上向下移
	LED_CARD_2_IN_PULL_CURTAIN_TO_DOWN		= 0x05,		//向下拉帘式
	LED_CARD_2_IN_PULL_CURTAIN_TO_UP		= 0x06,		//向上拉帘式
	LED_CARD_2_IN_PULL_CURTAIN_TO_LEFT		= 0x07,		//向左拉帘式
	LED_CARD_2_IN_PULL_CURTAIN_TO_RIGHT		= 0x08,		//向右拉帘式
	LED_CARD_2_IN_BACK_LIGHT				= 0x09,		//反亮
	LED_CARD_2_IN_SPACE_OPERATION			= 0x0A,		//无操作
	LED_CARD_2_IN_MEDIUM_SPEED_LEFT			= 0x0B,		//中速左移
	LED_CARD_2_IN_MEDIUM_SPEED_RIGHT		= 0x0C,		//中速右移
	LED_CARD_2_IN_VERBATIM_DISPLAY			= 0x0D,		//逐字显示
	LED_CARD_2_IN_OPEN_GATE_LEFT			= 0x0E,		//向左开栅
	LED_CARD_2_IN_OPEN_GATE_RIGHT			= 0x0F,		//向右开栅
	LED_CARD_2_IN_SNOWFLAKE_DISPLAY			= 0x10,		//雪花出现
	LED_CARD_2_IN_ROW_DISPLAY				= 0x11,		//隔行出现
	LED_CARD_2_IN_COL_DISPLAY				= 0x12,		//隔列出现
	LED_CARD_2_IN_SLOW_SPEED_LEFT			= 0x13,		//慢速左移
	LED_CARD_2_IN_SLOW_SPEED_RIGHT			= 0x14,		//慢速右移
	LED_CARD_2_IN_SERIES_DISPLAY			= 0x15,		//连续移动
	LED_CARD_2_IN_NONE_OPERATION			= 0x16,		//无操作
	LED_CARD_2_IN_SLOW_SPEED_SERIES_DISPLAY = 0x17,		//慢速连续移动
	LED_CARD_2_IN_MAX_LED_BS_DISPLAY	
}led_card_2_insert_mode;

//led控制卡子协议2 停留模式
typedef enum {
	LED_CARD_2_REMAIN_MODE0		= 0x00,					//停留
	LED_CARD_2_REMAIN_MODE1		= 0x01,					//停留 1/10
	LED_CARD_2_REMAIN_MODE2		= 0x02,					//停留 1/100
	LED_CARD_2_FAST_FLASH		= 0x03,  				//快速闪烁
	LED_CARD_2_MIDEUM_FLASH		= 0x04,					//中速闪烁
	LED_CARD_2_SLOW_FLASH		= 0x05,					//慢速闪烁
	LED_CARD_2_SINGLE_FLASH		= 0x06,					//单次闪烁
	LED_CARD_2_ENGLISH_DATE		= 0x07,					//英文日期
	LED_CARD_2_ENGLISH_TIME		= 0x08,					//英文时间
	LED_CARD_2_CHINESE_DATE		= 0x09,					//中文日期
	LED_CARD_2_CHINESE_TIME		= 0x0A,					//中文时间
	LED_CARD_2_CONTROL_MODE		= 0x0B,					//控制
	LED_CARD_2_LOOP_MODE		= 0x0C,					//循环
	LED_CARD_2_TMPREATURE_MODE  = 0x0D,					//温度
	LED_CARD_2_MAX_STOP_DISPLAY_MODE
	
}led_card_2_stop_display_mode;

//led控制卡子协议2 退出模式
typedef enum {
	LED_CARD_2_EXIT_INSTANT_DISAPPEAR			= 0x00,		//立即退出
	LED_CARD_2_EXIT_RIGHT_TO_LEFT				= 0x01,		//从右向左移
	LED_CARD_2_EXIT_LEFT_TO_RIGHT				= 0x02,		//从左向右移
	LED_CARD_2_EXIT_DOWN_TO_UP					= 0x03,		//从下向上移
	LED_CARD_2_EXIT_UP_TO_DOWN					= 0x04,		//从上向下移
	LED_CARD_2_EXIT_PULL_CURTAIN_TO_DOWN		= 0x05,		//向下拉帘式
	LED_CARD_2_EXIT_PULL_CURTAIN_TO_UP			= 0x06,		//向上拉帘式
	LED_CARD_2_EXIT_PULL_CURTAIN_TO_LEFT		= 0x07,		//向左拉帘式
	LED_CARD_2_EXIT_PULL_CURTAIN_TO_RIGHT		= 0x08,		//向右拉帘式
	LED_CARD_2_EXIT_BACK_LIGHT					= 0x09,		//反亮
	LED_CARD_2_EXIT_SPACE_OPERATION				= 0x0A,		//无操作
	LED_CARD_2_EXIT_MEDIUM_SPEED_LEFT			= 0x0B,		//中速左移
	LED_CARD_2_EXIT_MEDIUM_SPEED_RIGHT			= 0x0C,		//中速右移
	LED_CARD_2_EXIT_VERBATIM_DISAPPEAR			= 0x0D,		//逐字消失
	LED_CARD_2_EXIT_OPEN_GATE_LEFT				= 0x0E,		//向左开栅
	LED_CARD_2_EXIT_OPEN_GATE_RIGHT				= 0x0F,		//向右开栅
	LED_CARD_2_EXIT_SNOWFLAKE_DISAPPEAR			= 0x10,		//雪花消失
	LED_CARD_2_EXIT_ROW_DISAPPEAR				= 0x11,		//隔行消失
	LED_CARD_2_EXIT_COL_DISAPPEAR				= 0x12,		//隔列消失
	LED_CARD_2_EXIT_SLOW_SPEED_LEFT				= 0x13,		//慢速左移
	LED_CARD_2_EXIT_SLOW_SPEED_RIGHT			= 0x14,		//慢速右移
	LED_CARD_2_EXIT_SERIES_DISAPPEAR			= 0x15,		//连续移动
	LED_CARD_2_EXIT_NONE_OPERATION				= 0x16,		//无操作
	LED_CARD_2_EXIT_SLOW_SPEED_SERIES_DISAPPEAR = 0x17,		//慢速连续移动
	LED_CARD_2_EXIT_MAX_LED_BS_DISPLAY
}led_card_2_exit_mode;

//获取相机版本
typedef struct
{
	char szAppVersion[128];   //相机app版本
	char szAlgoVersion[256];  //相机算法版本
	int szIsEnc;              //相机是否加密
	char szAppTime[16];       //版本时间
	char szReserved[1024];    //预留
} ICE_CameraInfo;

//日志开关
typedef struct{
	ICE_U8 u8AppLog;		  //是否输出app日志
	ICE_U8 u8AlgoLog;		  //是否开启算法日志	
	ICE_U8 u8AlgoTimeLog;	  //是否开启耗时统计日志
	ICE_U8 u8DebugLog;		  //客户端开启重要日志, debug 级别
	ICE_U8 u8NomalLog;		  //客户端开启普通日志, info notice warning 级别
	ICE_U8 u8NetRealTimeLog;  //是否开启网络实时日志
	ICE_U8 u8SaveLogToSD;	  //是否把日志保存到SD卡
	ICE_U8 u8NetLogAddr[16];  //网络实时日志的IP地址
	ICE_U8 u8Rs485;
	ICE_U8 u8HttpPost;
	ICE_U8 u8LogLevel;
	ICE_U8 reserved[38];   //reserved
}ICE_LOG_CONFIG;

#define NET_LOG_LEVEL_DBG   0x05
#define NET_LOG_LEVEL_INF   0x04
#define NET_LOG_LEVEL_NOT   0x03
#define NET_LOG_LEVEL_WAR   0x02
#define NET_LOG_LEVEL_ERR   0x01
#define NET_LOG_LEVEL_FAT   0x00

//获取定制版本
typedef struct 
{
	ICE_U8 u8device_model[16];
	ICE_U8 reserved[48];
}ICE_DEVICE_INFO;

/**********************************脱机计费组播设置************************************************/
/* 组播配置*/
typedef struct
{
	ICE_U8	ucEnabled;      /* 组播使能*/
	ICE_U16	usOfflinePort;  /* 组播端口*/
	ICE_U32	uiIP;			/* 组播地址*/
	ICE_U8	aucReserved[10];
}ICE_OFFLINE_MULTICAST_CONFIG;
/******************************脱机计费组播设置*************************************************/


/******************************脱机计费LED屏设置*************************************************/
//脱机计费相关结构体
#define MAX_LED_CONTENT   64     //一行最多字符
#define MAX_LED_COUNT     4      //最多屏幕


typedef enum
{
	LED_SCREEN_1 = 0,    //车牌协议1
	LED_SCREEN_2,        //透明串口
	LED_SCREEN_3,        //LED屏控
	LED_SCREEN_4,        //混合模式
	LED_SCREEN_5,        //车牌协议2
	LED_SCREEN_6,        //车牌协议3 
	LED_SCREEN_7,        //车牌协议4 
	LED_SCREEN_8,        //rs232 wifi探针协议
	LED_SCREEN_9,        //车牌协议5
	LED_SCREEN_10,       //车牌协议6
	LED_SCREEN_11,
	LED_SCREEN_12,
	LED_SCREEN_13,
	LED_SCREEN_14,
	LED_SCREEN_15,
	LED_SCREEN_16,
	LED_SCREEN_17, 
	/***************新协议支持脱机计费***************************/
	LED_SCREEN_18,    //车牌协议7
	LED_SCREEN_19, 
	LED_SCREEN_20, 
	LED_SCREEN_21, 
	LED_SCREEN_22, 
	LED_SCREEN_23,
	LED_SCREEN_MAX
}E_LedScreenType;

typedef enum
{
	COLOR_TYPE_RED =0,  //红
	COLOR_TYPE_GREEN,   //绿
	COLOR_TYPE_YELLO,   //黄
	COLOR_TYPE_BLUE ,   //蓝
	COLOR_TYPE_WHITE,   //白
	COLOR_TYPE_BLACK,   //黑
	COLOR_TYPE_OTHER,   //其他
	COLOR_TYPE_YELLOW_GREEN, //黄绿
	COLOR_TYPE_ALL,      //全部
}E_ColorType;//颜色类型

typedef enum
{
	LED_SUB_MOD_VEH_PLATE=0,/*车牌显示*/
	LED_SUB_MOD_VEH_WELCOME,/*欢迎语显示*/
	LED_SUB_MOD_VEH_PAY,  /*停车付费显示*/
	LED_SUB_MOD_VEH_TIME, /*停车时间显示*/
	LED_SUB_MOD_VEH_PERIOD, /*月租有效期显示*/
	LED_SUB_MOD_TIME,/*时间显示，格式:XXXX年XX月XX时XX分*/
	LED_SUB_MOD_VEH_LEFT,/*剩余停车位显示*/
	LED_SUB_MOD_CUSTOM,  /*自定义内容显示*/
	LED_SUB_MOD_MAX,
}E_SubLedMode;

typedef struct
{
	ICE_U8   ucContentEnable;               //是否时间  0不支持自定义 1支持
	ICE_U8   ucTimeEnable;                  //是否自定义  0不显示时间   1支持
	ICE_U8   ucInterval;					//时间间隔  s秒
	ICE_U8   aucContent[MAX_LED_CONTENT];   //自定义字符   GB2312，自定义模式有效
	ICE_U8   ucColor;                //颜色
	ICE_U8   ucLeftVehEnable;               //是否余位 0不支持自定义 1支持
	ICE_U8   aucReserved[9];               //保留
}T_SubLedSetup;   //闲时显示

typedef struct
{
	ICE_U8   ucContentEnable;               //是否自定义		  0不支持自定义 1支持
	ICE_U8   ucVehTypeEnable;               //是否输出车辆类型    0不支持 1支持
	ICE_U8   ucPlateEnable;                 //是否显示车牌        0不显示 1显示
	ICE_U8   ucLeftDaysEnable;              //是否显示剩余天数    0不显示 1显示
	ICE_U8   ucParkPay;                     //是否停车计费        0不显示 1显示  
	ICE_U8   ucParkLastTime;                //是否停车时长        0不显示 1显示   
	ICE_U8   ucTmpCardColor;                //临时车颜色
	ICE_U8   ucMonthCardColor;              //月卡车颜色
	ICE_U8   aucContent[MAX_LED_CONTENT];   //自定义字符   GB2312，自定义模式有效
	ICE_U8   aucReserved[10];               //保留
}T_M_SubLedSetup;  //忙时显示

typedef struct
{
	ICE_U8   ucContentEnable;               //是否自定义		  0不支持自定义 1支持
	ICE_U8   ucVehTypeEnable;               //是否输出车辆类型    0不支持 1支持
	ICE_U8   ucPlateEnable;                 //是否显示车牌        0不显示 1显示
	ICE_U8   ucLeftDaysEnable;              //是否显示剩余天数    0不显示 1显示
	ICE_U8   ucParkPay;                     //是否听车计费        0不显示 1显示  
	ICE_U8   ucParkLastTime;                //是否听车时长        0不显示 1显示   
	ICE_U8   ucWelorByeEnable;              //是否播报欢迎\欢送语 0不播报 1播报
	ICE_U8   aucWelorByeContent[MAX_LED_CONTENT];   //欢送语   GB2312，
	ICE_U8   aucSelfContent[MAX_LED_CONTENT];   //自定义字符   GB2312，自定义模式有效
	ICE_U8   aucReserved[10];               //保留
}T_M_AudioLedSetup;  //忙时语音播报

typedef struct   //脱机计费LED
{
	E_LedScreenType    sreenType;                    //屏显协议类型
	ICE_U32            screenMode;                   //屏显模式 0脱机使能 1强制使能 2不使能
	ICE_U32            cameraType;                   //相机类型    1 入口  2出口
	ICE_U8             ucAudioEnable;                //是否语音播报

	ICE_U8             ucReserved[3];
	T_SubLedSetup      atSubLedInIdle[MAX_LED_COUNT];//入口空闲
	T_M_SubLedSetup   atSubLedInBusy[MAX_LED_COUNT];//入口忙
	T_M_AudioLedSetup atSubLedInBusyAudio;          //入口忙语音播报内容
	T_SubLedSetup      atSubLedOutIdle[MAX_LED_COUNT];//出口空闲
	T_M_SubLedSetup   atSubLedOutBusy[MAX_LED_COUNT];//出口忙
	T_M_AudioLedSetup atSubLedOutBusyAudio;         //出口忙语音播报内容
	ICE_U32            uc485ctrlEnable;              //485控制是否开启   1     0不开启
	ICE_U32            ucLeftVehPlace;               //车位剩余数

	ICE_U16			   FK_password;      //方控加密密码
	ICE_U8             ucFKEncipherment; //方控协议是否加密
	ICE_U8             aucReserved[89];  //保留
}ICE_OFFLINE_LED_CONFIG;
/******************************************LED屏设置******************************************************/



/********************************脱机计费规则********************************************************/
#define MAX_PAY_ITEM           2      //最大付费策略类型
#define MAX_TIMESECTION_NUM    3      //最大策略组
#define MAX_PARTTIME_SET_NUM   40     //最大时段设置组

typedef enum
{
	PAY_MODE_UNKNOW = 0,
	PAY_MODE_ONTIME,       /*按时计费 */
	PAY_MODE_TIMES,        /*按次计费 */
	PAY_MODE_TIME_SECTION,/*分段计费 */
	PAY_MODE_PARTTIME,/*查表计费 */    //分时计费
	PAY_MODE_MAX
}E_PayMode;   /*计费模式*/

typedef enum
{
	STRATEGY_TYPE_UNKNOW = 0,
	STRATEGY_TYPE_NOPAY, //不收费
	STRATEGY_TYPE_CYCLE,//按一个周期收费
	STRATEGY_TYPE_BYTIME,//根据时长收费
	STRATEGY_TYPE_MAX
}E_StrategyType;  /*不足一个周期的计费策略*/

typedef struct
{
	ICE_U8	ucEnable;
	ICE_U16	usCyclePay;/* 周期收费金额*/
	ICE_U16	usStartPay;/* 起步金额*/
	ICE_U16	usFreeTime;/* 免费时长*/
	ICE_U16	usCycleTime;/* 计费周期*/
	ICE_U16	usStartTime;/* 起步时长*/
	ICE_U16	usTotalPreDay;/* 封顶金额*/
	ICE_U8	aucReserved[10]; //保留
}T_OnTimePay;  /*按时收费*/

typedef struct
{
	ICE_U8	ucEnable;
	ICE_U8	ucMaxTime;/*封顶次数*/
	ICE_U16	usPayOne;/*一次收费金额*/
	ICE_U16	usFreeTime;/*免费时长*/
	ICE_U16	usFreeStartTime;  /*免费开始时间，以分钟为单位*/
	ICE_U16	usFreeEndTime; /*免费结束时间，以分钟为单位*/
	ICE_U8	aucReserved[10]; //保留
}T_TimesPay; /*按次收费*/

typedef struct
{
	ICE_U8	ucEnable;
	ICE_U16	usCyclePay;/* 周期收费金额*/
	ICE_U16	usStartPay;/* 起步金额*/
	ICE_U16	usFreeTime;/* 免费时长*/
	ICE_U16	usCycleTime;/* 计费周期*/
	ICE_U16	usStartTime;/* 起步时长*/
	ICE_U16	usTotalPreDay;/* 时段封顶金额*/
	ICE_U16	usSectionStartTime;  /*时段开始时间，以分钟为单位*/
	ICE_U16	usSectionEndTime;/*时段结束时间，以分钟为单位*/
	ICE_U8	aucReserved[10];  //保留
}T_TimeSectionPay;	/*按时段收费*/

typedef struct  
{
   ICE_U16  parkTime;  /*停车时长*/
   ICE_U16  usPay;     /*金额*/
}SetionSet;

typedef struct 
{
	ICE_U16		usCyclePayMax;  /* 周期最高收费金额*/
	ICE_U16		usFreeTime;		/* 免费时长*/
	SetionSet   usPartTime[MAX_PARTTIME_SET_NUM]; /*时段设置*/ 
	ICE_U8		aucReserved[10];  //保留
}T_PartTimesPay;


typedef struct   //脱机计费规则
{
	ICE_U32           offEnable;		//脱机使能 0脱机使能 1强制使能 2不使能
	ICE_U32		      ExtranceRule;     //开闸配置 入口临时车            0不开启 1开启  
	ICE_U32			  ExitRule;		    //开闸配置 出口临时车计费0放行   0不开启 1开启 

	E_PayMode		  ucRuleMode; 		//计费模式
	E_StrategyType	  ucStrategyType;	//计费策略
	ICE_U16			  usTimeLength;		//周期不足计费时间

	T_OnTimePay       atOnTimePay[MAX_PAY_ITEM]; //按时计费  小车atOnTimePay[0]  大车atOnTimePay[1] 
	T_TimesPay		  atTimesPay[MAX_PAY_ITEM];  //按次计费  小车atTimesPay[0]   大车atTimesPay[1] 
	T_TimeSectionPay  atTimeSectionPay[MAX_PAY_ITEM*MAX_TIMESECTION_NUM];  //按时段计费 0,1,2小车 3,4,5大车
    T_PartTimesPay    atPartTimePay;             //分时计费

	ICE_U8			  aucReserved[30];
}ICE_OFFLINE_CHARGE_RULE;
/********************************脱机计费规则********************************************************/


/*********************************脱机计费数据上报**********************************************************/
typedef struct    //计费数据上报
{
	E_PayMode		  ucRuleMode; 		//计费模式
	ICE_U8			  vehicleType;      //车辆类型
	ICE_U32			  usTotalMoney;		//付费金额
	ICE_U32           usParkingTime;    //停车时间
	ICE_U32           usRecordID;       //记录id
	ICE_U8            usVehiclePlate[16];//车牌号
	ICE_U8            reserved[20];     //保留
}ICE_VEHPAY_RSP;


typedef enum  
{
	ICE_CAMERA_OFFLINE_PAY_HEARTBEAT		= 0x4001,		//!< 脱机计费数据上报心跳包
	ICE_CAMERA_OFFLINE_PAY_HEARTBEAT_RSP	= 0x4002,		//!< 脱机计费数据上报心跳包应答

	ICE_CAMERA_OFFLINE_PAY_VEHICLE_INFO		= 0x4003,		//!< 脱机计费上报信息
	ICE_CAMERA_OFFLINE_PAY_VEHICLE_INFO_RSP	= 0x4004,		//!< 脱机计费上报信息应答

}ICE_PAYRULE_TYPE_E;
/****************************************************************************************************/

typedef struct
{
	unsigned char ucType;  /*导出信息内容，0为车辆在场信息表*/
	char aucLplPath[256];
}T_GetPrensentVehInfo;


/**************************************主从模式结构体****************************************/
typedef struct __MAIN_SUB_MODE
{
	ICE_U32 enable;  // 0 不使能， 1 使能
	ICE_U32 status;// 1 两个同时上传， 2 比较置信度上传.
	ICE_U32 msec;   //主从相机等待抓拍结果时间(ms)  默认为500.
	ICE_U8  ip_addr[16]; // 辅相机ip地址， enable 为1时有效。
	ICE_U8  reserved[32];// 保留
}ICE_MAIN_SUB_MODE_INFO;

typedef struct  
{
	ICE_S8 szDeviceType[32];
	ICE_S8 szDeviceMac[16];
	ICE_S8 szDeviceVersion[256];
	ICE_S8 szReserve[128];
}ICE_DEVICE_PARAM;



typedef struct tagT_ProductInfo
{
	ICE_S8 ProductModel[128];
	ICE_S8 HardwareModel[128];
} T_ProductInfo;

/** @brief 开关量输入 */
typedef enum tagE_DevAlarmInMode
{
	AlarmInMode_Default,	   //默认功能不予处理 IO输入控制对讲也包含在内[IO状态变化 上传到平台，平台下发对讲命令进行对讲]
	AlarmInMode_Hdtrigger,     //作为线圈触发功能 附加针对线圈和混合触发进行二次开闸
	AlarmInMode_SecondGate,    //作为二次开闸功能 只针对视频模式
	AlarmInMode_IoRelateGate,  //IO输入关联开闸
	AlarmInMode_Count
}E_DevAlarmInMode;

typedef struct tagT_DevAlarmIn
{
	ICE_S32 Io_num;
	ICE_S32 Type; //报警输入的报警类型 0 常开 1常闭。
	E_DevAlarmInMode 	  Io_mode;
}T_DevAlarmIn;

typedef enum tagE_DevAlarmOutMode
{
	AlarmOutMode_None = 0,
	AlarmOutMode_StrobeLight,	//爆闪灯
	AlarmOutMode_OpenGate, 		//开闸
	AlarmOutMode_SwitchLight, 	//外部闪光灯
	AlarmOutMode_Intercom		//对讲 
}E_DevAlarmOutMode;
//绑定io输出
typedef struct tagT_DevAlarmOutCfg
{
	ICE_S32 Io_num;
	E_DevAlarmOutMode 	  Io_mode;
}T_DevAlarmOutBindCfg;

typedef struct tagT_UartOperPro
{
	ICE_S8 szProtocolName[32];	//协议名字
	ICE_S32 len;				//
	ICE_S8 res[128];
} T_UartOperPro;

typedef struct tagT_UartBindPro
{
	ICE_S32 ProId;				//串口ID [0-1]
	ICE_S8 szProtocolName[32];	//协议名字
} T_UartBindPro;

/** @brief 协议名称最大长度*/
#define MaxProtocolNameLen    31
/** @brief 协议最大数量 */
#define MaxProtocolNum    256
/** @brief 外设类型 */
typedef enum tagE_PeripheralType
{
	Dpt_Uart,   /**< 串口 */
	Dpt_Rs232,  /**< RS232 */
	Dpt_Rs485,  /**< RS485 */
	Dpt_Eth,    /**< 网口 */
	Dpt_USB,    /**< usb */
	Dpt_Sd,     /**< sd */
	Dpt_Key,   /**< 按键 */
	Dpt_PluckSwitch,    /**< 拔码开关 */
	Dpt_IO,     /**< IO */
	Dpt_All,  /**< 全部 */
} E_PeripheralType;
/**< 中控协议名称 */
typedef struct tagT_ProtocolInfo
{
	E_PeripheralType ePerType;                 /**< 外设类型 */
	ICE_S8 szProtocol[MaxProtocolNameLen + 1];  /**< 协议名称 */
} T_ProtocolInfo;
/**< 中控协议列表 */
typedef struct tagT_ProtocolList
{
	ICE_S32 uiNum;
	T_ProtocolInfo atList[MaxProtocolNum];   /**< 协议列表 */
} T_ProtocolList;

typedef struct
{
	int alarm_in_type_sec; //报警输入2 的报警类型 0 常开1常闭
	int which_for_hardtriger; //地感信号选那个报警输入0 是选第一组，1选第二组
	int alarm_in_type_third; //报警输入3 的报警类型 0 常开1常闭
	int alarm_in_type_fourth; //报警输入4 的报警类型 0 常开1常闭
	int related_talkbacks;  //是否关联语音对讲使用与的关系来判断关联项，目前只支持IO2 IO3 IO4
	int u32Researve[17];
}ALARM_IN_EXT;

#define NETADDR_LEN (64)
typedef struct 
{
	ICE_S8 talk_status;  //0;对讲连接成功，返回ip。  -1，已经在对讲中，返回对讲ip
	ICE_U8 link_netaddr[NETADDR_LEN];
	ICE_U8 reserved[48];
}ICE_TALK_INFO;

typedef struct
{
	int key_value; //物理按键的值
	int talk_state;  //对讲状态 0 普通非对讲状态， 1， 触发对讲  2，正在对讲 3,拒绝对讲，talk_ip_addr为拒绝对讲ip
	char talk_ip_addr[NETADDR_LEN];//连接管理终端ip
	char reserevd[20];
}TalkState;

typedef struct
{
	unsigned char ucUID[32];
	unsigned char ucReserved[32];
}UID_PARAM;

typedef struct
{
	ICE_U8 u8UserModel[64];  //用户型号
	ICE_U8 u8Reserved[32]; 
} UserModelParam;

typedef struct T_OsdInfoCfg{
	ICE_S32	iEnable;	//是否使能,0不使能，1使能
	ICE_S32 iLocation;	//0左上,1中上，2右上,3左下,4中下,5右下（注：单行显示时，位置只能是左上或者左下，且需一致）
	ICE_S32 iType;		//0日期,1时间,2日期+时间,3识别结果,4设备名称,5出入口类型,6自定义内容
	char acCustomInfo[MAX_OSD_TEXT];//自定义信息，UTF8编码，最长60byte
	char acResrv[64];//预留
}T_OsdInfoCfg;

typedef struct T_SnapOsdCfg{
	ICE_S32 ibgColorMode;	//0 背景透明，1 背景黑色
	ICE_S32 iDateMode;		//0 yyyy/mm/dd ,  1 yyyy年mm月dd日
	ICE_S32 iFontSize;		//0 小，1 中, 2 大,默认为中，在540P 以下，中会转换为小
	ICE_S32 iLineMode;		//0多行显示，1单行显示
	T_OsdInfoCfg tOsdInfoCfg[MAX_CUSTOM_OSD_LINE_NUM];//osd内容，最大支持6行
	char acResrv[128];//预留
}T_SnapOsdCfg;

typedef struct T_CamInfo{
	ICE_U32 uiCamType;//相机类型 0入口 1出口
	ICE_U8 aucCamName[64];//相机名称
	ICE_U8 aucResrv[256];
}T_CamInfo;


typedef struct T_User{
	ICE_U8 aucUseName[64];//用户名
	ICE_U8 aucPasswd[64];//密码
	ICE_U8 aucUserId[32];//用户ID
	ICE_U32 uiPrivilege;//权限 0:管理员 1:操作员 2:观察员
	ICE_U8 aucResrv[32];
}T_User;

typedef struct T_UserList{
	T_User atUser[16];
	ICE_U32 uiUserCnt;//用户个数
	ICE_U8 aucResrv[256];
}T_UserList;

#define MAX_ENCODER_NUM 4
typedef struct T_SingleEncoderParam{
	ICE_U32 uiChannel;//码流类型 0:主码流 1:子码流
	ICE_U32 uiWidth;//宽
	ICE_U32 uiHeight;//高
	ICE_U32 uiEncMode;//编码方式 0:h264 1:mjpeg
	ICE_U32 uiFps;//帧率5,8,12,25,30
	ICE_U32 uiRateCtrl;//0变码率 1定码率
	ICE_U32 uiVideoQuality;//视频质量 0最流畅 1较流畅 2流畅 3中等 3清晰 4较清晰 5最清晰
	ICE_U32 uiMaxBitRate;//码流上限 512,1024,2048,4096
	ICE_U8 aucResrv[64];
}T_SingleEncoderParam;

typedef struct T_EncoderParam
{
	ICE_U32 uiEncoderCnt;//编码器配置数量
	T_SingleEncoderParam tEncoder[MAX_ENCODER_NUM];
	ICE_U8 aucResrv[256];
}T_EncoderParam;

typedef struct T_GpioInParam
{
	ICE_U32 uiIdleState;
	ICE_U32 uiRelatedTalks;
	ICE_U8 aucResrv[128];
}T_GpioInParam;

typedef struct T_DisplayCfg{
	ICE_U32 uiAdDisplayTime;//广告也没停留时长 1-300s
	ICE_U32 uiPlateDisplayTime;//车牌信息显示时长 1-100s
	ICE_U32 uiAdSwitchMode;//广告切换效果 0:从左到右 1:从右到左
	ICE_U8 aucResrv[256];
}T_DisplayCfg;

typedef struct T_ClearAdPic{
	ICE_U32 uiPicType;//广告图片清除 0:全屏广告图片清除 1:分屏广告图片清除
	ICE_U8 aucResrv[256];
}T_ClearAdPic;

#define MAX_KEY_NUM 8
typedef struct T_SingleKeyParam
{
	ICE_U32 uiRealValue;//实际键值
	ICE_U32 uiFixValue;//校正键值
	ICE_U8 aucResrv[64];
}T_SingleKeyParam;

typedef struct T_KeyParam
{
	ICE_U8 aucCtrlId[64];//遥控器ID 
	T_SingleKeyParam tSKeyParam[MAX_KEY_NUM];//目前支持四个
	ICE_U8 aucResrv[256];
}T_KeyParam;

typedef struct T_RemoteDebug
{	
	ICE_U32 uiDebug;//0不调试 1调试
	ICE_U8 aucResrv[128];
}T_RemoteDebug;

typedef struct T_RemoteCtrl
{
	ICE_U8 aucCtrlId[64];//遥控器ID
	ICE_U32 uiKeyRealValue;//实际键值
	ICE_U8 aucResrv[128];
}T_RemoteCtrl;

typedef struct
{
	ICE_U16 u16Identify;    //4G配置版本，0x5601 当前配置版本V1
	ICE_U8 u8NetPriorType;  //0表示优先有线连接 1表示优先4G (当前预留)
	ICE_U8 u8DialingMode;   //拨号方式    0表示自动拨号 1表示手动 (当前预留)

	ICE_U8 u8SignalValue;   //信号强度 0 脱网   1 差  2 中 3  强
	ICE_U8 u8NetworkState;  //联网标签   网络连接状态；0:不可上网 1：可以上网.
	ICE_U8 u8Operators;     //运营商 0表示未知 1表示中国移动 2表示中国电信 3表示中国联通
	ICE_U8 u8ModuleState;      //4G 模块联接状态 0:4G模块未识别；1：4G模块识别正常

	ICE_U8 u8NetType;          //网络类型 1:4G, 2:3G,3:2G ,4:其他  (当前预留)
	ICE_U8 u8Reserve; 
	ICE_U16 u16ExtParamSize;   //扩展参数大小

	//ICE_U8 u8ServerIPAddr[64]; //云端服务器地址，用户可输入IP或域名
	ICE_U8 u8ICCIDBuf[24];     //iccid buf  (当前预留)

}ICE_4G_MODULE_PARAM;

typedef struct{
	ICE_U32 u32Result;           //ping 动作返回的结果，相机端传给客户端
	ICE_U8 u8ServerIPAddr[64]; //云端服务器地址，用户可输入IP或域名
	ICE_U8 aucResrv[128];
}ICE_4G_MODULE_SERVER_ADDR;

typedef struct T_LockParam
{
	ICE_U32 uiEnable;//是否使能
	ICE_U32 uiModel;//地锁型号 0:DDTC_DS 1:DDTC_PT 2:DDTC_BD
	ICE_U8 aucId[32];//地锁ID
	ICE_U32 uiSocWarnValue;//地锁电量预警值0-100
	ICE_U32 uiSocFaultValue;//地锁电量故障值0-100
	ICE_U32 uiDelay;//相机主动升锁延时0-60秒
	ICE_U32 uiMode;//模式 0普通模式 1地锁模式
	ICE_U8 aucResrv[128];
}T_LockParam;

#define KEY_LEN 64
#define NET_LEN 128
#define ROUTEURLLEN 256

#define MAX_ROUTESERVER_NUM 8

typedef struct T_TldCfg
{
	ICE_S32 iEn;                     //是否使能特来电协议.[0,1] 0:不使能 1:使能	
	ICE_S32 iInterval;               //心跳周期,单位:秒 ，默认10s
	ICE_U8 aucDeviceKey[KEY_LEN];        //设备key
	ICE_U8 aucDeviceSecret[KEY_LEN];     //设备秘钥
	ICE_U8 aucProductKey[KEY_LEN];       //产品key
	ICE_U8 aucProductSecret[KEY_LEN];    //产品秘钥
	ICE_U8 aucRouteUrl[MAX_ROUTESERVER_NUM][ROUTEURLLEN];  // 路由服务器地址 支持多个路由地址，以|形式分隔
	ICE_U8 aucReserved[256];             // 预留参数
}T_TldCfg;

// ETC 扣费请求数据
typedef struct T_EtcCharge
{
	ICE_S8 acLaneId[32]; // 车道编号
	ICE_S8 acPaySerialNo[36]; // 支付流水号
	ICE_S8 acObuId[32]; // Obu标识
	ICE_S8 acPlate[48]; // 车牌号
	ICE_S8 acVer[16];//版本号
	ICE_S32 iPlateColor; // 车牌颜色，0:蓝色，1:黄色，2:黑色，3:白色，4：绿白5：绿黄，6：绿
	ICE_S32 iTransAmount; // 扣费金额，单位：分
	ICE_S32 iParkTime; //停车时长，单位：秒
	ICE_S32 iInTs; // 入场时间，UTC时间戳
	ICE_U8 aucReserved[256]; // 预留参数
} T_EtcCharge;

//ETC扣费请求应答
typedef struct T_EtcChargeRsp
{
	ICE_S8 acMsg[64]; // 提示信息
	ICE_S8 acTac[32]; // TAC码
	ICE_S8 acTerminalId[32]; // 终端编号
	ICE_S32 iCode; // 返回码
	ICE_S32 iChargeType; // 扣费方式(0：RSU  1：刷卡器 2:智能终端)
	ICE_U8 aucReserved[128];// 预留参数
} T_EtcChargeRsp;

typedef struct T_CloudCfgParamExt
{
	ICE_S32 cloudEn;			//是否打开cloud 功能，默认关闭.[0,1] 0:关闭 1:开启
	ICE_S32 mode;				//工作模式.1:模式1,2:模式2,3:模式3,4:模式4
	ICE_U8 reserved1[8];		//预留参数
	ICE_S32 camIdType;			//camId类型.[0,1] 0:使用相机MAC地址 1:使用相机UUID
	ICE_S32 interval;			//心跳周期,单位:秒.[0,300]，0=无心跳
	ICE_S32 maxSendCnt;			//发送最大次数, 1-3，默认为:2
	ICE_S32 fullImgEn;			//是否发送全景图；0:不发送，1:发送
	ICE_S32 miniImgEn;			//是否发送车牌特写图；
	ICE_S32 ioInEn;				//输入IO状态上报使能
	ICE_U8 ioInNum[8];			//指定上报输入IO，真有效，ioInNum[0]对应输入IO1，ioInNum[1]=IO2,ioInNum[2]=IO3,ioInNum[3]=IO4，4-7预留的
	ICE_U8 parkId[CLOUD_ID_LEN];	//停车场id,只支持英文、数字、'-',like:GD-SZ-A000001

	ICE_U8 cloudDomain[CLOUD_NET_LEN];	// 云平台的域名，like:www.baidu.com
	ICE_U8 path[CLOUD_NET_LEN];		// 云平台跟随的路径
	ICE_S32 port;				// 云平台访问端口，默认为：80
	ICE_U8 reserved2[12];		//预留参数
	ICE_S32 osType;			// 储存协议类型，0=aliyun,1=tencentyun,2=baiduyun
	ICE_U8 osDomain[CLOUD_NET_LEN];	// 对象存储的域名，like:bucket.endpoint
	ICE_S32 iPicUploadType;         // 图片上传方式 0:分开上传  1:一起上传

	ICE_U8 reserved[256];	// 预留参数
	ICE_S8 accessKey[CLOUD_ID_LEN]; // 模式4时，OSS_ACCESS_KEY
	ICE_S8 accessSecret[CLOUD_ID_LEN];// 模式4时，OSS_ACCESS_KEY_SECRET
	ICE_U8 reserved3[384]; // 预留参数
} T_CloudCfgParamExt;

typedef struct T_SyncTimeParam
{
	ICE_S32 iSdkEn;//是否开启相机SDK端校时功能,1开启 0关闭
	ICE_U8 reserved[64];
}T_SyncTimeParam;

typedef struct tagT_MqttType3Param
{
	ICE_S32 iHttpUploadEn;//独立上传图片，针对协议3有效
	ICE_S32 iHttpUploadPort;//独立上传图片服务器端口号，针对协议3有效
	ICE_S8 acProductKey3[64]; //产品名称，针对协议3有效
	ICE_S8 acProductSecret3[64];//产品秘钥，针对协议3有效
	ICE_S8 acDevName3[64];  //设备名称，针对协议3有效
	ICE_S8 acDevSecret3[64]; //设备秘钥  //界面密文，针对协议3有效        
	ICE_S8 acClientId[64];//客户端ID，针对协议3有效
	ICE_S8 acHttpUploadSrv[128];//独立上传图片服务器地址，针对协议3有效
	ICE_S8 acHttpUploadPath[128];//独立上传图片服务器路径，针对协议3有效
}T_MqttType3Param;

//结构体定义
typedef struct tagT_MqttCfgParam
{
	ICE_S32 iMqttEn;		//是否使能mqtt协议， 0 关闭， 1开启
	ICE_S32 iProtoType;	//协议类型， 1 阿里云物联网， 2其他自搭代理服务器 
	ICE_S32 iCamIdType;	//camId类型.[0,1] 0:使用相机MAC地址 1:使用相机UID
	ICE_S32 iHeartEnable;	//心跳使能（预留）
	ICE_S32 interval;		//心跳周期,单位:秒.范围：[1,300]
	ICE_S32 iMaxSendCnt;	//最大发送次数，范围：1-3
	ICE_S32 iPostIoInStatEn;//是否上报IO数据， 0 否， 1是
	ICE_U8 ioInNum[8];		//指定上报输入IO，真有效，ioInNum[0]对应输入IO1，ioInNum[1]=IO2,ioInNum[2]=IO3,ioInNum[3]=IO4，4-7预留的
	ICE_S32 iPostFullEn;	//是否推送全景图，0 否， 1是
	ICE_S32 iPostCloseupEn;	//是否推送车牌特写图，0 否， 1是
	ICE_S32 iPostUart1DataEn;//是否推送串口1数据，0 否， 1是
	ICE_S32 iPostUart2DataEn;//是否推送串口2数据，0 否， 1是
	ICE_U8 aucParkId[64];	//停车场id,只支持英文、数字、'-',like:GD-SZ-A000001，最大支持输入60字节

	ICE_S8 acDomain[128];//代理服务器域名，最大支持输入124字节
	ICE_S32 iPort;		//代理服务器端口
	ICE_S32 iTimeOut;	//超时时长，超时多少不予处理，针对下行接口，范围：1-6s

	//oss配置
	ICE_S32 iOssEn;		// 是否打开对象存储功能。范围：[0,1] 0:关闭， 1:开启
	ICE_U8 aucOssDomain[128]; //对象存储的域名，like:bucket.endpoint，最大支持输入124字节
	ICE_S8 acAccessKey[64];	//界面密文，最大支持输入60字节
	ICE_S8 acAccessSecret[64];//界面密文，最大支持输入60字节

	//阿里IOT三元组信息
	ICE_S8 acProductKey[32];//产品名称，最大支持输入28字节
	ICE_S8 acDevName[32];	//设备名称，最大支持输入28字节
	ICE_S8 acDevSecret[64];	//设备秘钥，最大支持输入60字节

	//自搭代理服务器信息
	ICE_S32 iAuthEn;			//是否开启用户认证，范围：[0,1] 0:关闭 1:开启
	ICE_S8 acUserName[64];	//用户名，最大支持输入60字节
	ICE_S8 acPassword[64];	//密码，最大支持输入60字节
	ICE_U32 uiVersion;		//通用协议扩展参数版本号,默认1.0.0,每一位最大值255,对应uiVersion=0x00010000
	ICE_U32 uiExtVersion;	//扩展参数版本号
	ICE_U8 aucReserved[256]; //通用协议预留参数,通用参数类
	ICE_U8 aucExtReserved[2048];//扩展参数预留
}T_MqttCfgParam;

//对讲柱文字OSD叠加
typedef struct T_RczSingleTextOsd
{
	ICE_U32 uiTextSize;//字体大小，范围1-7
	ICE_U32 uiTextColor;//文字颜色,文字颜色，AsRGB888，低8位表示蓝色分量，中8位表示绿色分量，高8位表示红色分量，最高8位表示透明度
	ICE_U32 uiPosX;//x坐标,范围0-800
	ICE_U32 uiPosY;//y坐标，范围0-1280
	ICE_U8 ucTextStr[128];//叠加内容，utf8编码，目前最多支持90byte(含结束符)
	ICE_U8 ucResvr[256];//预留
}T_RczSingleTextOsd;

#define MAX_RCZ_OSD_NUM 13
typedef struct T_RczTextOsd
{
	T_RczSingleTextOsd tRczSingleTextOsd[MAX_RCZ_OSD_NUM];//最大支持13行
	ICE_U8 ucResvr[256];//预留
}T_RczTextOsd;

typedef enum E_RemCtrlKeyDeal
{
	E_RemCtrlKeyDeal_EnterOpen = 0, // 允许入场
	E_RemCtrlKeyDeal_EnterClose, // 入场关闸
	E_RemCtrlKeyDeal_ExitOpen, // 免费放行
	E_RemCtrlKeyDeal_ExitMoneyOpen, // 收费放行
	E_RemCtrlKeyDeal_ExitClose, // 出场关闸
	E_RemCtrlKeyDeal_Blank, // 暂未启用
	E_RemCtrlKeyDeal_Error, // 错误功能
	E_RemCtrlKeyDeal_Max
} E_RemCtrlKeyDeal;

//遥控器事件上报数据结构体
typedef struct tagT_RemCtrlData
{
	ICE_S32 iKeyDealType;//按键值，详情见E_RemCtrlKeyDeal
	ICE_S8  acReserved[256];//预留
}T_RemCtrlData;

#define MAX_KEY_NUM 8
//遥控器设置/获取数据结构体
typedef struct tagT_RemCtrlCfg
{
	ICE_S32 iKeyDealNum;//按键数量，不支持设置
	ICE_S32 iKeyDealType[MAX_KEY_NUM];//下标0对应KEY1,下标1对应KEY2，以此类推（目前支持4个按键）。按键值详情见E_RemCtrlKeyDeal
	ICE_S8  acReserved[256];//预留
}T_RemCtrlCfg;

typedef struct tagT_TalkBackCfg
{
	ICE_S32 iCallTimeouts;//呼叫超时时间,范围：30-300（单位：秒） 
	ICE_S8  acReserved[256];//预留
}T_TalkBackCfg;

#ifdef __cplusplus
}
#endif


#endif // __ICE_COM_H__


