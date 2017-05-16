while (!(brick.read_analog_sensor("@@PORT@@") @@SIGN@@ @@PERCENTS@@)) {
	brick.wait(10);
}