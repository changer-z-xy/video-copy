#ifndef ABC_H
#define ABC_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>

#include <math.h>
#include <vector>
#include <iostream>
#include <queue>
#include <string>
#include <algorithm>

#include <windows.h>

#include <dshow.h>
#include <qedit.h>
//#include <atlbase.h>
#include <stdlib.h>
#include <time.h>

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <opencv.hpp>
#include <nonfree/nonfree.hpp>
#include <nonfree/features2d.hpp>
#include <cvaux.h>

#include "bm_process.h"
#include "get_frame.h"
#include "key_frame.h"
#include "framelistmatcher.h"

#define UNDEFINEDCOLOR -0.5
#define PI 3.1415926536
#define SCENEB 0.65
#define KFB 0.7
#define SFRA 10
#define MAX_HD 1920*1200*5


void MyFreeMediaType(AM_MEDIA_TYPE &mt);
void pixel_hsv(float R,float G,float B,float& H,float& S,float& V);
bool between(float a,float b,float c);
int lhsv_h(float h);
int lhsv_sv(float sv);
template <class T>
int Len(T& array);
//float distance(bm_process a,bm_process b);
//float distance_hgram(float *a,float *b);
void shtime(clock_t start,clock_t end);
//bool cp_video(key_frame a,key_frame b);
void show_lhsv(int a[10][5][5]);

extern QMutex outputMutex;
extern QWaitCondition outputNotEmpty;
extern QQueue<QString> outputQueue;

#endif // ABC_H
