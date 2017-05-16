while (!(brick.read_analog_sensor("@@PORT@@") @@SIGN@@ @@DISTANCE@@)) {
	brick.wait(10);
}
