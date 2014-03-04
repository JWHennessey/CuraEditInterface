#ifndef CONSOLEREADER_CC
#define CONSOLEREADER_CC
#include <iostream>
#include "ConsoleReader.hh"
#include <QTextStream>

#include <unistd.h> //Provides STDIN_FILENO

//#warning "Include ConsoleReader.cc"


ConsoleReader::ConsoleReader(QObject *parent) :
    QObject(parent)
{
    std::cout << "ConsoleReader Constructor" << "\n";
    notifier = new QSocketNotifier(STDIN_FILENO, QSocketNotifier::Read);
    connect(notifier, SIGNAL(activated(int)), this, SLOT(text()));
    notifier->setEnabled(true);
    mytext = QString("Test Text");
}


QString ConsoleReader::getText()
{
  return mytext;
}

void ConsoleReader::text()
{
    
    std::cout << "ConsoleReader text Called" << "\n";
    QTextStream qin(stdin);
    mytext = qin.readLine();
    emit textReceived(mytext);
}




#endif
