ZThreadPool:ZDependence.o ZRunnable.o ZSynchronization.o ZThread.o ZThreadPool.o
	g++ -shared -o lib$@.so ../obj/* -lpthread
	mv lib$@.so ../lib/
%.o:%.cpp
	g++ -fpic -c $< -I../head -std=c++11 
	mv *.o ../obj/
