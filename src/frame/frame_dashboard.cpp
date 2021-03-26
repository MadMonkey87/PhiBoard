#include "frame_dashboard.h"
#include "SD.h"
#include "ArduinoJson.h"
#include "FS.h"

Frame_Dashboard::Frame_Dashboard() : Frame_Base("TEST")
{
    _frame_name = Frame_Dashboard::APPID;

    exitbtn("Back");

    _key_exit->AddArgs(EPDGUI_Button::EVENT_RELEASED, 0, (void *)(&_is_run));
    _key_exit->BindEvent(EPDGUI_Button::EVENT_RELEASED, &Frame_Base::exit_cb);

    _header = new EPDGUI_Header(0, 0, WIDTH, HEADER_HEIGHT);
    _page_container = new EPDGUI_Page_Container(0, HEADER_HEIGHT, WIDTH, HEIGHT - HEADER_HEIGHT);
}

Frame_Dashboard::~Frame_Dashboard()
{
    delete _page_container;
}

void Frame_Dashboard::init(epdgui_args_vector_t &args)
{
    Serial.println("Initialize playground");

    _is_run = 1;
    M5.EPD.Clear();

    //EPDGUI_AddObject(_key_exit);

    _page_container->ClearWidgets();
    if (args.size() > 0)
    {
        String *param = (String *)(args[0]);
        String jsonFilePath = *param;

        LoadWidgetsFromJsonFile(jsonFilePath);
    }

    _page_container->Init();
    EPDGUI_AddObject(_page_container);
}

void Frame_Dashboard::run(void)
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

void Frame_Dashboard::LoadWidgetsFromJsonFile(String jsonFilePath)
{
    JsonArray widgets;
    File file = SD.open(jsonFilePath);
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
    widgets = jsonDocument["widgets"].as<JsonArray>();
    
    _header->SetTitle("TODO");
    _page_container->PropagateWidgets(widgets, WIDTH, HEADER_HEIGHT);
}