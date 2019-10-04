compile:
	rm -rf build || true
	mkdir build
	gcc -Wall -g src/*.c -o build/reverse
