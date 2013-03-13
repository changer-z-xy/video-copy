#include "C:\Documents and Settings\Administrator\My Documents\GitHub\video-copy\video_copy.h"



int main(int argc,char* argv[]){
	char* file="f:\\ÁúÔóÂÜÀ­.avi";
	Get_Frame abc(file);
	
	char* sdir="c:\\csene";
	double t=146.0;
//	abc.sF_position(t,sdir);
	char* pBuffer=abc.buf_position(t);
	bm_process aabc(pBuffer);
	aabc.change_hsv(); 
	aabc.readall();
	aabc.make_hgram();

	return 0;
}