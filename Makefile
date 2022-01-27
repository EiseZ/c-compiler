all:
	tcc -o compiler src/main.c src/scan.c src/tree.c src/expr.c src/interp.c src/gen.c src/cg.c src/stmt.c src/misc.c src/sym.c src/decl.c

test:
	./compiler input/input
	cc -o out out.s
	./out

clean:
	rm -f compiler *.o out.s out
