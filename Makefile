# --- VARIABLES ---
NAME          = ft_otp

# Sources
SRCS          = main.cpp ErrorManager.cpp OtpClass.cpp

# Fichiers Headers
INCLUDES      = includes.hpp

OBJS          = $(SRCS:.cpp=.o)

CC            = g++
FLAGS         = -Wall -Wextra -Werror -std=c++17

# Librairies (OpenSSL est nécessaire pour l'HMAC-SHA1)
LIBS          = -lcrypto

# --- COULEURS ---
GREEN         = \033[1;32m
YELLOW        = \033[1;33m
RESET         = \033[0m

# --- RÈGLES ---

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)Création de l'exécutable $(NAME)...$(RESET)"
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(LIBS)
	@rm -f $(OBJS)
	@echo "$(GREEN)✅ $(NAME) Terminé ! (Objets nettoyés)$(RESET)"

#Compilation des .cpp en .o
%.o: %.cpp $(INCLUDES)
	@echo "$(YELLOW)Compilation de $<...$(RESET)"
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@echo "Objets supprimés."

fclean: clean
	@rm -f $(NAME)
	@echo "Exécutable supprimé."

re: fclean all

.PHONY: all clean fclean re
