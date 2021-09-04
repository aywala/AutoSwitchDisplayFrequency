#include <iostream>
#include <Windows.h>
#define _WIN32_WINN 0x0400
using namespace std;

#pragma   comment(linker,   "/subsystem:\"windows\"  /entry:\"mainCRTStartup\" ") // 隐藏命令行窗口
int main()
{
    DEVMODE devMode;
    LPSYSTEM_POWER_STATUS lpSystemPowerStatus = new SYSTEM_POWER_STATUS;
    GetSystemPowerStatus(lpSystemPowerStatus);
    BYTE last_status = lpSystemPowerStatus->ACLineStatus;
    while (1) {
        EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &devMode);
        GetSystemPowerStatus(lpSystemPowerStatus);
        BYTE status = lpSystemPowerStatus->ACLineStatus;// AC电源连接状态，1为已连接，0为已断开
        if (status!=last_status) {// 仅当电源连接状态发生改变时才自动改变帧率
            if (status == 0 && devMode.dmDisplayFrequency == 165) {// 若电源已断开且帧率为165，则改帧率为60
                devMode.dmDisplayFrequency = 60;
                devMode.dmFields = DM_DISPLAYFREQUENCY;
                devMode.dmSize = sizeof(devMode);
                if(ChangeDisplaySettings(&devMode, 0)== DISP_CHANGE_SUCCESSFUL)
                    cout << "已更改刷新率为:" << devMode.dmDisplayFrequency << endl;
            }
            else if (status == 1 && devMode.dmDisplayFrequency == 60) {// 若电源已接通且帧率为60，则改帧率为165
                devMode.dmDisplayFrequency = 165;
                devMode.dmFields = DM_DISPLAYFREQUENCY;
                devMode.dmSize = sizeof(devMode);
                if (ChangeDisplaySettings(&devMode, 0) == DISP_CHANGE_SUCCESSFUL)
                    cout << "已更改刷新率为:" << devMode.dmDisplayFrequency << endl;
            }
        }
        last_status = status;
        Sleep(1000);
    }
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
