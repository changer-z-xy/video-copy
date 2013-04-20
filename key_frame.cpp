#include "abc.h"
#include <QDebug>
clock_t start,end;
clock_t dxx,bmp;

void shtime(clock_t start,clock_t end){
    //cout<<"Run time: "<<(double)(end-start)/CLOCKS_PER_SEC<<"s"<<endl;
    printf("Run time: %lf s\n",(double)(end-start)/CLOCKS_PER_SEC);
}

float distance_hgram(float a[250],float b[250]){
    float res=0;
    for(int i=0;i<250;i++) {
        a[i]>b[i]?res+=b[i]:res+=a[i];
        qDebug() << "zero res is: " << res;
    }
    return res;
}

float distance(bm_process* a,bm_process* b){
    float res=0;
    (res+=0.075*distance_hgram(a->hgram[0],b->hgram[0]));
    res+=0.075*distance_hgram(a->hgram[2],b->hgram[2]);
    res+=0.075*distance_hgram(a->hgram[6],b->hgram[6]);
    res+=0.075*distance_hgram(a->hgram[8],b->hgram[8]);
    res+=0.125*distance_hgram(a->hgram[1],b->hgram[1]);
    res+=0.125*distance_hgram(a->hgram[3],b->hgram[3]);
    res+=0.125*distance_hgram(a->hgram[5],b->hgram[5]);
    res+=0.125*distance_hgram(a->hgram[7],b->hgram[7]);
    res+=0.2*distance_hgram(a->hgram[4],b->hgram[4]);
    return res;
}

key_frame::key_frame( Get_Frame &video,char* sdir){
    this->dir=sdir;
    this->flist.reserve(3000);
    IplImage* pbuf;
    int i=0;
    pbuf=video.pop();
    bm_process* prefra=new bm_process(pbuf,video.height,video.width);
    prefra->readallC();
    float preres=0;
    bm_process* frame;
    bool last=false;
    dxx=bmp=0;
    for(int i=0;i<video.num_frame-5;i+=SFRA){
        pbuf=video.pop();
        start=clock();
        frame=new bm_process(pbuf,video.height,video.width);
        frame->readallC();
        end=clock();
//        shtime(start,end);
        float res=distance(prefra,frame);
        qDebug() << "second res is: " << res;
        if(res<SCENEB){
            qDebug() << "construct key_frame " << i;
            if(!last) this->flist.push_back(prefra);
            this->flist.push_back(frame);
            frame->iskframe=true;
            prefra->iskframe=true;
            last=true;
        }
        else last=false;
        if(!prefra->iskframe) delete prefra;
        preres=res;
        prefra=frame;
    }
    this->video_length=this->flist.size();
}

bool cp_video( const key_frame &a, const key_frame &b){
    int res=0;
    for(int i=0;i<b.flist.size();i++){
        float pot=(float)i/b.flist.size();
        int st=pot*a.flist.size();
        float max=-10;
        for(int j=0;j<40;j++){
            if(st+j<a.flist.size()){
                float temp=distance(a.flist[st+j],b.flist[i]);
                temp>max?max=temp:max;
            }
            if(st-j>0){
                float temp=distance(a.flist[st-j],b.flist[i]);
                temp>max?max=temp:max;
            }
        }
        if(max>=SCENEB) res++;
        qDebug() << i << ": " << res;
    }
    float rres=(float)res/b.flist.size();
    if(rres>KFB) return true;
    return false;
}
