#include<Windows.h>
#include<iostream>
typedef BOOL(*InstallHook)();
typedef BOOL(*unInstallHook)(); 
int main()
{
	HMODULE hmodule = LoadLibraryA("MFCDLL.dll");
	//InstallHook myInstallHook = (InstallHook)GetProcAddress(hmodule, "InstallHook");
	//unInstallHook myunInstallHook = (unInstallHook)GetProcAddress(hmodule, "unInstallHook");
	//if(myInstallHook())
	//{
	//	printf("HOOK�ɹ�! \n");
		
	//}
	MessageBoxW(0, L"321312",L"321312", MB_OK);

	system("pause");
	
	//myunInstallHook();


	//printf("��ж��\n");

	return 0;

}