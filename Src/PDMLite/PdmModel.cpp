#include "PdmModel.h"

PdmModel::PdmModel()
    :db_manager("D:\\Projects\\PDMLite\\Src\\PDMLite\\pdm_db.sqlite3"), current_part("dev"), current_part_bom("")
{
    this->pdm_state = PDM_IDLE;
    this->new_bom_entry_active = false;

    this->active_part_bom_entry = NULL;
    this->active_part_bom_entry_part_id = "";
}

std::vector<Part>* PdmModel::getPartOverview(qint32 part_count)
{
    this->parts_overview.clear();

    db_manager.queryAllParts(this->parts_overview, part_count);

    return &this->parts_overview;
}

bool PdmModel::deletePart(QString proprietary_id)
{
    return db_manager.deletePartByProprietaryId(proprietary_id);
}

Part* PdmModel::setCurrentPart(QString proprietary_id)
{
    QMap<QString, BomEntry> entries;

    this->current_part = db_manager.queryPartByProprietaryId(proprietary_id);

    entries = db_manager.queryPartBom(proprietary_id);
    this->current_part_bom = Bom(proprietary_id, entries);

    return &this->current_part;
}

Part* PdmModel::createCurrentPart()
{
    this->current_part.resetParameters("dev");

    this->current_part_bom = Bom("");

    return &this->current_part;
}

Part* PdmModel::getCurrentPart()
{
    //this->current_part = db_manager.queryPartByProprietaryId(this->current_part.getProprietaryId()); //TODO: need to have refreshFromDb
    return &this->current_part;
}

bool PdmModel::saveCurrentPart()
{
    bool success = false;

    if (current_part.isNew()) {
        qDebug() << "Saving new part";
        success = db_manager.addPart(current_part);
        if (success) current_part.setSaved();
    }
    else
    {
        qDebug() << "Save current part";
        success = db_manager.updatePart(current_part);
    }

    if (success)
    {
        qDebug() << "Saving current part BOM";
        this->saveCurrentPartBom();
    }

    return success;
}

PdmState_t PdmModel::getPdmState()
{
    return this->pdm_state;
}

void PdmModel::setPdmState(PdmState_t state)
{
    this->pdm_state = state;
}

bool PdmModel::isNewBomEntryActive()
{
    return this->new_bom_entry_active;
}

void PdmModel::setNewBomEntryActive(bool state)
{
    this->new_bom_entry_active = state;
}

qint32 PdmModel::getPartOverviewEntryCount()
{
    return db_manager.queryPartsCount();
}

Bom* PdmModel::getCurrentPartBom()
{
    return &this->current_part_bom;
}

bool PdmModel::checkPartNumberExists(QString proprietary_id)
{
    return db_manager.queryPartProprietaryIdExists(proprietary_id);
}

bool PdmModel::saveCurrentPartBom()
{
    QMap<QString, BomEntry> entries = this->current_part_bom.getEntries();
    bool failed = false;

    for (auto it = entries.begin(); it != entries.end(); ++it)
    {
        if (!db_manager.savePartBomEntry(this->current_part_bom.getPartId(), it.key(), it.value()))
        {
            qDebug() << "Failed to save part BOM entry";
            failed = true;
        }
    }

    return !failed;
}

BomEntry* PdmModel::createActivePartBomEntry()
{
    if (this->active_part_bom_entry != NULL)
    {
        delete this->active_part_bom_entry;
    }

    this->active_part_bom_entry = new BomEntry("dev");
    this->active_part_bom_entry_part_id = "";

    return this->active_part_bom_entry;
}

BomEntry* PdmModel::getActivePartBomEntry()
{
    return this->active_part_bom_entry;
}

QString PdmModel::getActivePartBomEntryPartId()
{
    return this->active_part_bom_entry_part_id;
}

void PdmModel::setActivePartBomEntryPartId(QString value)
{
    this->active_part_bom_entry_part_id = value;
}
