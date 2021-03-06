//=============================================================================================================
/**
 * @file     tmsiimpedancescene.cpp
 * @author   Christoph Dinh <chdinh@nmr.mgh.harvard.edu>;
 *           Lorenz Esch <lesch@mgh.harvard.edu>
 * @version  dev
 * @date     June, 2014
 *
 * @section  LICENSE
 *
 * Copyright (C) 2014, Christoph Dinh, Lorenz Esch. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that
 * the following conditions are met:
 *     * Redistributions of source code must retain the above copyright notice, this list of conditions and the
 *       following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
 *       the following disclaimer in the documentation and/or other materials provided with the distribution.
 *     * Neither the name of MNE-CPP authors nor the names of its contributors may be used
 *       to endorse or promote products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * @brief    Contains the implementation of the TMSIImpedanceScene class.
 *
 */

//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include "tmsiimpedancescene.h"

//=============================================================================================================
// USED NAMESPACES
//=============================================================================================================

using namespace TMSIPLUGIN;
using namespace std;

//=============================================================================================================
// DEFINE MEMBER METHODS
//=============================================================================================================

TMSIImpedanceScene::TMSIImpedanceScene(QGraphicsView* view, QObject* parent)
: QGraphicsScene(parent)
, m_bRightMouseKeyPressed(false)
, m_qvView(view)
{
}

//=============================================================================================================

void TMSIImpedanceScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->button() == Qt::RightButton)
        m_bRightMouseKeyPressed = true;

    QGraphicsScene::mousePressEvent(event);
}

//=============================================================================================================

void TMSIImpedanceScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if(m_bRightMouseKeyPressed)
    {
        if(m_mousePosition.x()-event->scenePos().x() > 0) // user moved mouse to the left while pressing the right mouse key
            scaleElectrodePositions(0.99);

        if(m_mousePosition.x()-event->scenePos().x() < 0) // user moved mouse to the right while pressing the right mouse key
            scaleElectrodePositions(1.01);
    }

    m_mousePosition = event->scenePos();

    QGraphicsScene::mouseMoveEvent(event);
}

//=============================================================================================================

void TMSIImpedanceScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->button() == Qt::RightButton)
        m_bRightMouseKeyPressed = false;

    QGraphicsScene::mouseReleaseEvent(event);
}

//=============================================================================================================

void TMSIImpedanceScene::scaleElectrodePositions(double scaleFactor)
{
    // Get scene items
    QList< QGraphicsItem *> itemList = this->items();

    // Update position
    for(int i = 0; i<itemList.size(); i++)
    {
        TMSIElectrodeItem* item = (TMSIElectrodeItem *) itemList.at(i);

        // Set both positions -> dunno why :-)
        item->setPosition(item->getPosition()*scaleFactor);
        item->setPos(item->pos()*scaleFactor);
    }

    this->update(this->sceneRect());
}

