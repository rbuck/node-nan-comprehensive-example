// Copyright (c) 2018, NuoDB, Inc.
// All rights reserved.
//
// Redistribution and use permitted under the terms of the 3-clause BSD license.

#include "NuoJsDriver.h"
#include "NuoJsConnection.h"

namespace NuoJs
{

Nan::Persistent<FunctionTemplate> Driver::constructor;

Driver::Driver()
    : Nan::ObjectWrap()
{
    TRACE("Driver::Driver");
}

/* virtual */
Driver::~Driver()
{
    TRACE("Driver::~Driver");
}

/* static */
NAN_MODULE_INIT(Driver::init)
{
    TRACE("Driver::init");
    Nan::HandleScope scope;

    // prepare constructor template...
    Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(newInstance);
    tpl->SetClassName(Nan::New("Driver").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    // prototypes...
    Nan::SetPrototypeMethod(tpl, "connect", connect);
    Nan::SetPrototypeMethod(tpl, "destroy", destroy);

    constructor.Reset(tpl);
    target->Set(Nan::New("Driver").ToLocalChecked(), tpl->GetFunction());
}

/* static */
NAN_METHOD(Driver::newInstance)
{
    TRACE("Driver::newInstance");
    Driver* driver = new Driver();
    driver->Wrap(info.This());
    driver->Ref(); // ?
    info.GetReturnValue().Set(info.This());
}

class ConnectWorker : public Nan::AsyncWorker
{
public:
    ConnectWorker(Nan::Callback* callback, Driver* driver)
        : Nan::AsyncWorker(callback), driver(driver)
    {
        TRACE("ConnectWorker::ConnectWorker");
    }

    ~ConnectWorker()
    {
        TRACE("ConnectWorker::~ConnectWorker");
    }

    virtual void Execute()
    {
        TRACE("ConnectWorker::Execute");
        /* Sample Code:
        NuoDB::Connection* connection = NuoDB::Connection::create();
        NuoDB::Properties* properties = propertiesFrom(parameters);
        connection->openDatabase(string, propeties);
        */
        driver->asyncConnect();
    }

    virtual void HandleOKCallback()
    {
        TRACE("ConnectWorker::HandleOKCallback");
        Nan::HandleScope scope;
        // Local<Object> jsonObject = Nan::New<Object>();
        // /* Sample Code:
        int* ptr = new int; // todo: get actual ptr to nuo connection
    TRACE("<< ----- NOFAULT");
        printf("here");
        Local<Object> jsonObject = Connection::createFrom(reinterpret_cast<uintptr_t>(ptr));
        // */
        Local<Value> argv[] = {
            Nan::Null(),
            jsonObject
        };
        callback->Call(2, argv, async_resource);
    }
protected:
    Driver* driver;
};

/* static */
NAN_METHOD(Driver::connect)
{
    TRACE("Driver::connect");
    Driver* driver = Nan::ObjectWrap::Unwrap<Driver>(info.This());

    if (!info.Length() || !info[(info.Length() - 1)]->IsFunction()) {
        Nan::ThrowError("connect arg count zero, or last arg is not a function");
        return;
    }
    Nan::Callback* callback = new Nan::Callback(info[info.Length() - 1].As<Function>());

    ConnectWorker* worker = new ConnectWorker(
        callback, driver);
    worker->SaveToPersistent("nuodb:Driver", info.This());
    Nan::AsyncQueueWorker(worker);
}

void Driver::asyncConnect()
{
    TRACE("Driver::asyncConnect");
}

class DestroyWorker : public Nan::AsyncWorker
{
public:
    DestroyWorker(Nan::Callback* callback, Driver* driver)
        : Nan::AsyncWorker(callback), driver(driver)
    {
        TRACE("DestroyWorker::DestroyWorker");
    }

    ~DestroyWorker()
    {
        TRACE("DestroyWorker::~DestroyWorker");
    }

    virtual void Execute()
    {
        TRACE("DestroyWorker::Execute");
        driver->asyncDestroy();
    }

    virtual void HandleOKCallback()
    {
        TRACE("DestroyWorker::HandleOKCallback");
        Nan::HandleScope scope;
        Local<Value> argv[] = {
            Nan::Null()
        };
        callback->Call(1, argv, async_resource);
    }
protected:
    Driver* driver;
};

/* static */
NAN_METHOD(Driver::destroy)
{
    TRACE("Driver::destroy");
    Driver* driver = Nan::ObjectWrap::Unwrap<Driver>(info.This());

    if (!info.Length() || !info[(info.Length() - 1)]->IsFunction()) {
        Nan::ThrowError("connect arg count zero, or last arg is not a function");
        return;
    }
    Nan::Callback* callback = new Nan::Callback(info[info.Length() - 1].As<Function>());
    DestroyWorker* worker = new DestroyWorker(
        callback, driver);
    worker->SaveToPersistent("nuodb:Driver", info.This());
    Nan::AsyncQueueWorker(worker);
}

void Driver::asyncDestroy()
{
    TRACE("Driver::asyncDestroy");
}
}
