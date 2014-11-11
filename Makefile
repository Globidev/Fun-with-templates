NAME            =   fun_with_templates

COMPILER        =   clang++
CFLAGS          =   -Wall -Wextra -Werror -std=c++1y -O3 -I. -c
LFLAGS          =   -o

TEST_DIR        =   tests
TEST_SRC        =   compose.cpp \
                    list.cpp

SRC             =   main.cpp
SRC             +=  $(addprefix $(TEST_DIR)/, $(TEST_SRC))

OBJ_DIR         =   objs
OBJ             =   $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.cpp=.o)))

all: $(NAME)

$(NAME): $(OBJ)
	$(COMPILER) $^ $(LFLAGS) $@

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(COMPILER) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: %.cpp
	$(COMPILER) $(CFLAGS) $^ -o $@

clean:
	rm -f $(OBJ)
	rm -df $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
