#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>

BOOL GetDriveInfo(LPCTSTR szDrive) {
    printf("%s\n", szDrive);

    UINT uDriveType;
    uDriveType = GetDriveType(szDrive);

    switch (uDriveType) {
    case DRIVE_UNKNOWN:
        printf("未知类型的驱动器。\n");
        break;
    case DRIVE_NO_ROOT_DIR:
        printf("根路径无效，例如，在该路径上未挂载卷。\n");
        break;
    case DRIVE_REMOVABLE:
        printf("有可移动媒体的驱动器，例如，软盘驱动器。\n");
        break;
    case DRIVE_FIXED:
        printf("不能移除的驱动器，例如，硬盘驱动器。\n");

        // 存储驱动器名字、序列号、最大组件长度、文件系统类型等信息
        TCHAR szDriveName[MAX_PATH];
        DWORD dwVolumeSerialNumber;
        DWORD dwMaximumComponentLength;
        DWORD dwFileSystemFlags;
        TCHAR szFileSystemNameBuffer[MAX_PATH];

        // 获取盘符的驱动器信息
        if (GetVolumeInformation(
            szDrive,// 盘符路径
            szDriveName, // 用于接收卷标的缓冲区
            MAX_PATH,// 缓冲区大小
            &dwVolumeSerialNumber,// 用于接收卷的序列号的指针
            &dwMaximumComponentLength,// 用于接收卷上文件名的最大组件长度的指针
            &dwFileSystemFlags, // 用于接收卷上文件系统的标志的指针
            szFileSystemNameBuffer,// 用于接收文件系统类型的缓冲区
            MAX_PATH // 缓冲区大小
        ))
        {
            printf("\nDrive Name: %s\n", szDriveName);
            printf("Volume Serial Number: %u\n", dwVolumeSerialNumber);
            printf("Maximum Component Length: %u\n", dwMaximumComponentLength);
            printf("File System Type: %s\n", szFileSystemNameBuffer);

            // 检查文件系统支持的特性
            if (dwFileSystemFlags & FILE_VOLUME_QUOTAS) {
                printf("The file system supports disk quotas.\n");
            }
            if (dwFileSystemFlags & FILE_SUPPORTS_ENCRYPTION) {
                printf("The file system supports encryption.\n");
            }
        }
        else
        {
            DWORD dwError = GetLastError();
            printf("GetVolumeInformation failed with error %lu\n", dwError);
            return FALSE; // 获取信息失败
        }
        break;
    case DRIVE_REMOTE:
        printf("网络驱动器。\n");
        break;
    case DRIVE_CDROM:
        printf("光盘驱动器。\n");
        break;
    case DRIVE_RAMDISK:
        printf(" RAM 磁盘。\n");
        break;
    default:
        break;
    }

    return TRUE; // 获取信息成功
}

int main() {
    GetDriveInfo(TEXT("C:\\"));
    printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n");
    GetDriveInfo(TEXT("D:\\"));

    system("pause");
    return 0;
}
