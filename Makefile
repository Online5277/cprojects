##
# Cprojects
#
# @file
# @version 0.1

main.exe: main.c stateMachine.c fileHelper.c cJSON/cJSON.c
	gcc main.c stateMachine.c fileHelper.c cJSON/cJSON.c \
		-IC:/raylib/raylib/src -LC:/raylib/raylib/src -lraylib -lopengl32 -lgdi32 -lwinmm -o main.exe

run: main.exe
	./main.exe

# end
