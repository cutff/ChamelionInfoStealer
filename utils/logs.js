const fs = require('fs');

function log404(req) {
    //Write to file user informations.
    let date = new Date();
    let stringToWrite = "\n" + date + " | 404 -> \n\t- IP Address : " + req.ip + "\n\t- Tried to access : " + req.url + "\n\t- User Agent : " + req.headers['user-agent'] + "\n--------------------------------------------------";
    fs.appendFile('logs/404_logs.txt', stringToWrite, function(err) {
        if(err) return console.log(err);
    })
}

module.exports = log404;