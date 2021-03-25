{
	"targets": [
		{
			"target_name": "node-glfw",
			"cflags!": [ "-fno-exceptions" ],
			"cflags_cc!": [ "-fno-exceptions" ],
			"include_dirs": [
				"<!(node -p \"require('node-addon-api').include_dir\")",
				"src/vendor/glad/include"
			],
			"dependencies": [ "glad" ],
			"libraries": [ "-lglfw" ],
			"sources": [ "<!@(find . -name \*.cpp)" ],
			"defines": [ "NAPI_DISABLE_CPP_EXCEPTIONS" ],
		},
		{
			"target_name": "glad",
			"type": "static_library",
			"cflags!": [ "-fno-exceptions" ],
			"cflags_cc!": [ "-fno-exceptions" ],
			"include_dirs": [
				"src/vendor/glad/include"
			],
			"sources": [ "src/vendor/glad/src/glad.c" ]
		}
	]
}
