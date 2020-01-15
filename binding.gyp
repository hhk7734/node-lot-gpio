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
            "defines": [],
            "sources": [
                "c_src/lot.cpp",
                "c_src/funcs_wrapper.cpp",
                "c_src/GpioWrapper.cpp",
                "c_src/UartWrapper.cpp",
                "c_src/I2cWrapper.cpp"
            ],
            "libraries": [
                "/usr/lib/liblot.so"
            ]
        }
    ]
}
