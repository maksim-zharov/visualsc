#ifndef ELBOWGRABBER_H
#define ELBOWGRABBER_H

#include <QGraphicsItem>
#include "transitiongraphic.h"
#include "selectablelinesegmentgraphic.h"

class TransitionGraphic;

class ElbowGrabber : public QGraphicsItem, public QObject
{

public:
    ElbowGrabber(TransitionGraphic* parentGraphic);
    ElbowGrabber(TransitionGraphic *parentGraphic, SelectableLineSegmentGraphic* start, SelectableLineSegmentGraphic* end);
    ElbowGrabber(TransitionGraphic *parentGraphic, SelectableLineSegmentGraphic* start, SelectableLineSegmentGraphic* end, int x, int y);
    ~ElbowGrabber();
    void setAngle(int agle);///< set the rotation angle for corners which are drawn as arrowheads
    int  getCorner(); ///< allows the owner to find out which coner this is
    void setMouseState(int); ///< allows the owner to record the current mouse state
    int  getMouseState(); ///< allows the owner to get the current mouse state
    QPointF getCenterPoint();

    qreal mouseDownX;
    qreal mouseDownY;

    enum {kMouseReleased=0, kMouseDown, kMouseMoving}; ///< define the mouse states

    enum PaintStyle {kBox, kCrossHair, kArrowHead};
    void setPaintStyle(PaintStyle s);///< set box or cross-hairs

    virtual QRectF boundingRect() const; ///< must be re-implemented in this class to provide the diminsions of the box to the QGraphicsView

private:


    virtual void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); ///< must be re-implemented here to pain the box on the paint-event
    virtual void hoverEnterEvent ( QGraphicsSceneHoverEvent * event ); ///< must be re-implemented to handle mouse hover enter events
    virtual void hoverLeaveEvent ( QGraphicsSceneHoverEvent * event ); ///< must be re-implemented to handle mouse hover leave events

    // once the hover event handlers are implemented in this class,
    // the mouse events must also be implemented because of
    // some linkage issue - apparrently there is some connection
    // between the hover events and mouseMove/Press/Release
    // events which triggers a vtable issue
    virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );
    virtual void mouseMoveEvent(QGraphicsSceneDragDropEvent *event);
    virtual void mousePressEvent (QGraphicsSceneMouseEvent * event );
    virtual void mousePressEvent(QGraphicsSceneDragDropEvent *event);
    virtual void mouseReleaseEvent (QGraphicsSceneMouseEvent * event );

    QColor _outterborderColor; ///< the hover event handlers will toggle this between red and black
    QPen _outterborderPen; ///< the pen is used to paint the red/black border

    qreal   _width;
    qreal   _height;

    int _corner;// 0,1,2,3  - starting at x=0,y=0 and moving clockwise around the box

    int _mouseButtonState;
    bool _placedOnASquare;

    PaintStyle _paintStyle;
    int        _arrowAngle;
    ArrowHeadGraphic * _arrowHead;

    SelectableLineSegmentGraphic* _start;
    SelectableLineSegmentGraphic* _end;
};

#endif // ELBOWGRABBER_H
