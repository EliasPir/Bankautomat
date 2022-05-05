const db = require('../database');

const tilitapahtumat = {
  getById: function(id, callback) {
    return db.query('select * from tilitapahtumat where idTapahtuma=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from tilitapahtumat', callback);
  },
  add: function(tilitapahtumat, callback) {
    return db.query(
      'insert into tilitapahtumat (idTapahtuma, aika, tapahtuma, summa, tilinumero) values(?,now(),?,?,?)',
      [tilitapahtumat.idTapahtuma, tilitapahtumat.tapahtuma, tilitapahtumat.summa, tilitapahtumat.tilinumero],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from tilitapahtumat where idTapahtuma=?', [id], callback);
  },
  update: function(id, tilitapahtumat, callback) {
    return db.query(
      'update tilitapahtumat set idTapahtuma=?, tapahtuma=?, summa=?, tilinumero=? where idTapahtuma=?',
      [tilitapahtumat.idTapahtuma, tilitapahtumat.tapahtuma, tilitapahtumat.summa, tilitapahtumat.tilinumero, id],
      callback
    );
  }
};
module.exports = tilitapahtumat;