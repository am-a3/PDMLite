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
    void cellClicked(int row, int column);
    void cellChangedParameterTable(int row, int column);
    void addPartButtonClicked();

private:
    Ui::MainWindow *ui;
    PdmModel pdm_model;

    void ConfigureOverviewTable();
    void ConfigurePartParameterTable();
    void ClearPartParameterTable();
    bool FillPartParameterTable(PartData_t* part);
};
#endif // MAINWINDOW_H
