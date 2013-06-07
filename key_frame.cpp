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

key_frame::key_frame(Get_Frame video, CmpWorker *_worker, const QString &dir) :
    worker(_worker), dir(dir)
{
    this->dir = dir;
    this->flist.reserve(3000);
    IplImage *pbuf;
    int i = 0;
    pbuf = video.pop();
    int timepos = (int) cvGetCaptureProperty(video.cap, CV_CAP_PROP_POS_MSEC);
    bm_process *prefra = new bm_process(pbuf, video.height, video.width, timepos);
    prefra->readallC();
    float preres = 0;
    bm_process *frame;
    bool last = false;
    dxx = bmp = 0;
    for (int i = 0; i < video.num_frame - 5; i += SFRA) {
        worker->output(QString("frame: %1").arg(i));
        if (!(pbuf = video.pop()))
            break;
        timepos = (int) cvGetCaptureProperty(video.cap, CV_CAP_PROP_POS_MSEC);
        frame = new bm_process(pbuf, video.height, video.width, timepos);
        frame->readallC();
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
    clock_t start;
    start = clock();
    FrameListMatcher matcher(flist, dir, b.flist, b.dir, worker);
    qDebug() << "constructor used " << clock() - start << "ms";
    start = clock();
    matcher.solve();
    qDebug() << "solve used " << clock() - start << "ms";
    return matcher.isSimilar();
}
