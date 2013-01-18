//=============================================================================================================
/**
* @file     fiff_cov.cpp
* @author   Christoph Dinh <chdinh@nmr.mgh.harvard.edu>;
*           Matti Hamalainen <msh@nmr.mgh.harvard.edu>
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
* @brief    Implementation of the FiffCov Class.
*
*/

//*************************************************************************************************************
//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include "fiff_cov.h"

#include <iostream>


//*************************************************************************************************************
//=============================================================================================================
// USED NAMESPACES
//=============================================================================================================

using namespace FIFFLIB;


//*************************************************************************************************************
//=============================================================================================================
// DEFINE MEMBER METHODS
//=============================================================================================================

FiffCov::FiffCov()
: kind(-1)
, diag(false)
, dim(-1)
, nfree(-1)
{

}


//*************************************************************************************************************

FiffCov::FiffCov(const FiffCov &p_FiffCov)
: QSharedData(p_FiffCov)
, kind(p_FiffCov.kind)
, diag(p_FiffCov.diag)
, dim(p_FiffCov.dim)
, names(p_FiffCov.names)
, data(p_FiffCov.data)
, projs(p_FiffCov.projs)
, bads(p_FiffCov.bads)
, nfree(p_FiffCov.nfree)
, eig(p_FiffCov.eig)
, eigvec(p_FiffCov.eigvec)
{

}


//*************************************************************************************************************

FiffCov::~FiffCov()
{
}


//*************************************************************************************************************

void FiffCov::clear()
{
    kind = -1;
    diag = false;
    dim = -1;
    names.clear();
    data = MatrixXd();
    projs.clear();
    bads.clear();
    nfree = -1;
    eig = VectorXd();
    eigvec = MatrixXd();
}


//*************************************************************************************************************

FiffCov FiffCov::prepare_noise_cov(FiffInfo& p_Info, QStringList& p_ChNames)
{
    FiffCov p_NoiseCov(*this);

    VectorXi C_ch_idx = VectorXi::Zero(p_NoiseCov.names.size());
    qint32 count = 0;
    for(qint32 i = 0; i < p_ChNames.size(); ++i)
    {
        qint32 idx = p_NoiseCov.names.indexOf(p_ChNames[i]);
        if(idx > -1)
        {
            C_ch_idx[count] = idx;
            ++count;
        }
    }
    C_ch_idx.conservativeResize(count);

    MatrixXd C(count, count);
    for(qint32 i = 0; i < count; ++i)
        for(qint32 j = 0; j < count; ++j)
            C(i,j) = p_NoiseCov.data(C_ch_idx(i), C_ch_idx(j));

    MatrixXd proj;
    qint32 ncomp = p_Info.make_projector_info(proj);

    //Create the projection operator
    if (ncomp > 0)
    {
        printf("Created an SSP operator (subspace dimension = %d)\n", ncomp);

        C = proj * (C * proj.transpose());
    }

    MatrixXi pick_meg = p_Info.pick_types(true, false, false, defaultQStringList, p_Info.bads);
    MatrixXi pick_eeg = p_Info.pick_types(false, true, false, defaultQStringList, p_Info.bads);

    QStringList meg_names, eeg_names;

    for(qint32 i = 0; i < pick_meg.size(); ++i)
        meg_names << p_Info.chs[pick_meg(0,i)].ch_name;
    VectorXi C_meg_idx = VectorXi::Zero(p_NoiseCov.names.size());
    count = 0;
    for(qint32 k = 0; k < C.rows(); ++k)
    {
        if(meg_names.indexOf(p_ChNames[k]) > -1)
        {
            C_meg_idx(count) = k;
            ++count;
        }
    }
    C_meg_idx.conservativeResize(count);

    //
    for(qint32 i = 0; i < pick_eeg.size(); ++i)
        eeg_names << p_Info.chs[pick_eeg(0,i)].ch_name;
    VectorXi C_eeg_idx = VectorXi::Zero(p_NoiseCov.names.size());
    count = 0;
    for(qint32 k = 0; k < C.rows(); ++k)
    {
        if(eeg_names.indexOf(p_ChNames[k]) > -1)
        {
            C_eeg_idx(count) = k;
            ++count;
        }
    }
    C_eeg_idx.conservativeResize(count);

    qDebug()  << "ncomp " << ncomp;

    return p_NoiseCov;
}
