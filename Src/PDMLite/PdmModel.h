#ifndef PDMMODEL_H
#define PDMMODEL_H

#include "DataModels.h"
#include "DbManager.h"
#include "Bom.h"

typedef enum PdmState_t {
    PDM_IDLE = 0,
    PDM_ADD_NEW_PART,
    PDM_EDIT_EXISTING_PART,
} PdmState_t;

class PdmModel
{
public:
    PdmModel();
    std::vector<Part>* getPartOverview(qint32 part_count);
    bool deletePart(QString proprietary_id);

    Part* setCurrentPart(QString proprietary_id);
    Part* createCurrentPart();
    Part* getCurrentPart();
    bool saveCurrentPart();

    qint32 getPartOverviewEntryCount();

    Bom* getCurrentPartBom();
    BomEntry* createActivePartBomEntry();
    BomEntry* getActivePartBomEntry();
    QString getActivePartBomEntryPartId();
    void setActivePartBomEntryPartId(QString value);

    //State related:
    PdmState_t getPdmState();
    void setPdmState(PdmState_t state);

    bool isNewBomEntryActive();
    void setNewBomEntryActive(bool state);

private:
    DbManager db_manager;
    std::vector<Part> parts_overview;
    Part current_part;


    Bom current_part_bom;
    QString active_part_bom_entry_part_id;
    BomEntry* active_part_bom_entry;

    bool checkPartNumberExists(QString proprietary_id);
    bool saveCurrentPartBom();

    //State related:
    PdmState_t pdm_state;
    bool new_bom_entry_active;
};

#endif // PDMMODEL_H
