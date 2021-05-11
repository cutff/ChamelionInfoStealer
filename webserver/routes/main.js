const express = require('express');
const Router = express.Router();
const path = require('path');
const nologinController = require('../controllers/nologin');
const loginPageController = require('../controllers/loginPage');
//const RootDirectory = require('../utils/path'); not using this anymore, we're getting files using template engine

Router.get('/pgp', nologinController.pgpController);

Router.post('/building', nologinController.buildingController);

Router.get('/building', nologinController.buildingController);

Router.get('/', loginPageController.loginPageController);

module.exports = Router;

