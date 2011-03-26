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
#ifndef SCSTATE_H
#define SCSTATE_H
#include <QMetaType>
#include <QObject>
#include <QList>
#include "stateattributes.h"
#include "sctransition.h"
class QString;

class QXmlStreamWriter;
class QPoint;
class QStandardItem;

#include "scdatamodel_global.h"



class SCDATAMODELSHARED_EXPORT  SCState : public QObject
{
    Q_OBJECT
public:
    explicit SCState(QObject *parent = 0);
    explicit SCState(const SCState& st);
    ~SCState();

    void setStateName(QString n);
    void addTransistion(SCTransition*);
    void addState(SCState *);
   // void makeTargetConnections(QList<SCTransition*> & transitionList);

    void setAttributeValue(QString key, QString value);
    QString getAttributeValue(QString key);

    int  getStateCount();

    void setParentItem(QStandardItem * item);
    void setItem(QStandardItem * item);

    QStandardItem * getParentItem();
    QStandardItem * getItem();

    void setSize (QPointF& size);
    void setSize (QPoint& size);
    void setPosition (QPointF& size);

    /**
      * \fn getAllTransitions
      * \brief Get all transitions including decendant state's transitions
      *
      */
     void getAllTransitions( QList<SCTransition*> & list);

     /**
       * \fn getTransitions
       * \brief Get transitions of this state only
       *
       */

     void getTransitions(QList<SCTransition*> & transitionList);

    /**
      * \fn getStates
      * \brief Get direct children states, no decendants
      *
      */
    void getStates(QList<SCState *> & stateList);

    /**
      * \fn getAllStates
      * \brief Get all states, including decendants
      *
      */
    void getAllStates(QList<SCState *> & stateList);



    /**
      * \fn writeSCVXML
      * \brief Write out the SCXML for the entire tree from this point downward
      * \param xmlWriter is the writer that writes the xml
      *
      */
    void writeSCVXML(QXmlStreamWriter & xmlWriter);


    StateAttributes         attributes;

signals:

     void changed();



public slots:


 private slots:


private:

    int                     _stateCount;
    QStandardItem *         _parentDMItem;
    QStandardItem *         _thisDMItem;

    void initCommon();

};

Q_DECLARE_METATYPE (SCState*)


#endif // SCSTATE_H
