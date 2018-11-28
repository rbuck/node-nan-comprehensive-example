#ifndef NUOJS_ADDON
#define NUOJS_ADDON

// Copyright (c) 2018, NuoDB, Inc.
// All rights reserved.
//
// Redistribution and use permitted under the terms of the 3-clause BSD license.

#include <v8.h>
#include <node.h>
#include <nan.h>

using namespace v8;

// #define ENABLE_TRACE 0

#define LOG(msg) fprintf(stderr, "%s\n", msg);

#ifdef ENABLE_TRACE
# define TRACE(msg) LOG(msg);
#else
# define TRACE(msg)
#endif

#endif
