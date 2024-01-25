#include<Windows.h>
#include <stdio.h>

int cmp(const void* a, const void* b) {
	return*(int*)a - *(int *)b;
}


int main()
{
	SYSTEMTIME st;
	GetLocalTime(&st);//��ȡ��ǰʱ��
	printf("Now: %d-%d-%d��%d :%d :%d\n",
		st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	
	// st.wHour--;  //�����õ�ǰʱ����һСʱ
	// SetLocalTime(&st);

	//DWORD c1 = GetTickCount();  //32λ��
	ULONGLONG c2 = GetTickCount64(); //64λ��    ���㿪��ʱ��
	printf("%d\n", c2);   //��λ�Ǻ���


	int nums[100000];
	srand(GetTickCount());  //��ϵͳ�������� ���㿪��ʱ��
	for (int i = 0; i < 100000; i++)
		nums[i] = rand() % 1000;

	int StartTime = GetTickCount();//������ʼ��ʱ
	qsort(nums, 100000, sizeof(nums[0]), cmp);//c�����е�����
	int EndTime = GetTickCount();//�����������ʱ
	printf("��ʱ:%d ms\n",EndTime - StartTime);


	//for (int i = 0; i < 100000; i++)
	//	printf("%d\n", nums[i]);


	system(" pause");
	return 0;
}