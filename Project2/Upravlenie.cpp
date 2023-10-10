#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); // ������� ��������� ��������� ����
// ������� �������������� ������ � �����
int StrToInt(char* s)
{
    int temp = 0; // �����
    int i = 0;
    int sign = 0; // ���� ����� 0- �������������, 1 - �������������
    if (s[i] == '-')
    {
        sign = 1;
        i++;
    }
    while (s[i] >= 0x30 && s[i] <= 0x39)
    {
        temp = temp + (s[i] & 0x0F);
        temp = temp * 10;
        i++;
    }
    temp = temp / 10;
    if (sign == 1)
        temp = -temp;
    return(temp);
}
// ������� �������������� ����� � ������
char* IntToStr(int n)
{
    char s[40], t, * temp;
    int i, k;
    int sign = 0;
    i = 0;
    k = n;
    if (k < 0)
    {
        sign = 1;
        k = -k;
    }
    do {
        t = k % 10;
        k = k / 10;
        s[i] = t | 0x30;
        i++;
    } while (k > 0);
    if (sign == 1)
    {
        s[i] = '-';
        i++;
    }
    temp = new char[i];
    k = 0;
    i--;
    while (i >= 0) {
        temp[k] = s[i];
        i--; k++;
    }
    temp[k] = '\0';
    return(temp);
}
// ��������� �������
int  WINAPI  WinMain(HINSTANCE  hInstance,
    HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    HWND hwnd; // ���������� ����
    MSG msg;   // ��������� ���������
    WNDCLASS w; // ��������� ������ ����
    memset(&w, 0, sizeof(WNDCLASS)); // ������� ������ ��� ���������
    w.style = CS_HREDRAW | CS_VREDRAW;
    w.lpfnWndProc = WndProc;
    w.hInstance = hInstance;
    w.hbrBackground = CreateSolidBrush(0x00FFFFFF);
    w.lpszClassName = "MyClass";
    RegisterClass(&w); // ����������� ������ ����
    // �������� ����
    hwnd = CreateWindow("MyClass", "����� ���� �����",
        WS_OVERLAPPEDWINDOW,
        500, 300, 500, 380,
        NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, nCmdShow); // ����������� ����
    UpdateWindow(hwnd);         // ����������� ����
    // ���� ��������� ���������
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}
// ������� ��������� ���������
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message,
    WPARAM wparam, LPARAM lparam) {
    HDC hdc;
    HINSTANCE hInst;
    PAINTSTRUCT ps;
    static HWND hBtn; // ���������� ������
    static HWND hEdt1, hEdt2, hEdt3; // ����������� ����� ��������������
    static HWND hStat; // ���������� ������������ ������
    TCHAR StrA[20];
    int a, b, c, sum, Len;
    switch (Message) {
    case WM_CREATE: // ��������� �������� ����
        hInst = ((LPCREATESTRUCT)lparam)->hInstance; // ���������� ����������
        // ������� � ���������� ������ ���� ��������������
        hEdt1 = CreateWindow("edit", "0",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 50, 50, 60, 20,
            hwnd, 0, hInst, NULL);
        ShowWindow(hEdt1, SW_SHOWNORMAL);
        // ������� � ���������� ������ ���� ��������������
        hEdt2 = CreateWindow("edit", "0",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 150, 50, 60,
            20, hwnd, 0, hInst, NULL);
        ShowWindow(hEdt2, SW_SHOWNORMAL);
        hEdt3 = CreateWindow("edit", "0",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 250, 50, 60, 20,
            hwnd, 0, hInst, NULL);
        ShowWindow(hEdt3, SW_SHOWNORMAL);
        // ������� � ���������� ������
        hBtn = CreateWindow("button", "����������",
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            50, 100, 120, 30, hwnd, 0, hInst, NULL);
        ShowWindow(hBtn, SW_SHOWNORMAL);
        // ������� � ���������� ���� ������ ��� ����������
        hStat = CreateWindow("static", "0", WS_CHILD | WS_VISIBLE,
            150, 180, 120, 20, hwnd, 0, hInst, NULL);
        ShowWindow(hStat, SW_SHOWNORMAL);
        break;
    case WM_COMMAND:  // ��������� � �������
        if (lparam == (LPARAM)hBtn)    // ���� ������ �� ������
        {
            Len = GetWindowText(hEdt1, StrA, 20);
            a = StrToInt(StrA); // ��������� ����� �� ������� ����
            Len = GetWindowText(hEdt2, StrA, 20);
            b = StrToInt(StrA); // ��������� ����� �� ������� ����
            Len = GetWindowText(hEdt3, StrA, 20);
            c = StrToInt(StrA);
            sum = a + b + c;  // ������� ����� ���� �����
            SetWindowText(hStat, IntToStr(sum)); // ������� ��������� � ����������� ����
        }
        break;
    case WM_PAINT: // ����������� ����
        hdc = BeginPaint(hwnd, &ps); // ������ �����������
        TextOut(hdc, 50, 20, "������� ��� �����", 18); // ����� ��������� ���������
        TextOut(hdc, 50, 180, "���������:", 10);
        EndPaint(hwnd, &ps); // ����� �����������
        break;
    case WM_DESTROY: // �������� ����
        PostQuitMessage(0);
        break;
    default: // ��������� ��������� �� ���������
        return DefWindowProc(hwnd, Message, wparam, lparam);
    }
    return 0;
}