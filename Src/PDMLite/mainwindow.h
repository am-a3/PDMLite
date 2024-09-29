#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "PdmModel.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void cellClickedOverviewTable(int row, int column);
    void cellChangedParameterTable(int row, int column);
    void cellChangedPartBomTable(int row, int column);

    void addPartButtonClicked();
    void deletePartButtonClicked();

    void savePartButtonClicked();

    void addPartBomButtonClicked();
    void deletePartBomButtonClicked();

private:
    Ui::MainWindow *ui;
    PdmModel pdm_model;

    void ConfigureOverviewTable();
    void FillOverviewTable(qint32 entry_number);

    void ConfigurePartParameterTable();
    void ClearPartParameterTable();
    bool FillPartParameterTable(Part* part);

    void ConfigurePartBomTable();
    bool FillPartBomTable(Bom* bom);
    bool FillPartBomRow(qint32 row, QString part_id, BomEntry entry);

    void RefreshPartView();
};
#endif // MAINWINDOW_H
