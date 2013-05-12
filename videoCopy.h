#ifndef VIDEOCOPY_H
#define VIDEOCOPY_H

#include <QApplication>

#include "abc.h"
#include "bm_process.h"
#include "get_frame.h"
#include "key_frame.h"

#include "cmpoutputwidget.h"
#include "cmpevent.h"
#include "cmpconsignor.h"
#include "cmppoolmanager.h"
#include "contentpage.h"
#include "customcontentwidget.h"
#include "custommainwidget.h"
#include "customstatusbar.h"
#include "customtitlebar.h"
#include "customtoolbar.h"
#include "customtoolbutton.h"
#include "customwebpage.h"
#include "customwidget.h"
#include "mplayerwidget.h"

extern const int MinWidth;
extern const int MinHeight;
extern const int TITLEBAR_HEIGHT;
extern const int TOOLBAR_HEIGHT;
extern const int STATUSBAR_HEIGHT;
extern const QString MPLAYER_PATH;
extern const QEvent::Type CmpTaskEventType;//QEvent::User
extern const QEvent::Type CmpOutputEventType;//QEvent::User + 1
extern const int CmpPoolSize;

#endif // VIDEOCOPY_H
