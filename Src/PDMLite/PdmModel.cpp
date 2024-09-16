#include "PdmModel.h"

PdmModel::PdmModel()
    :db_manager("D:\\Projects\\PDMLite\\Src\\PDMLite\\pdm_db.sqlite3"), current_part("dev")
{
    this->pdm_state = PDM_IDLE;
    this->part_overview_entry_count = 10;
}

std::vector<Part>* PdmModel::getPartOverview(qint32 part_count)
{
    this->parts_overview.clear();

    db_manager.queryAllParts(this->parts_overview, part_count);

    return &this->parts_overview;
}

Part* PdmModel::setCurrentPart(QString proprietary_id)
{
    this->current_part = db_manager.queryPartByProprietaryId(proprietary_id);
    return &this->current_part;
}

Part* PdmModel::createCurrentPart()
{
    this->current_part.clearParameters("dev");

    return &this->current_part;
}

Part* PdmModel::getCurrentPart()
{
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

qint32 PdmModel::getPartOverviewEntryCount()
{
    return this->part_overview_entry_count;
}
