/*
    visualsc - Visual State Chart Editing for SCXML State Engines
    Copyright (C) 2011  David W. Drell (david@davidwdrell.net) and
    Contributing Authors:


    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "cornergrabber.h"
#include "arrowheadgraphic.h"
#include <QDebug>
#include <QApplication>

#define PEN_THICKNESS 1.61803398875
#define WIDTH 5
#define HEIGHT 5

CornerGrabber::CornerGrabber(QGraphicsItem *parent,  int corner, bool placedOnASquare) :
    QGraphicsItem(parent),
    mouseDownX(0),
    mouseDownY(0),
    _outterborderColor(QColor(0,0,0,140)),
    _outterborderPen(),
    _width(WIDTH),
    _height(HEIGHT),
    _corner(corner),
    _mouseButtonState(kMouseReleased),
    _placedOnASquare(placedOnASquare),
    _paintStyle(kBox),
    _arrowAngle(0),
    _arrowHead(NULL),
    _isHovered(false)
{
   this->setParentItem(parent);
//    _outterborderPen.setWidth(2);
    _outterborderPen.setWidthF(PEN_THICKNESS);
    _outterborderPen.setColor(_outterborderColor);

   this->setAcceptHoverEvents(true);
}

void CornerGrabber::setPaintStyle(PaintStyle s)
{
    _paintStyle  = s;

    if (s == kArrowHead )
    {
        if ( ! _arrowHead )
        {
            _arrowHead = new ArrowHeadGraphic(this);  
            _arrowHead->setWidth(_width);
            _arrowHead->setHeight(_height);
            _arrowHead->setPos( - _width/2, - _height/2);
            _arrowHead->setColor(Qt::red);
        }
    }
    else
    {
        if ( _arrowHead )
        {
            delete _arrowHead;
            _arrowHead = NULL;
        }
    }
    this->update();
}

void CornerGrabber::setMouseState(int s)
{
    _mouseButtonState = s;
}

int CornerGrabber::getMouseState()
{
    return _mouseButtonState;
}

int CornerGrabber::getCorner()
{
    return _corner;
}


// we have to implement the mouse events to keep the linker happy,
// but just set accepted to false since are not actually handling them

void CornerGrabber::mouseMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    event->setAccepted(false);
}

void CornerGrabber::mousePressEvent(QGraphicsSceneDragDropEvent *event)
{
    event->setAccepted(false);
}

void CornerGrabber::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event )
{
    event->setAccepted(true);
}

void CornerGrabber::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{
    event->setAccepted(false);
}

void CornerGrabber::mouseMoveEvent ( QGraphicsSceneMouseEvent * event )
{
    event->setAccepted(false);
}


// change the color on hover events to indicate to the use the object has
// been captured by the mouse

void CornerGrabber::hoverLeaveEvent ( QGraphicsSceneHoverEvent * )
{
//    qDebug() << "CornerGrabber HoverLeaveEvent";
    _isHovered= false;
    _outterborderColor = QColor(0,0,0,140);

    // reset the cursor
    this->setCursorToResize(false);

    this->update(0,0,_width,_height);

    this->removeSceneEventFilter(this->parentItem());

}

void CornerGrabber::hoverEnterEvent ( QGraphicsSceneHoverEvent * )
{
//    qDebug() << "CornerGrabber HoverEnterEvent";
    _isHovered = true;
    _outterborderColor = QColor(255,0,0,140);

    // change the cursor to the diagonal sizer
    this->setCursorToResize(true);

    this->update(0,0,_width,_height);
    this->installSceneEventFilter(this->parentItem());
}

void CornerGrabber::setCursorToResize(bool on)
{
    if(on)
    {

//        if(QApplication::overrideCursor()->shape() == Qt::SizeFDiagCursor || QApplication::overrideCursor()->shape() == Qt::SizeFDiagCursor)
//            return;

        switch(_corner)
        {
        case 0:
        case 2:
            QApplication::setOverrideCursor(Qt::SizeFDiagCursor);
            break;

        case 1:
        case 3:
            QApplication::setOverrideCursor(Qt::SizeBDiagCursor);
            break;
        }
    }
    else
    {
        QApplication::restoreOverrideCursor();
    }
}

QRectF CornerGrabber::boundingRect() const
{
    int captureMargin = 12;
    QPointF topLeft (0-(_width/2)-captureMargin, 0-(_height/2)-captureMargin);
    QPointF bottomRight ( (_width/2)+captureMargin ,(_height/2)+captureMargin);

    QRectF rect (topLeft, bottomRight);
    return rect;
}

void CornerGrabber::setHovered(bool isHovered)
{
    _isHovered = isHovered;
}

bool CornerGrabber::isHovered()
{
    return _isHovered;
}

QPointF CornerGrabber::getCenterPoint()
{

     if (_placedOnASquare)
     {
         if ( _corner == 0 )
             return QPointF(pos().x() + _width/2,pos().y() + _height/2);
         else  if ( _corner == 1 )
             return QPointF(pos().x() - _width/2,pos().y() + _height/2);
         else  if ( _corner == 2 )
             return QPointF(pos().x() - _width/2,pos().y() - _height/2);
         else
             return QPointF(pos().x() + _width/2,pos().y() - _height/2);
     }
     else
     {
         return QPointF(pos()) ;
     }

}

void CornerGrabber::setAngle(int angle)
{
    _arrowAngle = angle - 45; // subtract 45 because of how we draw it
}

void CornerGrabber::paint (QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);

    if ( _paintStyle == kBox)
    {
        // fill the box with solid color, use sharp corners

        _outterborderPen.setCapStyle(Qt::SquareCap);
        _outterborderPen.setStyle(Qt::SolidLine);
        painter->setPen(_outterborderPen);

//        qDebug() << "corner pos: " << this->pos();
        QPointF topLeft (0-(_width/2), 0-(_height/2));
        QPointF bottomRight ( _width/2 ,_height/2);

        QRectF rect (topLeft, bottomRight);

        QBrush brush (Qt::SolidPattern);
        brush.setColor (_outterborderColor);

        if ( _outterborderColor == Qt::red)
        {
            painter->fillRect(rect,brush);
        }
        else
        {
            painter->drawRect(rect);
        }
    }
    else  if (_paintStyle == kCrossHair)
    {
        painter->setPen( _outterborderColor );

        // center of the box is at 0,0
        painter->drawLine( QPointF(0,0), QPointF(0,-(_height/2)) );
        painter->drawLine( QPointF(0,0), QPointF(0, (_height/2)) );
        painter->drawLine( QPointF(0,0), QPointF(-(_width/2) , 0) );
        painter->drawLine( QPointF(0,0), QPointF((_width/2) , 0) );
    }
    else  if (_paintStyle == kArrowHead)
    {
       // qDebug()<< "setting arrowhead angle: " << _arrowAngle;

        _arrowHead->setRotation(_arrowAngle);

        _arrowHead->update();
    }
    else if(_paintStyle == kNone)
    {
//qDebug() << "corner pos: " << this->pos();
    }
}
