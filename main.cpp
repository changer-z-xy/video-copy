#include "C:\Documents and Settings\Administrator\My Documents\GitHub\video-copy\video_copy.h"



int main(int argc,char* argv[]){
	char* file="f:\\101次求婚2.mp4";
	char a[90]="c:\\csene\\mp4";
	Get_Frame abc(file);
	key_frame kfram(abc,a);
	

	file="f:\\101次求婚2.avi";
	char b[90]="c:\\csene\\avi";
	Get_Frame bcd(file);
	key_frame kfram2(bcd,b);
	
	cout<<"1,size: "<<kfram.flist.size()<<endl;
	cout<<"2,size: "<<kfram2.flist.size()<<endl;
	if(cp_video(kfram,kfram2)) cout<<"true"<<endl;
	else cout<<"false"<<endl;

	return 0;
}