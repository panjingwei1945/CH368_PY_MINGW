// CH368_PY_LIB.cpp : ���� DLL Ӧ�ó���ĵ���������
//


#include "CH367DLL.H"
#include "windows.h" //must add this manually.
// #include "SDKDDKVer.h"

#ifdef __cplusplus
extern "C" {
#endif




// BOOL APIENTRY DllMain (HINSTANCE hInst     /* Library instance handle. */ ,
//                        DWORD reason        /* Reason this function is being called. */ ,
//                        LPVOID reserved     /* Not used. */ )
// {
//     switch (reason)
//     {
//       case DLL_PROCESS_ATTACH:
//         break;

//       case DLL_PROCESS_DETACH:
//         break;

//       case DLL_THREAD_ATTACH:
//         break;

//       case DLL_THREAD_DETACH:
//         break;
//     }

//     /* Returns TRUE on success, FALSE on failure */
//     return TRUE;
// }


_declspec (dllexport) HANDLE	__cdecl CH368_OpenDevice(  // ��CH367�豸,���ؾ��,��������Ч
	BOOL			iEnableMemory,  // �Ƿ���Ҫ֧�ִ洢��,CH367оƬ��֧��,CH368оƬ֧��
	BOOL			iEnableInterrupt,  // �Ƿ���Ҫ֧���ж�
	UCHAR           iInterruptMode) // λ0:�ж�����ļ���1:�ߵ�ƽ/�½���;0:�͵�ƽ/������;λ1:�ж���������� 1:����,0:��ƽ
{
	return CH367OpenDevice(iEnableMemory, iEnableInterrupt, iInterruptMode);
}


_declspec (dllexport) VOID	__cdecl	CH368_CloseDevice()  // �ر�CH367�豸
{
	CH367CloseDevice();
}


_declspec (dllexport) ULONG	__cdecl	CH368_GetVersion()  // ���DLL�汾��,���ذ汾��
{
	return CH367GetVersion();
}  


_declspec (dllexport) ULONG	__cdecl	CH368_DriverCommand(  // ֱ�Ӵ����������������,�����򷵻�0,���򷵻����ݳ���
	mPWIN32_COMMAND ioCommand)  // ����ṹ��ָ��
{
	return CH367DriverCommand(ioCommand);
}
// �ó����ڵ��ú󷵻����ݳ���,������Ȼ��������ṹ,����Ƕ�����,�����ݷ���������ṹ��,
// ���ص����ݳ����ڲ���ʧ��ʱΪ0,�����ɹ�ʱΪ��������ṹ�ĳ���,�����һ���ֽ�,�򷵻�mWIN32_COMMAND_HEAD+1,
// ����ṹ�ڵ���ǰ,�ֱ��ṩ:����ܴ���,��ʼ��ַ(��ѡ),��ȡ���ݵĳ���(��ѡ),
// ����ṹ�ڵ��ú�,�ֱ𷵻�:����״̬����,���صĻ�ַ(��ѡ),�������ݵĳ���(��ѡ),
// ����״̬��������WINDOWS����Ĵ���,���Բο�NTSTATUS.H,
// ���صĻ�ַֻ��������������:��ȡI/O��ַ,��ȡ�洢����ַ,��ȡ�жϺ�,�������������򱣳�����ʱ����ʼ��ַ
// �������ݵĳ�����ָ���������ص����ݳ���,���ݴ�������Ļ�������,����д����һ��Ϊ0

_declspec (dllexport) ULONG	__cdecl	CH368_GetDrvVersion()  // �����������汾��,���ذ汾��,�����򷵻�0
{
	return CH367GetDrvVersion();
}


_declspec (dllexport) BOOL	__cdecl	CH368_GetIoBaseAddr(  // ��ȡI/O�˿ڵĻ�ַ
	mPCH367_IO_REG	*oIoBaseAddr)  // ����I/O�˿ڻ�ַ�ĵ�Ԫ��ַ
{
	return CH367GetIoBaseAddr(oIoBaseAddr);
}


_declspec (dllexport) BOOL	__cdecl	CH368_GetMemBaseAddr(  // ��ȡ�洢���Ļ�ַ
	mPCH368_MEM_REG	*oMemBaseAddr)  // ����洢����ַ�ĵ�Ԫ��ַ
{
	return CH368_GetMemBaseAddr(oMemBaseAddr);
}


_declspec (dllexport) BOOL	__cdecl	CH368_SetMemBaseAddr(  // �趨�洢���Ļ�ַ
	mPCH368_MEM_REG	iMemBaseAddr)  // ָ���洢����ַ,Ϊ0��رմ洢��,Ϊ-1���Զ��趨
{
	return CH368SetMemBaseAddr(iMemBaseAddr);
}


_declspec (dllexport) BOOL	__cdecl	CH368_GetIntLine(  // ��ȡ�жϺ�
	PULONG			oIntLine) // �����жϺŵĵ�Ԫ��ַ
{
	return CH367GetIntLine(oIntLine);
}


_declspec (dllexport) BOOL	__cdecl	CH368_SetIntLine(  // �趨�жϺ�
	ULONG			iIntLine,  // ָ���жϺ�,Ϊ0��ر��ж�,Ϊ-1���Զ���Ⲣ�趨
	UCHAR           iInterruptMode) // λ0:�ж�����ļ���1:�ߵ�ƽ�½���;0:�͵�ƽ������;λ1:�ж�������� 1:����,0:�ж�
{
	return CH367SetIntLine(iIntLine, iInterruptMode);
}



_declspec (dllexport) BOOL	__cdecl	CH368_WaitInterrupt()  // �ȴ��ж��¼�
{
	return CH367WaitInterrupt();
}


_declspec (dllexport) BOOL	__cdecl	CH368_AbortWaitInt()  // �����ȴ��ж�
{
	return CH367AbortWaitInt();
}


_declspec (dllexport) BOOL	__cdecl	CH368_SetIntRoutine(  // �趨�жϷ������
	mPCH367_INT_ROUTINE	iIntRoutine)  // ָ���жϷ������,ΪNULL��ȡ���жϷ���,�������ж�ʱ���øó���
{
	return CH367SetIntRoutine(iIntRoutine);
}


_declspec (dllexport) BOOL	__cdecl	CH368_ReadIntCommand(  // ��ȡ�ж��������
	mPWIN32_COMMAND	oCommand,  // ָ��һ���㹻��Ļ�����,���ڱ����ȡ������ṹ
	ULONG			iCmdIndex)  // �ж��������,Ϊ1����2
{
	return CH367ReadIntCommand(oCommand, iCmdIndex);
}


_declspec (dllexport) BOOL	__cdecl	CH368_WriteIntCommand(  // д���ж��������
	mPWIN32_COMMAND	iCommand,  // ָ����Ϊ�ж����������ṹ
	ULONG			iCmdIndex)  // �ж��������,Ϊ1����2
{
	return CH367WriteIntCommand(iCommand, iCmdIndex);
}


_declspec (dllexport) BOOL	__cdecl	CH368_ReadIoByte(  // ��I/O�˿ڶ�ȡһ���ֽ�
	PVOID			iAddr,  // ָ��I/O�˿ڵĵ�ַ
	PUCHAR			oByte)  // ָ��һ���ֽڵ�Ԫ,���ڱ����ȡ���ֽ�����
{
	return CH367ReadIoByte(iAddr, oByte);
}


_declspec (dllexport) BOOL	__cdecl	CH368_ReadIoWord(  // ��I/O�˿ڶ�ȡһ����
	PVOID			iAddr,  // ָ��I/O�˿ڵĵ�ַ
	PUSHORT			oWord)  // ָ��һ���ֵ�Ԫ,���ڱ����ȡ��������
{
	return CH367ReadIoWord(iAddr, oWord);
}


_declspec (dllexport) BOOL	__cdecl	CH368_ReadIoDword(  // ��I/O�˿ڶ�ȡһ��˫��
	PVOID			iAddr,  // ָ��I/O�˿ڵĵ�ַ
	PULONG			oDword)  // ָ��һ��˫�ֵ�Ԫ,���ڱ����ȡ��˫������
{
	return CH367ReadIoDword(iAddr, oDword);
}


_declspec (dllexport) BOOL	__cdecl	CH368_WriteIoByte(  // ��I/O�˿�д��һ���ֽ�
	PVOID			iAddr,  // ָ��I/O�˿ڵĵ�ַ
	UCHAR			iByte)  // ��д����ֽ�����
{
	return CH367WriteIoByte(iAddr, iByte);
}


_declspec (dllexport) BOOL	__cdecl	CH368_WriteIoWord(  // ��I/O�˿�д��һ����
	PVOID			iAddr,  // ָ��I/O�˿ڵĵ�ַ
	USHORT			iWord)  // ��д���������
{
	return CH367WriteIoWord(iAddr, iWord);
}


_declspec (dllexport) BOOL	__cdecl	CH368_WriteIoDword(  // ��I/O�˿�д��һ��˫��
	PVOID			iAddr,  // ָ��I/O�˿ڵĵ�ַ
	ULONG			iDword)  // ��д���˫������
{
	return CH367WriteIoDword(iAddr, iDword);
}


_declspec (dllexport) BOOL	__cdecl	CH368_ReadMemByte(  // �Ӵ洢����ȡһ���ֽ�
	PVOID			iAddr,  // ָ���洢���ĵ�ַ,�����ַ
	PUCHAR			oByte)  // ָ��һ���ֽڵ�Ԫ,���ڱ����ȡ���ֽ�����
{
	return CH368ReadMemByte(iAddr, oByte);
}


_declspec (dllexport) BOOL	__cdecl	CH368_ReadMemDword(  // �Ӵ洢����ȡһ��˫��
	PVOID			iAddr,  // ָ���洢���ĵ�ַ,�����ַ
	PULONG			oDword)  // ָ��һ��˫�ֵ�Ԫ,���ڱ����ȡ��˫������
{
	return CH368ReadMemDword(iAddr, oDword);
}


_declspec (dllexport) BOOL	__cdecl	CH368_WriteMemByte(  // ��洢��д��һ���ֽ�
	PVOID			iAddr,  // ָ���洢���ĵ�ַ,�����ַ
	UCHAR			iByte)  // ��д����ֽ�����
{
	return CH368WriteMemByte(iAddr, iByte);
}


_declspec (dllexport) BOOL	__cdecl	CH368_WriteMemDword(  // ��洢��д��һ��˫��
	PVOID			iAddr,  // ָ���洢���ĵ�ַ,�����ַ
	ULONG			iDword)  // ��д���˫������
{
	return CH368WriteMemDword(iAddr, iDword);
}


_declspec (dllexport) BOOL	__cdecl	CH368_ReadConfig(  // �����ÿռ��ȡһ���ֽ�����
	PVOID			iOffset,  // ָ��ƫ�Ƶ�ַ
	PUCHAR			oByte)  // ָ��һ���ֽڵ�Ԫ,���ڱ����ȡ���ֽ�����
{
	return CH367ReadConfig(iOffset, oByte);
}


_declspec (dllexport) BOOL	__cdecl	CH368_WriteConfig(  // �����ÿռ�д��һ���ֽ�����
	PVOID			iOffset,  // ָ��ƫ�Ƶ�ַ
	UCHAR			iByte)  // ��д����ֽ�����
{
	return CH367WriteConfig(iOffset, iByte);
}


_declspec (dllexport) BOOL	__cdecl	CH368_SetA15_A8(  // ���øߵ�ַ,������A15-A8�����
	UCHAR			iA15_A8)  // λ7-λ0��ӦA15-A8�����,1Ϊ�ߵ�ƽ,0Ϊ�͵�ƽ
{
	return CH368SetA15_A8(iA15_A8);
}


_declspec (dllexport) BOOL	__cdecl	CH368_ReadI2C(  // ��I2C�ӿڶ�ȡһ���ֽ�����
	UCHAR			iDevice,  // ��7λָ��I2C�豸��ַ
	UCHAR			iAddr,  // ָ�����ݵ�Ԫ�ĵ�ַ
	PUCHAR			oByte)  // ָ��һ���ֽڵ�Ԫ,���ڱ����ȡ���ֽ�����
{
	return CH367ReadI2C(iDevice, iAddr, oByte);
}


_declspec (dllexport) BOOL	__cdecl	CH368_WriteI2C(  // ��I2C�ӿ�д��һ���ֽ�����
	UCHAR			iDevice,  // ��7λָ��I2C�豸��ַ
	UCHAR			iAddr,  // ָ�����ݵ�Ԫ�ĵ�ַ
	UCHAR			iByte)  // ��д����ֽ�����
{
	return CH367WriteI2C(iDevice, iAddr, iByte);
}


_declspec (dllexport) HANDLE	__cdecl	CH368_mOpenDevice(  // ��CH367�豸,���ؾ��,��������Ч
	ULONG			iIndex,  // ָ��CH367�豸���,0��Ӧ��һ���豸
	BOOL			iEnableMemory,  // �Ƿ���Ҫ֧�ִ洢��,CH367оƬ��֧��,CH368оƬ֧��
	BOOL			iEnableInterrupt,  // �Ƿ���Ҫ֧���ж�
	UCHAR           iInterruptMode) // λ0:�ж�����ļ���1:�ߵ�ƽ/�½���;0:�͵�ƽ/������;λ1:�ж���������� 1:����,0:��ƽ
{
	return CH367mOpenDevice(iIndex, iEnableMemory, iEnableInterrupt, iInterruptMode);
}

_declspec (dllexport) VOID	__cdecl	CH368_mCloseDevice(  // �ر�CH367�豸
	ULONG			iIndex)  // ָ��CH367�豸���
{
	return CH367mCloseDevice(iIndex);
}


_declspec (dllexport) ULONG	__cdecl	CH368_mDriverCommand(  // ֱ�Ӵ����������������,�����򷵻�0,���򷵻����ݳ���
	ULONG			iIndex,  // ָ��CH367�豸���
	mPWIN32_COMMAND	ioCommand)  // ����ṹ��ָ��
{
	return CH367mDriverCommand(iIndex, ioCommand);
}
// �ó����ڵ��ú󷵻����ݳ���,������Ȼ��������ṹ,����Ƕ�����,�����ݷ���������ṹ��,
// ���ص����ݳ����ڲ���ʧ��ʱΪ0,�����ɹ�ʱΪ��������ṹ�ĳ���,�����һ���ֽ�,�򷵻�mWIN32_COMMAND_HEAD+1,
// ����ṹ�ڵ���ǰ,�ֱ��ṩ:����ܴ���,��ʼ��ַ(��ѡ),��ȡ���ݵĳ���(��ѡ),
// ����ṹ�ڵ��ú�,�ֱ𷵻�:����״̬����,���صĻ�ַ(��ѡ),�������ݵĳ���(��ѡ),
//   ����״̬��������WINDOWS����Ĵ���,���Բο�NTSTATUS.H,
//
//   ���صĻ�ַֻ��������������:��ȡI/O��ַ,��ȡ�洢����ַ,��ȡ�жϺ�,�������������򱣳�����ʱ����ʼ��ַ
//   �������ݵĳ�����ָ���������ص����ݳ���,���ݴ�������Ļ�������,����д����һ��Ϊ0


_declspec (dllexport) BOOL	__cdecl	CH368_mGetIoBaseAddr(  // ��ȡI/O�˿ڵĻ�ַ
	ULONG			iIndex,  // ָ��CH367�豸���
	mPCH367_IO_REG	*oIoBaseAddr)  // ����I/O�˿ڻ�ַ�ĵ�Ԫ��ַ
{
	return CH367mGetIoBaseAddr(iIndex, oIoBaseAddr);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mSetIoBaseAddr(  // �趨I/O�˿ڵĻ�ַ
	ULONG			iIndex,  // ָ��CH367�豸���
	mPCH367_IO_REG	iIoBaseAddr)  // ָ��I/O�˿ڻ�ַ
{
	return CH367mSetIoBaseAddr(iIndex, iIoBaseAddr);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mGetMemBaseAddr(  // ��ȡ�洢���Ļ�ַ
	ULONG			iIndex,  // ָ��CH367�豸���
	mPCH368_MEM_REG	*oMemBaseAddr)  // ����洢����ַ�ĵ�Ԫ��ַ
{
	return CH368mGetMemBaseAddr(iIndex, oMemBaseAddr);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mSetMemBaseAddr(  // �趨�洢���Ļ�ַ
	ULONG			iIndex,  // ָ��CH367�豸���
	mPCH368_MEM_REG	iMemBaseAddr)  // ָ���洢����ַ,Ϊ0��رմ洢��,Ϊ-1���Զ��趨
{
	return CH368mSetMemBaseAddr(iIndex, iMemBaseAddr);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mGetIntLine(  // ��ȡ�жϺ�
	ULONG			iIndex,  // ָ��CH367�豸���
	PULONG			oIntLine)  // �����жϺŵĵ�Ԫ��ַ
{
	return CH367mGetIntLine(iIndex, oIntLine);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mSetIntLine(  // �趨�жϺ�
	ULONG			iIndex,  // ָ��CH367�豸���
	ULONG			iIntLine, // ָ���жϺ�,Ϊ0��ر��ж�,Ϊ-1���Զ���Ⲣ�趨
	UCHAR           iInterruptMode) // λ0:�ж�����ļ���1:�ߵ�ƽ�½���;0:�͵�ƽ������;λ1:�ж�������� 1:����,0:�ж�
{
	return CH367mSetIntLine(iIndex, iIntLine, iInterruptMode);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mWaitInterrupt(  // �ȴ��ж��¼�
	ULONG			iIndex)  // ָ��CH367�豸���
{
	return CH367mWaitInterrupt(iIndex);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mAbortWaitInt(  // �����ȴ��ж�
	ULONG			iIndex)  // ָ��CH367�豸���
{
	return CH367mAbortWaitInt(iIndex);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mSetIntRoutine(  // �趨�жϷ������
	ULONG			iIndex,  // ָ��CH367�豸���
	mPCH367_INT_ROUTINE	iIntRoutine)  // ָ���жϷ������,ΪNULL��ȡ���жϷ���,�������ж�ʱ���øó���
{
	return CH367mSetIntRoutine(iIndex, iIntRoutine);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mReadIntCommand(  // ��ȡ�ж��������
	ULONG			iIndex,  // ָ��CH367�豸���
	mPWIN32_COMMAND	oCommand,  // ָ��һ���㹻��Ļ�����,���ڱ����ȡ������ṹ
	ULONG			iCmdIndex)  // �ж��������,Ϊ1����2
{
	return CH367mReadIntCommand(iIndex, oCommand, iCmdIndex);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mWriteIntCommand(  // д���ж��������
	ULONG			iIndex,  // ָ��CH367�豸���
	mPWIN32_COMMAND	iCommand,  // ָ����Ϊ�ж����������ṹ
	ULONG			iCmdIndex)  // �ж��������,Ϊ1����2
{
	return CH367mWriteIntCommand(iIndex, iCommand, iCmdIndex);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mReadIoByte(  // ��I/O�˿ڶ�ȡһ���ֽ�
	ULONG			iIndex,  // ָ��CH367�豸���
	PVOID			iAddr,  // ָ��I/O�˿ڵĵ�ַ
	PUCHAR			oByte)  // ָ��һ���ֽڵ�Ԫ,���ڱ����ȡ���ֽ�����
{
	return CH367mReadIoByte(iIndex, iAddr, oByte);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mReadIoWord(  // ��I/O�˿ڶ�ȡһ����
	ULONG			iIndex,  // ָ��CH367�豸���
	PVOID			iAddr,  // ָ��I/O�˿ڵĵ�ַ
	PUSHORT			oWord)  // ָ��һ���ֵ�Ԫ,���ڱ����ȡ��������
{
	return CH367mReadIoWord(iIndex, iAddr, oWord);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mReadIoDword(  // ��I/O�˿ڶ�ȡһ��˫��
	ULONG			iIndex,  // ָ��CH367�豸���
	PVOID			iAddr,  // ָ��I/O�˿ڵĵ�ַ
	PULONG			oDword)  // ָ��һ��˫�ֵ�Ԫ,���ڱ����ȡ��˫������
{
	return CH367mReadIoDword(iIndex, iAddr, oDword);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mWriteIoByte(  // ��I/O�˿�д��һ���ֽ�
	ULONG			iIndex,  // ָ��CH367�豸���
	PVOID			iAddr,  // ָ��I/O�˿ڵĵ�ַ
	UCHAR			iByte)  // ��д����ֽ�����
{
	return CH367mWriteIoByte(iIndex, iAddr, iByte);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mWriteIoWord(  // ��I/O�˿�д��һ����
	ULONG			iIndex,  // ָ��CH367�豸���
	PVOID			iAddr,  // ָ��I/O�˿ڵĵ�ַ
	USHORT			iWord)  // ��д���������
{
	return CH367mWriteIoWord(iIndex, iAddr, iWord);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mWriteIoDword(  // ��I/O�˿�д��һ��˫��
	ULONG			iIndex,  // ָ��CH367�豸���
	PVOID			iAddr,  // ָ��I/O�˿ڵĵ�ַ
	ULONG			iDword)  // ��д���˫������
{
	return CH367mWriteIoDword(iIndex, iAddr, iDword);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mReadMemByte(  // �Ӵ洢����ȡһ���ֽ�
	ULONG			iIndex,  // ָ��CH367�豸���
	PVOID			iAddr,  // ָ���洢���ĵ�ַ,�����ַ
	PUCHAR			oByte)  // ָ��һ���ֽڵ�Ԫ,���ڱ����ȡ���ֽ�����
{
	return CH368mReadMemByte(iIndex, iAddr, oByte);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mReadMemDword(  // �Ӵ洢����ȡһ��˫��
	ULONG			iIndex,  // ָ��CH367�豸���
	PVOID			iAddr,  // ָ���洢���ĵ�ַ,�����ַ
	PULONG			oDword)  // ָ��һ��˫�ֵ�Ԫ,���ڱ����ȡ��˫������
{
	return CH368mReadMemDword(iIndex, iAddr, oDword);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mWriteMemByte(  // ��洢��д��һ���ֽ�
	ULONG			iIndex,  // ָ��CH367�豸���
	PVOID			iAddr,  // ָ���洢���ĵ�ַ,�����ַ
	UCHAR			iByte)  // ��д����ֽ�����
{
	return CH368mWriteMemByte(iIndex, iAddr, iByte);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mWriteMemDword(  // ��洢��д��һ��˫��
	ULONG			iIndex,  // ָ��CH367�豸���
	PVOID			iAddr,  // ָ���洢���ĵ�ַ,�����ַ
	ULONG			iDword)  // ��д���˫������
{
	return CH368mWriteMemDword(iIndex, iAddr, iDword);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mReadConfig(  // �����ÿռ��ȡһ���ֽ�����
	ULONG			iIndex,  // ָ��CH367�豸���
	PVOID			iOffset,  // ָ��ƫ�Ƶ�ַ
	PUCHAR			oByte)  // ָ��һ���ֽڵ�Ԫ,���ڱ����ȡ���ֽ�����
{
	return CH367mReadConfig(iIndex, iOffset, oByte);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mWriteConfig(  // �����ÿռ�д��һ���ֽ�����
	ULONG			iIndex,  // ָ��CH367�豸���
	PVOID			iOffset,  // ָ��ƫ�Ƶ�ַ
	UCHAR			iByte)  // ��д����ֽ�����
{
	return CH367mWriteConfig(iIndex, iOffset, iByte);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mSetA15_A8(  // ���øߵ�ַ,������A15-A8�����
	ULONG			iIndex,  // ָ��CH367�豸���
	UCHAR			iA15_A8)  // λ7-λ0��ӦA15-A8�����,1Ϊ�ߵ�ƽ,0Ϊ�͵�ƽ
{
	return CH368mSetA15_A8(iIndex, iA15_A8);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mReadI2C(  // ��I2C�ӿڶ�ȡһ���ֽ�����
	ULONG			iIndex,  // ָ��CH367�豸���
	UCHAR			iDevice,  // ��7λָ��I2C�豸��ַ
	UCHAR			iAddr,  // ָ�����ݵ�Ԫ�ĵ�ַ
	PUCHAR			oByte)  // ָ��һ���ֽڵ�Ԫ,���ڱ����ȡ���ֽ�����
{
	return CH367mReadI2C(iIndex, iDevice, iAddr, oByte);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mWriteI2C(  // ��I2C�ӿ�д��һ���ֽ�����
	ULONG			iIndex,  // ָ��CH367�豸���
	UCHAR			iDevice,  // ��7λָ��I2C�豸��ַ
	UCHAR			iAddr,  // ָ�����ݵ�Ԫ�ĵ�ַ
	UCHAR			iByte)  // ��д����ֽ�����
{
	return CH367mWriteI2C(iIndex, iDevice, iAddr, iByte);
}


_declspec (dllexport) BOOL	__cdecl	CH368_DelayUS(  // ��ʱָ��΢��
	ULONG			iDelay)  // ָ��Ҫ��ʱ��΢����,�����ʱС��10�����ϴ�
{
	return CH367DelayUS(iDelay);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mAccessBlock(  // ��ȡ����д�����ݿ�
	ULONG			iIndex,  // ָ��CH367�豸���
	ULONG			iAccessMode,  // �ο������˵��
	PVOID			iAddr,  // ָ��I/O�˿ڻ��ߴ洢���ĵ�ַ
	PVOID			ioBuffer,  // ָ�������������Ļ�����
	ULONG			iLength)  // ���ݿ鳤��,Ҳ���Ƕ�ȡ����д����ֽ���,���Ȳ�����32KB
{
	return CH367mAccessBlock(iIndex, iAccessMode, iAddr, ioBuffer, iLength);
}

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


_declspec (dllexport) BOOL	__cdecl	CH368_mSetExclusive(  // ���ö�ռʹ�õ�ǰCH367�豸
	ULONG			iIndex,  // ָ��CH367�豸���
	ULONG			iExclusive)  // Ϊ0���豸���Թ���ʹ��,��0���ռʹ��
{
	return CH367mSetExclusive(iIndex, iExclusive);
}

_declspec (dllexport) BOOL	__cdecl	CH368_SetStream(  // ���ô�����ģʽ
	ULONG			iIndex,      // ָ��CH367�豸���
	ULONG			iMode)     // ָ��ģʽ,������
{
	return CH367SetStream(iIndex, iMode);
}
// λ0:     SPIʱ��Ƶ��,0=31.3MHZ,1=15.6MHZ
// λ1:     SPI��I/O��/IO����, 0=SPI3(SCS/SCL/SDX),1=SPI4(SCS/SCL/SDX/SDI)
// ��������,����Ϊ0

_declspec (dllexport) BOOL	__cdecl	CH368_StreamSPI(  // ����SPI������,3�߽ӿ�,ʱ����ΪSCL����,�������������ΪSDX,����������������,������Ӵ���FlashROMоƬ25FXX��SDO/SDI����;Ƭѡ��ΪSCS
	//4�߽ӿ�,��������ΪSDI,�������ΪSDX,ʱ����ΪSCL����,Ƭѡ��ΪSDA����
	/* SPIʱ��: SCL����Ϊʱ�����, Ĭ��Ϊ�͵�ƽ, ��ʱ��������֮ǰ�ĵ͵�ƽ�ڼ����, ������ʱ���½���֮ǰ�ĸߵ�ƽ�ڼ����� */
	ULONG			iIndex,  // ָ��CH367�豸���	
	ULONG			iWriteLength,  // д����,׼��д���ĳ���
	PVOID			iWriteBuffer,  // ָ��һ��������,����׼��д��������
	PULONG			oReadLength,   // ָ�򳤶ȵ�Ԫ,���غ�Ϊʵ�ʶ�ȡ�ĳ���
	PVOID			oReadBuffer)  // ָ��һ���㹻��Ļ�����,���ڱ����ȡ������
{
	return CH367StreamSPI(iIndex, iWriteLength, iWriteBuffer, oReadLength, oReadBuffer);
}

_declspec (dllexport) BOOL	__cdecl	CH368_mLockFlash(
	ULONG			iIndex,        // ָ��CH367�豸���
	UCHAR			WRLock)	   // ������ʽ(Ϊ00H����д����,Ϊ8CH������д����/ֻ������,Ϊ0FFH���д����/��ȫ����,ֻ�ڸ�λ����ܽ���)
{
	return CH364mLockFlash(iIndex, WRLock);
}

_declspec (dllexport) BOOL	__cdecl	CH368_mReadFlash(
	ULONG			iIndex,        // ָ��CH367�豸���
	ULONG			iAddr,         // ָ��FLASH�ĵ�ַ
	PVOID			oBuffer,	   // ָ��һ��������,���ڱ����ȡ���ֽ�����
	ULONG			iLength)       // ��ȡ�����ݳ���
{
	return CH364mReadFlash(iIndex, iAddr, oBuffer, iLength);
}

_declspec (dllexport) BOOL	__cdecl	CH368_mEarseFlash(
	ULONG			iIndex,        // ָ��CH367�豸���
	ULONG			iAddr,         // ָ��FLASH�ĵ�ַ
	ULONG			iLength)	   // ָ�������ĳ��ȣ�ÿ4096�ֽڼ�4KΪһ������,��С������λ������
{
	return CH364mEarseFlash(iIndex, iAddr, iLength);
}

_declspec (dllexport) BOOL	__cdecl	CH368_mWriteFlash(
	ULONG			iIndex,        // ָ��CH367�豸���
	ULONG			iAddr,         // ָ��I/O�˿ڵĵ�ַ,�õ�ַ����ΪIOƫ�Ƶ�ַ(<=0xE7)�;���IO��ַ
	PVOID			iBuffer,	   // ָ��һ���ֽڵ�Ԫ,���ڱ����ȡ���ֽ�����
	ULONG			iLength)
{
	return CH364mWriteFlash(iIndex, iAddr, iBuffer, iLength);
}

#ifdef __cplusplus
}
#endif


