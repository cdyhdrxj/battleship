main:
	gcc main.c init.c place_ships.c generate_bot_field.c shoot.c -o out -lncursesw -lpanelw -Werror -Wall -Wextra