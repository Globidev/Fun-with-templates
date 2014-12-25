NAME            =   fun_with_templates

COMPILER        =   $(CXX)
CFLAGS          =   -Wall -Wextra -Werror -std=c++1y -O3 -I. -c
LFLAGS          =   -o

rwildcard       =   $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2)\
                    $(filter $(subst *,%,$2),$d))

TEST_DIR        =   tests
TEST_SRC        =   $(call rwildcard,tests,*.cpp)

SRC             =   main.cpp
SRC             +=  $(TEST_SRC)

OBJ_DIR         =   objs
OBJ             =   $(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))
OBJ_SUB_DIRS    =   $(dir $(OBJ))

all: $(NAME)

$(NAME): $(OBJ)
	@echo "linking"
	@$(COMPILER) $^ $(LFLAGS) $@

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	@$(foreach dir, $(OBJ_SUB_DIRS), mkdir -p $(dir))

$(OBJ_DIR)/%.o: %.cpp
	@echo "compiling $(notdir $^)"
	@$(COMPILER) $(CFLAGS) $^ -o $@

clean:
	@echo "cleaning object files"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "cleaning executable"
	@rm -f $(NAME)

re: fclean all
