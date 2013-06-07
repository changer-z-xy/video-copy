#include "copydetection.h"
#include "QDebug"

copydetection::copydetection()
{
}


vector<int> copydetection::gethist (IplImage *img){
  int  h , w ;
  h = img->height ;
  w = img->width ;

  vector<int> tmp(10) ;
  for ( int i = 0;i < h ;i ++)
    for ( int j = 0;j < w ; j ++)
      {
        CvScalar sca = cvGet2D(img,i,j) ;
        tmp[sca.val[0] / 30] ++ ;
        }
  return tmp ;
}

double copydetection::getsimilar (IplImage *img1, IplImage *img2){
    qDebug() << "img1 is: " << img1 << ", img2 is: " << img2;
  vector<int> h1(10) , h2(10) ;
  h1 = gethist(img1) ;
  h2 = gethist(img2) ;
  long long sum1 = 0 , sum2 = 0 , minsum = 0 ;
  for ( int i = 0;i < 10;i ++) {
      minsum += min(h1[i] , h2[i]);
      sum1 += h1[i];
      sum2 += h2[i];
      qDebug() << "h1[ " << i << " ] is: " << h1[ i ];
      qDebug() << "h2[ " << i << " ] is: " << h2[ i ];
  }
  qDebug() << "minsum is: " << minsum;
  qDebug() << "sum1 is: " << sum1 << ", sum2 is: " << sum2;
  return ( .0 + minsum ) / ( sum1 + sum2 + .0 ) * 2.0 ;
}

double copydetection::getsimilar (vector<int> &v1, vector<int> &v2){
  long long sum1 = 0 , sum2 = 0 , minsum = 0 ;
  for ( int i = 0;i < 10;i ++)
    for ( int j = 0;j < 10 ;j ++)
      {
      minsum += min(v1[i] ,v2[i] ) ;
      sum1 += v1[i] ;
      sum2 += v2[i] ;
      }
  return (.0 + minsum ) / ( sum1 + sum2 + .0) * 2.0 ;
}

vector<vector<int> >copydetection::gethistlist (char *filename){
  CvCapture* cap = 0 ;
  cap =  cvCreateFileCapture (filename) ;
  IplImage* frame  = cvQueryFrame (cap) ;
  vector< vector<int> > tmp ;
  tmp.push_back( gethist (frame)) ;
  while( (frame = cvQueryFrame (cap) )!= NULL){
      tmp.push_back(gethist(frame)) ;
    }
  return tmp ;
}

double copydetection::getsimilar (char *file1,char* file2){
  vector< vector<int> > hl1 , hl2 ;
  qDebug() << "file 1 started";
  if ( getkfhistlist( file1, hl1 ) == -1 )
      qDebug() << "file 1 failed";
  else
      qDebug() << "file 1 done";
  qDebug() << "file 2 started";
  if ( getkfhistlist( file2, hl1 ) == -1 )
      qDebug() << "file 2 failed";
  else
      qDebug() << "file 2 done";
  int n1 = hl1.size() , n2 = hl2.size() ;
  int sum = 0 ;
  for ( int i = 0;i < n1 ;i ++)
    for ( int j = 0;j < n2 ;j ++)
      if ( getsimilar (hl1[i] , hl2[i] ) > 0.8 ){
          sum ++ ;
          break ;
        }
  return ( sum + .0 ) / ( n1 + n2) ;
}

int copydetection::getkfhistlist (char *filename,
                                  vector< vector<int> > &kfhlist ){
    CvCapture* cap = cvCreateFileCapture (filename) ;
    const double fdistance = 0.8;
    if ( !cap )
        return -1;

    IplImage* now = cvQueryFrame (cap);
    IplImage* pre = new IplImage;
    memcpy( pre, now, sizeof(IplImage) );
    kfhlist.clear();
    int i = 0;
    while ( ( now = cvQueryFrame (cap) ) != NULL ){
        double sim = getsimilar (pre , now );
        qDebug() << "sim " << i++ << " is: " << sim;
        if ( sim < fdistance ) {
            kfhlist.push_back( gethist( pre ) );
            qDebug() << "kfhlist size is: " << kfhlist.size();
        }
        memcpy( pre, now, sizeof(IplImage) );
    }
    delete pre;
    return 0;
}
