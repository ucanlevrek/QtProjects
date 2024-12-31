#include "shipButton.h"
#include <QDrag>
#include <QMimeData>
#include <QKeyEvent>
#include <QTransform>


ShipButton::ShipButton(int size, QWidget *parent) {
    ShipButton::size = size;
    isHorizontal = true;
    initiallyHorizontal = true;

    setFixedSize(40*size, 40);
    setIconSize(QSize(40*size, 40));

    setShipIcon();
    parentWidget = parent;
    setParent(parent);
    isClicked = false;
    setFocusPolicy(Qt::StrongFocus);
}

void ShipButton::mousePressEvent(QMouseEvent *event){
    if(event->button() ==Qt::LeftButton){
        toggleDragging(true);
        if(!isClicked){
            isClicked = true;
            initialPosition = pos();
            emit grabbed(this);
        }
    }
}
void ShipButton::mouseReleaseEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        toggleDragging(false);
        if(isClicked){
            isClicked = false;
        }
    }
}

void ShipButton::mouseMoveEvent(QMouseEvent *event){
    if(isDragging){
        move(mapToParent(event->pos()) - rect().center());
    }
}


void ShipButton::toggleDragging(bool isD){
    isDragging = isD;
    if(isDragging){
        grabMouse();
    }else{
        releaseMouse();
        emit released(this);
    }
}

void ShipButton::keyPressEvent(QKeyEvent *event){
    if(event->key() ==Qt::Key_Space){
        if(isDragging){
            toggleOrientation();
        }
    }else{
        QPushButton::keyPressEvent(event);
    }
}


void ShipButton::toggleOrientation(){
    isHorizontal = !isHorizontal;

    QPixmap originalPixmap = icon().pixmap(iconSize());

    QTransform transform;
    transform.rotate(isHorizontal ? 0 : 90);
    QPixmap rotatedPixmap = originalPixmap.transformed(transform, Qt::SmoothTransformation);

    QSize nsize = QSize(isHorizontal ? 40 : size * 40,
                        isHorizontal ? 40 * size : 40);
    setFixedSize(nsize);
    setIconSize(nsize);


    setIcon(QIcon(rotatedPixmap));


    move(mapToParent(mapFromGlobal(rect().center()) - rect().center() ));
    emit rotated();

}


void ShipButton::resetPosition(){
    move(initialPosition);
}

void ShipButton::setShipIcon(){


    if(size == 2){
        setIcon(QIcon(":/shipArt/maps/ShipSized_2_Player.png"));
    }
    if(size == 3){
        setIcon(QIcon(":/shipArt/maps/ShipSized_3_Player.png"));
    }
    if(size == 4){
        setIcon(QIcon(":/shipArt/maps/ShipSized_4_Player.png"));
    }
    if(size == 5){
        setIcon(QIcon(":/shipArt/maps/ShipSized_5_Player.png"));
    }
}


void ShipButton::setPosition(QPoint pos){
    this->move(pos);
    initialPosition = this->pos();
}
void ShipButton::setInitiallyHorizontal(bool hor){
    initiallyHorizontal = hor;
}

QPoint ShipButton::getInitialPosition(){
    return initialPosition;
}
bool ShipButton::getInitiallyHorizontal(){
    return initiallyHorizontal;
}

