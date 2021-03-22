#include "phi_widget_icon.h"
#include "../../launcher.h"

void released_cb_234(epdgui_args_vector_t &args)
{
    Serial.println("pressed!");
    LaunchByAppId("24184b57-c0d8-4d2a-aa52-9ffd7ad0dc46");
    Serial.println("launched");
    //*((int *)(args[0])) = 0;
}

PHI_Widget_Icon::PHI_Widget_Icon(int16_t x, int16_t y, int16_t w, int16_t h) : PHI_Widget_Graphic_Base(x, y, w, h, true, true)
{
    Bind(PHI_Widget_Base::EVENT_RELEASED, &released_cb_234);
}

void PHI_Widget_Icon::Render(JsonVariant data)
{
    PHI_Widget_Graphic_Base::Render(data);

    String description = data["description"];
    String icon = data["icon"];

    this->_Canvas->drawJpgFile(SD, icon.c_str(), _w / 2 - 70, _h / 2 - 70 - 25, 140, 140);
    this->_CanvasPressed->drawJpgFile(SD, icon.c_str(), _w / 2 - 70, _h / 2 - 70 - 25, 140, 140);

    RenderDescriptionLabel(description.c_str());
}
