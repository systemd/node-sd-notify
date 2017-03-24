'use strict'

/* global describe, it */

const assert = require('assert')

const sdNotify = require('../')

describe('method calling test (not interacting with systemd)', function () {
  it('should call methods and not block for any significant period', function () {
    assert(sdNotify.ready() === undefined)
  })
})
