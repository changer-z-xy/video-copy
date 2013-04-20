#ifndef BM_PROCESS_H
#define BM_PROCESS_H
#include <abc.h>

typedef struct ahsv{
    int h,s,v;
    int count;
} ahsv;
class bm_process
{
public:
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
    char* pbuf;
    IplImage* cvp;


    bm_process(IplImage* cvp,int h,int w);
    bm_process(char* pbuf,float pst);//read rgb array from a bitmap buffer
    bm_process(char* pbuf);
    ~bm_process();
    void change_hsv();//change rgb array to hsv array

    void readline(int h,int a[10][5][5],int b[10][5][5],int c[10][5][5]);
    void readlineR(int h,float a[250],float b[250],float c[250]);
    void readall();
    void readallC();

    void make_hgram();//make all 9 histogram
    bool jahsv(ahsv a,int block);//judge if the ahsv is legal
    void make_ahsvl(ahsv* ahl,int hsv_space[10][5][5]);// color space to ahsvlist
    void sort_ahsvl(ahsv* ahl,int num);//sort ahsvlist
    void ahsvl_hgram(ahsv* ahl,float* hgram,int all_pixel);//ahsvlist to histogram
};

#endif // BM_PROCESS_H
