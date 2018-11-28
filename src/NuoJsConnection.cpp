// Copyright (c) 2018, NuoDB, Inc.
// All rights reserved.
//
// Redistribution and use permitted under the terms of the 3-clause BSD license.

#include "NuoJsConnection.h"

namespace NuoJs
{
Nan::Persistent<FunctionTemplate> Connection::constructor;

Connection::Connection()
    : Nan::ObjectWrap()
{
    TRACE("Connection::Connection");
}

/* virtual */
Connection::~Connection()
{
    TRACE("Connection::~Connection");
    printf("destructor called\n");
    // jsDriver.Reset();
}

/* static */
NAN_MODULE_INIT(Connection::init)
{
    TRACE("Connection::init");
    Nan::HandleScope scope;

    // prepare constructor template...
    Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(newInstance);
    tpl->SetClassName(Nan::New("Connection").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    // prototypes...
    Nan::SetPrototypeMethod(tpl, "destroy", destroy);

    constructor.Reset(tpl);
    target->Set(Nan::New("Connection").ToLocalChecked(), tpl->GetFunction());
}

/* static */
NAN_METHOD(Connection::newInstance)
{
    TRACE("Connection::newInstance");
    if (info.IsConstructCall()) {
        Connection* connection = new Connection();
        printf("ptr: %p\n", (void*)connection);
        connection->Wrap(info.This());
        connection->Ref();
        info.GetReturnValue().Set(info.This());
    } else {
        printf("-------------------- NOT HERE\n");
    }
}

/* static */
Local<Object> Connection::createFrom(uintptr_t handle)
{
    Nan::EscapableHandleScope scope;

    Local<Function> cons = Nan::GetFunction(Nan::New<FunctionTemplate>(constructor)).ToLocalChecked();
    TRACE("<< ----- NOFAULT");
    Local<Object> obj = Nan::NewInstance(cons).ToLocalChecked();
    
    Connection* connection = Nan::ObjectWrap::Unwrap<Connection>(obj);
    printf("ptr: %p\n", (void*)connection);
    
    // connection->jsDriver.Reset(baton->jsDriver);
    /* Sample Code:
    connection->ref = reinterpret_cast<NuoDB::Connection*>(handle);
    */

    return scope.Escape(obj);
}

class DestroyConnectionWorker : public Nan::AsyncWorker
{
public:
    DestroyConnectionWorker(Nan::Callback* callback, Connection* connection)
        : Nan::AsyncWorker(callback), connection(connection)
    {
        TRACE("DestroyConnectionWorker::DestroyConnectionWorker");
    }

    ~DestroyConnectionWorker()
    {
        TRACE("DestroyConnectionWorker::~DestroyConnectionWorker");
    }

    virtual void Execute()
    {
        TRACE("DestroyConnectionWorker::Execute");
        connection->asyncDestroy();
    }

    virtual void HandleOKCallback()
    {
        TRACE("DestroyConnectionWorker::HandleOKCallback");
        Nan::HandleScope scope;
        connection->Unref();

        Local<Value> argv[] = {
            Nan::Null()
        };
        callback->Call(1, argv, async_resource);
    }
protected:
    Connection* connection;
};

/* static */
NAN_METHOD(Connection::destroy)
{
    TRACE("Connection::destroy");
    Connection* connection = Nan::ObjectWrap::Unwrap<Connection>(info.This());

    if (!info.Length() || !info[(info.Length() - 1)]->IsFunction()) {
        Nan::ThrowError("connect arg count zero, or last arg is not a function");
        return;
    }
    Nan::Callback* callback = new Nan::Callback(info[info.Length() - 1].As<Function>());
    DestroyConnectionWorker* worker = new DestroyConnectionWorker(
        callback, connection);
    worker->SaveToPersistent("nuodb:Connection", info.This());
    Nan::AsyncQueueWorker(worker);

}

void Connection::asyncDestroy()
{
    TRACE("Connection::asyncDestroy");
}
}
