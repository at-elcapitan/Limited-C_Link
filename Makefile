# AT_C/LINK (c) by Vladislav 'ElCapitan' Nazarov
# 
# AT_C/LINK is licensed under a
# Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
# 
# You should have received a copy of the license along with this
# work. If not, see <http://creativecommons.org/licenses/by-nc-nd/4.0/>.

SOURCE_PATH = ./src/
BUILD_PATH = ./build/
OUTPUT_PAH = ./out/

C_COM = cc
CCOMFLAGS = -pthread -ldiscord -lcurl -ljansson -I/usr/include/glib-2.0 -lglib-2.0

FILES = $(wildcard $(SOURCE_PATH)*.c)
CMD_FILES = $(wildcard $(SOURCE_PATH)commands/*.c)
OBJECTS = $(patsubst $(SOURCE_PATH)%.c, $(BUILD_PATH)%.o, $(FILES))
OBJECTS_CMD = $(patsubst $(SOURCE_PATH)%.c, $(BUILD_PATH)%.o, $(CMD_FILES))

all : dirs executable
	@echo "Done!"

dirs :
	@if not [ -d "$(BUILD_PATH)" ]; then mkdir $(BUILD_PATH); fi
	@if not [ -d "$(BUILD_PATH)/commands" ]; then mkdir $(BUILD_PATH)/commands; fi

executable : $(OBJECTS) $(OBJECTS_CMD)
	$(C_COM) $(OBJECTS) $(OBJECTS_CMD) -o $(OUTPUT_PAH)bot $(CCOMFLAGS)

$(BUILD_PATH)%.o : $(SOURCE_PATH)%.c
	$(C_COM) -c $< -o $@ $(CCOMFLAGS)

clean :
	rm -rf ./**/*.o
	rm -rf ./**/**/*.o
