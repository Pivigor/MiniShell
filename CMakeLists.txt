cmake_minimum_required(VERSION 3.20)
project(JGarlic_and_JComic C)

set(CMAKE_C_STANDARD 99)

include_directories(/Users/jgarlic/.brew/Cellar/readline/8.1.2/include)

add_executable(JGarlic_and_JComic main.c my_minishell.h
        my_executer.c my_executer_helper.c
        my_builtin.c my_builtin2.c
        my_cmd_parser.c my_cmd_parser_parts.c my_cmd_parser_helper.c
        my_status_solver.c my_status_solver_helper.c
        my_split_controlls.c my_split_controlls_helper.c
        get_next_line.c get_next_line.h get_next_line_utils.c
        ft_itoa.c ft_atoi.c ft_split.c
        ft_strncmp.c ft_strdup.c ft_strjoin.c ft_strlen.c ft_strchr.c
        ft_lstadd_back.c ft_lstclear.c ft_lstnew.c ft_lstsize.c ft_lstlast.c)

target_link_libraries(JGarlic_and_JComic "-lreadline")
target_link_libraries(JGarlic_and_JComic "-L/Users/jgarlic/.brew/Cellar/readline/8.1.2/lib")
