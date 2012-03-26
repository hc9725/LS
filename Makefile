obj = my.o dbllink.o
l: $(obj)
	gcc -o l $(obj) -lpopt
main.o:dbllink.h
.PHONY :clean
clean:
	rm l $(obj)
