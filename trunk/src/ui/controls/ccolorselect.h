#ifndef CCOLORSELECT_H
#define CCOLORSELECT_H

#include <QWidget>
#include <QColor>


namespace Ui {
    class CColorSelect;
}

namespace ui
{
namespace controls
{

class CColorSelect : public QWidget
{
    Q_OBJECT
public: // ####################################################
    CColorSelect(const QRgb &color, QWidget *parent = 0);
    CColorSelect(QWidget *parent = 0);
    ~CColorSelect();
    const QRgb & selectedColor() const { return m_color; }
    void setColor(const QRgb &color);
    void setControlColor(const QRgb &rgba);

protected: // ####################################################
    void changeEvent(QEvent *e);

private: // ####################################################
    Ui::CColorSelect *ui;
    QRgb m_color;

private slots: // ####################################################
    void on_tbSelect_clicked();

public slots: // ####################################################
    void setEnabled(bool value);

signals: // ####################################################
    void colorChanged(QRgb color);
};
}
}
#endif // CCOLORSELECT_H
