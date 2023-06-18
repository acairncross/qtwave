#include "vcdparser.h"

#include <QFile>
#include <QIODevice>
#include <QTextStream>

namespace {
    bool parseTimescaleUnit(const QString &token, TimescaleUnit *timescaleUnit)
    {
        if (token == "s") {
            *timescaleUnit = TimescaleUnit::s;
        } else if (token == "ms") {
            *timescaleUnit = TimescaleUnit::ms;
        } else if (token == "us") {
            *timescaleUnit = TimescaleUnit::us;
        } else if (token == "ns") {
            *timescaleUnit = TimescaleUnit::ns;
        } else if (token == "ps") {
            *timescaleUnit = TimescaleUnit::ps;
        } else if (token == "fs") {
            *timescaleUnit = TimescaleUnit::fs;
        } else {
            return false;
        }
        return true;
    }
}

VcdParser::VcdParser(QTextStream *in) : in(in) {}

bool VcdParser::parseHeader(VcdHeader *inHeader)
{
    QStringList scope;
    VcdHeader header;
    while (!in->atEnd()) {
        in->skipWhiteSpace();
        if (in->atEnd()) {
            break;
        }

        QString token;
        *in >> token;
        if (token == "$comment") {
            for (*in >> token; token != "$end"; *in >> token);
        } else if (token == "$date") {
            token = "";
            while (token.size() < 4 || token.mid(token.size() - 4) != "$end") {
                QChar c;
                *in >> c;
                token.append(c);
            }
            token.truncate(token.size() - 4);
            header.date = token.trimmed();
        } else if (token == "$version") {
            token = "";
            while (token.size() < 4 || token.mid(token.size() - 4) != "$end") {
                QChar c;
                *in >> c;
                token.append(c);
            }
            token.truncate(token.size() - 4);
            header.version = token.trimmed();
        } if (token == "$timescale") {
            *in >> token;
            bool ok = true;
            header.timescaleNumber = token.toULongLong(&ok);
            if (!ok) {
                return false;
            }

            *in >> token;
            ok = parseTimescaleUnit(token, &header.timescaleUnit);
            if (!ok) {
                return false;
            }
        } else if (token == "$scope") {
            *in >> token; // scope type
            *in >> token; // scope identifier
            scope.append(token);
            *in >> token; // $end
        } else if (token == "$upscope") {
            scope.pop_back();
            *in >> token; // $end
        } else if (token == "$var") {
            QString var_type;
            *in >> var_type;

            qsizetype size;
            *in >> size;

            QString identifierCode;
            *in >> identifierCode;

            QString reference;
            *in >> reference;

            *in >> token; // $end

            header.vars.insert(identifierCode, reference);
            header.varWidths.insert(identifierCode, size);
        } else if (token == "$enddefinitions") {
            *inHeader = header;
            return true;
        }
    }

    // Successful header parse should have returned on $enddefinitions
    return false;
}
