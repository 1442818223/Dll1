#include <Windows.h>
#include"resource.h"

/*
ע��:���Radio������Group�к�,ֻ��Ҫ���׸�Radio�ķ�����������ΪTRUE  ���ɷ�Ϊһ��
*/


void PaintTheBlock(HWND hwnd,int iFigure, COLORREF drawColor) {
/*	
HDC �� Windows ��������ڱ�ʾ�豸�����ģ�Device Context���ľ�����͡�
��ͨ�����ڻ�ͼ�����������ڴ��ڻ�ͼ�α����ϻ���ͼ�Ρ��ı��ȡ�
*/
	HDC hdc;
	HBRUSH hBrush;
	
	RECT rect; //RECT �� Windows API �е�һ���ṹ�壬���ڱ�ʾ���ε�����
	GetClientRect(hwnd, &rect);//GetClientRect ��һ�� Windows API ���������ڻ�ȡָ�����ڿͻ����ľ������ꡣ

	InvalidateRect(hwnd, NULL, TRUE); //������ǰ�Ŀؼ�����ʧЧ��ˢ�²Ż��ػ�
	UpdateWindow(hwnd); 


	// ��ȡ���ڵĻ�ͼ������
	hdc = GetDC(hwnd);

	// ����һ��ʵ�Ļ�ˢ����������ɫΪ drawColor
	hBrush = CreateSolidBrush(drawColor);

	// ����ˢѡ���ͼ�����ģ���������ǰ�Ļ�ˢ���
	hBrush = (HBRUSH)SelectObject(hdc, hBrush);


	if(iFigure== IDC_RADIO10)
	//Ellipse �����ڴ��� hwnd �Ŀͻ�������һ����Բ����Բ��λ�úʹ�С�ɿͻ����ľ������궨�壩
	Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom); 
	else
    //Rectangle������
	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);


	// ɾ���´����Ļ�ˢ�����ָ���ǰ�Ļ�ˢ
	DeleteObject(SelectObject(hdc, hBrush));

	// �ͷŻ�ͼ������
	ReleaseDC(hwnd, hdc);
}


//hDlg��ʾ��ǰ�Ի���ľ�� uMsg��ʾ��ǰ��Ϣ�������簴ť���������ƶ���
INT_PTR CALLBACK MainDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	/*
	WM_COMMAND �� Windows ����ϵͳ�����ڴ���˵����������ť���û�����Ԫ�ص���Ϣ
	wParam: ��λ�ֽڰ��������Կؼ���֪ͨ���룬��λ�ֽڰ����˿ؼ���ʶ����
	lParam: ������ָ��ؼ��ľ����ָ�룬�����Ϣ���ɼ��ټ����ɵģ���Ϊ NULL��
	*/
	BOOL bRet = TRUE;

	static HWND hCtrlBlock;
	static int iFigure;
	static COLORREF drawColor;

	switch (uMsg) {

	case WM_INITDIALOG: //��ʼ���Ի�����Ϣʱ�͵õ���̬�ı�����
		hCtrlBlock = GetDlgItem(hDlg,IDC_STATIC3);
		iFigure = IDC_RADIO9;  //�տ�ʼĬ��Ϊ������
		drawColor = RGB(0, 0, 0); //��ɫĬ������Ϊ��ɫ
		//SendMessage(GetDlgItem(hDlg, IDC_RADIO1), BM_SETCHECK, 1, 0); ���ú�ɫ�ͷ���Ϊѡ��״̬
		//SendMessage(GetDlgItem(hDlg, IDC_RADIO9), BM_SETCHECK, 1, 0);
		SendDlgItemMessage(hDlg, IDC_RADIO1, BM_SETCHECK, 1, 0); //����д�൱�����������API�ϳ�
		SendDlgItemMessage(hDlg, IDC_RADIO9, BM_SETCHECK, 1, 0);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {//��λ�ֽڰ��������Կؼ��Ĵ���

		case IDC_RADIO1:
			drawColor = RGB(0, 0, 0);
			break;

		case IDC_RADIO2:
			drawColor = RGB(0, 0, 255);
			break;

		case IDC_RADIO3:
			drawColor = RGB(0, 255,0);
			break;

		case IDC_RADIO4:
			drawColor = RGB(0, 255, 255);
			break;

		case IDC_RADIO5:
			drawColor = RGB(255,0,0);
			break;

		case IDC_RADIO6:
			drawColor = RGB(255 , 0, 255);
			break;

		case IDC_RADIO7:
			drawColor = RGB(255,255,0);
			break;

		case IDC_RADIO8:
			drawColor = RGB(255, 255, 255);
			break;


		case IDC_RADIO9:
			iFigure = IDC_RADIO9;
			break;

		case IDC_RADIO10:
			iFigure = IDC_RADIO10;
			break;
			
		default:
			//���������ؼ���֪ͨ������δ��������������Ĭ�ϵ���Ϣ������
			return DefWindowProc(hDlg, uMsg, wParam, lParam);
			break;
		}
		PaintTheBlock(hCtrlBlock, iFigure, drawColor);
		break;

	case WM_PAINT: //���øտ�ʼ���л��õ�ͼ��
		PaintTheBlock(hCtrlBlock, iFigure, drawColor);
		bRet = FALSE;
		//������˵��bRet = FALSE; ��һ�д������ڸ���ϵͳ�������Ѿ������� WM_PAINT ��Ϣ��
		// ����Ҫϵͳ���������Ĭ�ϴ���ֱ�ӷ��ؼ��ɡ���
		break;

	case WM_CLOSE:
		EndDialog(hDlg, 0);
		break;

	default:
		bRet = FALSE;
		break;
	}

	return bRet; //Ĭ�Ϸ�����

}

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInStance,
	LPSTR lpCmdLine,
	int nCmdShow)//ָ��Ӧ�ó��򴰿ڵ���ʾ״̬
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, MainDlgProc);

	return 0;
}