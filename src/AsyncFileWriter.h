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

#ifndef ASYNCJPEGWRITER_H
#define ASYNCJPEGWRITER_H

#include <QObject>
#include <QWaitCondition>
#include <QMutex>
#include <QThread>

#include "AsyncQueue.h"
#include "FastAllocator.h"
#include <memory>

struct FileWriterTask
{
    //QByteArray data;
    std::unique_ptr<unsigned char, FastAllocator> data;
    unsigned int size{};
    QString fileName;
};

class AsyncFileWriter : public QObject
{
    Q_OBJECT
public:
    explicit AsyncFileWriter(int size = -1, QObject *parent = nullptr);
    ~AsyncFileWriter() override;

    void start();
    void stop();
    void put(FileWriterTask* task);
    void clear();
    void wake(){mStart.wakeAll();}
    void waitFinish();
    void setMaxSize(int sz);
    int  queueSize(){return mTasks.count();}
    int  getProcessedFrames(){return mProcessed;}
    int  getDroppedFrames(){return mDropped;}

signals:
    void progress(int percent);

public slots:

private:
    bool mCancel {false};
    bool mWriting {false};

    QMutex mLock;
    QWaitCondition mStart;
    QWaitCondition mFinish;
    QThread mWorkThread;
    AsyncQueue<FileWriterTask*> mTasks;

    void startWriting();
    void processTask(FileWriterTask* task);

    int mMaxSize = -1;
    int mProcessed = 0;
    int mDropped = 0;

    const uint maxQueuSize = 1024;
};

#endif // ASYNCJPEGWRITER_H
