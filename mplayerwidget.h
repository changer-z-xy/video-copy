#ifndef MPLAYERWIDGET_H
#define MPLAYERWIDGET_H

#include <QWidget>
#include <QProcess>
#include <QPainter>
#include <QDebug>

const QString MPLAYER_PATH = "mplayer/mplayer.exe";

class MPlayerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MPlayerWidget(QWidget *parent = 0);
    ~MPlayerWidget();
    QProcess *getMPProcess();
    const QString &getFilePath();
    void setFilePath( const QString &filePath );
    void paintEvent(QPaintEvent *event);
signals:

public slots:
    void pause();
    void stop();
    void frame_step();
    void volume( double vol, int dir );
    void load();
private:
    QProcess *mpProcess;
    QString file;
};

#endif // MPLAYERWIDGET_H
