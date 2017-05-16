while (brick.read_analog_sensor("@@PORT@@") <= 0) {
	brick.wait(10);
}