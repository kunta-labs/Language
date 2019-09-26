{
  "targets": [
    {
      "target_name": "Language",
      "sources": [ 
      			   "lexer/lexer.cpp", 
      			   "lexer/language.cpp", 
               "lexer/ks.cpp",
               "lexer/json.hpp"
      			   ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "lexer/"
      ],
      "cflags!" : [
        "-fno-exceptions"
      ],
      "cflags_cc!": [
        "-fno-rtti",
        "-fno-exceptions"
      ],
      "conditions": [
        [
          "OS==\"mac\"", {
            "xcode_settings": {
              "OTHER_CFLAGS": [
                "-mmacosx-version-min=10.7",
                "-std=c++11",
                "-stdlib=libc++"
              ],
              "GCC_ENABLE_CPP_RTTI": "YES",
              "GCC_ENABLE_CPP_EXCEPTIONS": "YES"
            }
          }
        ]
      ]
    }
  ]
}
