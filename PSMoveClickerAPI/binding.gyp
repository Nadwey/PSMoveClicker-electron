{
    "targets": [
        {
            "include_dirs": [
                "<!(node -p \"require('node-addon-api').include_dir\")"
            ],
            "target_name": "PSMoveClickerAPI",
            "sources": [
                "api.cc"
            ],
            "defines": [
                "NAPI_CPP_EXCEPTIONS"
            ],
            "libraries": [
                "../PSMoveClient_CAPI.lib",
            ],
            "copies": [
                {
                    "destination": "<(module_root_dir)/build/Release/",
                    "files": [
                        "<(module_root_dir)/PSMoveClient_CAPI.dll",
                    ]
                }
            ]
        }
    ]
}
