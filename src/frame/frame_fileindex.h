#ifndef _FRAME_FILEINDEX_H_
#define _FRAME_FILEINDEX_H_

#include "frame_base.h"
#include "../epdgui/epdgui.h"
#include <SD.h>

class Frame_FileIndex : public Frame_Base
{
public:
    static constexpr const char *APPID = "8b408095-8cab-4f2a-af86-38f708cc2a0a";

public:
    Frame_FileIndex(String path);
    ~Frame_FileIndex();
    void listDir(fs::FS &fs, const char *dirname);
    void init(epdgui_args_vector_t &args);

private:
    std::vector<EPDGUI_Button *> _key_files;
    String _path;
};

#endif //_FRAME_FILEINDEX_H_