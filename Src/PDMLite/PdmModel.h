#ifndef PDMMODEL_H
#define PDMMODEL_H

#include "DataModels.h"
#include "DbManager.h"

typedef enum PdmState_t {
    PDM_IDLE = 0,
    PDM_ADD_NEW_PART,
    PDM_EDIT_EXISTING_PART,
    PDM_ADD_NEW_MANUFACTURING_DATA,
    PDM_EDIT_MANUFACTURING_DATA,
    PDM_ADD_NEW_BOM_ENTRY,
    PDM_EDIT_EXISTING_BOM_ENTRY
} PdmState_t;

class PdmModel
{
public:
    PdmModel();
    std::vector<Part>* getPartOverview(qint32 part_count);

    Part* setCurrentPart(QString proprietary_id);
    Part* createCurrentPart();
    Part* getCurrentPart();
    bool saveCurrentPart();

    PdmState_t getPdmState();
    void setPdmState(PdmState_t state);

    qint32 getPartOverviewEntryCount();

private:
    DbManager db_manager;
    std::vector<Part> parts_overview;
    Part current_part;
    PdmState_t pdm_state;

    qint32 part_overview_entry_count;
};

#endif // PDMMODEL_H
