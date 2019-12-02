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

#ifndef FPNREADER_H
#define FPNREADER_H
#include <QString>
#include <QFileInfo>
#include <QMap>

#include "FastAllocator.h"
#include "fastvideo_sdk.h"
#include <memory>

#define gFPNStore FPNStore::Instance()

class FPNReader
{
public:
    FPNReader(const QString& fileName);
    unsigned int width(){return mWidth;}
    unsigned int height(){return mHeight;}
    unsigned int pitch(){return mPitch;}
    unsigned int bpp(){return mBpp;}
    bool isValid(){return mWidth > 0 && mHeight > 0 && mFPNBuffer;}
    void* data(){return mFPNBuffer.get();}

private:
    void readPGM(const QString& fileName);

    unsigned int mWidth;
    unsigned int mHeight;
    unsigned int mPitch;
    unsigned int mBpp;

    std::unique_ptr<unsigned char, FastAllocator> mFPNBuffer;

    QString mFileName;
};

class FPNStore
{
    // Maps file name to FFC as cache
    QMap<QString, FPNReader*> fpnCache;

public:
    ~FPNStore();
    void* getFPN(const QString& filename);
    FPNReader* getReader(const QString& filename);
    void clear();
    QList<QString> files(){return fpnCache.keys();}

    static FPNStore* Instance();
};

#endif // FPNREADER_H
