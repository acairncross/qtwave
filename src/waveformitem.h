#ifndef WAVEFORMITEM_H
#define WAVEFORMITEM_H

#include "vcdparser.h"

#include <QStandardItem>

class WaveformItem : public QStandardItem
{
public:
    WaveformItem(Waveform waveform);
    int type() const override;
    QVariant data(int role) const override;
    void setData(const QVariant &value, int role) override;

    Waveform waveform;
};

#endif // WAVEFORMITEM_H
