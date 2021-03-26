const nodeGLFW = require('bindings')('node-glfw');;

const config = {
	name: "my app",
	onMousePressed(event) {
		console.dir(event);
	},
	onMouseMoved(event) {
		console.dir(event);
	},
	onKeyPressed(event) {
		console.dir(event);
	},
	onWindowResized(event) {
		console.dir(event);
	},
	onWindowClosed(event) {
		console.dir(event);
	}
}

nodeGLFW.run(config);
