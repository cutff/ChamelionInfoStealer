const http = require('http');
const express = require('express');
const bodyParser = require('body-parser');
const path = require('path');
const log404 = require('./utils/logs');
const app = express();

app.disable('x-powered-by'); //Make fingerprinting the website a little bit harder.
app.set('view engine', 'ejs');
app.set('views', 'views');

const mainRoute = require('./routes/main');

app.unsubscribe(bodyParser.urlencoded({extended: false}));
app.use(express.static(path.join(__dirname, 'public'))); //serve css files statically
app.use(mainRoute); //Main route

//If requests have not found any middleware return 404
const status = require('./controllers/404');
app.use(status.status404);
const server = http.createServer(app);
server.listen(25464, '127.0.0.1');
