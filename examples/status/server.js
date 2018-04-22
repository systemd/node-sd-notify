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

  setTimeout(() => {
    sdNotify.sendState('test 1 after 1000 ms')
  }, 1000)

  setTimeout(() => {
    sdNotify.sendState('test 2 after 2000 ms')
  }, 2000)
})
