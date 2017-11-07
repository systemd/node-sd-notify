# sd-notify

[![NPM version][npm-image]][npm-url]
[![License][license-image]][license-url]
[![Code style][standard-image]][standard-url]

> Extremely minimal wrapper around [`sd_notify`](https://www.freedesktop.org/software/systemd/man/sd_notify.html)

### Requirements

Any Linux distribution that supports [__systemd__](https://en.wikipedia.org/wiki/Systemd).

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
Environment="NODE_ENV=production"
Type=notify
ExecStart=/usr/sbin/simple-notifying-service
TimeoutStartSec=30
Restart=always

[Install]
WantedBy=multi-user.target
```

__"Watchdog" mode:__

In the service file add `WatchdogSec=n` where `n` is the amount of seconds __`systemd`__ should
stop (or restart) the service if there is no contact.

```ini
[Service]
Environment="NODE_ENV=production"
Type=notify
ExecStart=/usr/sbin/simple-notifying-service
TimeoutStartSec=30
Restart=always
WatchdogSec=3
```

...and in Node, you can call the native method `.watchdog()` directly in a `setInterval` or any other mechanism
depending on what kind of application you are developing, or you can use the helper function
`startWatchdogMode([milliseconds])`:

```javascript
const notify = require('sd-notify')

app.listen(PORT, () => {
  console.log('listening on port ' + PORT)
  notify.ready()
  notify.startWatchdogMode(2800)
})
```

...above the number supplied to the `startWatchdogMode` method is the amount of milliseconds
we want to _ping_ `systemd`, in the example this is 200ms less than the 3 seconds set in the
service file. Due to the event loop there is no quarantee the `setInterval` underneath will
fire exactly 2800ms, this will change depending on how many functions are being called in the process,
though this has a nice side effect, as if the process gets that busy, that blocked, `systemd` will kill it
(and restart it with the `Restart=` config set); and in the context of having multiple processes being load
balanced with Nginx (as an example) and across multiple machines, ensures that no one process is blocking
for any significant amount of time.

[npm-image]: https://img.shields.io/npm/v/sd-notify.svg
[npm-url]: https://npmjs.org/package/sd-notify
[license-image]: http://img.shields.io/npm/l/sd-notify.svg
[license-url]: LICENSE
[standard-image]: https://img.shields.io/badge/code%20style-standard-brightgreen.svg
[standard-url]: https://github.com/feross/standard
