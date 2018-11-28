// Copyright (c) 2018, NuoDB, Inc.
// All rights reserved.
//
// Redistribution and use permitted under the terms of the 3-clause BSD license.

'use strict';

var addon = require('bindings')('nuodb.node');

var driver = new addon.Driver();
// extend(driver);

module.exports = driver;
