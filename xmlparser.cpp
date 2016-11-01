#include "xmlparser.h"
#include <QApplication>

xmlParser::xmlParser()
{
    workoutTags << "week" << "date" << "time" << "sport" << "code" << "title" << "duration" << "distance" << "stress";
    metaTags << "id" << "week" << "name" << "fdw";
    contentTags << "id" << "week" << "swim" << "bike" << "run" << "strength" << "alternativ" << "summery";

    this->openXML();
}

void xmlParser::openXML()
{
    QFile workouts(QApplication::applicationDirPath() + QDir::separator() + "workout_schedule.xml");
    QDomDocument doc_workouts;

    if(!workouts.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "File workout_schedule.xml not open!";
    }
    else
    {
        if(!doc_workouts.setContent(&workouts))
        {
            qDebug() << "Workouts not loaded!";
        }
        workouts.close();
    }

    QFile weekMeta(QApplication::applicationDirPath() + QDir::separator() + "workout_phase_meta.xml");
    QDomDocument doc_week_meta;
    if(!weekMeta.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "File workout_phase_meta.xml not open!";
    }
    else
    {
        if(!doc_week_meta.setContent(&weekMeta))
        {
            qDebug() << "Workouts not loaded!";
        }
        weekMeta.close();
    }

    QFile weekContent(QApplication::applicationDirPath() + QDir::separator() + "workout_phase_content.xml");
    QDomDocument doc_week_content;
    if(!weekContent.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "File workout_phase_content.xml not open!";
    }
    else
    {
        if(!doc_week_content.setContent(&weekContent))
        {
            qDebug() << "Workouts not loaded!";
        }
        weekContent.close();
    }
    this->read_workout_values(doc_workouts);
    this->read_week_values(doc_week_meta,doc_week_content);
}

void xmlParser::read_workout_values(QDomDocument workouts)
{
    QDomElement root_workouts = workouts.firstChildElement();
        QDomNodeList workout_list;

        if(workouts.hasChildNodes())
        {
            workout_list = root_workouts.elementsByTagName("workout");
        }

        workout_schedule = new QStandardItemModel(workout_list.count(),9);

        for(int i = 0; i < workout_list.count(); ++i)
        {
            QDomElement workout_element;

            QDomNode workout_node = workout_list.at(i);

            workout_element = workout_node.toElement();
            for(int col = 0; col < workout_schedule->columnCount(); ++col)
            {
                workout_schedule->setData(workout_schedule->index(i,col,QModelIndex()),workout_element.attribute(workoutTags.at(col)));
            }
        }
        workout_schedule->sort(2);
}

void xmlParser::read_week_values(QDomDocument weekMeta, QDomDocument weekContent)
{
    QDomElement root_meta = weekMeta.firstChildElement();
        QDomElement root_content = weekContent.firstChildElement();
        QDomNodeList meta_list,content_list;
        meta_list = root_meta.elementsByTagName("phase");
        content_list = root_content.elementsByTagName("content");

        week_meta = new QStandardItemModel(meta_list.count(),4);
        week_content = new QStandardItemModel(content_list.count(),8);

        for(int i = 0; i < meta_list.count(); ++i)
        {
            QDomElement meta_element;
            QDomNode meta_node = meta_list.at(i);
            meta_element = meta_node.toElement();
            for(int col = 0; col < week_meta->columnCount(); ++col)
            {
                if(col == 0)
                {
                    week_meta->setData(week_meta->index(i,col,QModelIndex()),meta_element.attribute(metaTags.at(col)).toInt());
                }
                else
                {
                    week_meta->setData(week_meta->index(i,col,QModelIndex()),meta_element.attribute(metaTags.at(col)));
                }
            }

        }
        week_meta->sort(0);

        for(int i = 0; i < content_list.count(); ++i)
        {
            QDomElement content_element;
            QDomNode content_node = content_list.at(i);
            content_element = content_node.toElement();
            for(int col = 0; col < week_content->columnCount(); ++col)
            {
                if(col == 0)
                {
                    week_content->setData(week_content->index(i,col,QModelIndex()),content_element.attribute(contentTags.at(col)).toInt());
                }
                else
                {
                    week_content->setData(week_content->index(i,col,QModelIndex()),content_element.attribute(contentTags.at(col)));
                }
            }
        }
}



