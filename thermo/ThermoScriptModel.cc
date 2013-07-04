#include <QFile>
#include <QTextStream>
#include <QPlainTextDocumentLayout>
#include <QFont>
#include <QDateTime>

#include "ThermoScriptModel.h"

ThermoScriptModel::ThermoScriptModel(JulaboModel* julaboModel,
                                     KeithleyModel* keithleyModel,
                                     HamegModel* hamegModel,
                                     PfeifferModel* pfeifferModel,
                                     QObject *parent) :
    QObject(parent),
    julaboModel_(julaboModel),
    keithleyModel_(keithleyModel),
    hamegModel_(hamegModel),
    pfeifferModel_(pfeifferModel)
{
    script_ = new QTextDocument(this);
    script_->setDocumentLayout(new QPlainTextDocumentLayout(script_));
    script_->setDefaultFont(QFont("Courier New",10));

    currentScriptFilename_ = QString();

    scriptThread_ = new ThermoScriptThread(this,
                                           julaboModel_,
                                           keithleyModel_,
                                           hamegModel_,
                                           pfeifferModel_,
                                           this);
    connect(scriptThread_, SIGNAL(started()), this, SLOT(executionStarted()));
    connect(scriptThread_, SIGNAL(finished()), this, SLOT(executionFinished()));

    connect(julaboModel_, SIGNAL(message(const QString &)),
            this, SLOT(doAppendMessageText(const QString &)));

    connect(keithleyModel_, SIGNAL(message(const QString &)),
            this, SLOT(doAppendMessageText(const QString &)));

    connect(hamegModel_, SIGNAL(message(const QString &)),
            this, SLOT(doAppendMessageText(const QString &)));

    connect(pfeifferModel_, SIGNAL(message(const QString &)),
            this, SLOT(doAppendMessageText(const QString &)));

    connect(&executionTimer_, SIGNAL(timeout()), this, SLOT(executionHeartBeat()));
}

void ThermoScriptModel::openScript(const QString filename) {

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    script_->setPlainText(file.readAll());

    currentScriptFilename_ = filename;
}

void ThermoScriptModel::saveScript(const QString filename) {

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
        return;

    QTextStream out(&file);
    out << script_->toPlainText();

    currentScriptFilename_ = filename;
}

void ThermoScriptModel::executeScript() {

    scriptThread_->executeScript(script_->toPlainText());
}

void ThermoScriptModel::abortScript() {

    scriptThread_->abortScript();
}

void ThermoScriptModel::executionStarted() {

    emit setControlsEnabled(false);
    emit clearMessageText();

    executionTime_ = 0;
    executionTimer_.start(1000);
}

void ThermoScriptModel::executionFinished() {

    executionTimer_.stop();

    emit setControlsEnabled(true);
}

void ThermoScriptModel::message(int value) {

    QString message = QString("%1")
            .arg(value);
    this->doAppendMessageText(message);
}

void ThermoScriptModel::message(uint value) {

    QString message = QString("%1")
            .arg(value);
    this->doAppendMessageText(message);
}

void ThermoScriptModel::message(double value) {

    QString message = QString("%1")
            .arg(value);
    this->doAppendMessageText(message);
}

void ThermoScriptModel::message(const QString & text) {

    QString message = QString("%1")
            .arg(text);
    this->doAppendMessageText(message);
}

void ThermoScriptModel::doClearMessageText() {

    emit clearMessageText();
}

void ThermoScriptModel::doAppendMessageText(const QString & text) {

    if (!executionTimer_.isActive()) return;

    static QString TIME_FORMAT = "yyyy-MM-dd hh:mm:ss";
    QDateTime dt = QDateTime::currentDateTime();
    QString message = QString("%1 - %2")
            .arg(dt.toString(TIME_FORMAT))
            .arg(text);
    emit appendMessageText(message);
}

void ThermoScriptModel::executionHeartBeat() {

    executionTime_++;
}