#include "epdgui_page_container.h"

EPDGUI_Page_Container::EPDGUI_Page_Container(int16_t x, int16_t y, int16_t w, int16_t h) : EPDGUI_Base(x, y, w, h)
{
}

EPDGUI_Page_Container::~EPDGUI_Page_Container()
{
    for (std::list<EPDGUI_Container *>::iterator p = _pages.begin(); p != _pages.end(); p++)
    {
        delete (*p);
    }
}

void EPDGUI_Page_Container::Init()
{
    if (_pages.size() == 0)
    {
        // todo: add an indicator that the page has no elements
    }
    _page_indicator = new EPDGUI_Page_Indicator(_x, _h - INDICATOR_HEIGHT + _y, _w, INDICATOR_HEIGHT, _pages.size());
}

void EPDGUI_Page_Container::SetPageIndex(int16_t pageIndex)
{
    if (pageIndex < 0)
    {
        pageIndex = _pages.size() - 1;
    }
    else if (pageIndex >= _pages.size())
    {
        pageIndex = 0;
    }

    if (pageIndex == _pageIndex)
    {
        return;
    }

    _pageIndex = pageIndex;
    _page_indicator->SetPageIndex(pageIndex);

    //M5.EPD.Clear(0);
    M5.EPD.Clear();

    UpdateTouchState(-1, -1);
    Draw();
    M5.EPD.UpdateArea(_x, _y, _w, _h, UPDATE_MODE_GC16);
}

void EPDGUI_Page_Container::Draw(m5epd_update_mode_t mode)
{
    if (_hidden)
    {
        return;
    }

    if (_size > 0)
    {
        GetPageByIndex(_pageIndex)->Draw(mode);
    }

    _page_indicator->Draw(mode);
}

void EPDGUI_Page_Container::Draw(M5EPD_Canvas *canvas)
{
    if (_hidden)
    {
        return;
    }

    if (_size > 0)
    {
        GetPageByIndex(_pageIndex)->Draw(canvas);
    }

    _page_indicator->Draw(canvas);
}

void EPDGUI_Page_Container::BindEvent(int16_t state, void (*func_cb)(epdgui_args_vector_t &))
{
}

void EPDGUI_Page_Container::UpdateTouchState(int16_t x, int16_t y)
{
    if (!_enabled)
    {
        return;
    }

    if (_size > 0)
    {
        GetPageByIndex(_pageIndex)->UpdateTouchState(x, y);
    }

    _page_indicator->UpdateTouchState(x, y);
}

void EPDGUI_Page_Container::AddComponent(EPDGUI_Base *component, int16_t pageIndex)
{
    // add missing pages
    for (int i = _pages.size(); i < pageIndex + 1; i++)
    {
        _pages.push_back(new EPDGUI_Container(0, 0, _w, _h - INDICATOR_HEIGHT));
        _size = _pages.size();
    }

    GetPageByIndex(pageIndex)->AddComponent(component);
}

EPDGUI_Container *EPDGUI_Page_Container::GetPageByIndex(int16_t pageIndex)
{
    auto iterator = _pages.begin();
    std::advance(iterator, pageIndex);
    //_pages.end();
    return *iterator;
}

bool EPDGUI_Page_Container::IsOccupied(bool occupancyMatrix[GRID_WIDTH][GRID_HEIGHT], int16_t x, int16_t y, int16_t w, int16_t h)
{
    for (int n = x; n < x + w; n++)
    {
        for (int m = y; m < y + h; m++)
        {
            if (occupancyMatrix[n][m])
            {
                return true;
            }
        }
    }

    return false;
}

void EPDGUI_Page_Container::Occupy(bool occupancyMatrix[GRID_WIDTH][GRID_HEIGHT], int16_t x, int16_t y, int16_t w, int16_t h)
{
    for (int n = x; n < x + w; n++)
    {
        for (int m = y; m < y + h; m++)
        {
            occupancyMatrix[n][m] = true;
        }
    }
}

void EPDGUI_Page_Container::ClearOccupancies(bool occupancyMatrix[GRID_WIDTH][GRID_HEIGHT])
{
    for (int n = 0; n < GRID_WIDTH; n++)
    {
        for (int m = 0; m < GRID_HEIGHT; m++)
        {
            occupancyMatrix[n][m] = false;
        }
    }
}

void EPDGUI_Page_Container::ClearWidgets()
{
    for (std::list<EPDGUI_Container *>::iterator p = _pages.begin(); p != _pages.end(); p++)
    {
        delete (*p);
    }
    _pages.clear();
}

void EPDGUI_Page_Container::PropagateWidgets(JsonArray widgets, int16_t width, int16_t offsetY)
{

    int16_t x = 0;
    int16_t y = 0;
    int16_t p = 0;

    bool occupancyMatrix[GRID_WIDTH][GRID_HEIGHT] = {{false}};

    for (JsonVariant jsonWidgetItem : widgets)
    {
        int16_t grid_width = jsonWidgetItem["grid_width"];
        if (grid_width <= 0)
        {
            grid_width = 1;
        }
        else if (grid_width > GRID_WIDTH)
        {
            grid_width = GRID_WIDTH;
        }
        int16_t grid_height = jsonWidgetItem["grid_height"];
        if (grid_height <= 0)
        {
            grid_height = 1;
        }
        else if (grid_height > GRID_HEIGHT)
        {
            grid_height = GRID_HEIGHT;
        }

        // todo GRID_WIDTH < x + grid_width is only necessary because we should check before this loop that x/y are in bounds
        while (GRID_WIDTH < x + grid_width || IsOccupied(occupancyMatrix, x, y, grid_width, grid_height))
        {
            x++;
            if (GRID_WIDTH < x + grid_width) // go to next column
            {
                x = 0;
                y++;
            }
            if (GRID_HEIGHT < y + grid_height) // go to next page
            {
                x = 0;
                y = 0;
                p++;
                ClearOccupancies(occupancyMatrix);
            }
        }

        Occupy(occupancyMatrix, x, y, grid_width, grid_height);

        int16_t element_width = ((width - 2 * GRID_MARGIN) - (GRID_WIDTH - 1) * GRID_MARGIN) / GRID_WIDTH;
        int16_t element_height = element_width; //((HEIGHT - offsetY - 2 * GRID_MARGIN) - (GRID_HEIGHT - 1) * GRID_MARGIN) / GRID_HEIGHT;

        int16_t pos_x = GRID_MARGIN + (x * (element_width + GRID_MARGIN));
        int16_t pos_y = offsetY + GRID_MARGIN + (y * (element_height + GRID_MARGIN));
        int16_t width = element_width * grid_width + (grid_width - 1) * GRID_MARGIN;
        int16_t height = element_height * grid_height + (grid_height - 1) * GRID_MARGIN;

        if (jsonWidgetItem["widgettype"] == "icon")
        {
            PHI_Widget_Icon *_widget_icon = new PHI_Widget_Icon(pos_x, pos_y, width, height);
            _widget_icon->Init(jsonWidgetItem);
            AddComponent(_widget_icon, p);
        }
        else if (jsonWidgetItem["widgettype"] == "text")
        {
            PHI_Widget_Text *_widget_text = new PHI_Widget_Text(pos_x, pos_y, width, height);
            _widget_text->Init(jsonWidgetItem);
            AddComponent(_widget_text, p);
        }
        else if (jsonWidgetItem["widgettype"] == "doubleswitch")
        {
            PHI_Widget_Double_Switch *_widget_double_switch = new PHI_Widget_Double_Switch(pos_x, pos_y, width, height);
            _widget_double_switch->Init(jsonWidgetItem);
            AddComponent(_widget_double_switch, p);
        }
        else if (jsonWidgetItem["widgettype"] == "toggle")
        {
            PHI_Widget_Toggle *_widget_toggle = new PHI_Widget_Toggle(pos_x, pos_y, width, height);
            _widget_toggle->Init(jsonWidgetItem);
            AddComponent(_widget_toggle, p);
        }
        else if (jsonWidgetItem["widgettype"] == "icontoggle")
        {
            PHI_Widget_Icon_Toggle *_widget_icon_toggle = new PHI_Widget_Icon_Toggle(pos_x, pos_y, width, height);
            _widget_icon_toggle->Init(jsonWidgetItem);
            AddComponent(_widget_icon_toggle, p);
        }
        else if (jsonWidgetItem["widgettype"] == "progress")
        {
            PHI_Widget_Progress *_widget_progress = new PHI_Widget_Progress(pos_x, pos_y, width, height);
            _widget_progress->Init(jsonWidgetItem);
            AddComponent(_widget_progress, p);
        }
        else if (jsonWidgetItem["widgettype"] == "multibutton")
        {
            PHI_Widget_Multi_Button *_widget_multi_button = new PHI_Widget_Multi_Button(pos_x, pos_y, width, height, grid_height * 3);
            _widget_multi_button->Init(jsonWidgetItem);
            AddComponent(_widget_multi_button, p);
        }
        else if (jsonWidgetItem["widgettype"] == "spinner")
        {
            PHI_Widget_Spinner *_widget_spinner = new PHI_Widget_Spinner(pos_x, pos_y, width, height);
            _widget_spinner->Init(jsonWidgetItem);
            AddComponent(_widget_spinner, p);
        }
        else if (jsonWidgetItem["widgettype"] == "slider")
        {
            PHI_Widget_Slider *_widget_slider = new PHI_Widget_Slider(pos_x, pos_y, width, height);
            _widget_slider->Init(jsonWidgetItem);
            AddComponent(_widget_slider, p);
        }

        /*EPDGUI_Button *button = new EPDGUI_Button(pos_x, pos_y, width, height);
        button->CanvasNormal()->fillCanvas(15);

        button->CanvasNormal()->setTextSize(26);
        button->CanvasNormal()->setTextColor(0);
        button->CanvasNormal()->setTextDatum(ML_DATUM);

        button->CanvasNormal()->drawString("pos " + String(pos_x) + " / " + String(pos_y), 10, 20);
        button->CanvasNormal()->drawString("size " + String(width) + " / " + String(height), 10, 60);
        button->CanvasNormal()->drawString("xy: " + String(x) + " / " + String(y), 10, 100);
        button->CanvasNormal()->drawString("grd" + String(grid_width) + " / " + String(grid_height), 10, 140);

        AddComponent(button, p);*/

        x += grid_width;
    }
}