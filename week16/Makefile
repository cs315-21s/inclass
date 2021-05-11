HEX_FILES = fib_rec_s.hex find_max_s.hex mergesort_s.hex quadratic_s.hex sum_array_s.hex

all: $(HEX_FILES)

%.o: %.s
	as -o $(basename $(notdir $@)).o $^

%.hex: %.o
	objdump -d $^ |python3 makerom3.py >$@
