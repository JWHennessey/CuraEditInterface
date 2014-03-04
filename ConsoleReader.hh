#ifndef CONSOLEREADER_HH
#define CONSOLEREADER_HH

//#warning "Include ConsoleReader.hh"

#include <QObject>
#include <QSocketNotifier>

class ConsoleReader : public QObject
{
    Q_OBJECT
public:
    ConsoleReader(QObject *parent = 0);
    QString getText();
signals:
    void textReceived(QString mytext);

public slots:
    void text();

private:
    QSocketNotifier *notifier;
    QString mytext;

};

#if !defined(CONSOLEREADER_CC)
#define CONSOLEREADER_CC
#  include "ConsoleReader.cc"
#endif


#endif
