
test1:
	./build/src/proyecto03 -d 100 -h 128 -v 128 -f -g 8 -o
test2:
	./build/src/proyecto03 -l -50 -d 100 -h 256 -v 128 -f -g 8 -o
test3:
	./build/src/proyecto03 -t -50 -d 100 -h 128 -v 128 -f -g 6 -o
test4:
	./build/src/proyecto03 -t 100 -d 100 -h 128 -v 128 -f -g 6 -o
test5:
	./build/src/proyecto03 -b 60 -d 100 -h 64 -v 128 -q -o
test6:
	./build/src/proyecto03 -b 60 -d 100 -h 64 -v 128 -f -g 6 -o

dotest:
	./do_test
clean:
	./order66
compile:
	./compile_all
