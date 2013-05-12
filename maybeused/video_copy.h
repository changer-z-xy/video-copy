#include <iostream>
#include <windows.h>
#include <dshow.h>
#include <qedit.h>
#include <atlbase.h>
#include <stdlib.h>
#include <math.h>
#include <vector>

#define UNDEFINEDCOLOR -0.5
#define PI 3.1415926536
#define SCENEB 0.65
#define KFB 0.7
#define Sfra 24
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
	char* pBuffer;


	Get_Frame(char* file);//read a video file and init
	HRESULT sF_position(double pst,char* save_dir);//save frame to disk at a special position
	HRESULT sF_all(char* save_dir,int stime,int etime);//save all frames to disk from stime to etime
	char* buf_position(double pst);//get frame at a special position and save it at mem
	char* pop_buf();//pop a frame in sequence
	void delbuf();
};

class bm_process{//change a frame to a histogram
public:
	int lhsv[9][10][5][5];//color space
	float hgram[9][250];//histogram
	int block_size[9];//each block's size
	unsigned char* a;
	float* hsv;
	int width,height;
	int bitcount;//bit per pixel(image type)
	bool iskframe;//use at key_frame to decide is key_frame or not
	float pst;



	bm_process(char* pbuf,float pst);//read rgb array from a bitmap buffer
	bm_process(char* pbuf);
	~bm_process();
	void change_hsv();//change rgb array to hsv array

	void readline(int h,int a[10][5][5],int b[10][5][5],int c[10][5][5]);
	void readall();

	void make_hgram();//make all 9 histogram
	bool jahsv(ahsv a,int block);//judge if the ahsv is legal
	void make_ahsvl(ahsv* ahl,int hsv_space[10][5][5]);// color space to ahsvlist
	void sort_ahsvl(ahsv* ahl,int num);//sort ahsvlist
	void ahsvl_hgram(ahsv* ahl,float* hgram,int all_pixel);//ahsvlist to histogram
};

class key_frame{
public:
	vector<bm_process*> flist;//key frame list,represent a video
	int video_length;
	char* dir;


	key_frame(Get_Frame video,char* sdir);
};


void MyFreeMediaType(AM_MEDIA_TYPE &mt);
void pixel_hsv(float R,float G,float B,float& H,float& S,float& V);
bool between(float a,float b,float c);
int lhsv_h(float h);
int lhsv_sv(float sv);
template <class T>
int Len(T& array);
float distance(bm_process a,bm_process b);
float distance_hgram(float a[250],float b[250]);

bool cp_video(key_frame a,key_frame b);