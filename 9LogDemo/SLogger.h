#ifndef SLOGGER_H
#define SLOGGER_H
#include <QString>
#include <fstream>

using namespace  std;

class SLogger {

public:

    static SLogger& getInstance() {
        static SLogger instance;  // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }

    void setFileName(const QString& filename);
    void Log(QString msg);
    void closeFile();

private:

    ~SLogger();

    QString m_filename;
    ofstream m_myfile;
};

#endif // SLOGGER_H
