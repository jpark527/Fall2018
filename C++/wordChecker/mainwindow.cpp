#include "mainwindow.h"
#include "ui_mainwindow.h"

// Public
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    parser = new Parser();
    connectSignalsSlots();
}

MainWindow::~MainWindow() {
    delete parser;
    delete ui;
}

// Slots
void MainWindow::openFile() {
    QString fileName = QFileDialog::getOpenFileName(NULL, "Open File", NULL, "*.txt");
    if(fileName.isNull())
        return;
    if (QFileInfo(fileName).suffix().isEmpty())
      fileName.append(".txt");
    ui->fileName->setText(fileName);
    readFile(fileName);
}

void MainWindow::saveFile() {
    QString fileName = QFileDialog::getSaveFileName(NULL, "Save File", NULL, "*.txt");
    if(fileName.isNull())
        return;
    if (QFileInfo(fileName).suffix().isEmpty())
        fileName.append(".txt");
    std::ofstream out(fileName.toStdString());
    if(!contents.isEmpty())
        out << contents.toStdString();
    out.close();
}

void MainWindow::convertFile() {
    vector<Word> words;
    clock_t start;
    double duration;
    parser->clear();
    start = clock();
    parser->loadHeap();
    parser->getTenMostUsedWords(words);
    duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    ui->fileContentsDisplay->clear();
    contents = "Word Count: " + QString::number(parser->getWordCount()) +
               "\nParagraph Count: " + QString::number(parser->getParagraphCount()) +
               "\nReading level: " + QString::number(parser->getReadingLevel()) +
               "\n10 Most frequently used words:\n";
    for(size_t i=0; i<words.size(); ++i)
        contents += (QString::fromStdString(words[i].myWord)+" : "+QString::number(words[i].count)+"\n");
    for(char letter='A'; letter<='Z'; ++letter)
        contents += ("\n# of words begin with " + QString(letter) + ": " +
                     QString::number(parser->getSizeOf(letter)));
    contents += ("\nTime: " + QString::number(duration));
    ui->fileContentsDisplay->setText(contents);
    ui->fileContentsDisplay->repaint();
}

void MainWindow::alphabetPressed() {
    vector<string> words;
    vector<int> count;
    QPushButton* button = (QPushButton*) sender();
    parser->getWordsThatStartsWith(button->text()[0].toLatin1(), words, count);
    contents.clear();
    ui->fileContentsDisplay->clear();
    for(int i=words.size()-1; i >= 0; --i)
        ui->fileContentsDisplay->append(QString::fromStdString(words[i]) + " : " + QString::number(count[i]) + "\n");
    ui->fileContentsDisplay->repaint();
    words.clear();
    contents = ui->fileContentsDisplay->toPlainText();
}

// Private
void MainWindow::readFile(const QString &fileName) {
    parser->setFileName(fileName.toStdString());
    string data(parser->readFile());
    contents = QString::fromStdString(data);
    ui->fileContentsDisplay->clear();
    ui->fileContentsDisplay->setText(contents);
    ui->fileContentsDisplay->repaint();
}

void MainWindow::connectSignalsSlots() {
    connect(ui->exitButton, SIGNAL(pressed()), this, SLOT(close()));
    connect(ui->openButton, SIGNAL(pressed()), this, SLOT(openFile()));
    connect(ui->saveButton, SIGNAL(pressed()), this, SLOT(saveFile()));
    connect(ui->convertButton, SIGNAL(pressed()), this, SLOT(convertFile()));
    alphabetsSignalsSlots();
}

void MainWindow::alphabetsSignalsSlots() {
    connect(ui->buttonA, SIGNAL(pressed()), this, SLOT(alphabetPressed()));
    connect(ui->buttonB, SIGNAL(pressed()), this, SLOT(alphabetPressed()));
    connect(ui->buttonC, SIGNAL(pressed()), this, SLOT(alphabetPressed()));
    connect(ui->buttonD, SIGNAL(pressed()), this, SLOT(alphabetPressed()));
    connect(ui->buttonE, SIGNAL(pressed()), this, SLOT(alphabetPressed()));
    connect(ui->buttonF, SIGNAL(pressed()), this, SLOT(alphabetPressed()));
    connect(ui->buttonG, SIGNAL(pressed()), this, SLOT(alphabetPressed()));
    connect(ui->buttonH, SIGNAL(pressed()), this, SLOT(alphabetPressed()));
    connect(ui->buttonI, SIGNAL(pressed()), this, SLOT(alphabetPressed()));
    connect(ui->buttonJ, SIGNAL(pressed()), this, SLOT(alphabetPressed()));
    connect(ui->buttonK, SIGNAL(pressed()), this, SLOT(alphabetPressed()));
    connect(ui->buttonL, SIGNAL(pressed()), this, SLOT(alphabetPressed()));
    connect(ui->buttonM, SIGNAL(pressed()), this, SLOT(alphabetPressed()));
    connect(ui->buttonN, SIGNAL(pressed()), this, SLOT(alphabetPressed()));
    connect(ui->buttonO, SIGNAL(pressed()), this, SLOT(alphabetPressed()));
    connect(ui->buttonP, SIGNAL(pressed()), this, SLOT(alphabetPressed()));
    connect(ui->buttonQ, SIGNAL(pressed()), this, SLOT(alphabetPressed()));
    connect(ui->buttonR, SIGNAL(pressed()), this, SLOT(alphabetPressed()));
    connect(ui->buttonS, SIGNAL(pressed()), this, SLOT(alphabetPressed()));
    connect(ui->buttonT, SIGNAL(pressed()), this, SLOT(alphabetPressed()));
    connect(ui->buttonU, SIGNAL(pressed()), this, SLOT(alphabetPressed()));
    connect(ui->buttonV, SIGNAL(pressed()), this, SLOT(alphabetPressed()));
    connect(ui->buttonW, SIGNAL(pressed()), this, SLOT(alphabetPressed()));
    connect(ui->buttonX, SIGNAL(pressed()), this, SLOT(alphabetPressed()));
    connect(ui->buttonY, SIGNAL(pressed()), this, SLOT(alphabetPressed()));
    connect(ui->buttonZ, SIGNAL(pressed()), this, SLOT(alphabetPressed()));
}

