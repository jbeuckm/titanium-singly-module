// This is a test harness for your module
// You should do something interesting in this harness 
// to test out the module and to provide instructions 
// to users on how to use it by example.


// open a single window
var win = Ti.UI.createWindow({
	backgroundColor:'white'
});
var label = Ti.UI.createLabel();
win.add(label);
win.open();

//Prepare the Singly session:

var singly  = require('singly');
singly.startSession({

	clientID: "YOUR_SINGLY_ID",
	    clientSecret: "YOUR_SINGLY_SECRET",
	    success: function() {
	    Ti.API.debug('singly session ready');
	},
	    error: function(e) {
	    Ti.API.info('singly session error '+JSON.stringify(e));
	}
    });


//handle the outcome...

    singly.addEventListener('singlyServiceDidFail', function(e){
	    alert('singlyServiceDidFail');
	    Ti.API.info(e);
	});

singly.addEventListener('singlyServiceDidAuthorize', function(e){
	Ti.API.info('singlyServiceDidAuthorize');
	connected();
    });


//Now, connect to a service or two (or 20)

    singly.requestAuthorization({
	    serviceName:'twitter'
		});    


//And make some requests:

singly.makeRequest({

	endPoint: "types/statuses",

	    postParams: {
	    to: "twitter",
		body: "test posted at "+d.getTime(),
		},
	    success: function(resp) {
	    alert('Your tweet has been sent.');
	},
	    failure: function(resp) {
	    alert('There was a problem sending your tweet.');
	}

    });

//Post a photo to Twitter:

var image = $.view.toImage();

Alloy.Globals.singly.makeRequest({

        endPoint: "types/photos",

	    postParams: {
            to: "twitter",
		body: "Check out my photo!"
		},

	    photo: image,

	    success: function(resp) {
            alert('Your tweet has been sent.');
        },
	    failure: function(resp) {
            alert('There was a problem sending your tweet.');
        }

    });


