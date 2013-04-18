#include "mplayerwidget.h"

MPlayerWidget::MPlayerWidget(QWidget *parent) :
    QWidget(parent)
{
    mpProcess = new QProcess( this );
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

void MPlayerWidget::setFilePath( const QString &filePath )
{
    file = filePath;
}

void MPlayerWidget::load()
{
    if ( mpProcess->state() == QProcess::Running ) {
        QString cmd = "loadfile " + file + "\n";
        mpProcess->write( cmd.toLocal8Bit() );
    } else if ( mpProcess->state() == QProcess::NotRunning ) {
        QStringList argList;
        argList << "-slave" << "-quiet";
        argList << "-wid" << QString::number( this->winId() );
        argList << file;
        mpProcess->start( MPLAYER_PATH, argList );
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
