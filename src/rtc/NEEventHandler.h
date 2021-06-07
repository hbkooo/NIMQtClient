//
// Created by 19216 on 2021/6/7.
//

#ifndef NIMQTCLIENT_NEEVENTHANDLER_H
#define NIMQTCLIENT_NEEVENTHANDLER_H

#include <QObject>

#include "nertc_engine_ex.h"

using namespace nertc;

class NERtcEngine;

class NEEventHandler : public QObject, public IRtcEngineEventHandlerEx{
Q_OBJECT

public:
    explicit NEEventHandler(NERtcEngine *engine);

    ~NEEventHandler() = default;

private:
    NERtcEngine *neRtcEngine;
};


#endif //NIMQTCLIENT_NEEVENTHANDLER_H
