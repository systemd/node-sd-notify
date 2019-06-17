# sd-notify [![Build Status](https://travis-ci.org/systemd/node-sd-notify.svg?branch=master)](https://travis-ci.org/systemd/node-sd-notify) [![js-standard-style](https://img.shields.io/badge/code%20style-standard-brightgreen.svg?style=flat)](https://github.com/feross/standard) [![NPM version](https://img.shields.io/npm/v/sd-notify.svg)](https://npmjs.org/package/sd-notify) [![License](http://img.shields.io/npm/l/sd-notify.svg)](LICENSE)

> Extremely minimal wrapper around [`sd_notify`](https://www.freedesktop.org/software/systemd/man/sd_notify.html)

### Requirements

* any Linux distribution that supports [__systemd__](https://en.wikipedia.org/wiki/Systemd)
* C/C++ tool stack (GCC/Clang, etc...)
* Node.js >= `8.0.0`

### Installation

Firstly you need some __systemd__ development files, on __Ubuntu__ these can be installed via:

```
$ sudo apt install libsystemd-dev
```

...then using `npm`:

```
$ npm install --save sd-notify
```

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
`startWatchdogMode(milliseconds)`:

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
service file. Due to the event loop there is no guarantee the `setInterval` underneath will
fire exactly 2800ms, this will change depending on how many functions are being called in the process,
though this has a nice side effect, as if the process gets that busy, that blocked, `systemd` will kill it
(and restart it with the `Restart=` config set); and in the context of having multiple processes being load
balanced with Nginx (as an example) and across multiple machines, ensures that no one process is blocking
for any significant amount of time.

You can also check if the process was called by __systemd__ with Watchdog mode
enabled, using `watchdogInterval()` which returns the amount of milliseconds
watchdog has been set to, or `0` if it has not been set:

```javascript
app.listen(PORT, () => {
  console.log('listening on port ' + PORT)
  notify.ready()

  const watchdogInterval = notify.watchdogInterval()

  if (watchdogInterval > 0) {
    const interval = Math.floor(watchdogInterval / 2)
    notify.startWatchdogMode(interval)
  }
})
```

...this way the Node process will behave in the correct manner in either situation.

__Status:__

You can also send some status string to __systemd__, which will append to the service's log.

```javascript
const notify = require('sd-notify')

// ...

notify.sendStatus('send some status to systemd')

// ...
```

...then, for example:

```
$ journalctl -u node-status

...
Apr 22 17:29:41 lenovo node[8275]: (8275) listening on 8000
Apr 22 17:29:41 lenovo systemd[1]: Started Express Node.js.
Apr 22 17:35:50 lenovo node[8275]: send some status to systemd
...
```
