/*
 Copyright 2011-2019 Fastvideo, LLC.
 All rights reserved.

 This file is a part of the GPUCameraSample project
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 3. Any third-party SDKs from that project (XIMEA SDK, Fastvideo SDK, etc.) are licensed on different terms. Please see their corresponding license terms.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 The views and conclusions contained in the software and documentation are those
 of the authors and should not be interpreted as representing official policies,
 either expressed or implied, of the FreeBSD Project.
*/

#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QSettings>
#include <QVector>
#include <QPointF>
#include "fastvideo_sdk.h"


class AppSettingsStorage : public QSettings
{
    Q_OBJECT
public:
    AppSettingsStorage();

private:
    Q_DISABLE_COPY(AppSettingsStorage)
};

class AppSettings
{
public:
    AppSettings();
    void save();

    QString lastProjectPath;
    QString lastLoadImgPath;
    QString lastDCPProfile;

    bool useSystemICCProfile;
    bool useProjectColorSpace;
    QString customICCProfile;

    unsigned maxOutWidth;
    unsigned maxOutHeight;

    unsigned maxInputWidth;
    unsigned maxInputHeight;

    //Defaults
    QString rootPath;
    
    QString localeName;
    fastJpegFormat_t jpegPixelFormat;
    int jpegQty;

    bool fixBadPixels;
};

#endif // APPSETTINGS_H
