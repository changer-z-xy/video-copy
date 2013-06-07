#ifndef COPYDETECTION_H
#define COPYDETECTION_H

#include <QObject>
#include <cv.h>
#include <highgui.h>
#include <vector>
using namespace cv ;
using namespace std ;
class copydetection
{
public:
  copydetection() ;
  std::vector<int> gethist(IplImage* img) ;
  std::vector< vector<int> > gethistlist(char* filename) ;
  double getsimilar (IplImage* img1 , IplImage* img2) ;
  int getkfhistlist ( char *filename,
                      vector< vector<int> > &kfhlist );
  double getsimilar(char* file1 ,char* file2 ) ;
  double getsimilar (vector<int> &v1 , vector<int> &v2) ;

};

#endif // COPYDETECTION_H
