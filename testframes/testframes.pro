#--------------------------------------------------------------------------------------------------------------
#
# @file     testframes.pro
# @author   Christoph Dinh <chdinh@nmr.mgh.harvard.edu>;
#           Matti Hamalainen <msh@nmr.mgh.harvard.edu>
# @version  1.0
# @date     July, 2012
#
# @section  LICENSE
#
# Copyright (C) 2012, Christoph Dinh and Matti Hamalainen. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without modification, are permitted provided that
# the following conditions are met:
#     * Redistributions of source code must retain the above copyright notice, this list of conditions and the
#       following disclaimer.
#     * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
#       the following disclaimer in the documentation and/or other materials provided with the distribution.
#     * Neither the name of MNE-CPP authors nor the names of its contributors may be used
#       to endorse or promote products derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
# WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
# PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
# INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
# NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
#
# @brief    This project file generates the makefile to build the unit tests.
#
#--------------------------------------------------------------------------------------------------------------

include(../mne-cpp.pri)

TEMPLATE = subdirs

SUBDIRS += \
    test_codecov \
    test_fiff_rwr
#    test_mne_libs \
#    test_mne_rt \
#    mne_x_plugin_com \
#    test_mne_future \
#    test_ssp \

#!contains(MNECPP_CONFIG, minimalVersion) {
#    SUBDIRS += \
#        test_mne_graph \
#        test_mne_cluster_eval \
#        test_rap_cluster_eval \
#        test_rtc_eval \
#        test_rap_eval \
#       test_orig_rap_cluster_eval \

#    qtHaveModule(3dcore,3drender,3dinput,3dextras) {
#        message(testframes.pro - Qt3D available)
#        message(Qt3D available && QTVersion >= Qt 5.7: mne 3D tests configured!)
#        SUBDIRS += \
#            mne_3d_widget \
#            test_mne_cluster \
#            test_mne_surface \
#            test_mne_stc \
#    }
#}