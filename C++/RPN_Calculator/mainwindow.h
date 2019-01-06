#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QString>
#include <QFileDialog>
#include <QXmlStreamReader>
#include <QMessageBox>
#include <QFile>
#include "mynewtypes.h"
#include "mydatabase.h"

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
    function<void(MainWindow&, char)>* convert;
    myDatabase db;
    void initialize();
    bool minus;
    char myLHS;
    QString myExpression;
    void setupSignalsSlots();
    void alphabetsSigsSlots();
    void numAndopSigsSlots();
    void allTheOthersSigsSlots();
    void clearLabel();
    void convertExpression(const QString &line);
    void getLHS(const QString& line);
    void nothing(char c);
    void alphabet(char c);
    void clear();
    void singleCharInput(const QString &text);

private slots:
    void buttonPressed();
    void dotPressed();
    void clearPressed();
    void enterPressed();
    void readPressed();
    void writePressed();

};

#endif // MAINWINDOW_H
