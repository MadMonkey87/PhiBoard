#include "frame_home.h"
#include "SD.h"
#include "ArduinoJson.h"
#include "FS.h"
#include "frame_playground.h"

void key_synctime_cb2(epdgui_args_vector_t &args)
{
    Frame_Base *frame = EPDGUI_GetFrame("Frame_Playground");
    if (frame == NULL)
    {
        frame = new Frame_Playground();
        EPDGUI_AddFrame("Frame_Playground", frame);
    }
    EPDGUI_PushFrame(frame);
    *((int *)(args[0])) = 0;
}

Frame_Home::Frame_Home() : Frame_Base()
{
    _frame_name = "Frame_Home";
    _frame_id = 1;

    _canvas_title->drawString("PhiBoard", 270, 34);

    DynamicJsonDocument jsonDocument(1024 * 16);
    JsonArray widgets = jsonDocument.to<JsonArray>();

    JsonObject dashboardWidget = widgets.createNestedObject();
    dashboardWidget["widgettype"] = "icon";
    dashboardWidget["description"] = "Dashboard";
    dashboardWidget["icon"] = "/Icons/Dashboard.jpg";
    dashboardWidget["grid_width"] = 1;
    dashboardWidget["grid_height"] = 1;

    JsonObject settingsWidget = widgets.createNestedObject();
    settingsWidget["widgettype"] = "icon";
    settingsWidget["description"] = "Settings";
    settingsWidget["icon"] = "/Icons/Settings.jpg";
    settingsWidget["grid_width"] = 1;
    settingsWidget["grid_height"] = 1;

    JsonObject factoryTestWidget = widgets.createNestedObject();
    factoryTestWidget["widgettype"] = "icon";
    factoryTestWidget["description"] = "Factory Test";
    factoryTestWidget["icon"] = "/Icons/Test.jpg";
    factoryTestWidget["grid_width"] = 1;
    factoryTestWidget["grid_height"] = 1;

    JsonObject compareWidget = widgets.createNestedObject();
    compareWidget["widgettype"] = "icon";
    compareWidget["description"] = "Compare Graphic Modes";
    compareWidget["icon"] = "/Icons/Lab.jpg";
    compareWidget["grid_width"] = 1;
    compareWidget["grid_height"] = 1;

    _page_container = new EPDGUI_Page_Container(0, HEADER_HEIGHT, WIDTH, HEIGHT - HEADER_HEIGHT);
    _page_container->PropagateWidgets(widgets, WIDTH, HEADER_HEIGHT);
}

Frame_Home::~Frame_Home()
{
    delete _page_container;
}

int Frame_Home::init(epdgui_args_vector_t &args)
{
    _is_run = 1;
    M5.EPD.Clear();

    _canvas_title->pushCanvas(0, 8, UPDATE_MODE_NONE);

    _page_container->Init();
    EPDGUI_AddObject(_page_container);

    return 0;
}

int Frame_Home::run(void)
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
