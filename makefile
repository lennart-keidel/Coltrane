coltrane: lex.yy.c y.tab.c
	gcc -g lex.yy.c y.tab.c -o coltrane

lex.yy.c: y.tab.c coltrane.l
	flex -l coltrane.l

y.tab.c: coltrane.y
	bison -y -d coltrane.y

clean:
	rm -rf lex.yy.c y.tab.c y.tab.h coltrane.tab.h coltrane.tab.c

