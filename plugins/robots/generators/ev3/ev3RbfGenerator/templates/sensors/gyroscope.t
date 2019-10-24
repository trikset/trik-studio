INPUT_DEVICE(READY_SI, 0, @@PORT@@, 0, 0, 1, _temp_sensor_value_f)
DATA32 tmp32_@@RANDOM_ID@@
MOVEF_32(_temp_sensor_value_f, tmp32_@@RANDOM_ID@@)
ARRAY_WRITE(@@RESULT@@, 0, tmp32_@@RANDOM_ID@@)
