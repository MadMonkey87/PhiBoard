#include "frame_playground.h"
#include "SD.h"
#include "ArduinoJson.h"
#include "FS.h"

Frame_Playground::Frame_Playground() : Frame_Base()
{
    Serial.print("Frame_Playground constructor");

    _frame_name = "Frame_Playground";

    exitbtn("Back");
    _canvas_title->drawString("Playground", 270, 34);

    _key_exit->AddArgs(EPDGUI_Button::EVENT_RELEASED, 0, (void *)(&_is_run));
    _key_exit->Bind(EPDGUI_Button::EVENT_RELEASED, &Frame_Base::exit_cb);

    File file = SD.open("/index.json");
    if (!file)
    {
        Serial.println("Failed to open file for reading");
        return;
    }

    String content = "";
    while (file.available())
    {
        content += (char)file.read();
    }

    DynamicJsonDocument jsonDocument(1024 * 16);
    DeserializationError error = deserializeJson(jsonDocument, content);
    if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
    }
    JsonArray widgets = jsonDocument["widgets"].as<JsonArray>();

    _page_container = new EPDGUI_Page_Container(0, HEADER_HEIGHT, WIDTH, HEIGHT - HEADER_HEIGHT);
    _page_container->PropagateWidgets(widgets, WIDTH, HEADER_HEIGHT);
}

Frame_Playground::~Frame_Playground()
{
    Serial.print("Frame_Playground destructor");

    delete _page_container;
}

int Frame_Playground::init(epdgui_args_vector_t &args)
{
    Serial.print("Frame_Playground init");

    _is_run = 1;
    M5.EPD.Clear();

    _canvas_title->pushCanvas(0, 8, UPDATE_MODE_NONE);
    EPDGUI_AddObject(_key_exit);

    _page_container->Init();
    EPDGUI_AddObject(_page_container);

    return 0;
}

int Frame_Playground::run(void)
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

    return 1;
}
