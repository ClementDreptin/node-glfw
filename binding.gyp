{
	"targets": [
		{
			"target_name": "node-glfw",
			"cflags!": [ "-fno-exceptions" ],
			"cflags_cc!": [ "-fno-exceptions" ],
			"include_dirs": ["<!(node -p \"require('node-addon-api').include_dir\")"],
			"sources": [ "<!@(find . -name \*.cpp)" ],
			"defines": [ "NAPI_DISABLE_CPP_EXCEPTIONS" ],
		}
	]
}
