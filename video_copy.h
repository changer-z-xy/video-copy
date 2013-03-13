#include <iostream>
#include <windows.h>
#include <dshow.h>
#include <qedit.h>
#include <atlbase.h>
#include <stdlib.h>
#include <math.h>

#define UNDEFINEDCOLOR -1
#define PI 3.1415926536

typedef struct ahsv{
	int h,s,v;
	int count;
} ahsv;

using namespace std;
class Get_Frame{//get frame from video file
public:
	CComPtr< IMediaDet > pDet;
	long width,height;
	double totalTime,dRate,position;
	Get_Frame(char* file);//read a video file and init
	HRESULT sF_position(double pst,char* save_dir);//save frame to disk at a special position
	HRESULT sF_all(char* save_dir,int stime,int etime);//save all frames to disk from stime to etime
	char* buf_position(double pst);//get frame at a special position and save it at mem
	char* pop_buf();//pop a frame in sequence
};

class bm_process{
public:
	int lhsv[9][10][5][5];//color space
	float hgram[9][250];//histogram
	int block_size[9];//each block's size
	unsigned char* a;
	float* hsv;
	int width,height;
	int bitcount;//bit per pixel(image type)
	bm_process(char* pbuf);//read rgb array from a bitmap buffer
	void change_hsv();//change rgb array to hsv array

	void readline(int h,int a[10][5][5],int b[10][5][5],int c[10][5][5]);
	void readall();

	void make_hgram();//make all 9 histogram
	bool jahsv(ahsv a);//judge if the ahsv is legal
	void make_ahsvl(ahsv* ahl,int hsv_space[10][5][5]);// color space to ahsvlist
	void sort_ahsvl(ahsv* ahl,int num);//sort ahsvlist
	void ahsvl_hgram(ahsv* ahl,float* hgram,int all_pixel);//ahsvlist to histogram
};

void MyFreeMediaType(AM_MEDIA_TYPE &mt);
void pixel_hsv(float R,float G,float B,float& H,float& S,float& V);
bool between(float a,float b,float c);
int lhsv_h(float h);
int lhsv_sv(float sv);
template <class T>
int Len(T& array);

