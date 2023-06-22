#include "waveformitem.h"

WaveformItem::WaveformItem(Waveform waveform)
    : waveform(waveform)
{
}

int WaveformItem::type() const
{
    return UserType;
}

QVariant WaveformItem::data(int role) const
{
    QVariant dat;
    dat.setValue(waveform);
    return dat;
}

void WaveformItem::setData(const QVariant &value, int role)
{
    waveform = qvariant_cast<Waveform>(value);
}
