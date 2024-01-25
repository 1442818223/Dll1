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
        printf("δ֪���͵���������\n");
        break;
    case DRIVE_NO_ROOT_DIR:
        printf("��·����Ч�����磬�ڸ�·����δ���ؾ�\n");
        break;
    case DRIVE_REMOVABLE:
        printf("�п��ƶ�ý��������������磬������������\n");
        break;
    case DRIVE_FIXED:
        printf("�����Ƴ��������������磬Ӳ����������\n");

        // �洢���������֡����кš����������ȡ��ļ�ϵͳ���͵���Ϣ
        TCHAR szDriveName[MAX_PATH];
        DWORD dwVolumeSerialNumber;
        DWORD dwMaximumComponentLength;
        DWORD dwFileSystemFlags;
        TCHAR szFileSystemNameBuffer[MAX_PATH];

        // ��ȡ�̷�����������Ϣ
        if (GetVolumeInformation(
            szDrive,// �̷�·��
            szDriveName, // ���ڽ��վ��Ļ�����
            MAX_PATH,// ��������С
            &dwVolumeSerialNumber,// ���ڽ��վ�����кŵ�ָ��
            &dwMaximumComponentLength,// ���ڽ��վ����ļ��������������ȵ�ָ��
            &dwFileSystemFlags, // ���ڽ��վ����ļ�ϵͳ�ı�־��ָ��
            szFileSystemNameBuffer,// ���ڽ����ļ�ϵͳ���͵Ļ�����
            MAX_PATH // ��������С
        ))
        {
            printf("\nDrive Name: %s\n", szDriveName);
            printf("Volume Serial Number: %u\n", dwVolumeSerialNumber);
            printf("Maximum Component Length: %u\n", dwMaximumComponentLength);
            printf("File System Type: %s\n", szFileSystemNameBuffer);

            // ����ļ�ϵͳ֧�ֵ�����
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
            return FALSE; // ��ȡ��Ϣʧ��
        }
        break;
    case DRIVE_REMOTE:
        printf("������������\n");
        break;
    case DRIVE_CDROM:
        printf("������������\n");
        break;
    case DRIVE_RAMDISK:
        printf(" RAM ���̡�\n");
        break;
    default:
        break;
    }

    return TRUE; // ��ȡ��Ϣ�ɹ�
}

int main() {
    GetDriveInfo(TEXT("C:\\"));
    printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n");
    GetDriveInfo(TEXT("D:\\"));

    system("pause");
    return 0;
}
