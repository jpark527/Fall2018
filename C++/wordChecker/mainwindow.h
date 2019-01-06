#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QString>
#include <QFileDialog>
#include <fstream>
#include "parser.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString contents;
    Parser *parser;
    void connectSignalsSlots();
    void alphabetsSignalsSlots();
    void readFile(const QString &fileName);

private slots:
    void openFile();
    void saveFile();
    void convertFile();
    void alphabetPressed();
};

#endif // MAINWINDOW_H
