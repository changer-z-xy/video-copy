#ifndef GET_FRAME_H
#define GET_FRAME_H
#include <abc.h>
class Get_Frame
{
public:
    int height;
    int width;
    int fps;
    int num_frame;
    int nowframe;
    IplImage *frame;
    CvCapture *cap;

    Get_Frame(char *fn);
    IplImage *pop();
};

#endif // GET_FRAME_H
