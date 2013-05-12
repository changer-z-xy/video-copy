#ifndef MPLAYERWIDGET_H
#define MPLAYERWIDGET_H

#include <QFrame>
#include <QProcess>
#include <QPainter>
#include <QDebug>
#include <QHBoxLayout>
#include <QFileDialog>

#include "customtoolbutton.h"

extern const QString MPLAYER_PATH;

class MPlayerWidget : public QFrame
{
    Q_OBJECT
public:
    explicit MPlayerWidget(QWidget *parent = 0);
    ~MPlayerWidget();
    QProcess *getMPProcess();
    const QString &getFilePath();
    void setFilePath(const QString &filePath);
    void setFilePath();
protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
signals:

public slots:
    void pause();
    void stop();
    void frame_step();
    void volume( double vol, int dir );
    void load();
private:
    QProcess *mpProcess;
    QWidget *screen;
    QString file;
    CustomToolButton *loadButton;
    CustomToolButton *pauseButton;
    CustomToolButton *stopButton;
    bool mouseIsOnScreen;
    int state;
};

#endif // MPLAYERWIDGET_H
