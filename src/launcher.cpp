#include "launcher.h"

void PerformPhiAction(String phiActionId, String phiActionParam)
{
    if (phiActionId == NULL)
    {
        return;
    }

    Frame_Base *frame = EPDGUI_GetFrame(phiActionId);

    if (frame == NULL)
    {
        if (phiActionId == Frame_Home::APPID)
        {
            frame = new Frame_Home();
        }
        else if (phiActionId == Frame_Dashboard::APPID)
        {
            frame = new Frame_Dashboard();
        }
        else if (phiActionId == Frame_FactoryTest::APPID)
        {
            frame = new Frame_FactoryTest();
        }
        else if (phiActionId == Frame_Keyboard::APPID)
        {
            frame = new Frame_Keyboard();
        }
        else if (phiActionId == Frame_Setting::APPID)
        {
            frame = new Frame_Setting();
        }
        else if (phiActionId == Frame_FileIndex::APPID)
        {
            frame = new Frame_FileIndex("/");
        }
        else if (phiActionId == Frame_Compare::APPID)
        {
            frame = new Frame_Compare();
        }
        else
        {
            Serial.println("appid not found");
            // todo: show an error
        }

        if (frame != NULL)
        {
            EPDGUI_AddFrame(phiActionId, frame);
        }
    }

    if (frame != NULL)
    {
        Serial.println("launch app");
        if (phiActionParam != NULL)
        {
            String *param = new String(phiActionParam);
            EPDGUI_AddFrameArg(phiActionId, 0, param);
        }

        EPDGUI_PushFrame(frame);
    }
}