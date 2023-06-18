#ifndef VCD_PARSER_H
#define VCD_PARSER_H

#include <QString>
#include <QMap>

QT_BEGIN_NAMESPACE
class QTextStream;
QT_END_NAMESPACE

enum class TimescaleUnit
{
    s,
    ms,
    us,
    ns,
    ps,
    fs,
};

struct VcdHeader
{
    QString date;
    QString version;
    quint64 timescaleNumber;
    TimescaleUnit timescaleUnit;
    QMap<QString, QString> vars;
};

class VcdParser
{
public:
    VcdParser(QTextStream *in);
    bool parseHeader(VcdHeader *inHeader);

private:
    QTextStream *in;
};

#endif // VCD_PARSER_H
