all: ps-logger
ps-logger: logger.c
	@gcc logger.c -o ps-logger
clean:
	@rm *.o ps.log ps-logger
