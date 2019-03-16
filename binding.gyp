{
  "targets": [
    {
      "target_name": "notify",
      "sources": [
        "notify.cc",
        "noop.cc"
      ],
      "libraries": [
        "-lsystemd"
      ],
      'conditions': [
        ['OS!="linux"',
          {
            'sources/': [['exclude', 'notify.cc$']],
            'libraries/': [['exclude', '-lsystemd$']],
          }
        ],
        ['OS=="linux"',
          {
            'sources/': [['exclude', 'noop.cc$']]
          }
        ]
      ]
    }
  ]
}
