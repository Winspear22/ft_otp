# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/15 19:34:25 by adaloui           #+#    #+#              #
#    Updated: 2026/07/18 20:03:24 by adaloui          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ft_otp

SRCS		= main.cpp ArgsParser.cpp OtpGClass.cpp

OBJDIR		= obj
OBJS		= $(SRCS:%.cpp=$(OBJDIR)/%.o)

CC			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++23 -I.
LIBS		= -lcrypto

GREEN		= \033[1;32m
YELLOW		= \033[1;33m
RED		= \033[1;31m
RESET		= \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	@$(CC) $(CXXFLAGS) $(OBJS) -o $(NAME) $(LIBS)
	@echo "$(GREEN)$(NAME) ready.$(RESET)"

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<$(RESET)"
	@$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)
	@echo "$(RED)Objects cleaned.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) removed.$(RESET)"

re: fclean all

.PHONY: all clean fclean re