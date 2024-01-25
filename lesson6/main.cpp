#include <Windows.h>

HINSTANCE hinst;//ʵ�����
HWND hwnd;//���ھ��

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int APIENTRY WinMain(HINSTANCE hinstance,//�ǵ�ǰ����ʵ���ľ��
	HINSTANCE hPrevInstance,//ʼ��Ϊ NULL,����֧�ֶ��ʵ����Ӧ�ó���
	LPSTR lpCmdLine,// �������в�����������������л�ȡ��������ʱ���ݵĶ�����Ϣ
	int nCmdshow)//��ͨ�����ڿ��ƴ����������������С�����������ʾ��
{
	//����ʵ�����
	hinst = hinstance;

	//���崰����
	WNDCLASSEX wcx;


/*
typedef struct tagMSG {
  HWND   hwnd;//ָ��������Ϣ�Ĵ��ھ����
  UINT   message;//ָ����Ϣ�����͡�
  WPARAM wParam;//wParam �� lParam: ���ڴ��ݶ������Ϣ��Ϣ�����庬��ȡ������Ϣ���͡�
  LPARAM lParam;//
  DWORD  time;//ָ����Ϣ��������ʱ�䡣
  POINT  pt;//ָ�����ָ�����Ļ���ꡣ
  DWORD  lPrivate;//�����ֶΡ�
} MSG, *PMSG, *LPMSG;
*/
	//��Ϣ
	MSG msg;
	BOOL fGotMessage;

	wcx.cbSize = sizeof(wcx);
	wcx.style = CS_HREDRAW | CS_VREDRAW; //���ڿ�Ⱥ͸߶ȷ����仯�����»�
	wcx.lpfnWndProc = MainWndProc; //**************���ڹ���
	wcx.lpszClassName = "MainWClass";// �����������
	wcx.cbClsExtra = 0;//��ʹ�ö�����ڴ汣����Ϣ
	wcx.cbWndExtra = 0;//��ʹ�ö�����ڴ汣�洰����Ϣ
	wcx.hInstance = hinstance;//������������ʵ�����
	wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION); //����ͼ�� Ĭ��  (��ͼ��)
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW); //�������ָ����״ Ĭ��
	wcx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//ʹ�ð�ɫ�Ļ�ˢ��������
	wcx.lpszMenuName = NULL;//���ڲ˵� û����
	//����(Сͼ��)
	wcx.hIconSm = (HICON)LoadImage(hinstance, // ��Ӧ�ó���ʵ���ľ��������ָ������ͼ����Դ��ģ��
		MAKEINTRESOURCE(5), //����Դ�ı�ʶ��������ʹ�� MAKEINTRESOURCE �꽫���� 5 ת��Ϊ��Դ��ʶ���ַ�����
		IMAGE_ICON,//��ʾ���ص���ͼ�����͵���Դ
		GetSystemMetrics(SM_CXSMICON), //GetSystemMetrics ������ȡ��ϵͳ�����Сͼ��ı�׼��С,����ͼ��Ŀ�Ⱥ͸߶�
		GetSystemMetrics(SM_CYSMICON),
		LR_DEFAULTCOLOR);//ʹ��ͼ���Ĭ����ɫ


	//ע�ᴰ��
	if (!RegisterClassEx(&wcx)) {
		return 1;
	}
	
	//��������
	hwnd = CreateWindow(
			"MainWClass",
			"Hello",//������
			WS_OVERLAPPEDWINDOW, //������ʽ 
		    CW_USEDEFAULT,//λ��
			CW_USEDEFAULT,
			CW_USEDEFAULT,//���
		    CW_USEDEFAULT,//�߶�
			(HWND)NULL,//�޸�����
			(HMENU)NULL,//�˵�
			hinstance,
			(LPVOID)NULL);
		if (!hwnd)
		{
			return 1;
		}

    // ��ʾ����
		ShowWindow(hwnd, nCmdshow);
		UpdateWindow(hwnd);

	//������Ϣ
		/*
		BOOL GetMessage(
        LPMSG lpMsg,  // ָ��MSG�ṹ��ָ�룬���ڴ洢��Ϣ��Ϣ
        HWND hWnd,     // �ȴ���Ϣ�Ĵ��ھ�������ΪNULL�����ȡ�κ��̵߳���Ϣ
        UINT wMsgFilterMin,  // ָ����С����Ϣֵ
         UINT wMsgFilterMax   // ָ��������Ϣֵ
         );
		*/
		while ((fGotMessage = GetMessage(&msg,(HWND)NULL, 0, 0)) != 0) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);   //***��Ϣ�������Ƿ���ϵͳ��***
		}

		return msg.wParam;//msg.wParam �洢������Ϣѭ���������˳���
}


//MainWndProc �Ǵ��ڹ��̺��������ڴ�������Ϣ��
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_LBUTTONDOWN: //���������
		MessageBox(hwnd,"Hello����!","hello", MB_OK); return 0;
	case WM_DESTROY:  //���Ͻǵ��ʱ 
		PostQuitMessage(0);  //���ٴ���
		return 0;
	default: //Ĭ��
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}
