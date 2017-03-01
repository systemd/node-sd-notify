# sd-notify

> Extremely minimal wrapper around [`sd_notify`](https://www.freedesktop.org/software/systemd/man/sd_notify.html)

### Usage

__Example:__

```javascript
const notify = require('sd-notify')

// call notify after some async start up process
// such as in the `http` or `express` listen callback

app.listen(PORT, () => {
  console.log('listening on port ' + PORT)
  notify()
})
```

Calling `notify()` will inform [__systemd__](https://www.freedesktop.org/software/systemd/man/systemd.service.html) that the process has started, when using `notify` type in a service definition file, eg:

```
[Unit]
Description=Simple notifying service

[Service]
Type=notify
ExecStart=/usr/sbin/simple-notifying-service

[Install]
WantedBy=multi-user.target
```
