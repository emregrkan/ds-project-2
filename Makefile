NAME=main
CXX=g++
CXXFLAGS=-Wall -Weffc++ -Werror -O3 -pedantic -std=c++11
SRC=$(shell find . -maxdepth 1 -name "*.cpp")

$(NAME): format
	@$(CXX) $(CXXFLAGS) $(SRC) -o $(NAME)

format: clean
	@find . -regex '.*\.\(cpp\|hpp\|cu\|c\|h\)' -exec clang-format -style=file -i {} \;

clean:
	@find . -maxdepth 1 -type f -executable -delete
