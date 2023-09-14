FILES = Huber_dist.cpp mixtures.cpp selection.cpp utility.cpp
TEST_FLAGS = -lm -lcheck -lsubunit
test: test_1 test_2
	./test1
	./test2

test_1: 
	g++ -g $(FILES) tests/*c $(TEST_FLAGS) -o test1

test_2:
	g++ -g $(FILES) tests/*.cpp $(TEST_FLAGS) -o test2


run: 
	g++ -g $(FILES) test.cpp -lm