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
	ICE_STATUS_NOERROR = 0,		//�ɹ�
	ICE_STATUS_INVALID_HANDLE,	//handleΪ��
	ICE_STATUS_INVALID_PARAM,	//��������ȷ
	ICE_STATUS_INIT_FAILED,		//��ʼ��ʧ��
	ICE_STATUS_SEND_FAILURE,	//����ʧ��
	ICE_STATUS_TIMEOUT,			//����ʱ��δ���յ������������
	ICE_STATUS_RECV_FAILURE,	//�������ʧ��
	ICE_STATUS_CONN_ERROR,		//������Ϣ��֤ʧ��
	ICE_STATUS_CONN_FAILED,		//���Ӳ��ɹ�
	ICE_STATUS_ANALYSIS_ERROR,	//���ݽ�������
	ICE_STATUS_FILE_NOT_EXIST,	//�ļ�������
	ICE_STATUS_FILE_OPEN_ERROR,	//���ļ�ʧ��
	ICE_STATUS_FILE_NOT_COMPLIANT,//�ļ������Ϲ淶
	ICE_STATUS_NOT_SUPPORT		//��֧��
}E_ICE_SDK_STATUS;

#if 0
typedef enum
{
	ICE_DEVICE_OFFLINE,		//����
	ICE_DEVICE_ONLINE,		//����
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
	int enable;			//NTPʹ��
	int period;			//ͬ�������������ͬ��һ�Σ���λ�루10-3600��
	int diff;			//ͬ����ֵ����������������ʱ�������������ϲ�ͬ������λ�루����1��
	int port;			//NTP�������˿ڣ�0-65535��
	char serverIp[128];	//NTP��������ַ
	char resv[256];
}ICE_NTPCFG_S;

//----------------------------------------------
// ����ʶ������ṹ����
//----------------------------------------------
//! �������Ͷ���
typedef enum 
{
	ICE_PLATE_UNCERTAIN			= 0,	//!< ��ȷ����
	ICE_PLATE_BLUE				= 1,	//!< ���Ƴ�
	ICE_PLATE_YELLOW			= 2,	//!< ������Ƴ�
	ICE_PLATE_POLICE			= 4,    //!< ����
	ICE_PLATE_WUJING			= 8,	//!< �侯����
	ICE_PLATE_DBYELLOW			= 16,	//!< ˫�����
	ICE_PLATE_MOTOR				= 32,	//!< Ħ�г�
	ICE_PLATE_INSTRUCTIONCAR	= 64,	//!< ������
	ICE_PLATE_MILITARY			= 128,	//!< ����
	ICE_PLATE_PERSONAL			= 256,	//!< ���Ի���
	ICE_PLATE_GANGAO			= 512,	//!< �۰ĳ�
	ICE_PLATE_EMBASSY			= 1024,			//!< ʹ�ݳ�
	ICE_PLATE_NONGLARE			= 2048,			//!< ��ʽ����(������)
	ICE_PLATE_AVIATION			= 4096,			//!< �񺽳���
	ICE_PLATE_NEWENERGY			= 8192,			//!< ����Դ����
	ICE_PLATE_NEWENERGYBIG		= 0x00004000,	//!< ����Դ���ƴ󳵣�
	ICE_PLATE_WHITE_TWOTWO		= 0x10000001,	//!< 2+2ģ�ͣ�
	ICE_PLATE_WHITE_TWOTHR		= 0x10000002,	//!< 2+3ģ�ͣ�
	ICE_PLATE_WHITE_THRTWO		= 0x10000004,	//!< 3+2ģ�ͣ�
	ICE_PLATE_WHITE_THRTHR		= 0x10000008,	//!< 3+3ģ�ͣ�
	ICE_PLATE_WHITE_THRFOR		= 0x10000010,	//!< 3+4ģ�ͣ�
	ICE_PLATE_BLACK_THRTWO		= 0x10000020,	//!< 3+2ģ�ͣ�
	ICE_PLATE_BLACK_TWOTHR		= 0x10000040,	//!< 2+3ģ�ͣ�
	ICE_PLATE_BLACK_THRTHR		= 0x10000080,	//!< 3+3ģ�ͣ�
	ICE_PLATE_BLACK_TWOFOR		= 0x10000100,	//!< 2+4ģ�ͣ�
	ICE_PLATE_BLACK_FORTWO		= 0x10000200,	//!< 4+2ģ�ͣ�
	ICE_PLATE_BLACK_THRFOR		= 0x10000400,	//!< 3+4ģ�ͣ�
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
	char	plateNum[128];		//���ƺţ�UTF-8����
	char	plateColor[32];		//������ɫ��UTF-8����
	int		flasePlate;			//�Ƿ�Ϊ��ٳ���
	float	confidence;			//���ֵ
	ICE_PLATETYPE_E	plateType;	//��������
	ICE_RECT_S	stPlateRect;	//���ƾ��ο�
	char	resv[256];			//Ԥ��
}ICE_PLATEINFO_S;

typedef enum
{
	ICE_VDC_VEHICLE_TYPE_UNKOWN				= 0,			//!<  δ֪
	ICE_VDC_VEHICLE_TYPE_NORMAL_CAR			= 1,			//!<  �γ�
	ICE_VDC_VEHICLE_TYPE_MINIBUS			= 2,			//!<  �����
	ICE_VDC_VEHICLE_TYPE_BUS				= 3,			//!<  ���Ϳͳ�
	ICE_VDC_VEHICLE_TYPE_MEDIUMBUS			= 4,			//!<  ���Ϳͳ�
	ICE_VDC_VEHICLE_TYPE_PICK_UP_TRUCK		= 5,			//!<  Ƥ��
	ICE_VDC_VEHICLE_TYPE_NONMOTORIZED	    = 6,			//!<  �ǻ�����
	ICE_VDC_VEHICLE_TYPE_SUV				= 7,			//!<  SUV
	ICE_VDC_VEHICLE_TYPE_MPV				= 8,			//!<  MPV
	ICE_VDC_VEHICLE_TYPE_MINITRUCK			= 9,			//!<  ΢�ͻ���
	ICE_VDC_VEHICLE_TYPE_PICKUPTRUCK		= 10,			//!<  ���ͻ���
	ICE_VDC_VEHICLE_TYPE_MEDIUMTRUCK		= 11,			//!<  ���ͻ���
	ICE_VDC_VEHICLE_TYPE_HEAVYTRUCK			= 12,			//!<  ���ͻ���
}ICE_VDC_VEHICLETYPE_E;

typedef enum
{
	ICE_VCR_VEHICLE_COLOR_UNKOWN 	= -1,	 //!<  δ֪
	ICE_VCR_VEHICLE_COLOR_BLACK 	= 0,	 //!<  ��ɫ
	ICE_VCR_VEHICLE_COLOR_BLUE 		= 1,	 //!<  ��ɫ

	ICE_VCR_VEHICLE_COLOR_GRAY 		= 2,	 //!<  ��ɫ	
	ICE_VCR_VEHICLE_COLOR_BROWN 	= 3,	 //!<  ��ɫ
	ICE_VCR_VEHICLE_COLOR_GREEN 	= 4,	 //!<  ��ɫ
	ICE_VCR_VEHICLE_COLOR_NIGHTDARK	= 5,   	 //!<  ҹ����ɫ
	ICE_VCR_VEHICLE_COLOR_PURPLE	= 6,	 //!<  ��ɫ
	ICE_VCR_VEHICLE_COLOR_RED 		= 7,	 //!<  ��ɫ
	ICE_VCR_VEHICLE_COLOR_WHITE 	= 8,	 //!<  ��ɫ
	ICE_VCR_VEHICLE_COLOR_YELLOW 	= 9,	 //!<  ��ɫ

}ICE_VCR_VEHICLECOLOR_E;

typedef enum 
{
	ICE_VDC_VERHICLE_DIR_HEAD			 = 0,				//!<  ��ͷ���� 			
	ICE_VDC_VERHICLE_DIR_TAIL			 = 1,				//!<  ��β���� 			
	ICE_VDC_VERHICLE_DIR_HEAD_AND_TAIL	 = 2				//!<  ��ͷ�ͳ�β���� 	
}ICE_VDC_VERHICLE_DIR_E;

typedef struct
{
	ICE_VDC_VEHICLETYPE_E	vehicleType;	//��������
	ICE_VCR_VEHICLECOLOR_E	vehicleColor;	//������ɫ
	ICE_VDC_VERHICLE_DIR_E	vehicleDir;		//��������
	char	logName[128];					//Ʒ�ƣ�UTF-8����
	char	subLogName[128];				//��Ʒ�ƣ�UTF-8����
	char	productYearName[32];			//�������
	char	resv[256];						//Ԥ��				
}ICE_VEHICLEINFO_S;

//��������
typedef enum
{
	ICE_VDC_VIDEO_TRIGGER, 					//��Ƶ����
	ICE_VDC_HD_TRIGGER,						//Ӳ����
	ICE_VDC_SOFT_TRIGGER,					//����
	ICE_VDC_TRIGGER_UNKOWN,
}ICE_VDC_TRIGGER_TYPE_E;

typedef struct  
{
	ICE_PLATEINFO_S				plateInfo;		//������Ϣ
	ICE_VEHICLEINFO_S			vehicleInfo;	//������Ϣ
	ICE_VDC_TRIGGER_TYPE_E		triggerType;	//�������� 
	ICE_DATE_TIME_INFO_S		capTime;		//ץ��ʱ��
	char	resv[256];							//Ԥ��
}ICE_LPRRESULT_S;
#endif

#define MAX_LINEOSD_TEXT 256
#define MAX_PLATE_OSD_TEXT 64
#define MAX_CUSTOM_OSD_LINE_NUM 6

typedef struct T_LineTextOsd
{
	UINT32 uiTextSize;//�����С 0�� 1�� 2С
	UINT32 uiTextColor;//������ɫ��RGB888����8λ��ʾ��ɫ��������8λ��ʾ��ɫ��������8λ��ʾ��ɫ����
	UINT32 uiAlignMode;//���뷽ʽ��ǿ�ƾ��ж��룬����ʹ�ã�
	UINT8 ucTextStr[MAX_LINEOSD_TEXT];//�������ݣ�����ΪСʱ��Ŀǰ���֧��128byte������Ϊ��ʱ��Ŀǰ���֧��84byte;����Ϊ��ʱ�����֧��64byte��UTF8����
	UINT8 ucResvr[256];//Ԥ��
}T_LineTextOsd;

typedef struct T_TextOsd
{
	T_LineTextOsd tLineTextOsd[MAX_CUSTOM_OSD_LINE_NUM];//Ŀǰ���֧��2�У������±�0��ʾ��һ�� �±�1��ʾ�ڶ���
	UINT8 ucResvr[128];//Ԥ��
}T_TextOsd;

typedef struct T_PlateOsd
{
	UINT32 uiTextColor;//������ɫ��RGB888����8λ��ʾ��ɫ��������8λ��ʾ��ɫ��������8λ��ʾ��ɫ����
	UINT8  ucPlateStr[MAX_PLATE_OSD_TEXT];//������Ϣ��Ŀǰ���֧��18byte,UTF8����
	UINT8 ucResvr[128];//Ԥ��
}T_PlateOsd;

typedef struct T_LcdParam
{
	UINT32 uiPicSwitchTime;//ͼƬ�л�Ƶ�ʣ�ͼƬ��ʾʱ��������λ���룬��Χ1-300
	UINT32 uiPlateShowTime;//������Ϣ��ʾʱ��������ģʽ��Ч������λ���룬��Χ1-100
	UINT32 uiScreenDisplayDir;//��Ļ��ʾ����0 ���ԣ� 1����
	UINT32 uiQrCodeBgColor;//��ά�뱳����ɫ��RGB888����8λ��ʾ��ɫ��������8λ��ʾ��ɫ��������8λ��ʾ��ɫ����
	UINT8 ucResvr[120];//Ԥ��
}T_LcdParam;

typedef struct T_AdPicPlayParam
{
	UINT32 uiEnable;//0ֹͣ�ֲ���1��ʼ�ֲ�
	UINT32 uiAdPicType;//1ȫ����� 2�������
	UINT8 ucResvr[128];//Ԥ��
}T_AdPicPlayParam;

#if 0
typedef struct 
{
	UINT32	u32Size;							//!<  ���ݰ�����
	UINT32	u32Type;							//!<  ����
	UINT32	u32Status;							//!<  ״̬
	UINT32	u32Channel;							//!<  ͨ����
	UINT32	u32Time;							//!<  ʱ��
	UINT32	u32Date;							//!<  ����
	UINT32	u32Id;								//!<  ��ʶ
	UINT32	u32Level;							//!<  ��������
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
	int as32Reserved[4]; //Ԥ������
} T_TalkBackVolumeParam;
#endif

typedef struct  
{
	UINT32 uiTextType;		//��������ʾ���ͣ�0��ʾ����ר������+2���Զ����������ͣ�1��ʾ4�ж�����������
	T_PlateOsd tPlateOsd;	//����ר������ĳ���������Ϣ
	T_TextOsd tTextOsd;		//�Զ�����������Ϣ����������ʾ����Ϊ0ʱ��ȡǰ2���Զ������ݣ���������ʾ����Ϊ1ʱ��ȡǰ4���Զ������ݣ�
	UINT8 ucResvr[256];//Ԥ��
}T_LcdShowInfo;

typedef struct  
{
	UINT32 uiLightLevel;//���ȵȼ�����Χ1-5
	UINT32 uiScrollSpeed;//�����ٶȣ���Χ1-3��1-����2-�У�3-��
	UINT32 uiLineMode;//����ģʽ����Χ0-1��0-2�ߣ�1-1��
	UINT32 uiScanNums; //ɨ��ģʽ����Χ0-1��0-32ɨ��1-16ɨ
	UINT32 uiScreenDir;//���Է��򣬷�Χ0-1��0-������1-����
	UINT32 uiScreenMode;//��ģʽ����Χ0-1��0-������1-˫��
	UINT32 uiVolume;//��������Χ0-10,0Ϊ����
	UINT32 uiVoiceSpeed;//���٣�Ԥ�����ݲ�֧�֣�
	UINT32 uiVoiceType;//�������ͣ�Ԥ�����ݲ�֧�֣�
	UINT8 ucResvr[244];//Ԥ��
}T_LedCfgInfo;

typedef struct  
{
	UINT8 ucLineText[MAX_LINEOSD_TEXT];//�Զ�����ʾ���֣�Ŀǰ�������120�ֽڣ�utf8����
	UINT32 uiColor;//������ɫ����Χ0-2��0-��ɫ��1-��ɫ��2-��ɫ
	UINT8 ucResvr[256];//Ԥ��
}T_LedLineInfo;

typedef struct
{
	UINT32 uiSetQRCodeUrl;//�Ƿ����ö�ά��url����Χ0-1
	UINT8 ucUrl[MAX_LINEOSD_TEXT];//��ά��url��Ŀǰ�������180�ֽڣ�utf8����
	UINT32 uiColor;//������ɫ����Χ0-2��0-��ɫ��1-��ɫ��2-��ɫ
	UINT8 ucResvr[256];//Ԥ��
}T_QRCodeInfo;

#define MAX_LED_LINE_NUM 8
typedef struct  
{
	T_LedLineInfo tLedLineInfo[MAX_LED_LINE_NUM];//�Զ�����������Ϣ��Ŀǰ���֧��4��
	T_QRCodeInfo tQrCodeInfo;//��ά��ͼƬ��Ϣ
	UINT8 ucResvr[256];//Ԥ��
}T_LedShowInfo;

#ifdef __cplusplus
}
#endif
#endif