all: ps-logger
ps-logger: ps-logger.c
	@gcc -g ps-logger.c -o ps-logger
clean:
	@rm ps.log ps-logger
