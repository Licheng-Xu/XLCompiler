all: bin/parser

clean:
	rm -f obj/* bin/*

test: bin/parser
	bin/parser < test.c

out: bin/parser
	bin/parser < test.c > test.asm


obj/parser.cpp: src/parser.y
	bison -d -o $@ $^

obj/parser.hpp: obj/parser.cpp

obj/lex.cpp: src/lex.l obj/parser.hpp
	lex -o $@ $^

bin/parser: obj/parser.cpp obj/lex.cpp src/genAsm.cpp src/typeCheck.cpp
	g++ -o $@ $^ -Iinclude -Iobj
	