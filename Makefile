TARGET:=vector_test
run:${TARGET}
	
${TARGET}:test/src/${TARGET}.c src/*.c
	@gcc -g test/src/${TARGET}.c src/*.c -Iinc -o test/bin/$@
	@./test/bin/$@
# list_test:test/src/list_test.c src/*.c
# 	@gcc -g test/src/list_test.c src/*.c -Iinc -o test/bin/$@
# 	@./test/bin/$@
clean:
	rm test/bin/*
    	
