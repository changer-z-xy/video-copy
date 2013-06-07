#include "abc.h"

void show_lhsv(int a[10][5][5])
{
    for (int h = 0; h < 10; h++)
        for (int s = 0; s < 5; s++)
            for (int v = 0; v < 5; v++) {
                std::cout << a[h][s][v] << " ";
            }
}

void init_lhsv(int a[10][5][5])
{
    for (int h = 0; h < 10; h++)
        for (int s = 0; s < 5; s++)
            for (int v = 0; v < 5; v++) {
                a[h][s][v] = 0;
            }
}

bm_process::~bm_process()
{
    cvReleaseImage(&cvp);
}

bm_process::bm_process(char *pbuf, float pst)
{
    BITMAPINFOHEADER *head = (BITMAPINFOHEADER *) pbuf;
    //save some info
    this->height = head->biHeight;
    this->width = head->biWidth;
    this->bitcount = head->biBitCount;
    this->iskframe = false;
    this->pst = pst;
    this->pbuf = (unsigned char *)(pbuf + sizeof(BITMAPINFOHEADER));
}

bm_process::bm_process(char *pbuf)
{
    BITMAPINFOHEADER *head = (BITMAPINFOHEADER *) pbuf;
    //save some info
    this->height = head->biHeight;
    this->width = head->biWidth;
    this->bitcount = head->biBitCount;
    this->iskframe = false;
    this->pbuf = (unsigned char *)(pbuf + sizeof(BITMAPINFOHEADER));
    int lineByte = (this->width * this->bitcount / 8 + 3) / 4 * 4;    //align to 4 times
}

bm_process::bm_process(IplImage *_cvp, int h, int w, int timePos)
{
    time_pos = timePos;

    this->height = h;
    this->width = w;
    this->bitcount = 24;
    this->iskframe = false;
    this->cvp = cvCreateImage(cvGetSize(_cvp), _cvp->depth, _cvp->nChannels);
    cvCopyImage(_cvp, cvp);
    this->pbuf = (unsigned char *)cvp->imageData;
    this->block_size[0] = this->block_size[2]
                      	= this->block_size[6]
                        = this->block_size[8]
                        = (3 * this->height / 11) * (3 * this->width / 11);
	this->block_size[1] = this->block_size[7]
                      	= (5 * this->width / 11) * (3 * this->height / 11);
	this->block_size[3] = this->block_size[5]
                      	= (3 * this->width / 11) * (5 * this->height / 11);
    this->block_size[4] = (5 * this->width / 11) * (5 * this->height / 11);
}

void bm_process::change_hsv()
{
}

//////color space
void bm_process::readall()
{
    int i = 0;
    int count = 0;
    int lineByte = (this->width * this->bitcount / 8 + 3) / 4 * 4;    //align to 4 times
    memset(this->lhsv, 0, sizeof(this->lhsv));
    for (i; i < this->height * 3 / 11 * this->width * 3; i += lineByte) {
        this->readline(i, this->lhsv[0], this->lhsv[1], this->lhsv[2]);
    }
    for (i; i < this->height * 8 / 11 * this->width * 3; i += lineByte) {
        this->readline(i, this->lhsv[3], this->lhsv[4], this->lhsv[5]);
    }
    for (i; i < this->height * 11 / 11 * this->width * 3; i += lineByte) {
        this->readline(i, this->lhsv[6], this->lhsv[7], this->lhsv[8]);
    }
}

void bm_process::readallC()
{
    //IplImage9
    //,readline
    //9,9
    int i = 0;
    int count = 0;
    int lineByte = this->cvp->widthStep;
    //    qDebug() << QString("this->hgram[i]) is: %1").arg(sizeof(this->hgram[0]));
    memset(this->hgram, 0, sizeof(this->hgram));
    for (i; i < this->height * 3 / 11 * this->width * 3; i += lineByte) {
        this->readlineR(i, this->hgram[0], this->hgram[1], this->hgram[2]);
    }
    for (int j = 0; j < 250; j++)
        this->hgram[0][j] /= this->block_size[0];
    for (int j = 0; j < 250; j++)
        this->hgram[1][j] /= this->block_size[1];
    for (int j = 0; j < 250; j++)
        this->hgram[2][j] /= this->block_size[2];
    for (i; i < this->height * 8 / 11 * this->width * 3; i += lineByte) {
        this->readlineR(i, this->hgram[3], this->hgram[4], this->hgram[5]);
    }
    for (int j = 0; j < 250; j++)
        this->hgram[3][j] /= this->block_size[3];
    for (int j = 0; j < 250; j++)
        this->hgram[4][j] /= this->block_size[4];
    for (int j = 0; j < 250; j++)
        this->hgram[5][j] /= this->block_size[5];
    for (i; i < this->height * 11 / 11 * this->width * 3; i += lineByte) {
        this->readlineR(i, this->hgram[6], this->hgram[7], this->hgram[8]);
    }
    for (int j = 0; j < 250; j++)
        this->hgram[6][j] /= this->block_size[6];
    for (int j = 0; j < 250; j++)
        this->hgram[7][j] /= this->block_size[7];
    for (int j = 0; j < 250; j++)
        this->hgram[8][j] /= this->block_size[8];
}

void bm_process::readline(int h, int a[10][5][5], int b[10][5][5], int c[10][5][5])
{
    int i = h;
    int base = h;
    for (i; i < this->width * 3 / 11 * 3 + base; i += 3) {
        float h, s, v;
        pixel_hsv(* (this->pbuf + i) / 255.0,
                  * (this->pbuf + i + 1) / 255.0, * (this->pbuf + i + 2) / 255.0, h, s, v);
        a[lhsv_h(h)][lhsv_sv(s)][lhsv_sv(v)]++;
    }
    for (i; i < this->width * 8 / 11 * 3 + base; i += 3) {
        float h, s, v;
        pixel_hsv(*(this->pbuf + i) / 255.0,
                  *(this->pbuf + i + 1) / 255.0, * (this->pbuf + i + 2) / 255.0, h, s, v);
        b[lhsv_h(h)][lhsv_sv(s)][lhsv_sv(v)]++;
    }
    for (i; i < this->width * 3 + base; i += 3) {
        float h, s, v;
        pixel_hsv(*(this->pbuf + i) / 255.0,
                  *(this->pbuf + i + 1) / 255.0, * (this->pbuf + i + 2) / 255.0, h, s, v);
        c[lhsv_h(h)][lhsv_sv(s)][lhsv_sv(v)]++;
    }
}

void bm_process::readlineR(int h, float a[250], float b[250], float c[250])
{
    //
    int i = h;
    int base = h;
    for (i; i < this->width * 3 / 11 * 3 + base; i += 3) {
        float h, s, v;
        pixel_hsv(*(this->pbuf + i + 2) / 255.0,
                  *(this->pbuf + i + 1) / 255.0,
                  *(this->pbuf + i) / 255.0, h, s, v);
        int temp = 25 * lhsv_h(h) + 5 * lhsv_sv(s) + lhsv_sv(v);
        a[temp]++;
    }
    for (i; i < this->width * 8 / 11 * 3 + base; i += 3) {
        float h, s, v;
        pixel_hsv(* (this->pbuf + i + 2) / 255.0,
                  * (this->pbuf + i + 1) / 255.0, * (this->pbuf + i) / 255.0, h, s, v);
        int temp = 25 * lhsv_h(h) + 5 * lhsv_sv(s) + lhsv_sv(v);
        b[temp]++;
    }
    for (i; i < this->width * 3 + base; i += 3) {
        float h, s, v;
        pixel_hsv(*(this->pbuf + i + 2) / 255.0,
                  *(this->pbuf + i + 1) / 255.0,
                  *(this->pbuf + i) / 255.0, h, s, v);
        int temp = 25 * lhsv_h(h) + 5 * lhsv_sv(s) + lhsv_sv(v);
        c[temp]++;
    }
}

/////////////color spaced  end

/////color object

void bm_process::make_hgram()    //make all 9 histogram
{
    for (int i = 0; i < 9; i++) {
        ahsv ahl[250];
        this->make_ahsvl(ahl, this->lhsv[i]);
        this->sort_ahsvl(ahl, 250);
        memset(this->hgram[i], 0, sizeof(this->hgram[i]));
        this->ahsvl_hgram(ahl, this->hgram[i], this->block_size[i]);
    }
}

bool bm_process::jahsv(ahsv a, int block)    //judge if the ahsv is legal
{
    int h = a.h;
    int s = a.s;
    int v = a.v;
    if (h - 1 >= 0 && this->lhsv[block][h - 1][s][v] < a.count * 0.2)
        return false;
    if (s - 1 >= 0 && this->lhsv[block][h][s - 1][v] < a.count * 0.2)
        return false;
    if (v - 1 >= 0 && this->lhsv[block][h][s][v - 1] < a.count * 0.2)
        return false;
    if (h + 1 < 10 && this->lhsv[block][h + 1][s][v] < a.count * 0.2)
        return false;
    if (s + 1 < 5 && this->lhsv[block][h][s + 1][v] < a.count * 0.2)
        return false;
    if (v + 1 < 5 && this->lhsv[block][h][s][v + 1] < a.count * 0.2)
        return false;
    return true;
}

void bm_process::make_ahsvl(ahsv *ahl, int hsv_space[10][5][5])     // color space to ahsvlist
{
    int c = 0;
    for (int h = 0; h < 10; h++)
        for (int s = 0; s < 5; s++)
            for (int v = 0; v < 5; v++) {
                ahl[c].count = hsv_space[h][s][v];
                ahl[c].h = h;
                ahl[c].s = s;
                ahl[c].v = v;
                c++;
            }
}

int cmp(const void *a, const void *b)
{
    return (* (ahsv *) b).count - (* (ahsv *) a).count;
}

void bm_process::sort_ahsvl(ahsv *ahl, int num)     //sort ahsvlist
{
    qsort(ahl, num, sizeof(ahsv), cmp);
}

void bm_process::ahsvl_hgram(ahsv *ahl, float *hgram, int all_pixel)     //ahsvlist to histogram
{
    //  cout<<"ahl[0]->count "<<ahl[0].count<<"  "<<"all_pixel "<<all_pixel<<endl;
    for (int i = 0; i < 100; i++) {
        int temp = ahl[i].h * 25 + ahl[i].s * 5 + ahl[i].v;
        hgram[temp] = ((float) ahl[i].count) / all_pixel;
        //      cout<<((float)ahl[i].count)/all_pixel<<" ";
    }
    //  getchar();
}

////color object end

bool between(float a, float b, float c)    //if a between b and c,true
{
    if (a >= b && a <= c)
        return true;
    return false;
}

int lhsv_h(float h)        //quantify h in hsv
{
    if (between(h, 0, 20))
        return 0;
    else if (between(h, 20, 40))
        return 1;
    else if (between(h, 20, 75))
        return 2;
    else if (between(h, 75, 100))
        return 3;
    else if (between(h, 100, 155))
        return 4;
    else if (between(h, 155, 190))
        return 5;
    else if (between(h, 190, 240))
        return 6;
    else if (between(h, 240, 270))
        return 7;
    else if (between(h, 270, 295))
        return 8;
    else
        return 9;
}

int lhsv_sv(float sv)        //quantify s and v in hsv
{
    if (between(sv, 0, 0.2))
        return 0;
    else if (between(sv, 0.2, 0.4))
        return 1;
    else if (between(sv, 0.4, 0.5))
        return 2;
    else if (between(sv, 0.5, 0.7))
        return 3;
    else if (between(sv, 0.7, 1))
        return 4;
}

void pixel_hsv(float R, float G, float B, float& H, float& S, float& V)
{
    float mmin, mmax, delta, tmp;
    tmp = __min(R, G);
    mmin = __min(tmp, B);
    tmp = __max(R, G);
    mmax = __max(tmp, B);
    V = mmax;        // v
    delta = mmax - mmin;
    if (mmax > 0.00001 || mmax < -0.00001)
        S = delta / mmax;    // s
    else {
        // r = g = b = 0 // s = 0, v is undefined
        S = 0;
        H = UNDEFINEDCOLOR;
        return;
    }
    if (delta < 0.00001 && delta > -0.00001) {
        H = 0;
        return;
    }
    if (R == mmax)
        H = (G - B) / delta;    // between yellow & magenta
    else if (G == mmax)
        H = 2 + (B - R) / delta;    // between cyan & yellow
    else
        H = 4 + (R - G) / delta;    // between magenta & cyan
    H *= 60;        // degrees
    if (H < -0.00001)
        H += 360;
}

template < class T > int Len(T& array)
{
    return (sizeof(array) / sizeof(array[0]));
}
