*** Usage ***

Prepare the Singly session:

```javascript
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
```

handle the outcome...

```javascript
singly.addEventListener('singlyServiceDidFail', function(e){
    alert('singlyServiceDidFail');
    Ti.API.info(e);
});

singly.addEventListener('singlyServiceDidAuthorize', function(e){
    Ti.API.info('singlyServiceDidAuthorize');
    connected();
});
```

Now, connect to a service or two (or 20)

```javascript
singly.requestAuthorization({
    serviceName:'twitter'
});    
```

And make some requests:

```javascript
singly.makeRequest({
    
    endPoint: 'types/statuses',
     
    postParams: {
        to: 'twitter',
        body: 'test '+d.getTime(),
    },
    success: function(resp) {
        alert('Your tweet has been sent.');
    },
    failure: function(resp) {
        alert('There was a problem sending your tweet.');
    }
     
});

```