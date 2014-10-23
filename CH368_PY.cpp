// CH368_PY_LIB.cpp : 定义 DLL 应用程序的导出函数。
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


_declspec (dllexport) HANDLE	__cdecl CH368_OpenDevice(  // 打开CH367设备,返回句柄,出错则无效
	BOOL			iEnableMemory,  // 是否需要支持存储器,CH367芯片不支持,CH368芯片支持
	BOOL			iEnableInterrupt,  // 是否需要支持中断
	UCHAR           iInterruptMode) // 位0:中断输入的极性1:高电平/下降沿;0:低电平/上升沿;位1:中断输入的类型 1:边沿,0:电平
{
	return CH367OpenDevice(iEnableMemory, iEnableInterrupt, iInterruptMode);
}


_declspec (dllexport) VOID	__cdecl	CH368_CloseDevice()  // 关闭CH367设备
{
	CH367CloseDevice();
}


_declspec (dllexport) ULONG	__cdecl	CH368_GetVersion()  // 获得DLL版本号,返回版本号
{
	return CH367GetVersion();
}  


_declspec (dllexport) ULONG	__cdecl	CH368_DriverCommand(  // 直接传递命令给驱动程序,出错则返回0,否则返回数据长度
	mPWIN32_COMMAND ioCommand)  // 命令结构的指针
{
	return CH367DriverCommand(ioCommand);
}
// 该程序在调用后返回数据长度,并且仍然返回命令结构,如果是读操作,则数据返回在命令结构中,
// 返回的数据长度在操作失败时为0,操作成功时为整个命令结构的长度,例如读一个字节,则返回mWIN32_COMMAND_HEAD+1,
// 命令结构在调用前,分别提供:命令功能代码,起始地址(可选),存取数据的长度(可选),
// 命令结构在调用后,分别返回:操作状态代码,返回的基址(可选),后续数据的长度(可选),
// 操作状态代码是由WINDOWS定义的代码,可以参考NTSTATUS.H,
// 返回的基址只适用于下列命令:获取I/O基址,获取存储器基址,获取中断号,对于其它命令则保持输入时的起始地址
// 后续数据的长度是指读操作返回的数据长度,数据存放在随后的缓冲区中,对于写操作一般为0

_declspec (dllexport) ULONG	__cdecl	CH368_GetDrvVersion()  // 获得驱动程序版本号,返回版本号,出错则返回0
{
	return CH367GetDrvVersion();
}


_declspec (dllexport) BOOL	__cdecl	CH368_GetIoBaseAddr(  // 获取I/O端口的基址
	mPCH367_IO_REG	*oIoBaseAddr)  // 保存I/O端口基址的单元地址
{
	return CH367GetIoBaseAddr(oIoBaseAddr);
}


_declspec (dllexport) BOOL	__cdecl	CH368_GetMemBaseAddr(  // 获取存储器的基址
	mPCH368_MEM_REG	*oMemBaseAddr)  // 保存存储器基址的单元地址
{
	return CH368_GetMemBaseAddr(oMemBaseAddr);
}


_declspec (dllexport) BOOL	__cdecl	CH368_SetMemBaseAddr(  // 设定存储器的基址
	mPCH368_MEM_REG	iMemBaseAddr)  // 指定存储器基址,为0则关闭存储器,为-1则自动设定
{
	return CH368SetMemBaseAddr(iMemBaseAddr);
}


_declspec (dllexport) BOOL	__cdecl	CH368_GetIntLine(  // 获取中断号
	PULONG			oIntLine) // 保存中断号的单元地址
{
	return CH367GetIntLine(oIntLine);
}


_declspec (dllexport) BOOL	__cdecl	CH368_SetIntLine(  // 设定中断号
	ULONG			iIntLine,  // 指定中断号,为0则关闭中断,为-1则自动检测并设定
	UCHAR           iInterruptMode) // 位0:中断输入的极性1:高电平下降沿;0:低电平上升沿;位1:中断输入的类 1:边沿,0:中断
{
	return CH367SetIntLine(iIntLine, iInterruptMode);
}



_declspec (dllexport) BOOL	__cdecl	CH368_WaitInterrupt()  // 等待中断事件
{
	return CH367WaitInterrupt();
}


_declspec (dllexport) BOOL	__cdecl	CH368_AbortWaitInt()  // 放弃等待中断
{
	return CH367AbortWaitInt();
}


_declspec (dllexport) BOOL	__cdecl	CH368_SetIntRoutine(  // 设定中断服务程序
	mPCH367_INT_ROUTINE	iIntRoutine)  // 指定中断服务程序,为NULL则取消中断服务,否则在中断时调用该程序
{
	return CH367SetIntRoutine(iIntRoutine);
}


_declspec (dllexport) BOOL	__cdecl	CH368_ReadIntCommand(  // 读取中断命令缓冲区
	mPWIN32_COMMAND	oCommand,  // 指向一个足够大的缓冲区,用于保存读取的命令结构
	ULONG			iCmdIndex)  // 中断命令序号,为1或者2
{
	return CH367ReadIntCommand(oCommand, iCmdIndex);
}


_declspec (dllexport) BOOL	__cdecl	CH368_WriteIntCommand(  // 写入中断命令缓冲区
	mPWIN32_COMMAND	iCommand,  // 指向作为中断命令的命令结构
	ULONG			iCmdIndex)  // 中断命令序号,为1或者2
{
	return CH367WriteIntCommand(iCommand, iCmdIndex);
}


_declspec (dllexport) BOOL	__cdecl	CH368_ReadIoByte(  // 从I/O端口读取一个字节
	PVOID			iAddr,  // 指定I/O端口的地址
	PUCHAR			oByte)  // 指向一个字节单元,用于保存读取的字节数据
{
	return CH367ReadIoByte(iAddr, oByte);
}


_declspec (dllexport) BOOL	__cdecl	CH368_ReadIoWord(  // 从I/O端口读取一个字
	PVOID			iAddr,  // 指定I/O端口的地址
	PUSHORT			oWord)  // 指向一个字单元,用于保存读取的字数据
{
	return CH367ReadIoWord(iAddr, oWord);
}


_declspec (dllexport) BOOL	__cdecl	CH368_ReadIoDword(  // 从I/O端口读取一个双字
	PVOID			iAddr,  // 指定I/O端口的地址
	PULONG			oDword)  // 指向一个双字单元,用于保存读取的双字数据
{
	return CH367ReadIoDword(iAddr, oDword);
}


_declspec (dllexport) BOOL	__cdecl	CH368_WriteIoByte(  // 向I/O端口写入一个字节
	PVOID			iAddr,  // 指定I/O端口的地址
	UCHAR			iByte)  // 待写入的字节数据
{
	return CH367WriteIoByte(iAddr, iByte);
}


_declspec (dllexport) BOOL	__cdecl	CH368_WriteIoWord(  // 向I/O端口写入一个字
	PVOID			iAddr,  // 指定I/O端口的地址
	USHORT			iWord)  // 待写入的字数据
{
	return CH367WriteIoWord(iAddr, iWord);
}


_declspec (dllexport) BOOL	__cdecl	CH368_WriteIoDword(  // 向I/O端口写入一个双字
	PVOID			iAddr,  // 指定I/O端口的地址
	ULONG			iDword)  // 待写入的双字数据
{
	return CH367WriteIoDword(iAddr, iDword);
}


_declspec (dllexport) BOOL	__cdecl	CH368_ReadMemByte(  // 从存储器读取一个字节
	PVOID			iAddr,  // 指定存储器的地址,虚拟地址
	PUCHAR			oByte)  // 指向一个字节单元,用于保存读取的字节数据
{
	return CH368ReadMemByte(iAddr, oByte);
}


_declspec (dllexport) BOOL	__cdecl	CH368_ReadMemDword(  // 从存储器读取一个双字
	PVOID			iAddr,  // 指定存储器的地址,虚拟地址
	PULONG			oDword)  // 指向一个双字单元,用于保存读取的双字数据
{
	return CH368ReadMemDword(iAddr, oDword);
}


_declspec (dllexport) BOOL	__cdecl	CH368_WriteMemByte(  // 向存储器写入一个字节
	PVOID			iAddr,  // 指定存储器的地址,虚拟地址
	UCHAR			iByte)  // 待写入的字节数据
{
	return CH368WriteMemByte(iAddr, iByte);
}


_declspec (dllexport) BOOL	__cdecl	CH368_WriteMemDword(  // 向存储器写入一个双字
	PVOID			iAddr,  // 指定存储器的地址,虚拟地址
	ULONG			iDword)  // 待写入的双字数据
{
	return CH368WriteMemDword(iAddr, iDword);
}


_declspec (dllexport) BOOL	__cdecl	CH368_ReadConfig(  // 从配置空间读取一个字节数据
	PVOID			iOffset,  // 指定偏移地址
	PUCHAR			oByte)  // 指向一个字节单元,用于保存读取的字节数据
{
	return CH367ReadConfig(iOffset, oByte);
}


_declspec (dllexport) BOOL	__cdecl	CH368_WriteConfig(  // 向配置空间写入一个字节数据
	PVOID			iOffset,  // 指定偏移地址
	UCHAR			iByte)  // 待写入的字节数据
{
	return CH367WriteConfig(iOffset, iByte);
}


_declspec (dllexport) BOOL	__cdecl	CH368_SetA15_A8(  // 设置高地址,即设置A15-A8的输出
	UCHAR			iA15_A8)  // 位7-位0对应A15-A8的输出,1为高电平,0为低电平
{
	return CH368SetA15_A8(iA15_A8);
}


_declspec (dllexport) BOOL	__cdecl	CH368_ReadI2C(  // 从I2C接口读取一个字节数据
	UCHAR			iDevice,  // 低7位指定I2C设备地址
	UCHAR			iAddr,  // 指定数据单元的地址
	PUCHAR			oByte)  // 指向一个字节单元,用于保存读取的字节数据
{
	return CH367ReadI2C(iDevice, iAddr, oByte);
}


_declspec (dllexport) BOOL	__cdecl	CH368_WriteI2C(  // 向I2C接口写入一个字节数据
	UCHAR			iDevice,  // 低7位指定I2C设备地址
	UCHAR			iAddr,  // 指定数据单元的地址
	UCHAR			iByte)  // 待写入的字节数据
{
	return CH367WriteI2C(iDevice, iAddr, iByte);
}


_declspec (dllexport) HANDLE	__cdecl	CH368_mOpenDevice(  // 打开CH367设备,返回句柄,出错则无效
	ULONG			iIndex,  // 指定CH367设备序号,0对应第一个设备
	BOOL			iEnableMemory,  // 是否需要支持存储器,CH367芯片不支持,CH368芯片支持
	BOOL			iEnableInterrupt,  // 是否需要支持中断
	UCHAR           iInterruptMode) // 位0:中断输入的极性1:高电平/下降沿;0:低电平/上升沿;位1:中断输入的类型 1:边沿,0:电平
{
	return CH367mOpenDevice(iIndex, iEnableMemory, iEnableInterrupt, iInterruptMode);
}

_declspec (dllexport) VOID	__cdecl	CH368_mCloseDevice(  // 关闭CH367设备
	ULONG			iIndex)  // 指定CH367设备序号
{
	return CH367mCloseDevice(iIndex);
}


_declspec (dllexport) ULONG	__cdecl	CH368_mDriverCommand(  // 直接传递命令给驱动程序,出错则返回0,否则返回数据长度
	ULONG			iIndex,  // 指定CH367设备序号
	mPWIN32_COMMAND	ioCommand)  // 命令结构的指针
{
	return CH367mDriverCommand(iIndex, ioCommand);
}
// 该程序在调用后返回数据长度,并且仍然返回命令结构,如果是读操作,则数据返回在命令结构中,
// 返回的数据长度在操作失败时为0,操作成功时为整个命令结构的长度,例如读一个字节,则返回mWIN32_COMMAND_HEAD+1,
// 命令结构在调用前,分别提供:命令功能代码,起始地址(可选),存取数据的长度(可选),
// 命令结构在调用后,分别返回:操作状态代码,返回的基址(可选),后续数据的长度(可选),
//   操作状态代码是由WINDOWS定义的代码,可以参考NTSTATUS.H,
//
//   返回的基址只适用于下列命令:获取I/O基址,获取存储器基址,获取中断号,对于其它命令则保持输入时的起始地址
//   后续数据的长度是指读操作返回的数据长度,数据存放在随后的缓冲区中,对于写操作一般为0


_declspec (dllexport) BOOL	__cdecl	CH368_mGetIoBaseAddr(  // 获取I/O端口的基址
	ULONG			iIndex,  // 指定CH367设备序号
	mPCH367_IO_REG	*oIoBaseAddr)  // 保存I/O端口基址的单元地址
{
	return CH367mGetIoBaseAddr(iIndex, oIoBaseAddr);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mSetIoBaseAddr(  // 设定I/O端口的基址
	ULONG			iIndex,  // 指定CH367设备序号
	mPCH367_IO_REG	iIoBaseAddr)  // 指定I/O端口基址
{
	return CH367mSetIoBaseAddr(iIndex, iIoBaseAddr);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mGetMemBaseAddr(  // 获取存储器的基址
	ULONG			iIndex,  // 指定CH367设备序号
	mPCH368_MEM_REG	*oMemBaseAddr)  // 保存存储器基址的单元地址
{
	return CH368mGetMemBaseAddr(iIndex, oMemBaseAddr);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mSetMemBaseAddr(  // 设定存储器的基址
	ULONG			iIndex,  // 指定CH367设备序号
	mPCH368_MEM_REG	iMemBaseAddr)  // 指定存储器基址,为0则关闭存储器,为-1则自动设定
{
	return CH368mSetMemBaseAddr(iIndex, iMemBaseAddr);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mGetIntLine(  // 获取中断号
	ULONG			iIndex,  // 指定CH367设备序号
	PULONG			oIntLine)  // 保存中断号的单元地址
{
	return CH367mGetIntLine(iIndex, oIntLine);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mSetIntLine(  // 设定中断号
	ULONG			iIndex,  // 指定CH367设备序号
	ULONG			iIntLine, // 指定中断号,为0则关闭中断,为-1则自动检测并设定
	UCHAR           iInterruptMode) // 位0:中断输入的极性1:高电平下降沿;0:低电平上升沿;位1:中断输入的类 1:边沿,0:中断
{
	return CH367mSetIntLine(iIndex, iIntLine, iInterruptMode);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mWaitInterrupt(  // 等待中断事件
	ULONG			iIndex)  // 指定CH367设备序号
{
	return CH367mWaitInterrupt(iIndex);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mAbortWaitInt(  // 放弃等待中断
	ULONG			iIndex)  // 指定CH367设备序号
{
	return CH367mAbortWaitInt(iIndex);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mSetIntRoutine(  // 设定中断服务程序
	ULONG			iIndex,  // 指定CH367设备序号
	mPCH367_INT_ROUTINE	iIntRoutine)  // 指定中断服务程序,为NULL则取消中断服务,否则在中断时调用该程序
{
	return CH367mSetIntRoutine(iIndex, iIntRoutine);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mReadIntCommand(  // 读取中断命令缓冲区
	ULONG			iIndex,  // 指定CH367设备序号
	mPWIN32_COMMAND	oCommand,  // 指向一个足够大的缓冲区,用于保存读取的命令结构
	ULONG			iCmdIndex)  // 中断命令序号,为1或者2
{
	return CH367mReadIntCommand(iIndex, oCommand, iCmdIndex);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mWriteIntCommand(  // 写入中断命令缓冲区
	ULONG			iIndex,  // 指定CH367设备序号
	mPWIN32_COMMAND	iCommand,  // 指向作为中断命令的命令结构
	ULONG			iCmdIndex)  // 中断命令序号,为1或者2
{
	return CH367mWriteIntCommand(iIndex, iCommand, iCmdIndex);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mReadIoByte(  // 从I/O端口读取一个字节
	ULONG			iIndex,  // 指定CH367设备序号
	PVOID			iAddr,  // 指定I/O端口的地址
	PUCHAR			oByte)  // 指向一个字节单元,用于保存读取的字节数据
{
	return CH367mReadIoByte(iIndex, iAddr, oByte);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mReadIoWord(  // 从I/O端口读取一个字
	ULONG			iIndex,  // 指定CH367设备序号
	PVOID			iAddr,  // 指定I/O端口的地址
	PUSHORT			oWord)  // 指向一个字单元,用于保存读取的字数据
{
	return CH367mReadIoWord(iIndex, iAddr, oWord);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mReadIoDword(  // 从I/O端口读取一个双字
	ULONG			iIndex,  // 指定CH367设备序号
	PVOID			iAddr,  // 指定I/O端口的地址
	PULONG			oDword)  // 指向一个双字单元,用于保存读取的双字数据
{
	return CH367mReadIoDword(iIndex, iAddr, oDword);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mWriteIoByte(  // 向I/O端口写入一个字节
	ULONG			iIndex,  // 指定CH367设备序号
	PVOID			iAddr,  // 指定I/O端口的地址
	UCHAR			iByte)  // 待写入的字节数据
{
	return CH367mWriteIoByte(iIndex, iAddr, iByte);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mWriteIoWord(  // 向I/O端口写入一个字
	ULONG			iIndex,  // 指定CH367设备序号
	PVOID			iAddr,  // 指定I/O端口的地址
	USHORT			iWord)  // 待写入的字数据
{
	return CH367mWriteIoWord(iIndex, iAddr, iWord);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mWriteIoDword(  // 向I/O端口写入一个双字
	ULONG			iIndex,  // 指定CH367设备序号
	PVOID			iAddr,  // 指定I/O端口的地址
	ULONG			iDword)  // 待写入的双字数据
{
	return CH367mWriteIoDword(iIndex, iAddr, iDword);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mReadMemByte(  // 从存储器读取一个字节
	ULONG			iIndex,  // 指定CH367设备序号
	PVOID			iAddr,  // 指定存储器的地址,虚拟地址
	PUCHAR			oByte)  // 指向一个字节单元,用于保存读取的字节数据
{
	return CH368mReadMemByte(iIndex, iAddr, oByte);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mReadMemDword(  // 从存储器读取一个双字
	ULONG			iIndex,  // 指定CH367设备序号
	PVOID			iAddr,  // 指定存储器的地址,虚拟地址
	PULONG			oDword)  // 指向一个双字单元,用于保存读取的双字数据
{
	return CH368mReadMemDword(iIndex, iAddr, oDword);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mWriteMemByte(  // 向存储器写入一个字节
	ULONG			iIndex,  // 指定CH367设备序号
	PVOID			iAddr,  // 指定存储器的地址,虚拟地址
	UCHAR			iByte)  // 待写入的字节数据
{
	return CH368mWriteMemByte(iIndex, iAddr, iByte);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mWriteMemDword(  // 向存储器写入一个双字
	ULONG			iIndex,  // 指定CH367设备序号
	PVOID			iAddr,  // 指定存储器的地址,虚拟地址
	ULONG			iDword)  // 待写入的双字数据
{
	return CH368mWriteMemDword(iIndex, iAddr, iDword);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mReadConfig(  // 从配置空间读取一个字节数据
	ULONG			iIndex,  // 指定CH367设备序号
	PVOID			iOffset,  // 指定偏移地址
	PUCHAR			oByte)  // 指向一个字节单元,用于保存读取的字节数据
{
	return CH367mReadConfig(iIndex, iOffset, oByte);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mWriteConfig(  // 向配置空间写入一个字节数据
	ULONG			iIndex,  // 指定CH367设备序号
	PVOID			iOffset,  // 指定偏移地址
	UCHAR			iByte)  // 待写入的字节数据
{
	return CH367mWriteConfig(iIndex, iOffset, iByte);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mSetA15_A8(  // 设置高地址,即设置A15-A8的输出
	ULONG			iIndex,  // 指定CH367设备序号
	UCHAR			iA15_A8)  // 位7-位0对应A15-A8的输出,1为高电平,0为低电平
{
	return CH368mSetA15_A8(iIndex, iA15_A8);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mReadI2C(  // 从I2C接口读取一个字节数据
	ULONG			iIndex,  // 指定CH367设备序号
	UCHAR			iDevice,  // 低7位指定I2C设备地址
	UCHAR			iAddr,  // 指定数据单元的地址
	PUCHAR			oByte)  // 指向一个字节单元,用于保存读取的字节数据
{
	return CH367mReadI2C(iIndex, iDevice, iAddr, oByte);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mWriteI2C(  // 向I2C接口写入一个字节数据
	ULONG			iIndex,  // 指定CH367设备序号
	UCHAR			iDevice,  // 低7位指定I2C设备地址
	UCHAR			iAddr,  // 指定数据单元的地址
	UCHAR			iByte)  // 待写入的字节数据
{
	return CH367mWriteI2C(iIndex, iDevice, iAddr, iByte);
}


_declspec (dllexport) BOOL	__cdecl	CH368_DelayUS(  // 延时指定微秒
	ULONG			iDelay)  // 指定要延时的微秒数,如果延时小于10则误差较大
{
	return CH367DelayUS(iDelay);
}


_declspec (dllexport) BOOL	__cdecl	CH368_mAccessBlock(  // 读取或者写入数据块
	ULONG			iIndex,  // 指定CH367设备序号
	ULONG			iAccessMode,  // 参考下面的说明
	PVOID			iAddr,  // 指定I/O端口或者存储器的地址
	PVOID			ioBuffer,  // 指向输入或者输出的缓冲区
	ULONG			iLength)  // 数据块长度,也就是读取或者写入的字节数,长度不超过32KB
{
	return CH367mAccessBlock(iIndex, iAccessMode, iAddr, ioBuffer, iLength);
}

// iAccessMode 定义如下
// #define		mFuncReadIoByte			0x00000010	// 读取输入输出端口,在同一个端口地址以字节为单位连续读取,最大长度32KB
// #define		mFuncReadIoWord			0x00000011	// 读取输入输出端口,在同一个端口地址以字为单位连续读取,最大长度32KB
// #define		mFuncReadIoDword		0x00000012	// 读取输入输出端口,在同一个端口地址以双字为单位连续读取,最大长度32KB
// #define		mFuncReadIoBlock		0x00000013	// 读取输入输出端口,每读取一个字节,端口地址加一,最大长度232B(从偏移地址00H读到E7H)
// #define		mFuncReadIo32Block		0x0000001f	// 读取输入输出端口,每读取一个四字节,端口地址加一/二/四,最大长度232B(从偏移地址00H读到E7H)
// #define		mFuncWriteIoByte		0x00000014	// 写入输入输出端口,在同一个端口地址以字节为单位连续写入,最大长度32KB
// #define		mFuncWriteIoWord		0x00000015	// 写入输入输出端口,在同一个端口地址以字为单位连续写入,最大长度32KB
// #define		mFuncWriteIoDword		0x00000016	// 写入输入输出端口,在同一个端口地址以双字为单位连续写入,最大长度32KB
// #define		mFuncWriteIoBlock		0x00000017	// 写入输入输出端口,每写入一个字节,端口地址加一,最大长度232B(从偏移地址00H写到E7H)
// #define		mFuncWriteIo32Block		0x00000020	// 写入输入输出端口,每写入一个四字节,端口地址加一/二/四,最大长度232B(从偏移地址00H写到E7H)
// #define		mFuncReadMemByte		0x00000018	// 读取存储器/寄存器,以字节为单位连续读,每读取一个字节,地址加一,最大长度32KB(从偏移地址0000H读到7FFFH)
// #define		mFuncReadMemDword		0x0000001a	// 读取存储器/寄存器,以双字为单位连续读,每读取一个字节,地址加四,最大长度32KB(从偏移地址0000H读到7FFFH)
// #define		mFuncWriteMemByte		0x0000001c	// 写入存储器/寄存器,以字节为单位连续写,每读取一个字节,地址加一,最大长度32KB(从偏移地址0000H写到7FFFH)
// #define		mFuncWriteMemDword		0x0000001e	// 写入存储器/寄存器,以双字为单位连续写,每读取一个双字,地址加四,最大长度32KB(从偏移地址0000H写到7FFFH)
// 其它方式不支持,上述定义在文件CH367DLL.H中


_declspec (dllexport) BOOL	__cdecl	CH368_mSetExclusive(  // 设置独占使用当前CH367设备
	ULONG			iIndex,  // 指定CH367设备序号
	ULONG			iExclusive)  // 为0则设备可以共享使用,非0则独占使用
{
	return CH367mSetExclusive(iIndex, iExclusive);
}

_declspec (dllexport) BOOL	__cdecl	CH368_SetStream(  // 设置串口流模式
	ULONG			iIndex,      // 指定CH367设备序号
	ULONG			iMode)     // 指定模式,见下行
{
	return CH367SetStream(iIndex, iMode);
}
// 位0:     SPI时钟频率,0=31.3MHZ,1=15.6MHZ
// 位1:     SPI的I/O数/IO引脚, 0=SPI3(SCS/SCL/SDX),1=SPI4(SCS/SCL/SDX/SDI)
// 其它保留,必须为0

_declspec (dllexport) BOOL	__cdecl	CH368_StreamSPI(  // 处理SPI数据流,3线接口,时钟线为SCL引脚,输出及输入引脚为SDX,内置上拉电阻引脚,可以外接串行FlashROM芯片25FXX的SDO/SDI引脚;片选线为SCS
	//4线接口,输入引脚为SDI,输出引脚为SDX,时钟线为SCL引脚,片选线为SDA引脚
	/* SPI时序: SCL引脚为时钟输出, 默认为低电平, 在时钟上升沿之前的低电平期间输出, 引脚在时钟下降沿之前的高电平期间输入 */
	ULONG			iIndex,  // 指定CH367设备序号	
	ULONG			iWriteLength,  // 写长度,准备写出的长度
	PVOID			iWriteBuffer,  // 指向一个缓冲区,放置准备写出的数据
	PULONG			oReadLength,   // 指向长度单元,返回后为实际读取的长度
	PVOID			oReadBuffer)  // 指向一个足够大的缓冲区,用于保存读取的数据
{
	return CH367StreamSPI(iIndex, iWriteLength, iWriteBuffer, oReadLength, oReadBuffer);
}

_declspec (dllexport) BOOL	__cdecl	CH368_mLockFlash(
	ULONG			iIndex,        // 指定CH367设备序号
	UCHAR			WRLock)	   // 锁定方式(为00H则解除写保护,为8CH则允许写保护/只读锁定,为0FFH则读写保护/完全锁定,只在复位后才能解锁)
{
	return CH364mLockFlash(iIndex, WRLock);
}

_declspec (dllexport) BOOL	__cdecl	CH368_mReadFlash(
	ULONG			iIndex,        // 指定CH367设备序号
	ULONG			iAddr,         // 指定FLASH的地址
	PVOID			oBuffer,	   // 指向一个缓冲区,用于保存读取的字节数据
	ULONG			iLength)       // 读取的数据长度
{
	return CH364mReadFlash(iIndex, iAddr, oBuffer, iLength);
}

_declspec (dllexport) BOOL	__cdecl	CH368_mEarseFlash(
	ULONG			iIndex,        // 指定CH367设备序号
	ULONG			iAddr,         // 指定FLASH的地址
	ULONG			iLength)	   // 指定擦除的长度，每4096字节即4K为一个扇区,最小擦除单位是扇区
{
	return CH364mEarseFlash(iIndex, iAddr, iLength);
}

_declspec (dllexport) BOOL	__cdecl	CH368_mWriteFlash(
	ULONG			iIndex,        // 指定CH367设备序号
	ULONG			iAddr,         // 指定I/O端口的地址,该地址可以为IO偏移地址(<=0xE7)和绝对IO地址
	PVOID			iBuffer,	   // 指向一个字节单元,用于保存读取的字节数据
	ULONG			iLength)
{
	return CH364mWriteFlash(iIndex, iAddr, iBuffer, iLength);
}

#ifdef __cplusplus
}
#endif


