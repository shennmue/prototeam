# --- Configuration ---
# Nom de ton jeu/menu final
TARGET = mon_menu

# Compilateur (utilise gcc si tu codes en C pur)
CXX = g++

# Options de compilation (-Wall affiche les avertissements, -O2 optimise le code)
CXXFLAGS = -Wall -std=c++17 -O2

# Bibliothèques requises par Raylib (Configuration Linux Desktop)
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Ton (ou tes) fichier(s) source(s)
SRC = main.cpp

# --- Règles ---
# Règle par défaut (lancée avec la commande "make")
all: $(TARGET)

# Compilation de l'exécutable
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

# Nettoyage (lancé avec "make clean")
clean:
	rm -f $(TARGET)