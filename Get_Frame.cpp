
#include "C:\Documents and Settings\Administrator\My Documents\GitHub\video-copy\video_copy.h"


#pragma comment(lib,"strmiids.lib")
//void MyFreeMediaType(AM_MEDIA_TYPE &mt);




void Get_Frame::delbuf(){
	delete[] this->pBuffer;
}
char* Get_Frame::buf_position(double pst){
long size;
HRESULT hr = this->pDet->GetBitmapBits(pst, &size, 0, this->width, this->height);
if (SUCCEEDED(hr)) 
{
    this->pBuffer = new char[size];//allocate an area in heap
    if (!this->pBuffer){
		cout<<"error1"<<endl;
        return NULL;
	}
    try {
        hr = pDet->GetBitmapBits(pst, 0, this->pBuffer, width, height);
		/*
		int m;
		for(int i=0;i<1000;i++){
		m=*(pBuffer+i+sizeof(BITMAPINFOHEADER));
		printf("%2.2x ",m);
		if(i+1%16==0) cout<<endl;
		
	}*/
		if(FAILED(hr)) return NULL;
		return this->pBuffer;
    }
    catch (...) {
		cout<<"error2"<<endl;
        delete [] this->pBuffer;
		return NULL;
        throw;
    }

}
else{
	cout<<"cannot open file"<<endl;
	return  NULL;
}
}
char* Get_Frame::pop_buf(){
	if(this->position>this->totalTime){
		cout<<"this->position>this->totalTime"<<endl;
		return NULL;
	}
	else{
		this->position+=Sfra/this->dRate;
		char* pBuffer=this->buf_position(this->position);
		return pBuffer;
	}
}

HRESULT Get_Frame::sF_position(double pst,char* save_dir){//save file at special position
	char str[200];
	sprintf(str,"%s\\%5.5f.bmp",save_dir,pst);
	CComBSTR saveBSTR(str);
	// 将该帧保存为指定路径的位图文件
	cout<<"saving "<<str<<endl;
	HRESULT hr = pDet->WriteBitmapBits(pst, this->width, this->height, saveBSTR);
	if (FAILED(hr)){
		printf("error,saving,%d,%d,%d,%s\n",width,height,hr,str);
		return hr;}
}

HRESULT Get_Frame::sF_all(char* save_dir,int stime,int etime){//time(seconds),when etime=0,catch stime to the end of the video
	HRESULT hr;
	int startf=stime*this->dRate;//start frame
	int endf=0;//end frame
	if(etime==0) endf=this->totalTime*this->dRate;
	else endf=etime*this->dRate;

	if(endf>(this->totalTime*this->dRate)||endf<startf){
		cout<<"error stime or etime"<<endl;
		cout<<"total time:"<<this->totalTime<<endl;
		cout<<"dRate:"<<this->dRate<<endl;
		cout<<"startf:"<<startf<<endl;
		cout<<"endf:"<<endf<<endl;
		return E_FAIL;
	}

	for(int i=startf;i<endf;i++){
		double position=(double)(i/this->dRate);
		hr=this->sF_position(position,save_dir);
		if(FAILED(hr)) return hr;
	}
	return S_OK;
}

Get_Frame::Get_Frame(char* file){//initial
	this->position=0;
	char* m_editOpenDir=file;
	CoInitialize(NULL);

	HRESULT hr;
	hr = CoCreateInstance( CLSID_MediaDet, NULL, CLSCTX_INPROC_SERVER, 
		IID_IMediaDet, (void**) &this->pDet );
	if (FAILED(hr)){
		printf("error,CoCreateInstance\n");
		return;
		}
	
	// 将影片文件名转换成BSTR类型
	CComBSTR openBSTR(m_editOpenDir);
	// 设置IMediaDet接口的文件关联
	hr = this->pDet->put_Filename(openBSTR);
	if (FAILED(hr)){
		printf("error,put_Filename\n");
		return;
		}
	
	// 从影片中检索视频流和音频流
	long lStreams;
    hr = this->pDet->get_OutputStreams(&lStreams);
    if (FAILED(hr)){
		printf("error,get_OutputStreams\n");
		return;
		}
	
	// 取出影片的视频流，因为帧的信息是保存在视频流中的
	bool bFound = false;
	for (int i=0; i<lStreams;i++){
		GUID major_type;
		hr=this->pDet->put_CurrentStream(i);
		if (SUCCEEDED(hr))
			hr = this->pDet->get_StreamType(&major_type);
		if (FAILED(hr))
			break;
		if (major_type == MEDIATYPE_Video)
		{
			bFound = true;
			break;
		}
	}
	if (!bFound){
		printf("error,get_StreamType\n");
		return;
		}
	this->width = 0, this->height = 0; // 存储位图的宽和高（单位：象素）
    AM_MEDIA_TYPE mt;
    hr = this->pDet->get_StreamMediaType(&mt);
    if (SUCCEEDED(hr))
    {
        if ((mt.formattype == FORMAT_VideoInfo) && 
            (mt.cbFormat >= sizeof(VIDEOINFOHEADER)))
        {
			// 得到VIDEOINFOHEADER结构指针，VIDEOINFOHEADER结构包含一些与视频
			// 有关的信息，其中含有BITMAPINFORHEADER结构
            VIDEOINFOHEADER *pVih = (VIDEOINFOHEADER*)(mt.pbFormat);
            this->width = pVih->bmiHeader.biWidth;
            this->height = pVih->bmiHeader.biHeight;
        }
        else
            hr = VFW_E_INVALIDMEDIATYPE;
       MyFreeMediaType(mt); // 释放AM_MEDIA_TYPE结构
    }
    if (FAILED(hr)){
		printf("error,get_StreamMediaType\n");
		return;
		}
	this->pDet->get_FrameRate(&this->dRate);
	this->pDet->get_StreamLength(&this->totalTime);
}


void MyFreeMediaType(AM_MEDIA_TYPE &mt){
	if(mt.cbFormat!=0){
		CoTaskMemFree((PVOID)mt.pbFormat);
		mt.cbFormat=0;
		mt.pbFormat=NULL;
	}
	if(mt.pUnk!=NULL){
		mt.pUnk->Release();
		mt.pUnk=NULL;
	}
}

