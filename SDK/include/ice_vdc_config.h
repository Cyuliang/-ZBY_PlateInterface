/*! \file ice_vdc_config.h
\brief ice_vdc_config.h document.
*/

#ifndef __ICE_VDC_CONFIG_H__
#define __ICE_VDC_CONFIG_H__

#include "ice_base_type.h"

#ifdef __cplusplus
extern "C"
{
#endif

//! \ingroup group_vd
//! 出入口车道高级参数定义
typedef struct 
{
	ICE_S32 s32AdaptiveThreshOnOff;					//!<  自适应阈值开关  (1:开 0:关  默认:关)								
	ICE_S32 s32DayTriggerThresh;					//!<  白天触发阈值    (范围:1-100 默认:25)													
	ICE_S32 s32NightTriggerThresh;					//!<  夜间触发阈值    (范围:1-100 默认:50)													
	ICE_S32 s32TriggerSensitivity;					//!<  触发灵敏度      (范围:1-100 默认:10)													
	ICE_S32 s32FilterByPlate;						//!<  无车牌过滤开关  (1:开 0:关  默认:开)														
	ICE_S32 s32TrigerInterval;						//!<  无牌车触发间隔  (范围:10-500  默认:50)
	ICE_S32 s32DetectDoubleDirectOnOff;				//!<  检测双向车辆开关(2:支持双向车辆并输出方向信息 1:支持双向车辆但不输出方向信息 0:只输出单向车辆  默认:1)
	ICE_S32 s32EnableSamePlateCar;					//!<  允许相同车辆开关(1:开 0:关  默认:关)
	ICE_S32 s32SamePlateCarOutputTime;				//!<  相同车辆输出间隔(范围:1-3600 默认:30 单位:秒)
	ICE_S32 s32EnableNonMotorizedVehicles;			//!<  开启非机动车检测开关(1:开 0:关  默认:关)
	ICE_S32 s32FilterNonMotorizedVehicles;			//!<  是否过滤非机动车辆(1:开 0:关  默认:关)
	ICE_S32 s32EnableVehicleBrand;					//!<  支持车款识别(有牌车)
	ICE_S32 s32FilterNoiseChar;						//!<  开启字符干扰过滤(1:开 0:关  默认:关)
	ICE_S32 s32NoiseCharLprThresh;					//!<  字符干扰车牌阈值上限( 15-28 默认:20)
	ICE_S32 s32EnableNoPlateVehicleBrand;			//!< 支持无牌车车款识别（1：开 0：关 默认：关）
	ICE_S32 s32EnableEqualPlateCar;     //!<  相同车辆输出间隔外重复输出开关（1：开 0：关）                          
	ICE_S32 u32Reserved[5];       //!<  保留值                          
    																					
}ICE_VDC_ADV_PARAM_S;

//! \ingroup group_vdc
//! 出入口方向定义
typedef enum 
{
	ICE_VDC_VERHICLE_DIR_HEAD			 = 0,				//!<  车头方向 			
	ICE_VDC_VERHICLE_DIR_TAIL			 = 1,				//!<  车尾方向 			
	ICE_VDC_VERHICLE_DIR_HEAD_AND_TAIL	 = 2				//!<  车头和车尾方向 	
}ICE_VDC_VERHICLE_DIR_E;

//! \ingroup group_vdc
//! 触发方式定义
typedef enum 
{
	ICE_VDC_TRIGER_MODE_HDWARE				= 0,				//!<  外触发（开关量输入） 			
	ICE_VDC_TRIGER_MODE_VIDEO				= 1,				//!<  视频触发 			
	ICE_VDC_TRIGER_MODE_HDWARE_AND_VIDEO	= 2					//!<  外触发和视频混合触发 	
}ICE_VDC_TRIGER_MODE_E;

//! \ingroup group_vdc
//! 安装位置定义
typedef enum 
{
	ICE_VDC_INSTALL_POS_DRIVER_SIDE					= 0,				//!<  司机同侧（推荐）		
	ICE_VDC_INSTALL_POS_DRIVER_REVERSE_SIDE			= 1					//!<  司机异侧 			
}ICE_VDC_INSTALL_POS_E;

//! \ingroup group_vd
//! 车道参数定义
typedef struct 
{																						
	ICE_VDC_VERHICLE_DIR_E enVehiceleDirection;				//!<  车辆方向(默认:车头)											
	ICE_RECT_S astLoop;				 						//!<  虚拟线圈(识别区域)																					
	ICE_VDC_ADV_PARAM_S stAdvParam;							//!<  高级参数
	ICE_VDC_TRIGER_MODE_E enTrigerMode;						//!<  触发模式

	ICE_S32 s32QuqdrangleEnable;							//!<  虚拟线圈多边形识别区域使能
	ICE_S32 s32TripWiresEnable;								//!<  绊线使能标志
	ICE_LINE_S stTripWiresLane;								//!<  绊线
	ICE_LINE_S stTripWiresLane2;							//!<  双向模式下上方的绊线
	ICE_S32 s32OnekeyConfigEnable;							//!<  开启一键调试功能  

	ICE_S32 u32Reserved[8];                        		//!<  保留     																					
	//ICE_S32 u32Reserved[15];                        		//!<  保留     																					
}ICE_VDC_LANE_S;

//! \ingroup group_vd
//! 车牌参数定义
#if 0//此的结构体已更新为后面的结构体（但先不要删除）
typedef struct 
{
	ICE_S32	s32MinPlateWidth;						//!<  最小车牌宽度 									   
	ICE_S32	s32MaxPlateWidth;						//!<  最大车牌宽度 
	ICE_QUADRANGLE_S stVLoopRect;					//!<  虚拟线圈四边形区域
	
	ICE_S32  s32OnlyPlateFilter;                     //!<  虚假车牌告警，虚假车牌使能
	ICE_S8 s8Smoothflag;       //!< 平滑参数；用于车牌相机；
	ICE_S8 s8PlateNoColor;             //!< 车牌颜色无效开关：1无效  0有效（默认）
	ICE_S8 s8VehiAttributeCodeOn;     //!< 无牌车特征码开关：1有效  0无效（默认）
	ICE_S8    s8FalsePlateFilter;                  //虚假车牌过滤与虚假车牌告警关联，如果为1，并且识别到为虚假车牌不上报，0-告警，1-过滤
	ICE_S8    s8VirtualPlate;     //无牌车虚拟车牌输出设置,0 不输出 输出
	ICE_S8 u32Reserved2[7];     //保留

	//ICE_CHAR cPriorCity[32];					 	//!<  优先城市（目前未使用，可以用作多边形区域） 										 
	ICE_S32	s32PlateConfidThrld;					//!<  车牌可信度阈值（-28-28），默认：15 			 
	ICE_FLOAT fPlateAngle;							//!<  车牌倾斜角度，默认：0 
	ICE_S32 s32PlateTypeSp;							//!<  支持车牌类型     0默认全部开启；
	ICE_S32	s32CarColorOn;							//!<  车身颜色额启用； 0不启用
	ICE_S32 s32PriorCityType;						//!<  优先城市类型
	ICE_S32 s32PriorArmyPlate;						//!<  军牌优先
	ICE_VDC_INSTALL_POS_E enCameraInstallPos;		//!<  相机安装位置（默认：司机同侧）
	ICE_S32 s32EnableOnePlateSameChars;				//!<  支持1车牌重复字符（例如:京N11111） 0不启用 1启动 ，默认：0（默认：0）
	ICE_S32 s32EnableOneCarMultiPlates;				//!<  支持1车多牌   0不启用 1启动 ，默认：0
	ICE_S32 s32EnableWJChineseChar;					//!<  支持武警汉字输出   0不启用 1启动 ，默认：0
	ICE_S32 u32Reserved[7];                         //!<  保留     									
}ICE_VDC_PLATE_CONFIG_S;
#endif

typedef struct 
{
	ICE_S32 s32MinPlateWidth;      //!<  最小车牌宽度             
	ICE_S32 s32MaxPlateWidth;      //!<  最大车牌宽度 
	ICE_QUADRANGLE_S stVLoopRect;     //!<  虚拟线圈四边形区域
	ICE_S32  s32AntiFakeEn;                         //!<车牌防伪功能开启  1   开启  0 不开启 
	ICE_S8 s8Smoothflag;       //!< 平滑参数；用于车牌相机；
	ICE_S8 s8PlateNoColor;             //!< 车牌颜色无效开关：1无效  0有效（默认）
	ICE_S8 s8VehiAttributeCodeOn;     //!< 无牌车特征码开关：1有效  0无效（默认）
	//虚假过滤规则
	// s32AntiFakeEn 1 s8FalsePlateFilter 1 过滤
	//s32AntiFakeEn 1 s8FalsePlateFilter  0 告警
	ICE_S8    s8FalsePlateFilter;                  //虚假车牌过滤
	ICE_S8    s8VirtualPlate;     //无牌车虚拟车牌输出设置,0 不输出 输出
	ICE_S8    s8AntiFakeArea;                     //防伪范围  0 所有车   1  白名单
	ICE_S8    s8Reserved2[6];     //保留
	//ICE_CHAR cPriorCity[32];       //!<  优先城市（目前未使用，可以用作多边形区域）            
	ICE_S32 s32PlateConfidThrld;     //!<  车牌可信度阈值（-28-28），默认：15     
	ICE_FLOAT fPlateAngle;       //!<  车牌倾斜角度，默认：0 
	ICE_S32 s32PlateTypeSp;       //!<  支持车牌类型     0默认全部开启；
	ICE_S32 s32CarColorOn;       //!<  车身颜色额启用； 0不启用
	ICE_S32 s32PriorCityType;      //!<  优先城市类型
	ICE_S32 s32PriorArmyPlate;      //!<  军牌优先
	ICE_VDC_INSTALL_POS_E enCameraInstallPos;  //!<  相机安装位置（默认：司机同侧）
	ICE_S32 s32EnableOnePlateSameChars;    //!<  支持1车牌重复字符（例如:京N11111） 0不启用 1启动 ，默认：0（默认：0）
	ICE_S32 s32EnableOneCarMultiPlates;    //!<  支持1车多牌   0不启用 1启动 ，默认：0
	ICE_S32 s32EnableWJChineseChar;     //!<  支持武警汉字输出   0不启用 1启动 ，默认：0
	ICE_S32 u32Reserved[7];                         //!<  保留              
}ICE_VDC_PLATE_CONFIG_S;

//! \ingroup group_vd
//! 出入口参数定义
typedef struct  
{
	ICE_VDC_LANE_S astLane;				 						 //!<  车道参数 		  						  
	ICE_VDC_PLATE_CONFIG_S stPlateParam;						 //!<  车牌参数   		  						  	  
	ICE_S32 s32Width;											 //!<  配置所在参考图像宽度		  						  	  
	ICE_S32 s32Height;											 //!<  配置所在参考图像高度
	ICE_S32 as32Reserved[8];              						 //!<  保留 											  
}ICE_VDC_PARAM_S;

#ifdef __cplusplus
}
#endif


#endif// __ICE_VDC_CONFIG_H__
