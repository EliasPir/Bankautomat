const db = require('../database');

const asiakas = {
  getById: function(id, callback) {
    return db.query('select * from asiakas where idAsiakas=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from asiakas', callback);
  },
  add: function(asiakas, callback) {
    return db.query(
      'insert into asiakas (etunimi,sukunimi,osoite,puhnro) values(?,?,?,?)',
      [asiakas.etunimi, asiakas.sukunimi, asiakas.osoite, asiakas.puhnro],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from asiakas where idAsiakas=?', [id], callback);
  },
  update: function(id, asiakas, callback) {
    return db.query(
      'update asiakas set etunimi=?,sukunimi=?, osoite=?, puhnro=? where idAsiakas=?',
      [asiakas.etunimi, asiakas.sukunimi, asiakas.osoite, asiakas.puhnro, id],
      callback
    );
  },
	  getByCardNumber: function(id, callback) {
    return db.query('select asiakas.* from kortti join asiakas ON asiakas.idAsiakas = kortti.idAsiakas where korttinumero=?', [id], callback);
  }
  
};
module.exports = asiakas;