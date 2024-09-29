#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTableWidgetItem>
#include <QString>
#include <QDateTime>

#define PART_PARAM_TABLE_PARAM_COLUMN   0
#define PART_PARAM_TABLE_VALUE_COLUMN   1

typedef enum overview_table_columns {
    OVERVIEW_TABLE_PART_NUMBER_COLUMN = 0,
    OVERVIEW_TABLE_DESCRIPTION_COLUMN,
    OVERVIEW_TABLE_CATEGORY_COLUMN,
    OVERVIEW_TABLE_COLUMN_COUNT
} overview_table_columns;

typedef enum part_parameter_table_rows {
    PART_PARAM_TABLE_PART_NUMBER_ROW = 0,
    PART_PARAM_TABLE_DESCRIPTION_ROW,
    PART_PARAM_TABLE_VERSION_ROW,
    PART_PARAM_TABLE_CATEGORY_ROW,
    PART_PARAM_TABLE_IS_SIMPLE_ROW,
    PART_PARAM_TABLE_CREATED_BY_ROW,
    PART_PARAM_TABLE_CREATED_DATE_ROW,
    PART_PARAM_TABLE_LAST_MODIFIED_BY_ROW,
    PART_PARAM_TABLE_LAST_MODIFIED_DATE_ROW,
    PART_PARAM_TABLE_ROW_COUNT
} part_parameter_table_rows;

typedef enum part_bom_table_columns {
    PART_BOM_TABLE_PART_NUMBER_COLUMN = 0,
    PART_BOM_TABLE_QUANTITY_COLUMN,
    PART_BOM_TABLE_CREATED_BY_COLUMN,
    PART_BOM_TABLE_CREATED_DATE_COLUMN,
    PART_BOM_TABLE_LAST_MODIFIED_BY_COLUMN,
    PART_BOM_TABLE_LAST_MODIFIED_DATE_COLUMN,
    PART_BOM_TABLE_COLUMN_COUNT
} part_bom_table_columns;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pdm_model()
{
    ui->setupUi(this);

    ConfigureOverviewTable();
    ConfigurePartParameterTable();
    ConfigurePartBomTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ConfigureOverviewTable()
{
    ui->overviewTable->setColumnCount(OVERVIEW_TABLE_COLUMN_COUNT);
    ui->overviewTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->overviewTable->setHorizontalHeaderLabels({"Part number", "Description", "Category"});
    ui->overviewTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    FillOverviewTable(pdm_model.getPartOverviewEntryCount());
}

void MainWindow::FillOverviewTable(qint32 entry_number)
{
    std::vector<Part>* part_overview_ptr = NULL;

    part_overview_ptr = pdm_model.getPartOverview(entry_number);
    ui->overviewTable->setRowCount(part_overview_ptr->size());
    for (qint32 i = 0; i < part_overview_ptr->size(); i++)
    {
        ui->overviewTable->setItem(i, OVERVIEW_TABLE_PART_NUMBER_COLUMN, new QTableWidgetItem((*part_overview_ptr)[i].getProprietaryId()));
        ui->overviewTable->setItem(i, OVERVIEW_TABLE_DESCRIPTION_COLUMN, new QTableWidgetItem((*part_overview_ptr)[i].getDescription()));
        ui->overviewTable->setItem(i, OVERVIEW_TABLE_CATEGORY_COLUMN, new QTableWidgetItem((*part_overview_ptr)[i].getCategory()));
    }
}

void MainWindow::ConfigurePartParameterTable()
{
    QTableWidgetItem* item = NULL;

    ui->partParameterTable->setColumnCount(2); // parameter and value
    ui->partParameterTable->setRowCount(PART_PARAM_TABLE_ROW_COUNT);
    ui->partParameterTable->setHorizontalHeaderLabels({"Parameter", "Value"});
    ui->partParameterTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    item = new QTableWidgetItem("Part number");
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    ui->partParameterTable->setItem(PART_PARAM_TABLE_PART_NUMBER_ROW, PART_PARAM_TABLE_PARAM_COLUMN, item);
    item = new QTableWidgetItem("");
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    ui->partParameterTable->setItem(PART_PARAM_TABLE_PART_NUMBER_ROW, PART_PARAM_TABLE_VALUE_COLUMN, item);

    item = new QTableWidgetItem("Description");
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    ui->partParameterTable->setItem(PART_PARAM_TABLE_DESCRIPTION_ROW, PART_PARAM_TABLE_PARAM_COLUMN, item);
    item = new QTableWidgetItem("");
    ui->partParameterTable->setItem(PART_PARAM_TABLE_DESCRIPTION_ROW, PART_PARAM_TABLE_VALUE_COLUMN, item);

    item = new QTableWidgetItem("Version");
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    ui->partParameterTable->setItem(PART_PARAM_TABLE_VERSION_ROW, PART_PARAM_TABLE_PARAM_COLUMN, item);
    item = new QTableWidgetItem("");
    ui->partParameterTable->setItem(PART_PARAM_TABLE_VERSION_ROW, PART_PARAM_TABLE_VALUE_COLUMN, item);

    item = new QTableWidgetItem("Category");
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    ui->partParameterTable->setItem(PART_PARAM_TABLE_CATEGORY_ROW, PART_PARAM_TABLE_PARAM_COLUMN, item);
    item = new QTableWidgetItem("");
    ui->partParameterTable->setItem(PART_PARAM_TABLE_CATEGORY_ROW, PART_PARAM_TABLE_VALUE_COLUMN, item);

    item = new QTableWidgetItem("Simple part");
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    ui->partParameterTable->setItem(PART_PARAM_TABLE_IS_SIMPLE_ROW, PART_PARAM_TABLE_PARAM_COLUMN, item);
    item = new QTableWidgetItem("");
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    ui->partParameterTable->setItem(PART_PARAM_TABLE_IS_SIMPLE_ROW, PART_PARAM_TABLE_VALUE_COLUMN, item);

    item = new QTableWidgetItem("Created by");
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    ui->partParameterTable->setItem(PART_PARAM_TABLE_CREATED_BY_ROW, PART_PARAM_TABLE_PARAM_COLUMN, item);
    item = new QTableWidgetItem("");
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    ui->partParameterTable->setItem(PART_PARAM_TABLE_CREATED_BY_ROW, PART_PARAM_TABLE_VALUE_COLUMN, item);

    item = new QTableWidgetItem("Created date");
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    ui->partParameterTable->setItem(PART_PARAM_TABLE_CREATED_DATE_ROW, PART_PARAM_TABLE_PARAM_COLUMN, item);
    item = new QTableWidgetItem("");
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    ui->partParameterTable->setItem(PART_PARAM_TABLE_CREATED_DATE_ROW, PART_PARAM_TABLE_VALUE_COLUMN, item);

    item = new QTableWidgetItem("Last modified by");
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    ui->partParameterTable->setItem(PART_PARAM_TABLE_LAST_MODIFIED_BY_ROW, PART_PARAM_TABLE_PARAM_COLUMN, item);
    item = new QTableWidgetItem("");
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    ui->partParameterTable->setItem(PART_PARAM_TABLE_LAST_MODIFIED_BY_ROW, PART_PARAM_TABLE_VALUE_COLUMN, item);

    item = new QTableWidgetItem("Last modified date");
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    ui->partParameterTable->setItem(PART_PARAM_TABLE_LAST_MODIFIED_DATE_ROW, PART_PARAM_TABLE_PARAM_COLUMN, item);
    item = new QTableWidgetItem("");
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    ui->partParameterTable->setItem(PART_PARAM_TABLE_LAST_MODIFIED_DATE_ROW, PART_PARAM_TABLE_VALUE_COLUMN, item);
}

void MainWindow::ClearPartParameterTable()
{
    ui->partParameterTable->blockSignals(true);

    ui->partParameterTable->item(PART_PARAM_TABLE_PART_NUMBER_ROW, PART_PARAM_TABLE_VALUE_COLUMN)->setText("");
    ui->partParameterTable->item(PART_PARAM_TABLE_DESCRIPTION_ROW, PART_PARAM_TABLE_VALUE_COLUMN)->setText("");
    ui->partParameterTable->item(PART_PARAM_TABLE_CATEGORY_ROW, PART_PARAM_TABLE_VALUE_COLUMN)->setText("");
    ui->partParameterTable->item(PART_PARAM_TABLE_IS_SIMPLE_ROW, PART_PARAM_TABLE_VALUE_COLUMN)->setText("");
    ui->partParameterTable->item(PART_PARAM_TABLE_CREATED_BY_ROW, PART_PARAM_TABLE_VALUE_COLUMN)->setText("");
    ui->partParameterTable->item(PART_PARAM_TABLE_CREATED_DATE_ROW, PART_PARAM_TABLE_VALUE_COLUMN)->setText("");
    ui->partParameterTable->item(PART_PARAM_TABLE_LAST_MODIFIED_BY_ROW, PART_PARAM_TABLE_VALUE_COLUMN)->setText("");
    ui->partParameterTable->item(PART_PARAM_TABLE_LAST_MODIFIED_DATE_ROW, PART_PARAM_TABLE_VALUE_COLUMN)->setText("");

    ui->partParameterTable->blockSignals(false);
}

bool MainWindow::FillPartParameterTable(Part* part)
{
    QTableWidgetItem* item = NULL;

    if (part == NULL) {
        return false;
    }

    ui->partParameterTable->blockSignals(true);

    ui->partParameterTable->item(PART_PARAM_TABLE_PART_NUMBER_ROW, PART_PARAM_TABLE_VALUE_COLUMN)->setText(part->getProprietaryId());
    ui->partParameterTable->item(PART_PARAM_TABLE_DESCRIPTION_ROW, PART_PARAM_TABLE_VALUE_COLUMN)->setText(part->getDescription());
    ui->partParameterTable->item(PART_PARAM_TABLE_CATEGORY_ROW, PART_PARAM_TABLE_VALUE_COLUMN)->setText(part->getCategory());

    item = ui->partParameterTable->item(PART_PARAM_TABLE_IS_SIMPLE_ROW, PART_PARAM_TABLE_VALUE_COLUMN);
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    item->setText(QString::number(part->getIsSimplePart()));
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);

    item = ui->partParameterTable->item(PART_PARAM_TABLE_CREATED_BY_ROW, PART_PARAM_TABLE_VALUE_COLUMN);
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    item->setText(part->getCreatedBy());
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);

    item = ui->partParameterTable->item(PART_PARAM_TABLE_CREATED_DATE_ROW, PART_PARAM_TABLE_VALUE_COLUMN);
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    item->setText(part->getCreatedDate().toString());
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);

    item = ui->partParameterTable->item(PART_PARAM_TABLE_LAST_MODIFIED_BY_ROW, PART_PARAM_TABLE_VALUE_COLUMN);
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    item->setText(part->getLastModifiedBy());
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);

    item = ui->partParameterTable->item(PART_PARAM_TABLE_LAST_MODIFIED_DATE_ROW, PART_PARAM_TABLE_VALUE_COLUMN);
    item->setText(part->getLastModifiedDate().toString());
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);

    ui->partParameterTable->blockSignals(false);

    return true;
}

void MainWindow::RefreshPartView()
{
    FillOverviewTable(pdm_model.getPartOverviewEntryCount());

    auto part = pdm_model.getCurrentPart();
    if (!FillPartParameterTable(part)) {
        ClearPartParameterTable();

        return;
    }

    FillPartBomTable(pdm_model.getCurrentPartBom());
}

void MainWindow::ConfigurePartBomTable()
{
    QTableWidgetItem* item = NULL;

    ui->bomTable->setColumnCount(PART_BOM_TABLE_COLUMN_COUNT); // parameter and value
    ui->bomTable->setRowCount(0);
    ui->bomTable->setHorizontalHeaderLabels({"Part Number", "Quantity", "Created by",
                                             "Created date", "Last modified by", "Last modified date"});
    ui->bomTable->setSelectionBehavior(QAbstractItemView::SelectRows);
}

bool MainWindow::FillPartBomTable(Bom* bom)
{
    QTableWidgetItem* item = NULL;

    if (bom == NULL) {
        return false;
    }

    QMap<QString, BomEntry> entries = bom->getEntries();
    qint32 row_count = 0;
    ui->bomTable->setRowCount(bom->getEntryCount());
    for (auto it = entries.begin(); it != entries.end(); ++it)
    {
        FillPartBomRow(row_count, it.key(), it.value());

        row_count++;
    }

    return true;
}

bool MainWindow::FillPartBomRow(qint32 row, QString part_id, BomEntry entry)
{
    QTableWidgetItem* item = NULL;

    item = new QTableWidgetItem(part_id);
    ui->bomTable->setItem(row, PART_BOM_TABLE_PART_NUMBER_COLUMN, item);

    item = new QTableWidgetItem(QString::number(entry.getQuantity()));
    ui->bomTable->setItem(row, PART_BOM_TABLE_QUANTITY_COLUMN, item);

    item = new QTableWidgetItem(entry.getCreatedBy());
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    ui->bomTable->setItem(row, PART_BOM_TABLE_CREATED_BY_COLUMN, item);

    item = new QTableWidgetItem(entry.getCreatedDatetime().toString());
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    ui->bomTable->setItem(row, PART_BOM_TABLE_CREATED_DATE_COLUMN, item);

    item = new QTableWidgetItem(entry.getLastModifiedBy());
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    ui->bomTable->setItem(row, PART_BOM_TABLE_LAST_MODIFIED_BY_COLUMN, item);

    item = new QTableWidgetItem(entry.getLastModifiedDatetime().toString());
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    ui->bomTable->setItem(row, PART_BOM_TABLE_LAST_MODIFIED_DATE_COLUMN, item);

    return true;
}

//Slots:

void MainWindow::cellClickedOverviewTable(int row, int column)
{
    QTableWidgetItem* part_number;
    Part* part;

    ui->savePartButton->setEnabled(false);

    auto row_count = ui->overviewTable->rowCount();

    //New part creation interrupted:
    if ((pdm_model.getPdmState() == PDM_ADD_NEW_PART) && row != (row_count - 1))
    {
        ui->overviewTable->removeRow(row_count - 1);

        ui->addPartButton->setEnabled(true);
        ui->deletePartButton->setEnabled(true);

        pdm_model.setPdmState(PDM_IDLE);
    }

    if (pdm_model.getPdmState() == PDM_ADD_NEW_PART)
    {
        part = pdm_model.getCurrentPart();
    }
    else
    {
        part_number = ui->overviewTable->item(row, OVERVIEW_TABLE_PART_NUMBER_COLUMN);

        if (part_number != NULL) {
            part = pdm_model.setCurrentPart(part_number->data(Qt::DisplayRole).toString());
        }
        else
        {
            ClearPartParameterTable();
            return;
        }
    }

    if (!FillPartParameterTable(part)) {
        ClearPartParameterTable();
    }
}

void MainWindow::cellChangedParameterTable(int row, int column)
{
    Part* part;
    QTableWidgetItem* parameter;

    if (column == PART_PARAM_TABLE_VALUE_COLUMN)
    {
        qDebug() << "Row: " << row << " value updated.";

        ui->savePartButton->setEnabled(true);

        part = pdm_model.getCurrentPart();

        parameter = ui->partParameterTable->item(row, column);

        switch (row)
        {
            case PART_PARAM_TABLE_DESCRIPTION_ROW:
                part->setDescription(parameter->text(), "dev");
                break;
            case PART_PARAM_TABLE_CATEGORY_ROW:
                part->setCategory(parameter->text(), "dev");
                break;
            case PART_PARAM_TABLE_VERSION_ROW:
                part->setVersion(parameter->text(), "dev");
                break;
        }
    }
}

void MainWindow::cellChangedPartBomTable(int row, int column)
{
    auto row_count = ui->bomTable->rowCount();
    BomEntry* bom_entry(nullptr);
    QString part_id = "";

    QTableWidgetItem* changed_cell = ui->bomTable->item(row, column);

    if ((pdm_model.isNewBomEntryActive()) && (row == row_count))
    {
        bom_entry = pdm_model.getActivePartBomEntry();
        part_id = pdm_model.getActivePartBomEntryPartId();

        if ((column == PART_BOM_TABLE_PART_NUMBER_COLUMN) && (changed_cell->data(Qt::DisplayRole).toString() != ""))
        {
            ui->addBomPartButton->setEnabled(true);
            ui->deleteBomPartButton->setEnabled(true);
        }
    }
    else
    {
        QMap<QString, BomEntry> entries = pdm_model.getCurrentPartBom()->getEntries();
        QTableWidgetItem* cell = ui->bomTable->item(row, PART_BOM_TABLE_PART_NUMBER_COLUMN);
        part_id = cell->data(Qt::DisplayRole).toString();

        bom_entry = new BomEntry(entries.value(part_id));
    }

    switch (column)
    {
    case PART_BOM_TABLE_PART_NUMBER_COLUMN: //TODO: need to handle part id duplication, deny enter of same part number
        part_id = changed_cell->data(Qt::DisplayRole).toString();
        break;
    case PART_BOM_TABLE_QUANTITY_COLUMN:
        bom_entry->setQuantity(changed_cell->data(Qt::DisplayRole).toInt(), "dev");
        break;
    }

    pdm_model.getCurrentPartBom()->saveEntry(part_id, *bom_entry);
}

void MainWindow::addPartButtonClicked()
{
    auto row_count = ui->overviewTable->rowCount();

    if (pdm_model.getPdmState() != PDM_ADD_NEW_PART)
    {
        pdm_model.setPdmState(PDM_ADD_NEW_PART);
        pdm_model.createCurrentPart();

        ui->overviewTable->setRowCount(row_count + 1);
        emit ui->overviewTable->cellClicked(row_count, 0);
        ui->overviewTable->selectRow(row_count);

        ui->addPartButton->setEnabled(false);
        ui->deletePartButton->setEnabled(false);
    }
}

void MainWindow::deletePartButtonClicked()
{
    QList selected_item = ui->overviewTable->selectedItems();

    auto part_number = ui->overviewTable->item(selected_item[0]->row(), OVERVIEW_TABLE_PART_NUMBER_COLUMN)->text();

    if (!part_number.isEmpty())
    {
        qDebug() << "Deleting part: " << part_number;

        pdm_model.deletePart(part_number);
    }

    RefreshPartView();
}

void MainWindow::savePartButtonClicked()
{
        pdm_model.saveCurrentPart();
        ui->savePartButton->setEnabled(false);

        if (pdm_model.getPdmState() == PDM_ADD_NEW_PART)
        {
            pdm_model.setPdmState(PDM_EDIT_EXISTING_PART);

            ui->addPartButton->setEnabled(true);
            ui->deletePartButton->setEnabled(true);
        }

        RefreshPartView();
}

void MainWindow::addPartBomButtonClicked()
{
    if (!pdm_model.isNewBomEntryActive())
    {
        auto row_count = ui->bomTable->rowCount();

        pdm_model.setNewBomEntryActive(true);

        ui->addBomPartButton->setEnabled(false);
        ui->deleteBomPartButton->setEnabled(false);
        ui->bomTable->setRowCount(row_count + 1);

        BomEntry* active_bom_entry = pdm_model.createActivePartBomEntry();
        FillPartBomRow(row_count, pdm_model.getActivePartBomEntryPartId(), *active_bom_entry);
    }
}

void MainWindow::deletePartBomButtonClicked()
{

}
