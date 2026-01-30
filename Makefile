build_HW1: HW1.cpp 
	g++ -o run_HW1 HW1.cpp

HW1: build_HW1 #info after : declares dependancies
	./run_HW1 16
	./run_HW1 32
	./run_HW1 64
	./run_HW1 128
	./run_HW1 256	

clean: 
	rm -f run_HW1 
