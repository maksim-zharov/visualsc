#ifndef TEXTBLOCK_H
#define TEXTBLOCK_H

#include "textblockattributes.h"
#include <QXmlStreamWriter>
//#include "scstate.h"
#include "scitem.h"
#include "stateattributes.h"
#include "transitionattributes.h"

/**

  \class   SCTextBlock
  \ingroup DataModel
  \brief   The class represents a text-block in a state-chart Data-Model

  A SCTextBlock only has attributes and text.

*/
#define TEXTBLOCK_DEFAULT_WIDTH     137
#define TEXTBLOCK_DEFAULT_HEIGHT    40
#define TEXTBLOCK_DEFAULT_X         10
#define TEXTBLOCK_DEFAULT_Y         10
class SCDATAMODELSHARED_EXPORT SCTextBlock : public SCItem
{
    Q_OBJECT

public:
    SCTextBlock();
    //SCTextBlock(const SCState& st);
    virtual IAttributeContainer * getAttributes(); // reimplemented from base SCItem
    TextBlockAttributes attributes;
    QString getText();
    void    setText(QString);
    void writeSCVXML(QXmlStreamWriter & sw);

    SizeAttribute* getSizeAttr();
    PositionAttribute* getPosAttr();


public slots:
    void handleAttributeChanged(IAttribute *attr);
    void handleAttributeChanged(StateName*);
    void handleAttributeChanged(TransitionStringAttribute*);

signals:
     void textChanged();
     void positionChangedInDataModel(SCTextBlock*, QPointF);
     void sizeChangedInDataModel(SCTextBlock*, QPointF);

private:

    QString _text;
};


Q_DECLARE_METATYPE (SCTextBlock*)


#endif // TEXTBLOCK_H
