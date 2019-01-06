#! /usr/bin/env python3
# -*- coding: utf-8 -*-
import sys
from PyQt5.QtWidgets import (QMainWindow, QApplication, QPushButton, QWidget, QHeaderView, 
                             QLabel, QTabWidget, QHBoxLayout, QVBoxLayout, QTableWidget, 
                             QTableWidgetItem, QSizePolicy, QMessageBox, QScrollArea, QTextBrowser)
from PyQt5.QtGui import QIcon, QPixmap, QDesktopServices
from PyQt5.QtCore import pyqtSlot, Qt, QSize, QFile, QIODevice, QTextStream, QUrl

from LaunchData import getData, parseLocation, createMap
from functools import partial
import os
from LaunchCommitCriteria import getStatus
import urllib
import YelpJSON


class SpaceApp(QMainWindow):
 
    def __init__(self):
        super().__init__()
        self.title = 'Rocket Watch'
        self.left = 150
        self.top = 150
        self.width = 1100
        self.height = 700
        self.setWindowTitle(self.title)
        self.setWindowIcon(QIcon('rocket.png'))
        self.setGeometry(self.left, self.top, self.width, self.height) 
        self.myWidget = SpaceWidget(self)
        self.setCentralWidget(self.myWidget)
        self.show()
        stream = QFile('tab1StyleSheet.qss')
        stream.open(QIODevice.ReadOnly)
        self.setStyleSheet(QTextStream(stream).readAll())
        
 
class SpaceWidget(QWidget):        
 
    def __init__(self, parent):   
        super(QWidget, self).__init__(parent)
        self.parseData()
        self.layout = QVBoxLayout(self)
        self.initTabs()        
 
    def parseData(self):
        self.weather = getStatus()
        self.launchData = getData()
        parseLocation(self.launchData)
        self.cords = list(self.launchData['Coordinates'])
        self.dates = list(self.launchData['Launch Dates'])
        self.missions = list(self.launchData['Missions'])
        self.infos = list(self.launchData['Info'])
        self.launchSites = list(self.launchData['Launch Sites'])
        self.times = list(self.launchData['Times'])
        self.numOfItem = len(self.launchData)

    def reFreshData(self):
        self.dates.clear()
        self.missions.clear()
        self.infos.clear()
        self.launchSites.clear()
        self.times.clear()
        self.numOfItem = 0
        self.launchData = None
        self.launchData = getData()
        
    def initTabs(self):
        self.tabs = QTabWidget()
        self.addTab1()
        self.addTab2()
        self.addTab3()
        self.wireTab1()
        self.wireTab2()
        self.wireTab3()
        self.layout.addWidget(self.tabs)
        self.setLayout(self.layout)
        
    def addTab1(self):
        self.tab1 = QScrollArea()
        self.tabs.addTab(self.tab1, "Launches")
        self.addTab1Contents()
        
    def addTab1Contents(self):
        self.tab1Content = QWidget()
        self.tab1.setWidget(self.tab1Content)
        self.tab1.setWidgetResizable(True)
        self.tab1.layout = self.layout 
        self.addAcessBtns()
        self.vl = QVBoxLayout()
        self.vl.addLayout(self.hl)
        self.vl.addWidget(QLabel(""))
        self.addCords()
        self.addInfo()
        self.addStatus()
        self.addFoodBtns()
        self.addCell()
        self.tab1Content.setLayout(self.vl)
        
    def addFoodBtns(self):
        self.yelpBtns = list()
        self.hlYelp = list()
        for n in range(self.numOfItem):
            self.yelpBtns.append(QPushButton('Yelp', self))
            self.hlYelp.append(QHBoxLayout())
            self.hlYelp[n].addWidget(self.yelpBtns[n])
            self.hlYelp[n].addStretch(50)
        
    def addAcessBtns(self):
        self.refreshBtn = QPushButton('Refresh')
        self.qBtn = QPushButton(' ? ')        
        self.hl = QHBoxLayout()
        self.hl.addStretch(50)
        self.hl.addWidget(self.refreshBtn)
        self.hl.addWidget(self.qBtn)
        
    def addCell(self):
        self.tables = list()
        for n in range(self.numOfItem):
            self.tables.append(QTableWidget())
            self.tables[n].setRowCount(1)
            self.tables[n].setColumnCount(5)
            self.tables[n].setHorizontalHeaderLabels(['Date', 'Time', 'Launch Site', 'Mission', 'Status'])
            self.tables[n].horizontalHeader().setSectionResizeMode(0, QHeaderView.ResizeToContents)
            self.tables[n].horizontalHeader().setSectionResizeMode(1, QHeaderView.ResizeToContents)
            self.tables[n].horizontalHeader().setSectionResizeMode(2, QHeaderView.Stretch)
            self.tables[n].horizontalHeader().setSectionResizeMode(3, QHeaderView.Stretch)
            self.tables[n].horizontalHeader().setSectionResizeMode(4, QHeaderView.ResizeToContents)
            self.tables[n].verticalHeader().setSectionResizeMode(QHeaderView.Stretch)
            self.tables[n].verticalHeader().setVisible(False)      
            self.tables[n].setItem(0,0, QTableWidgetItem(self.dates[n]))
            self.tables[n].setItem(0,1, QTableWidgetItem(self.times[n]))            
            self.tables[n].setCellWidget(0,2, self.cordWidgets[n])
            self.tables[n].setCellWidget(0,3, self.infoWidgets[n])
            self.tables[n].setCellWidget(0,4, self.statusWidgets[n])
            self.vl.addWidget(self.tables[n])
            self.vl.addLayout(self.hlYelp[n])
            self.vl.addWidget(QLabel("\n"))
      
    def addCords(self):
        self.cordBtns = list()
        self.cordWidgets = list()
        self.cordLayouts = list()
        self.cordURL = list()
        for n in range(self.numOfItem):
            self.cordURL.append(createMap(self.cords[n]))
            self.cordBtns.append(QPushButton(self.launchSites[n], self))
            self.cordBtns[n].setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
            self.cordWidgets.append(QWidget())
            self.cordLayouts.append(QHBoxLayout(self.cordWidgets[n]))
            self.cordLayouts[n].addWidget(self.cordBtns[n])
            self.cordLayouts[n].setAlignment(Qt.AlignCenter)
            self.cordLayouts[n].setContentsMargins(0,0,0,0)
            self.cordWidgets[n].setLayout(self.cordLayouts[n])
        
    def addInfo(self):
        self.infoBtns = list()
        self.infoWidgets = list()
        self.infoLayouts = list()
        for n in range(self.numOfItem):
            self.infoBtns.append(QPushButton(self.missions[n], self))
            self.infoBtns[n].setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
            self.infoWidgets.append(QWidget())
            self.infoLayouts.append(QHBoxLayout(self.infoWidgets[n]))
            self.infoLayouts[n].addWidget(self.infoBtns[n])
            self.infoLayouts[n].setAlignment(Qt.AlignCenter)
            self.infoLayouts[n].setContentsMargins(0,0,0,0)
            self.infoWidgets[n].setLayout(self.infoLayouts[n])
            
    def setStatusColor(self, ind):
        if self.weather[ind][0] == 'Unknown':
            return 'white.png',''
        elif self.weather[ind][0] == 'Fail':
            return 'yellow.png',self.weather[ind][1]
        else:
            return 'green.png',''
        
    def addStatus(self):
        self.statusIcons = list()
        self.statusBtns = list()
        self.statusWidgets = list()
        self.statusLayouts = list()
        self.myStatus = list()
        for n in range(self.numOfItem):
            self.myStatus.append(self.setStatusColor(n))
            self.statusIcons.append(QIcon(self.myStatus[n][0]))
            self.statusBtns.append(QPushButton('', self))
            self.statusBtns[n].setIcon(self.statusIcons[n])
            self.statusBtns[n].setIconSize(QSize(25,25))
            self.statusWidgets.append(QWidget())
            self.statusLayouts.append(QHBoxLayout(self.statusWidgets[n]))
            self.statusLayouts[n].addWidget(self.statusBtns[n])
            self.statusLayouts[n].setAlignment(Qt.AlignCenter)
            self.statusLayouts[n].setContentsMargins(0,0,0,0)
            self.statusWidgets[n].setLayout(self.statusLayouts[n])
    
    def wireTab1(self):
        for n in range(self.numOfItem):
            self.infoBtns[n].clicked.connect(partial(self.onClickInfo, n))
            self.statusBtns[n].clicked.connect(partial(self.onClickStatus, n))
            self.cordBtns[n].clicked.connect(partial(self.onClickCord, n))
            self.yelpBtns[n].clicked.connect(partial(self.onClickYelp, n))
        self.refreshBtn.clicked.connect(self.onClickRefresh)
        self.qBtn.clicked.connect(partial(self.onClickQuestionMark, 0))

    def addTab2(self):
        self.tab2 = QWidget()
        self.tabs.addTab(self.tab2,"Mars")
        self.tab2CreateWidgets()
        self.forQBtns.addStretch(50)
        self.forQBtns.addWidget(self.qBtnTab2)
        self.hlBtns.addStretch(15)
        self.hlBtns.addWidget(self.openBtn)
        self.hlBtns.addWidget(self.lsBtn)
        self.hlBtns.addStretch(15)  
        self.hlPictureInfo.addWidget(self.showDir)
        self.hlPictureInfo.addWidget(self.imgToDisplay)       
        self.vlForTab2.addLayout(self.forQBtns)
        self.vlForTab2.addLayout(self.hlPictureInfo)
        self.vlForTab2.addLayout(self.hlBtns)
        self.tab2.setLayout(self.vlForTab2)
        
    def tab2CreateWidgets(self):
        self.vlForTab2 = QVBoxLayout()
        self.hlPictureInfo = QHBoxLayout()
        self.qBtnTab2 = QPushButton(' ? ')
        self.lsBtn = QPushButton('Classify')
        self.openBtn = QPushButton('Satellite')        
        self.showDir = QTextBrowser()
        self.imgToDisplay = QLabel()
        self.hlBtns = QHBoxLayout()
        self.forQBtns = QHBoxLayout()
        self.displayImage('rocket.png')
        self.path = str()
        self.imgCount = True
        
    def displayImage(self, path):
        self.mySateliteImg = QPixmap(path)
        self.mySateliteImg = self.mySateliteImg.scaled(450,350,Qt.KeepAspectRatio,Qt.FastTransformation)
        self.imgToDisplay.setPixmap(self.mySateliteImg)
        self.imgToDisplay.setAlignment(Qt.AlignCenter)
        self.imgToDisplay.setFixedSize(450,350)
        self.imgToDisplay.repaint()
        
    def wireTab2(self):
        self.lsBtn.clicked.connect(self.onClickLs)
        self.openBtn.clicked.connect(self.onClickFindPath)
        self.qBtnTab2.clicked.connect(partial(self.onClickQuestionMark, 1))       
    
    def addTab3(self):
        self.tab3 = QWidget()
        self.tabs.addTab(self.tab3,"About")  
        self.tab3CreateWidgets()
        self.tab3Text.setSource(QUrl('aboutpage.html'))
        self.vlForTab3.addWidget(self.tab3Text)
        self.tab3.setLayout(self.vlForTab3)
        
    def tab3CreateWidgets(self):
        self.vlForTab3 = QVBoxLayout()
        self.tab3Text = QTextBrowser()
    
    def wireTab3(self):
        pass
    
    @pyqtSlot()
    def onClickFindPath(self):
        self.imgCount = not self.imgCount
        if self.imgCount:
            self.path = 'DeepModel/tf_files/test/test2.jpg'
        else:
            self.path = 'DeepModel/tf_files/test/test1.jpg'
        self.displayImage(self.path)
        
    @pyqtSlot()
    def onClickLs(self):      
        if self.imgCount:
            os.system('cd DeepModel; python -m scripts.label_image \
                      --graph=tf_files/retrained_graph.pb  \
                      --image=tf_files/test/test2.jpg > ls.txt')
        else:
            os.system('cd DeepModel; python -m scripts.label_image \
                      --graph=tf_files/retrained_graph.pb  \
                      --image=tf_files/test/test1.jpg > ls.txt')
        self.inFile = open('DeepModel/ls.txt', 'r')
        self.lsList = str()
        for line in self.inFile:
            self.lsList += line
        self.inFile.close()
        self.showDir.setText(self.lsList)
        self.showDir.repaint()
        
    @pyqtSlot()
    def onClickRefresh(self):
        self.reFreshData()
        self.parseData()
        self.tab1.takeWidget()
        self.addTab1Contents()
        self.wireTab1()
        
    @pyqtSlot()
    def onClickYelp(self, ind):
        self.yelpMB = YelpMessageBox(ind, self.cords[ind])
        self.yelpMB.exec()
    
    @pyqtSlot()
    def onClickQuestionMark(self, tabNum):
        if not tabNum:
            QMessageBox.about(self, 'Launch Commit Criteria', 'In order for a rocket to be safely launched and accomplish it’s mission, the weather conditions at launch must a strict set of criteria. First of all, if there is any precipitation whatsoever, the launch must be postponed. The windspeed at the launch site must not exceed 33 km/h and the visibility on the ground must be greater than 6.4 km. Due the the sensitivity of the rocket instruments and rocket fuel, the temperature must be within a range of 2℃ - 37℃. Finally if there is a thunderstorm with 63 km, the launch must be cancelled. \nGreen  = On time\nYellow = Delayed\nWhite   = Undetermined date')
        else:
            QMessageBox.about(self, 'Satellite', 'Using satellite imaging, a convolutional neural network was trained in order to detect dust storms. The risk to space missions posed by dust storms on mars has been displayed from The Martian to the recent loss of the opportunity rover that hasn’t been responding since the global  dust storm that consumed the planet this summer. By being able to identify and predict dust storms on Mars before they get too large can save countless dollars and man-hours of labor, not to mention lives of future astronauts on the surface of the planet.')
    
    @pyqtSlot()
    def onClickInfo(self, n):
        QMessageBox.about(self, 'Detail', self.infos[n])
    
    @pyqtSlot()
    def onClickStatus(self, n):
        if self.myStatus[n][1]:
            QMessageBox.about(self, 'Reason', self.myStatus[n][1])
            
    @pyqtSlot()
    def onClickCord(self, n):
#        self.myURL = QUrl(self.cordURL[n])
#        QDesktopServices.openUrl(self.myURL)
        self.urlData = urllib.request.urlopen(self.cordURL[n]).read()
        self.urlImg = QPixmap()
        self.urlImg.loadFromData(self.urlData)
        myMBox = QMessageBox()
        myMBox.setIconPixmap(self.urlImg)
        myMBox.setStandardButtons(QMessageBox.Ok)
        myMBox.setDefaultButton(QMessageBox.Ok)
        myMBox.exec()
    
    
class YelpMessageBox(QMessageBox):
    def __init__(self, index, myCords):
        QMessageBox.__init__(self)
        self.setSizeGripEnabled (True)
        self.index = index
        self.setWindowTitle('Yelp')

        self.foods = YelpJSON.request(myCords, 'food')
        self.hotels = YelpJSON.request(myCords, 'hotels')

        self.addTableWidget(self)
        
        self.setStandardButtons(QMessageBox.Ok)
        self.setDefaultButton(QMessageBox.Ok)
        

    def addTableCell(self):
#        print(self.foods)
        self.myLabels = list()
        self.myLinkIcons = list()
        self.myLinkBtns = list()
        self.myLinkWidgets = list()
        self.myLinkLayouts = list()
        for n in range( len(self.foods) ):   
            self.urlData = urllib.request.urlopen(self.foods[n]['picture link']).read()
            self.urlImg = QPixmap()
            self.urlImg.loadFromData(self.urlData)
            self.myLabels.append(QLabel())
            self.urlImg = self.urlImg.scaled(50,50,Qt.KeepAspectRatio,Qt.FastTransformation)        
            self.myLabels[n].setPixmap(self.urlImg)
            self.myLabels[n].setAlignment(Qt.AlignCenter)
            self.myLabels[n].setFixedSize(50,50)
            self.myLabels[n].repaint()
            self.tableWidget.setCellWidget(n,0, self.myLabels[n])
            self.tableWidget.setItem(n,1, QTableWidgetItem(str(self.foods[n]['name'])))
            self.tableWidget.setItem(n,2, QTableWidgetItem(str(self.foods[n]['address'])))
            self.tableWidget.setItem(n,3, QTableWidgetItem(str(self.foods[n]['stars'])))
            self.tableWidget.setItem(n,4, QTableWidgetItem(str(self.foods[n]['price'])))
            
            self.myLinkIcons.append(QIcon('yelp.png'))
            self.myLinkBtns.append(QPushButton('', self))
            self.myLinkBtns[n].setIcon(self.myLinkIcons[n])
            self.myLinkBtns[n].setIconSize(QSize(50,50))
            self.myLinkWidgets.append(QWidget())
            self.myLinkLayouts.append(QHBoxLayout(self.myLinkWidgets[n]))
            self.myLinkLayouts[n].addWidget(self.myLinkBtns[n])
            self.myLinkLayouts[n].setAlignment(Qt.AlignCenter)
            self.myLinkLayouts[n].setContentsMargins(0,0,0,0)
            self.myLinkWidgets[n].setLayout(self.myLinkLayouts[n])
            self.tableWidget.setCellWidget(n,5, self.myLinkBtns[n])
            self.myLinkBtns[n].clicked.connect(partial(self.onClickLink, n))
            
            
    def addTableWidget(self, parentItem) :
        self.l =  QVBoxLayout()
        self.tableWidget = QTableWidget(parentItem)
        self.tableWidget.setObjectName ('tableWidget')

        self.tableWidget.setColumnCount(6)
        self.tableWidget.setRowCount( len(self.foods) )
        self.tableWidget.setHorizontalHeaderLabels(['', 'Name', 'Address', 'Rating', 'Price', 'Link'])
        self.tableWidget.verticalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.tableWidget.verticalHeader().setVisible(False) 
        self.tableWidget.horizontalHeader().setSectionResizeMode(5, QHeaderView.ResizeToContents)
        self.tableWidget.horizontalHeader().setSectionResizeMode(3, QHeaderView.Stretch)
        self.tableWidget.horizontalHeader().setSectionResizeMode(2, QHeaderView.ResizeToContents)
        self.tableWidget.horizontalHeader().setSectionResizeMode(1, QHeaderView.ResizeToContents)
        self.tableWidget.horizontalHeader().setSectionResizeMode(0, QHeaderView.ResizeToContents)
        self.tableWidget.move(30,80)
        self.tableWidget.resize(1000, 500)
        

        self.addTableCell()
        
        self.l.addWidget(self.tableWidget)
        self.setLayout(self.l)

    def event(self, e):
        result = QMessageBox.event(self, e)
        self.setMinimumWidth(0)
        self.setMaximumWidth(16777215)
        self.setMinimumHeight(0)
        self.setMaximumHeight(16777215)
        self.setSizePolicy(
            QSizePolicy.Expanding, 
            QSizePolicy.Expanding
        )
        self.resize(1000, 600)

        return result
        
    @pyqtSlot()
    def onClickLink(self, ind):
        self.myURL = QUrl(self.foods[ind]['link'])
        QDesktopServices.openUrl(self.myURL)
            

if __name__ == '__main__':
    app = QApplication(sys.argv)
    ui = SpaceApp()
    sys.exit(app.exec_())
    
