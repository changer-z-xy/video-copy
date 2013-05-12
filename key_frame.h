#ifndef KEY_FRAME_H
#define KEY_FRAME_H

#include <abc.h>

#include "cmpworker.h"

class CmpWorker;

class key_frame
{
public:
    std::vector <bm_process*> flist;//key frame list,represent a video
    int video_length;
    char* dir;
    CmpWorker *worker;

    key_frame(Get_Frame video, CmpWorker *_worker, char *sdir);
    ~key_frame();
    float distance_hgram(float *a, float *b);
    float distance(bm_process* a, bm_process* b);
    bool cp_video(const key_frame &b);
};

#endif // KEY_FRAME_H
