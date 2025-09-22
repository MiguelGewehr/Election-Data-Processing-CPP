# Configurações
CXX      := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -O2 -g
TARGET   := deputados

# Busca Automática de Arquivos
SRCDIR  := src
OBJDIR  := obj
SOURCES := $(shell find $(SRCDIR) -name '*.cpp')
OBJECTS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))
DEPS    := $(OBJECTS:.o=.d) 

# Regras Principais 

# Regra padrão: compila o alvo principal
all: $(TARGET)

# Regra para linkar o executável final
$(TARGET): $(OBJECTS)
	@echo "Linkando executável..."
	$(CXX) $^ -o $@
	@echo "Executável '$(TARGET)' criado com sucesso!"

# Regra para compilar os arquivos .cpp em arquivos objeto .o
# Também cria os arquivos de dependência .d (-MMD -MP)
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo "Compilando $<..."
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Limpa todos os arquivos gerados
clean:
	@echo "Limpando arquivos compilados..."
	@rm -rf $(OBJDIR) $(TARGET)
	@echo "Limpeza concluída."

# Inclui as dependências geradas. O '-' ignora erros se os arquivos não existirem.
-include $(DEPS)

# Targets Utilitários

# Executa o programa para deputados federais
run-federal: $(TARGET)
	./$(TARGET) --federal input/acre/candidatos.csv input/acre/votacao.csv 02/10/2022

# Executa o programa para deputados estaduais
run-estadual: $(TARGET)
	./$(TARGET) --estadual input/acre/candidatos.csv input/acre/votacao.csv 02/10/2022

# Limpa e recompila o projeto
rebuild: clean all

# Define targets que não representam arquivos
.PHONY: all clean rebuild run-federal run-estadual