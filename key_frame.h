#ifndef KEY_FRAME_H
#define KEY_FRAME_H
#include <abc.h>
class key_frame
{
public:
    std::vector <bm_process*> flist;//key frame list,represent a video
    int video_length;
    char* dir;


    key_frame( Get_Frame &video,char* sdir);
};

#endif // KEY_FRAME_H
