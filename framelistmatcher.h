#ifndef FRAMELISTMATCHER_H
#define FRAMELISTMATCHER_H

#include <vector>

#include <QDebug>
#include <QDir>

#include "abc.h"
#include "cmpworker.h"

extern const float alpha;
extern const float THRESHOLD_PATH;

struct GraphNode {
    float sim;
    int i;
    int j;
    int ti;
    int tj;
    int path_length;
    int path_next;
    std::vector<cv::DMatch> matches;
};

struct RecStNode {
    int id;
    int next;
};

class FrameListMatcher
{
public:
    FrameListMatcher(const std::vector< bm_process* >& kfla,
                     const QString& fa,
                     const std::vector< bm_process* >& kflb,
                     const QString& fb,
                     CmpWorker *_worker);
    bool check(int i, int j);
    float similaraty(GraphNode &sim_frame);
    std::vector<int> longest_path(int i);
    void solve();
    bool isSimilar();
    const std::vector< std::vector<int> >& get_paths();
    const std::vector<float>& get_sim_paths();
private:
    QString fa;
    QString fb;
    void init_sift();
    void init_sim();
    void init_next();
    void search_paths();
    void calc_sim_paths();
    const std::vector< bm_process* >& kfla;
    const std::vector< bm_process* >& kflb;
    std::vector<GraphNode> result_graph;
    std::vector< std::vector<int> > paths;
    std::vector<float> sim_paths;
    std::vector<bool> isVisited;
    std::vector<cv::Mat> descriptor_a;
    std::vector<cv::Mat> descriptor_b;
    std::vector< std::vector<cv::KeyPoint> > keypoints_a;
    std::vector< std::vector<cv::KeyPoint> > keypoints_b;
    CmpWorker *worker;
    int k;
    int n;
};

#endif // FRAMELISTMATCHER_H
