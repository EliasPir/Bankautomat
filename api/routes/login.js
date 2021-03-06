const express = require('express');
const router = express.Router();
const login = require('../models/login_model');

router.post('/', 
  function(request, response) {
    if(request.body.korttinumero && request.body.pin){
      const korttinumero = request.body.korttinumero;
      const pin = request.body.pin;
        login.checkPin(korttinumero, function(dbError, dbResult) {
          if(dbError){
            response.json(dbError);
          }
          else{
				if (dbResult.length > 0) {
				
				
					if(pin == dbResult[0].pin) {
					console.log("Oikein");
					response.send(true);
					}
				
					else {
					console.log("Pin väärin");
					response.json({result:false,message:"Väärä PIN!"});	
					//response.send(false);
					}
				
            }
            else{
              console.log("Korttia ei ole olemassa");
			  response.json({result:false,message:"Korttinumeroa ei ole olemassa!"});
              //response.send(false);
            }
          }
          }
        );
      }
    else{
      console.log("Korttinumero tai pin puuttuu");
	  response.json({result:false,message:"Korttinumero tai pin puuttuu!"});
      //response.send(false);
    }
  }
);

module.exports=router;