# sd-notify


[![Greenkeeper badge](https://badges.greenkeeper.io/roryrjb/sd-notify.svg)](https://greenkeeper.io/)
[![NPM version][npm-image]][npm-url]
[![Build status][travis-image]][travis-url]
[![License][license-image]][license-url]
[![Code style][standard-image]][standard-url]

> Extremely minimal wrapper around [`sd_notify`](https://www.freedesktop.org/software/systemd/man/sd_notify.html)

### Installation

Firstly you need some __systemd__ development files, on __Ubuntu__ these can be installed via:

```
$ sudo apt install libsystemd-dev
```

...then using `npm` or `yarn`:

```
$ npm install --save sd-notify
```

or:

```
$ yarn add sd-notify
```

_Please note that this has currently only been tested on Ubuntu 16.04._

### Usage

__Example:__

```javascript
const notify = require('sd-notify')

// call notify after some async start up process
// such as in the `http` or `express` listen callback

app.listen(PORT, () => {
  console.log('listening on port ' + PORT)
  notify.ready()
})
```

Calling `.ready()` will inform [__systemd__](https://www.freedesktop.org/software/systemd/man/systemd.service.html) that the process has started, when using `notify` type in a service definition file, eg:

```ini
[Unit]
Description=Simple notifying service

[Service]
Type=notify
ExecStart=/usr/sbin/simple-notifying-service

[Install]
WantedBy=multi-user.target
```

[npm-image]: https://img.shields.io/npm/v/sd-notify.svg
[npm-url]: https://npmjs.org/package/sd-notify
[travis-image]: https://img.shields.io/travis/roryrjb/sd-notify.svg
[travis-url]: https://travis-ci.org/roryrjb/sd-notify
[license-image]: http://img.shields.io/npm/l/sd-notify.svg
[license-url]: LICENSE
[standard-image]: https://img.shields.io/badge/code%20style-standard-brightgreen.svg
[standard-url]: https://github.com/feross/standard
