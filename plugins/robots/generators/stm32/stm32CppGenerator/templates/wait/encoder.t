while (!(brick.read_analog_sensor("@@PORT@@") @@SIGN@@ @@TACHO_LIMIT@@)) {
	brick.wait(10);
}
