#include<Windows.h>
#include<iostream>

typedef enum _PROCESSINFOCLASS {
	ProcessBasicInformation = 0,
	ProcessQuotaLimits,
	ProcessIoCounters,
	ProcessVmCounters,
	ProcessTimes,
	ProcessBasePriority,
	ProcessRaisePriority,
	ProcessDebugPort,
	ProcessExceptionPort,
	ProcessAccessToken,
	ProcessLdtInformation,
	ProcessLdtSize,
	ProcessDefaultHardErrorMode,
	ProcessIoPortHandlers,           // Note: This is kernel mode only
	ProcessPooledUsageAndLimits,
	ProcessWorkingSetWatch,
	ProcessUserModeIOPL,
	ProcessEnableAlignmentFaultFixup,
	ProcessPriorityClass,
	ProcessWx86Information,
	ProcessHandleCount,
	ProcessAffinityMask,
	ProcessPriorityBoost,
	ProcessDeviceMap,
	ProcessSessionInformation,
	ProcessForegroundInformation,
	ProcessWow64Information,
	ProcessImageFileName,
	ProcessLUIDDeviceMapsEnabled,
	ProcessBreakOnTermination,
	ProcessDebugObjectHandle,
	ProcessDebugFlags,
	ProcessHandleTracing,
	ProcessIoPriority,
	ProcessExecuteFlags,
	ProcessTlsInformation,
	ProcessCookie,
	ProcessImageInformation,
	MaxProcessInfoClass
} PROCESSINFOCLASS;

typedef struct _UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
#ifdef MIDL_PASS
	[size_is(MaximumLength / 2), length_is((Length) / 2)] USHORT* Buffer;
#else
	PWSTR Buffer;
#endif
} UNICODE_STRING;

typedef struct _OBJECT_NAME_INFORMATION {
	UNICODE_STRING Name;
} OBJECT_NAME_INFORMATION, * POBJECT_NAME_INFORMATION;

typedef enum _OBJECT_INFORMATION_CLASS {
	ObjectBasicInformation = 0,
	ObjectNameInformation,
	ObjectTypeInformation,
	ObjectTypesInformation,
	ObjectHandleFlagInformation,
	ObjectSessionInformation,
	ObjectSessionObjectInformation,
	MaxObjectInfoClass
} OBJECT_INFORMATION_CLASS;

typedef NTSTATUS(NTAPI* _NtQueryObject)(
	__in HANDLE Handle,
	__in OBJECT_INFORMATION_CLASS ObjectlnformationClass,
	__out_bcount_opt(ObjectlnformationLength) PVOID ObjectInformation,
	__in ULONG ObjectlnformationLength,
	__out_opt PULONG ReturnLength
	);


typedef NTSTATUS(NTAPI* _NtQueryInformationProcess)(
	__in HANDLE ProcessHandle,
	__in PROCESSINFOCLASS ProcessInformationClass,
	__out_bcount(ProcessInformationLength)PVOID ProcessInformation,
	__in ULONG ProcessInformationLength,
	__out_opt PULONG ReturnLength);

_NtQueryInformationProcess NtQueryInformationProcess;
_NtQueryObject NtQueryObject;

int main()
{

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, 28304);
	if (!hProcess) {
		printf("打开进程失败! \n");
		return 0;
	}

	//获取NtQueryInformationProcess  查询指定进程句柄信息。
	NtQueryInformationProcess = (_NtQueryInformationProcess)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtQueryInformationProcess");
	//获取NtQueryObject  获取某个句柄信息
	NtQueryObject = (_NtQueryObject)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtQueryObject");

	DWORD handleCount = 0;
	DWORD handleData = 4;
	HANDLE cpyHandle = 0;
	POBJECT_NAME_INFORMATION nameIfo = (POBJECT_NAME_INFORMATION)malloc(0x1000);

	NtQueryInformationProcess(hProcess, ProcessHandleCount, &handleCount, sizeof(DWORD), 0);
	//句柄他都是4的整数倍，一个进程的有效句柄，我可以认为是从4开始的。
	for (size_t i = 0; i < handleCount; handleData += 4)
	{

		//判断句柄是否为有效句柄 
		//DuplicateHandle  复制句柄并关闭源句柄，最后关闭复制的句柄
		BOOL dupRet = DuplicateHandle(hProcess, (HANDLE)handleData, GetCurrentProcess(),
			&cpyHandle, 0, FALSE, DUPLICATE_SAME_ACCESS);
		if (dupRet == FALSE)
		{
			continue;
		}
		else {

			// nameInfo  获取句柄对象的名称信息
			NtQueryObject(cpyHandle, ObjectNameInformation, nameIfo, 0X1000, 0);
			if (nameIfo->Name.Length == 0) {
				CloseHandle(cpyHandle);
				
					i++;
				continue;
			} 

			printf("句柄名称:%ls \n", nameIfo->Name.Buffer);

			// 检查对象名称是否为指定的名称
			if ( wcscmp(L"\\Windows\\Theme85352962", nameIfo->Name.Buffer) == 0 )
			{       //关闭目标进程句柄
				DuplicateHandle(hProcess,(HANDLE)handleData,GetCurrentProcess(),
					&cpyHandle, 0,FALSE, DUPLICATE_CLOSE_SOURCE);
				CloseHandle(cpyHandle);           //
				break;
			}                             
			CloseHandle(cpyHandle);
			i++;
		}
	}

	system("pause");
	return 0;
}