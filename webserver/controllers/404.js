exports.status404 = (req, res, next) => {
    res.status(404).render('404', {'title': '0x60d5 - 404 Page not found'});
    //res.status(404).sendFile(path.join(__dirname, 'views', '404.pug'));
    //Make a function to log 404 requests.
    log404(req);
}