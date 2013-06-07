#include "mplayerwidget.h"

const QString MPLAYER_PATH = "mplayer/mplayer.exe";

MPlayerWidget::MPlayerWidget(QWidget *_parent) :
    QFrame(_parent)
{
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setMouseTracking(true);

    state = 0;
    parent = _parent;
    mpProcess = new QProcess(this);
    screen = new QWidget(this);
    loadButton = new CustomToolButton(":/img/open.png",
                                      "",
                                      Qt::ToolButtonIconOnly,
                                      2,
                                      this);
    pauseButton = new CustomToolButton(":/img/play.png",
                                       "",
                                       Qt::ToolButtonIconOnly,
                                       2,
                                       this);
    stopButton = new CustomToolButton(":/img/stop.png",
                                      "",
                                      Qt::ToolButtonIconOnly,
                                      2,
                                      this);

    connect(loadButton, SIGNAL(clicked()),
            this, SLOT(load()));
    connect(pauseButton, SIGNAL(clicked()),
            this, SLOT(pause()));
    connect(stopButton, SIGNAL(clicked()),
            this, SLOT(stop()));

    QHBoxLayout *buttonLayout = new QHBoxLayout(this);
    buttonLayout->addWidget(loadButton);
    buttonLayout->addWidget(pauseButton);
    buttonLayout->addWidget(stopButton);
    buttonLayout->setAlignment(Qt::AlignHCenter);

}

MPlayerWidget::~MPlayerWidget()
{
    if ( mpProcess->state() == QProcess::Running ) {
        mpProcess->write( "quit\n" );
    }
    mpProcess->waitForFinished();
}

QProcess* MPlayerWidget::getMPProcess()
{
    return mpProcess;
}

void MPlayerWidget::pause()
{
    if ( mpProcess->state() == QProcess::Running )
        mpProcess->write( "pause\n" );
}

void MPlayerWidget::stop()
{
    if ( mpProcess->state() == QProcess::Running )
        mpProcess->write( "stop\n" );
}

void MPlayerWidget::setFilePath()
{
    file = QFileDialog::getOpenFileName(parent, "打开视频", ".", tr("Avi 视频( *.avi )"));
}

void MPlayerWidget::setFilePath(const QString &filePath)
{
    file = filePath;
}

void MPlayerWidget::load()
{
    setFilePath();
    if ( mpProcess->state() == QProcess::Running ) {
        QString cmd = "loadfile " + file + "\n";
        mpProcess->write( cmd.toLocal8Bit() );
        mpProcess->write("pause\n");
    } else if ( mpProcess->state() == QProcess::NotRunning ) {
        QStringList argList;
        argList << "-slave" << "-quiet";
        argList << "-wid" << QString::number(screen->winId());
        argList << "-nosound";
        argList << file;
        mpProcess->start( MPLAYER_PATH, argList );
        mpProcess->write( "pause\n" );
        state = 1;
    }
}

void MPlayerWidget::volume( double vol, int dir )
{
    if ( mpProcess->state() == QProcess::Running ) {
        QString cmd = "volume " + QString::number( vol ) +
                QString::number( dir ) + "\n";
        mpProcess->write( cmd.toLocal8Bit() );
    }
}

void MPlayerWidget::frame_step()
{
    if ( mpProcess->state() == QProcess::Running )
        mpProcess->write( "frame_step\n" );
}

const QString& MPlayerWidget::getFilePath()
{
    return file;
}

void MPlayerWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QLinearGradient gradient(rect().topLeft(), rect().bottomRight());
    gradient.setColorAt(0, QColor(0, 0, 0, 1));
    gradient.setColorAt(1, QColor(0, 0, 0, 1));
    QBrush brush(Qt::black);
    painter.setPen(QPen(Qt::NoBrush, 1));
    painter.setBrush(brush);
    painter.drawRect(rect());
    QFrame::paintEvent(event);
}

void MPlayerWidget::resizeEvent(QResizeEvent *event)
{
    screen->resize(size());
    QFrame::resizeEvent(event);
}

void MPlayerWidget::enterEvent(QEvent *event)
{
    mouseIsOnScreen = true;
    loadButton->setVisible(true);
    pauseButton->setVisible(true);
    stopButton->setVisible(true);
    QFrame::enterEvent(event);
}

void MPlayerWidget::leaveEvent(QEvent *event)
{
    mouseIsOnScreen = false;
    loadButton->setVisible(false);
    pauseButton->setVisible(false);
    stopButton->setVisible(false);
    QFrame::leaveEvent(event);
}
