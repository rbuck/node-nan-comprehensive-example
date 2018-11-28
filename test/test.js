'use strict';

var nuodb = require('../lib');

var config = {};

config.database = 'test';
config.hostname = 'ad1';
config.port = '48004';
config.user = 'dba';
config.password = 'dba';
config.schema = 'USER';

for (let i = 0; i < 20000; i++) {
  nuodb.connect(config, function (err, connection) {
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
