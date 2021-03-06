const express = require('express');
const router = express.Router();
const withdraw = require('../models/withdraw_model');

router.post('/',
	function (request, response)
	{
		if(request.body.tilinumero && request.body.amount)
		{
			const tilinumero = request.body.tilinumero;
			const amount = request.body.amount;
			withdraw.checkAccount(tilinumero, function(dbError1, dbResult1)
			{
				if(dbResult1.length > 0)
				{
				if(dbResult1[0].saldo-amount > 0)
				{
					withdraw.nosto(tilinumero, amount, function(dbError, dbResult) 
					{
							if(dbError){
								response.json(false);
								console.log(dbError);
							}
									else {
									console.log("Nosto tehty");
									response.json(true);
									}
					}
					);
				}
				else
				{
				response.json({result:false,message:"Saldo ei riitä"});	
				console.log("Saldo ei riitä");
				}
				}
				else
				{
					response.json({result:false,message:"Tilinumeroa ei ole olemassa"});
					console.log("Tilinumeroa ei ole olemassa");
				}
			}
			);
		}
		else {
			response.json({result:false,message:"Määrä puuttuu"});
			console.log("Tilinumero tai määrä puuttuu");
		}
	}
);  
	
module.exports = router;