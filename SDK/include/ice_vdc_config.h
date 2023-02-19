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
//! ����ڳ����߼���������
typedef struct 
{
	ICE_S32 s32AdaptiveThreshOnOff;					//!<  ����Ӧ��ֵ����  (1:�� 0:��  Ĭ��:��)								
	ICE_S32 s32DayTriggerThresh;					//!<  ���촥����ֵ    (��Χ:1-100 Ĭ��:25)													
	ICE_S32 s32NightTriggerThresh;					//!<  ҹ�䴥����ֵ    (��Χ:1-100 Ĭ��:50)													
	ICE_S32 s32TriggerSensitivity;					//!<  ����������      (��Χ:1-100 Ĭ��:10)													
	ICE_S32 s32FilterByPlate;						//!<  �޳��ƹ��˿���  (1:�� 0:��  Ĭ��:��)														
	ICE_S32 s32TrigerInterval;						//!<  ���Ƴ��������  (��Χ:10-500  Ĭ��:50)
	ICE_S32 s32DetectDoubleDirectOnOff;				//!<  ���˫��������(2:֧��˫���������������Ϣ 1:֧��˫�����������������Ϣ 0:ֻ���������  Ĭ��:1)
	ICE_S32 s32EnableSamePlateCar;					//!<  ������ͬ��������(1:�� 0:��  Ĭ��:��)
	ICE_S32 s32SamePlateCarOutputTime;				//!<  ��ͬ����������(��Χ:1-3600 Ĭ��:30 ��λ:��)
	ICE_S32 s32EnableNonMotorizedVehicles;			//!<  �����ǻ�������⿪��(1:�� 0:��  Ĭ��:��)
	ICE_S32 s32FilterNonMotorizedVehicles;			//!<  �Ƿ���˷ǻ�������(1:�� 0:��  Ĭ��:��)
	ICE_S32 s32EnableVehicleBrand;					//!<  ֧�ֳ���ʶ��(���Ƴ�)
	ICE_S32 s32FilterNoiseChar;						//!<  �����ַ����Ź���(1:�� 0:��  Ĭ��:��)
	ICE_S32 s32NoiseCharLprThresh;					//!<  �ַ����ų�����ֵ����( 15-28 Ĭ��:20)
	ICE_S32 s32EnableNoPlateVehicleBrand;			//!< ֧�����Ƴ�����ʶ��1���� 0���� Ĭ�ϣ��أ�
	ICE_S32 s32EnableEqualPlateCar;     //!<  ��ͬ�������������ظ�������أ�1���� 0���أ�                          
	ICE_S32 u32Reserved[5];       //!<  ����ֵ                          
    																					
}ICE_VDC_ADV_PARAM_S;

//! \ingroup group_vdc
//! ����ڷ�����
typedef enum 
{
	ICE_VDC_VERHICLE_DIR_HEAD			 = 0,				//!<  ��ͷ���� 			
	ICE_VDC_VERHICLE_DIR_TAIL			 = 1,				//!<  ��β���� 			
	ICE_VDC_VERHICLE_DIR_HEAD_AND_TAIL	 = 2				//!<  ��ͷ�ͳ�β���� 	
}ICE_VDC_VERHICLE_DIR_E;

//! \ingroup group_vdc
//! ������ʽ����
typedef enum 
{
	ICE_VDC_TRIGER_MODE_HDWARE				= 0,				//!<  �ⴥ�������������룩 			
	ICE_VDC_TRIGER_MODE_VIDEO				= 1,				//!<  ��Ƶ���� 			
	ICE_VDC_TRIGER_MODE_HDWARE_AND_VIDEO	= 2					//!<  �ⴥ������Ƶ��ϴ��� 	
}ICE_VDC_TRIGER_MODE_E;

//! \ingroup group_vdc
//! ��װλ�ö���
typedef enum 
{
	ICE_VDC_INSTALL_POS_DRIVER_SIDE					= 0,				//!<  ˾��ͬ�ࣨ�Ƽ���		
	ICE_VDC_INSTALL_POS_DRIVER_REVERSE_SIDE			= 1					//!<  ˾����� 			
}ICE_VDC_INSTALL_POS_E;

//! \ingroup group_vd
//! ������������
typedef struct 
{																						
	ICE_VDC_VERHICLE_DIR_E enVehiceleDirection;				//!<  ��������(Ĭ��:��ͷ)											
	ICE_RECT_S astLoop;				 						//!<  ������Ȧ(ʶ������)																					
	ICE_VDC_ADV_PARAM_S stAdvParam;							//!<  �߼�����
	ICE_VDC_TRIGER_MODE_E enTrigerMode;						//!<  ����ģʽ

	ICE_S32 s32QuqdrangleEnable;							//!<  ������Ȧ�����ʶ������ʹ��
	ICE_S32 s32TripWiresEnable;								//!<  ����ʹ�ܱ�־
	ICE_LINE_S stTripWiresLane;								//!<  ����
	ICE_LINE_S stTripWiresLane2;							//!<  ˫��ģʽ���Ϸ��İ���
	ICE_S32 s32OnekeyConfigEnable;							//!<  ����һ�����Թ���  

	ICE_S32 u32Reserved[8];                        		//!<  ����     																					
	//ICE_S32 u32Reserved[15];                        		//!<  ����     																					
}ICE_VDC_LANE_S;

//! \ingroup group_vd
//! ���Ʋ�������
#if 0//�˵Ľṹ���Ѹ���Ϊ����Ľṹ�壨���Ȳ�Ҫɾ����
typedef struct 
{
	ICE_S32	s32MinPlateWidth;						//!<  ��С���ƿ�� 									   
	ICE_S32	s32MaxPlateWidth;						//!<  ����ƿ�� 
	ICE_QUADRANGLE_S stVLoopRect;					//!<  ������Ȧ�ı�������
	
	ICE_S32  s32OnlyPlateFilter;                     //!<  ��ٳ��Ƹ澯����ٳ���ʹ��
	ICE_S8 s8Smoothflag;       //!< ƽ�����������ڳ��������
	ICE_S8 s8PlateNoColor;             //!< ������ɫ��Ч���أ�1��Ч  0��Ч��Ĭ�ϣ�
	ICE_S8 s8VehiAttributeCodeOn;     //!< ���Ƴ������뿪�أ�1��Ч  0��Ч��Ĭ�ϣ�
	ICE_S8    s8FalsePlateFilter;                  //��ٳ��ƹ�������ٳ��Ƹ澯���������Ϊ1������ʶ��Ϊ��ٳ��Ʋ��ϱ���0-�澯��1-����
	ICE_S8    s8VirtualPlate;     //���Ƴ����⳵���������,0 ����� ���
	ICE_S8 u32Reserved2[7];     //����

	//ICE_CHAR cPriorCity[32];					 	//!<  ���ȳ��У�Ŀǰδʹ�ã������������������ 										 
	ICE_S32	s32PlateConfidThrld;					//!<  ���ƿ��Ŷ���ֵ��-28-28����Ĭ�ϣ�15 			 
	ICE_FLOAT fPlateAngle;							//!<  ������б�Ƕȣ�Ĭ�ϣ�0 
	ICE_S32 s32PlateTypeSp;							//!<  ֧�ֳ�������     0Ĭ��ȫ��������
	ICE_S32	s32CarColorOn;							//!<  ������ɫ�����ã� 0������
	ICE_S32 s32PriorCityType;						//!<  ���ȳ�������
	ICE_S32 s32PriorArmyPlate;						//!<  ��������
	ICE_VDC_INSTALL_POS_E enCameraInstallPos;		//!<  �����װλ�ã�Ĭ�ϣ�˾��ͬ�ࣩ
	ICE_S32 s32EnableOnePlateSameChars;				//!<  ֧��1�����ظ��ַ�������:��N11111�� 0������ 1���� ��Ĭ�ϣ�0��Ĭ�ϣ�0��
	ICE_S32 s32EnableOneCarMultiPlates;				//!<  ֧��1������   0������ 1���� ��Ĭ�ϣ�0
	ICE_S32 s32EnableWJChineseChar;					//!<  ֧���侯�������   0������ 1���� ��Ĭ�ϣ�0
	ICE_S32 u32Reserved[7];                         //!<  ����     									
}ICE_VDC_PLATE_CONFIG_S;
#endif

typedef struct 
{
	ICE_S32 s32MinPlateWidth;      //!<  ��С���ƿ��             
	ICE_S32 s32MaxPlateWidth;      //!<  ����ƿ�� 
	ICE_QUADRANGLE_S stVLoopRect;     //!<  ������Ȧ�ı�������
	ICE_S32  s32AntiFakeEn;                         //!<���Ʒ�α���ܿ���  1   ����  0 ������ 
	ICE_S8 s8Smoothflag;       //!< ƽ�����������ڳ��������
	ICE_S8 s8PlateNoColor;             //!< ������ɫ��Ч���أ�1��Ч  0��Ч��Ĭ�ϣ�
	ICE_S8 s8VehiAttributeCodeOn;     //!< ���Ƴ������뿪�أ�1��Ч  0��Ч��Ĭ�ϣ�
	//��ٹ��˹���
	// s32AntiFakeEn 1 s8FalsePlateFilter 1 ����
	//s32AntiFakeEn 1 s8FalsePlateFilter  0 �澯
	ICE_S8    s8FalsePlateFilter;                  //��ٳ��ƹ���
	ICE_S8    s8VirtualPlate;     //���Ƴ����⳵���������,0 ����� ���
	ICE_S8    s8AntiFakeArea;                     //��α��Χ  0 ���г�   1  ������
	ICE_S8    s8Reserved2[6];     //����
	//ICE_CHAR cPriorCity[32];       //!<  ���ȳ��У�Ŀǰδʹ�ã������������������            
	ICE_S32 s32PlateConfidThrld;     //!<  ���ƿ��Ŷ���ֵ��-28-28����Ĭ�ϣ�15     
	ICE_FLOAT fPlateAngle;       //!<  ������б�Ƕȣ�Ĭ�ϣ�0 
	ICE_S32 s32PlateTypeSp;       //!<  ֧�ֳ�������     0Ĭ��ȫ��������
	ICE_S32 s32CarColorOn;       //!<  ������ɫ�����ã� 0������
	ICE_S32 s32PriorCityType;      //!<  ���ȳ�������
	ICE_S32 s32PriorArmyPlate;      //!<  ��������
	ICE_VDC_INSTALL_POS_E enCameraInstallPos;  //!<  �����װλ�ã�Ĭ�ϣ�˾��ͬ�ࣩ
	ICE_S32 s32EnableOnePlateSameChars;    //!<  ֧��1�����ظ��ַ�������:��N11111�� 0������ 1���� ��Ĭ�ϣ�0��Ĭ�ϣ�0��
	ICE_S32 s32EnableOneCarMultiPlates;    //!<  ֧��1������   0������ 1���� ��Ĭ�ϣ�0
	ICE_S32 s32EnableWJChineseChar;     //!<  ֧���侯�������   0������ 1���� ��Ĭ�ϣ�0
	ICE_S32 u32Reserved[7];                         //!<  ����              
}ICE_VDC_PLATE_CONFIG_S;

//! \ingroup group_vd
//! ����ڲ�������
typedef struct  
{
	ICE_VDC_LANE_S astLane;				 						 //!<  �������� 		  						  
	ICE_VDC_PLATE_CONFIG_S stPlateParam;						 //!<  ���Ʋ���   		  						  	  
	ICE_S32 s32Width;											 //!<  �������ڲο�ͼ����		  						  	  
	ICE_S32 s32Height;											 //!<  �������ڲο�ͼ��߶�
	ICE_S32 as32Reserved[8];              						 //!<  ���� 											  
}ICE_VDC_PARAM_S;

#ifdef __cplusplus
}
#endif


#endif// __ICE_VDC_CONFIG_H__
