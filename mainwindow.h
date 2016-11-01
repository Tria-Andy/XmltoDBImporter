#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "xmlparser.h"
#include <QStandardItemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    void on_comboBox_xml_activated(int index);

private:
    Ui::MainWindow *ui;
    xmlParser *parser;
    QMap<int,QString> xmlTags;
    QStandardItemModel *xmlmodel,*modelptr;
};

#endif // MAINWINDOW_H
