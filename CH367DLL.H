// 2011.07.01 V1.0
//****************************************
//**  Copyright  (C)  W.ch  1999-2011   **
//**  Web:  http://www.winchiphead.com  **
//****************************************
//**  DLL for PCI interface chip CH367/8**
//**  C, VC5.0                          **
//****************************************
//
// PCIe���߽ӿ�оƬCH367��Ӧ�ò�ӿڿ� V1.0
// �Ͼ��ߺ�������޹�˾ ����: TECH30 2011.07
// CH367-DLL  V1.0 ,    Support: IO/MEM/INT
// ���л���: Windows 98/ME, Windows 2000/XP/7
//
/* !!ע���:
     1.CH367DLL�ӿ���Ӧ��CH367&CH368оƬ,CH367��ͷ�ĺ���������CH367��CH368,CH368��ͷ�ĺ���ֻ������CH368оƬ,��������CH367.   
     2.CH368֧��PC�����������ֽڣ�˫�֣�Ϊ��λ��I/O �˿ڻ��ߴ洢�����ж�д��
       CH367mReadIoWord/CH367mWriteIoWord�������ֲ���ʱ����ʼ��ַ�����ǻ�ַ��Χ�ڵ������ֱ߽�ĵ�ַ��2 �ı�������
       CH367mReadIoDword/CH367mWriteIoDword/CH368ReadMemDword/CH368WriteMemDword�������ֽڴ�ȡʱ����ʼ��ַ�����ǻ�ַ��Χ�ڵ�����˫�ֱ߽�ĵ�ַ��4 �ı�����
*/

#include "windows.h" //must add this man
       
#ifndef		_CH367_DLL_H
#define		_CH367_DLL_H

#ifdef __cplusplus
extern "C" {
#endif


#define		mOFFSET( s, m )			( (ULONG_PTR) & ( ( ( s * ) 0 ) -> m ) )	// �����ȡ�ṹ��Ա���ƫ�Ƶ�ַ�ĺ�

#ifndef		max
#define		max( a, b )				( ( ( a ) > ( b ) ) ? ( a ) : ( b ) )	// �ϴ�ֵ
#endif

#ifndef		min
#define		min( a, b )				( ( ( a ) < ( b ) ) ? ( a ) : ( b ) )	// ��Сֵ
#endif

#ifdef		ExAllocatePool
#undef		ExAllocatePool						// ɾ����TAG���ڴ����
#endif

#ifndef		NTSTATUS
typedef		LONG	NTSTATUS;					// ����״̬
#endif


typedef	struct	_PCI_CONFIG {					// ����PCI���ÿռ����ݽṹ
	USHORT			mPcVendorId;				// 00H ��Ӧ�̱�ʶ
	USHORT			mPcDeviceId;				// 02H �豸��ʶ
	USHORT			mPcCommandReg;				// 04H ����Ĵ���
	USHORT			mPcStatusReg;				// 06H ״̬�Ĵ���
	UCHAR			mPcRevisionId;				// 08H �޸ı�ʶ
	UCHAR			mPcProgramIf;				// 09H �Ĵ�������̽ӿ�
	UCHAR			mPcSubClass;				// 0AH �������
	UCHAR			mPcBaseClass;				// 0BH �����������
	UCHAR			mPcCacheLine;				// 0CH �����г���
	UCHAR			mPcLatenTimer;				// 0DH �ӳټ�����
	UCHAR			mPcHeaderType;				// 0EH ͷ������
	UCHAR			mPcBistReg;					// 0FH �ں��Բ��ԼĴ���
	ULONG			mPcBaseAddr0;				// 10H ��ַ�Ĵ���0
	ULONG			mPcBaseAddr1;				// 14H ��ַ�Ĵ���1
	ULONG			mPcBaseAddr2;				// 18H ��ַ�Ĵ���2
	ULONG			mPcBaseAddr3;				// 1CH ��ַ�Ĵ���3
	ULONG			mPcBaseAddr4;				// 20H ��ַ�Ĵ���4
	ULONG			mPcBaseAddr5;				// 24H ��ַ�Ĵ���5
	ULONG			mPcCardCis;					// 28H
	USHORT			mPcSubSysVen;				// 2CH ��ϵͳ��Ӧ�̱�ʶ
	USHORT			mPcSubSysDev;				// 2EH ��ϵͳ�豸��ʶ
	ULONG			mPcExpansRom;				// 30H ��չROM��ַ�Ĵ���
	UCHAR			mPcCapPtr;					// 34H
	UCHAR			mPcReserved1[3];			// 35H
	ULONG			mPcReserved2;				// 38H
	UCHAR			mPcInterLine;				// 3CH �ж��߼Ĵ���
	UCHAR			mPcInterPin;				// 3DH �ж����żĴ���
	UCHAR			mPcMinGrant;				// 3EH
	UCHAR			mPcMaxLatency;				// 3FH
} mPCI_CONFIG, *mPPCI_CONFIG;

typedef	struct	_PCI_EXP_ROM {					// PCI��չROM�����ݽṹ
	UCHAR			mPerRomSig[4];				// 00H PCI��չROMǩ���ַ���'PCIR'
	USHORT			mPerVendorId;				// 04H ��Ӧ�̱�ʶ
	USHORT			mPerDeviceId;				// 06H �豸��ʶ
	USHORT			mPerVpdPtr;					// 08H ��Ҫ��Ʒ����ָ��
	USHORT			mPerStrucLen;				// 0AH PCI��չROM���ݽṹ�ĳ���
	UCHAR			mPerRevision;				// 0CH PCI��չROM���ݽṹ���޸İ汾
	UCHAR			mPerProgramIf;				// 0DH �Ĵ�������̽ӿ�
	UCHAR			mPerSubClass;				// 0EH �������
	UCHAR			mPerBaseClass;				// 0FH �����������
	USHORT			mPerImageLen;				// 10H ӳ�񳤶�
	USHORT			mPerImageRev;				// 12H ӳ���д���/���ݵ��޸İ汾
	UCHAR			mPerCodeType;				// 14H ��������
	UCHAR			mPerIndicator;				// 15H ӳ��ָʾ��־
	USHORT			mPerReserved;				// 16H
} mPCI_EXP_ROM, *mPPCI_EXP_ROM;

typedef	struct	_CH367_IO_REG {	                //CH367оƬ��I/O�ռ�Ĵ���
	UCHAR mCH367IoPort[0xE8];                     //00H-E7H,��232�ֽ�Ϊ��׼��I/O�˿�
	UCHAR mCH367GPOR;	                        //E8H ͨ������Ĵ���
	UCHAR mCH367GPVR;	                        //E9H ͨ�ñ����Ĵ���
	UCHAR mCH367GPIR;	                        //EAH ͨ������Ĵ���
	UCHAR mCH367IntCtr;	                        //EBH �жϿ��ƼĴ���
	union{
		UCHAR mCH367IoBuf8;                     //ECH 8λ�������нӿ����ݻ�����
		ULONG mCH367IoBuf32;                    //ECH 32λ�������нӿ����ݻ�����
	};
	union{
		USHORT mCH368MemAddr;                   //F0H �洢���ӿ�: A15-A0��ַ�趨�Ĵ��� ??
		struct{
			UCHAR mCH368MemAddrL;               //F0H �洢���ӿ�: A7-A0��ַ�趨�Ĵ���
			union{
				UCHAR mCH368MemAddrH;           //F1H �洢���ӿ�: A15-A8��ַ�趨�Ĵ���
				UCHAR mCH367GPOR2;              //F1H ͨ������Ĵ���2 ??
			};
		}ASR;
	};
	UCHAR mCH367IORESV2;                        //F2H
	UCHAR mCH368MemData;                        //F3H �洢���ӿ�: �洢�����ݴ�ȡ�Ĵ���
	union{
		UCHAR mCH367Data8Sta;                   //F4H D7-D0�˿�״̬�Ĵ���
		ULONG mCH367SData32Sta;                 //F4H D31-D0�˿�״̬�Ĵ���
	};
	UCHAR mCH367Status;                         //F8H ������ƺ�״̬�Ĵ���
	UCHAR mCH367IO_RESV3;                       //F9H
	UCHAR mCH367Speed;                          //FAH ��д�ٶȿ��ƼĴ���
	UCHAR mCH367PDataCtrl;                      //FBH �������нӿڿ��ƼĴ���
	UCHAR mCH367IoTime;                         //FCH Ӳ��ѭ�������Ĵ���
	UCHAR mCH367SPICtrl;                        //FDH SPI���ƼĴ���
	UCHAR mCH367SPIData;                        //FEH SPI���ݼĴ���
	UCHAR mCH367IO_RESV4;                       //FFH
} mCH367_IO_REG, *mPCH367_IO_REG;

typedef	struct	_CH368_MEM_REG {				// CH367оƬ�Ĵ洢���ռ�
	UCHAR			mCH368MemPort[0x8000];		// 0000H-7FFFH,��32768�ֽ�Ϊ��׼�Ĵ洢����Ԫ
} mCH368_MEM_REG, *mPCH368_MEM_REG;

typedef	struct	_WIN32_COMMAND {				// ����WIN32����ӿڽṹ
	union	{
		ULONG		mFunction;					// ����ʱָ�����ܴ���
		NTSTATUS	mStatus;					// ���ʱ���ز���״̬
	};
	ULONG			mLength;					// ��ȡ����,���غ������ݵĳ���
	union	{
		PVOID			mAddress;				// ��ʼ��ַ,���ص�ַ
		ULONGLONG		mAddress64;				// ��ʼ��ַ,���ص�ַ
	};
	UCHAR			mBuffer[8];					// ���ݻ�����,����Ϊ0��32KB
} mWIN32_COMMAND, *mPWIN32_COMMAND;

// WIN32Ӧ�ò�ӿ�����
#define		IOCTL_CH367_COMMAND		( FILE_DEVICE_UNKNOWN << 16 | FILE_ANY_ACCESS << 14 | 0x0f36 << 2 | METHOD_BUFFERED )	// ר�ýӿ�

#define		mWIN32_COMMAND_HEAD		mOFFSET( mWIN32_COMMAND, mBuffer )	// WIN32����ӿڵ�ͷ����

#define		mCH367_MAX_NUMBER		16			// ���ͬʱ���ӵ�CH367��

#define		mMAX_BUFFER_LENGTH		max( sizeof( mCH367_IO_REG ), sizeof( mCH368_MEM_REG ) )	// ���ݻ�������󳤶�

#define		mMAX_COMMAND_LENGTH		( mWIN32_COMMAND_HEAD + mMAX_BUFFER_LENGTH )	// ������ݳ��ȼ�������ṹͷ�ĳ���

#define		mCH368_MEM_BASE_AUTO	( (PVOID)(ULONG_PTR)0xffffffff )	// �Զ��趨CH368�Ĵ洢����ַ

#define		mCH367_INT_LINE_AUTO	0xffffffff				// �Զ����CH367���жϺ�

// �Ĵ�����λ����
//0xE8
#define		mBitI2cSdaOut           0x01        //�趨SDA ���ŵ����ֵ(1),1*:high,0:low
#define		mBitI2cSclOut           0x02        //�趨SCL ���ŵ����ֵ(1)
#define		mBitSpiScsOut           0x04        //�趨SCS ���ŵ����ֵ(1)
#define		mBitBeWakenEnable       0x32        //ʹ��֧�ֱ�ǿ�ƻ���(0)
#define		mBitSetSpiSdxDir        0x64        //�趨SDX ���ŵ����ݷ���(0)
//0xEA
#define		mBitSpiSdxOut           0x01        //����SDA ���ŵ�״̬(1)
#define		mBitIntStatus           0x08        //����INT#���ŵ�״̬(1)
#define		mBitRDStatus            0x10        //����RD#���ŵ�״̬(1)
#define		mBitWRStatus            0x20        //����WR#���ŵ�״̬(1)
#define		mBitAddrStatus          0x40        //����ADDR ���ŵ�״̬(1)
#define		mBitSdxStatus           0x80        //����SDX ���ŵ�״̬(1)
//0xEB
#define		mBitGlobalIntEnable     0x02        //ȫ���ж�ʹ��(0)
#define		mBitIntPolarity         0x04        //INT#�����ж�����ļ���(0),0:�͵�ƽ/������;1:�ߵ�ƽ/�½���
#define		mBitIntInType           0x08        //INT#�����ж����������(0)
//0xF8:
#define		mBitAddr15Out           0x01        //�趨A15 ���ŵ����ֵ(1)
#define		mBitIntAction           0x04        //�жϼ���״̬(0)
#define		mBitIntStatus           0x08        //����INT#���ŵ�״̬(1)     
#define		mBitRST0Out             0x80        //�趨RSTO ���ŵ����ֵ(1)
//0xFA
#define		mBitSpeedInact          0xFA        //������ʱ��ͱ���ʱ��Ķ�д�ź��ܿ���(0111)
#define		mBitDataAddrOutCreate   0x10        //���ݺ͵�ַ�������ʱ��(0),0:15nS,1:45nS
#define		mBitDataAddrOutKeep     0x20        //���ݺ͵�ַ�������ʱ��(0),0:15nS,1:45nS
#define		mBitLocalBusWidth       0x40        //�����������߿���(0),0:8λ,1:32λ
//0xFD
#define		mBitHWCountH4           0x0F        //Ӳ��ѭ�������ĸ�4 λ(XXXX),��Ӳ��ѭ�������Ĵ���CNTR ����һ��12 λ
#define		mBitSpiTransportStatus  0x10        //SPI �������ڽ���״̬(0),0:����,1:���ڴ���
#define		mBitSpiClockFreq        0x20        //ѡ��SPI ����ʱ��Ƶ��(0),0:31.3MHz,1:15.6MHz
#define		mBitSelSpiInPin         0x40        //ѡ��SPI ������������(0),0:SDK,1:ADDR
#define		mBitStartNewSPITrans    0x80        //ʹ�ܶ�SPIDR �������´���(0),0:�������,1:��������


// Ӧ�ò�ӿڵĹ��ܴ���
#define		mFuncNoOperation		0x00000000	// �޲���
#define		mFuncGetVersion			0x00000001	// ��ȡ��������汾��
#define		mFuncGetIoBaseAddr		0x00000004	// ��ȡI/O�˿ڻ�ַ
#define		mFuncSetIoBaseAddr		0x00000005	// ����I/O�˿ڻ�ַ
#define		mFuncGetMemBaseAddr		0x00000006	// ��ȡ�洢����ַ
#define		mFuncSetMemBaseAddr		0x00000007	// ���ô洢����ַ,�Զ��趨�洢����ַ
#define		mFuncGetInterLine		0x00000008	// ��ȡ�жϺ�
#define		mFuncSetInterLine		0x00000009	// �����жϺ�,�Զ�����жϺ�
#define		mFuncWaitInterrupt		0x0000000a	// �ȴ��ж�,ֱ��CH367�����ж�
#define		mFuncAbortWaitInter		0x0000000b	// �����ȴ��ж�,��ֹ�ȴ�
#define		mFuncSetExclusive		0x0000000c	// ���ö�ռʹ��
#define		mFuncReadIoByte			0x00000010	// ��ȡ��������˿�,��ͬһ���˿ڵ�ַ���ֽ�Ϊ��λ������ȡ
#define		mFuncReadIoWord			0x00000011	// ��ȡ��������˿�,��ͬһ���˿ڵ�ַ����Ϊ��λ������ȡ
#define		mFuncReadIoDword		0x00000012	// ��ȡ��������˿�,��ͬһ���˿ڵ�ַ��˫��Ϊ��λ������ȡ
#define		mFuncReadIoBlock		0x00000013	// ��ȡ��������˿�,ÿ��ȡһ���ֽ�,�˿ڵ�ַ��һ
#define		mFuncReadIo32Block		0x00000028	// ��ȡ��������˿�,ÿ��ȡ���ֽ�,�˿ڵ�ַ����,��󳤶�232B(��ƫ�Ƶ�ַ00H����E7H)
#define		mFuncWriteIoByte		0x00000014	// д����������˿�,��ͬһ���˿ڵ�ַ���ֽ�Ϊ��λ����д��
#define		mFuncWriteIoWord		0x00000015	// д����������˿�,��ͬһ���˿ڵ�ַ����Ϊ��λ����д��
#define		mFuncWriteIoDword		0x00000016	// д����������˿�,��ͬһ���˿ڵ�ַ��˫��Ϊ��λ����д��
#define		mFuncWriteIoBlock		0x00000017	// д����������˿�,ÿд��һ���ֽ�,�˿ڵ�ַ��һ
#define		mFuncWriteIo32Block		0x00000029	// д����������˿�,ÿд��һ�����ֽ�,�˿ڵ�ַ����,��󳤶�232B(��ƫ�Ƶ�ַ00Hд��E7H)
#define		mFuncReadMemByte		0x00000018	// ��ȡ�洢��/�Ĵ���
#define		mFuncReadMemDword		0x0000001a	// ��ȡ�洢��/�Ĵ���
#define		mFuncWriteMemByte		0x0000001c	// д��洢��/�Ĵ���
#define		mFuncWriteMemDword		0x0000001e	// д��洢��/�Ĵ���
#define		mFuncReadConfig			0x00000020	// ��ȡPCI���ÿռ�
#define		mFuncWriteConfig		0x00000021	// д��PCI���ÿռ�
#define		mFuncReadBuffer1		0x00000024	// ��ȡ�ж��������1
#define		mFuncWriteBuffer1		0x00000025	// д���ж��������1
#define		mFuncReadBuffer2		0x00000026	// ��ȡ�ж��������2
#define		mFuncWriteBuffer2		0x00000027	// д���ж��������2

#define		mFuncStreamSPI	    	0x0000002A	// SPI���������亯��
#define		mFuncSetStreamMode    	0x0000002B	// ����SPIΪSPI3��SPI4
#define		mFuncSetInterMode    	0x0000002C	// �����жϼ��Լ���������


#define		mFuncFlashLock    	0x0000002D	// ��Flash-ROM�洢������д�����趨 
#define		mFuncFlashRead    	0x0000002E	// ��Flash-ROM�洢����ȡ���ݿ�
#define		mFuncFlashErase    	0x0000002F	// ��Flash-ROM�洢����ָ��������в���,ÿ4096�ֽڼ�4KΪһ������,��С������λ������
#define		mFuncFlashWrite    	0x00000030	// ��Flash-ROM�洢��д�����ݿ�

typedef		VOID	( CALLBACK	* mPCH367_INT_ROUTINE ) ( VOID );		// �жϷ������



HANDLE	WINAPI	CH367OpenDevice(  // ��CH367�豸,���ؾ��,��������Ч
	BOOL			iEnableMemory,  // �Ƿ���Ҫ֧�ִ洢��,CH367оƬ��֧��,CH368оƬ֧��
	BOOL			iEnableInterrupt,  // �Ƿ���Ҫ֧���ж�
    UCHAR           iInterruptMode ); // λ0:�ж�����ļ���1:�ߵ�ƽ/�½���;0:�͵�ƽ/������;λ1:�ж���������� 1:����,0:��ƽ


VOID	WINAPI	CH367CloseDevice( );  // �ر�CH367�豸


ULONG	WINAPI	CH367GetVersion( );  // ���DLL�汾��,���ذ汾��


ULONG	WINAPI	CH367DriverCommand(  // ֱ�Ӵ����������������,�����򷵻�0,���򷵻����ݳ���
	mPWIN32_COMMAND	ioCommand );  // ����ṹ��ָ��
// �ó����ڵ��ú󷵻����ݳ���,������Ȼ��������ṹ,����Ƕ�����,�����ݷ���������ṹ��,
// ���ص����ݳ����ڲ���ʧ��ʱΪ0,�����ɹ�ʱΪ��������ṹ�ĳ���,�����һ���ֽ�,�򷵻�mWIN32_COMMAND_HEAD+1,
// ����ṹ�ڵ���ǰ,�ֱ��ṩ:����ܴ���,��ʼ��ַ(��ѡ),��ȡ���ݵĳ���(��ѡ),
// ����ṹ�ڵ��ú�,�ֱ𷵻�:����״̬����,���صĻ�ַ(��ѡ),�������ݵĳ���(��ѡ),
// ����״̬��������WINDOWS����Ĵ���,���Բο�NTSTATUS.H,
// ���صĻ�ַֻ��������������:��ȡI/O��ַ,��ȡ�洢����ַ,��ȡ�жϺ�,�������������򱣳�����ʱ����ʼ��ַ
// �������ݵĳ�����ָ���������ص����ݳ���,���ݴ�������Ļ�������,����д����һ��Ϊ0

ULONG	WINAPI	CH367GetDrvVersion( );  // �����������汾��,���ذ汾��,�����򷵻�0


BOOL	WINAPI	CH367GetIoBaseAddr(  // ��ȡI/O�˿ڵĻ�ַ
	mPCH367_IO_REG	*oIoBaseAddr );  // ����I/O�˿ڻ�ַ�ĵ�Ԫ��ַ


BOOL	WINAPI	CH367SetIoBaseAddr(  // �趨I/O�˿ڵĻ�ַ
	mPCH367_IO_REG	iIoBaseAddr );  // ָ��I/O�˿ڻ�ַ


BOOL	WINAPI	CH368GetMemBaseAddr(  // ��ȡ�洢���Ļ�ַ
	mPCH368_MEM_REG	*oMemBaseAddr );  // ����洢����ַ�ĵ�Ԫ��ַ


BOOL	WINAPI	CH368SetMemBaseAddr(  // �趨�洢���Ļ�ַ
	mPCH368_MEM_REG	iMemBaseAddr );  // ָ���洢����ַ,Ϊ0��رմ洢��,Ϊ-1���Զ��趨


BOOL	WINAPI	CH367GetIntLine(  // ��ȡ�жϺ�
	PULONG			oIntLine );  // �����жϺŵĵ�Ԫ��ַ


BOOL	WINAPI	CH367SetIntLine(  // �趨�жϺ�
	ULONG			iIntLine,  // ָ���жϺ�,Ϊ0��ر��ж�,Ϊ-1���Զ���Ⲣ�趨
	UCHAR           iInterruptMode ); // λ0:�ж�����ļ���1:�ߵ�ƽ�½���;0:�͵�ƽ������;λ1:�ж�������� 1:����,0:�ж�


BOOL	WINAPI	CH367WaitInterrupt( );  // �ȴ��ж��¼�


BOOL	WINAPI	CH367AbortWaitInt( );  // �����ȴ��ж�


BOOL	WINAPI	CH367SetIntRoutine(  // �趨�жϷ������
	mPCH367_INT_ROUTINE	iIntRoutine );  // ָ���жϷ������,ΪNULL��ȡ���жϷ���,�������ж�ʱ���øó���


BOOL	WINAPI	CH367ReadIntCommand(  // ��ȡ�ж��������
	mPWIN32_COMMAND	oCommand,  // ָ��һ���㹻��Ļ�����,���ڱ����ȡ������ṹ
	ULONG			iCmdIndex );  // �ж��������,Ϊ1����2


BOOL	WINAPI	CH367WriteIntCommand(  // д���ж��������
	mPWIN32_COMMAND	iCommand,  // ָ����Ϊ�ж����������ṹ
	ULONG			iCmdIndex );  // �ж��������,Ϊ1����2


BOOL	WINAPI	CH367ReadIoByte(  // ��I/O�˿ڶ�ȡһ���ֽ�
	PVOID			iAddr,  // ָ��I/O�˿ڵĵ�ַ
	PUCHAR			oByte );  // ָ��һ���ֽڵ�Ԫ,���ڱ����ȡ���ֽ�����


BOOL	WINAPI	CH367ReadIoWord(  // ��I/O�˿ڶ�ȡһ����
	PVOID			iAddr,  // ָ��I/O�˿ڵĵ�ַ
	PUSHORT			oWord );  // ָ��һ���ֵ�Ԫ,���ڱ����ȡ��������


BOOL	WINAPI	CH367ReadIoDword(  // ��I/O�˿ڶ�ȡһ��˫��
	PVOID			iAddr,  // ָ��I/O�˿ڵĵ�ַ
	PULONG			oDword );  // ָ��һ��˫�ֵ�Ԫ,���ڱ����ȡ��˫������


BOOL	WINAPI	CH367WriteIoByte(  // ��I/O�˿�д��һ���ֽ�
	PVOID			iAddr,  // ָ��I/O�˿ڵĵ�ַ
	UCHAR			iByte );  // ��д����ֽ�����


BOOL	WINAPI	CH367WriteIoWord(  // ��I/O�˿�д��һ����
	PVOID			iAddr,  // ָ��I/O�˿ڵĵ�ַ
	USHORT			iWord );  // ��д���������


BOOL	WINAPI	CH367WriteIoDword(  // ��I/O�˿�д��һ��˫��
	PVOID			iAddr,  // ָ��I/O�˿ڵĵ�ַ
	ULONG			iDword );  // ��д���˫������


BOOL	WINAPI	CH368ReadMemByte(  // �Ӵ洢����ȡһ���ֽ�
	PVOID			iAddr,  // ָ���洢���ĵ�ַ,�����ַ
	PUCHAR			oByte );  // ָ��һ���ֽڵ�Ԫ,���ڱ����ȡ���ֽ�����


BOOL	WINAPI	CH368ReadMemDword(  // �Ӵ洢����ȡһ��˫��
	PVOID			iAddr,  // ָ���洢���ĵ�ַ,�����ַ
	PULONG			oDword );  // ָ��һ��˫�ֵ�Ԫ,���ڱ����ȡ��˫������


BOOL	WINAPI	CH368WriteMemByte(  // ��洢��д��һ���ֽ�
	PVOID			iAddr,  // ָ���洢���ĵ�ַ,�����ַ
	UCHAR			iByte );  // ��д����ֽ�����


BOOL	WINAPI	CH368WriteMemDword(  // ��洢��д��һ��˫��
	PVOID			iAddr,  // ָ���洢���ĵ�ַ,�����ַ
	ULONG			iDword );  // ��д���˫������


BOOL	WINAPI	CH367ReadConfig(  // �����ÿռ��ȡһ���ֽ�����
	PVOID			iOffset,  // ָ��ƫ�Ƶ�ַ
	PUCHAR			oByte );  // ָ��һ���ֽڵ�Ԫ,���ڱ����ȡ���ֽ�����


BOOL	WINAPI	CH367WriteConfig(  // �����ÿռ�д��һ���ֽ�����
	PVOID			iOffset,  // ָ��ƫ�Ƶ�ַ
	UCHAR			iByte );  // ��д����ֽ�����


BOOL	WINAPI	CH368SetA15_A8(  // ���øߵ�ַ,������A15-A8�����
	UCHAR			iA15_A8 );  // λ7-λ0��ӦA15-A8�����,1Ϊ�ߵ�ƽ,0Ϊ�͵�ƽ


BOOL	WINAPI	CH367ReadI2C(  // ��I2C�ӿڶ�ȡһ���ֽ�����
	UCHAR			iDevice,  // ��7λָ��I2C�豸��ַ
	UCHAR			iAddr,  // ָ�����ݵ�Ԫ�ĵ�ַ
	PUCHAR			oByte );  // ָ��һ���ֽڵ�Ԫ,���ڱ����ȡ���ֽ�����


BOOL	WINAPI	CH367WriteI2C(  // ��I2C�ӿ�д��һ���ֽ�����
	UCHAR			iDevice,  // ��7λָ��I2C�豸��ַ
	UCHAR			iAddr,  // ָ�����ݵ�Ԫ�ĵ�ַ
	UCHAR			iByte );  // ��д����ֽ�����


  HANDLE	WINAPI	CH367mOpenDevice(  // ��CH367�豸,���ؾ��,��������Ч
	ULONG			iIndex,  // ָ��CH367�豸���,0��Ӧ��һ���豸
	BOOL			iEnableMemory,  // �Ƿ���Ҫ֧�ִ洢��,CH367оƬ��֧��,CH368оƬ֧��
	BOOL			iEnableInterrupt,  // �Ƿ���Ҫ֧���ж�
    UCHAR           iInterruptMode ); // λ0:�ж�����ļ���1:�ߵ�ƽ/�½���;0:�͵�ƽ/������;λ1:�ж���������� 1:����,0:��ƽ

VOID	WINAPI	CH367mCloseDevice(  // �ر�CH367�豸
	ULONG			iIndex );  // ָ��CH367�豸���


ULONG	WINAPI	CH367mDriverCommand(  // ֱ�Ӵ����������������,�����򷵻�0,���򷵻����ݳ���
	ULONG			iIndex,  // ָ��CH367�豸���
	mPWIN32_COMMAND	ioCommand );  // ����ṹ��ָ��
// �ó����ڵ��ú󷵻����ݳ���,������Ȼ��������ṹ,����Ƕ�����,�����ݷ���������ṹ��,
// ���ص����ݳ����ڲ���ʧ��ʱΪ0,�����ɹ�ʱΪ��������ṹ�ĳ���,�����һ���ֽ�,�򷵻�mWIN32_COMMAND_HEAD+1,
// ����ṹ�ڵ���ǰ,�ֱ��ṩ:����ܴ���,��ʼ��ַ(��ѡ),��ȡ���ݵĳ���(��ѡ),
// ����ṹ�ڵ��ú�,�ֱ𷵻�:����״̬����,���صĻ�ַ(��ѡ),�������ݵĳ���(��ѡ),
//   ����״̬��������WINDOWS����Ĵ���,���Բο�NTSTATUS.H,
//   ���صĻ�ַֻ��������������:��ȡI/O��ַ,��ȡ�洢����ַ,��ȡ�жϺ�,�������������򱣳�����ʱ����ʼ��ַ
//   �������ݵĳ�����ָ���������ص����ݳ���,���ݴ�������Ļ�������,����д����һ��Ϊ0


BOOL	WINAPI	CH367mGetIoBaseAddr(  // ��ȡI/O�˿ڵĻ�ַ
	ULONG			iIndex,  // ָ��CH367�豸���
	mPCH367_IO_REG	*oIoBaseAddr );  // ����I/O�˿ڻ�ַ�ĵ�Ԫ��ַ


BOOL	WINAPI	CH367mSetIoBaseAddr(  // �趨I/O�˿ڵĻ�ַ
	ULONG			iIndex,  // ָ��CH367�豸���
	mPCH367_IO_REG	iIoBaseAddr );  // ָ��I/O�˿ڻ�ַ


BOOL	WINAPI	CH368mGetMemBaseAddr(  // ��ȡ�洢���Ļ�ַ
	ULONG			iIndex,  // ָ��CH367�豸���
	mPCH368_MEM_REG	*oMemBaseAddr );  // ����洢����ַ�ĵ�Ԫ��ַ


BOOL	WINAPI	CH368mSetMemBaseAddr(  // �趨�洢���Ļ�ַ
	ULONG			iIndex,  // ָ��CH367�豸���
	mPCH368_MEM_REG	iMemBaseAddr );  // ָ���洢����ַ,Ϊ0��رմ洢��,Ϊ-1���Զ��趨


BOOL	WINAPI	CH367mGetIntLine(  // ��ȡ�жϺ�
	ULONG			iIndex,  // ָ��CH367�豸���
	PULONG			oIntLine );  // �����жϺŵĵ�Ԫ��ַ


BOOL	WINAPI	CH367mSetIntLine(  // �趨�жϺ�
	ULONG			iIndex,  // ָ��CH367�豸���
	ULONG			iIntLine, // ָ���жϺ�,Ϊ0��ر��ж�,Ϊ-1���Զ���Ⲣ�趨
	UCHAR           iInterruptMode ); // λ0:�ж�����ļ���1:�ߵ�ƽ�½���;0:�͵�ƽ������;λ1:�ж�������� 1:����,0:�ж�


BOOL	WINAPI	CH367mWaitInterrupt(  // �ȴ��ж��¼�
	ULONG			iIndex );  // ָ��CH367�豸���


BOOL	WINAPI	CH367mAbortWaitInt(  // �����ȴ��ж�
	ULONG			iIndex );  // ָ��CH367�豸���


BOOL	WINAPI	CH367mSetIntRoutine(  // �趨�жϷ������
	ULONG			iIndex,  // ָ��CH367�豸���
	mPCH367_INT_ROUTINE	iIntRoutine );  // ָ���жϷ������,ΪNULL��ȡ���жϷ���,�������ж�ʱ���øó���


BOOL	WINAPI	CH367mReadIntCommand(  // ��ȡ�ж��������
	ULONG			iIndex,  // ָ��CH367�豸���
	mPWIN32_COMMAND	oCommand,  // ָ��һ���㹻��Ļ�����,���ڱ����ȡ������ṹ
	ULONG			iCmdIndex );  // �ж��������,Ϊ1����2


BOOL	WINAPI	CH367mWriteIntCommand(  // д���ж��������
	ULONG			iIndex,  // ָ��CH367�豸���
	mPWIN32_COMMAND	iCommand,  // ָ����Ϊ�ж����������ṹ
	ULONG			iCmdIndex );  // �ж��������,Ϊ1����2


BOOL	WINAPI	CH367mReadIoByte(  // ��I/O�˿ڶ�ȡһ���ֽ�
	ULONG			iIndex,  // ָ��CH367�豸���
	PVOID			iAddr,  // ָ��I/O�˿ڵĵ�ַ
	PUCHAR			oByte );  // ָ��һ���ֽڵ�Ԫ,���ڱ����ȡ���ֽ�����


BOOL	WINAPI	CH367mReadIoWord(  // ��I/O�˿ڶ�ȡһ����
	ULONG			iIndex,  // ָ��CH367�豸���
	PVOID			iAddr,  // ָ��I/O�˿ڵĵ�ַ
	PUSHORT			oWord );  // ָ��һ���ֵ�Ԫ,���ڱ����ȡ��������


BOOL	WINAPI	CH367mReadIoDword(  // ��I/O�˿ڶ�ȡһ��˫��
	ULONG			iIndex,  // ָ��CH367�豸���
	PVOID			iAddr,  // ָ��I/O�˿ڵĵ�ַ
	PULONG			oDword );  // ָ��һ��˫�ֵ�Ԫ,���ڱ����ȡ��˫������


BOOL	WINAPI	CH367mWriteIoByte(  // ��I/O�˿�д��һ���ֽ�
	ULONG			iIndex,  // ָ��CH367�豸���
	PVOID			iAddr,  // ָ��I/O�˿ڵĵ�ַ
	UCHAR			iByte );  // ��д����ֽ�����


BOOL	WINAPI	CH367mWriteIoWord(  // ��I/O�˿�д��һ����
	ULONG			iIndex,  // ָ��CH367�豸���
	PVOID			iAddr,  // ָ��I/O�˿ڵĵ�ַ
	USHORT			iWord );  // ��д���������


BOOL	WINAPI	CH367mWriteIoDword(  // ��I/O�˿�д��һ��˫��
	ULONG			iIndex,  // ָ��CH367�豸���
	PVOID			iAddr,  // ָ��I/O�˿ڵĵ�ַ
	ULONG			iDword );  // ��д���˫������


BOOL	WINAPI	CH368mReadMemByte(  // �Ӵ洢����ȡһ���ֽ�
	ULONG			iIndex,  // ָ��CH367�豸���
	PVOID			iAddr,  // ָ���洢���ĵ�ַ,�����ַ
	PUCHAR			oByte );  // ָ��һ���ֽڵ�Ԫ,���ڱ����ȡ���ֽ�����


BOOL	WINAPI	CH368mReadMemDword(  // �Ӵ洢����ȡһ��˫��
	ULONG			iIndex,  // ָ��CH367�豸���
	PVOID			iAddr,  // ָ���洢���ĵ�ַ,�����ַ
	PULONG			oDword );  // ָ��һ��˫�ֵ�Ԫ,���ڱ����ȡ��˫������


BOOL	WINAPI	CH368mWriteMemByte(  // ��洢��д��һ���ֽ�
	ULONG			iIndex,  // ָ��CH367�豸���
	PVOID			iAddr,  // ָ���洢���ĵ�ַ,�����ַ
	UCHAR			iByte );  // ��д����ֽ�����


BOOL	WINAPI	CH368mWriteMemDword(  // ��洢��д��һ��˫��
	ULONG			iIndex,  // ָ��CH367�豸���
	PVOID			iAddr,  // ָ���洢���ĵ�ַ,�����ַ
	ULONG			iDword );  // ��д���˫������


BOOL	WINAPI	CH367mReadConfig(  // �����ÿռ��ȡһ���ֽ�����
	ULONG			iIndex,  // ָ��CH367�豸���
	PVOID			iOffset,  // ָ��ƫ�Ƶ�ַ
	PUCHAR			oByte );  // ָ��һ���ֽڵ�Ԫ,���ڱ����ȡ���ֽ�����


BOOL	WINAPI	CH367mWriteConfig(  // �����ÿռ�д��һ���ֽ�����
	ULONG			iIndex,  // ָ��CH367�豸���
	PVOID			iOffset,  // ָ��ƫ�Ƶ�ַ
	UCHAR			iByte );  // ��д����ֽ�����


BOOL	WINAPI	CH368mSetA15_A8(  // ���øߵ�ַ,������A15-A8�����
	ULONG			iIndex,  // ָ��CH367�豸���
	UCHAR			iA15_A8 );  // λ7-λ0��ӦA15-A8�����,1Ϊ�ߵ�ƽ,0Ϊ�͵�ƽ


BOOL	WINAPI	CH367mReadI2C(  // ��I2C�ӿڶ�ȡһ���ֽ�����
	ULONG			iIndex,  // ָ��CH367�豸���
	UCHAR			iDevice,  // ��7λָ��I2C�豸��ַ
	UCHAR			iAddr,  // ָ�����ݵ�Ԫ�ĵ�ַ
	PUCHAR			oByte );  // ָ��һ���ֽڵ�Ԫ,���ڱ����ȡ���ֽ�����


BOOL	WINAPI	CH367mWriteI2C(  // ��I2C�ӿ�д��һ���ֽ�����
	ULONG			iIndex,  // ָ��CH367�豸���
	UCHAR			iDevice,  // ��7λָ��I2C�豸��ַ
	UCHAR			iAddr,  // ָ�����ݵ�Ԫ�ĵ�ַ
	UCHAR			iByte );  // ��д����ֽ�����


BOOL	WINAPI	CH367DelayUS(  // ��ʱָ��΢��
	ULONG			iDelay );  // ָ��Ҫ��ʱ��΢����,�����ʱС��10�����ϴ�


BOOL	WINAPI	CH367mAccessBlock(  // ��ȡ����д�����ݿ�
	ULONG			iIndex,  // ָ��CH367�豸���
	ULONG			iAccessMode,  // �ο������˵��
	PVOID			iAddr,  // ָ��I/O�˿ڻ��ߴ洢���ĵ�ַ
	PVOID			ioBuffer,  // ָ�������������Ļ�����
	ULONG			iLength );  // ���ݿ鳤��,Ҳ���Ƕ�ȡ����д����ֽ���,���Ȳ�����32KB

// iAccessMode ��������
// #define		mFuncReadIoByte			0x00000010	// ��ȡ��������˿�,��ͬһ���˿ڵ�ַ���ֽ�Ϊ��λ������ȡ,��󳤶�32KB
// #define		mFuncReadIoWord			0x00000011	// ��ȡ��������˿�,��ͬһ���˿ڵ�ַ����Ϊ��λ������ȡ,��󳤶�32KB
// #define		mFuncReadIoDword		0x00000012	// ��ȡ��������˿�,��ͬһ���˿ڵ�ַ��˫��Ϊ��λ������ȡ,��󳤶�32KB
// #define		mFuncReadIoBlock		0x00000013	// ��ȡ��������˿�,ÿ��ȡһ���ֽ�,�˿ڵ�ַ��һ,��󳤶�232B(��ƫ�Ƶ�ַ00H����E7H)
// #define		mFuncReadIo32Block		0x0000001f	// ��ȡ��������˿�,ÿ��ȡһ�����ֽ�,�˿ڵ�ַ��һ/��/��,��󳤶�232B(��ƫ�Ƶ�ַ00H����E7H)
// #define		mFuncWriteIoByte		0x00000014	// д����������˿�,��ͬһ���˿ڵ�ַ���ֽ�Ϊ��λ����д��,��󳤶�32KB
// #define		mFuncWriteIoWord		0x00000015	// д����������˿�,��ͬһ���˿ڵ�ַ����Ϊ��λ����д��,��󳤶�32KB
// #define		mFuncWriteIoDword		0x00000016	// д����������˿�,��ͬһ���˿ڵ�ַ��˫��Ϊ��λ����д��,��󳤶�32KB
// #define		mFuncWriteIoBlock		0x00000017	// д����������˿�,ÿд��һ���ֽ�,�˿ڵ�ַ��һ,��󳤶�232B(��ƫ�Ƶ�ַ00Hд��E7H)
// #define		mFuncWriteIo32Block		0x00000020	// д����������˿�,ÿд��һ�����ֽ�,�˿ڵ�ַ��һ/��/��,��󳤶�232B(��ƫ�Ƶ�ַ00Hд��E7H)
// #define		mFuncReadMemByte		0x00000018	// ��ȡ�洢��/�Ĵ���,���ֽ�Ϊ��λ������,ÿ��ȡһ���ֽ�,��ַ��һ,��󳤶�32KB(��ƫ�Ƶ�ַ0000H����7FFFH)
// #define		mFuncReadMemDword		0x0000001a	// ��ȡ�洢��/�Ĵ���,��˫��Ϊ��λ������,ÿ��ȡһ���ֽ�,��ַ����,��󳤶�32KB(��ƫ�Ƶ�ַ0000H����7FFFH)
// #define		mFuncWriteMemByte		0x0000001c	// д��洢��/�Ĵ���,���ֽ�Ϊ��λ����д,ÿ��ȡһ���ֽ�,��ַ��һ,��󳤶�32KB(��ƫ�Ƶ�ַ0000Hд��7FFFH)
// #define		mFuncWriteMemDword		0x0000001e	// д��洢��/�Ĵ���,��˫��Ϊ��λ����д,ÿ��ȡһ��˫��,��ַ����,��󳤶�32KB(��ƫ�Ƶ�ַ0000Hд��7FFFH)
// ������ʽ��֧��,�����������ļ�CH367DLL.H��


BOOL	WINAPI	CH367mSetExclusive(  // ���ö�ռʹ�õ�ǰCH367�豸
	ULONG			iIndex,  // ָ��CH367�豸���
	ULONG			iExclusive );  // Ϊ0���豸���Թ���ʹ��,��0���ռʹ��

BOOL	WINAPI	CH367SetStream(  // ���ô�����ģʽ
	ULONG			iIndex,      // ָ��CH367�豸���
	ULONG			iMode );     // ָ��ģʽ,������
// λ0:     SPIʱ��Ƶ��,0=31.3MHZ,1=15.6MHZ
// λ1:     SPI��I/O��/IO����, 0=SPI3(SCS/SCL/SDX),1=SPI4(SCS/SCL/SDX/SDI)
// ��������,����Ϊ0

BOOL	WINAPI	CH367StreamSPI(  // ����SPI������,3�߽ӿ�,ʱ����ΪSCL����,�������������ΪSDX,����������������,������Ӵ���FlashROMоƬ25FXX��SDO/SDI����;Ƭѡ��ΪSCS
							     //4�߽ӿ�,��������ΪSDI,�������ΪSDX,ʱ����ΪSCL����,Ƭѡ��ΪSDA����
                                 /* SPIʱ��: SCL����Ϊʱ�����, Ĭ��Ϊ�͵�ƽ, ��ʱ��������֮ǰ�ĵ͵�ƽ�ڼ����, ������ʱ���½���֮ǰ�ĸߵ�ƽ�ڼ����� */
                ULONG			iIndex,  // ָ��CH367�豸���	
                ULONG			iWriteLength,  // д����,׼��д���ĳ���
                PVOID			iWriteBuffer,  // ָ��һ��������,����׼��д��������
                PULONG			oReadLength,   // ָ�򳤶ȵ�Ԫ,���غ�Ϊʵ�ʶ�ȡ�ĳ���
				PVOID			oReadBuffer );  // ָ��һ���㹻��Ļ�����,���ڱ����ȡ������


BOOL	WINAPI	CH364mLockFlash(
		ULONG			iIndex,        // ָ��CH367�豸���
		UCHAR			WRLock);	   // ������ʽ(Ϊ00H����д����,Ϊ8CH������д����/ֻ������,Ϊ0FFH���д����/��ȫ����,ֻ�ڸ�λ����ܽ���)

BOOL	WINAPI	CH364mReadFlash(
		ULONG			iIndex,        // ָ��CH367�豸���
		ULONG			iAddr,         // ָ��FLASH�ĵ�ַ
		PVOID			oBuffer,	   // ָ��һ��������,���ڱ����ȡ���ֽ�����
		ULONG			iLength);       // ��ȡ�����ݳ���
		
BOOL	WINAPI	CH364mEarseFlash(
		ULONG			iIndex,        // ָ��CH367�豸���
		ULONG			iAddr,         // ָ��FLASH�ĵ�ַ
		ULONG			iLength );	   // ָ�������ĳ��ȣ�ÿ4096�ֽڼ�4KΪһ������,��С������λ������

BOOL	WINAPI	CH364mWriteFlash(
		ULONG			iIndex,        // ָ��CH367�豸���
		ULONG			iAddr,         // ָ��I/O�˿ڵĵ�ַ,�õ�ַ����ΪIOƫ�Ƶ�ַ(<=0xE7)�;���IO��ַ
		PVOID			iBuffer,	   // ָ��һ���ֽڵ�Ԫ,���ڱ����ȡ���ֽ�����
		ULONG			iLength);  

#ifdef __cplusplus
}
#endif

#endif		// _CH367_DLL_H