#include "SLogger.h"


void SLogger::Log(QString msg) {
    m_myfile << msg.toStdString() << "\n";
}

void SLogger::setFileName(const QString& filename) {
    closeFile();
    m_filename = filename;
    m_myfile.open(m_filename.toStdString(),ios::app);
}

void SLogger::closeFile() {
    m_myfile.close();
}

SLogger::~SLogger()
{
    closeFile();
}
