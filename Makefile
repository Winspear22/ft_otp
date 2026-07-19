# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/15 19:34:25 by adaloui           #+#    #+#              #
#    Updated: 2026/07/19 19:43:52 by adaloui          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ft_otp

SRCS		= main.cpp ArgsParser.cpp OtpGClass.cpp OtpKClass.cpp

OBJDIR		= obj
OBJS		= $(SRCS:%.cpp=$(OBJDIR)/%.o)

CC			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++23 -I.
LIBS		= -lcrypto

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Linking $(NAME)..."
	@$(CC) $(CXXFLAGS) $(OBJS) -o $(NAME) $(LIBS)
	@echo "$(NAME) ready."

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling $<"
	@$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)
	@echo "Objects cleaned."

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME) removed."

re: fclean all

.PHONY: all clean fclean re