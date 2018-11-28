#ifndef NUOJS_DRIVER
#define NUOJS_DRIVER

// Copyright (c) 2018, NuoDB, Inc.
// All rights reserved.
//
// Redistribution and use permitted under the terms of the 3-clause BSD license.

#include "NuoJsAddon.h"

namespace NuoJs
{
class Driver : public Nan::ObjectWrap
{
public:
    Driver();
    virtual ~Driver();

    static NAN_MODULE_INIT(init);

    static NAN_METHOD(newInstance);

private:

    static NAN_METHOD(connect);
    friend class ConnectWorker;
    void asyncConnect();

    static NAN_METHOD(destroy);
    friend class DestroyWorker;
    void asyncDestroy();

    static Nan::Persistent<v8::FunctionTemplate> constructor;
};
}

#endif
