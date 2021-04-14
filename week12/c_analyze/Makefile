PROG = analyze
OBJS = analyze.o fib_rec_s.o find_max_s.o  max3_s.o quadratic_s.o  

%.o: %.c
	gcc -c -g -o $@ $<

%.o: %.s
	as -g -o $@ $<

$(PROG): $(OBJS)
	gcc -g -o $@ $^
	
clean:
	rm -rf $(PROG) $(OBJS)
