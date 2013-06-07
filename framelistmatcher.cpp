#include "framelistmatcher.h"

const float alpha = 0.05;
const float THRESHOLD_PATH = 0.8;
const int THRESHOLD_TIME = 20000;

bool compare_desc_func(const GraphNode &a, const GraphNode &b)
{
    return a.sim > b.sim;
}

FrameListMatcher::FrameListMatcher(const std::vector <bm_process *> &kfla, const QString &fa,
                                   const std::vector <bm_process *> &kflb, const QString &fb,
                                   CmpWorker *worker)
    : worker(worker), kfla(kfla), kflb(kflb), fa(fa), fb(fb)
{
    worker->output(QString("init start"));
    n = kfla.size();
    k = n * alpha;
    k = k > 0 ? k : 1;
    isVisited.resize(k * n, false);
    result_graph.resize(k * n);

    clock_t start = clock();
    init_sift();
    qDebug() << "init_sift() used: " << clock() - start;
    start = clock();
    init_sim();
    qDebug() << "init_sim() used: " << clock() - start;
    start = clock();
    init_next();
    qDebug() << "init_next() used: " << clock() - start;

    worker->output(QString("init end"));
}

void FrameListMatcher::init_sift()
{
    descriptor_a.resize(kfla.size());
    descriptor_b.resize(kflb.size());
    keypoints_a.resize(kfla.size());
    keypoints_b.resize(kflb.size());

    cv::SIFT sift;
    IplImage *grayimg = NULL;
    for (int i = 0; i < kfla.size(); ++i) {
        grayimg = cvCreateImage(cvGetSize(kfla[i]->cvp), IPL_DEPTH_8U, 1);
        cvCvtColor(kfla[i]->cvp, grayimg, CV_BGR2GRAY);
        cv::Mat mtxa(grayimg);
        sift(mtxa, cv::Mat(), keypoints_a[i], descriptor_a[i]);
        cvReleaseImage(&grayimg);
        worker->output(QString("sift(kfla[%1]) done").arg(i));
    }
    for (int i = 0; i < kflb.size(); ++i) {
        grayimg = cvCreateImage(cvGetSize(kflb[i]->cvp), IPL_DEPTH_8U, 1);
        cvCvtColor(kflb[i]->cvp, grayimg, CV_BGR2GRAY);
        cv::Mat mtxb(grayimg);
        sift(mtxb, cv::Mat(), keypoints_b[i], descriptor_b[i]);
        cvReleaseImage(&grayimg);
        worker->output(QString("sift(kflb[%1]) done").arg(i));
    }
}

void FrameListMatcher::init_sim()
{
    for (int i = 0; i < kfla.size(); ++i) {
        std::vector<GraphNode> sim_frame(kflb.size());
        for (int j = 0; j < kflb.size(); ++j) {
            sim_frame[j].i = i;
            sim_frame[j].j = j;
            sim_frame[j].ti = kfla[i]->time_pos;
            sim_frame[j].tj = kflb[j]->time_pos;
            sim_frame[j].sim = similaraty(sim_frame[j]);
            worker->output(QString("src kframe %1, target kframe %2, sim is: %3")
                    .arg(i).arg(j).arg(sim_frame[j].sim));
        }
        std::sort(sim_frame.begin(), sim_frame.end(), compare_desc_func);
        sim_frame.resize(k);
        for (int j = 0; j < k; ++j)
            result_graph[i * k + j] = sim_frame[j];
    }
}

void FrameListMatcher::init_next()
{
    for (int i = k * (n - 1), sz = k * n; i < sz; ++i) {
        result_graph[i].path_next = -1;
        result_graph[i].path_length = 0;
    }
    for (int i = n - 2; i >= 0; --i) {
        for (int j = k - 1; j >= 0; --j) {
            result_graph[i * k + j].path_next = -1;
            result_graph[i * k + j].path_length = 0;
            for (int m = k - 1; m >= 0; --m) {
                if (check(i * k + j, (i + 1) * k + m) && result_graph[i * k + j].path_length <= result_graph[(i + 1) * k + m].path_length) {
                    result_graph[i * k + j].path_length = result_graph[(i + 1) * k + m].path_length + 1;
                    result_graph[i * k + j].path_next = (i + 1) * k + m;
                }
            }
        }
    }
}

float FrameListMatcher::similaraty(GraphNode &sim_frame)
{
    cv::BFMatcher matcher = cv::BFMatcher(4, true);
    int i = sim_frame.i;
    int j = sim_frame.j;
    matcher.match(descriptor_a[i], descriptor_b[j], sim_frame.matches);
    worker->output(QString("matches.size() is: %1, keypoints_b.size() is: %2")
                   .arg(sim_frame.matches.size()).arg(keypoints_b[j].size()));
    // fa是查询视频的帧，也就是可能被修改了的视频，所以应除以视频的帧fb的关键点数量
    float ans = (float)(sim_frame.matches.size()) / (keypoints_a[i].size() + keypoints_b[j].size()) * 2;
    return ans;// 0 ~ 1
}

void FrameListMatcher::solve()
{
    worker->output("solve() start");
    search_paths();
    calc_sim_paths();
    worker->output("solve() end");
}

void FrameListMatcher::search_paths()
{
    for (int i = 0; i < n; ) {
        int ik = i * k;
        int tmp = ik;
        for (int j = 0; j < k; ++j) {
            if (result_graph[ik + j].path_length > result_graph[tmp].path_length)
                tmp = ik + j;
        }
        std::vector<int> path;
        path.reserve(result_graph[tmp].path_length + 1);
        while (tmp != -1) {
            path.push_back(tmp);
            int ia = result_graph[tmp].i;
            int ib = result_graph[tmp].j;
            cv::Mat imga(kfla[ia]->cvp);
            cv::Mat imgb(kflb[ib]->cvp);
            cv::Mat imgMatches;
            worker->output("drawing matches");
            cv::drawMatches(imga, keypoints_a[ia], imgb, keypoints_b[ib],
                            result_graph[tmp].matches, imgMatches);
            QDir dir(".");
            if (!dir.exists("result"))
                dir.mkdir("result");
            QString fn = QString("result/%1_%2.jpg").arg(ia).arg(ib);
            worker->output(fn);
            cv::imwrite(fn.toLocal8Bit().data(), imgMatches);
            worker->output("drawing done");
            tmp = result_graph[tmp].path_next;
        }
        paths.push_back(path);
        i += path.size();
    }
}

void FrameListMatcher::calc_sim_paths()
{
    sim_paths.resize(paths.size());
    for (size_t i = 0; i < paths.size(); ++i) {
        float tmp_sim = 0;
        for (size_t j = 0; j < paths[i].size(); ++j)
            tmp_sim += result_graph[paths[i][j]].sim;
        tmp_sim /= paths[i].size();
        tmp_sim *= log(paths[i].size() + 1);
        sim_paths[i] = tmp_sim;
        worker->output(QString("sim_paths[%1] is %2").arg(i).arg(sim_paths[i]));
    }
}

bool FrameListMatcher::isSimilar()
{
    for (size_t i = 0; i < sim_paths.size(); ++i) {
        if (sim_paths[i] > THRESHOLD_PATH) {
            worker->output(QString("sim_paths[%1] is: %2").arg(i).arg(sim_paths[i]));
            return true;
        }
    }
    return false;
}

bool FrameListMatcher::check(int i, int j)
{
    if ((result_graph[i].i - result_graph[j].i) *
            (result_graph[i].j - result_graph[j].j) <= 0)
        return false;
    if (std::max(std::abs(result_graph[i].ti - result_graph[j].ti),
                 std::abs(result_graph[i].tj - result_graph[j].tj)) >= THRESHOLD_TIME)
        return false;
    return true;
}

const std::vector< std::vector<int> >& FrameListMatcher::get_paths()
{
    return paths;
}

const std::vector<float>& FrameListMatcher::get_sim_paths()
{
    return sim_paths;
}
