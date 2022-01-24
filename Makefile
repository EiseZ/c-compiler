all:
	cc -o compiler main.c scan.c tree.c expr.c interp.c

clean:
	rm -f compiler *.o
