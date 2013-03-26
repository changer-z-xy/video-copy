#include "C:\Documents and Settings\Administrator\My Documents\GitHub\video-copy\video_copy.h"


void show_lhsv(int a[10][5][5]){
	for(int h=0;h<10;h++)
		for(int s=0;s<5;s++)
			for(int v=0;v<5;v++)
			{
				cout<<a[h][s][v]<<" ";
			}
}
void init_lhsv(int a[10][5][5]){
	for(int h=0;h<10;h++)
		for(int s=0;s<5;s++)
			for(int v=0;v<5;v++)
			{
				a[h][s][v]=0;
			}
}

bm_process::~bm_process(){
	//
	//	delete[] this->hsv;
	//
}

bm_process::bm_process(char* pbuf,float pst){
	BITMAPINFOHEADER* head=(BITMAPINFOHEADER*)pbuf;
	//save some info
	this->height=head->biHeight;
	this->width=head->biWidth;
	this->bitcount=head->biBitCount;
	this->iskframe=false;
	this->pst=pst;

	int lineByte=(this->width*this->bitcount/8+3)/4*4;//align to 4 times

//
//	cout<<"allocate heap"<<endl;
//	cout<<this->width*this->height*3<<endl;
//

	this->a=new unsigned char[this->width*this->height*3];//allocate an array for storing pixel
	long total=0;
	pbuf+=sizeof(BITMAPINFOHEADER);//skip the bitmapinfoheader
	//scan mem and read bitmap
	unsigned char m;
	for(int i=0;i<this->height;i++){
		for(int j=0;j<this->width;j++){
			for(int k=0;k<3;k++){
				m=*(pbuf+i*lineByte+j*3+k);
			//	printf("%2.2x ",m);
				this->a[total++]=m;
			}
		}
	//	printf("-------------\n");
	//	getchar();
	}
//	delete[] pbuf; how to delete this buf?
}

bm_process::bm_process(char* pbuf){
	BITMAPINFOHEADER* head=(BITMAPINFOHEADER*)pbuf;
	//save some info
	this->height=head->biHeight;
	this->width=head->biWidth;
	this->bitcount=head->biBitCount;
	this->iskframe=false;

	int lineByte=(this->width*this->bitcount/8+3)/4*4;//align to 4 times

//
//	cout<<"allocate heap"<<endl;
//	cout<<this->width*this->height*3<<endl;
//

	this->a=new unsigned char[this->width*this->height*3];//allocate an array for storing pixel
	long total=0;
	pbuf+=sizeof(BITMAPINFOHEADER);//skip the bitmapinfoheader
	//scan mem and read bitmap
	unsigned char m;
	for(int i=0;i<this->height;i++){
		for(int j=0;j<this->width;j++){
			for(int k=0;k<3;k++){
				m=*(pbuf+i*lineByte+j*3+k);
			//	printf("%2.2x ",m);
				this->a[total++]=m;
			}
		}
	//	printf("-------------\n");
	//	getchar();
	}
//	delete[] pbuf; how to delete this buf?
}
void bm_process::change_hsv(){
	this->hsv=new float[this->width*this->height*3];
	if(this->hsv==NULL){
		cout<<"allocate mem error!!"<<endl;
		return;
	}
	float h,s,v;
	for(int i=0;i<this->width*this->height*3;i+=3){
		pixel_hsv(
			this->a[i]/255.0,
			this->a[i+1]/255.0,
			this->a[i+2]/255.0,
			h,s,v);
		this->hsv[i]=h;
		this->hsv[i+1]=s;
		this->hsv[i+2]=v;
/*
		printf("%4d %4d %4d\n",a[i],a[i+1],a[i+2]);
		printf("%4.4f %4.4f %4.4f\n",h,s,v);
		if(i%100==0) getchar();
*/
	}
	delete[] this->a;
}
//////color space
void bm_process::readall(){
	int i=0;
	int count=0;
	//for(int j=0;j<9;j++) init_lhsv(this->lhsv[i]);
	memset(this->lhsv,0,sizeof(this->lhsv));
	for(i;i<this->height*3/11*this->width*3;i+=this->width*3){
		this->readline(i,this->lhsv[0],this->lhsv[1],this->lhsv[2]);
	}
	for(i;i<this->height*8/11*this->width*3;i+=this->width*3){
		this->readline(i,this->lhsv[3],this->lhsv[4],this->lhsv[5]);
	}
	for(i;i<this->height*11/11*this->width*3;i+=this->width*3){
		this->readline(i,this->lhsv[6],this->lhsv[7],this->lhsv[8]);
	}
	/*
	for(i=0;i<9;i++)
	{
		show_lhsv(this->lhsv[i]);
		cout<<endl;
		getchar();
	}
	*/
}

void bm_process::readline(int h,int a[10][5][5],int b[10][5][5],int c[10][5][5]){
	int i=h;
	int base=h;
	for(i;i<this->width*3/11*3+base;i+=3){
		float h,s,v;
		h=this->hsv[i];
		s=this->hsv[i+1];
		v=this->hsv[i+2];
	//	cout<<"h:"<<h<<"  s:"<<s<<"  v:"<<v<<endl;
		a[lhsv_h(h)][lhsv_sv(s)][lhsv_sv(v)]++;
	}
	for(i;i<this->width*8/11*3+base;i+=3){
		float h,s,v;
		h=this->hsv[i];
		s=this->hsv[i+1];
		v=this->hsv[i+2];
		b[lhsv_h(h)][lhsv_sv(s)][lhsv_sv(v)]++;
	}

	for(i;i<this->width*3+base;i+=3){
		float h,s,v;
		h=this->hsv[i];
		s=this->hsv[i+1];
		v=this->hsv[i+2];
		c[lhsv_h(h)][lhsv_sv(s)][lhsv_sv(v)]++;
	}
}
/////////////color spaced  end

/////color object

void bm_process::make_hgram()//make all 9 histogram
{
	this->block_size[0]=this->block_size[2]=this->block_size[6]=this->block_size[8]=(3*this->height/11)*(3*this->width/11);
	this->block_size[1]=this->block_size[7]=(5*this->width/11)*(3*this->height/11);
	this->block_size[3]=this->block_size[5]=(3*this->width/11)*(5*this->height/11);
	this->block_size[4]=(5*this->width/11)*(5*this->height/11);

	for(int i=0;i<9;i++){
		ahsv ahl[250];
	//	cout<<"make_ahsvl"<<endl;
		this->make_ahsvl(ahl,this->lhsv[i]);
	//	cout<<"sort_ahsvl"<<endl;
		this->sort_ahsvl(ahl,250);
/*
		for(int l=0;l<250;l++) cout<<ahl[l].count<<" ";
		cout<<endl;
		getchar();
*/
		int j=0;
		//if judge little ahsv left
		/*
		cout<<"jahsv"<<endl;
		for(j;j<250;j++){
			if(!this->jahsv(ahl[j],i)) ahl[j].count=0;
		}
		cout<<"sort_ahsvl again"<<endl;
		this->sort_ahsvl(ahl,250);
		*/
		///

/*
		for(int l=0;l<250;l++) cout<<ahl[l].count<<" ";
		cout<<endl;
		getchar();
*/

		//expand to three point of color
		/*
		for(j=0;j<100;j++){
			int h=ahl[j].h-1;
			int s=ahl[j].s-1;
			int v=ahl[j].v-1;
			for(h;h<ahl[j].h+2;h++){
				if(h<0||h>9) continue;
				for(s;s<ahl[j].s+2;s++){
					if(s<0||s>4) continue;
					for(v;v<ahl[j].v+2;v++){
						if(v<0||v>4) continue;
						ahl[j].count+=this->lhsv[i][h][s][v];
					}
				}
			}
		}
		
		*/

/*
		for(int l=0;l<250;l++) cout<<ahl[l].count<<" ";
		cout<<endl;
		getchar();
*/

	//	cout<<"sort_ahsvl 100"<<endl;
//		this->sort_ahsvl(ahl,100);
	//	cout<<"ahsvl_hgram"<<"  sizeof(hgram[i] )"<<sizeof(this->hgram[i])<<endl;
		memset(this->hgram[i],0,sizeof(this->hgram[i]));
		this->ahsvl_hgram(ahl,this->hgram[i],this->block_size[i]);
	}

	delete[] this->hsv;
}
bool bm_process::jahsv(ahsv a,int block)//judge if the ahsv is legal
{
	int h=a.h;
	int s=a.s;
	int v=a.v;
	if(h-1>=0&&this->lhsv[block][h-1][s][v]<a.count*0.2) return false;
	if(s-1>=0&&this->lhsv[block][h][s-1][v]<a.count*0.2) return false;
	if(v-1>=0&&this->lhsv[block][h][s][v-1]<a.count*0.2) return false;
	if(h+1<10&&this->lhsv[block][h+1][s][v]<a.count*0.2) return false;
	if(s+1<5&&this->lhsv[block][h][s+1][v]<a.count*0.2) return false;
	if(v+1<5&&this->lhsv[block][h][s][v+1]<a.count*0.2) return false;
	/*
			int h=a.h-1;
			int s=a.s-1;
			int v=a.v-1;
			for(h;h<a.h+2;h++){
				if(h<0||h>9) continue;
				for(s;s<a.s+2;s++){
					if(s<0||s>4) continue;
					for(v;v<a.v+2;v++){
						if(v<0||v>4) continue;
						if(this->lhsv[block][h][s][v]<a.count*0.2) return false;
					}
				}
			}
			*/
return true;
}
void bm_process::make_ahsvl(ahsv* ahl,int hsv_space[10][5][5])// color space to ahsvlist
{
	int c=0;
	for(int h=0;h<10;h++)
		for(int s=0;s<5;s++)
			for(int v=0;v<5;v++){
				ahl[c].count=hsv_space[h][s][v];
				ahl[c].h=h;
				ahl[c].s=s;
				ahl[c].v=v;
				c++;
			}
}
int cmp(const void* a,const void* b){
	return (*(ahsv*)b).count-(*(ahsv*)a).count;
}
void bm_process::sort_ahsvl(ahsv* ahl,int num)//sort ahsvlist
{
	qsort(ahl,num,sizeof(ahsv),cmp);	
}
void bm_process::ahsvl_hgram(ahsv* ahl,float* hgram,int all_pixel)//ahsvlist to histogram
{
//	cout<<"ahl[0]->count "<<ahl[0].count<<"  "<<"all_pixel "<<all_pixel<<endl;
	for(int i=0;i<100;i++){
		int temp=ahl[i].h*25+ahl[i].s*5+ahl[i].v;
		hgram[temp]=((float)ahl[i].count)/all_pixel;
//		cout<<((float)ahl[i].count)/all_pixel<<" ";
	}
//	getchar();
}

////color object end

bool between(float a,float b,float c)//if a between b and c,true
{
		if(a>=b&&a<=c) return true;
		return false;
}

int lhsv_h(float h)//quantify h in hsv
{
	if(between(h,0,20)) return 0;
	else if(between(h,20,40)) return 1;
	else if(between(h,20,75)) return 2;
	else if(between(h,75,100)) return 3;
	else if(between(h,100,155)) return 4;
	else if(between(h,155,190)) return 5;
	else if(between(h,190,240)) return 6;
	else if(between(h,240,270)) return 7;
	else if(between(h,270,295)) return 8;
	else  return 9;
}

int lhsv_sv(float sv)//quantify s and v in hsv
{
	if(between(sv,0,0.2)) return 0;
	else if(between(sv,0.2,0.4)) return 1;
	else if(between(sv,0.4,0.5)) return 2;
	else if(between(sv,0.5,0.7)) return 3;
	else if(between(sv,0.7,1)) return 4;
}

void pixel_hsv(float R,float G,float B,float& H,float& S,float& V){
	float min, max, delta,tmp;
    tmp = min(R, G);
    min = min( tmp, B );
    tmp = max( R, G);
    max = max(tmp, B );
    V = max; // v
    delta = max - min;
    if( max > 0.00001 || max<-0.00001)
      S = delta / max; // s
    else
    {
       // r = g = b = 0 // s = 0, v is undefined
      S = 0;
      H = UNDEFINEDCOLOR;
      return;
    }
	if(delta<0.00001 && delta>-0.00001){
		H=0;
		return;
	}
    if( R == max )
        H = ( G - B ) / delta; // between yellow & magenta
   else if( G == max )
        H = 2 + ( B - R ) / delta; // between cyan & yellow
   else
        H = 4 + ( R - G ) / delta; // between magenta & cyan
    H *= 60; // degrees
    if( H < -0.00001 )
       H += 360;
}

template <class T>
int Len(T& array)
{
return (sizeof(array) / sizeof(array[0]));
}

