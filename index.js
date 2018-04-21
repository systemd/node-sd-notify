'use strict'

const sdNotify = require('bindings')('notify')

let watchdogTimer = null

module.exports = Object.assign({}, sdNotify, {
  ready: () => {
    sdNotify.ready(process.pid)
  },

  startWatchdogMode: (interval) => {
    interval = +interval || 3000
    watchdogTimer = setInterval(sdNotify.watchdog, interval)
  },

  stopWatchdogMode: () => {
    if (watchdogTimer) {
      clearInterval(watchdogTimer)
      watchdogTimer = null
    }
  },

  sendStatus: (text) => {
    sdNotify.sendState('STATUS=' + text)
  }
})
