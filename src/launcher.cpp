#include "launcher.h"

void LaunchByAppId(String appId)
{
    Serial.println("launch an app by its id");
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
            Serial.println("appid not found");
            // todo: show an error
        }
        EPDGUI_AddFrame(appId, frame);
    }

    if (frame != NULL)
    {
        Serial.println("launch app");
        EPDGUI_PushFrame(frame);
    }
}