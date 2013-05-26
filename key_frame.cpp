#include "abc.h"

clock_t start, end;
clock_t dxx, bmp;

float key_frame::distance_hgram(float *a, float *b)
{
    float res = 0;
    for (int i = 0; i < 250; i++) {
        a[i] > b[i] ? res += b[i] : res += a[i];
    }
    return res;
}

float key_frame::distance(bm_process *a, bm_process *b)
{
    float res = 0;
    res += 0.075 * distance_hgram(a->hgram[0], b->hgram[0]);
    res += 0.075 * distance_hgram(a->hgram[2], b->hgram[2]);
    res += 0.075 * distance_hgram(a->hgram[6], b->hgram[6]);
    res += 0.075 * distance_hgram(a->hgram[8], b->hgram[8]);
    res += 0.125 * distance_hgram(a->hgram[1], b->hgram[1]);
    res += 0.125 * distance_hgram(a->hgram[3], b->hgram[3]);
    res += 0.125 * distance_hgram(a->hgram[5], b->hgram[5]);
    res += 0.125 * distance_hgram(a->hgram[7], b->hgram[7]);
    res += 0.2 * distance_hgram(a->hgram[4], b->hgram[4]);
    return res;
}

key_frame::key_frame(Get_Frame video, CmpWorker *_worker, char *sdir) :
    worker(_worker)
{
    this->dir = sdir;
    this->flist.reserve(3000);
    IplImage *pbuf;
    int i = 0;
    pbuf = video.pop();
    bm_process *prefra = new bm_process(pbuf, video.height, video.width);
    prefra->readallC();
    float preres = 0;
    bm_process *frame;
    bool last = false;
    dxx = bmp = 0;
    for (int i = 0; i < video.num_frame - 5; i += SFRA) {
        worker->output(QString("frame: %1").arg(i));
        pbuf = video.pop();
        if (!pbuf)
            break;
        start = clock();
        frame = new bm_process(pbuf, video.height, video.width);
        frame->readallC();
        end = clock();
        float res = distance(prefra, frame);
        worker->output(QString("distance is: %1\n").arg(res));
        if (res < SCENEB) {
            if (!last)
                this->flist.push_back(prefra);
            this->flist.push_back(frame);
            frame->iskframe = true;
            prefra->iskframe = true;
            last = true;
        } else {
            last = false;
        }
        if (!prefra->iskframe)
            delete prefra;
        preres = res;
        prefra = frame;
    }
    this->video_length = this->flist.size();
}

key_frame::~key_frame()
{
    for (int i = 0, sz = flist.size(); i < sz; ++ i) {
        delete flist[i];
    }
}

bool key_frame::cp_video(const key_frame &b)
{
    int res = 0;
    for (int i = 0; i < b.flist.size(); i++) {
        float pot = (float) i / b.flist.size();
        int st = pot * this->flist.size();
        float max = -10;
        for (int j = 0; j < 40; j++) {
            float temp = 0;
            if (st + j < this->flist.size()) {
                temp = distance(this->flist[st + j], b.flist[i]);
                temp > max ? max = temp : max;
            }
            if (st - j > 0) {
                temp = distance(this->flist[st - j], b.flist[i]);
                temp > max ? max = temp : max;
            }
        }
        if (max >= SCENEB)
            res++;
        worker->output(QString("the %1 %2 %3")
                       .arg(i)
                       .arg("frame of b video's distance is:")
                       .arg(max));
    }
    float rres = (float) res / b.flist.size();
    worker->output(QString("distance of two video: %1").arg(rres));
    if (rres > KFB)
        return true;
    return false;
}
