NAME=150121823
CXX=g++
CXXFLAGS=-Wall -Weffc++ -Werror -O3 -pedantic -std=c++11
SRC=$(shell find . -maxdepth 1 -name "*.cpp")

$(NAME): clean
	@$(CXX) $(CXXFLAGS) $(SRC) -o $(NAME)

clean:
	@find . -maxdepth 1 -type f -executable -delete
