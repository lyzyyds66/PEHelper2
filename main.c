#include <windows.h>
#include <commdlg.h>

// 窗口过程函数声明
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// 此处定义按钮ID
#define ID_POWEROFF_BUTTON 0
#define ID_CMD_BUTTON 1
#define ID_REGEDIT_BUTTON 2
#define ID_REBOOT_BUTTON 3
#define ID_DISM_BUTTON 4
#define ID_7ZIP_BUTTON 5
#define ID_DG_BUTTON 6
#define ID_FM_BUTTON 7


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    // 注册窗口类
    WNDCLASS wc = { 0 };
    wc.lpszClassName = L"PEHelperClass";  // 使用宽字符字面量
    wc.hInstance = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_BTNFACE);
    wc.lpfnWndProc = WindowProc;
    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, L"Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);  // 使用宽字符字面量
        return 0;
    }

    // 创建窗口
    HWND hwnd = CreateWindowEx(
        0,                              // 扩展窗口样式
        L"PEHelperClass",               // 窗口类名
        L"Windows Preinstallation Environment Helper",                    // 窗口标题
        WS_OVERLAPPEDWINDOW & ~(WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_THICKFRAME), // 窗口样式。禁止最小化，禁止最大化，禁止系统菜单（包括关闭按钮），禁止调整窗口大小
        CW_USEDEFAULT, CW_USEDEFAULT,  // 窗口初始位置
        500, 500,                      // 窗口大小
        NULL,                          // 父窗口句柄
        NULL,                          // 菜单句柄
        hInstance,                     // 当前实例句柄
        NULL);                         // 创建参数

    if (hwnd == NULL)
    {
        MessageBox(NULL, L"主窗口创建失败!", L"Error!", MB_ICONEXCLAMATION | MB_OK);  // 使用宽字符字面量
        return 0;
    }

    // 创建命令提示符按钮
    HWND hCmdButton = CreateWindow(
        L"BUTTON",                     // 预定义类；使用按钮类
        L"命令提示符",                 // 按钮上的文字
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // 样式
        100,                           // 位置x
        100,                           // 位置y
        100,                           // 按钮宽度
        30,                            // 按钮高度
        hwnd,                          // 父窗口
        (HMENU)ID_CMD_BUTTON,          // 按钮ID
        hInstance,                     // 实例句柄
        NULL);                         // 不使用

    // 创建注册表编辑器按钮
    HWND hRegeditButton = CreateWindow(
        L"BUTTON",                     // 预定义类；使用按钮类
        L"注册表编辑器",               // 按钮上的文字
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // 样式
        300,                           // 位置x
        100,                           // 位置y
        100,                           // 按钮宽度
        30,                            // 按钮高度
        hwnd,                          // 父窗口
        (HMENU)ID_REGEDIT_BUTTON,      // 按钮ID
        hInstance,                     // 实例句柄
        NULL);                         // 不使用

    //创建关机按钮（PE命令）
    HWND hPowerOffButton = CreateWindow(
        L"BUTTON",                     // 预定义类；使用按钮类
        L"关机",               // 按钮上的文字
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // 样式
        50,                           // 位置x
        400,                           // 位置y
        100,                           // 按钮宽度
        30,                            // 按钮高度
        hwnd,                          // 父窗口
        (HMENU)ID_POWEROFF_BUTTON,      // 按钮ID
        hInstance,                     // 实例句柄
        NULL);                         // 不使用

    //创建重启按钮（PE系统下主程序推出，系统自动重启）
    HWND hRebootButton = CreateWindow(
        L"BUTTON",                     // 预定义类；使用按钮类
        L"重启",               // 按钮上的文字
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // 样式
        350,                           // 位置x
        400,                           // 位置y
        100,                           // 按钮宽度
        30,                            // 按钮高度
        hwnd,                          // 父窗口
        (HMENU)ID_REBOOT_BUTTON,      // 按钮ID
        hInstance,                     // 实例句柄
        NULL);
    /*
    HWND hDismButton = CreateWindow(
        L"BUTTON",                     // 预定义类；使用按钮类
        L"Dism++",               // 按钮上的文字
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // 样式
        300,                           // 位置x
        150,                           // 位置y
        100,                           // 按钮宽度
        30,                            // 按钮高度
        hwnd,                          // 父窗口
        (HMENU)ID_DISM_BUTTON,      // 按钮ID
        hInstance,                     // 实例句柄
        NULL);

    HWND h7ZipButton = CreateWindow(
        L"BUTTON",                     // 预定义类；使用按钮类
        L"7-Zip",               // 按钮上的文字
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // 样式
        100,                           // 位置x
        150,                           // 位置y
        100,                           // 按钮宽度
        30,                            // 按钮高度
        hwnd,                          // 父窗口
        (HMENU)ID_7ZIP_BUTTON,      // 按钮ID
        hInstance,                     // 实例句柄
        NULL);

    HWND hDGButton = CreateWindow(
        L"BUTTON",                     // 预定义类；使用按钮类
        L"DiskGenius",               // 按钮上的文字
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // 样式
        100,                           // 位置x
        200,                           // 位置y
        100,                           // 按钮宽度
        30,                            // 按钮高度
        hwnd,                          // 父窗口
        (HMENU)ID_DG_BUTTON,      // 按钮ID
        hInstance,                     // 实例句柄
        NULL);
        */
    HWND hFMButton = CreateWindow(
        L"BUTTON",                     // 预定义类；使用按钮类
        L"简易文件管理器",               // 按钮上的文字
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // 样式
        300,                           // 位置x
        200,                           // 位置y
        100,                           // 按钮宽度
        30,                            // 按钮高度
        hwnd,                          // 父窗口
        (HMENU)ID_FM_BUTTON,      // 按钮ID
        hInstance,                     // 实例句柄
        NULL);

    // 检查按钮是否创建成功(弃用)
    /*
    if (hCmdButton == NULL || hRegeditButton == NULL || hPowerOffButton == NULL || hRebootButton == NULL)
    {
        MessageBox(hwnd, L"按钮创建失败！", L"错误", MB_ICONERROR | MB_OK);  // 使用宽字符字面量
        return 0;
    }*/

    // 显示窗口
    ShowWindow(hwnd, nShowCmd);
    UpdateWindow(hwnd);

    // 消息循环
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

// 窗口过程函数定义
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_COMMAND:

        // 启动cmd.exe
        if (LOWORD(wParam) == ID_CMD_BUTTON)
        {
            ShellExecute(hwnd, L"open", L"cmd.exe", NULL, NULL, SW_SHOW);  // 使用宽字符字面量
        }

        // 启动regedit.exe
        else if (LOWORD(wParam) == ID_REGEDIT_BUTTON)
        {
            ShellExecute(hwnd, L"open", L"regedit.exe", NULL, NULL, SW_SHOW);  // 使用宽字符字面量
        }

        // 执行pe关机指令
        else if (LOWORD(wParam) == ID_POWEROFF_BUTTON)
        {
            ShellExecute(hwnd, L"open", L"wpeutil", L"shutdown", NULL, SW_SHOW);  // 父窗口句柄，要执行的操作，要执行的程序（可带路径），传参（例如 /c），工作目录，窗口显示方式（SW_SHOW，SW_HIDE等）
        }
        // 直接推出程序，等待系统自动重启
        else if (LOWORD(wParam) == ID_REBOOT_BUTTON)
        {
            PostQuitMessage(0);  
        }
        /*
        // 打开Dism++
        else if (LOWORD(wParam) == ID_DISM_BUTTON)
        {
            ShellExecute(hwnd, L"open", L"X:\\SWWORK_DIR\\SOFTWARE\\Dism++10.1.1002.1\\Dism++x64.exe", NULL, NULL, SW_SHOW);  // 使用宽字符字面量
        }

        // 7zip
        else if (LOWORD(wParam) == ID_7ZIP_BUTTON)
        {
            ShellExecute(hwnd, L"open", L"X:\\SWWORK_DIR\\SOFTWARE\\7-Zip\\7zFM.exe", NULL, NULL, SW_SHOW);  // 使用宽字符字面量
        }
        // dg
        else if (LOWORD(wParam) == ID_DG_BUTTON)
        {
            ShellExecute(hwnd, L"open", L"X:\\SWWORK_DIR\\SOFTWARE\\DiskGenius\\DiskGenius.exe", NULL, NULL, SW_SHOW);  // 使用宽字符字面量
        }
        */
        // file manager
        else if (LOWORD(wParam) == ID_FM_BUTTON)
        {
            OPENFILENAME ofn;
            wchar_t szFile[999] = { 0 }; //文件名的缓冲区
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

            // 显示打开文件对话框
            if (GetOpenFileName(&ofn) == TRUE)
            {
                // 用户选择了文件，szFile 中包含文件路径
                MessageBox(hwnd, szFile, L"Selected File", MB_OK);  // 显示选择的文件路径
                MessageBox(hwnd, L"本功能的用意是让您在精简版pe系统无explorer的情况下通过系统内置函数弹出一个文件管理器页面，在此页面您可以右键单击某程序并运行。\n本程序的运行不需三方运行库，您无需向本程序传递文件参数。", L"关于本功能的说明", MB_OK);
            }
        }
        return 0;


        // 因为程序设计之初去除了右上角关闭按钮，所以这个case暂时用不上了
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

        // 处理其他消息
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}
