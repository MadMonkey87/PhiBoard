#include "launcher.h"

void LaunchByAppId(String appId)
{
    Frame_Base *frame = EPDGUI_GetFrame(appId);
    if (frame == NULL)
    {
        if (appId == Frame_Home::APPID)
        {
            frame = new Frame_Home();
        }
        else if (appId == Frame_Playground::APPID)
        {
            frame = new Frame_Playground();
        }
        else if (appId == Frame_FactoryTest::APPID)
        {
            frame = new Frame_FactoryTest();
        }
        else if (appId == Frame_Keyboard::APPID)
        {
            frame = new Frame_Keyboard();
        }
        else if (appId == Frame_Setting::APPID)
        {
            frame = new Frame_Setting();
        }
        else if (appId == Frame_FileIndex::APPID)
        {
            frame = new Frame_FileIndex("/");
        }
        else if (appId == Frame_Compare::APPID)
        {
            frame = new Frame_Compare();
        }
        else
        {
            // todo: show an error
        }

        if (frame == NULL)
        {
            EPDGUI_AddFrame(appId, frame);
        }
    }

    EPDGUI_PushFrame(frame);
}