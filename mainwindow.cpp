#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    parser = new xmlParser();
    xmlTags.insert(0,"-");
    xmlTags.insert(1,"Schedule");
    xmlTags.insert(2,"Meta");
    xmlTags.insert(3,"Content");
    //xmlTags.insert(4,"xxx");

    for(int i = 0; i < xmlTags.count(); ++i)
    {
        ui->comboBox_xml->addItem(xmlTags.value(i));
    }
    xmlmodel = new QStandardItemModel();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_comboBox_xml_activated(int value)
{
    QModelIndex modelindex;

    qDebug() << value;

    if(xmlmodel->rowCount() > 0)
    {
        xmlmodel->clear();
    }
    if(value == 1)
    {
        modelptr = parser->workout_schedule;
    }
    if(value == 2)
    {
        modelptr = parser->week_meta;
    }
    if(value == 3)
    {
        modelptr = parser->week_content;
    }

    xmlmodel->setRowCount(modelptr->rowCount());
    xmlmodel->setColumnCount(modelptr->columnCount());

    for(int row = 0; row < modelptr->rowCount(); ++row)
    {
        for(int col = 0; col < modelptr->columnCount(); ++col)
        {
            modelindex = modelptr->index(row,col,QModelIndex());
            xmlmodel->setData(xmlmodel->index(row,col,QModelIndex()),modelptr->data(modelindex));
        }
    }
    ui->tableView_xml->setModel(xmlmodel);

}
