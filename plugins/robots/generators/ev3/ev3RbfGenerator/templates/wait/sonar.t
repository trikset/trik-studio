@@RANDOM_ID@@:
TIMER_WAIT(50, timer)
TIMER_READY(timer)
INPUT_READSI(0, @@PORT@@, 0, 0, _temp_sensor_value_f)
MOVEF_32(_temp_sensor_value_f, timer)
CP_@@SIGN@@32(timer, @@DISTANCE@@, _temp_sensor_value_8)
JR_FALSE(_temp_sensor_value_8, @@RANDOM_ID@@)
