#ifndef CRTTEXTPROPDLG_H
#define CRTTEXTPROPDLG_H
#include <QDialog>
#include <QColor>
#include <QLineEdit>
#include <QSpinBox>
#include "crttextitem.h"

class CrtTextPropDlg : public QDialog
{
    Q_OBJECT
public:
    explicit CrtTextPropDlg(CrtTextItem* item, QWidget *parent = 0, Qt::WindowFlags f = 0);
    ~CrtTextPropDlg();
private slots:
    void slotOk();
    void slotCancel();
    void slotColor();
private:
    QLineEdit* m_editTxt;
    QLineEdit* m_editColor;
    QSpinBox* m_sbSize;
    CrtTextItem* m_item;
};

#endif // CRTTEXTPROPDLG_H
