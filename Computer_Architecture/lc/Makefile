FILE = main

all: assemble run

assemble:
	lc3as $(FILE).asm

run:
	lc3sim main.obj

clean:
	rm -f *.obj *.lst *.sym
