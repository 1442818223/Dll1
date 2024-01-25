#include<Windows.h>
#include <stdio.h>

int cmp(const void* a, const void* b) {
	return*(int*)a - *(int *)b;
}


int main()
{
	SYSTEMTIME st;
	GetLocalTime(&st);//获取当前时间
	printf("Now: %d-%d-%d，%d :%d :%d\n",
		st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	
	// st.wHour--;  //设置让当前时钟慢一小时
	// SetLocalTime(&st);

	//DWORD c1 = GetTickCount();  //32位的
	ULONGLONG c2 = GetTickCount64(); //64位的    计算开机时长
	printf("%d\n", c2);   //单位是毫秒


	int nums[100000];
	srand(GetTickCount());  //自系统启动以来 计算开机时长
	for (int i = 0; i < 100000; i++)
		nums[i] = rand() % 1000;

	int StartTime = GetTickCount();//对排序开始计时
	qsort(nums, 100000, sizeof(nums[0]), cmp);//c语言中的排序
	int EndTime = GetTickCount();//对排序结束计时
	printf("用时:%d ms\n",EndTime - StartTime);


	//for (int i = 0; i < 100000; i++)
	//	printf("%d\n", nums[i]);


	system(" pause");
	return 0;
}