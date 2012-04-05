module.exports = require("./build/Release/allegro.node");

function map_rgba(r, g, b, a) {
	return {r: r, g: g, b: b, a: a};
}

function map_rgb(r, g, b) {
	return map_rgba(r, g, b, 255);
}

module.exports.map_rgba = map_rgba;
module.exports.map_rgb = map_rgb;
