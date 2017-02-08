while (brick.sensor(@@PORT@@).read() <= 0) {
	brick.wait(10);
}
