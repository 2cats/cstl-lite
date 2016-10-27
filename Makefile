run:vector_test
	
vector_test:test/src/vector_test.c src/*.c
	@gcc -g test/src/vector_test.c src/*.c -Iinc -o test/bin/$@
	@./test/bin/$@
clean:
	rm test/bin/*
    	
