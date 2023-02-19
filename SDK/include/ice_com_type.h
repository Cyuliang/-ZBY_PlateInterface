/*! \file ice_com_type.h
\brief ice_com_type.h document.
*/
#ifndef _ICE_COM_TYPE_H_
#define _ICE_COM_TYPE_H_

#include "ice_base_type.h"

//! \defgroup group_communication ͨ��Э��
//!  ͨ��Э����������
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
	int enable;   //0 ����, 1 ͼ�� default 1   
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
//! ״̬��
typedef enum
{
	ICE_STATUS_SUCCESS				= 0x00000000,		//!<  �ɹ�
	ICE_STATUS_COMMAND				= 0x00010000,		//!<  ����
	ICE_STATUS_ERROR2				= 0x00080000,		//!<  ����
	ICE_STATUS_ERROR_NOT_FOUND		= 0x00080001,		//!<  û�в��ҵ�
	ICE_STATUS_ERROR_NOT_SUPPORTED	= 0x00080002,		//!<  ��֧��
} ICE_COM_STATUS_E;

//! \ingroup group_communication
//! ����ͨ������
typedef struct 
{
	ICE_U32	u32Size;							//!<  ���ݰ�����
	ICE_U32	u32Type;							//!<  ����
	ICE_U32	u32Status;							//!<  ״̬
	ICE_U32	u32Channel;							//!<  ͨ����
	ICE_U32	u32Time;							//!<  ʱ��
	ICE_U32	u32Date;							//!<  ����
	ICE_U32	u32Id;								//!<  ��ʶ
	ICE_U32	u32Level;							//!<  ��������
} ICE_OPER_DATA_S;

///////////////////////////////////////////////////////////////////////////////////////////////////
// ���������������

// ��������
typedef struct
{
	char filename[128];		//�����������ļ�����.g711a
	int index;				//���鲥������������

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
//! ��������������
typedef enum
{		
	ICE_CONTROL_TYPE_BASE 						= 0x1000,			//!< ���ƻ����ֶ�
	ICE_CONTROL_TYPE_VDR_ARM					= 0x1001,			//!< ��������
	ICE_CONTROL_TYPE_VDR_ARM_RSP				= 0x1002,			//!< ��������Ӧ��
	ICE_CONTROL_TYPE_VDR_DISARM					= 0x1003,			//!< �������
	ICE_CONTROL_TYPE_VDR_DISARM_RSP			    = 0x1004,			//!< �������Ӧ��
	ICE_CONTROL_TYPE_VDR_CLEAR_ALARAM			= 0x1005,			//!< �������
	ICE_CONTROL_TYPE_VDR_CLEAR_ALARAM_RSP     	= 0x1006,			//!< �������Ӧ��
	ICE_CONTROL_TYPE_VDR_REQUEST_ALARM_DATA		= 0x1007,			//!< ���󱨾�����
	ICE_CONTROL_TYPE_VDR_REQUEST_ALARM_DATA_RSP = 0x1008,			//!< ���󱨾�����Ӧ��	
	ICE_CONTROL_TYPE_STREAM_CONNECT			    = 0x1010,			//!< ������Ƶ����
	ICE_CONTROL_TYPE_STREAM_CONNECT_RSP     	= 0x1011,			//!< ������Ƶ����Ӧ��
	ICE_CONTROL_TYPE_STREAM_DISCONNECT			= 0x1012,			//!< �Ͽ���Ƶ����
	ICE_CONTROL_TYPE_STREAM_DISCONNECT_RSP     	= 0x1013,			//!< �Ͽ���Ƶ����Ӧ��
	ICE_CONTROL_TYPE_RESTART					= 0x1020,			//!< �����豸
	ICE_CONTROL_TYPE_RESTART_RSP     			= 0x1021,			//!< �����豸Ӧ��	
	ICE_CONTROL_TYPE_HEART_BEAT					= 0x1022,			//!< �豸����
	ICE_CONTROL_TYPE_HEART_BEAT_RSP     		= 0x1023,			//!< �豸����Ӧ��	
	ICE_CONTROL_TYPE_ERROR_REPORT				= 0x1024,			//!< �豸�����ϱ�
	ICE_CONTROL_TYPE_ERROR_REPORT_RSP     		= 0x1025,			//!< �豸�����ϱ�Ӧ��	
	ICE_CONTROL_TYPE_REQUEST_COUNT				= 0x1026,			//!< �������ͳ�ƽ��
	ICE_CONTROL_TYPE_REQUEST_COUNT_RSP     		= 0x1027,			//!< �������ͳ�ƽ��Ӧ��
	ICE_CONTROL_TYPE_TALK_DATA					= 0x1028,			//!< �����Խ�
	ICE_CONTROL_TYPE_TALK_BEGIN					= 0x1029,			//!< �����Խ���ʼ
	ICE_CONTROL_TYPE_TALK_END					= 0x1030,			//!< �����Խ�����
	ICE_CONTROL_TYPE_SDCARD_FORMAT              = 0x1031,           //!<sd����ʽ��	
	ICE_CONTROL_TYPE_SDCARD_FORMAT_RSP          = 0x1032,           //!<sd����ʽ��Ӧ��	
	ICE_CONTROL_TYPE_CAPTURE					= 0x1033,           //!< ץ�ģ���������ʶ��
	ICE_CONTROL_TYPE_CAPTURE_RSP				= 0x1034,           //!< ץ�ģ���������ʶ��Ӧ��
	ICE_CONTROL_TYPE_SDCARD_UNLOAD				= 0x1035,			//!< SD��ж��
	ICE_CONTROL_TYPE_SDCARD_UNLOAD_RSP			= 0x1036,			//!<SD ��ж��Ӧ��
	
	ICE_CONTROL_TYPE_TRANS_SERIAL_PORT			= 0x1037,           //!< ͸��������������
	ICE_CONTROL_TYPE_TRANS_SERIAL_PORT_RSP		= 0x1038,           //!< ͸��������������Ӧ��
	
	ICE_CONTROL_TYPE_BROADCSAT					= 0x1039,           //!< ������������
	ICE_CONTROL_TYPE_BROADCSAT_RSP				= 0x1040,           //!< ������������Ӧ��
	
	ICE_CONTROL_TYPE_BROADCSAT_WAV				= 0x104A,			//!< wav������������
	ICE_CONTROL_TYPE_BROADCSAT_WAV_RSP			= 0x104B,			//!< wav������������Ӧ��

	ICE_CONTROL_TYPE_VDR_REQUEST_ALARM_DATA_PASSWD		= 0x1041,			//!< ���󱨾����ݣ������룩
	ICE_CONTROL_TYPE_VDR_REQUEST_ALARM_DATA_PASSWD_RSP	= 0x1042,			//!< ���󱨾����ݣ������룩Ӧ��	
	
	ICE_CONTROL_TYPE_TRANS_SERIAL_PORT_RS232			= 0x1043,           //!< ͸��������������
	ICE_CONTROL_TYPE_TRANS_SERIAL_PORT_RS232_RSP		= 0x1044,           //!< ͸��������������Ӧ��
	
	ICE_CONTROL_TYPE_GET_IO_IN_STATE							= 0x1045,		//!<IO ����״̬��ȡ����
	ICE_CONTROL_TYPE_GET_IO_IN_STATE_RSP					= 0x1046,			//!<IO ����״̬��ȡ����Ӧ��

	ICE_CONTROL_TYPE_VDR_REQUEST_ALARM_DATA_NO_PIC	= 0x1047,			//!< ���󱨾�����(��ͼƬ����)
	ICE_CONTROL_TYPE_VDR_REQUEST_ALARM_DATA_NO_PIC_RSP = 0x1048,			//!< ���󱨾�����Ӧ��(��ͼƬ����)	

	ICE_CONTROL_TYPE_VDR_REQUEST_ALARM_DATA_NO_PIC_PASSWD = 0x1049,			//!< ���󱨾�����(��ͼƬ����)
	ICE_CONTROL_TYPE_VDR_REQUEST_ALARM_DATA_NO_PIC_PASSWD_RSP = 0x1050,			//!< ���󱨾�����Ӧ��(��ͼƬ����)
	ICE_CONTROL_TYPE_GET_CAMERA_HARDWARE_INFO	= 0x1051,			//!< �������Ӳ����Ϣ
	ICE_CONTROL_TYPE_GET_CAMERA_HARDWARE_INFO_RSP = 0x1052,			//!< �������Ӳ����ϢӦ��
	
	ICE_CONTROL_TYPE_GET_CAMERA_SOFTWARE_INFO	= 0x1053,			//!< ������������Ϣ
	ICE_CONTROL_TYPE_GET_CAMERA_SOFTWARE_INFO_RSP = 0x1054,			//!< ������������ϢӦ��

	ICE_CONTROL_TYPE_SDCARD_FORMAT_ONLY              = 0x1055,           //!<sd����ʽ��������	
	ICE_CONTROL_TYPE_SDCARD_FORMAT_ONLY_RSP          = 0x1056,           //!<sd����ʽ��Ӧ��	������

	ICE_CONTROL_TYPE_GET_OFFLINE_STATE_INFO	= 0x1057,			//!< ��ȡ����ѻ���Ϣ
	ICE_CONTROL_TYPE_GET_OFFLINE_STATE_INFO_RSP	= 0x1058,		//!< ��ȡ����ѻ���ϢӦ��

	ICE_CONTROL_TYPE_GET_CAMERA_INFO_JSON	= 0x1059,			//!< ��ȡ����ѻ���Ϣ
	ICE_CONTROL_TYPE_GET_CAMERA_INFO_JSON_RSP	= 0x105a,		//!< ��ȡ����ѻ���ϢӦ��

	ICE_CONTROL_TYPE_TALK_REFUSE = 0x105b,							//!< �����ն˾ܾ������Խ�
	ICE_CONTROL_TYPE_TALK_REFUSE_RSP = 0x105c,						//!< �����ն˾ܾ������Խ�Ӧ��

	ICE_CONTROL_TYPE_TALK_IGNORE = 0x105d,       //!< �����ն˺��Խ����Խ�
	ICE_CONTROL_TYPE_TALK_IGNORE_RSP = 0x105e,      //!< �����ն˺��Խ����Խ�Ӧ��

	ICE_CONTROL_TYPE_WJ_ETC_CHARGE = 0x105F,       //!< ETC �۷�����
	ICE_CONTROL_TYPE_WJ_ETC_CHARGE_RSP = 0x1060,      //!< ETC �۷�����Ӧ��

	ICE_CONTROL_TYPE_END						= 0x106F,		
} ICE_CONTROL_TYPE_E;


//! ���������ݻ���
typedef union 
{
	ICE_U8 au8Buffer[ICE_BUF_SIZE_CONTROL];
} ICE_CONTROL_DATA_INTERNAL_U;

//! \ingroup group_communication
//! ����������ͷ�����ݻ���
typedef struct 
{
	ICE_OPER_DATA_S stHead;						
	ICE_CONTROL_DATA_INTERNAL_U unData;			
} ICE_CONTROL_DATA_S;

//!��ȡ���Ӳ����Ϣ
typedef struct
{
	ICE_U32 u32FlashSize;
	ICE_U32 u32AlpuIcType;
	ICE_U32 reserved[14];

} ICE_CAMERA_HW_INFO_S;

// ���Ʋ��������������
///////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////
// �¼������������

//! \ingroup group_communication
//! �¼���������
typedef enum
{
	ICE_EVENT_TYPE_BASE			= 0x2000,		//!< �¼������ֶ�
	ICE_EVENT_TYPE_DTCA_EVENT	= 0x2001,		//!< �ܽ��¼�����
	ICE_EVENT_TYPE_VLPR_EVENT	= 0x2002,		//!< �����¼�����
	ICE_EVENT_TYPE_FAST_VLPR_EVENT	= 0x2003,        //!< ����ʶ������¼�
    ICE_EVENT_TYPE_SFDV_EVENT	= 0x2004,		//!< �г��¼�����
	ICE_EVENT_TYPE_VLPREXT_EVENT	= 0x2005,	//!< ������չ�¼�����
	ICE_EVENT_TYPE_HCNT_EVENT	= 0x2006,		//!< �����¼�����
	ICE_EVENT_TYPE_IPG_EVENT	= 0x2007,		//!< ��λ�¼�����
	ICE_EVENT_TYPE_VLPR_CFG_NOTIFY_EVENT = 0x20fd,	//!< �����¼����ñ仯֪ͨ�¼�
	ICE_EVENT_TYPE_IO_EVENT     = 0x20fe,		//!< ͸��IO״̬�ص�
	ICE_EVENT_TYPE_RS232_EVENT	= 0x20ff,		//!< ͸������(rs232)�ش�����
	ICE_EVENT_TYPE_RS485_EVENT	= 0x2100,		//!< ͸������(rs485)�ش�����
	ICE_EVENT_TYPE_IO_EVENT_EXPIRED     = 0x2101,		//!< ͸��IO״̬�ص�!!���ڼ�����������Ҫ�Ƴ���SDKĿǰʹ��rtsp����
	TYPE_TALK_STATE				= 0x2102,//�Խ�״̬
	ICE_EVENT_TYPE_REMCTRL_EVENT = 0x2103,//ң�����¼�
	ICE_EVENT_TYPE_END			= 0x2104,		
} ICE_EVENT_TYPE_E;




//! �¼����ݻ���
typedef union 
{
	ICE_U8 au8Buffer[ICE_BUF_SIZE_EVENT];			//!< �¼����ݻ���
} ICE_EVENT_DATA_INTERNAL_U;

//! \ingroup group_communication
//! �¼�����ͷ�����ݻ���
typedef struct 
{
	ICE_OPER_DATA_S stHead;							//!< ����ͷ
	ICE_EVENT_DATA_INTERNAL_U unData;				//!< �¼�����
} ICE_EVENT_DATA_S;

// �¼������������
///////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////
// ��Ƶ���������������

//! \ingroup group_communication
//! Ŀ�괦����������
typedef enum
{
	ICE_VPRO_TYPE_BASE 				= 0x3000,		//!< Ŀ�����ݻ����ֶ�
	ICE_VPRO_TYPE_DTCA_TARGET_SET	= 0x3001,		//!< �ܽ��㷨Ŀ��
	ICE_VPRO_TYPE_VLPR_TARGET_SET	= 0x3002,		//!< �����㷨Ŀ��
	ICE_VPRO_TYPE_SFDV_TARGET_SET	= 0x3004,		//!< �г��㷨Ŀ��
	ICE_VPRO_TYPE_SNAP				= 0x3100,		//!< ץ������
	ICE_VPRO_TYPE_END				= 0x3101,		
} ICE_VPRO_TYPE_E;


//! Ŀ�괦�����ݻ���
typedef union 
{
	ICE_U8 au8Buffer[ICE_BUF_SIZE_VPRO];			//!< Ŀ�����ݻ���
} ICE_VPRO_DATA_INTERNAL_U;

//! \ingroup group_communication
//! Ŀ�괦������ͷ�����ݻ���
typedef struct 
{
	ICE_OPER_DATA_S stHead;							//!< ����ͷ
	ICE_VPRO_DATA_INTERNAL_U unData;				//!< Ŀ������
} ICE_VPRO_DATA_S;

// ��Ƶ���������������
///////////////////////////////////////////////////////////////////////////////////////////////////


//! \ingroup group_communication
//! �㷨���������������
typedef enum
{
	ICE_ALGO_CONFIG_TYPE_BASE 						= 0x4000,		//!< �㷨�������ͻ����ֶ�

	ICE_ALGO_CONFIG_TYPE_SET_AGLO_MODULE			= 0x4001,		//!< �����㷨ģ��
	ICE_ALGO_CONFIG_TYPE_SET_AGLO_MODULE_RSP		= 0x4002,		//!< �����㷨ģ��Ӧ��	
	ICE_ALGO_CONFIG_TYPE_GET_AGLO_MODULE			= 0x4003,		//!< ��ȡ�㷨ģ��
	ICE_ALGO_CONFIG_TYPE_GET_AGLO_MODULE_RSP		= 0x4004,		//!< ��ȡ�㷨ģ��Ӧ��

	ICE_ALGO_CONFIG_TYPE_SET_VIDEO_SOURCE_MODE		= 0x4100,		//!< ������Ƶ������ʽ
	ICE_ALGO_CONFIG_TYPE_SET_VIDEO_SOURCE_MODE_RSP	= 0x4101,		//!< ������Ƶ������ʽӦ��
	
	ICE_ALGO_CONFIG_TYPE_GET_VIDEO_SOURCE_MODE		= 0x4102,		//!< ��ȡ��Ƶ������ʽ
	ICE_ALGO_CONFIG_TYPE_GET_VIDEO_SOURCE_MODE_RSP	= 0x4103,		//!< ��ȡ��Ƶ������ʽӦ��
	

	ICE_ALGO_CONFIG_TYPE_SET_DTCA_ALGO_LIB_INFO		= 0x4200,		//!< �����ܽ��㷨����Ϣ(������ )
	ICE_ALGO_CONFIG_TYPE_SET_DTCA_ALGO_LIB_INFO_RSP	= 0x4201,		//!< �����ܽ��㷨����ϢӦ��	
	ICE_ALGO_CONFIG_TYPE_GET_DTCA_ALGO_LIB_INFO		= 0x4202,		//!< ��ȡ�ܽ��㷨����Ϣ�������롢�汾�š�������Ŀ�������ȣ�
	ICE_ALGO_CONFIG_TYPE_GET_DTCA_ALGO_LIB_INFO_RSP	= 0x4203,		//!< ��ȡ�ܽ��㷨����ϢӦ��
	
	ICE_ALGO_CONFIG_TYPE_SET_VLPR_ALGO_LIB_INFO		= 0x4204,		//!< ���ÿ����㷨����Ϣ(������ )
	ICE_ALGO_CONFIG_TYPE_SET_VLPR_ALGO_LIB_INFO_RSP	= 0x4205,		//!< ���ÿ����㷨����ϢӦ��	
	ICE_ALGO_CONFIG_TYPE_GET_VLPR_ALGO_LIB_INFO		= 0x4206,		//!< ��ȡ�����㷨����Ϣ�������롢�汾�š�������Ŀ�������ȣ�
	ICE_ALGO_CONFIG_TYPE_GET_VLPR_ALGO_LIB_INFO_RSP	= 0x4207,		//!< ��ȡ�����㷨����ϢӦ��
	
	ICE_ALGO_CONFIG_TYPE_SET_SFDV_ALGO_LIB_INFO		= 0x4208,		//!< �����г��㷨����Ϣ(������ )
	ICE_ALGO_CONFIG_TYPE_SET_SFDV_ALGO_LIB_INFO_RSP	= 0x4209,		//!< �����г��㷨����ϢӦ��	
	ICE_ALGO_CONFIG_TYPE_GET_SFDV_ALGO_LIB_INFO		= 0x4210,		//!< ��ȡ�г��㷨����Ϣ�������롢�汾�š�������Ŀ�������ȣ�
	ICE_ALGO_CONFIG_TYPE_GET_SFDV_ALGO_LIB_INFO_RSP	= 0x4211,		//!< ��ȡ�г��㷨����ϢӦ��
	
	ICE_ALGO_CONFIG_TYPE_SET_ITSE_ALGO_LIB_INFO		= 0x4212,		//!< ���ý�ͨ�¼��㷨����Ϣ(������ )
	ICE_ALGO_CONFIG_TYPE_SET_ITSE_ALGO_LIB_INFO_RSP	= 0x4213,		//!< ���ý�ͨ�¼��㷨����ϢӦ��	
	ICE_ALGO_CONFIG_TYPE_GET_ITSE_ALGO_LIB_INFO		= 0x4214,		//!< ��ȡ��ͨ�¼��㷨����Ϣ�������롢�汾�š�������Ŀ�������ȣ�
	ICE_ALGO_CONFIG_TYPE_GET_ITSE_ALGO_LIB_INFO_RSP	= 0x4215,		//!< ��ȡ��ͨ�¼��㷨����ϢӦ��

	ICE_ALGO_CONFIG_TYPE_SET_DTCA_RULE_PARAM		= 0x4300,		//!< �����ܽ��㷨��������
	ICE_ALGO_CONFIG_TYPE_SET_DTCA_RULE_PARAM_RSP	= 0x4301,		//!< �����ܽ��㷨��������Ӧ��
	ICE_ALGO_CONFIG_TYPE_GET_DTCA_RULE_PARAM		= 0x4302, 		//!< ��ȡ�ܽ��㷨��������
	ICE_ALGO_CONFIG_TYPE_GET_DTCA_RULE_PARAM_RSP	= 0x4303, 		//!< ��ȡ�ܽ��㷨��������Ӧ��
	
	ICE_ALGO_CONFIG_TYPE_SET_VLPR_RULE_PARAM		= 0x4304,		//!< ���ÿ����㷨��������
	ICE_ALGO_CONFIG_TYPE_SET_VLPR_RULE_PARAM_RSP	= 0x4305,		//!< ���ÿ����㷨��������Ӧ��
	ICE_ALGO_CONFIG_TYPE_GET_VLPR_RULE_PARAM		= 0x4305,		//!< ��ȡ�����㷨��������
	ICE_ALGO_CONFIG_TYPE_GET_VLPR_RULE_PARAM_RSP	= 0x4306,		//!< ��ȡ�����㷨��������Ӧ��
	
	ICE_ALGO_CONFIG_TYPE_SET_SFDV_RULE_PARAM		= 0x4307,		//!< �����г��㷨��������
	ICE_ALGO_CONFIG_TYPE_SET_SFDV_RULE_PARAM_RSP	= 0x4308,		//!< �����г��㷨��������Ӧ��
	ICE_ALGO_CONFIG_TYPE_GET_SFDV_RULE_PARAM		= 0x4309, 		//!< ��ȡ�г��㷨��������
	ICE_ALGO_CONFIG_TYPE_GET_SFDV_RULE_PARAM_RSP	= 0x4310, 		//!< ��ȡ�г��㷨��������Ӧ��
	
	ICE_ALGO_CONFIG_TYPE_SET_HCNT_RULE_PARAM		= 0x4311,		//!< ���ü����㷨��������
	ICE_ALGO_CONFIG_TYPE_SET_HCNT_RULE_PARAM_RSP	= 0x4312,		//!< ���ü����㷨��������Ӧ��
	ICE_ALGO_CONFIG_TYPE_GET_HCNT_RULE_PARAM		= 0x4313, 		//!< ��ȡ�����㷨��������
	ICE_ALGO_CONFIG_TYPE_GET_HCNT_RULE_PARAM_RSP	= 0x4314, 		//!< ��ȡ�����㷨��������Ӧ��
	
	ICE_ALGO_CONFIG_TYPE_END						= 0x4315,		
} ICE_ALGO_CONFIG_TYPE_E;

///////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct __NET_ONVIF_CONFIG{
	ICE_U32 version;  //��ǰ�汾1
	ICE_U32 enable;  //onvif�Ƿ�ʹ��0 �ر� 1���� Ĭ�Ϲر�
	ICE_U8 aucReserved[128]; // �����ֽ�
}NET_ONVIF_CONFIG;

typedef struct
{
	ICE_U32 u32Expline;			//�ֶ��ع�ʱ��
	ICE_S32 s32AGain;			//�ֶ�ģ������
	ICE_S32 s32DGain;			//�ֶ���������

	ICE_U32 u32Mode;			//ģʽ��0�Զ���1��ʱ��2�ֶ�

	ICE_U32 u32DayBegin;		//���쿪ʼʱ�䣨����Ϊ��λ������8��Ϊ480��
	ICE_U32 u32DayEnd;			//�������ʱ�䣨����Ϊ��λ������18��Ϊ1080��
	ICE_U32 u32DayExplineMin;	//������С�ع�ʱ�䣨0-40000��
	ICE_U32 u32DayExplineMax;	//��������ع�ʱ�䣨0-40000��
	ICE_S32 s32DayAGainMin;		//������Сģ�����棨1-16��
	ICE_S32 s32DayAGainMax;		//�������ģ�����棨1-16��
	ICE_S32 s32DayDGainMin;		//������С�������棨1-4��
	ICE_S32 s32DayDGainMax;		//��������������棨1-4��

	ICE_U32 u32NightBegin;		//���Ͽ�ʼʱ�䣨����Ϊ��λ������20��Ϊ1200��
	ICE_U32 u32NightEnd;		//���Ͻ���ʱ�䣨����Ϊ��λ������6��Ϊ360��
	ICE_U32 u32NightExplineMin;	//������С�ع�ʱ��
	ICE_U32 u32NightExplineMax;	//��������ع�ʱ��
	ICE_S32 s32NightAGainMin;	//������Сģ������
	ICE_S32 s32NightAGainMax;	//�������ģ������
	ICE_S32 s32NightDGainMin;	//������С��������
	ICE_S32 s32NightDGainMax;	//���������������

	ICE_U32 u32OtherExplineMin;	//����ʱ����С�ع�ʱ��
	ICE_U32 u32Focus;			//����
	ICE_S32 s32Height;			//��װ�߶�
	ICE_S32 s32HeightAlgo;		//��װ�߶��Զ�����
	ICE_S32 s32Distance;		//��װ����
	ICE_S32 s32DistAlgo;		//��װ�����Զ�����

	ICE_U32 u32LightMode;		//�����ģʽ
	ICE_U32 u32ColorMode;		//��ת��ģʽ

	ICE_U32 u32AlgoWidth;
	ICE_U32 u32AlgoHeight;

} ICE_ExpAttr_S;

//����ƿ���ģʽ
typedef enum
{
	ICE_LIGHT_MODE_AUTO = 0,		//�����Զ����
	ICE_LIGHT_MODE_BY_TIME,			//ʱ�����
	ICE_LIGHT_MODE_BY_TMLS,			//������ʱ���ۺϿ��ƣ������ǹ���������Ϊʱ�����
} ICE_LIGHT_MODE_TYPE_E;

typedef enum
{
	ICE_COLOR_MODE_AUTO = 0,		//�����Զ����
	ICE_COLOR_MODE_COLOR,			//��ɫ
	ICE_COLOR_MODE_NOCOLOR,			//�ڰ�
	
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
	ICE_HCNT_DOOR_FRONT = 0,		//ǰ��
	ICE_HCNT_DOOR_MID,				//����
	ICE_HCNT_DOOR_BACK				//����
	
} ICE_HCNT_DOOR_TYPE_E;

typedef enum
{
	ICE_HCNT_LINK_SERVER_NET = 0,		//����������Ӳ�����̫��ģʽ
	ICE_HCNT_LINK_SERVER_RS485,			//����������Ӳ�������rs485 ģʽ
	
} ICE_HCNT_IPC_LINK_SERVER_MODE_E;

typedef enum
{
	ICE_HCNT_CLEAR_PERIOD = 0,		//����
	ICE_HCNT_CLEAR_TRIGGER,			//�ⴥ��
	
} ICE_HCNT_CLEAR_MODE_E;

typedef enum
{
	ICE_HCNT_TRIGGER_RELAYIN = 0,		//����������
	ICE_HCNT_TRIGGER_RS485,				//RS485����
	ICE_HCNT_TRIGGER_PROGRAM,			//�������
	
} ICE_HCNT_TRIGGER_MODE_E;

typedef enum
{
	ICE_HCNT_RELAYIN_OFF = 0,		//�պϴ�������
	ICE_HCNT_RELAYIN_ON,			//�򿪴�������
	
} ICE_HCNT_RELAYIN_MODE_E;

typedef enum
{
	ICE_HCNT_STORE_FLASH = 0,		//FLASH�洢
	ICE_HCNT_STORE_SDCARD,			//SD���洢

} ICE_HCNT_STORE_MODE;

typedef enum
{
	ICE_HCNT_COLLECT_HOUR = 0,		//Сʱ����
	ICE_HCNT_COLLECT_DAY,			//�����

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
	ICE_U32 u32HBInterval;			//��������
	
	ICE_U32 u32ClearMode;			//����ģʽ
	ICE_U32 u32ClearInterval;		//��������
	ICE_U32 u32TriggerMode;			//�ⴥ��ģʽ
	ICE_U32 u32RelayinMode;			//����������ģʽ
	
	ICE_U32 u32DataStore;			//�Ƿ����ݴ洢
	ICE_U32 u32StoreMode;			//���ݴ洢ģʽ
	ICE_U32 u32StoreSize;			//�洢�ռ�
	ICE_U32 u32StoreStat;			//�Ƿ�ͳ�ƴ洢
	ICE_U32 u32StatCollect;			//�Ƿ����ݻ���
	ICE_U32 u32CollectMode;			//����ģʽ
	
	ICE_U32 au32Reserved[32];

} ICE_HCNTAttr_S;


//ͼ����OSDλ������

typedef enum
{
	ICE_OSD_LOCATION_LEFT_TOP = 0,	//����
	ICE_OSD_LOCATION_RIGHT_TOP,		//����
	ICE_OSD_LOCATION_LEFT_BOTTOM,	//����
	ICE_OSD_LOCATION_RIGHT_BOTTOM,	//����
	ICE_OSD_LOCATION_TOP_MID,		//�Ͼ���
	ICE_OSD_LOCATION_BOTTOM_MID,		//�¾���
} ICE_OSD_LOCATION_TYPE_E;

//ͼ������OSDλ������
typedef enum
{
	ICE_OSD_LOCATION_IN_IMAGE = 0,
	ICE_OSD_LOCATION_OUT_TOP,	   //ͼ���Ϸ�
	ICE_OSD_LOCATION_OUT_BOTTOM,   //ͼ���·�
} ICE_OSD_BIG_LOCATION_TYPE_E;



typedef enum
{
	ICE_CAMERA_DIRECTION_NORTH = 0,	//������
	ICE_CAMERA_DIRECTION_WEST,		//�ɶ�����
	ICE_CAMERA_DIRECTION_EAST,		//������
	ICE_CAMERA_DIRECTION_SOUTH		//�ɱ�����
	
} ICE_CAMERA_DIRECTION_TYPE_E;


typedef enum
{
	ICE_OSD_FONTSIZE_SMALL= 0,	//С
	ICE_OSD_FONTSIZE_MEDIUM,		//��
	ICE_OSD_FONTSIZE_LARGE,		//��
} ICE_OSD_FONTSIZE_TYPE_E;


#define MAX_OSD_TEXT 64
#define MAX_CUSTOM_OSD_LINE_NUM 6

#define MAX_OSD_TEXT_SFM 32
#define MAX_CUSTOM_OSD_LINE_NUM_SFM 4


typedef struct
{
	//video
	ICE_U32 u32OSDLocationVideo;		//����λ��
	ICE_U32 u32ColorVideo;				//��ɫ

	ICE_U32 u32DateVideo;				//�Ƿ��������ʱ��
	ICE_U32 u32License;					//�Ƿ������Ȩ��Ϣ

	ICE_U32 u32CustomVideo;				//�Ƿ�����Զ�����Ϣ
	char szCustomVideo[MAX_OSD_TEXT];	//�Զ�����Ϣ

	//jpeg
	ICE_U32 u32OSDLocationJpeg;			//����λ��
	ICE_U32 u32ColorJpeg;				//��ɫ

	ICE_U32 u32DateJpeg;				//�Ƿ��������ʱ��
	ICE_U32 u32Algo;					//�Ƿ�����㷨��Ϣ

	ICE_U32 u32DeviceID;				//�Ƿ�����豸ID
	char szDeviceID[MAX_OSD_TEXT];		//�豸ID

	ICE_U32 u32DeviceName;				//�Ƿ�����豸����
	char szDeviceName[MAX_OSD_TEXT];	//�豸����

	ICE_U32 u32CamreaLocation;			//�Ƿ���ӵص���Ϣ
	char szCamreaLocation[MAX_OSD_TEXT];	//�ص���Ϣ

	ICE_U32 u32SubLocation;				//�Ƿ�����ӵص���Ϣ
	char szSubLocation[MAX_OSD_TEXT];	//�ӵص���Ϣ

	ICE_U32 u32ShowDirection;			//�Ƿ�����������
	ICE_U32 u32CameraDirection;			//�������

	ICE_U32 u32CustomJpeg;				//�Ƿ�����Զ�����Ϣ

	ICE_U32 u32ItemDisplayMode;             //ͼƬ��Ϣ��ʾģʽ��0��������ʾ��1��������ʾ,Ĭ��0
	ICE_U32 u32DateMode;                 //������ʾģʽ��0��xxxx/xx/xx   1��xxxx��xx��xx�գ�Ĭ��0
	ICE_U32 u32BgColor;                  //OSD ����ɫ��0����ȫ͸����1��������ɫ��Ĭ��0
	ICE_U32 u32FontSize;				//�����С��0:С��1:�� 2:��,Ĭ��Ϊ�У���540P ���£��л�ת��ΪС
	ICE_U32 u32ExpandMode;				//����ģʽ��0:�����ţ�1:ͼ�������ţ�2:ͼ��������
	char szCustomJpeg[MAX_OSD_TEXT - 20];	//�Զ�����Ϣ
	
	char szCustomVideo6[MAX_CUSTOM_OSD_LINE_NUM * MAX_OSD_TEXT];	//�Զ�����Ϣ
	char szCustomJpeg6[MAX_CUSTOM_OSD_LINE_NUM * MAX_OSD_TEXT];	//�Զ�����Ϣ

} ICE_OSDAttr_S;

typedef struct T_VideoOsdAttr 
{
	ICE_U32 u32OSDLocationVideo;		//����λ��
	ICE_U32 u32ColorVideo;				//��ɫ

	ICE_U32 u32DateVideo;				//�Ƿ��������ʱ��
	ICE_U32 u32License;					//�Ƿ������Ȩ��Ϣ
	ICE_U32 u32FontSize;				//�����С��0:С��1:�� 2:��,Ĭ��Ϊ�У���540P ���£��л�ת��ΪС

	ICE_U32 u32CustomVideo;				//�Ƿ�����Զ�����Ϣ
	char szCustomVideo6[MAX_CUSTOM_OSD_LINE_NUM * MAX_OSD_TEXT];	//�Զ�����Ϣ
}T_VideoOsdAttr;


#define ICE_SCHED_TASK_MASK_ARM		0x00000003
#define ICE_SCHED_TASK_MASK_RELAY	0x0000000C
#define ICE_SCHED_TASK_MASK_COLOR	0x00000030

typedef enum
{
	ICE_SCHED_TASK_TYPE_ARM			= 0x00000001, 	//����
	ICE_SCHED_TASK_TYPE_DISARM		= 0x00000002, 	//����
	ICE_SCHED_TASK_TYPE_RELAY_ON	= 0x00000004, 	//�������պ�
	ICE_SCHED_TASK_TYPE_RELAY_OFF	= 0x00000008, 	//��������
	ICE_SCHED_TASK_TYPE_GRAY		= 0x00000010,	//��ת��
	ICE_SCHED_TASK_TYPE_COLOR		= 0x00000020, 	//��ת��
	
} ICE_SCHED_TASK_TYPE_E;

typedef struct
{
	ICE_U32 u32Time;		//ʱ�䣨����Ϊ��λ������20��Ϊ1200��
	ICE_U32 u32Type;		//�������ͣ����������߿��������
	ICE_U32 u32TimeEnd;		//ʱ�䣨����Ϊ��λ������20��Ϊ1200��
	ICE_U32 u32Reserved[7];	//�����ֶ�
	
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
	ICE_PHYCHN_MODE_SUB_VENC = 0,		//������
	ICE_PHYCHN_MODE_VO,					//vo���
	
} ICE_PHYCHN_MODE_TYPE_E;


typedef struct
{
	ICE_U32 u32PhyChn;
	ICE_U32 u32RCMain;
	ICE_U32 u32RCSub;
	ICE_U32 u32CloseupEn; //�Ƿ����������дͼ��
	ICE_U32 u32Qfactor;//ץ��ͼƬ����1~99,Ĭ��90
	ICE_U32 u32FullEn;//�Ƿ�ץ�ĳ���ȫ��ͼ
	ICE_U32 u32CloseupInFullEn; //�Ƿ���ȫ��ͼ�ϵ��ӳ�����дͼ
	ICE_U16 u16Width;//ץ�ķֱ��� ���
	ICE_U16 u16Height;//ץ�ķֱ��ʸ߶�
	ICE_U32 u32PlateSize;	//����ͼ�Ŵ�����1 2 3
	ICE_U32 u32Reserved[2];
	
} ICE_PHYCHN_CFG_S;


typedef struct
{
	ICE_U32 u32VFDRelayout;			//����������������
	ICE_U32 u32DTCARelayout;		//�ܽ�������������
	
	ICE_U32 u32Expline;			//������ֶ��ع�ʱ��
	ICE_S32 s32AGain;			//������ֶ�ģ������
	ICE_S32 s32DGain;			//������ֶ���������
	ICE_U32 u32Mode;			//������ع�ģʽ��0��ȫ�Զ���1�Զ���2�ֶ�
	ICE_U32 u32ExplineMin;		//�������С�ع�ʱ��
	ICE_U32 u32ExplineMax;		//���������ع�ʱ��
	ICE_S32 s32AGainMin;		//�������Сģ������
	ICE_S32 s32AGainMax;		//��������ģ������
	ICE_S32 s32DGainMin;		//�������С��������
	ICE_S32 s32DGainMax;		//����������������
	
	ICE_U32 u32Reserved[1024];			//�����ֶ�
	
} ICE_VFD_PARAM_S;


//�Զ��ع��Ե��ڲ���
typedef struct
{
	int expARegulateEn;//�Ƿ����ع��Ե��ڣ�0�رգ�1������Ĭ��Ϊ��1 ����
	int dayOrNightJudgeCnt; //�����жϵ�����������һ�δ��һ�룻Ĭ��Ϊ��10
	int lumLimitForDay; //�������ȷֽ��ߣ�Ĭ��Ϊ��75
	int lumLimitForNight; //ҹ�����ȷֽ��ߣ�Ĭ��Ϊ��65
	int maxValidBright; //����ʶ��Ч���������ޣ�Ĭ��Ϊ��120
	int minValidBright; //����ʶ��Ч���������ޣ�Ĭ��Ϊ��80
	int maxValidForEnvBright; //������Ƴ��������������ޣ�Ĭ��Ϊ��110
	int minValidForEnvBright; //������Ƴ��������������ޣ�Ĭ��Ϊ��90
	int maxExpCompensation; //�عⲹ���������ֵ��Ĭ��Ϊ��160
	int minExpCompensation;//�عⲹ��������Сֵ��Ĭ��Ϊ��30
	int initExpCompensation;//�عⲹ��ֵ��ʼֵ��Ĭ��Ϊ��70
	int expReguateInterval;//�������������عⲹ�����ĵ��������Ĭ��Ϊ��5
	
	int antiflickerEn;  //ISP����˸�Ƿ�ʹ�� 0 �رգ� 1ʹ�ܣ�Ĭ��ֵΪ��0 �ر�
	int antiflickerFrequency; //ISP ����Ƶ��ֵ������ԴƵ��Ϊ 50Hz ʱ������Ƶ��ֵ����Ϊ 50������ԴƵ��Ϊ 60Hz ʱ������Ƶ��ֵ����Ϊ 60��Ĭ��Ϊ�� 50HZ
	int antiflickerMode; //ISP ����ģʽ 0��1�� Ĭ��Ϊ��1
	int s32PowerFrequencyCompensation; //��Ƶ����

	int u32HighLightMode;    //�Ƿ�Ϊ���⻷����
	int maxExpCompensationHL; //���⻷���£��عⲹ���������ֵ��Ĭ��Ϊ��100
	int minExpCompensationHL;//���⻷���£��عⲹ��������Сֵ��Ĭ��Ϊ��20
	int initExpCompensationHL;//���⻷���£��عⲹ��ֵ��ʼֵ��Ĭ��Ϊ��56

	int as32Reserved[5]; //Ԥ������
}ICE_EXP_AREGULATE_PARAM;

//ע���Զ��ع��Ե��ڲ���������ֻ��Ҫ��ʾ�����͹رռ��ɣ�ISP����˸����Ҫ��¶�������������������Ҫ���ԣ��������ز����ļ��ֶ��޸ģ�Ȼ���ٵ��뵽���


//HTTP post ������


typedef struct
{
	int httpPostEn; //�Ƿ��http post ���ܣ�Ĭ�Ϲر�
	int directionFalg; //������ڷ����־��0 ��ڣ�1 ����Ĭ��ֵΪ��0 ���
	int parkID; //ͣ����ID��Ĭ��Ϊ��13
	char ipStr[20]; //������IP��ַ��Ĭ��Ϊ��123.57.136.148
	int port; //���������ʶ˿ڣ�Ĭ��Ϊ��80
	char domainName[44]; //������IP��Ӧ��������Ĭ��Ϊ��service.tigmall.com
	char ipStr_bak[20]; //���÷�����IP��ַ
	char path[64]; //·�������ϳ���ڷ����־��ͣ������Ŵ���Ĭ��Ϊ: /parking/count
	int maxSendCnt; //����������, Ĭ��Ϊ��3
	int mode; // 2������ģʽ2 ��   1��3������ģʽ1
	int autoAlarmoutEn; //�Ƿ���������Զ���բ,Ĭ�ϲ�����
	int autoAlarmoutMode;//  ģʽ1��ʶ��ɹ���բ����Ĭ�ϣ�,ģʽ2��ȫ����բ��
	int snap_full;//  �Ƿ���ȫ��ͼ��
	int snap_closeup;//  �Ƿ��ͳ�����дͼ��
	int enable_baksvr; //�Ƿ����ñ��÷�����
	short offlinePostEn;   //�Ƿ����ö������� default 0 ,unable 
	short interval;  // 5~30s  
	int ssl_enable;

	char ioPostEn;
	char ioNum;
	char rsv1;
	char rsv2;
	int as32Reserved[1]; //Ԥ������

}ICE_HTTP_POST_PARAM;

typedef struct 
{
	int identify;  //��POST���ñ�ǣ��̶��ַ���"POEX"
	int httpPostEn; //�Ƿ��http post ���ܣ�Ĭ�Ϲر�
	int mode; //1��3������ģʽ1��������ֵ�������ģʽ��ģʽ2����POSTЭ�飬ģʽ5������HXPOST V2.0Э��
	int sslEn;  //SSLʹ�ܣ�Ĭ�ϲ�ʹ��
	int sslPort;  //SSL�˿ڣ�Ĭ��443
	int bakServerEn; //�Ƿ����ñ��÷�����
	int serverPostMode;  //��������������Чʱ����ģʽ:0=ȫ���ͣ�1=�����ȣ����Ʋ��ɹ����Ʊ���
	int serverPort; //���������ʶ˿ڣ�Ĭ��Ϊ��80

	char serverIpStr[32]; //������IP��ַ��Ĭ��Ϊ��123.57.136.148
	char serverDomian[64]; //������������Ĭ��Ϊ��service.tigmall.com
	char bakServerIpStr[32]; //���÷�����IP��ַ��Ĭ��Ϊ��123.57.136.148
	char bakServerDomian[64]; //���÷�����������Ĭ��Ϊ��service.tigmall.com
	char path[64]; //·�������ϳ���ڷ����־��ͣ������Ŵ���Ĭ��Ϊ: /parking/count
	char parkIdStr[64]; //ͣ����ID���ַ�����ֻ֧��Ӣ�ġ����֡�-

	int maxSendCnt; //����������, 1-3��Ĭ��Ϊ:3
	int snapFull;//  �Ƿ���ȫ��ͼ��
	int snapCloseup;//  �Ƿ��ͳ�����дͼ��
	int camIdType;   //ID�ţ�0ʹ�����MAC��ַ��1ʹ�����UUID
	int directionFalg; //������ڷ����־��0=��ڣ�1=���ڣ�Ĭ��0
	int offlinePostEn;  //default 0,��������ʹ�� -----���汾�𣬸�ʹ�ú������ֿ������Ƕ����ģ�����Ӱ��
	int interval;  //������� 1~30s��0��ʾ������ -----���汾�𣬸�ʹ�ú������ֿ������Ƕ����ģ�����Ӱ��
	int autoAlarmOutEn;  //����Զ���բʹ��,Ĭ�ϲ�ʹ��
	int autoAlarmOutMode;//����Զ���բ ģʽ1=ʶ��ɹ���բ��Ĭ�ϣ���ģʽ2=ȫ����բ��ģʽ3=������բ
	int ioInPostEn;  //����IO״̬�ϱ�ʹ��
	char ioInNum[4];  //ָ���ϱ�����IO������Ч��ioInNum[0]��Ӧ����IO1��ioInNum[1]=IO2,ioInNum[2]=IO3,ioInNum[3]=IO4

	char iUnderwayExt;   //�Ƿ������չ��0=�����У�1=����
	char reserve[63];   //Ԥ��������
	int extParamSize;   //ICE_HTTP_POST_NEW_PARAM Ϊ����������������ȫ�����ں��棬ÿ��ģʽ������Ҫ���������׸����������ﵽ������������ͬʱ��֧�ֶ��ⶨ��
}ICE_HTTP_POST_NEW_PARAM;

//ģʽ6 ��������
typedef struct 
{
	char userID[32]; //�û�ID
	char address[64]; //��ַ
}ICE_HTTP_POST_MODE6_EXT_PARAM;

//ģʽ5 ��������
typedef struct ICE_HTTP_POST5_EXTPARAM
{
	char serverDomian[128]; //����������
	char path[128]; //·��
	char acReserved[256];//Ԥ��
} ICE_HTTP_POST5_EXTPARAM;

#define MAX_USEABLE_UART_CNT 2  //�������õĴ��ڸ���

typedef enum{
	UART_PLATENUM_PROTOCOL_ONE =0,	//����Э��1
	UART_TRANS_TRANSMIT,	//͸������
	UART_LED_CONTROL,	//LED������
	UART_MIX_MODE,		//���ģʽ
	UART_PLATENUM_PROTOCOL_TWO,   //����Э��2
	UART_PLATENUM_PROTOCOL_THR,   //����Э��3  
	UART_PLATENUM_PROTOCOL_FOUR,	 // ����Э��4 
	UART_RS232_GETPHONEMAC     // rs232  wifi ̽��Э��
}ICE_UART_WORK_MODE_E;

//ǿ������ѻ���������
typedef struct {
	int force_offline_enable;
	int reserved[15];
}Force_camera_offline_cfg_param;

typedef enum
{
	LED_CARD_SERIAL_PROTOL1 = 0x00,		//led ���ƿ�Э��1
	LED_CARD_SERIAL_PROTOL2 = 0x01,		//led ���ƿ�Э��2
	LED_CARD_SERIAL_MAX_VALUE
}LED_CARD_SERIAL_TYPE_PROTOL;

typedef struct
{
	int uartEn;					 //�����Ƿ�ʹ��0 �����ã�1ʹ�ã�Ĭ��Ϊ1ʹ��
	int uartWorkMode;			 //���ڹ���ģʽ��0:����Э�飬1:͸�����ڣ�Ĭ��Ϊ0 ����Э��
	int baudRate;				 //�����ʣ�Ĭ��ֵΪ9600�����ò����� 1200��2400��4800��9600��19200��38400��115200
	int dataBits;				 //����λ��Ĭ��ֵΪ 8����ѡֵΪ�� 5��6��7��8
	int parity;					 //У��λ��Ĭ��ֵΪ �ޣ���ѡֵΪ���ޡ���У�顢żУ�顢��ǡ��ո�
	int stopBits;				 //ֹͣλ��Ĭ��ֵΪ 1����ѡֵΪ��1��2
	int flowControl;			 //����ģʽ��Ĭ��ֵΪ �ޣ���ѡֵΪ��  �ޡ�Ӳ����Xon/Xoff
	int LEDControlCardType;		 //����LED ����ģʽ�£����ƿ�������
	int LEDBusinessType;		 //ĳһ��LED���ƿ���ҵ�����ͣ�ʲô�����µ�������ӡ��Щ��Ϣ
	int u32UartProcOneReSendCnt; //����Э���ط�����    Ĭ��ֵ0�� ȡֵ��Χ[0~2]
	char screen_mode;            //����ģʽ 1���� 2͸�� 3��բ���� 4��������
	char as32Reserved[7]; //Ԥ������
}ice_uart;


typedef struct{
	ice_uart uart_param[MAX_USEABLE_UART_CNT];//�����������
	int as32Reserved[10]; //Ԥ������
}ICE_UART_PARAM;

//SD ����ز���

typedef enum{
	SDS_NO =1,	//SD��������
	SDS_ERROR,	//SD�����ִ���
	SDS_ENOUGH,	//SD������û����������
	SDS_FULL,		//SD������
	SDS_UNFORMATTED   //SD��δ��ʽ��
}DISK_STATUS;

typedef enum{
	STORE_NO_CLIENT_CONNET =0,	//SD�������洢
	STORE_ALWAYS,	//SD��ʵʱ�洢
	STORE_NEVER	//SD card not store
}DISK_STORE_MODE;

typedef struct
{
	int status; //SD ��״̬��
	int totalSize; //�ܿռ��С
	int usedSize;//���ÿռ��С
	int availableSize; //���ÿռ��С
	int SDStoreMode; //sd �洢ģʽ�������洢��ʵʱ�洢��Ĭ�϶���
	int SDFormatFlag; //sd ���Ƿ��ڸ�ʽ����
	int SDUnloadFlag; //SD ������ж��
	int SDUmountFlag;//SD �Ƿ���Խ�ң����ڸ�ʽ����ж��
	int u32Reserved[6];
}SD_card_param;

#define	MAX_DISK_NAME_LEN		128	//�������������
#define MAX_DISK_MOUNT_PATH_LEN	128	//����Mount·���������
#define DISK_DEV_NODE_LEN			12	// EX: /dev/sda	


typedef struct
{
	int SDTotalNum;
	SD_card_param SDCard_param;
	char	MountPoint[MAX_DISK_MOUNT_PATH_LEN];	//����д��̣�Mount��Ŀ¼���ƣ�ע������������"/"����
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
//	int mode;		//0��ʾ����������1��ʾʵʱ����,2 ��������բ�򲻹���
//	int match;		//������ƥ�����ƣ���Χ��60%-100%����Ĭ�ϣ�80%
//	int black_mode; //������������բģʽ��0 ��������բ��1 ��բ
//	int black_match; //������ƥ�����ƣ���Χ��60%-100%����Ĭ�ϣ�80%
//	int temp_mode;  //��ʱ��������բģʽ��0 ��������բ��1 ��բ
//	char reserved[112];
//	
//} WhiteList_Param;

typedef struct
{
	int mode;  //0��ʾ����������1��ʾʵʱ����,2 ��������բ�򲻹���
	int match;  //������ƥ�����ƣ���Χ��60%-100%����Ĭ�ϣ�80%
	int black_mode; //������������բģʽ��0 ��������բ��1 ��բ
	int black_match; //������ƥ�����ƣ���Χ��60%-100%����Ĭ�ϣ�80%
	int temp_mode;  //��ʱ��������բģʽ��0 ��������բ��1 ��բ
	int ignoreHZ_flag;//���Ժ��ֱ�־��0 �����ԣ�1 ����
	int allow_unmatch_chars_cnt;// ���в�ƥ����ַ�������Χ��0 ~3��
	int new_version; //  new or old WhiteList flag, new:1, old:other.
	int Jing_mode;  //����ģʽ������բģʽ��0 ��������բ��1 ��բ
	int Army_mode;  //����ģʽ������բģʽ��0 ��������բ��1 ��բ
	int Antifake_mode;  //����ٳ���ģʽ 0  ������բ, 1 ����բ(�ѻ�ģʽ��)
	int NewEnergy_mode; //����Դ����ģʽ 0 ��������բ  1������բ

	int EmergencyMode; //Ӧ������ģʽ 0 ��������բ  1������բ
	char reserved[80]; 
} WhiteList_Param;



typedef struct
{
	int alarm_in_delay;
	int alarm_in_stable_frame;   
	int alarm_in_check_interval; //�ظ���Ȧģʽ�£�������ʱ����0~2000ms,Ĭ��0
	int max_again_process_cnt;   //�ظ���Ȧģʽ�£����Ƴ����δ������0~30,Ĭ��10
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
	ICE_U32 u32Enable;		//�Ƿ���
	ICE_U32 u32Time;		//����Ϊ��λ������8��Ϊ480
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
	ICE_U32 rs485_1;	//0:�������1:�������
	ICE_U32 rs485_2;	//0:�������1:�������
	ICE_U32 u32Reserved[16];
}SFM_RS485TransTypeParam;//485����͸��ģʽ����

typedef struct
{
	char old_passwd[16];
	char new_passwd[16];
	ICE_U32 u32Reserved[64];
	
} PasswdParam;

typedef struct
{
	ICE_U32 u32DNS;		//��ѡDNS
	ICE_U32 u32DNS2;	//����DNS
	ICE_U32 u32Reserved[6];
	
} DNSParam;

typedef struct
{
	ICE_U32 u32Luminance;		//����
	ICE_U32 u32AlwaysOn;		//����ģʽ: ����:1 �ر�:0
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
	ICE_U32 u32Enable;			//�Ƿ���
	ICE_U32 u32Interval;		//���ο�բ����
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
	ICE_U32 u32Plate; // �ļ����Ƿ�������ƺ�
	ICE_U32 u32XML; //�Ƿ��ϴ�XML �ļ�
	char s8Path[100]; //�ϴ�·��
	ICE_U32 u32Reserved[2];
	
}FTPParam;

typedef struct
{
	int enable;	//�Ƿ�ʹ��
	char ledip[16];//led��ip
	int ledport;//led�Ķ˿ں�
	int as32Reserved[4]; //Ԥ������

} ICE_LED_PARAM;


typedef struct
{
	ICE_U16 u16EnStrobeCtl;			//�Ƿ�������������
	ICE_U16 u16TriggerDelay;			//����-ʶ����ʱ
	ICE_U16 u16StrobeLastTime;		//�����Ƴ���ʱ��
	ICE_U16 u16StrobeMode;				//0:����ģʽ��1:����ģʽ
	ICE_U16 u16StrobeCtlMode;			//0:���������ģʽ��1:�������ҹ����ģʽ
	ICE_U32 reserved[7];				//����λ
}strobe_light_param_st;//����������

//��ͷAF ZOOM����
typedef struct _IPC_AF_ZOOM
{
	ICE_U8	num;		//1�䱶��2�۽�
	ICE_U8	direction;	//1:�Ŵ���Զ, 2:��С������
	ICE_U8  speed;		//�ٶȣ� 0-1��0Ϊֹͣ,1Ϊ����
	ICE_U16 step;		//����
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
//! ������������������
typedef enum
{
	ICE_CAMERA_CONFIG_TYPE_BASE 					= 0x5000,		//!< ����������ͻ����ֶ�

	ICE_CAMERA_CONFIG_TYPE_SET_BASE_PARAM			= 0x5001,		//!< ��������������������ơ�IP��ַ���豸��ŵȣ�
	ICE_CAMERA_CONFIG_TYPE_SET_BASE_PARAM_RSP		= 0x5002,		//!< ���������������Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_BASE_PARAM			= 0x5003,		//!< ��ȡ�����������
	ICE_CAMERA_CONFIG_TYPE_GET_BASE_PARAM_RSP		= 0x5004,		//!< ��ȡ�����������Ӧ��
	
	ICE_CAMERA_CONFIG_TYPE_SET_SYSTEM_TIME			= 0x5005,		//!< �������ϵͳʱ��
	ICE_CAMERA_CONFIG_TYPE_SET_SYSTEM_TIME_RSP		= 0x5006,		//!< �������ϵͳʱ��Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_SYSTEM_TIME			= 0x5007,		//!< ��ȡ���ϵͳʱ��
	ICE_CAMERA_CONFIG_TYPE_GET_SYSTEM_TIME_RSP		= 0x5008,		//!< ��ȡ���ϵͳʱ��Ӧ��
	
	ICE_CAMERA_CONFIG_TYPE_SET_ISP_PARAM			= 0x5009,		//!< ����ISP�������ع⡢���桢��ƽ��)
	ICE_CAMERA_CONFIG_TYPE_SET_ISP_PARAM_RSP		= 0x5010,		//!< ����ISP����Ӧ!��
	ICE_CAMERA_CONFIG_TYPE_GET_ISP_PARAM			= 0x5011,		//!< ��ȡISP����
	ICE_CAMERA_CONFIG_TYPE_GET_ISP_PARAM_RSP		= 0x5012,		//!< ��ȡISP����Ӧ��
	
	ICE_CAMERA_CONFIG_TYPE_SET_VENC_PARAM			= 0x5013,		//!< ���ñ���������������ֱ��ʡ����ʿ��Ʒ�ʽ�ȣ�
	ICE_CAMERA_CONFIG_TYPE_SET_VENC_PARAM_RSP		= 0x5014,		//!< ���ñ������Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_VENC_PARAM			= 0x5015,		//!< ��ȡ�������
	ICE_CAMERA_CONFIG_TYPE_GET_VENC_PARAM_RSP		= 0x5016,		//!< ���ñ������Ӧ��
	
	ICE_CAMERA_CONFIG_TYPE_SET_IO_PARAM				= 0x5017,		//!< ����IO��������ƽ������ߡ��͡������ء��½��أ������������
	ICE_CAMERA_CONFIG_TYPE_SET_IO_PARAM_RSP			= 0x5018,		//!< ����IO����Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_IO_PARAM				= 0x5019,		//!< ��ȡIO����
	ICE_CAMERA_CONFIG_TYPE_GET_IO_PARAM_RSP			= 0x5020,		//!< ����IO����Ӧ��
	
	ICE_CAMERA_CONFIG_TYPE_SET_COM_PARAM			= 0x5021,		//!< ���ô��ڲ�����232/485 ������ ��
	ICE_CAMERA_CONFIG_TYPE_SET_COM_PARAM_RSP		= 0x5022,		//!< ���ô��ڲ���Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_COM_PARAM			= 0x5023,		//!< ��ȡ���ڲ���
	ICE_CAMERA_CONFIG_TYPE_GET_COM_PARAM_RSP		= 0x5024,		//!< ���ô��ڲ���Ӧ��
	
	ICE_CAMERA_CONFIG_TYPE_UPDATE_PROGRAM			= 0x5025,		//!< ��������
	ICE_CAMERA_CONFIG_TYPE_UPDATE_PROGRAM_RSP		= 0x5026,		//!< ��������Ӧ��
	
	ICE_CAMERA_CONFIG_TYPE_DEFAULT_PROGRAM			= 0x5027,		//!< �ָ�����Ĭ�ϳ���
	ICE_CAMERA_CONFIG_TYPE_DEFAULT_PROGRAM_RSP		= 0x5028,		//!< �ָ�����Ĭ��Ӧ��
	
	ICE_CAMERA_CONFIG_TYPE_DEFAULT_PARAM			= 0x5029,		//!< �ָ�Ĭ�ϲ���
	ICE_CAMERA_CONFIG_TYPE_DEFAULT_PARAM_RSP		= 0x5030,		//!< �ָ�Ĭ�ϲ���Ӧ��
	
	ICE_CAMERA_CONFIG_TYPE_DEFAULT_PARAM_EXP_IP		= 0x5031,		//!< �ָ���IP���Ĭ�ϲ���
	ICE_CAMERA_CONFIG_TYPE_DEFAULT_PARAM_EXP_IP_RSP	= 0x5032,		//!< �ָ���IP���Ĭ�ϲ���Ӧ��
	
	ICE_CAMERA_CONFIG_TYPE_SET_FTP_PARAM			= 0x5033,		//!< ����FTP������FTP��ַ���û��������룩
	ICE_CAMERA_CONFIG_TYPE_SET_FTP_PARAM_RSP		= 0x5034,		//!< ����FTP����Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_FTP_PARAM			= 0x5035,		//!< ��ȡFTP����
	ICE_CAMERA_CONFIG_TYPE_GET_FTP_PARAM_RSP		= 0x5036,		//!< ��ȡFTP����Ӧ��
	
	ICE_CAMERA_CONFIG_TYPE_SET_SNAP_PARAM			= 0x5037,		//!< ����ץ�Ļ��������Ƿ�����ץ�Ļ���ץ�Ļ���ַ��ץ����ʱ��
	ICE_CAMERA_CONFIG_TYPE_SET_SNAP_PARAM_RSP		= 0x5038,		//!< ����ץ�Ļ�����Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_SNAP_PARAM			= 0x5039,		//!< ��ȡץ�Ļ�����
	ICE_CAMERA_CONFIG_TYPE_GET_SNAP_PARAM_RSP		= 0x5040,		//!< ��ȡץ�Ļ�����Ӧ��
	
	ICE_CAMERA_CONFIG_TYPE_SET_HCNT_PARAM			= 0x5041,		//!< ��������ͳ�Ʋ�����rs485Э�����͡��������ͣ�
	ICE_CAMERA_CONFIG_TYPE_SET_HCNT_PARAM_RSP		= 0x5042,		//!< ��������ͳ�Ʋ���Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_HCNT_PARAM			= 0x5043,		//!< ��ȡ����ͳ�Ʋ���
	ICE_CAMERA_CONFIG_TYPE_GET_HCNT_PARAM_RSP		= 0x5044,		//!< ��ȡ����ͳ�Ʋ���Ӧ��
	
	ICE_CAMERA_CONFIG_TYPE_SET_ALARM_IN_CFG			= 0x5045,		//!< ���ø澯�������ã������򳣱գ�
	ICE_CAMERA_CONFIG_TYPE_SET_ALARM_IN_CFG_RSP		= 0x5046,		//!< ���ø澯��������Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_ALARM_IN_CFG			= 0x5047,		//!< ��ȡ�澯��������
	ICE_CAMERA_CONFIG_TYPE_GET_ALARM_IN_CFG_RSP		= 0x5048,		//!< ��ȡ�澯��������Ӧ��
	
	ICE_CAMERA_CONFIG_TYPE_SET_TMSYNC_CFG				= 0x5049,		//!< ����ʱ��ͬ������
	ICE_CAMERA_CONFIG_TYPE_SET_TMSYNC_CFG_RSP			= 0x5050,		//!< ����ʱ��ͬ������Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_TMSYNC_CFG				= 0x5051,		//!< ��ȡʱ��ͬ������
	ICE_CAMERA_CONFIG_TYPE_GET_TMSYNC_CFG_RSP			= 0x5052,		//!< ��ȡʱ��ͬ������Ӧ��
	
	ICE_CAMERA_CONFIG_TYPE_SET_OSD_CFG				= 0x5053,		//!< ����OSD����
	ICE_CAMERA_CONFIG_TYPE_SET_OSD_CFG_RSP			= 0x5054,		//!< ����OSD����Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_OSD_CFG				= 0x5055,		//!< ��ȡOSD����
	ICE_CAMERA_CONFIG_TYPE_GET_OSD_CFG_RSP			= 0x5056,		//!< ��ȡOSD����Ӧ��
	
	ICE_CAMERA_CONFIG_TYPE_SET_SCHED_TASK_CFG		= 0x5061,		//!< ���üƻ���������
	ICE_CAMERA_CONFIG_TYPE_SET_SCHED_TASK_CFG_RSP	= 0x5062,		//!< ���üƻ���������Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_SCHED_TASK_CFG		= 0x5063,		//!< ��ȡ�ƻ���������
	ICE_CAMERA_CONFIG_TYPE_GET_SCHED_TASK_CFG_RSP	= 0x5064,		//!< ��ȡ�ƻ���������Ӧ��
	
	ICE_CAMERA_CONFIG_TYPE_SET_RELAY_OUT		= 0x5065,		//!< ���ÿ��������
	ICE_CAMERA_CONFIG_TYPE_SET_RELAY_OUT_RSP	= 0x5066,		//!< ���ÿ��������Ӧ��
	
	ICE_CAMERA_CONFIG_TYPE_SET_PHYCHN_CFG				= 0x5067,		//!< ��������ͨ������
	ICE_CAMERA_CONFIG_TYPE_SET_PHYCHN_CFG_RSP			= 0x5068,		//!< ��������ͨ������Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_PHYCHN_CFG				= 0x5069,		//!< ��ȡ����ͨ������
	ICE_CAMERA_CONFIG_TYPE_GET_PHYCHN_CFG_RSP			= 0x5070,		//!< ��ȡ����ͨ������Ӧ��

	
	ICE_CAMERA_CONFIG_TYPE_CHECK_VFD_COMM			= 0x5071,		//!< ��֤�����������ͨѶ
	ICE_CAMERA_CONFIG_TYPE_CHECK_VFD_COMM_RSP		= 0x5072,		//!< ��֤�����������ͨѶӦ��
	
	ICE_CAMERA_CONFIG_TYPE_SET_VFD_PARAM		= 0x5073,		//!< ���û����������
	ICE_CAMERA_CONFIG_TYPE_SET_VFD_PARAM_RSP	= 0x5074,		//!< ���û����������Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_VFD_PARAM		= 0x5075,		//!< ��ȡ�����������
	ICE_CAMERA_CONFIG_TYPE_GET_VFD_PARAM_RSP	= 0x5076,		//!< ��ȡ�����������Ӧ��

	ICE_CAMERA_CONFIG_TYPE_SET_UART_PARAM		= 0x5077,		//!< ����������ڲ���
	ICE_CAMERA_CONFIG_TYPE_SET_UART_PARAM_RSP	= 0x5078,		//!< ����������ڲ���Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_UART_PARAM		= 0x5079,		//!< ��ȡ������ڲ���
	ICE_CAMERA_CONFIG_TYPE_GET_UART_PARAM_RSP	= 0x5080,		//!< ��ȡ������ڲ���Ӧ��

	ICE_CAMERA_CONFIG_TYPE_SET_HTTP_POST_PARAM		= 0x5081,		//!< ����HTTP POST����
	ICE_CAMERA_CONFIG_TYPE_SET_HTTP_POST_PARAM_RSP	= 0x5082,		//!< ����HTTP POST����Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_HTTP_POST_PARAM		= 0x5083,		//!< ��ȡHTTP POST����
	ICE_CAMERA_CONFIG_TYPE_GET_HTTP_POST_PARAM_RSP	= 0x5084,		//!< ��ȡHTTP POST����Ӧ��

	ICE_CAMERA_CONFIG_TYPE_SET_EXP_AREGULATE_PARAM		= 0x5085,		//!< �����ع��Զ����ڲ���
	ICE_CAMERA_CONFIG_TYPE_SET_EXP_AREGULATE_PARAM_RSP	= 0x5086,		//!< �����ع��Զ����ڲ���Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_EXP_AREGULATE_PARAM		= 0x5087,		//!< ��ȡ�ع��Զ����ڲ���
	ICE_CAMERA_CONFIG_TYPE_GET_EXP_AREGULATE_PARAM_RSP	= 0x5088,		//!< ��ȡ�ع��Զ����ڲ���Ӧ��


	ICE_CAMERA_CONFIG_TYPE_SET_SDCARD_PARAM		= 0x5089,		//!< ����VDC SD���洢����
	ICE_CAMERA_CONFIG_TYPE_SET_SDCARD_PARAM_RSP	= 0x5090,		//!< ����VDC SD���洢����Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_SDCARD_PARAM		= 0x5091,		//!< ��ȡVDC SD���洢����
	ICE_CAMERA_CONFIG_TYPE_GET_SDCARD_PARAM_RSP	= 0x5092,		//!< ��ȡVDC SD���洢����Ӧ��

	ICE_CAMERA_CONFIG_TYPE_GET_DEV_ID		= 0x5093,		//!< ��ȡ�豸ΨһID
	ICE_CAMERA_CONFIG_TYPE_GET_DEV_ID_RSP	= 0x5094,		//!< ��ȡ�豸ΨһIDӦ��

	ICE_CAMERA_CONFIG_TYPE_SET_WHITELIST_PARAM		= 0x5095,		//!< ���ð���������
	ICE_CAMERA_CONFIG_TYPE_SET_WHITELIST_PARAM_RSP	= 0x5096,		//!< ���ð���������Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_WHITELIST_PARAM		= 0x5097,		//!< ��ȡ����������
	ICE_CAMERA_CONFIG_TYPE_GET_WHITELIST_PARAM_RSP	= 0x5098,		//!< ��ȡ����������Ӧ��

	ICE_CAMERA_CONFIG_TYPE_WRITE_USER_DATA		= 0x5099,		//!< д���û�����
	ICE_CAMERA_CONFIG_TYPE_WRITE_USER_DATA_RSP	= 0x5100,		//!< д���û�����Ӧ��
	ICE_CAMERA_CONFIG_TYPE_READ_USER_DATA		= 0x5101,		//!< �����û�����
	ICE_CAMERA_CONFIG_TYPE_READ_USER_DATA_RSP	= 0x5102,		//!< �����û�����Ӧ��

	ICE_CAMERA_CONFIG_TYPE_WRITE_WHITE_LIST		= 0x5103,		//!< д�������
	ICE_CAMERA_CONFIG_TYPE_WRITE_WHITE_LIST_RSP	= 0x5104,		//!< д�������Ӧ��
	ICE_CAMERA_CONFIG_TYPE_READ_WHITE_LIST		= 0x5105,		//!< ����������
	ICE_CAMERA_CONFIG_TYPE_READ_WHITE_LIST_RSP	= 0x5106,		//!< ����������Ӧ��
	

	ICE_CAMERA_CONFIG_TYPE_SET_HDTRIGGER_PARAM		= 0x5107,		//!< ����Ӳ��������
	ICE_CAMERA_CONFIG_TYPE_SET_HDTRIGGER_PARAM_RSP	= 0x5108,		//!< ����Ӳ��������Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_HDTRIGGER_PARAM		= 0x5109,		//!< ��ȡӲ��������
	ICE_CAMERA_CONFIG_TYPE_GET_HDTRIGGER_PARAM_RSP	= 0x5110,		//!< ��ȡӲ��������Ӧ��

	ICE_CAMERA_CONFIG_TYPE_ADD_WHITE_LIST		= 0x5111,		//!< ���Ӱ�����
	ICE_CAMERA_CONFIG_TYPE_ADD_WHITE_LIST_RSP	= 0x5112,		//!< ���Ӱ�����Ӧ��
	ICE_CAMERA_CONFIG_TYPE_DEL_WHITE_LIST		= 0x5113,		//!< ɾ��������
	ICE_CAMERA_CONFIG_TYPE_DEL_WHITE_LIST_RSP	= 0x5114,		//!< ɾ��������Ӧ��
	ICE_CAMERA_CONFIG_TYPE_EDIT_WHITE_LIST		= 0x5115,		//!< �༭������
	ICE_CAMERA_CONFIG_TYPE_EDIT_WHITE_LIST_RSP	= 0x5116,		//!< �༭������Ӧ��
	ICE_CAMERA_CONFIG_TYPE_FIND_WHITE_LIST		= 0x5117,		//!< ���Ұ�����
	ICE_CAMERA_CONFIG_TYPE_FIND_WHITE_LIST_RSP	= 0x5118,		//!< ���Ұ�����Ӧ��
	ICE_CAMERA_CONFIG_TYPE_DELALL_WHITE_LIST		= 0x5119,		//!< ɾ�����а�����
	ICE_CAMERA_CONFIG_TYPE_DELALL_WHITE_LIST_RSP	= 0x5120,		//!< ɾ�����а�����Ӧ��

	ICE_CAMERA_CONFIG_TYPE_SET_AUTO_REBOOT_PARAM		= 0x5121,		//!< �����Զ���������
	ICE_CAMERA_CONFIG_TYPE_SET_AUTO_REBOOT_PARAM_RSP	= 0x5122,		//!< �����Զ���������Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_AUTO_REBOOT_PARAM		= 0x5123,		//!< ��ȡ�Զ���������
	ICE_CAMERA_CONFIG_TYPE_GET_AUTO_REBOOT_PARAM_RSP	= 0x5124,		//!< ��ȡ�Զ���������Ӧ��

	ICE_CAMERA_CONFIG_TYPE_SET_PASSWD_PARAM		= 0x5125,		//!< �����������
	ICE_CAMERA_CONFIG_TYPE_SET_PASSWD_PARAM_RSP	= 0x5126,		//!< �����������Ӧ��
	ICE_CAMERA_CONFIG_TYPE_RM_LOG_FILE		= 0x5127,		//!< ɾ����־�ļ�
	ICE_CAMERA_CONFIG_TYPE_RM_LOG_FILE_RSP	= 0x5128,		//!<  ɾ����־�ļ�Ӧ��
	
	ICE_CAMERA_CONFIG_TYPE_SET_DNS_PARAM			= 0x5129,		//!< �������DNS����
	ICE_CAMERA_CONFIG_TYPE_SET_DNS_PARAM_RSP		= 0x5130,		//!< �������DNS����Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_DNS_PARAM			= 0x5131,		//!< ��ȡ���DNS����
	ICE_CAMERA_CONFIG_TYPE_GET_DNS_PARAM_RSP		= 0x5132,		//!< ��ȡ���DNS����Ӧ��
	
	ICE_CAMERA_CONFIG_TYPE_SET_LIGHT_PARAM			= 0x5133,		//!< ���ò���Ʋ���
	ICE_CAMERA_CONFIG_TYPE_SET_LIGHT_PARAM_RSP		= 0x5134,		//!< ���ò���Ʋ���Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_LIGHT_PARAM			= 0x5135,		//!< ��ȡ����Ʋ���
	ICE_CAMERA_CONFIG_TYPE_GET_LIGHT_PARAM_RSP		= 0x5136,		//!< ��ȡ����Ʋ���Ӧ��
	
	ICE_CAMERA_CONFIG_TYPE_SET_RELAY_OUT2		= 0x5137,		//!< ���ÿ�����2���
	ICE_CAMERA_CONFIG_TYPE_SET_RELAY_OUT2_RSP	= 0x5138,		//!< ���ÿ�����2���Ӧ��

	ICE_CAMERA_CONFIG_TYPE_SET_REOPEN_PARAM		= 0x5139,		//!< ���ö��ο�բ����
	ICE_CAMERA_CONFIG_TYPE_SET_REOPEN_PARAM_RSP	= 0x5140,		//!< ���ö��ο�բ����Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_REOPEN_PARAM		= 0x5141,		//!< ��ȡ���ο�բ����
	ICE_CAMERA_CONFIG_TYPE_GET_REOPEN_PARAM_RSP	= 0x5142,		//!< ��ȡ���ο�բ����Ӧ��

	ICE_CAMERA_CONFIG_TYPE_SET_OFFLINE_AO_PLAY_PARAM = 0x5143, //!<�����ѻ�������������
	ICE_CAMERA_CONFIG_TYPE_SET_OFFLINE_AO_PLAY_PARAM_RSP = 0x5144,//!>�����ѻ�������������Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_OFFLINE_AO_PLAY_PARAM = 0x5145, //!> ��ȡ�ѻ�������������
	ICE_CAMERA_CONFIG_TYPE_GET_OFFLINE_AO_PLAY_PARAM_RSP = 0x5146,//!>��ȡ�ѻ�������������Ӧ��

	ICE_CAMERA_CONFIG_TYPE_SET_LED_PARAM		= 0x5147,		//!< ����LED����
	ICE_CAMERA_CONFIG_TYPE_SET_LED_PARAM_RSP	= 0x5148,		//!< ����LED����Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_LED_PARAM		= 0x5149,		//!< ��ȡLED����
	ICE_CAMERA_CONFIG_TYPE_GET_LED_PARAM_RSP	= 0x514A,		//!< ��ȡLED����Ӧ��

	ICE_CAMERA_CONFIG_TYPE_SET_CGI_PARAM		= 0x514B,		//!< ����CGI����
	ICE_CAMERA_CONFIG_TYPE_SET_CGI_PARAM_RSP	= 0x514C,		//!< ����CGI����Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_CGI_PARAM		= 0x514D,		//!< ��ȡCGI����
	ICE_CAMERA_CONFIG_TYPE_GET_CGI_PARAM_RSP	= 0x514E,		//!< ��ȡCGI����Ӧ��

	ICE_CAMERA_CONFIG_TYPE_SET_LED_PROTOCOL1    = 0x5150,       //����ledЭ��1����
	ICE_CAMERA_CONFIG_TYPE_SET_LED_PROTOCOL1_RSP    = 0x5151,   // ����ledЭ��1����Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_LED_PROTOCOL1    = 0x5152,       //��ȡledЭ��1����
	ICE_CAMERA_CONFIG_TYPE_GET_LED_PROTOCOL1_RSP    = 0x5153,   // ��ȡledЭ��1����Ӧ��
	
	ICE_CAMERA_CONFIG_TYPE_SET_CAMERA_OFFLINE_PARAM		 = 0x5154,       //!<�������ǿ���ѻ������Ĳ���
	ICE_CAMERA_CONFIG_TYPE_SET_CAMERA_OFFLINE_PARAM_RSP  = 0x5155,   //!<�������ǿ���ѻ������Ĳ���Ӧ��	
	ICE_CAMERA_CONFIG_TYPE_GET_CAMERA_OFFLINE_PARAM		 = 0x5156,       //!<��ȡ���ǿ���ѻ������Ĳ���
	ICE_CAMERA_CONFIG_TYPE_GET_CAMERA_OFFLINE_PARAM_RSP  = 0x5157,   //!<��ȡ���ǿ���ѻ������Ĳ���Ӧ��

	ICE_CAMERA_CONFIG_TYPE_SET_STROBE_LIGHT_PARAM		= 0x5158,       //!<���ñ����Ʋ���
	ICE_CAMERA_CONFIG_TYPE_SET_STROBE_LIGHT_PARAM_RSP   = 0x5159,   //!<���ñ����Ʋ���Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_STROBE_LIGHT_PARAM		= 0x5160,       //!<��ȡ�����Ʋ���
	ICE_CAMERA_CONFIG_TYPE_GET_STROBE_LIGHT_PARAM_RSP   = 0x5161,   //!<��ȡ�����Ʋ���Ӧ��

	ICE_CAMERA_CONFIG_TYPE_SET_LED_CARD_2_SERIAL_PROTOCOL		 = 0x5162,       //!<����led���ƿ�Э��2����
	ICE_CAMERA_CONFIG_TYPE_SET_LED_CARD_2_SERIAL_PROTOCOL_RSP    = 0x5163,   //!<����led���ƿ�Э��2����Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_LED_CARD_2_SERIAL_PROTOCOL		 = 0x5164,       //!<��ȡled���ƿ�Э��2����
	ICE_CAMERA_CONFIG_TYPE_GET_LED_CARD_2_SERIAL_PROTOCOL_RSP    = 0x5165,   //!<��ȡled���ƿ�Э��2����Ӧ��

	ICE_CAMERA_CONFIG_TYPE_SERIAL_LED_CARD_COMMON_TIME_CFG_PARAM	= 0x5166,	//!<���ô���led���ƿ��ֶ�Уʱ����
	ICE_CAMERA_CONFIG_TYPE_SERIAL_LED_CARD_COMMON_TIME_CFG_PARAM_RSP	= 0x5167,	//!<���ô���led���ƿ��ֶ�Уʱ����Ӧ��

	ICE_CAMERA_CONFIG_TYPE_CONTROL_SERIAL_CARD_COMMON_BASE_PARAM  = 0x5168,			//!< ���ڿ��ƿ��������������趨
	ICE_CAMERA_CONFIG_TYPE_CONTROL_SERIAL_CARD_COMMON_BASE_PARAM_RSP  = 0x5169,		//!<  ���ڿ��ƿ��������������趨Ӧ��
	
	ICE_CAMERA_CONFIG_TYPE_SET_ENCRYPT_PARAM		= 0x516A,		//!< ���������������
	ICE_CAMERA_CONFIG_TYPE_SET_ENCRYPT_PARAM_RSP	= 0x516B,		//!< ���������������Ӧ��

	ICE_CAMERA_CONFIG_TYPE_SET_RS485_TRANS_TYPE_SFM = 0x516C,		//!<���� 485����͸������
	ICE_CAMERA_CONFIG_TYPE_SET_RS485_TRANS_TYPE_SFM_RSP = 0x516D, //!<���� 485����͸������Ӧ��

	ICE_CAMERA_CONFIG_TYPE_GET_RS485_TRANS_TYPE_SFM = 0x516E,		//!<��ȡ 485����͸������
	ICE_CAMERA_CONFIG_TYPE_GET_RS485_TRANS_TYPE_SFM_RSP = 0x516F, //!<��ȡ 485����͸������Ӧ��


	ICE_CAMERA_CONFIG_TYPE_SET_DEVICE_PARAM		= 0x5170,		//!< �����豸��Ϣ����	
	ICE_CAMERA_CONFIG_TYPE_SET_DEVICE_PARAM_RSP	= 0x5171,		//!< �����豸��Ϣ����Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_DEVICE_PARAM		= 0x5172,		//!< ��ȡ�豸��Ϣ����	
	ICE_CAMERA_CONFIG_TYPE_GET_DEVICE_PARAM_RSP	= 0x5173,		//!< ��ȡ�豸��Ϣ����Ӧ��

	ICE_CAMERA_CONFIG_TYPE_SET_ALARM_IN_EXT_PARAM		= 0x5174,		//!< ���ö���ı����������	
	ICE_CAMERA_CONFIG_TYPE_SET_ALARM_IN_EXT_PARAM_RSP	= 0x5175,		//!< ���ö���ı����������Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_ALARM_IN_EXT_PARAM		= 0x5176,		//!< ��ȡ����ı����������	
	ICE_CAMERA_CONFIG_TYPE_GET_ALARM_IN_EXT_PARAM_RSP	= 0x5177,		//!< ��ȡ����ı����������Ӧ��

	ICE_CAMERA_CONFIG_TYPE_SET_FAC_MODE = 0x5178,			//!<���ù���ģʽ
	ICE_CAMERA_CONFIG_TYPE_SET_FAC_MODE_RSP = 0x5179,		//!<���ù���ģʽӦ��



	//up to 0x5300 for 83C reserved
	ICE_CAMERA_CONFIG_TYPE_SET_USER_LICENSE	= 0x5300,                //!< �����Զ���У����Ϣ
	ICE_CAMERA_CONFIG_TYPE_SET_USER_LICENSE_RSP	= 0x5301,            //!< �����Զ���У����ϢӦ��
	ICE_CAMERA_CONFIG_TYPE_CHECK_USER_LICENSE	= 0x5302,            //!< У���Զ���У����Ϣ
	ICE_CAMERA_CONFIG_TYPE_CHECK_USER_LICENSE_RSP	= 0x5303,	     //!< У���Զ���У����ϢӦ��
	ICE_CAMERA_CONFIG_TYPE_GET_RTSP_SESSION_COUNT = 0x5304,		//!<��ȡ��Ƶ����·��
	ICE_CAMERA_CONFIG_TYPE_GET_RTSP_SESSION_COUNT_RSP = 0x5305,	//!<��ȡ��Ƶ����·��Ӧ��

	ICE_CAMERA_CONFIG_TYPE_RESET_USER_LICENSE = 0x5306,			//!<��λ�û��Զ���У����Ϣ
	ICE_CAMERA_CONFIG_TYPE_RESET_USER_LICENSE_RSP = 0x5307,		//!<��λ�û��Զ���У����ϢӦ��

	ICE_CAMERA_CONFIG_TYPE_HAS_USER_LICENSE = 0x5308,			//!<�Ƿ����û��Զ���У��
	ICE_CAMERA_CONFIG_TYPE_HAS_USER_LICENSE_RSP = 0x5309,		//!<�Ƿ����û��Զ���У��Ӧ��


	ICE_CAMERA_CONFIG_TYPE_GET_DIVISOR_CTL_LIGHT_CONFIG = 0x530a,		//!<��ȡʱ�οصƲ���
	ICE_CAMERA_CONFIG_TYPE_GET_DIVISOR_CTL_LIGHT_CONFIG_RSP = 0x530b,	//!<��ȡʱ�οصƲ���Ӧ��

	ICE_CAMERA_CONFIG_TYPE_SET_DIVISOR_CTL_LIGHT_CONFIG = 0x530c,		//!<����ʱ�οصƲ���
	ICE_CAMERA_CONFIG_TYPE_SET_DIVISOR_CTL_LIGHT_CONFIG_RSP = 0x530d,	//!<����ʱ�οصƲ���Ӧ��

	ICE_CAMERA_CONFIG_TYPE_SET_NORMAL_AF_ZOOM = 0x530e,		//!<���õ��� �䱶
	ICE_CAMERA_CONFIG_TYPE_SET_NORMAL_AF_ZOOM_RSP = 0x530f,	//!<���õ���Ӧ��

	ICE_CAMERA_CONFIG_TYPE_SET_NORMAL_AF_RESET	= 0x5310,// �۽���λ
	ICE_CAMERA_CONFIG_TYPE_SET_NORMAL_AF_RESET_RSP	= 0x5311,

	ICE_CAMERA_CONFIG_TYPE_SET_NORMAL_FOCUS_FAR	= 0x5312,// ������Զ
	ICE_CAMERA_CONFIG_TYPE_SET_NORMAL_FOCUS_FAR_RSP	= 0x5313,

	ICE_CAMERA_CONFIG_TYPE_SET_NORMAL_FOCUS_NEAR	= 0x5314,// ���� ���
	ICE_CAMERA_CONFIG_TYPE_SET_NORMAL_FOCUS_NEAR_RSP = 0x5315,

	ICE_CAMERA_CONFIG_TYPE_GET_SCENE_MODE = 0x5316, 	//!<��ȡ����ģʽ
	ICE_CAMERA_CONFIG_TYPE_GET_SCENE_MODE_RSP = 0x5317, //!<��ȡ����ģʽӦ��

	ICE_CAMERA_CONFIG_TYPE_SET_SCENE_MODE = 0x5318, 	//!<���ó���ģʽ
	ICE_CAMERA_CONFIG_TYPE_SET_SCENE_MODE_RSP = 0x5319, //!<���ó���ģʽӦ��

	ICE_CAMERA_CONFIG_TYPE_AUDIO_TEST = 0x531a, 	// ��Ƶ�ػ�����
	ICE_CAMERA_CONFIG_TYPE_AUDIO_TEST_RSP = 0x531b, //  ��Ƶ�ػ�����  Ӧ��


	ICE_CAMERA_CONFIG_TYPE_GET_LOG_CONFIG = 0x531c,		//!<��ȡ��־����
	ICE_CAMERA_CONFIG_TYPE_GET_LOG_CONFIG_RSP = 0x531d,	//!<��ȡ��־����Ӧ��

	ICE_CAMERA_CONFIG_TYPE_SET_LOG_CONFIG = 0x531e,		//!<������־����
	ICE_CAMERA_CONFIG_TYPE_SET_LOG_CONFIG_RSP = 0x531f,	//!<������־����Ӧ��

	ICE_CAMERA_CONFIG_TYPE_SET_OFFLINE_LED_CONFIG = 0x5320,             //!<�����ѻ�LED������Ϣ
	ICE_CAMERA_CONFIG_TYPE_SET_OFFLINE_LED_CONFIG_RSP = 0x5321,         //!>�����ѻ�LED������ϢӦ��
	ICE_CAMERA_CONFIG_TYPE_GET_OFFLINE_LED_CONFIG = 0x5322,             //!> ��ȡ�ѻ�LED������Ϣ
	ICE_CAMERA_CONFIG_TYPE_GET_OFFLINE_LED_CONFIG_RSP = 0x5323,         //!>��ȡ�ѻ�LED������ϢӦ��

	ICE_CAMERA_CONFIG_TYPE_SET_OFFLINE_CHARGE_RULE = 0x5324,             //!<�����ѻ��Ʒѹ���
	ICE_CAMERA_CONFIG_TYPE_SET_OFFLINE_CHARGE_RULE_RSP = 0x5325,         //!>�����ѻ��Ʒѹ���Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_OFFLINE_CHARGE_RULE = 0x5326,             //!> ��ȡ�ѻ��Ʒѹ���
	ICE_CAMERA_CONFIG_TYPE_GET_OFFLINE_CHARGE_RULE_RSP = 0x5327,         //!>��ȡ�ѻ��Ʒѹ���Ӧ��

	ICE_CAMERA_CONFIG_TYPE_SET_OFFLINE_MULTICAST = 0x5328,             //!<�����ѻ��Ʒ��鲥��Ϣ
	ICE_CAMERA_CONFIG_TYPE_SET_OFFLINE_MULTICAST_RSP = 0x5329,         //!>�����ѻ��Ʒ��鲥��ϢӦ��
	ICE_CAMERA_CONFIG_TYPE_GET_OFFLINE_MULTICAST = 0x532a,             //!> ��ȡ�ѻ��Ʒ��鲥��Ϣ
	ICE_CAMERA_CONFIG_TYPE_GET_OFFLINE_MULTICAST_RSP = 0x532b,         //!>��ȡ�ѻ��Ʒ��鲥��ϢӦ��

	ICE_CAMERA_CONFIG_TYPE_READ_OFFLINE_VEHICLE_INFO_LIST		= 0x532c,		//!< ���������ڳ���Ϣ
	ICE_CAMERA_CONFIG_TYPE_READ_OFFLINE_VEHICLE_INFO_LIST_RSP	= 0x532d,		//!< ���������ڳ���ϢӦ��

	ICE_CAMERA_CONFIG_TYPE_GET_DEVICE_INFO  = 0x532e,                  //��ȡ���ƻ��汾��Ϣ
	ICE_CAMERA_CONFIG_TYPE_GET_DEVICE_INFO_RSP = 0x532f,               //��ȡ���ƻ��汾��ϢӦ��

	ICE_CAMERA_CONFIG_TYPE_OCD_RMALLDB	= 0x5331,						//!< ɾ����������
	ICE_CAMERA_CONFIG_TYPE_OCD_RMALLDB_RSP	= 0x5332,					//!<  ɾ����������Ӧ��

	ICE_CAMERA_CONFIG_TYPE_GET_ICE_OCD_TO_LED	= 0x5333,			    //!<��ȡ�Ʒ���Ϣ
	ICE_CAMERA_CONFIG_TYPE_GET_ICE_OCD_TO_LED_RSP	= 0x5334,			//!<��ȡ�Ʒ���ϢӦ��

	ICE_CAMERA_CONFIG_TYPE_READ_OFFLINE_COST_LIST	= 0x5337,				//!<�����շѼ�¼
	ICE_CAMERA_CONFIG_TYPE_READ_OFFLINE_COST_LIST_RSP	= 0x5338,			//!<�����շѼ�¼Ӧ��

	ICE_CAMERA_CONFIG_TYPE_GET_MAIN_SUB_MODE_CFG	= 0x5339,			//!<��ȡ����ģʽ����
	ICE_CAMERA_CONFIG_TYPE_GET_MAIN_SUB_MODE_CFG_RSP	= 0x533a,		//!<��ȡ����ģʽ����Ӧ��

	ICE_CAMERA_CONFIG_TYPE_SET_MAIN_SUB_MODE_CFG	= 0x533b,			//!<��������ģʽ����
	ICE_CAMERA_CONFIG_TYPE_SET_MAIN_SUB_MODE_CFG_RSP	= 0x533c,		//!<��������ģʽ����Ӧ��

	ICE_CAMERA_CONFIG_TYPE_SET_ICE_OCD_TO_VDC	= 0x533d,				//!<�ѻ��Ʒ��ϱ���Ϣ
	ICE_CAMERA_CONFIG_TYPE_SET_ICE_OCD_TO_VDC_RSP	= 0x533e,           //!<�ѻ��Ʒ��ϱ���ϢӦ��



	ICE_CAMERA_CONFIG_TYPE_SET_RELAY_OUT3		= 0x533f,				//!< ���ÿ�����3���
	ICE_CAMERA_CONFIG_TYPE_SET_RELAY_OUT3_RSP	= 0x5340,				//!< ���ÿ�����3���Ӧ��

	ICE_CAMERA_CONFIG_TYPE_SET_RELAY_OUT4		= 0x5341,				//!< ���ÿ�����4���
	ICE_CAMERA_CONFIG_TYPE_SET_RELAY_OUT4_RSP	= 0x5342,				//!< ���ÿ�����4���Ӧ��

	ICE_CAMERA_CONFIG_TYPE_READ_LOCAL_OFFLINE_COST_LIST	= 0x5343,		//!<���������շѼ�¼
	ICE_CAMERA_CONFIG_TYPE_READ_LOCAL_OFFLINE_COST_LIST_RSP= 0x5344,		//!<���������շѼ�¼Ӧ��


	ICE_CAMERA_CONFIG_TYPE_UPDATE_VACANCIES = 0x5354,                                     //!<ʣ�೵λ������
	ICE_CAMERA_CONFIG_TYPE_UPDATE_VACANCIES_RSP = 0x5355,			 //!<ʣ�೵λ������Ӧ��

	ICE_CAMERA_CONFIG_TYPE_SET_TALK_BACK_VOLUME = 0x5356,			  //!<set talk back volume
	ICE_CAMERA_CONFIG_TYPE_SET_TALK_BACK_VOLUME_RSP = 0x5357,			 //!<

	ICE_CAMERA_CONFIG_TYPE_GET_TALK_BACK_VOLUME = 0x5358,			  //!<get talk back volume
	ICE_CAMERA_CONFIG_TYPE_GET_TALK_BACK_VOLUME_RSP = 0x5359,			 //!<		


	ICE_CAMERA_CONFIG_TYPE_SET_UID = 0x5360,			  //!<set UID
	ICE_CAMERA_CONFIG_TYPE_SET_UID_RSP = 0x5361,			 //!<

	ICE_CAMERA_CONFIG_TYPE_GET_UID = 0x5362,			  //!<get
	ICE_CAMERA_CONFIG_TYPE_GET_UID_RSP = 0x5363,			 //!<		


	//xinjiang
	ICE_CAMERA_CONFIG_TYPE_SET_HTTP_POST2_PARAM		= 0x5366,		//!< ����HTTP POST����
	ICE_CAMERA_CONFIG_TYPE_SET_HTTP_POST2_PARAM_RSP	= 0x5367,		//!< ����HTTP POST����Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_HTTP_POST2_PARAM		= 0x5368,		//!< ��ȡHTTP POST����
	ICE_CAMERA_CONFIG_TYPE_GET_HTTP_POST2_PARAM_RSP	= 0x5369,		//!< ��ȡHTTP POST����Ӧ��

	ICE_CAMERA_CONFIG_TYPE_SET_CTP_CFG = 0x536A,			 //!<����CTP����
	ICE_CAMERA_CONFIG_TYPE_SET_CTP_CFG_RSP = 0x536B,		 //!>����CTP����Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_CTP_CFG = 0x536C,			 //!> ��ȡCTP����
	ICE_CAMERA_CONFIG_TYPE_GET_CTP_CFG_RSP = 0x536D,		 //!>��ȡCTP����Ӧ��

	ICE_CAMERA_CONFIG_TYPE_SET_NETWORK_DHCP = 0x5370,  		   //!< DHCP ʹ�ܿ�����ر�
	ICE_CAMERA_CONFIG_TYPE_SET_NETWORK_DHCP_RSP = 0x5371,   	   //!<DHCP ʹ�ܿ����ر�Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_NETWORK_DHCP = 0x5372,		   //!<��ȡʹ��״̬
	ICE_CAMERA_CONFIG_TYPE_GET_NETWORK_DHCP_RSP = 0x5373,	   //!<��ȡʹ��״̬Ӧ��

	ICE_CAMERA_CONFIG_TYPE_SET_CAMERA_4G_PARAM	= 0x5374,		//!<�������4G��Ϣ����
	ICE_CAMERA_CONFIG_TYPE_SET_CAMERA_4G_PARAM_RSP	= 0x5375,	//!<�������4G��Ϣ��������Ӧ��	
	ICE_CAMERA_CONFIG_TYPE_GET_CAMERA_4G_PARAM	= 0x5376,		//!<��ȡ���4G����
	ICE_CAMERA_CONFIG_TYPE_GET_CAMERA_4G_PARAM_RSP	= 0x5377,	//!<��ȡ���4G��������Ӧ��	

	ICE_CAMERA_CONFIG_TYPE_SET_CAMERA_ONVIF_CONFIG	= 0x5378,  	     //!<ONVIF ���ܿ���/�ر�
	ICE_CAMERA_CONFIG_TYPE_SET_CAMERA_ONVIF_CONFIG_RSP	= 0x5379,	     //!<ONVIF���ܿ���/�ر�Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_CAMERA_ONVIF_CONFIG	= 0x537A,             //!<��ȡONVIFʹ��״̬
	ICE_CAMERA_CONFIG_TYPE_GET_CAMERA_ONVIF_CONFIG_RSP	= 0x537B,             //!<��ȡONVIFʹ��״̬Ӧ��	


	ICE_CAMERA_CONFIG_TYPE_SET_HTTP_POST_NEW_PARAM		= 0x5380,		//!< ����ICE_HTTP_POST_NEW_PARAM
	ICE_CAMERA_CONFIG_TYPE_SET_HTTP_POST_NEW_PARAM_RSP	= 0x5381,		//!< ����ICE_HTTP_POST_NEW_PARAMӦ��
	ICE_CAMERA_CONFIG_TYPE_GET_HTTP_POST_NEW_PARAM		= 0x5382,		//!< ��ȡICE_HTTP_POST_NEW_PARAM
	ICE_CAMERA_CONFIG_TYPE_GET_HTTP_POST_NEW_PARAM_RSP	= 0x5383,		//!< ��ȡICE_HTTP_POST_NEW_PARAMӦ��


	ICE_NEW_CAMERA_SET_OLD_UPDATE_MODE_ENABLE  = 0x5384,  //!< ����ICE_NEW_CAMERA_SET_OLD_UPDATE_MODE_ENABLE
	ICE_NEW_CAMERA_SET_OLD_UPDATE_MODE_ENABLE_RSP = 0x5385,  //!< 
	ICE_NEW_CAMERA_GET_OLD_UPDATE_MODE_ENABLE  = 0x5386,  //!< 
	ICE_NEW_CAMERA_GET_OLD_UPDATE_MODE_ENABLE_RSP = 0x5387,  //!< 

	ICE_NEW_CAMERA_SET_USER_MODEL                = 0x5388,  //!< ��������û��ͺ�
	ICE_NEW_CAMERA_SET_USER_MODEL_RSP            = 0x5389,  //!< 
	ICE_NEW_CAMERA_GET_USER_MODEL				 = 0x538A,  //!< 
	ICE_NEW_CAMERA_GET_USER_MODEL_RSP            = 0x538B,  //!< 

	ICE_SET_PING_SERVER_ACTION                = 0x538C,		//!< ���� ping ������ ����
	ICE_SET_PING_SERVER_ACTION_RSP            = 0x538D,		//!< 
	ICE_GET_PING_SERVER_ACTION		        = 0x538E,		//!< 
	ICE_GET_PING_SERVER_ACTION_RSP	        = 0x538F,		//!< 

	ICE_CAMERA_CONFIG_TYPE_SET_CLOUD_PARAM = 0x5390,           //!< ������ƽ̨����
	ICE_CAMERA_CONFIG_TYPE_SET_CLOUD_PARAM_RSP = 0x5391,       //!< ������ƽ̨����Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_CLOUD_PARAM = 0x5392,           //!< ��ȡ��ƽ̨����
	ICE_CAMERA_CONFIG_TYPE_GET_CLOUD_PARAM_RSP = 0x5393,       //!< ��ȡ��ƽ̨����Ӧ��

	ICE_CAMERA_CONFIG_TYPE_SET_NETWORK_DIAGNOSTICS  = 0x5394,  //!< ���� ������� network diagnostics 
	ICE_CAMERA_CONFIG_TYPE_SET_NETWORK_DIAGNOSTICS_RSP = 0x5395,  //!< 
	ICE_CAMERA_CONFIG_TYPE_STOP_NETWORK_DIAGNOSTICS  = 0x5396,  //!< ֹͣ ������� network diagnostics 
	ICE_CAMERA_CONFIG_TYPE_STOP_NETWORK_DIAGNOSTICS_RSP = 0x5397,  //!< 
	ICE_CAMERA_CONFIG_TYPE_GET_NETWORK_DIAGNOSTICS  = 0x5398,  //!< 
	ICE_CAMERA_CONFIG_TYPE_GET_NETWORK_DIAGNOSTICS_RSP = 0x5399,  //!< 

	ICE_CAMERA_CONFIG_TYPE_SET_CAMERA_ALIVETIME = 0x539A,  //!<��������ʱ��
	ICE_CAMERA_CONFIG_TYPE_SET_CAMERA_ALIVETIME_RSP = 0x539B, //!<��������ʱ��Ӧ��

	ICE_CAMERA_CONFIG_TYPE_GET_CAMERA_ALIVETIME = 0x539C,  //!<��ȡ��ǰʹ����Ϣ
	ICE_CAMERA_CONFIG_TYPE_GET_CAMERA_ALIVETIME_RSP = 0x539D, //!<��ȡ��ǰʹ����ϢӦ��

	ICE_CAMERA_CONFIG_TYPE_SET_TLDGATE_PARAM = 0x53AA,     //!<�����������բ���� 
	ICE_CAMERA_CONFIG_TYPE_SET_TLDGATE_PARAM_RSP = 0x53AB,   //!<�����������բ����Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_TLDGATE_PARAM = 0x53AC,     //!<��ȡ�������բ����
	ICE_CAMERA_CONFIG_TYPE_GET_TLDGATE_PARAM_RSP = 0x53AD,    //!<��ȡ�������բ����Ӧ��

	ICE_CAMERA_CONFIG_TYPE_SET_TIMEZONE = 0x53AE,                   //!<�������ʱ��
	ICE_CAMERA_CONFIG_TYPE_SET_TIMEZONE_RSP = 0x53AF,
	ICE_CAMERA_CONFIG_TYPE_GET_TIMEZONE = 0x53B0,                   //!<��ȡ���ʱ��
	ICE_CAMERA_CONFIG_TYPE_GET_TIMEZONE_RSP = 0x53B1,

	ICE_CAMERA_CONFIG_TYPE_SET_NTP_PARAM = 0x53B2,                  //!<����NTP����
	ICE_CAMERA_CONFIG_TYPE_SET_NTP_PARAM_RSP = 0x53B3,
	ICE_CAMERA_CONFIG_TYPE_GET_NTP_PARAM = 0x53B4,                  //!<��ȡNTP����
	ICE_CAMERA_CONFIG_TYPE_GET_NTP_PARAM_RSP = 0x53B5,

	ICE_CAMERA_CONFIG_TYPE_SET_DISPLAY_PARAM = 0x53B6,     //!<����V88����һ����������ò���
	ICE_CAMERA_CONFIG_TYPE_SET_DISPLAY_PARAM_RSP = 0x53B7,
	ICE_CAMERA_CONFIG_TYPE_GET_DISPLAY_PARAM = 0x53B8,     //!<��ȡV88����һ����������ò���
	ICE_CAMERA_CONFIG_TYPE_GET_DISPLAY_PARAM_RSP = 0x53B9,

	ICE_CAMERA_CONFIG_TYPE_CLEAR_ADVERT_PIC = 0x53BA,     //!<���V88  ���ͼƬ
	ICE_CAMERA_CONFIG_TYPE_CLEAR_ADVERT_PIC_RSP = 0x53BB,
	
	ICE_CAMERA_CONFIG_TYPE_GET_SUPPORT_NEW_INTERFACE = 0x53BC, //��ȡ֧���½ӿڵĹ���ģ��
	ICE_CAMERA_CONFIG_TYPE_GET_SUPPORT_NEW_INTERFACE_RSP = 0x53BD, //��ȡ֧���½ӿڵĹ���ģ��ظ�

	ICE_CAMERA_CONFIG_TYPE_SET_NEW_SYSTEM_TIME			= 0x53BE,		//!< �������ϵͳʱ��
	ICE_CAMERA_CONFIG_TYPE_SET_NEW_SYSTEM_TIME_RSP		= 0x53BF,		//!< �������ϵͳʱ��Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_NEW_SYSTEM_TIME			= 0x53C0,		//!< ��ȡ���ϵͳʱ��
	ICE_CAMERA_CONFIG_TYPE_GET_NEW_SYSTEM_TIME_RSP		= 0x53C1,		//!< ��ȡ���ϵͳʱ��Ӧ��
	ICE_CAMERA_CONFIG_TYPE_SET_SNAPOSD_CFG				= 0x53CE,		//!< ���ý�ͼͼƬOSD����
	ICE_CAMERA_CONFIG_TYPE_SET_SNAPOSD_CFG_RSP			= 0x53CF,		//!< ���ý�ͼͼƬOSD����Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_SNAPOSD_CFG				= 0x53D0,		//!< ��ȡ��ͼͼƬOSD����
	ICE_CAMERA_CONFIG_TYPE_GET_SNAPOSD_CFG_RSP			= 0x53D1,		//!< ��ȡ��ͼͼƬOSD����Ӧ��
	ICE_CAMERA_CONFIG_TYPE_GET_AUDIO_DIR_FREE_SPACE 	= 0x53D6,		//!< ��ȡ��Ƶ����ļ���ʣ��ռ䣬KB
	ICE_CAMERA_CONFIG_TYPE_GET_AUDIO_DIR_FREE_SPACE_RSP = 0x53D7,       //!< ��ȡ��Ƶ����ļ���ʣ��ռ�Ӧ��	
	ICE_CAMERA_CONFIG_TYPE_CLEAN_AUDIO_DIR       	= 0x53D8,			//!< �����Ƶ�ļ�
	ICE_CAMERA_CONFIG_TYPE_CLEAN_AUDIO_DIR_RSP     	= 0x53D9,			//!< �����Ƶ�ļ�Ӧ��	
	ICE_CAMERA_CONFIG_TYPE_UPLOAD_AUDIO_FILE       	= 0x53DA,			//!< �ϴ���Ƶ�ļ�
	ICE_CAMERA_CONFIG_TYPE_UPLOAD_AUDIO_FILE_RSP    = 0x53DB,	    	//!< �ϴ���Ƶ�ļ�����

	ICE_CAMERA_CONFIG_TYPE_GET_MQTT_CFG = 0x540C, //!<��ȡmqttЭ��
	ICE_CAMERA_CONFIG_TYPE_GET_MQTT_CFG_RSP = 0x540D,
	ICE_CAMERA_CONFIG_TYPE_SET_MQTT_CFG = 0x540E, //!<����mqttЭ��
	ICE_CAMERA_CONFIG_TYPE_SET_MQTT_CFG_RSP = 0x540F,
	ICE_CAMERA_CONFIG_TYPE_GET_MQTT_CFG_DEF = 0x5410, //!<��ȡĬ��mqttЭ�����
	ICE_CAMERA_CONFIG_TYPE_GET_MQTT_CFG_DEF_RSP = 0x5411,

	ICE_CAMERA_CONFIG_TYPE_FS_GET_TALKBACK_CFG = 0X550A,				//��ȡ�Խ�����
	ICE_CAMERA_CONFIG_TYPE_FS_GET_TALKBACK_CFG_RSP = 0X550B,			//��ȡ�Խ�����Ӧ��
	ICE_CAMERA_CONFIG_TYPE_FS_SET_TALKBACK_CFG = 0X550C,				//���öԽ�����
	ICE_CAMERA_CONFIG_TYPE_FS_SET_TALKBACK_CFG_RSP = 0X550D,			//���öԽ�����Ӧ��

	/***************��������Ų�֪��Ϊʲô����0x6001��ʼ��***********************/
	ICE_CAMERA_CONFIG_TYPE_SET_PRODUCT_MODEL = 0x6001,//���ò�Ʒ�ͺ�
	ICE_CAMERA_CONFIG_TYPE_SET_PRODUCT_MODEL_RSP = 0x6002,//���ò�Ʒ�ͺŻظ�
	ICE_CAMERA_CONFIG_TYPE_GET_PRODUCT_MODEL = 0x6003,//��ȡ��Ʒ�ͺ�
	ICE_CAMERA_CONFIG_TYPE_GET_PRODUCT_MODEL_RSP = 0x6004,//��ȡ��Ʒ�ͺŻظ�

	ICE_CAMERA_CONFIG_TYPE_BIND_IO_IN_PRO = 0x6007,//��IO����
	ICE_CAMERA_CONFIG_TYPE_BIND_IO_IN_PRO_RSP = 0x6008,//��IO����ظ�
	ICE_CAMERA_CONFIG_TYPE_BIND_IO_OUT_PRO = 0x6009,//��IO���
	ICE_CAMERA_CONFIG_TYPE_BIND_IO_OUT_PRO_RSP = 0x600a,//��IO����ظ�

	ICE_CAMERA_CONFIG_TYPE_ADD_SERAIL_PRO = 0x600b,	//���Ӵ���Э��
	ICE_CAMERA_CONFIG_TYPE_ADD_SERAIL_PRO_RSP = 0x600c,	//���Ӵ���Э��ظ�
	ICE_CAMERA_CONFIG_TYPE_DEL_SERAIL_PRO = 0x600d,//ɾ������Э��
	ICE_CAMERA_CONFIG_TYPE_DEL_SERAIL_PRO_RSP = 0x600e,//ɾ������Э��ظ�
	ICE_CAMERA_CONFIG_TYPE_BIND_SERAIL_PRO = 0x6010,//�󶨴���Э��	
	ICE_CAMERA_CONFIG_TYPE_BIND_SERAIL_PRO_RSP = 0x6011,//�󶨴���Э��ظ�
	ICE_CAMERA_CONFIG_TYPE_GET_SERIAL_PRO_LIST = 0x6012,//��ȡ����Э���б�
	ICE_CAMERA_CONFIG_TYPE_GET_SERIAL_PRO_LIST_RSP = 0x6013,//��ȡ����Э���б�ظ�

	ICE_CAMERA_CONFIG_TYPE_GET_TIME_SYNC_CFG						= 0x61B0,//��ȡУʱ��������
	ICE_CAMERA_CONFIG_TYPE_GET_TIME_SYNC_CFG_RSP 					= 0x61B1,//��ȡУʱ�������ûظ�
	ICE_CAMERA_CONFIG_TYPE_SET_TIME_SYNC_CFG						= 0x61B2,//��ȡУʱ��������
	ICE_CAMERA_CONFIG_TYPE_SET_TIME_SYNC_CFG_RSP 					= 0x61B3,//����Уʱ��������
	ICE_CAMERA_CONFIG_TYPE_GET_TIME_SYNC_CFG_DEF					= 0x61B4,//����Уʱ��������
	ICE_CAMERA_CONFIG_TYPE_GET_TIME_SYNC_CFG_DEF_RSP 				= 0x61B5,//��ȡУʱ����Ĭ������
	ICE_CAMERA_CONFIG_TYPE_SET_REMCTRL_KEYFUNCTION					= 0x6204,//����ң������ֵ
	ICE_CAMERA_CONFIG_TYPE_SET_REMCTRL_KEYFUNCTION_RSP				= 0x6205,//����ң������ֵ�ظ�
	ICE_CAMERA_CONFIG_TYPE_GET_REMCTRL_KEYFUNCTION					= 0x6206,//��ȡң������ֵ
	ICE_CAMERA_CONFIG_TYPE_GET_REMCTRL_KEYFUNCTION_RSP				= 0x6207,//��ȡң������ֵ�ظ�

	/***************�����������֮���ڲ�����Ϳͻ��������ͻ***********************/
	ICE_CAMERA_INNER_CONFIG_TYPE_SET_ICE_OCD_TO_VDC	= 0x9001,				//!<�ѻ��Ʒ��ϱ���Ϣ
	ICE_CAMERA_INNER_CONFIG_TYPE_SET_ICE_OCD_TO_VDC_RSP	= 0x9002,		//!<?�ѻ��Ʒ��ϱ���ϢӦ��

	ICE_CAMERA_CONFIG_TYPE_END                      = 0x941f,

} ICE_CAMERA_CONFIG_TYPE_E;


//NTP���ýṹ��
typedef struct T_SntpCfg{
	ICE_S32   iEn;            //NTPʹ��
	ICE_S32   iSyncPeriod;    //ͬ�������������ͬ��һ�Σ���λ��
	ICE_S32   iSyncDiff;      //ͬ����ֵ����������������ʱ�������������ϲ�ͬ������λ��
	ICE_S32   iSrvPort;       //NTP�������˿�
	ICE_S8    acSrvAddr[128]; //NTP��������ַ
	ICE_S8    acResearve[256]; 
}T_SntpCfg;

typedef struct tagT_TimeZone
{
	ICE_S8 acTimeZoneStr[32];
	ICE_S8 acResearve[256];
} T_TimeZone;

//ʱ����Ϣ�ṹ��
//��������������ʱ���ʾ
typedef struct T_TimeInfo{
	ICE_S32 iYear;   //�꣬������ݣ���2019��ȡֵΪ2019
	ICE_S32 iMon;    //�£�ȡֵ��Χ��1-12
	ICE_S32 iDay;    //�գ�ȡֵ��Χ��1-31
	ICE_S32 iHour;   //ʱ��24Сʱ�ƣ�ȡֵ��Χ��0-23
	ICE_S32 iMin;    //�֣�ȡֵ��Χ��0-59
	ICE_S32 iSec;    //�룬ȡֵ��Χ��0-59
}T_TimeInfo;

typedef struct T_TimeCfgInfo{
	ICE_S8 acReqSrcIp[16];//����ԴIP��ַ��
	ICE_S8 acReqSrcDesc[16];//����Դ��������"HX-CGI""HX-SDK""HX-USERAPP""HX-CLIENT"������ȫ�ǿͻ�����
	T_TimeInfo tLocalTimeInfo;//����ʱ����Ϣ
	ICE_S8 acResearve[256];
}T_TimeCfgInfo;


typedef struct{
	ICE_S32 time_sync_mode; //0 �ֶ���1ntp,2 ����
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

//����·��
#define TLD_GATE_CONFIG "/data/config/TldGateCfg.json"

typedef struct T_TldGateCfg
{
	ICE_S32 iEn;                     //�Ƿ�ʹ���������բЭ��.[0,1] 0:��ʹ�� 1:ʹ�� 
	ICE_S32 iInterval;               //��������,��λ:�� ��Ĭ��10s
	ICE_S32 iResendInterval;       //Ӧ�������ش����,������  Ĭ��30 - 1320 min��Ĭ��120min(2h)
	ICE_U8 aucDeviceKey[TLD_GATE_KEY_LEN];        //�豸key
	ICE_U8 aucDeviceSecret[TLD_GATE_KEY_LEN];     //�豸��Կ
	ICE_U8 aucProductKey[TLD_GATE_KEY_LEN];       //��Ʒkey
	ICE_U8 aucProductSecret[TLD_GATE_KEY_LEN];    //��Ʒ��Կ
	ICE_U8 aucRouteUrl[TLD_GATE_MAX_ROUTESERVER_NUM][TLD_GATE_ROUTEURLLEN];  // ·�ɷ�������ַ ֧�ֶ��·�ɵ�ַ����|��ʽ�ָ�
	ICE_S32 iOpenGateTimeout;      //����λ��ʱ 0-600 ��λs  
	ICE_S32 iCloseGateTimeout;     //�ص�λ��ʱ 0-600 ��λs
	ICE_S32 iMode;				  //0 ��ͨģʽ 1 �ظ�ģʽ
	ICE_S32 iCoilCheckTimeout;   //�ظ�ģʽ��ⳬʱʱ�� ��Χ 0-30s
	ICE_U8 aucReserved[240];             // Ԥ������
}T_TldGateCfg;
//////////////////////////////////////////////////////////////////////////

#define DIAG_RESU_MAXLEN  4096*2
/*���������ز���*/
typedef struct
{
	unsigned char ucNetworkDiagCmd[100];         //�ͻ��·�������ϵ�ָ�� 
	unsigned char ucDiagResuBuff[DIAG_RESU_MAXLEN];    //������Ͻ�����
	unsigned char ucReserved[10];
}NETWORK_DIAGNOSTICS_PARAM;

#define CLOUD_ID_LEN 64
#define CLOUD_NET_LEN 128

typedef struct _CLOUD_CFG_PARAM_S
{
	ICE_S32 cloudEn;			//�Ƿ��cloud ���ܣ�Ĭ�Ϲر�.[0,1] 0:�ر� 1:����
	ICE_S32 mode;				//����ģʽ.����ֻ��ģʽ1=YDT
	ICE_S32 sslEn;			//SSLʹ�ܣ�Ĭ�ϲ�ʹ��
	ICE_S32 sslPort;			//SSL�˿ڣ�Ĭ��443
	ICE_S32 camIdType;		//camId����.[0,1] 0:ʹ�����MAC��ַ 1:ʹ�����UUID
	ICE_S32 interval;			//��������,��λ:��.[0,300]��0=������
	ICE_S32 maxSendCnt;		//����������, 1-3��Ĭ��Ϊ:2
	ICE_S32 fullImgEn;		//�Ƿ���ȫ��ͼ��
	ICE_S32 miniImgEn;		//�Ƿ��ͳ�����дͼ��
	ICE_S32 ioInEn;			//����IO״̬�ϱ�ʹ��
	ICE_U8 ioInNum[8];		//ָ���ϱ�����IO������Ч��ioInNum[0]��Ӧ����IO1��ioInNum[1]=IO2,ioInNum[2]=IO3,ioInNum[3]=IO4��4-7Ԥ����
	ICE_U8 parkId[CLOUD_ID_LEN];		//ͣ����id,ֻ֧��Ӣ�ġ����֡�'-',like:GD-SZ-A000001

	ICE_U8 cloudDomain[CLOUD_NET_LEN];	// ��ƽ̨��������like:www.baidu.com
	ICE_U8 path[CLOUD_NET_LEN];		// ��ƽ̨�����·��
	ICE_S32 port;				// ��ƽ̨���ʶ˿ڣ�Ĭ��Ϊ��80
	ICE_S32 syncTimeEn;		// ��ƽ̨ʱ��Уʱʹ��
	ICE_S32 syncTimeOffset;	// Уʱƫ����������λ�룬1-900,ƫ����ڸ�ֵ��Уʱ

	ICE_S32 osEn;				// �Ƿ�򿪶���洢���ܣ�Ĭ�Ϲر�.[0,1] 0:�ر� 1:����
	ICE_S32 osType;			// ����Э�����ͣ�0=aliyun,1=tencentyun,2=baiduyun,3=��������
	ICE_U8 osDomain[CLOUD_NET_LEN];	// ����洢��������like:bucket.endpoint
	ICE_S32 iPicUploadType;             // ͼƬ�ϴ���ʽ 0:�ֿ��ϴ�  1:һ���ϴ�

	ICE_U8 reserved[252];	// Ԥ������
	ICE_S32 extParamSize;		// CLOUD_CFG_PARAM_S Ϊ����������������ȫ�����ں��棬ÿ��ģʽ������Ҫ���������׸����������ﵽ������������ͬʱ��֧�ֶ��ⶨ�ơ�Ĭ��:0
} CLOUD_CFG_PARAM_S;

typedef struct tagT_CloudM2CfgParam
{
	ICE_S8 key[64];
	ICE_U8 reserved[128]; // Ԥ������
} T_CloudM2CfgParam;

typedef struct tagT_CloudM3CfgParam
{
	ICE_S8 accessKey[CLOUD_ID_LEN]; // ģʽ3ʱ��OSS_ACCESS_KEY
	ICE_S8 accessSecret[CLOUD_ID_LEN];// ģʽ3ʱ��OSS_ACCESS_KEY_SECRET
	ICE_U8 reserved[128]; // Ԥ������
} T_CloudM3CfgParam;

typedef struct T_CloudM4CfgParamV1
{
	ICE_S8 acAccessKey[CLOUD_ID_LEN];	   // ģʽ4ʱ��OSS_ACCESS_KEY
	ICE_S8 acAccessSecret[CLOUD_ID_LEN]; // ģʽ4ʱ��OSS_ACCESS_KEY_SECRET
} T_CloudM4CfgParamV1;

typedef struct
{
	int InVolume; //0- 10
	int OutVolume;//0- 10
	int as32Reserved[4]; //Ԥ������

} ICE_TALK_BACK_VOLUME_PARAM;

//!�����ѻ������������� 
typedef struct
{
	ICE_U32 u32Mode;             //����ģʽ�� 0 ������, 1 ����(ԭ���Ļ�ӭ����/һ·˳��), 2 ����+ƥ�������   Ĭ�� 2
	ICE_U32 u32Broadcast_order;     //����˳��   0 ����������  1�󲥱�����  2 �Ȳ��������ٲ���������Ϣ  Ĭ�� 2
	ICE_U32 u32Reserved[15];           
} OfflineAoParam;

//���մ洢���ն�mac list ����
typedef struct {
  ICE_S32 mac_list_size;  //  list����
  ICE_S8 phone_mac_list[100][18];
  ICE_S8 reserved[50*18];
} ICE_Phone_Mac_List;


//! �������ݻ���
typedef union
{
	ICE_U8 au8Buffer[ICE_BUF_SIZE_CONFIG];		//!< �������ݻ���
} ICE_CONFIG_DATA_INTERNAL_U;

//! \ingroup group_communication
//! ��������ͷ�����ݻ���
typedef struct  
{
	ICE_OPER_DATA_S stHead;					//!< ����ͷ
	ICE_CONFIG_DATA_INTERNAL_U unData;		//!< ��������
} ICE_CONFIG_DATA_S;

typedef struct
{
 ICE_U8 u8ModeNo;
 ICE_U8 u8Reserved[3];
 ICE_U32 u32BeginTime;//��ֵ��ÿ��00:00:00�����õ�����Чʱ�̵ķ�����
 ICE_U32 u32Interval;//��Чʱ���
 ICE_U8 u8Reserved1[52];
}ICE_SCENE_MODE_ST;

///////////////////////////////////////////////////////////////////////////////////////////////////
//! \ingroup group_communication
//! ������Ƶ����������
typedef enum
{
	ICE_VIDEO_STREAM_TYPE_BASE 						= 0x6000,		//!< ������Ƶ���������ͻ����ֶ�
	ICE_VIDEO_STREAM_TYPE_VENC_H264					= 0x6001,		//!< H264����
	ICE_VIDEO_STREAM_TYPE_VENC_MJPEG				= 0x6002,		//!< MJPEG����
	ICE_VIDEO_STREAM_TYPE_VENC_MPEG2				= 0x6004,		//!< MPEG2����
	ICE_VIDEO_STREAM_TYPE_VENC_MPEG4				= 0x6008,		//!< MPEG4����
	ICE_VIDEO_STREAM_TYPE_END						= 0x6009,		
}ICE_VIDEO_STREAM_E;

//led��ʾ�û��Զ�����Ϣ �ṹ��
typedef struct{
	char default_data[64];  //�޳���ʱ
	char blacklist_data[64]; //������
	char tmp_data[64];      // ��ʱ����
	char reserve[256];
} Led_Display_Pro1_Param;

// ���ڿ��ƿ�������������
typedef struct {
	int serial_card_type;		//��������Led ������������0 ��ʾled��1��ʾ������
	int serial_card_addr;		//������ƿ���ַ1~255
	int reserved[16];
}Led_Card_Serial_Common_param;

//led���ƿ���Э��2֮led�������ṹ��
typedef struct {
	int address;			//led���ĵ�ַ
	int mainsection;		//��������ַ����Χ00~199
	int subsection;			//��������ַ����Χ201~219
	int subsection_nor;		//��������ַ����Χ201~219����Ҫ���ڷ���Ȩ��
	int enter_mode;			//����ģʽ����Χ00~23 
	int stop_time;			//ͣ��ʱ��
	int stop_mode;			//ͣ��ģʽ	��Χ00~13
	int exit_mode;			//�˳�ģʽ	��Χ00~23
	unsigned char maintext[64];		//������ĳ����������ʾ���������������
	unsigned char subtext[64];		//�Ӳ���ĳ����������ʾ���������������
	unsigned char subtext_nor[64];   //��Ҫ���ڷ���Ȩ����ʾ����
	int reserved[16];
} Led_Card_2_Display_Cfg_param;

//led���ƿ���Э��2֮�������������ṹ��
typedef struct {
	int address;			//��������ַ 1~255
	int modify_addr_enable;	//�޸���������ַʹ�ܣ�Ĭ�� 0�����޸�
	int modify_addr;		//�޸���������ַ
	unsigned char whitelist_broadcasttext[50]; //��Ȩ������������������ Э��涨���50�ֽ�
	unsigned char normal_broadcasttext[50];	  //����Ȩ����������������	
	unsigned char reserved[20];
}Led_Card_2_attach_broadcast_cfg_param;

//led���ƿ���Э��2 �ṹ��
typedef struct {
	int relay_time;											//������ʱ�̵����պ�ʱ�� �ͻ�350-2000
	int change_addr_enable;									//�޸�led����ַʹ�ܣ�Ĭ�� 0�����޸�
	int change_addr_led;										//�޸�led���ĵ�ַ
	Led_Card_2_Display_Cfg_param led_protol_2_card[3];		//0 ��������led������,//1 ����ʱ��led������,// 2���ƺ���led������
	Led_Card_2_attach_broadcast_cfg_param broadcast_card;	//��������������
	int reserved[20];
}Led_Card_2_total_cfg_param;

//led���ƿ���Э��2 ����ģʽ
typedef enum {
	LED_CARD_2_IN_INSTANT_DISPLAY			= 0x00,		//������ʾ
	LED_CARD_2_IN_RIGHT_TO_LEFT				= 0x01,		//����������
	LED_CARD_2_IN_LEFT_TO_RIGHT				= 0x02,		//����������
	LED_CARD_2_IN_DOWN_TO_UP				= 0x03,		//����������
	LED_CARD_2_IN_UP_TO_DOWN				= 0x04,		//����������
	LED_CARD_2_IN_PULL_CURTAIN_TO_DOWN		= 0x05,		//��������ʽ
	LED_CARD_2_IN_PULL_CURTAIN_TO_UP		= 0x06,		//��������ʽ
	LED_CARD_2_IN_PULL_CURTAIN_TO_LEFT		= 0x07,		//��������ʽ
	LED_CARD_2_IN_PULL_CURTAIN_TO_RIGHT		= 0x08,		//��������ʽ
	LED_CARD_2_IN_BACK_LIGHT				= 0x09,		//����
	LED_CARD_2_IN_SPACE_OPERATION			= 0x0A,		//�޲���
	LED_CARD_2_IN_MEDIUM_SPEED_LEFT			= 0x0B,		//��������
	LED_CARD_2_IN_MEDIUM_SPEED_RIGHT		= 0x0C,		//��������
	LED_CARD_2_IN_VERBATIM_DISPLAY			= 0x0D,		//������ʾ
	LED_CARD_2_IN_OPEN_GATE_LEFT			= 0x0E,		//����դ
	LED_CARD_2_IN_OPEN_GATE_RIGHT			= 0x0F,		//���ҿ�դ
	LED_CARD_2_IN_SNOWFLAKE_DISPLAY			= 0x10,		//ѩ������
	LED_CARD_2_IN_ROW_DISPLAY				= 0x11,		//���г���
	LED_CARD_2_IN_COL_DISPLAY				= 0x12,		//���г���
	LED_CARD_2_IN_SLOW_SPEED_LEFT			= 0x13,		//��������
	LED_CARD_2_IN_SLOW_SPEED_RIGHT			= 0x14,		//��������
	LED_CARD_2_IN_SERIES_DISPLAY			= 0x15,		//�����ƶ�
	LED_CARD_2_IN_NONE_OPERATION			= 0x16,		//�޲���
	LED_CARD_2_IN_SLOW_SPEED_SERIES_DISPLAY = 0x17,		//���������ƶ�
	LED_CARD_2_IN_MAX_LED_BS_DISPLAY	
}led_card_2_insert_mode;

//led���ƿ���Э��2 ͣ��ģʽ
typedef enum {
	LED_CARD_2_REMAIN_MODE0		= 0x00,					//ͣ��
	LED_CARD_2_REMAIN_MODE1		= 0x01,					//ͣ�� 1/10
	LED_CARD_2_REMAIN_MODE2		= 0x02,					//ͣ�� 1/100
	LED_CARD_2_FAST_FLASH		= 0x03,  				//������˸
	LED_CARD_2_MIDEUM_FLASH		= 0x04,					//������˸
	LED_CARD_2_SLOW_FLASH		= 0x05,					//������˸
	LED_CARD_2_SINGLE_FLASH		= 0x06,					//������˸
	LED_CARD_2_ENGLISH_DATE		= 0x07,					//Ӣ������
	LED_CARD_2_ENGLISH_TIME		= 0x08,					//Ӣ��ʱ��
	LED_CARD_2_CHINESE_DATE		= 0x09,					//��������
	LED_CARD_2_CHINESE_TIME		= 0x0A,					//����ʱ��
	LED_CARD_2_CONTROL_MODE		= 0x0B,					//����
	LED_CARD_2_LOOP_MODE		= 0x0C,					//ѭ��
	LED_CARD_2_TMPREATURE_MODE  = 0x0D,					//�¶�
	LED_CARD_2_MAX_STOP_DISPLAY_MODE
	
}led_card_2_stop_display_mode;

//led���ƿ���Э��2 �˳�ģʽ
typedef enum {
	LED_CARD_2_EXIT_INSTANT_DISAPPEAR			= 0x00,		//�����˳�
	LED_CARD_2_EXIT_RIGHT_TO_LEFT				= 0x01,		//����������
	LED_CARD_2_EXIT_LEFT_TO_RIGHT				= 0x02,		//����������
	LED_CARD_2_EXIT_DOWN_TO_UP					= 0x03,		//����������
	LED_CARD_2_EXIT_UP_TO_DOWN					= 0x04,		//����������
	LED_CARD_2_EXIT_PULL_CURTAIN_TO_DOWN		= 0x05,		//��������ʽ
	LED_CARD_2_EXIT_PULL_CURTAIN_TO_UP			= 0x06,		//��������ʽ
	LED_CARD_2_EXIT_PULL_CURTAIN_TO_LEFT		= 0x07,		//��������ʽ
	LED_CARD_2_EXIT_PULL_CURTAIN_TO_RIGHT		= 0x08,		//��������ʽ
	LED_CARD_2_EXIT_BACK_LIGHT					= 0x09,		//����
	LED_CARD_2_EXIT_SPACE_OPERATION				= 0x0A,		//�޲���
	LED_CARD_2_EXIT_MEDIUM_SPEED_LEFT			= 0x0B,		//��������
	LED_CARD_2_EXIT_MEDIUM_SPEED_RIGHT			= 0x0C,		//��������
	LED_CARD_2_EXIT_VERBATIM_DISAPPEAR			= 0x0D,		//������ʧ
	LED_CARD_2_EXIT_OPEN_GATE_LEFT				= 0x0E,		//����դ
	LED_CARD_2_EXIT_OPEN_GATE_RIGHT				= 0x0F,		//���ҿ�դ
	LED_CARD_2_EXIT_SNOWFLAKE_DISAPPEAR			= 0x10,		//ѩ����ʧ
	LED_CARD_2_EXIT_ROW_DISAPPEAR				= 0x11,		//������ʧ
	LED_CARD_2_EXIT_COL_DISAPPEAR				= 0x12,		//������ʧ
	LED_CARD_2_EXIT_SLOW_SPEED_LEFT				= 0x13,		//��������
	LED_CARD_2_EXIT_SLOW_SPEED_RIGHT			= 0x14,		//��������
	LED_CARD_2_EXIT_SERIES_DISAPPEAR			= 0x15,		//�����ƶ�
	LED_CARD_2_EXIT_NONE_OPERATION				= 0x16,		//�޲���
	LED_CARD_2_EXIT_SLOW_SPEED_SERIES_DISAPPEAR = 0x17,		//���������ƶ�
	LED_CARD_2_EXIT_MAX_LED_BS_DISPLAY
}led_card_2_exit_mode;

//��ȡ����汾
typedef struct
{
	char szAppVersion[128];   //���app�汾
	char szAlgoVersion[256];  //����㷨�汾
	int szIsEnc;              //����Ƿ����
	char szAppTime[16];       //�汾ʱ��
	char szReserved[1024];    //Ԥ��
} ICE_CameraInfo;

//��־����
typedef struct{
	ICE_U8 u8AppLog;		  //�Ƿ����app��־
	ICE_U8 u8AlgoLog;		  //�Ƿ����㷨��־	
	ICE_U8 u8AlgoTimeLog;	  //�Ƿ�����ʱͳ����־
	ICE_U8 u8DebugLog;		  //�ͻ��˿�����Ҫ��־, debug ����
	ICE_U8 u8NomalLog;		  //�ͻ��˿�����ͨ��־, info notice warning ����
	ICE_U8 u8NetRealTimeLog;  //�Ƿ�������ʵʱ��־
	ICE_U8 u8SaveLogToSD;	  //�Ƿ����־���浽SD��
	ICE_U8 u8NetLogAddr[16];  //����ʵʱ��־��IP��ַ
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

//��ȡ���ư汾
typedef struct 
{
	ICE_U8 u8device_model[16];
	ICE_U8 reserved[48];
}ICE_DEVICE_INFO;

/**********************************�ѻ��Ʒ��鲥����************************************************/
/* �鲥����*/
typedef struct
{
	ICE_U8	ucEnabled;      /* �鲥ʹ��*/
	ICE_U16	usOfflinePort;  /* �鲥�˿�*/
	ICE_U32	uiIP;			/* �鲥��ַ*/
	ICE_U8	aucReserved[10];
}ICE_OFFLINE_MULTICAST_CONFIG;
/******************************�ѻ��Ʒ��鲥����*************************************************/


/******************************�ѻ��Ʒ�LED������*************************************************/
//�ѻ��Ʒ���ؽṹ��
#define MAX_LED_CONTENT   64     //һ������ַ�
#define MAX_LED_COUNT     4      //�����Ļ


typedef enum
{
	LED_SCREEN_1 = 0,    //����Э��1
	LED_SCREEN_2,        //͸������
	LED_SCREEN_3,        //LED����
	LED_SCREEN_4,        //���ģʽ
	LED_SCREEN_5,        //����Э��2
	LED_SCREEN_6,        //����Э��3 
	LED_SCREEN_7,        //����Э��4 
	LED_SCREEN_8,        //rs232 wifi̽��Э��
	LED_SCREEN_9,        //����Э��5
	LED_SCREEN_10,       //����Э��6
	LED_SCREEN_11,
	LED_SCREEN_12,
	LED_SCREEN_13,
	LED_SCREEN_14,
	LED_SCREEN_15,
	LED_SCREEN_16,
	LED_SCREEN_17, 
	/***************��Э��֧���ѻ��Ʒ�***************************/
	LED_SCREEN_18,    //����Э��7
	LED_SCREEN_19, 
	LED_SCREEN_20, 
	LED_SCREEN_21, 
	LED_SCREEN_22, 
	LED_SCREEN_23,
	LED_SCREEN_MAX
}E_LedScreenType;

typedef enum
{
	COLOR_TYPE_RED =0,  //��
	COLOR_TYPE_GREEN,   //��
	COLOR_TYPE_YELLO,   //��
	COLOR_TYPE_BLUE ,   //��
	COLOR_TYPE_WHITE,   //��
	COLOR_TYPE_BLACK,   //��
	COLOR_TYPE_OTHER,   //����
	COLOR_TYPE_YELLOW_GREEN, //����
	COLOR_TYPE_ALL,      //ȫ��
}E_ColorType;//��ɫ����

typedef enum
{
	LED_SUB_MOD_VEH_PLATE=0,/*������ʾ*/
	LED_SUB_MOD_VEH_WELCOME,/*��ӭ����ʾ*/
	LED_SUB_MOD_VEH_PAY,  /*ͣ��������ʾ*/
	LED_SUB_MOD_VEH_TIME, /*ͣ��ʱ����ʾ*/
	LED_SUB_MOD_VEH_PERIOD, /*������Ч����ʾ*/
	LED_SUB_MOD_TIME,/*ʱ����ʾ����ʽ:XXXX��XX��XXʱXX��*/
	LED_SUB_MOD_VEH_LEFT,/*ʣ��ͣ��λ��ʾ*/
	LED_SUB_MOD_CUSTOM,  /*�Զ���������ʾ*/
	LED_SUB_MOD_MAX,
}E_SubLedMode;

typedef struct
{
	ICE_U8   ucContentEnable;               //�Ƿ�ʱ��  0��֧���Զ��� 1֧��
	ICE_U8   ucTimeEnable;                  //�Ƿ��Զ���  0����ʾʱ��   1֧��
	ICE_U8   ucInterval;					//ʱ����  s��
	ICE_U8   aucContent[MAX_LED_CONTENT];   //�Զ����ַ�   GB2312���Զ���ģʽ��Ч
	ICE_U8   ucColor;                //��ɫ
	ICE_U8   ucLeftVehEnable;               //�Ƿ���λ 0��֧���Զ��� 1֧��
	ICE_U8   aucReserved[9];               //����
}T_SubLedSetup;   //��ʱ��ʾ

typedef struct
{
	ICE_U8   ucContentEnable;               //�Ƿ��Զ���		  0��֧���Զ��� 1֧��
	ICE_U8   ucVehTypeEnable;               //�Ƿ������������    0��֧�� 1֧��
	ICE_U8   ucPlateEnable;                 //�Ƿ���ʾ����        0����ʾ 1��ʾ
	ICE_U8   ucLeftDaysEnable;              //�Ƿ���ʾʣ������    0����ʾ 1��ʾ
	ICE_U8   ucParkPay;                     //�Ƿ�ͣ���Ʒ�        0����ʾ 1��ʾ  
	ICE_U8   ucParkLastTime;                //�Ƿ�ͣ��ʱ��        0����ʾ 1��ʾ   
	ICE_U8   ucTmpCardColor;                //��ʱ����ɫ
	ICE_U8   ucMonthCardColor;              //�¿�����ɫ
	ICE_U8   aucContent[MAX_LED_CONTENT];   //�Զ����ַ�   GB2312���Զ���ģʽ��Ч
	ICE_U8   aucReserved[10];               //����
}T_M_SubLedSetup;  //æʱ��ʾ

typedef struct
{
	ICE_U8   ucContentEnable;               //�Ƿ��Զ���		  0��֧���Զ��� 1֧��
	ICE_U8   ucVehTypeEnable;               //�Ƿ������������    0��֧�� 1֧��
	ICE_U8   ucPlateEnable;                 //�Ƿ���ʾ����        0����ʾ 1��ʾ
	ICE_U8   ucLeftDaysEnable;              //�Ƿ���ʾʣ������    0����ʾ 1��ʾ
	ICE_U8   ucParkPay;                     //�Ƿ������Ʒ�        0����ʾ 1��ʾ  
	ICE_U8   ucParkLastTime;                //�Ƿ�����ʱ��        0����ʾ 1��ʾ   
	ICE_U8   ucWelorByeEnable;              //�Ƿ񲥱���ӭ\������ 0������ 1����
	ICE_U8   aucWelorByeContent[MAX_LED_CONTENT];   //������   GB2312��
	ICE_U8   aucSelfContent[MAX_LED_CONTENT];   //�Զ����ַ�   GB2312���Զ���ģʽ��Ч
	ICE_U8   aucReserved[10];               //����
}T_M_AudioLedSetup;  //æʱ��������

typedef struct   //�ѻ��Ʒ�LED
{
	E_LedScreenType    sreenType;                    //����Э������
	ICE_U32            screenMode;                   //����ģʽ 0�ѻ�ʹ�� 1ǿ��ʹ�� 2��ʹ��
	ICE_U32            cameraType;                   //�������    1 ���  2����
	ICE_U8             ucAudioEnable;                //�Ƿ���������

	ICE_U8             ucReserved[3];
	T_SubLedSetup      atSubLedInIdle[MAX_LED_COUNT];//��ڿ���
	T_M_SubLedSetup   atSubLedInBusy[MAX_LED_COUNT];//���æ
	T_M_AudioLedSetup atSubLedInBusyAudio;          //���æ������������
	T_SubLedSetup      atSubLedOutIdle[MAX_LED_COUNT];//���ڿ���
	T_M_SubLedSetup   atSubLedOutBusy[MAX_LED_COUNT];//����æ
	T_M_AudioLedSetup atSubLedOutBusyAudio;         //����æ������������
	ICE_U32            uc485ctrlEnable;              //485�����Ƿ���   1     0������
	ICE_U32            ucLeftVehPlace;               //��λʣ����

	ICE_U16			   FK_password;      //���ؼ�������
	ICE_U8             ucFKEncipherment; //����Э���Ƿ����
	ICE_U8             aucReserved[89];  //����
}ICE_OFFLINE_LED_CONFIG;
/******************************************LED������******************************************************/



/********************************�ѻ��Ʒѹ���********************************************************/
#define MAX_PAY_ITEM           2      //��󸶷Ѳ�������
#define MAX_TIMESECTION_NUM    3      //��������
#define MAX_PARTTIME_SET_NUM   40     //���ʱ��������

typedef enum
{
	PAY_MODE_UNKNOW = 0,
	PAY_MODE_ONTIME,       /*��ʱ�Ʒ� */
	PAY_MODE_TIMES,        /*���μƷ� */
	PAY_MODE_TIME_SECTION,/*�ֶμƷ� */
	PAY_MODE_PARTTIME,/*���Ʒ� */    //��ʱ�Ʒ�
	PAY_MODE_MAX
}E_PayMode;   /*�Ʒ�ģʽ*/

typedef enum
{
	STRATEGY_TYPE_UNKNOW = 0,
	STRATEGY_TYPE_NOPAY, //���շ�
	STRATEGY_TYPE_CYCLE,//��һ�������շ�
	STRATEGY_TYPE_BYTIME,//����ʱ���շ�
	STRATEGY_TYPE_MAX
}E_StrategyType;  /*����һ�����ڵļƷѲ���*/

typedef struct
{
	ICE_U8	ucEnable;
	ICE_U16	usCyclePay;/* �����շѽ��*/
	ICE_U16	usStartPay;/* �𲽽��*/
	ICE_U16	usFreeTime;/* ���ʱ��*/
	ICE_U16	usCycleTime;/* �Ʒ�����*/
	ICE_U16	usStartTime;/* ��ʱ��*/
	ICE_U16	usTotalPreDay;/* �ⶥ���*/
	ICE_U8	aucReserved[10]; //����
}T_OnTimePay;  /*��ʱ�շ�*/

typedef struct
{
	ICE_U8	ucEnable;
	ICE_U8	ucMaxTime;/*�ⶥ����*/
	ICE_U16	usPayOne;/*һ���շѽ��*/
	ICE_U16	usFreeTime;/*���ʱ��*/
	ICE_U16	usFreeStartTime;  /*��ѿ�ʼʱ�䣬�Է���Ϊ��λ*/
	ICE_U16	usFreeEndTime; /*��ѽ���ʱ�䣬�Է���Ϊ��λ*/
	ICE_U8	aucReserved[10]; //����
}T_TimesPay; /*�����շ�*/

typedef struct
{
	ICE_U8	ucEnable;
	ICE_U16	usCyclePay;/* �����շѽ��*/
	ICE_U16	usStartPay;/* �𲽽��*/
	ICE_U16	usFreeTime;/* ���ʱ��*/
	ICE_U16	usCycleTime;/* �Ʒ�����*/
	ICE_U16	usStartTime;/* ��ʱ��*/
	ICE_U16	usTotalPreDay;/* ʱ�ηⶥ���*/
	ICE_U16	usSectionStartTime;  /*ʱ�ο�ʼʱ�䣬�Է���Ϊ��λ*/
	ICE_U16	usSectionEndTime;/*ʱ�ν���ʱ�䣬�Է���Ϊ��λ*/
	ICE_U8	aucReserved[10];  //����
}T_TimeSectionPay;	/*��ʱ���շ�*/

typedef struct  
{
   ICE_U16  parkTime;  /*ͣ��ʱ��*/
   ICE_U16  usPay;     /*���*/
}SetionSet;

typedef struct 
{
	ICE_U16		usCyclePayMax;  /* ��������շѽ��*/
	ICE_U16		usFreeTime;		/* ���ʱ��*/
	SetionSet   usPartTime[MAX_PARTTIME_SET_NUM]; /*ʱ������*/ 
	ICE_U8		aucReserved[10];  //����
}T_PartTimesPay;


typedef struct   //�ѻ��Ʒѹ���
{
	ICE_U32           offEnable;		//�ѻ�ʹ�� 0�ѻ�ʹ�� 1ǿ��ʹ�� 2��ʹ��
	ICE_U32		      ExtranceRule;     //��բ���� �����ʱ��            0������ 1����  
	ICE_U32			  ExitRule;		    //��բ���� ������ʱ���Ʒ�0����   0������ 1���� 

	E_PayMode		  ucRuleMode; 		//�Ʒ�ģʽ
	E_StrategyType	  ucStrategyType;	//�ƷѲ���
	ICE_U16			  usTimeLength;		//���ڲ���Ʒ�ʱ��

	T_OnTimePay       atOnTimePay[MAX_PAY_ITEM]; //��ʱ�Ʒ�  С��atOnTimePay[0]  ��atOnTimePay[1] 
	T_TimesPay		  atTimesPay[MAX_PAY_ITEM];  //���μƷ�  С��atTimesPay[0]   ��atTimesPay[1] 
	T_TimeSectionPay  atTimeSectionPay[MAX_PAY_ITEM*MAX_TIMESECTION_NUM];  //��ʱ�μƷ� 0,1,2С�� 3,4,5��
    T_PartTimesPay    atPartTimePay;             //��ʱ�Ʒ�

	ICE_U8			  aucReserved[30];
}ICE_OFFLINE_CHARGE_RULE;
/********************************�ѻ��Ʒѹ���********************************************************/


/*********************************�ѻ��Ʒ������ϱ�**********************************************************/
typedef struct    //�Ʒ������ϱ�
{
	E_PayMode		  ucRuleMode; 		//�Ʒ�ģʽ
	ICE_U8			  vehicleType;      //��������
	ICE_U32			  usTotalMoney;		//���ѽ��
	ICE_U32           usParkingTime;    //ͣ��ʱ��
	ICE_U32           usRecordID;       //��¼id
	ICE_U8            usVehiclePlate[16];//���ƺ�
	ICE_U8            reserved[20];     //����
}ICE_VEHPAY_RSP;


typedef enum  
{
	ICE_CAMERA_OFFLINE_PAY_HEARTBEAT		= 0x4001,		//!< �ѻ��Ʒ������ϱ�������
	ICE_CAMERA_OFFLINE_PAY_HEARTBEAT_RSP	= 0x4002,		//!< �ѻ��Ʒ������ϱ�������Ӧ��

	ICE_CAMERA_OFFLINE_PAY_VEHICLE_INFO		= 0x4003,		//!< �ѻ��Ʒ��ϱ���Ϣ
	ICE_CAMERA_OFFLINE_PAY_VEHICLE_INFO_RSP	= 0x4004,		//!< �ѻ��Ʒ��ϱ���ϢӦ��

}ICE_PAYRULE_TYPE_E;
/****************************************************************************************************/

typedef struct
{
	unsigned char ucType;  /*������Ϣ���ݣ�0Ϊ�����ڳ���Ϣ��*/
	char aucLplPath[256];
}T_GetPrensentVehInfo;


/**************************************����ģʽ�ṹ��****************************************/
typedef struct __MAIN_SUB_MODE
{
	ICE_U32 enable;  // 0 ��ʹ�ܣ� 1 ʹ��
	ICE_U32 status;// 1 ����ͬʱ�ϴ��� 2 �Ƚ����Ŷ��ϴ�.
	ICE_U32 msec;   //��������ȴ�ץ�Ľ��ʱ��(ms)  Ĭ��Ϊ500.
	ICE_U8  ip_addr[16]; // �����ip��ַ�� enable Ϊ1ʱ��Ч��
	ICE_U8  reserved[32];// ����
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

/** @brief ���������� */
typedef enum tagE_DevAlarmInMode
{
	AlarmInMode_Default,	   //Ĭ�Ϲ��ܲ��账�� IO������ƶԽ�Ҳ��������[IO״̬�仯 �ϴ���ƽ̨��ƽ̨�·��Խ�������жԽ�]
	AlarmInMode_Hdtrigger,     //��Ϊ��Ȧ�������� ���������Ȧ�ͻ�ϴ������ж��ο�բ
	AlarmInMode_SecondGate,    //��Ϊ���ο�բ���� ֻ�����Ƶģʽ
	AlarmInMode_IoRelateGate,  //IO���������բ
	AlarmInMode_Count
}E_DevAlarmInMode;

typedef struct tagT_DevAlarmIn
{
	ICE_S32 Io_num;
	ICE_S32 Type; //��������ı������� 0 ���� 1���ա�
	E_DevAlarmInMode 	  Io_mode;
}T_DevAlarmIn;

typedef enum tagE_DevAlarmOutMode
{
	AlarmOutMode_None = 0,
	AlarmOutMode_StrobeLight,	//������
	AlarmOutMode_OpenGate, 		//��բ
	AlarmOutMode_SwitchLight, 	//�ⲿ�����
	AlarmOutMode_Intercom		//�Խ� 
}E_DevAlarmOutMode;
//��io���
typedef struct tagT_DevAlarmOutCfg
{
	ICE_S32 Io_num;
	E_DevAlarmOutMode 	  Io_mode;
}T_DevAlarmOutBindCfg;

typedef struct tagT_UartOperPro
{
	ICE_S8 szProtocolName[32];	//Э������
	ICE_S32 len;				//
	ICE_S8 res[128];
} T_UartOperPro;

typedef struct tagT_UartBindPro
{
	ICE_S32 ProId;				//����ID [0-1]
	ICE_S8 szProtocolName[32];	//Э������
} T_UartBindPro;

/** @brief Э��������󳤶�*/
#define MaxProtocolNameLen    31
/** @brief Э��������� */
#define MaxProtocolNum    256
/** @brief �������� */
typedef enum tagE_PeripheralType
{
	Dpt_Uart,   /**< ���� */
	Dpt_Rs232,  /**< RS232 */
	Dpt_Rs485,  /**< RS485 */
	Dpt_Eth,    /**< ���� */
	Dpt_USB,    /**< usb */
	Dpt_Sd,     /**< sd */
	Dpt_Key,   /**< ���� */
	Dpt_PluckSwitch,    /**< ���뿪�� */
	Dpt_IO,     /**< IO */
	Dpt_All,  /**< ȫ�� */
} E_PeripheralType;
/**< �п�Э������ */
typedef struct tagT_ProtocolInfo
{
	E_PeripheralType ePerType;                 /**< �������� */
	ICE_S8 szProtocol[MaxProtocolNameLen + 1];  /**< Э������ */
} T_ProtocolInfo;
/**< �п�Э���б� */
typedef struct tagT_ProtocolList
{
	ICE_S32 uiNum;
	T_ProtocolInfo atList[MaxProtocolNum];   /**< Э���б� */
} T_ProtocolList;

typedef struct
{
	int alarm_in_type_sec; //��������2 �ı������� 0 ����1����
	int which_for_hardtriger; //�ظ��ź�ѡ�Ǹ���������0 ��ѡ��һ�飬1ѡ�ڶ���
	int alarm_in_type_third; //��������3 �ı������� 0 ����1����
	int alarm_in_type_fourth; //��������4 �ı������� 0 ����1����
	int related_talkbacks;  //�Ƿ���������Խ�ʹ����Ĺ�ϵ���жϹ����Ŀǰֻ֧��IO2 IO3 IO4
	int u32Researve[17];
}ALARM_IN_EXT;

#define NETADDR_LEN (64)
typedef struct 
{
	ICE_S8 talk_status;  //0;�Խ����ӳɹ�������ip��  -1���Ѿ��ڶԽ��У����ضԽ�ip
	ICE_U8 link_netaddr[NETADDR_LEN];
	ICE_U8 reserved[48];
}ICE_TALK_INFO;

typedef struct
{
	int key_value; //��������ֵ
	int talk_state;  //�Խ�״̬ 0 ��ͨ�ǶԽ�״̬�� 1�� �����Խ�  2�����ڶԽ� 3,�ܾ��Խ���talk_ip_addrΪ�ܾ��Խ�ip
	char talk_ip_addr[NETADDR_LEN];//���ӹ����ն�ip
	char reserevd[20];
}TalkState;

typedef struct
{
	unsigned char ucUID[32];
	unsigned char ucReserved[32];
}UID_PARAM;

typedef struct
{
	ICE_U8 u8UserModel[64];  //�û��ͺ�
	ICE_U8 u8Reserved[32]; 
} UserModelParam;

typedef struct T_OsdInfoCfg{
	ICE_S32	iEnable;	//�Ƿ�ʹ��,0��ʹ�ܣ�1ʹ��
	ICE_S32 iLocation;	//0����,1���ϣ�2����,3����,4����,5���£�ע��������ʾʱ��λ��ֻ�������ϻ������£�����һ�£�
	ICE_S32 iType;		//0����,1ʱ��,2����+ʱ��,3ʶ����,4�豸����,5���������,6�Զ�������
	char acCustomInfo[MAX_OSD_TEXT];//�Զ�����Ϣ��UTF8���룬�60byte
	char acResrv[64];//Ԥ��
}T_OsdInfoCfg;

typedef struct T_SnapOsdCfg{
	ICE_S32 ibgColorMode;	//0 ����͸����1 ������ɫ
	ICE_S32 iDateMode;		//0 yyyy/mm/dd ,  1 yyyy��mm��dd��
	ICE_S32 iFontSize;		//0 С��1 ��, 2 ��,Ĭ��Ϊ�У���540P ���£��л�ת��ΪС
	ICE_S32 iLineMode;		//0������ʾ��1������ʾ
	T_OsdInfoCfg tOsdInfoCfg[MAX_CUSTOM_OSD_LINE_NUM];//osd���ݣ����֧��6��
	char acResrv[128];//Ԥ��
}T_SnapOsdCfg;

typedef struct T_CamInfo{
	ICE_U32 uiCamType;//������� 0��� 1����
	ICE_U8 aucCamName[64];//�������
	ICE_U8 aucResrv[256];
}T_CamInfo;


typedef struct T_User{
	ICE_U8 aucUseName[64];//�û���
	ICE_U8 aucPasswd[64];//����
	ICE_U8 aucUserId[32];//�û�ID
	ICE_U32 uiPrivilege;//Ȩ�� 0:����Ա 1:����Ա 2:�۲�Ա
	ICE_U8 aucResrv[32];
}T_User;

typedef struct T_UserList{
	T_User atUser[16];
	ICE_U32 uiUserCnt;//�û�����
	ICE_U8 aucResrv[256];
}T_UserList;

#define MAX_ENCODER_NUM 4
typedef struct T_SingleEncoderParam{
	ICE_U32 uiChannel;//�������� 0:������ 1:������
	ICE_U32 uiWidth;//��
	ICE_U32 uiHeight;//��
	ICE_U32 uiEncMode;//���뷽ʽ 0:h264 1:mjpeg
	ICE_U32 uiFps;//֡��5,8,12,25,30
	ICE_U32 uiRateCtrl;//0������ 1������
	ICE_U32 uiVideoQuality;//��Ƶ���� 0������ 1������ 2���� 3�е� 3���� 4������ 5������
	ICE_U32 uiMaxBitRate;//�������� 512,1024,2048,4096
	ICE_U8 aucResrv[64];
}T_SingleEncoderParam;

typedef struct T_EncoderParam
{
	ICE_U32 uiEncoderCnt;//��������������
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
	ICE_U32 uiAdDisplayTime;//���Ҳûͣ��ʱ�� 1-300s
	ICE_U32 uiPlateDisplayTime;//������Ϣ��ʾʱ�� 1-100s
	ICE_U32 uiAdSwitchMode;//����л�Ч�� 0:������ 1:���ҵ���
	ICE_U8 aucResrv[256];
}T_DisplayCfg;

typedef struct T_ClearAdPic{
	ICE_U32 uiPicType;//���ͼƬ��� 0:ȫ�����ͼƬ��� 1:�������ͼƬ���
	ICE_U8 aucResrv[256];
}T_ClearAdPic;

#define MAX_KEY_NUM 8
typedef struct T_SingleKeyParam
{
	ICE_U32 uiRealValue;//ʵ�ʼ�ֵ
	ICE_U32 uiFixValue;//У����ֵ
	ICE_U8 aucResrv[64];
}T_SingleKeyParam;

typedef struct T_KeyParam
{
	ICE_U8 aucCtrlId[64];//ң����ID 
	T_SingleKeyParam tSKeyParam[MAX_KEY_NUM];//Ŀǰ֧���ĸ�
	ICE_U8 aucResrv[256];
}T_KeyParam;

typedef struct T_RemoteDebug
{	
	ICE_U32 uiDebug;//0������ 1����
	ICE_U8 aucResrv[128];
}T_RemoteDebug;

typedef struct T_RemoteCtrl
{
	ICE_U8 aucCtrlId[64];//ң����ID
	ICE_U32 uiKeyRealValue;//ʵ�ʼ�ֵ
	ICE_U8 aucResrv[128];
}T_RemoteCtrl;

typedef struct
{
	ICE_U16 u16Identify;    //4G���ð汾��0x5601 ��ǰ���ð汾V1
	ICE_U8 u8NetPriorType;  //0��ʾ������������ 1��ʾ����4G (��ǰԤ��)
	ICE_U8 u8DialingMode;   //���ŷ�ʽ    0��ʾ�Զ����� 1��ʾ�ֶ� (��ǰԤ��)

	ICE_U8 u8SignalValue;   //�ź�ǿ�� 0 ����   1 ��  2 �� 3  ǿ
	ICE_U8 u8NetworkState;  //������ǩ   ��������״̬��0:�������� 1����������.
	ICE_U8 u8Operators;     //��Ӫ�� 0��ʾδ֪ 1��ʾ�й��ƶ� 2��ʾ�й����� 3��ʾ�й���ͨ
	ICE_U8 u8ModuleState;      //4G ģ������״̬ 0:4Gģ��δʶ��1��4Gģ��ʶ������

	ICE_U8 u8NetType;          //�������� 1:4G, 2:3G,3:2G ,4:����  (��ǰԤ��)
	ICE_U8 u8Reserve; 
	ICE_U16 u16ExtParamSize;   //��չ������С

	//ICE_U8 u8ServerIPAddr[64]; //�ƶ˷�������ַ���û�������IP������
	ICE_U8 u8ICCIDBuf[24];     //iccid buf  (��ǰԤ��)

}ICE_4G_MODULE_PARAM;

typedef struct{
	ICE_U32 u32Result;           //ping �������صĽ��������˴����ͻ���
	ICE_U8 u8ServerIPAddr[64]; //�ƶ˷�������ַ���û�������IP������
	ICE_U8 aucResrv[128];
}ICE_4G_MODULE_SERVER_ADDR;

typedef struct T_LockParam
{
	ICE_U32 uiEnable;//�Ƿ�ʹ��
	ICE_U32 uiModel;//�����ͺ� 0:DDTC_DS 1:DDTC_PT 2:DDTC_BD
	ICE_U8 aucId[32];//����ID
	ICE_U32 uiSocWarnValue;//��������Ԥ��ֵ0-100
	ICE_U32 uiSocFaultValue;//������������ֵ0-100
	ICE_U32 uiDelay;//�������������ʱ0-60��
	ICE_U32 uiMode;//ģʽ 0��ͨģʽ 1����ģʽ
	ICE_U8 aucResrv[128];
}T_LockParam;

#define KEY_LEN 64
#define NET_LEN 128
#define ROUTEURLLEN 256

#define MAX_ROUTESERVER_NUM 8

typedef struct T_TldCfg
{
	ICE_S32 iEn;                     //�Ƿ�ʹ��������Э��.[0,1] 0:��ʹ�� 1:ʹ��	
	ICE_S32 iInterval;               //��������,��λ:�� ��Ĭ��10s
	ICE_U8 aucDeviceKey[KEY_LEN];        //�豸key
	ICE_U8 aucDeviceSecret[KEY_LEN];     //�豸��Կ
	ICE_U8 aucProductKey[KEY_LEN];       //��Ʒkey
	ICE_U8 aucProductSecret[KEY_LEN];    //��Ʒ��Կ
	ICE_U8 aucRouteUrl[MAX_ROUTESERVER_NUM][ROUTEURLLEN];  // ·�ɷ�������ַ ֧�ֶ��·�ɵ�ַ����|��ʽ�ָ�
	ICE_U8 aucReserved[256];             // Ԥ������
}T_TldCfg;

// ETC �۷���������
typedef struct T_EtcCharge
{
	ICE_S8 acLaneId[32]; // �������
	ICE_S8 acPaySerialNo[36]; // ֧����ˮ��
	ICE_S8 acObuId[32]; // Obu��ʶ
	ICE_S8 acPlate[48]; // ���ƺ�
	ICE_S8 acVer[16];//�汾��
	ICE_S32 iPlateColor; // ������ɫ��0:��ɫ��1:��ɫ��2:��ɫ��3:��ɫ��4���̰�5���̻ƣ�6����
	ICE_S32 iTransAmount; // �۷ѽ���λ����
	ICE_S32 iParkTime; //ͣ��ʱ������λ����
	ICE_S32 iInTs; // �볡ʱ�䣬UTCʱ���
	ICE_U8 aucReserved[256]; // Ԥ������
} T_EtcCharge;

//ETC�۷�����Ӧ��
typedef struct T_EtcChargeRsp
{
	ICE_S8 acMsg[64]; // ��ʾ��Ϣ
	ICE_S8 acTac[32]; // TAC��
	ICE_S8 acTerminalId[32]; // �ն˱��
	ICE_S32 iCode; // ������
	ICE_S32 iChargeType; // �۷ѷ�ʽ(0��RSU  1��ˢ���� 2:�����ն�)
	ICE_U8 aucReserved[128];// Ԥ������
} T_EtcChargeRsp;

typedef struct T_CloudCfgParamExt
{
	ICE_S32 cloudEn;			//�Ƿ��cloud ���ܣ�Ĭ�Ϲر�.[0,1] 0:�ر� 1:����
	ICE_S32 mode;				//����ģʽ.1:ģʽ1,2:ģʽ2,3:ģʽ3,4:ģʽ4
	ICE_U8 reserved1[8];		//Ԥ������
	ICE_S32 camIdType;			//camId����.[0,1] 0:ʹ�����MAC��ַ 1:ʹ�����UUID
	ICE_S32 interval;			//��������,��λ:��.[0,300]��0=������
	ICE_S32 maxSendCnt;			//����������, 1-3��Ĭ��Ϊ:2
	ICE_S32 fullImgEn;			//�Ƿ���ȫ��ͼ��0:�����ͣ�1:����
	ICE_S32 miniImgEn;			//�Ƿ��ͳ�����дͼ��
	ICE_S32 ioInEn;				//����IO״̬�ϱ�ʹ��
	ICE_U8 ioInNum[8];			//ָ���ϱ�����IO������Ч��ioInNum[0]��Ӧ����IO1��ioInNum[1]=IO2,ioInNum[2]=IO3,ioInNum[3]=IO4��4-7Ԥ����
	ICE_U8 parkId[CLOUD_ID_LEN];	//ͣ����id,ֻ֧��Ӣ�ġ����֡�'-',like:GD-SZ-A000001

	ICE_U8 cloudDomain[CLOUD_NET_LEN];	// ��ƽ̨��������like:www.baidu.com
	ICE_U8 path[CLOUD_NET_LEN];		// ��ƽ̨�����·��
	ICE_S32 port;				// ��ƽ̨���ʶ˿ڣ�Ĭ��Ϊ��80
	ICE_U8 reserved2[12];		//Ԥ������
	ICE_S32 osType;			// ����Э�����ͣ�0=aliyun,1=tencentyun,2=baiduyun
	ICE_U8 osDomain[CLOUD_NET_LEN];	// ����洢��������like:bucket.endpoint
	ICE_S32 iPicUploadType;         // ͼƬ�ϴ���ʽ 0:�ֿ��ϴ�  1:һ���ϴ�

	ICE_U8 reserved[256];	// Ԥ������
	ICE_S8 accessKey[CLOUD_ID_LEN]; // ģʽ4ʱ��OSS_ACCESS_KEY
	ICE_S8 accessSecret[CLOUD_ID_LEN];// ģʽ4ʱ��OSS_ACCESS_KEY_SECRET
	ICE_U8 reserved3[384]; // Ԥ������
} T_CloudCfgParamExt;

typedef struct T_SyncTimeParam
{
	ICE_S32 iSdkEn;//�Ƿ������SDK��Уʱ����,1���� 0�ر�
	ICE_U8 reserved[64];
}T_SyncTimeParam;

typedef struct tagT_MqttType3Param
{
	ICE_S32 iHttpUploadEn;//�����ϴ�ͼƬ�����Э��3��Ч
	ICE_S32 iHttpUploadPort;//�����ϴ�ͼƬ�������˿ںţ����Э��3��Ч
	ICE_S8 acProductKey3[64]; //��Ʒ���ƣ����Э��3��Ч
	ICE_S8 acProductSecret3[64];//��Ʒ��Կ�����Э��3��Ч
	ICE_S8 acDevName3[64];  //�豸���ƣ����Э��3��Ч
	ICE_S8 acDevSecret3[64]; //�豸��Կ  //�������ģ����Э��3��Ч        
	ICE_S8 acClientId[64];//�ͻ���ID�����Э��3��Ч
	ICE_S8 acHttpUploadSrv[128];//�����ϴ�ͼƬ��������ַ�����Э��3��Ч
	ICE_S8 acHttpUploadPath[128];//�����ϴ�ͼƬ������·�������Э��3��Ч
}T_MqttType3Param;

//�ṹ�嶨��
typedef struct tagT_MqttCfgParam
{
	ICE_S32 iMqttEn;		//�Ƿ�ʹ��mqttЭ�飬 0 �رգ� 1����
	ICE_S32 iProtoType;	//Э�����ͣ� 1 �������������� 2�����Դ��������� 
	ICE_S32 iCamIdType;	//camId����.[0,1] 0:ʹ�����MAC��ַ 1:ʹ�����UID
	ICE_S32 iHeartEnable;	//����ʹ�ܣ�Ԥ����
	ICE_S32 interval;		//��������,��λ:��.��Χ��[1,300]
	ICE_S32 iMaxSendCnt;	//����ʹ�������Χ��1-3
	ICE_S32 iPostIoInStatEn;//�Ƿ��ϱ�IO���ݣ� 0 �� 1��
	ICE_U8 ioInNum[8];		//ָ���ϱ�����IO������Ч��ioInNum[0]��Ӧ����IO1��ioInNum[1]=IO2,ioInNum[2]=IO3,ioInNum[3]=IO4��4-7Ԥ����
	ICE_S32 iPostFullEn;	//�Ƿ�����ȫ��ͼ��0 �� 1��
	ICE_S32 iPostCloseupEn;	//�Ƿ����ͳ�����дͼ��0 �� 1��
	ICE_S32 iPostUart1DataEn;//�Ƿ����ʹ���1���ݣ�0 �� 1��
	ICE_S32 iPostUart2DataEn;//�Ƿ����ʹ���2���ݣ�0 �� 1��
	ICE_U8 aucParkId[64];	//ͣ����id,ֻ֧��Ӣ�ġ����֡�'-',like:GD-SZ-A000001�����֧������60�ֽ�

	ICE_S8 acDomain[128];//������������������֧������124�ֽ�
	ICE_S32 iPort;		//����������˿�
	ICE_S32 iTimeOut;	//��ʱʱ������ʱ���ٲ��账��������нӿڣ���Χ��1-6s

	//oss����
	ICE_S32 iOssEn;		// �Ƿ�򿪶���洢���ܡ���Χ��[0,1] 0:�رգ� 1:����
	ICE_U8 aucOssDomain[128]; //����洢��������like:bucket.endpoint�����֧������124�ֽ�
	ICE_S8 acAccessKey[64];	//�������ģ����֧������60�ֽ�
	ICE_S8 acAccessSecret[64];//�������ģ����֧������60�ֽ�

	//����IOT��Ԫ����Ϣ
	ICE_S8 acProductKey[32];//��Ʒ���ƣ����֧������28�ֽ�
	ICE_S8 acDevName[32];	//�豸���ƣ����֧������28�ֽ�
	ICE_S8 acDevSecret[64];	//�豸��Կ�����֧������60�ֽ�

	//�Դ�����������Ϣ
	ICE_S32 iAuthEn;			//�Ƿ����û���֤����Χ��[0,1] 0:�ر� 1:����
	ICE_S8 acUserName[64];	//�û��������֧������60�ֽ�
	ICE_S8 acPassword[64];	//���룬���֧������60�ֽ�
	ICE_U32 uiVersion;		//ͨ��Э����չ�����汾��,Ĭ��1.0.0,ÿһλ���ֵ255,��ӦuiVersion=0x00010000
	ICE_U32 uiExtVersion;	//��չ�����汾��
	ICE_U8 aucReserved[256]; //ͨ��Э��Ԥ������,ͨ�ò�����
	ICE_U8 aucExtReserved[2048];//��չ����Ԥ��
}T_MqttCfgParam;

//�Խ�������OSD����
typedef struct T_RczSingleTextOsd
{
	ICE_U32 uiTextSize;//�����С����Χ1-7
	ICE_U32 uiTextColor;//������ɫ,������ɫ��AsRGB888����8λ��ʾ��ɫ��������8λ��ʾ��ɫ��������8λ��ʾ��ɫ���������8λ��ʾ͸����
	ICE_U32 uiPosX;//x����,��Χ0-800
	ICE_U32 uiPosY;//y���꣬��Χ0-1280
	ICE_U8 ucTextStr[128];//�������ݣ�utf8���룬Ŀǰ���֧��90byte(��������)
	ICE_U8 ucResvr[256];//Ԥ��
}T_RczSingleTextOsd;

#define MAX_RCZ_OSD_NUM 13
typedef struct T_RczTextOsd
{
	T_RczSingleTextOsd tRczSingleTextOsd[MAX_RCZ_OSD_NUM];//���֧��13��
	ICE_U8 ucResvr[256];//Ԥ��
}T_RczTextOsd;

typedef enum E_RemCtrlKeyDeal
{
	E_RemCtrlKeyDeal_EnterOpen = 0, // �����볡
	E_RemCtrlKeyDeal_EnterClose, // �볡��բ
	E_RemCtrlKeyDeal_ExitOpen, // ��ѷ���
	E_RemCtrlKeyDeal_ExitMoneyOpen, // �շѷ���
	E_RemCtrlKeyDeal_ExitClose, // ������բ
	E_RemCtrlKeyDeal_Blank, // ��δ����
	E_RemCtrlKeyDeal_Error, // ������
	E_RemCtrlKeyDeal_Max
} E_RemCtrlKeyDeal;

//ң�����¼��ϱ����ݽṹ��
typedef struct tagT_RemCtrlData
{
	ICE_S32 iKeyDealType;//����ֵ�������E_RemCtrlKeyDeal
	ICE_S8  acReserved[256];//Ԥ��
}T_RemCtrlData;

#define MAX_KEY_NUM 8
//ң��������/��ȡ���ݽṹ��
typedef struct tagT_RemCtrlCfg
{
	ICE_S32 iKeyDealNum;//������������֧������
	ICE_S32 iKeyDealType[MAX_KEY_NUM];//�±�0��ӦKEY1,�±�1��ӦKEY2���Դ����ƣ�Ŀǰ֧��4��������������ֵ�����E_RemCtrlKeyDeal
	ICE_S8  acReserved[256];//Ԥ��
}T_RemCtrlCfg;

typedef struct tagT_TalkBackCfg
{
	ICE_S32 iCallTimeouts;//���г�ʱʱ��,��Χ��30-300����λ���룩 
	ICE_S8  acReserved[256];//Ԥ��
}T_TalkBackCfg;

#ifdef __cplusplus
}
#endif


#endif // __ICE_COM_H__


