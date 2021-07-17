# sudo apt install -y make gcc nasm qemu-system

# $@ = target(s), $< = sources
# Shell commands in makefile have to be on one line or have \ at end of lines

gccParams = -lm

#Compile c code
bin/tcalc: src/main.c
	if [ ! -d "bin" ]; then mkdir bin; fi

	gcc src/main.c -o bin/tcalc $(gccParams)

run:
	./bin/tcalc

clean:
	rm -rf bin