# 1. Gerar parser e header
bison -d lights.y

# 2. Gerar scanner
flex -o lights.lex.c lights.l

# 3. Compilar tudo em um executável
gcc -o lights_parser lights.tab.c lights.lex.c -lfl

# 4. Testar com um arquivo válido
./lights_parser exemplo_bom.lights

# 5. Testar com um arquivo inválido
./lights_parser exemplo_ruim.lights
