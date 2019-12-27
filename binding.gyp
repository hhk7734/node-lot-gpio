{
    "targets": [
        {
            "target_name": "lot",
            "include_dirs": ["<!@(node -p \"require('node-addon-api').include\")"],
            "dependencies": ["<!(node -p \"require('node-addon-api').gyp\")"],
            "cflags!": ["-fno-exceptions"],
            "cflags_cc!": ["-fno-exceptions"],
            "cflags": ["-llot"],
            "cflags_cc": ["-llot"],
            "defines": ["NAPI_DISABLE_CPP_EXCEPTIONS"],
            "sources": [
                "src/main.cpp",
                "src/gpio.cpp"
            ],
            "libraries": [
                "/usr/lib/liblot.so"
            ]
        }
    ]
}
