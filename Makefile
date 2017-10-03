test: main.c
	$(CC) -o $@ $< -ldl

.PHONY: clean

clean:
	rm -f test
