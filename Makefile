main:
	gcc main.c main_loop.c init.c place_ships.c generate_bot_field.c user_shoot.c bot_shoot.c -o out -lncursesw -lpanelw -Werror -Wall -Wextra