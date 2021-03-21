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
    if(_pages.size() == 0){
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

    M5.EPD.Clear(0);
    UpdateState(-1, -1);
    Draw();
    M5.EPD.UpdateArea(_x, _y, _w, _h, UPDATE_MODE_GC16);
}

void EPDGUI_Page_Container::Draw(m5epd_update_mode_t mode)
{
    if (_ishide)
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
    if (_ishide)
    {
        return;
    }

    if (_size > 0)
    {
        GetPageByIndex(_pageIndex)->Draw(canvas);
    }

    _page_indicator->Draw(canvas);
}

void EPDGUI_Page_Container::Bind(int16_t state, void (*func_cb)(epdgui_args_vector_t &))
{
}

void EPDGUI_Page_Container::UpdateState(int16_t x, int16_t y)
{
    if (!_isenable)
    {
        return;
    }

    if (_size > 0)
    {
        GetPageByIndex(_pageIndex)->UpdateState(x, y);
    }

    _page_indicator->UpdateState(x, y);
}

void EPDGUI_Page_Container::EPDGUI_AddComponent(EPDGUI_Base *component, int16_t pageIndex)
{
    // add missing pages
    for (int i = _pages.size(); i < pageIndex + 1; i++)
    {
        _pages.push_back(new EPDGUI_Container(0, 0, _w, _h - INDICATOR_HEIGHT));
        _size = _pages.size();
    }

    GetPageByIndex(pageIndex)->EPDGUI_AddComponent(component);
}

void EPDGUI_Page_Container::PropagateWidgets(JsonArray widgets, int16_t width, int16_t offsetY)
{
    int16_t x = 0;
    int16_t y = 0;
    int16_t p = 0;
    int16_t last_grid_height = 0;

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

        // go to next row/column/page if not enough space is available
        if (GRID_WIDTH - x < grid_width)
        {
            x = 0;
            y += last_grid_height;
        }

        if (GRID_HEIGHT - y < grid_height)
        {
            x = 0;
            y = 0;
            p++;
            last_grid_height = 0;
        }

        int16_t element_width = ((width - 2 * GRID_MARGIN) - (GRID_WIDTH - 1) * GRID_MARGIN) / GRID_WIDTH;
        int16_t element_height = element_width; //((HEIGHT - offsetY - 2 * GRID_MARGIN) - (GRID_HEIGHT - 1) * GRID_MARGIN) / GRID_HEIGHT;

        int16_t pos_x = GRID_MARGIN + (x * (element_width + GRID_MARGIN));
        int16_t pos_y = offsetY + GRID_MARGIN + (y * (element_height + GRID_MARGIN));
        int16_t width = element_width * grid_width + (grid_width - 1) * (x + 1) * GRID_MARGIN;
        int16_t height = element_height * grid_height + (grid_height - 1) * (y + 1) * GRID_MARGIN;

        x += grid_width;
        last_grid_height = last_grid_height > grid_height ? last_grid_height : grid_height;

        if (jsonWidgetItem["widgettype"] == "icon")
        {
            EPDGUI_Widget_Icon *_widget_icon = new EPDGUI_Widget_Icon(pos_x, pos_y, width, height);
            _widget_icon->Init(jsonWidgetItem);
            EPDGUI_AddComponent(_widget_icon, p);
        }
        else if (jsonWidgetItem["widgettype"] == "text")
        {
            EPDGUI_Widget_Text *_widget_text = new EPDGUI_Widget_Text(pos_x, pos_y, width, height);
            _widget_text->Init(jsonWidgetItem);
            EPDGUI_AddComponent(_widget_text, p);
        }
        else if (jsonWidgetItem["widgettype"] == "doubleswitch")
        {
            EPDGUI_Widget_Double_Switch *_widget_double_switch = new EPDGUI_Widget_Double_Switch(pos_x, pos_y, width, height);
            _widget_double_switch->Init(jsonWidgetItem);
            EPDGUI_AddComponent(_widget_double_switch, p);
        }
        else if (jsonWidgetItem["widgettype"] == "toggle")
        {
            EPDGUI_Widget_Toggle *_widget_toggle = new EPDGUI_Widget_Toggle(pos_x, pos_y, width, height);
            _widget_toggle->Init(jsonWidgetItem);
            EPDGUI_AddComponent(_widget_toggle, p);
        }
        else if (jsonWidgetItem["widgettype"] == "icontoggle")
        {
            EPDGUI_Widget_Icon_Toggle *_widget_icon_toggle = new EPDGUI_Widget_Icon_Toggle(pos_x, pos_y, width, height);
            _widget_icon_toggle->Init(jsonWidgetItem);
            EPDGUI_AddComponent(_widget_icon_toggle, p);
        }
        else if (jsonWidgetItem["widgettype"] == "progress")
        {
            EPDGUI_Widget_Progress *_widget_progress = new EPDGUI_Widget_Progress(pos_x, pos_y, width, height);
            _widget_progress->Init(jsonWidgetItem);
            EPDGUI_AddComponent(_widget_progress, p);
        }
        else if (jsonWidgetItem["widgettype"] == "multibutton")
        {
            EPDGUI_Widget_Multi_Button *_widget_multi_button = new EPDGUI_Widget_Multi_Button(pos_x, pos_y, width, height, grid_height * 3);
            _widget_multi_button->Init(jsonWidgetItem);
            EPDGUI_AddComponent(_widget_multi_button, p);
        }
        else if (jsonWidgetItem["widgettype"] == "spinner")
        {
            EPDGUI_Widget_Spinner *_widget_spinner = new EPDGUI_Widget_Spinner(pos_x, pos_y, width, height);
            _widget_spinner->Init(jsonWidgetItem);
            EPDGUI_AddComponent(_widget_spinner, p);
        }
    }
}

EPDGUI_Container *EPDGUI_Page_Container::GetPageByIndex(int16_t pageIndex)
{
    auto iterator = _pages.begin();
    std::advance(iterator, pageIndex);
    //_pages.end();
    return *iterator;
}