#ifndef FREEZETABLEWIDGET_H
#define FREEZETABLEWIDGET_H

#include <QTableView>

QT_BEGIN_NAMESPACE
class QAbstractItemModel;
QT_END_NAMESPACE

class FreezeTableWidget : public QTableView {
    Q_OBJECT

public:
    FreezeTableWidget(QAbstractItemModel *model);
    ~FreezeTableWidget();

protected:
    void resizeEvent(QResizeEvent *event) override;
    QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers) override;
    void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible) override;

private:
    QTableView *frozenTableView;
    void init();
    void updateFrozenTableGeometry();

private slots:
    void updateSectionWidth(int logicalIndex, int oldSize, int newSize);
    void updateSectionHeight(int logicalIndex, int oldSize, int newSize);
};

#endif // FREEZETABLEWIDGET_H
