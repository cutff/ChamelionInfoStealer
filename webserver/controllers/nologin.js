exports.pgpController = (req, res, next) => {
    res.render('pgp', {'title': '0x60d5 - PGP Key'});
};

exports.buildingController = (req, res, next) => {
    res.render('build', {'title': '0x60d5 - Building the website'});
};