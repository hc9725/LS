obj = my.o dbllink.o carg_parser.o
l: $(obj)
	gcc -o l $(obj) 
main.o:dbllink.h carg_parser.h
.PHONY :clean
clean:
	rm l $(obj)
