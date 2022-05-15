all:
	g++ bellman_dijkstra.cpp -std=c++11 -o exe

clean:
	/bin/rm -rf exe
