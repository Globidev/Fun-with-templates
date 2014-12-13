NAME            =   fun_with_templates

COMPILER        =   $(CXX)
CFLAGS          =   -Wall -Wextra -Werror -std=c++1y -O3 -I. -c
LFLAGS          =   -o

TEST_DIR        =   tests
TEST_SRC        =   functional/compose.cpp                          \
                    functional/list/list_basic.cpp                  \
                    functional/list/list_transform.cpp              \
                    functional/list/list_fold_reduce.cpp            \
                    functional/list/list_fold_special.cpp           \
                    functional/list/list_sublist_extract.cpp        \
                    functional/list/list_sublist_predicate.cpp      \
                    functional/compile_time/compile_time_list.cpp   \
                    functional/maybe/maybe.cpp                      \
                    functional/variant/variant.cpp                  \

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

$(OBJ_DIR)/%.o: $(TEST_DIR)/functional/%.cpp
	$(COMPILER) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/functional/list/%.cpp
	$(COMPILER) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/functional/compile_time/%.cpp
	$(COMPILER) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/functional/maybe/%.cpp
	$(COMPILER) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/functional/variant/%.cpp
	$(COMPILER) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: %.cpp
	$(COMPILER) $(CFLAGS) $^ -o $@

clean:
	rm -f $(OBJ)
	rm -df $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
