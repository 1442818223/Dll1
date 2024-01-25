#define _CRT_SECURE_NO_WARNINGS
//c���Զ�д�ļ�
#include <stdio.h>
#include <errno.h>

#define BUF_SIZE 256
int main(int argc, char* argv[]) {
	FILE *inFile, *outFile;
	char rec[BUF_SIZE];
	size_t bytesIn, bytesOut;

	if (argc != 3)
	{
		printf("Usage : cpc file1 file2\n");
		return 1;
	}
	                            
	inFile = fopen(argv[1], "rb");//�Զ����ƶ���
	if (inFile == NULL)
	{
		perror(argv[1]);
		return 2;
	}

	outFile = fopen(argv[2],"wb");//�Զ�����д��
	if (outFile == NULL)
	{
		perror(argv[2]);
		return 3;
	}
	

	/*
	fread����ֵ��ʵ�ʶ�ȡ���������������

	size_t fread(void *ptr,//һ��ָ��洢���ݵĻ�������ָ�롣
	size_t size, //Ҫ��ȡ��ÿ��������Ĵ�С�����ֽ�Ϊ��λ��
	size_t nmemb,//Ҫ��ȡ�������������
	FILE *stream);// �ļ�ָ�룬ָ��Ҫ��ȡ���ļ�
	*/
	while ((bytesIn = fread(rec,1, BUF_SIZE, inFile)) > 0) {
		bytesOut = fwrite(rec, 1, bytesIn, outFile);
		if (bytesIn != bytesOut)
		{
			perror("Fat al write error.");
			return 4;
		}
	}

	fclose(inFile);
	fclose(outFile);


}
