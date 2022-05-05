const db = require('../database');

const kortti = {
  getById: function(id, callback) {
    return db.query('select * from kortti where korttinumero=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from kortti', callback);
  },
  add: function(kortti, callback) {
    return db.query(
      'insert into kortti (korttinumero, tilinumero, pin) values(?,?,?)',
      [kortti.korttinumero, kortti.tilinumero, kortti.pin],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from kortti where korttinumero=?', [id], callback);
  },
  update: function(id, kortti, callback) {
    return db.query(
      'update kortti set korttinumero=?, tilinumero=?, pin=? where korttinumero=?',
      [kortti.korttinumero, kortti.tilinumero, kortti.pin, id],
      callback
    );
  }
};
module.exports = kortti;