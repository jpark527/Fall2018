#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

// Public
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    minus = false;
    initialize();
    setupSignalsSlots();
}

MainWindow::~MainWindow() {
    delete[] convert;
    delete ui;
}

// Slots
void MainWindow::buttonPressed() {
    QPushButton* button = (QPushButton*) sender();
    QString print(ui->textBrowser->toPlainText());
    if(print.isEmpty() && button != ui->signButton)
        print = button->text();
    else {
        if(button == ui->multButton)
            print += " *";
        else if(button == ui->divButton)
            print += " /";
        else if(button == ui->signButton) {
            minus && !print.isEmpty() ? print = print.left(print.length()-2) : print += " -";
            minus = !minus;
        } else {
            QString t(button->text());
            if(t[0].isDigit() && (print[print.length()-1].isDigit() || minus)) {
                print += t;
                minus = false;
            } else
                print += (" "+t);
        }
    }
    ui->textBrowser->setText(print);
    ui->textBrowser->repaint();
    clearLabel();
}

void MainWindow::dotPressed() {
    QPushButton* button = (QPushButton*) sender();
    QString print(ui->textBrowser->toPlainText());
    ui->textBrowser->setText(print + button->text());
    ui->textBrowser->repaint();
    clearLabel();
}

void MainWindow::clearPressed() {
    ui->textBrowser->setText("");
    ui->textBrowser->repaint();
    clearLabel();
}

void MainWindow::enterPressed() {
    try {
        QString text(ui->textBrowser->toPlainText());
        if(text.length() < 2) {
            singleCharInput(text);
            return;
        }
        convertExpression(text);
        if(text.contains('=')) {
            getLHS(text);
            db.addData(myLHS, db.solve(myExpression.toStdString()));
            QString newExp = QString::fromLatin1(&myLHS) + " = " + QString::number(db[myLHS]);
            ui->answerlabel->setText(newExp);
        } else
            ui->answerlabel->setText(QString::number(db.solve(myExpression.toStdString())));
        ui->answerlabel->repaint();
    } catch(MY_ERROR e) {
        qDebug() << "ERROR# " << e;
        ui->answerlabel->setText("ERROR: Press 'AC' to continue..");
        ui->answerlabel->repaint();
    }
}

void MainWindow::readPressed() {
    QString myFile = QFileDialog::getOpenFileName(NULL, "Data File", QString(), "*.rpn");
    if(myFile.isNull())
        return ;
    if (QFileInfo(myFile).suffix().isEmpty())
        myFile.append(".rpn");
    QFile in(myFile);
    QXmlStreamReader reader;
    QMap<char, double> items;
    if(!in.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("File Input Error");
        msgBox.setText("File cannot be read.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        return ;
    }
    clear();
    reader.setDevice(&in);
    while(!reader.atEnd()) {
        reader.readNextStartElement();
        if(reader.name() == "Data") {
            do {
                reader.readNext();
                if(reader.name().length()==1)
                    items[reader.name().at(0).toLatin1()] = reader.readElementText().toDouble();
            } while(!reader.atEnd());
        }
    }
    QMapIterator<char, double> it(items);
    while (it.hasNext()) {
        it.next();
        db.addData(it.key(), it.value());
    }
    items.clear();
    in.close();
}

void MainWindow::writePressed() {
    QXmlStreamWriter writer;
    QString fileName = QFileDialog::getSaveFileName(NULL, "Save File", QString(), "*.rpn");
    if(fileName.isNull())
        return;
    if (QFileInfo(fileName).suffix().isEmpty())
        fileName.append(".rpn");
    QFile out(fileName);
    out.open(QFile::WriteOnly);
    writer.setDevice(&out);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("Data");
    for(QChar c='A'; c.unicode() < QChar('Z').unicode()+1; c = c.unicode()+1)
        writer.writeTextElement(QString(c), QString::number(db[c.toLatin1()]));
    writer.writeEndElement();
    writer.writeEndDocument();
    out.close();
}

// Private
void MainWindow::singleCharInput(const QString &text) {
    if(text.isEmpty())
        return;
    if(text[0] >= 'A' && text[0] <= 'Z')
        ui->answerlabel->setText(QString::number(db[text[0].toLatin1()]));
    else
        ui->answerlabel->setText(text);
}

void MainWindow::getLHS(const QString &line) {
    myLHS = '\0';
    QString temp;
    for(int i=0; i<line.length(); ++i)
        if(line.at(i) == '=') {
            myLHS = line.at(i-2).toLatin1();
            temp = line.right(line.length()-i-2);
            convertExpression(temp);
        }
}

void MainWindow::convertExpression(const QString& line) {
    myExpression.clear();
    for(int i=0; i<line.length(); ++i)
        convert[line.at(i).toLatin1()](*this, line.at(i).toLatin1());
}

void MainWindow::setupSignalsSlots() {
    alphabetsSigsSlots();
    numAndopSigsSlots();
    allTheOthersSigsSlots();
}

void MainWindow::allTheOthersSigsSlots() {
    connect(ui->parenLeftButton, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->parenRightButton, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->signButton, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->dotButton, SIGNAL(released()), this, SLOT(dotPressed()));
    connect(ui->clearButton, SIGNAL(released()), this, SLOT(clearPressed()));
    connect(ui->enterButton, SIGNAL(released()), this, SLOT(enterPressed()));
    connect(ui->readButton, SIGNAL(released()), this, SLOT(readPressed()));
    connect(ui->writeButton, SIGNAL(released()), this, SLOT(writePressed()));
}

void MainWindow::clearLabel() {
    if(!ui->answerlabel->text().isEmpty()) {
        myLHS = '\0';
        myExpression.clear();
        ui->answerlabel->setText("");
        ui->answerlabel->repaint();
    }
}

void MainWindow::initialize() {
    convert = new function<void(MainWindow&, char)>[128];
    for (size_t i=0; i<128; ++i)
        convert[i] = &MainWindow::nothing;
    for (size_t i='A'; i<'Z'+1; ++i)
        convert[i] = &MainWindow::alphabet;
}

void MainWindow::clear() {
    db.clear();
    clearLabel();
}

void MainWindow::nothing(char c) {
    myExpression += c;
}

void MainWindow::alphabet(char c) {
    myExpression += QString::number(db[c]);
}

void MainWindow::numAndopSigsSlots() {
    connect(ui->button0, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->button1, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->button2, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->button3, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->button4, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->button5, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->button6, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->button7, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->button8, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->button9, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->plusButton, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->minusButton, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->multButton, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->divButton, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->powerButton, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->equalsbutton, SIGNAL(released()), this, SLOT(buttonPressed()));
}

void MainWindow::alphabetsSigsSlots() {
    connect(ui->buttonA, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->buttonB, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->buttonC, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->buttonD, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->buttonE, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->buttonF, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->buttonG, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->buttonH, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->buttonI, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->buttonJ, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->buttonK, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->buttonL, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->buttonM, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->buttonN, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->buttonO, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->buttonP, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->buttonQ, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->buttonR, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->buttonS, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->buttonT, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->buttonU, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->buttonV, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->buttonW, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->buttonX, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->buttonY, SIGNAL(released()), this, SLOT(buttonPressed()));
    connect(ui->buttonZ, SIGNAL(released()), this, SLOT(buttonPressed()));
}
