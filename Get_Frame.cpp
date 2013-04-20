#include <abc.h>
#include <QDebug>

Get_Frame::Get_Frame( const char* fn )
{
    this->cap = cvCreateFileCapture(fn);
    qDebug() << cap;
    //获取视频信息
    cvQueryFrame(this->cap);
    this->height= (int) cvGetCaptureProperty(this->cap, CV_CAP_PROP_FRAME_HEIGHT);
    this->width= (int) cvGetCaptureProperty(this->cap, CV_CAP_PROP_FRAME_WIDTH);
    this->fps= (int) cvGetCaptureProperty(this->cap, CV_CAP_PROP_FPS);
    this->num_frame= (int) cvGetCaptureProperty(this->cap, CV_CAP_PROP_FRAME_COUNT);
    this->nowframe=0;
}
IplImage* Get_Frame::pop(){
    for(int i=0;i<SFRA-1;i++)cvQueryFrame(this->cap);
    this->frame=cvQueryFrame(this->cap);
    return this->frame;

}
