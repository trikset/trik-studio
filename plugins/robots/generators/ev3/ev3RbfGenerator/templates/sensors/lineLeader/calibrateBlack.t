ARRAY8 a1@@RANDOM_ID_1@@ 4
ARRAY(CREATE8, 4, a1@@RANDOM_ID_1@@)
ARRAY_WRITE(a1@@RANDOM_ID_1@@, 0, 1)
ARRAY_WRITE(a1@@RANDOM_ID_1@@, 1, 65)
ARRAY_WRITE(a1@@RANDOM_ID_1@@, 2, 66)
ARRAY8 a2@@RANDOM_ID_2@@ 4
ARRAY(CREATE8, 4, a2@@RANDOM_ID_2@@)

INPUT_DEVICE(SETUP, 0, @@PORT@@, 1, 50, 3, @a1@@RANDOM_ID_1@@, 0, @a2@@RANDOM_ID_2@@)

ARRAY(DELETE, a1@@RANDOM_ID_1@@)
ARRAY(DELETE, a2@@RANDOM_ID_2@@)