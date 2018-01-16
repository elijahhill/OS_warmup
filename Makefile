all: ps-logger
ps-logger: logger.c
	@gcc -g logger.c -o ps-logger
clean:
	@rm ps.log ps-logger
