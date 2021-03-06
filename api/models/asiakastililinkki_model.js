const db = require('../database');

const asiakastililinkki = {
  getById: function(id, callback) {
    return db.query('select * from asiakastililinkki where idAsiakas=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from asiakastililinkki', callback);
  },
  add: function(asiakastililinkki, callback) {
    return db.query(
      'insert into asiakastililinkki (idAsiakas,tilinumero) values(?,?)',
      [asiakastililinkki.idAsiakas, asiakastililinkki.tilinumero],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from asiakastililinkki where idAsiakas=?', [id], callback);
  },
  update: function(id, asiakastililinkki, callback) {
    return db.query(
      'update asiakastililinkki set idAsiakas=?,tilinumero=? where idAsiakas=?',
      [asiakastililinkki.idAsiakas, asiakastililinkki.tilinumero, id],
      callback
    );
  }
};
module.exports = asiakastililinkki;