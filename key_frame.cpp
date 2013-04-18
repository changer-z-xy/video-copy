#include "C:\Documents and Settings\Administrator\My Documents\GitHub\video-copy\video_copy.h"

float distance_hgram(float a[250],float b[250]){
	float res=0;
	for(int i=0;i<250;i++) a[i]>b[i]?res+=b[i]:res+=a[i];
	return res;
}

float distance(bm_process* a,bm_process* b){
	float res=0;
	res+=0.075*distance_hgram(a->hgram[0],b->hgram[0]);
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

key_frame::key_frame(Get_Frame video,char* sdir){
	this->dir=sdir;
	video.position=0;

	this->flist.reserve(3000);
	//this->tflist.reserve(500);
	char* pbuf;
	int i=0;
	pbuf=video.pop_buf();
	bm_process* prefra=new bm_process(pbuf,video.position);
	prefra->change_hsv();
	prefra->readall();
	prefra->make_hgram();
	delete[] pbuf;

	float preres=0;
	bm_process* frame;

	bool last=false;

	while(video.position<=video.totalTime){
		cout<<"frame: "<<i++<<endl;
		pbuf=video.pop_buf();
		frame=new bm_process(pbuf,video.position);
	
		delete[] pbuf;

		frame->change_hsv();
		frame->readall();
		frame->make_hgram();


		float res=distance(prefra,frame);

		cout<<"distance: "<<res<<endl;
		if(res<SCENEB){
			video.sF_position(video.position,this->dir);
			video.sF_position(video.position-Sfra/video.dRate,this->dir);
			if(!last) this->flist.push_back(prefra);//if last has included this frame then pass it 
			this->flist.push_back(frame);
			frame->iskframe=true;
			prefra->iskframe=true;
			last=true;
		//	getchar();
		}
		else last=false;
		if(!prefra->iskframe) delete prefra;
		
	//	video.position+=5/video.dRate;
		preres=res;
		
		prefra=frame;
	}
this->video_length=this->flist.size();
/*
for(i=0;i<this->flist.size();i++){
			float hgram=0;
			for(int j=0;j<9;j++)
				for(int k=0;k<250;k++)
					hgram+=this->flist[i]->hgram[j][k];
			cout<<hgram<<endl;
			getchar();
		}
		*/
}

bool cp_video(key_frame a,key_frame b){
	int res=0;
	for(int i=0;i<b.flist.size();i++){
		float pot=(float)i/b.flist.size();
		int st=pot*a.flist.size();
		float max=-10;
		for(int j=0;j<40;j++){
			if(st+j<a.flist.size()){
				float temp=distance(a.flist[st+j],b.flist[i]);
				temp>max?max=temp:max;
			//	cout<<"st+j: j="<<j<<"  temp="<<temp<<"----apst: "<<a.flist[st+j]->pst<<",bpst: "<<b.flist[i]->pst<<endl;
			}
			if(st-j>0){
				float temp=distance(a.flist[st-j],b.flist[i]);
				temp>max?max=temp:max;
			//	cout<<"st-j: j="<<j<<"  temp="<<temp<<"----apst: "<<a.flist[st-j]->pst<<",bpst: "<<b.flist[i]->pst<<endl;
			}
		}
		if(max>=SCENEB) res++;
		cout<<"the "<<i<<"frame of b video's distance is:"<<max<<endl;

		/*
		if(max<0.5){
			for(j=0;j<40;j++){
			if(st+j<a.flist.size()){
				float temp=distance(a.flist[st+j],b.flist[i]);
				temp>max?max=temp:max;
				cout<<"st+j: j="<<j<<"  temp="<<temp<<"----apst: "<<a.flist[st+j]->pst<<",bpst: "<<b.flist[i]->pst<<endl;
			}
			if(st-j>0){
				float temp=distance(a.flist[st-j],b.flist[i]);
				temp>max?max=temp:max;
				cout<<"st-j: j="<<j<<"  temp="<<temp<<"----apst: "<<a.flist[st-j]->pst<<",bpst: "<<b.flist[i]->pst<<endl;
			}
		}
		getchar();
		}
		*/

	}
	float rres=(float)res/b.flist.size();
	cout<<"distance of two video: "<<rres<<endl;
	if(rres>KFB) return true;
	return false;
}