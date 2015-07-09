libhttp.a: http_request.o
	ar rcs libhttp.a http_request.o

.PHONY: clean
clean:
	rm *.o
	rm libhttp.a

http_request.o: http_request.cpp
	g++ http_request.cpp -c -o http_request.o -std=c++1y -Wall -Werror
