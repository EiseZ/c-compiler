all:
	tcc -o compiler src/main.c src/scan.c src/tree.c src/expr.c src/interp.c

test:
	./compiler input/input01
	./compiler input/input02
	-./compiler input/input03
	-./compiler input/input04
	-./compiler input/input05

clean:
	rm -f compiler *.o
