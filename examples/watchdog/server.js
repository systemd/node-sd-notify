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
  sdNotify.ready()
  sdNotify.startWatchdogMode(2800)
})
