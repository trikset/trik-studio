while (brick.read_analog_sensor("F1") == 0) {
	brick.wait(10);
}
