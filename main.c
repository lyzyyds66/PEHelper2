#include <windows.h>
#include <commdlg.h>

// ���ڹ��̺�������
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// �˴����尴ťID
#define ID_POWEROFF_BUTTON 0
#define ID_CMD_BUTTON 1
#define ID_REGEDIT_BUTTON 2
#define ID_REBOOT_BUTTON 3
#define ID_DISKPART_BUTTON 4
#define ID_FM_BUTTON 5

// ����ȫ�ֱ���
HFONT hFont;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    // ���� DPI ��֪
    SetProcessDPIAware();

    // ע�ᴰ����
    WNDCLASS wc = { 0 };
    wc.lpszClassName = L"PEHelperClass";  // ʹ�ÿ��ַ�������
    wc.hInstance = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_BTNFACE);
    wc.lpfnWndProc = WindowProc;
    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, L"Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);  // ʹ�ÿ��ַ�������
        return 0;
    }

    // ��������
    HWND hwnd = CreateWindowEx(
        0,                              // ��չ������ʽ
        L"PEHelperClass",               // ��������
        L"Windows Preinstallation Environment Helper",                    // ���ڱ���
        WS_OVERLAPPEDWINDOW & ~(WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_THICKFRAME), // ������ʽ����ֹ��С������ֹ��󻯣���ֹϵͳ�˵��������رհ�ť������ֹ�������ڴ�С
        CW_USEDEFAULT, CW_USEDEFAULT,  // ���ڳ�ʼλ��
        550, 500,                      // ���ڴ�С
        NULL,                          // �����ھ��
        NULL,                          // �˵����
        hInstance,                     // ��ǰʵ�����
        NULL);                         // ��������

    if (hwnd == NULL)
    {
        MessageBox(NULL, L"�����ڴ���ʧ��!", L"Error!", MB_ICONEXCLAMATION | MB_OK);  // ʹ�ÿ��ַ�������
        return 0;
    }

    // ��������
    hFont = CreateFont(
        -MulDiv(5, GetDeviceCaps(GetDC(hwnd), LOGPIXELSY), 72),
        0, 0, 0,
        FW_NORMAL, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS,
        CLEARTYPE_QUALITY, VARIABLE_PITCH,
        TEXT("Microsoft YaHei"));

    // ����������ʾ����ť
    HWND hCmdButton = CreateWindow(
        L"BUTTON",                     // Ԥ�����ࣻʹ�ð�ť��
        L"������ʾ��",                 // ��ť�ϵ�����
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // ��ʽ
        100,                           // λ��x
        100,                           // λ��y
        100,                           // ��ť���
        30,                            // ��ť�߶�
        hwnd,                          // ������
        (HMENU)ID_CMD_BUTTON,          // ��ťID
        hInstance,                     // ʵ�����
        NULL);                         // ��ʹ��
    SendMessage(hCmdButton, WM_SETFONT, (WPARAM)hFont, TRUE);

    // ����ע���༭����ť
    HWND hRegeditButton = CreateWindow(
        L"BUTTON",                     // Ԥ�����ࣻʹ�ð�ť��
        L"ע���༭��",               // ��ť�ϵ�����
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // ��ʽ
        300,                           // λ��x
        100,                           // λ��y
        100,                           // ��ť���
        30,                            // ��ť�߶�
        hwnd,                          // ������
        (HMENU)ID_REGEDIT_BUTTON,      // ��ťID
        hInstance,                     // ʵ�����
        NULL);                         // ��ʹ��
    SendMessage(hRegeditButton, WM_SETFONT, (WPARAM)hFont, TRUE);

    //�����ػ���ť��PE���
    HWND hPowerOffButton = CreateWindow(
        L"BUTTON",                     // Ԥ�����ࣻʹ�ð�ť��
        L"�ػ�",               // ��ť�ϵ�����
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // ��ʽ
        50,                           // λ��x
        400,                           // λ��y
        100,                           // ��ť���
        30,                            // ��ť�߶�
        hwnd,                          // ������
        (HMENU)ID_POWEROFF_BUTTON,      // ��ťID
        hInstance,                     // ʵ�����
        NULL);                         // ��ʹ��
    SendMessage(hPowerOffButton, WM_SETFONT, (WPARAM)hFont, TRUE);

    //����������ť��PEϵͳ���������Ƴ���ϵͳ�Զ�������
    HWND hRebootButton = CreateWindow(
        L"BUTTON",                     // Ԥ�����ࣻʹ�ð�ť��
        L"����",               // ��ť�ϵ�����
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // ��ʽ
        350,                           // λ��x
        400,                           // λ��y
        100,                           // ��ť���
        30,                            // ��ť�߶�
        hwnd,                          // ������
        (HMENU)ID_REBOOT_BUTTON,      // ��ťID
        hInstance,                     // ʵ�����
        NULL);
    SendMessage(hRebootButton, WM_SETFONT, (WPARAM)hFont, TRUE);


    HWND hDiskPartButton = CreateWindow(
        L"BUTTON",                     // Ԥ�����ࣻʹ�ð�ť��
        L"DiskPart",               // ��ť�ϵ�����
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // ��ʽ
        300,                           // λ��x
        150,                           // λ��y
        100,                           // ��ť���
        30,                            // ��ť�߶�
        hwnd,                          // ������
        (HMENU)ID_DISKPART_BUTTON,      // ��ťID
        hInstance,                     // ʵ�����
        NULL);


    HWND hFMButton = CreateWindow(
        L"BUTTON",                     // Ԥ�����ࣻʹ�ð�ť��
        L"�����ļ�������",               // ��ť�ϵ�����
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // ��ʽ
        300,                           // λ��x
        200,                           // λ��y
        100,                           // ��ť���
        30,                            // ��ť�߶�
        hwnd,                          // ������
        (HMENU)ID_FM_BUTTON,      // ��ťID
        hInstance,                     // ʵ�����
        NULL);
    SendMessage(hFMButton, WM_SETFONT, (WPARAM)hFont, TRUE);

    // ��ʾ����
    ShowWindow(hwnd, nShowCmd);
    UpdateWindow(hwnd);

    // ��Ϣѭ��
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // ɾ���������
    DeleteObject(hFont);

    return msg.wParam;
}

// ���ڹ��̺�������
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_COMMAND:

        // ����cmd.exe
        if (LOWORD(wParam) == ID_CMD_BUTTON)
        {
            ShellExecute(hwnd, L"open", L"cmd.exe", NULL, NULL, SW_SHOW);  // ʹ�ÿ��ַ�������
        }

        // ����regedit.exe
        else if (LOWORD(wParam) == ID_REGEDIT_BUTTON)
        {
            ShellExecute(hwnd, L"open", L"regedit.exe", NULL, NULL, SW_SHOW);  // ʹ�ÿ��ַ�������
        }

        // ִ��pe�ػ�ָ��
        else if (LOWORD(wParam) == ID_POWEROFF_BUTTON)
        {
            // �����ھ����Ҫִ�еĲ�����Ҫִ�еĳ��򣨿ɴ�·���������Σ����� /c��������Ŀ¼��������ʾ��ʽ��SW_SHOW��SW_HIDE�ȣ�
            ShellExecute(hwnd, L"open", L"wpeutil", L"shutdown", NULL, SW_SHOW);
        }
        // ֱ���˳����򣬵ȴ�ϵͳ�Զ�����
        else if (LOWORD(wParam) == ID_REBOOT_BUTTON)
        {
            PostQuitMessage(0);
        }

        // ��Dism++
        else if (LOWORD(wParam) == ID_DISKPART_BUTTON)
        {
            ShellExecute(hwnd, L"open", L"diskpart.exe", NULL, NULL, SW_SHOW);  // ʹ�ÿ��ַ�������
        }

        // file manager
        else if (LOWORD(wParam) == ID_FM_BUTTON)
        {
            OPENFILENAME ofn;
            wchar_t szFile[999] = { 0 }; //�ļ����Ļ�����
            ZeroMemory(&ofn, sizeof(ofn));
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = hwnd;
            ofn.lpstrFile = szFile;
            ofn.nMaxFile = sizeof(szFile) / sizeof(szFile[0]);
            ofn.lpstrFilter = L"All Files\0*.*\0Text Files\0*.TXT\0";
            ofn.nFilterIndex = 1;
            ofn.lpstrFileTitle = NULL;
            ofn.nMaxFileTitle = 0;
            ofn.lpstrInitialDir = NULL;
            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

            // ��ʾ���ļ��Ի���
            if (GetOpenFileName(&ofn) == TRUE)
            {
                // �û�ѡ�����ļ���szFile �а����ļ�·��
                MessageBox(hwnd, szFile, L"Selected File", MB_OK);  // ��ʾѡ����ļ�·��
                MessageBox(hwnd, L"�����ܵ������������ھ����peϵͳ��explorer�������ͨ��ϵͳ���ú�������һ���ļ�������ҳ�棬�ڴ�ҳ���������Ҽ�����ĳ�������С�", L"���ڱ����ܵ�˵��", MB_OK);
                MessageBox(hwnd, L"����������в����������п⣬�����򱾳��򴫵��ļ�������", L"���ڱ����ܵ�˵��", MB_OK);
            }
        }
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

        // ����������Ϣ
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}