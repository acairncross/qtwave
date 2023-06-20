#ifndef VCD_PARSER_H
#define VCD_PARSER_H

#include <QString>
#include <QVector>
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
    uint64_t timescaleNumber;
    TimescaleUnit timescaleUnit;
    // Maybe this map should go the other way since multiple reference names can be mapped to the
    // same identifier code
    QMap<QString, QString> vars; // Identifier code -> reference name
    QMap<QString, size_t> varWidths; // Identifier code -> width
};

enum class Value
{
    V0,
    V1,
    X,
    Z,
};

struct Waveform {
    QMap<uint64_t, QVector<Value>> values; // Time -> value
    size_t width;
};

class VcdParser
{
public:
    VcdParser(QTextStream *in);
    bool parseHeader(VcdHeader *inHeader);
    bool parseBody(QMap<QString, Waveform> *inBody);

private:
    QTextStream *in;
    uint64_t time = 0;
};

#endif // VCD_PARSER_H
