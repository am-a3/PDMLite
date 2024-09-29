#ifndef BOM_H
#define BOM_H

#include <QString>
#include <QDateTime>
#include "BomEntry.h"

class Bom
{
public:
    Bom(QString part_id);
    Bom(QString part_id, QMap<QString, BomEntry> bom);

    QMap<QString, BomEntry> getEntries(); //TODO> need to implement iterator, to hide bom map
    void saveEntry(QString part_number, BomEntry entry);
    bool removeEntry(QString part_number);
    qint32 getEntryCount();
    void setPartId(QString part_id);
    QString getPartId();

private:
    QString part_id;
    QMap<QString, BomEntry> bom;
};

#endif // BOM_H
