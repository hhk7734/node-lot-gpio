{
    "targets": [
        {
            "target_name": "lot",
            "include_dirs": ["<!@(node -p \"require('node-addon-api').include\")"],
            "dependencies": ["<!(node -p \"require('node-addon-api').gyp\")"],
            "cflags!": ["-fno-exceptions", "-llot"],
            "cflags_cc!": ["-fno-exceptions", "-llot"],
            "defines": ["NAPI_DISABLE_CPP_EXCEPTIONS"],
            "sources": [
                "src/main.cpp",
                "src/gpio.cpp"
            ]
        }
    ]
}