#include <Windows.h>
#include"resource.h"

//hDlg��ʾ��ǰ�Ի���ľ�� uMsg��ʾ��ǰ��Ϣ�������簴ť���������ƶ���
INT_PTR CALLBACK MainDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	BOOL bRet = TRUE;

	static HWND hwndEdit1,hwndEdit2;
	static TCHAR pszBuffer[1024];

/*
WM_COMMAND �� Windows ����ϵͳ�����ڴ���˵����������ť���û�����Ԫ�ص���Ϣ
wParam: ��λ�ֽڰ��������Կؼ���֪ͨ���룬��λ�ֽڰ����˿ؼ���ʶ����
lParam: ������ָ��ؼ��ľ����ָ�룬�����Ϣ���ɼ��ټ����ɵģ���Ϊ NULL��
*/
	switch (uMsg) {

	case WM_COMMAND:
		hwndEdit1 = GetDlgItem(hDlg, IDC_EDIT1);
		hwndEdit2 = GetDlgItem(hDlg, IDC_EDIT2);

		switch (LOWORD(wParam)) {//��λ�ֽڰ��������Կؼ��Ĵ���

		case IDC_EDIT1:
			switch (HIWORD(wParam)) {
			case EN_MAXTEXT:
				break;
			case EN_ERRSPACE:
				break;
			case EN_UPDATE: //ˢ�±༭��1
				GetWindowText(hwndEdit1, pszBuffer, 1024); //�͵��༭��1���ı�
				SetWindowText(hwndEdit2, pszBuffer); //���ı����õ��༭��2
				break;
			}
			break;

		case IDC_BUTTON2:
			switch (HIWORD(wParam)) {
				case BN_CLICKED :
					SendMessage(hwndEdit1, WM_COPY, 0, 0); //�ѱ༭��1ѡ�еĸ��Ƶ�ճ����
					break;
			}
			break;

		case IDC_BUTTON3:
			SendMessage(hwndEdit2, WM_PASTE, 0, 0);//��ճ�����ϵ����ݸ��Ƶ��༭��2
			break;

		case IDC_BUTTON4:
			GetWindowText(hwndEdit1, pszBuffer, 1024);   //�ӱ༭��1�еõ��ַ��Ž�pszBuffer����
			MessageBox(hDlg, pszBuffer, TEXT("TEST"), MB_OK);
			break;

		case IDC_BUTTON5:
			SetWindowText(hwndEdit2,TEXT("this is set window text"));//���ı�д��༭��2
			break;

		case IDC_BUTTON1:
			switch ((HIWORD(wParam))) {//��λ�ֽڰ����˿ؼ���Ϣ��ʶ�� 
				                     //������Ҫ�Կؼ�����Ϣ�������ж�,��һ�㶼�ǶԿؼ����,���Կ���ʡ�ԶԸ�λ��ѡ��
			case BN_CLICKED: //����¼�
				SendMessage(hwndEdit1,WM_CLEAR, 0, 0);//��ѡ�е��ı����
				break;
			case BN_SETFOCUS:
				break;
			}
			break;
			 
		default:
			//���������ؼ���֪ͨ������δ��������������Ĭ�ϵ���Ϣ������
			return DefWindowProc(hDlg, uMsg, wParam, lParam);
			break;
		}
		break;

	case WM_CLOSE:
		EndDialog(hDlg, 0);
		break;

	default:
		bRet = FALSE;//ϵͳ�ص�������Ҫ����ʣ��û�������Ϣ
		break;
	}

	return bRet; //Ĭ�Ϸ�����,������,��Ϊ�Ѿ���Ĭ���д�����

}

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInStance,
	LPSTR lpCmdLine,
	int nCmdShow)//ָ��Ӧ�ó��򴰿ڵ���ʾ״̬
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, MainDlgProc);

	return 0;
}