all: test libfoo1.so libfoo2.so

test: main.c
	$(CC) $(CFLAGS) -o $@ $< -ldl

libfoo1.so: foo1.c
	$(CC) $(CFLAGS) -shared -o $@ -fpic $<

libfoo2.so: foo2.c
	$(CC) $(CFLAGS) -shared -o $@ -fpic $<

.PHONY: clean

clean:
	rm -f test
	rm -f libfoo*.so
