al = require("../allegro")

al.run_main(function() {
	al.init();
	display = al.create_display(640, 480);
	al.set_window_title(display, "Hello, Allegro!")
	blue = al.map_rgb(0, 0, 255)
	while (true) {
		al.clear_to_color(blue)
		al.flip_display()
	}
});
