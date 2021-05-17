INPUT_F=./src/main.c ./src/sha-256.c ./src/header.c ./src/utils.c
COMPILER=gcc
FLAGS=-Wall -Wextra -g -O2
OUTPUT_F=./bin/encrypt
TEST_F=./bin/file

all:
	$(COMPILER) $(INPUT_F) $(FLAGS) -o $(OUTPUT_F)

dirs:
	mkdir ./bin

files:
	touch $(TEST_F)
	echo "wepqowieqwiepqwoeiq239819248pojdpwouepqwopwoeiqwe" > $(TEST_F)

run:
	$(OUTPUT_F) $(TEST_F) m123
	$(OUTPUT_F) $(TEST_F).cyp m12123
	$(OUTPUT_F) $(TEST_F).cyp.cyp m12521613
	hexdump $(TEST_F)
	hexdump $(TEST_F).cyp
	hexdump $(TEST_F).cyp.cyp
	hexdump $(TEST_F).cyp.cyp.cyp