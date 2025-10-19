// WARNING: Unreadable code! Close your eyes and run away!

// Don`t tell me I didn`t warn you. Now a little tips to understand this.
// This is an asm-like code to deal with native EV3 software. All your nice TRIK Studio
// mathematical one-line expressions are now big and slow pieces of ... code.
// For example "a = 100 * 200 - 50" will be translated into
//
//    MUL32(100, 100, _int_temp_result_1) /* _temp_result_* is something like asm register here */
//    SUB32(_int_temp_result_1, 50, _int_temp_result_2)
//    MOVE32_32(_temp_result_2, a)
//
// No temporary variables count optimization is performed for now, so suffer.
// Control flow is emulated with goto statements (kill me please).
// Note: 8, 16, 32-bit and float mathematical functions accept arguments only in corresponding bitness,
// so many temporary variables for type casting will be met there.

// Again, reading the code below may harm your mind. If something behaves strangely please contact developers.

@@VARIABLES@@

vmthread MAIN
{
@@CONSTANTS_INITIALIZATION@@
@@ARRAYS_INITIALIZATION@@

	DATA32 timer
	DATA8 _temp_sensor_value_8
	DATAF _temp_sensor_value_f

@@MAILBOXES_OPENING@@
@@MAIN_CODE@@

@@MAILBOXES_CLOSING@@
__programEnd:
}

@@THREADS@@

subcall atan2wrap_EV3_KERNEL_util
{
	IN_F y
	IN_F x
	OUT_F z

	DATAF yDividedByX
	DIVF(y, x, yDividedByX)
	MATH(ATAN, yDividedByX, z)
	DIVF(z, 57.29577951308232F, z)
	JR_GTF(x, 0.0F, endLabel)
	JR_GTEQF(y, 0.0F, yGreatEqualZero)
	SUBF(z, pi, z)
	JR(endLabel)
yGreatEqualZero:
	ADDF(z, pi, z)
endLabel:
}

// utils functions block start
subcall motors_overflow_check_EV3_KERNEL_util
{
	IN_8 src
	OUT_8 dst

	MOVE8_8(src,dst)

	DATA8 lowerBound
	MOVE8_8(-100,lowerBound)
	DATA8 upperBound
	MOVE8_8(100,upperBound)

	JR_LT8(src, 0, lowThenZero)
	JR_LT8(src, upperBound, endLabel)
	MOVE8_8(upperBound,dst)
	JR(endLabel)

lowThenZero:
	JR_GTEQ8(src, lowerBound, endLabel)
	MOVE8_8(lowerBound,dst)

endLabel:
}

subcall clp2_EV3_KERNEL_util
{
	IN_32 src
	OUT_32 dst

	MOVE32_32(1, dst)
	JR_LTEQ32(src, 1, endLabel)

	DATA32 tmp
	DATA32 xRotated
	MOVE32_32(src, tmp)
	SUB32(tmp, 1, tmp)
	MOVE32_32(tmp, xRotated)
	DIV32(xRotated, 2, xRotated)
	OR32(tmp, xRotated, tmp)
	MOVE32_32(tmp, xRotated)
	DIV32(xRotated, 4, xRotated)
	OR32(tmp, xRotated, tmp)
	MOVE32_32(tmp, xRotated)
	DIV32(xRotated, 16, xRotated)
	OR32(tmp, xRotated, tmp)
	MOVE32_32(tmp, xRotated)
	DIV32(xRotated, 256, xRotated)
	OR32(tmp, xRotated, tmp)
	MOVE32_32(tmp, xRotated)
	DIV32(xRotated, 65536, xRotated)
	OR32(tmp, xRotated, tmp)

	ADD32(tmp, 1, dst)
endLabel:
}

subcall write32Array_EV3_KERNEL_util
{
	IN_H array
	IN_32 pos
	IN_32 value

	CALL(writeArray_EV3_KERNEL_util, array, pos)
	ARRAY_WRITE(array, pos, value)
}

subcall writeFArray_EV3_KERNEL_util
{
	IN_H array
	IN_32 pos
	IN_F value

	CALL(writeArray_EV3_KERNEL_util, array, pos)
	ARRAY_WRITE(array, pos, value)
}

subcall writeArray_EV3_KERNEL_util
{
	IN_H  array
	IN_32  pos

	DATA32 size
	ARRAY(SIZE, array, size)
	JR_LT32(pos, size, endLabel)
	DATA32 newSize
	CALL(clp2_EV3_KERNEL_util, size, newSize)
	ARRAY(RESIZE, array, newSize)
endLabel:
}

subcall assign32Array_EV3_KERNEL_util
{
	IN_H srcArray
	IN_H dstArray

	DATA32 sizeSrc
	DATA32 sizeDst
	ARRAY(SIZE, srcArray, sizeSrc)
	ARRAY(SIZE, dstArray, sizeDst)
	JR_LTEQ32(sizeSrc, sizeDst, copy_label)
	ARRAY(RESIZE, dstArray, sizeSrc)

	copy_label:
	ARRAY(COPY, srcArray, dstArray)
}

subcall B2U32_EV3_KERNEL_util
{
	IN_8 src
	OUT_32 dst

	DATA8 tmp8
	MOVE8_8(src, tmp8)
	AND8(tmp8, 127, tmp8)
	MOVE8_32(tmp8, dst)
	JR_GTEQ8(src, 0, end_label)
	OR32(dst, 128, dst)
	end_label:
}

// utils functions block end

@@SUBPROGRAMS@@
