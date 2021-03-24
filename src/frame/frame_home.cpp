#include "frame_home.h"
#include "SD.h"
#include "ArduinoJson.h"
#include "FS.h"
#include "frame.h"

Frame_Home::Frame_Home() : Frame_Base()
{
    _frame_name = Frame_Home::APPID;
    _frame_id = 1;

    _page_container = new EPDGUI_Page_Container(0, HEADER_HEIGHT, WIDTH, HEIGHT - HEADER_HEIGHT);
}

Frame_Home::~Frame_Home()
{
    delete _page_container;
}

void Frame_Home::init(epdgui_args_vector_t &args)
{
    Serial.println("initialize home screen");

    _is_run = 1;
    M5.EPD.Clear();

    String content = "";
    File file = SD.open("/Index.json");
    if (file)
    {
        while (file.available())
        {
            content += (char)file.read();
        }
        Serial.println("Read file completed");
    }
    else
    {
        Serial.println("Unable to read file");
    }

    DynamicJsonDocument virtualJsonDocument(1024 * 16);
    if (content != "")
    {
        DeserializationError error = deserializeJson(virtualJsonDocument, content);
        if (error)
        {
            Serial.println("Deserialize failed");
        }
        Serial.println("deserialized successfully");
    }

    JsonArray widgets = virtualJsonDocument.containsKey("widgets") ? virtualJsonDocument["widgets"].as<JsonArray>() : virtualJsonDocument.createNestedArray("widgets");

    JsonObject factoryTestWidget = widgets.createNestedObject();
    factoryTestWidget["widgettype"] = "icon";
    factoryTestWidget["description"] = "Factory Test";
    factoryTestWidget["icon"] = "/Icons/Test.jpg";
    factoryTestWidget["grid_width"] = 1;
    factoryTestWidget["grid_height"] = 1;
    factoryTestWidget["phiActionId"] = Frame_FactoryTest::APPID;

    JsonObject compareWidget = widgets.createNestedObject();
    compareWidget["widgettype"] = "icon";
    compareWidget["description"] = "Compare Graphic Modes";
    compareWidget["icon"] = "/Icons/Lab.jpg";
    compareWidget["grid_width"] = 1;
    compareWidget["grid_height"] = 1;
    compareWidget["phiActionId"] = Frame_Compare::APPID;

    JsonObject keyboardWidget = widgets.createNestedObject();
    keyboardWidget["widgettype"] = "icon";
    keyboardWidget["description"] = "Keyboard";
    keyboardWidget["icon"] = "/Icons/Lab.jpg";
    keyboardWidget["grid_width"] = 1;
    keyboardWidget["grid_height"] = 1;
    keyboardWidget["phiActionId"] = Frame_Keyboard::APPID;

    JsonObject settingsWidget = widgets.createNestedObject();
    settingsWidget["widgettype"] = "icon";
    settingsWidget["description"] = "Settings";
    settingsWidget["icon"] = "/Icons/Settings.jpg";
    settingsWidget["grid_width"] = 1;
    settingsWidget["grid_height"] = 1;
    settingsWidget["phiActionId"] = Frame_Setting::APPID;

    //serializeJsonPretty(virtualJsonDocument, Serial);

    String name = "PhiBoard";
    if (virtualJsonDocument.containsKey("name"))
    {
        virtualJsonDocument["name"];
    }
    _canvas_title->drawString(name, 270, 34);
    _canvas_title->pushCanvas(0, 8, UPDATE_MODE_NONE);

    _page_container->PropagateWidgets(widgets, WIDTH, HEADER_HEIGHT);

    _page_container->Init();
    EPDGUI_AddObject(_page_container);
}

void Frame_Home::run(void)
{
    M5.update();
    if (M5.BtnL.isPressed() && lastButtonIndex != -1)
    {
        lastButtonIndex = -1;
        _page_container->SetPageIndex(_page_container->GetPageIndex() - 1);
    }
    else if (M5.BtnR.isPressed() && lastButtonIndex != 1)
    {
        lastButtonIndex = 1;
        _page_container->SetPageIndex(_page_container->GetPageIndex() + 1);
    }
    else if (!M5.BtnL.isPressed() && lastButtonIndex == -1)
    {
        lastButtonIndex = 0;
    }
    else if (!M5.BtnR.isPressed() && lastButtonIndex == 1)
    {
        lastButtonIndex = 0;
    }
}
