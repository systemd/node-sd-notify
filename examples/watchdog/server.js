#!/usr/bin/env node

'use strict'

const sdNotify = require('../../')
const express = require('express')

const app = express()

app.get('/', (req, res) => {
  res.end('hello world')
})

app.listen(8000, () => {
  console.log(`(${process.pid}) listening on 8000`)
  const watchdogInterval = sdNotify.watchdogInterval()

  if (watchdogInterval > 0) {
    const interval = Math.floor(watchdogInterval / 2)
    console.log('watchdog enabled, every ' + interval + ' ms')
    sdNotify.startWatchdogMode(interval)
  }

  sdNotify.ready()
})
