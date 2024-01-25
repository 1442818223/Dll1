#include <Windows.h>
#include"resource.h"


//hDlg��ʾ��ǰ�Ի���ľ�� uMsg��ʾ��ǰ��Ϣ�������簴ť���������ƶ���
INT_PTR CALLBACK MainDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	BOOL bRet = TRUE;

	static HWND hButton;
	static HWND hCheckBox;
	static HWND hRadioButton;

	static int iCheck;
	static TCHAR pszBuffer[128];

	/*
	WM_COMMAND �� Windows ����ϵͳ�����ڴ���˵����������ť���û�����Ԫ�ص���Ϣ
	wParam: ��λ�ֽڰ��������Կؼ���֪ͨ���룬��λ�ֽڰ����˿ؼ���ʶ����
	lParam: ������ָ��ؼ��ľ����ָ�룬�����Ϣ���ɼ��ټ����ɵģ���Ϊ NULL��
	*/

	switch (uMsg) {


	case WM_COMMAND://���ڴ���˵����������ť���û�����Ԫ�ص���Ϣ
		hButton = GetDlgItem(hDlg, IDC_BUTTON1);//��ȡ�Ի����еĿؼ����
		hCheckBox = GetDlgItem(hDlg, IDC_CHECK1);
		hRadioButton = GetDlgItem(hDlg, IDC_RADIO1);
		switch (LOWORD(wParam))//��λ�ֽڰ��������Կؼ���֪ͨ����
		{
		case IDC_BUTTON1:
			MessageBox(hDlg, TEXT("Hello Button1"), TEXT("Test"), MB_OK);
			break;
		case IDC_BUTTON2:
			/*
			LRESULT SendMessage(
			  HWND   hWnd,//Ŀ�괰�ڻ�ؼ��ľ��
			  UINT   Msg,//Ҫ���͵���Ϣ���͡�
			  WPARAM wParam,
			  LPARAM lParam  //wParam �� lParam�������������ľ��庬��ȡ���������͵���Ϣ���� Msg��
			);
			*/
			//BM_SETCHECK���ø�ѡ��״̬����Ϣ
			//1 �� wParam����ʾ����ѡ��ť����Ϊѡ��״̬��
			//0 �� lParam������û�����⺬�壬��Ϊ BM_SETCHECK ����Ҫ�õ� lParam��
			SendMessage(hCheckBox, BM_SETCHECK, 1, 0);
			SendMessage(hRadioButton, BM_SETCHECK, 1, 0);
			break;

		case IDC_BUTTON3:                     //0Ϊδѡ��״̬
			SendMessage(hCheckBox, BM_SETCHECK, 0, 0);
			SendMessage(hRadioButton, BM_SETCHECK, 0, 0);
			break;

		case IDC_BUTTON4:                     //BM_GETCHECKΪ�õ�״̬
			iCheck = (int)SendMessage(hCheckBox,BM_GETCHECK, 0, 0);
			if (iCheck)
				MessageBox(hDlg, TEXT("CheckBoxѡ����"), TEXT("TEST"), MB_OK);
			else
				MessageBox(hDlg, TEXT("CheckBoxûѡ��"), TEXT("TEST"), MB_OK);

         case IDC_BUTTON5:
			 SetWindowText(hButton, TEXT("Hello")); //���ù�������ť�ϵ�����
			 break;

		 case IDC_BUTTON6:
			 GetWindowText(hButton,pszBuffer, 128); //�õ���������ť�ϵ�����
			 MessageBox(hDlg, pszBuffer, TEXT("TEST"), MB_OK);
			 break;

		 case IDC_BUTTON7:
			 if (IsWindowVisible(hButton))  
				 ShowWindow(hDlg, SW_HIDE); //ShowWindow������ʾ�������ش���,��ؼ�
			 else
				 ShowWindow(hDlg, SW_SHOW);
			 break;

		 case IDC_BUTTON8:
			 //if (IsWindowEnabled(hButton))
				// EnableWindow(hButton, FALSE);// EnableWindow���ÿؼ����û�����
			 //else
				// EnableWindow(hButton, TRUE);

			 IsWindowEnabled(hButton) ? EnableWindow(hButton, FALSE) : EnableWindow(hButton, TRUE);
			 IsWindowEnabled(hCheckBox) ? EnableWindow(hCheckBox, FALSE) : EnableWindow(hCheckBox, TRUE);
			 IsWindowEnabled(hRadioButton) ? EnableWindow(hRadioButton, FALSE) : EnableWindow(hRadioButton, TRUE);
			 break;

		default:
			//���������ؼ���֪ͨ������δ��������������Ĭ�ϵ���Ϣ������
			return DefWindowProc(hDlg, uMsg, wParam, lParam);
		}
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