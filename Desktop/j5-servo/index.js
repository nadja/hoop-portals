var five = require("johnny-five");
var board = new five.Board();
var osc = require('node-osc');
var oscServer = new osc.Server(8338, '127.0.0.1');
var eyebrowleft,mouthwid, mouthop = 0; // init our face tracking vars

var minmouthop = 2; // minimum height (openig) of mouth
var minsmilewid = 15; // min wid of mouth to trigger smile

board.on("ready", function() {

// done initializing board
  var servobig =   new five.Servo({ // big one
  pin: 8, // on the arduino board
  startAt: 120 // defaults to 120 deg
});


var servo =   new five.Servo({ // little one!
  pin: 3, // on the arduino board
  startAt: 120
});
  


  oscServer.on("message", function(msg, rinfo) { // when we receive an osc msg
  
  //console.log("TUIO message:");
  //console.log(msg);

  // assign the rows to the face tracking vars
  eyebrowleft = msg[8];
  mouthwid = msg[6];
  mouthop = msg[7];

  // mouth
  if (typeof mouthwid !="undefined") { // if defined, i.e. if there is a face recognized in win

  	console.log(mouthwid[1] + ", " + mouthop[1]+"\n"); // write the numbers to console
  	// if mouthwid > 15 (this is often a smile)
  	if (mouthwid[1]>minsmilewid) {
  	  servo.to(90, 500); // move to 90 deg
  	}
  	else { // nosmile
  		servo.to(180, 500); // move to 180 deg

  	}

	// going to assume that if we have wid we have mouthop too, so not going to validate there
  
	// mouth height/ opening
  	/*if (mouthop[1]> minmouthop) {
  	  servobig.to(90, 500); // move to 90 deg

  	}
  	else { // small
  		servobig.to(180, 500); // move to 180 deg
  	}*/

  	// alternate/; have it scale continuously so that the servo is representing a more continuous angle based on the input mouth opening
  	angle = (mouthop[1]-2)*18 + 90;
  	servobig.to(angle);
  }
  
});

});