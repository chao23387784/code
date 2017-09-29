#include "crtpropview.h"
#include "crtmaster.h"
#include <QHeaderView>

CrtPropView::CrtPropView(QWidget *parent):QTableView(parent)
{
    setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    verticalHeader()->setVisible(false);
}

void CrtPropView::itemDataChanged(QString value)
{
    foreach(QModelIndex index,selectionModel()->selectedIndexes())
    {
        model()->setData(index,value);
        update(index);
        CrtMaster::GetInstance()->ProjectTreeView()->updateItem(static_cast<CrtObject*>(index.internalPointer()));
    }
}

void CrtPropView::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        if(selectionModel()->selectedIndexes().count()>1)
        {
            bool bSameRow = true;

            for(int i = 0;i<selectionModel()->selectedIndexes().count()-1;i++)
            {
                if(selectionModel()->selectedIndexes().at(i).column() !=
                        selectionModel()->selectedIndexes().at(i+1).column())
                {
                    bSameRow = false;
                    break;
                }
            }


            if(bSameRow && selectionModel()->selectedIndexes().last().column() > 1)
            {
                if (selectionModel()->selectedIndexes().last().flags() & Qt::ItemIsEditable) {
                    edit(selectionModel()->selectedIndexes().last());
                }
            }
        }
    }

    QTableView::mouseReleaseEvent(event);
}
