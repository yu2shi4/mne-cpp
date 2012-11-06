//=============================================================================================================
/**
* @file     fiffstreamserver.h
* @author   Christoph Dinh <chdinh@nmr.mgh.harvard.edu>;
*           Matti Hämäläinen <msh@nmr.mgh.harvard.edu>
* @version  1.0
* @date     July, 2012
*
* @section  LICENSE
*
* Copyright (C) 2012, Christoph Dinh and Matti Hamalainen. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that
* the following conditions are met:
*     * Redistributions of source code must retain the above copyright notice, this list of conditions and the
*       following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
*       the following disclaimer in the documentation and/or other materials provided with the distribution.
*     * Neither the name of the Massachusetts General Hospital nor the names of its contributors may be used
*       to endorse or promote products derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL MASSACHUSETTS GENERAL HOSPITAL BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*
* @brief    Contains the implementation of the FiffStreamServer Class.
*
*/

#ifndef FIFFSTREAMSERVER_H
#define FIFFSTREAMSERVER_H

//*************************************************************************************************************
//=============================================================================================================
// FIFF INCLUDES
//=============================================================================================================

#include "../../MNE/fiff/fiff_info.h"


//*************************************************************************************************************
//=============================================================================================================
// QT INCLUDES
//=============================================================================================================

#include <QStringList>
#include <QTcpServer>


//*************************************************************************************************************
//=============================================================================================================
// DEFINE NAMESPACE MSERVER
//=============================================================================================================

namespace MSERVER
{

//*************************************************************************************************************
//=============================================================================================================
// USED NAMESPACES
//=============================================================================================================

using namespace FIFFLIB;


//*************************************************************************************************************
//=============================================================================================================
// FORWARD DECLARATIONS
//=============================================================================================================

class FiffStreamThread;

//=============================================================================================================
/**
* DECLARE CLASS FiffStreamServer
*
* @brief The FiffStreamServer class provides
*/
class FiffStreamServer : public QTcpServer
{
    Q_OBJECT

    friend class CommandServer;
    friend class CommandThread;

public:

    FiffStreamServer(QObject *parent = 0);

    //=========================================================================================================
    /**
    * Destroys the FiffStreamServer.
    */
    ~FiffStreamServer();

    //=========================================================================================================
    /**
    * ToDo...
    */
    inline FiffStreamThread* getClient(qint32 id);

    //=========================================================================================================
    /**
    * ToDo...
    */
    void clearClients();

//public slots: --> in Qt 5 not anymore declared as slot
//    void readCommandServerInstruction();
    void forwardMeasInfo(qint32 ID, FiffInfo* p_pFiffInfo);

signals:
//    void sendFiffStreamThreadInstruction(quint8 id, quint8 instruction);
    void sendMeasInfo(qint32 ID, FIFFLIB::FiffInfo* p_pFiffInfo);



protected:
    void incomingConnection(qintptr socketDescriptor);

private:
    QMap<qint32, FiffStreamThread*> m_qClientList;
    qint32                          m_iNextClientId;

};


//*************************************************************************************************************
//=============================================================================================================
// INLINE DEFINITIONS
//=============================================================================================================

FiffStreamThread* FiffStreamServer::getClient(qint32 id)
{
    return m_qClientList[id];
}

} // NAMESPACE

#endif //FIFFSTREAMSERVER_H
