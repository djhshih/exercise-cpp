CXX=g++

all: numeric pearson
	
numeric:
	$(CXX) -o numeric numeric_test.cpp

pearson:
	$(CXX) -o pearson pearson_problem.cpp

clean:
	rm numeric pearson

