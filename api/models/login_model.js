const db = require('../database');

const login={
  checkPin: function(korttinumero, callback) {
      return db.query('SELECT pin FROM kortti WHERE korttinumero = ?',[korttinumero], callback); 
    }
};
          
module.exports = login;