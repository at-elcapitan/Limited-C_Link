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

C_COM = gcc
CCOMFLAGS = -pthread -ldiscord -lcurl

FILES = $(wildcard $(SOURCE_PATH)*.c)
OBJECTS = $(patsubst $(SOURCE_PATH)%.c, $(BUILD_PATH)%.o, $(FILES))

all : dirs executable
	@echo "Done!"

dirs :
	@if not [ -d "$(BUILD_PATH)" ]; then mkdir $(BUILD_PATH); fi

executable : $(OBJECTS)
	$(C_COM) $(OBJECTS) -o $(OUTPUT_PAH)bot $(CCOMFLAGS)

$(BUILD_PATH)%.o : $(SOURCE_PATH)%.c
	$(C_COM) $(CCOMFLAGS) -c $< -o $@

clean :
	rm -rf ./**/*.o
