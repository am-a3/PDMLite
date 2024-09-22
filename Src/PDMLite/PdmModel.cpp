#include "PdmModel.h"

PdmModel::PdmModel()
    :db_manager("D:\\Projects\\PDMLite\\Src\\PDMLite\\pdm_db.sqlite3"), current_part("dev")
{
    this->pdm_state = PDM_IDLE;
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
    this->current_part = db_manager.queryPartByProprietaryId(proprietary_id);
    return &this->current_part;
}

Part* PdmModel::createCurrentPart()
{
    this->current_part.resetParameters("dev");

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
    return db_manager.queryPartsCount();
}

bool PdmModel::checkPartNumberExists(QString proprietary_id)
{
    return db_manager.queryPartProprietaryIdExists(proprietary_id);
}
