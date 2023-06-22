#include "vcdparser.h"
#include "waveformdelegate.h"

#include <QPainter>

#include <iostream>

void WaveformDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
    if (index.data().canConvert<Waveform>()) {
        Waveform waveform = qvariant_cast<Waveform>(index.data());

        // first find the smallest and largest times
        uint64_t lo, hi = 0;

        for (auto i = waveform.values.cbegin(); i != waveform.values.cend(); i++) {
            if (i.key() < lo) {
                lo = i.key();
            }
            if (i.key() > hi) {
                hi = i.key();
            }
        }

        painter->save();
//        const int yOffset = option.rect.height() / 2;
        painter->translate(option.rect.x(), option.rect.y());
        QPoint lastPoint = QPoint(0, 0);
        for (auto i = waveform.values.cbegin(); i != waveform.values.cend(); i++) {
            if (i.value().size() == 1) {
                if (i.value()[0] == Value::V0) {
                    QPoint nextPoint = QPoint(1.0 * i.key() * option.rect.width() / hi, 2);
                    painter->drawLine(lastPoint, nextPoint);
                    lastPoint = nextPoint;
                } else if (i.value()[0] == Value::V1) {
                    QPoint nextPoint = QPoint(1.0 * i.key() * option.rect.width() / hi, option.rect.height() - 2);
                    painter->drawLine(lastPoint, nextPoint);
                    lastPoint = nextPoint;
                } else {
                    QPoint nextPoint = QPoint(1.0 * i.key() * option.rect.width() / hi, option.rect.height() / 2.0);
                    painter->drawLine(lastPoint, nextPoint);
                    lastPoint = nextPoint;
                }
            }
        }
        painter->restore();
    } else {
//        int anInt = qvariant_cast<int>(index.data());

//        painter->fillRect(option.rect, option.palette.highlight());

//        painter->save();
//        painter->drawEllipse(option.rect.x(), option.rect.y(), option.rect.width(), option.rect.height());
//        painter->restore();
        QStyledItemDelegate::paint(painter, option, index);
    }
}
