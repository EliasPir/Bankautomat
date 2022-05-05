const db = require('../database');

const withdraw={
	nosto: function(tilinumero, amount, callback) {
      return db.query('call withdraw (?,?)',[tilinumero, amount], callback); 
	  },
	 checkAccount: function(tilinumero, callback) {
		 return db.query('select tilinumero, saldo from tili where tilinumero = ?',[tilinumero], callback);
	 }
};

module.exports = withdraw;