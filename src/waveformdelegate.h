#ifndef WAVEFORMDELEGATE_H
#define WAVEFORMDELEGATE_H

#include <QStyledItemDelegate>

class WaveformDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
//    WaveformDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
};

#endif // WAVEFORMDELEGATE_H
