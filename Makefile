END   = \033[0m
RED     = \033[31m
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m

NAME = webserv

SRC = 	sources/main.cpp \
		sources/Config_parser.cpp \
		sources/Server.cpp \
		sources/Location.cpp \
		sources/Sockets.cpp \
		sources/webserver.cpp \
		sources/MIMEtypes.cpp \
		sources/cgi.cpp \

CPP = c++

CPPFLAGS = -Wall -Wextra -Werror -std=c++98 -fsanitize=address -g3

RM = rm -f

OBJ = $(SRC:.cpp=.o)

.cpp.o:
	@printf "\033[2K"                        # Clear the line
	@echo "${BLUE}> Compiling $< ${END}\c"
	@$(CPP) $(CPPFLAGS) -c $< -o $@
	@printf "\r"                             # Move the cursor back to the beginning of the line

all: $(NAME)

$(NAME) : $(OBJ)
	@$(CPP) $(CPPFLAGS) $(OBJ) -o $(NAME)
	@printf "\033[2K"
	@echo "${GREEN}> Compiled successfully 🎉${END}"

clean:
	@$(RM) $(OBJ)
	@echo "${YELLOW}> All objects files have been deleted ❌${END}"

fclean: clean
	@$(RM) $(NAME)
	@echo "${YELLOW}> Cleaning has been done ❌${END}"

re: fclean all