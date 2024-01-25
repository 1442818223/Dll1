//list book�б��
#include <Windows.h>
#include"resource.h"

//hDlg��ʾ��ǰ�Ի���ľ�� uMsg��ʾ��ǰ��Ϣ�������簴ť���������ƶ���
INT_PTR CALLBACK MainDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	/*
	WM_COMMAND �� Windows ����ϵͳ�����ڴ���˵����������ť���û�����Ԫ�ص���Ϣ
	wParam: ��λ�ֽڰ��������Կؼ���֪ͨ���룬��λ�ֽڰ����˿ؼ���ʶ����
	lParam: ������ָ��ؼ��ľ����ָ�룬�����Ϣ���ɼ��ټ����ɵģ���Ϊ NULL��
	*/
	BOOL bRet = TRUE;

	int wmId,wmEvent;
	static HWND hwndList1, hwndList2, hwndList3;

	switch (uMsg) {
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		hwndList1 = GetDlgItem(hDlg, IDC_LIST1);
		hwndList2 = GetDlgItem(hDlg, IDC_LIST2);
		hwndList3 = GetDlgItem(hDlg, IDC_LIST3);

		int iIndex,iLength, iCount,iSelect;
		TCHAR* pVarText;

		switch (wmId) {//��λ�ֽڰ��������Կؼ��Ĵ���
		case IDC_LIST1:
			//if (wmEvent == LBN_SELCHANGE) {//LBN_SELCHANGEΪѡ��IDC_LIST1��ĳһ��
			if (wmEvent == LBN_DBLCLK){// LBN_DBLCLKΪ˫��

			iIndex = SendMessage(hwndList1, LB_GETCURSEL, 0, 0);// ��ȡ��ǰѡ��������� 
				iLength = SendMessage(hwndList1, LB_GETTEXTLEN,iIndex, 0) + 1; // ��ȡѡ�����ı��ĳ���
				pVarText = (TCHAR*)calloc(iLength, sizeof(TCHAR));
				SendMessage(hwndList1, LB_GETTEXT, iIndex, (LPARAM)pVarText);//��ȡѡ������ı���
				MessageBox(hDlg, pVarText, TEXT("TEST"), MB_OK);
			}
			break;
	
		case IDC_BUTTON1:
			                      // LB_ADDSTRING�����ַ���
			SendMessage(hwndList1, LB_ADDSTRING, 0, (LPARAM)TEXT("Hello"));
			SendMessage(hwndList1, LB_ADDSTRING, 0, (LPARAM)TEXT("Hello1"));
			SendMessage(hwndList1, LB_ADDSTRING, 0, (LPARAM)TEXT("Hello2"));
			break;

		case IDC_BUTTON2:          //LB_DELETESTRING,2ɾ���ڶ���
			SendMessage(hwndList1, LB_DELETESTRING, 2, 0);
			break;

		case IDC_BUTTON3:          //LB_RESETCONTENTΪ����
			SendMessage(hwndList1, LB_RESETCONTENT, 0, 0);
			break;

		case IDC_BUTTON4:
			SendMessage(hwndList1, LB_SETCURSEL, 2, 0); // LB_SETCURSEL,2Ϊѡ��IDC_LIST1�ĵ�1��
			break;

		case IDC_BUTTON5:
			SendMessage(hwndList1, LB_SETCURSEL, -1, 0);//û��-1��һ��,����Ϊȡ��ѡ��IDC_LIST1��ѡ����
			break;

		case IDC_BUTTON7:    //�� IDC_LIST1��ѡ���е��ַ������͵�IDC_LIST2��(����ѡ��ĳ��)
			iIndex = SendMessage(hwndList1, LB_GETCURSEL, 0, 0);
			iLength = SendMessage(hwndList1, LB_GETTEXTLEN, iIndex, 0) + 1; 
			pVarText = (TCHAR*)calloc(iLength, sizeof(TCHAR));
			SendMessage(hwndList1, LB_GETTEXT,iIndex, (LPARAM)pVarText); 
			SendMessage(hwndList2, LB_INSERTSTRING, -1,(LPARAM)pVarText);//-1: ��ʾ���б���ĩβ�������ַ���
			SendMessage(hwndList1, LB_DELETESTRING, iIndex, 0);
			break;

		case IDC_BUTTON6: //����
			SendMessage(hwndList2, LB_INSERTSTRING, -1,(LPARAM)TEXT("one"));
			SendMessage(hwndList2, LB_INSERTSTRING, -1,(LPARAM)TEXT("t wo"));
			SendMessage(hwndList2, LB_INSERTSTRING, - 1,(LPARAM)TEXT("three"));
			break;

		case IDC_BUTTON8://�������±�2��λ��
			SendMessage(hwndList2, LB_INSERTSTRING, 2, (LPARAM)TEXT("��"));
			break;

		case IDC_BUTTON9: //ǰ������Դ�༭�������listbox2���������ö�ѡ
			SendMessage(hwndList2, LB_SETSEL, 1, 2); //����listbox2�ĵڶ�,������Ϊѡ��״̬
			SendMessage(hwndList2, LB_SETSEL, 1, 5);
			break;

		case IDC_BUTTON10:
			SendMessage(hwndList2, LB_SETSEL, 0, 2); //����listbox2�ĵڶ�,������Ϊ��ѡ��״̬
			SendMessage(hwndList2, LB_SETSEL, 0, 5);
			break;

		case IDC_BUTTON11:
			SendMessage(hwndList2, LB_SETSEL, 1, -1); //-1Ϊȫ��,1Ϊѡ��
			break;

		case IDC_BUTTON12://��listbox2��ѡ�е�����listbox3����
			// �����б��2��������
			iCount = SendMessage(hwndList2, LB_GETCOUNT, 0, 0);
			// �����ʼ�����б��2����
			for (iIndex = iCount - 1; iIndex >= 0; iIndex--){//�Ӻ���ǰ��������Ϊɾ������±�ǰ������
				// ��鵱ǰ���Ƿ�ѡ��
				iSelect = SendMessage(hwndList2, LB_GETSEL, iIndex, 0);
				if (iSelect != 0) {// ���Ϊ���㣬��ʾ��ǰ�ѡ��
					// ��ȡ��ǰѡ������ı�����
					iLength = SendMessage(hwndList2, LB_GETTEXTLEN, iIndex, 0);
					// �����ڴ棬��ȡ��ǰѡ������ı�
					pVarText = (TCHAR*)calloc(iLength + 1, sizeof(TCHAR));
					SendMessage(hwndList2, LB_GETTEXT, iIndex, (LPARAM)pVarText);
					// ���б��3�в���ѡ������ı�
					SendMessage(hwndList3, LB_INSERTSTRING, -1, (LPARAM)pVarText);
					// ���б��2��ɾ��ѡ����
					SendMessage(hwndList2, LB_DELETESTRING, iIndex, 0);
				}
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