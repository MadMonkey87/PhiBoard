#ifndef _FRAME_BASE_H_
#define _FRAME_BASE_H_

#include <M5EPD.h>
#include "../epdgui/epdgui_button.h"
#include "../global_setting.h"
#include "../resources/ImageResource.h"

class Frame_Base
{
public:
    Frame_Base(String title = "");
    void exitbtn(String title, uint16_t width = 150);
    virtual ~Frame_Base();
    virtual void run();
    virtual void exit();
    virtual void init(epdgui_args_vector_t &args) = 0;
    String GetFrameName() { return _frame_name; }
    int isRun() { return _is_run; }
    void SetIsRun(int value)
    {
        _is_run = value;
    }
    void SetFrameID(uint32_t id) { _frame_id = id; }
    uint32_t GetFrameID() { return _frame_id; }

protected:
    static void exit_cb(epdgui_args_vector_t &args);
    String _frame_name;
    int _is_run = 1;
    M5EPD_Canvas *_canvas_title = NULL;
    EPDGUI_Button *_key_exit = NULL;
    uint32_t _frame_id;
};

#endif