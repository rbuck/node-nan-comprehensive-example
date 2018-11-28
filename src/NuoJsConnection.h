#ifndef NUOJS_CONNECTION
#define NUOJS_CONNECTION

// Copyright (c) 2018, NuoDB, Inc.
// All rights reserved.
//
// Redistribution and use permitted under the terms of the 3-clause BSD license.

#include "NuoJsAddon.h"

namespace NuoJs
{
class Connection : public Nan::ObjectWrap
{
public:
    Connection();
    virtual ~Connection();

    static NAN_MODULE_INIT(init);

    static NAN_METHOD(newInstance);

    static Local<Object> createFrom(uintptr_t handle);

private:

    static NAN_METHOD(destroy);
    friend class DestroyConnectionWorker;
    void asyncDestroy();

    // Nan::Persistent<Object> jsDriver;

    static Nan::Persistent<FunctionTemplate> constructor;
};
}

#endif
