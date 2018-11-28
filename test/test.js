'use strict';

var nuodb = require('../lib');

var config = {};

config.database = 'test';
config.hostname = 'ad1';
config.port = '48004';
config.user = 'dba';
config.password = 'dba';
config.schema = 'USER';

for (let i = 0; i < 20; i++) {
  nuodb.connect(config, function (err, connection) {
    console.log('connected');
    console.log("typename: " + connection.constructor.name);
    if (err) {
      console.error(err.message);
      return;
    }
    connection.destroy(function (err) {
      if (err) {
        console.error(err.message);
        return;
      }
    });
  });
}
