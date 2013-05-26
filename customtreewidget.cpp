#include "customtreewidget.h"

CustomTreeWidget::CustomTreeWidget(CmpPoolManager *_pm, QWidget *parent) :
    QWidget(parent)
{
    tw = new QTreeWidget(this);
    btnAdd = new QPushButton("添加", this);
    btnRemove = new QPushButton("删除", this);
    btnCompare = new QPushButton("比较", this);
    pm = _pm;
    consignor = new CmpConsignor(pm);
    count = 0;

    QStringList headers;
    headers << "源视频" << "目标视频" << "结果";
    tw->setHeaderLabels(headers);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(tw);
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(btnAdd);
    btnLayout->addWidget(btnRemove);
    btnLayout->addWidget(btnCompare);
    mainLayout->addLayout(btnLayout);

    connect(btnAdd, SIGNAL(clicked()),
            this, SLOT(insertItem()));
    connect(btnRemove, SIGNAL(clicked()),
            this, SLOT(deleteItem()));
    connect(btnCompare, SIGNAL(clicked()),
            this, SLOT(compareItems()));
    connect(consignor, SIGNAL(cmpEnd(int,bool)),
            this, SLOT(showAns(int,bool)));
}

void CustomTreeWidget::insertItem()
{
    QStringList sl = QFileDialog::getOpenFileNames(this, "打开文件对", "", "Avi 视频( *.avi )");
    if (sl.count() == 1)
        sl << sl.at(0);
    if (sl.count() == 2)
        new QTreeWidgetItem(tw, sl);
}

void CustomTreeWidget::deleteItem()
{
    if (tw->topLevelItemCount() > 0) {
        tw->takeTopLevelItem(tw->currentIndex().row());
    }
}

void CustomTreeWidget::compareItems()
{
    btnAdd->setDisabled(true);
    btnRemove->setDisabled(true);
    btnCompare->setDisabled(true);

    for (int i = 0, sz = tw->topLevelItemCount(); i < sz; ++i) {
        QTreeWidgetItem *tmp = tw->topLevelItem(i);
        consignor->addTask(tmp->text(0), tmp->text(1), false, i);
        qDebug() << "comparing " << i << "th item";
        qDebug() << tmp->text(0) << " " << tmp->text(1);
    }
}

void CustomTreeWidget::showAns(int _taskNo, bool _ans)
{
    if (count++ >= tw->topLevelItemCount()) {
        btnAdd->setDisabled(false);
        btnRemove->setDisabled(false);
        btnCompare->setDisabled(false);
    }
    qDebug() << "taskNo is: " << _taskNo << " " << "ans is: " << _ans;
    tw->topLevelItem(_taskNo)->setText(2, _ans ? "相同" : "不相同");
}
