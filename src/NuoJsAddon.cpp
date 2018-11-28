// Copyright (c) 2018, NuoDB, Inc.
// All rights reserved.
//
// Redistribution and use permitted under the terms of the 3-clause BSD license.

#include "NuoJsAddon.h"
#include "NuoJsDriver.h"
#include "NuoJsConnection.h"

NAN_MODULE_INIT(initModule)
{
    TRACE("initModule");
    NuoJs::Driver::init(target);
    NuoJs::Connection::init(target);
}

NODE_MODULE(nuodb, initModule);
