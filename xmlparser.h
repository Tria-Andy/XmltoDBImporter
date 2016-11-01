#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QStandardItemModel>
#include <QtXml>

class xmlParser
{
public:
    xmlParser();
    QStandardItemModel *workout_schedule, *week_meta, *week_content;

private:

    QStringList workoutTags,metaTags,contentTags;

    void openXML();
    void read_workout_values(QDomDocument);
    void read_week_values(QDomDocument,QDomDocument);

};

#endif // XMLPARSER_H
