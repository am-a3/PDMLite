#include "Bom.h"
#include <QDateTime>

Bom::Bom(QString part_id)
{
    this->part_id = part_id;
}

Bom::Bom(QString part_id, QMap<QString, BomEntry> bom)
{
    this->part_id = part_id;
    this->bom = bom;
}

void Bom::setPartId(QString part_id)
{
    this->part_id = part_id;
}

QMap<QString, BomEntry> Bom::getEntries()
{
    return this->bom;
}

void Bom::saveEntry(QString part_number, BomEntry entry)
{
    this->bom.insert(part_number, entry);

    entry.setSaved();
}

bool Bom::removeEntry(QString part_number)
{
    return this->bom.remove(part_number);
}

qint32 Bom::getEntryCount()
{
    return this->bom.size();
}

QString Bom::getPartId()
{
    return this->part_id;
}
