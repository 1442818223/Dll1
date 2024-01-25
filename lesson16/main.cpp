#define _CRT_SECURE_NO_WARNINGS
//c语言读写文件
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
	                            
	inFile = fopen(argv[1], "rb");//以二进制读打开
	if (inFile == NULL)
	{
		perror(argv[1]);
		return 2;
	}

	outFile = fopen(argv[2],"wb");//以二进制写打开
	if (outFile == NULL)
	{
		perror(argv[2]);
		return 3;
	}
	

	/*
	fread返回值是实际读取的数据项的数量。

	size_t fread(void *ptr,//一个指向存储数据的缓冲区的指针。
	size_t size, //要读取的每个数据项的大小（以字节为单位）
	size_t nmemb,//要读取的数据项的数量
	FILE *stream);// 文件指针，指向要读取的文件
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
