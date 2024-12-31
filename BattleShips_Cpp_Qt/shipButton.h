#ifndef SHIPBUTTON_H
#define SHIPBUTTON_H

#include <QObject>
#include <QPushButton>
#include <QWidget>
#include <QIcon>
#include <QPoint>
#include <QMainWindow>


class ShipButton : public QPushButton
{
    Q_OBJECT
public:
    explicit ShipButton(int size, QWidget *parent = nullptr);

    QWidget *parentWidget;

    int size;
    bool isHorizontal;

    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void setShipIcon();

    void toggleOrientation();

    void toggleDragging(bool isD);
    void resetPosition();
    bool isDragging;

    void setPosition(QPoint pos);
    QPoint getInitialPosition();
    bool getInitiallyHorizontal();
    void setInitiallyHorizontal(bool hor);

    bool isClicked;

private:
    bool initiallyHorizontal;
    QPoint initialPosition;


signals:
    void released(ShipButton *ship);
    void grabbed(ShipButton *ship);
    void rotated();
};

#endif // SHIPBUTTON_H
