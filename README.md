Passo 1: Entrar na pasta do projeto
No terminal do PowerShell, navegue até a pasta correta:

PowerShell:

cd C:\Users\aluno\Downloads\CRUD-Lista-de-Anime-main\CRUD-Lista-de-Anime-main\Arquivos-CRU

Passo 2: Executar no PowerShell:

Para compilar e rodar em uma única linha no PowerShell, use ; if ($?) e coloque .\ antes do executável:

PowerShell:

g++ -std=c++17 main.cpp GenrenciadorAnime.cpp -o programa_animes.exe; if ($?) { .\programa_animes.exe }

ou

PowerShell:

g++ -std=c++17 main.cpp GenrenciadorAnime.cpp -o programa_animes.exe
E em seguida:

PowerShell:

.\programa_animes.exe

Opção Codeblocks: Apontando diretamente para o Code::Blocks

1. Compilar:

PowerShell

& "C:\Program Files\CodeBlocks\MinGW\bin\g++.exe" -std=c++17 main.cpp GenrenciadorAnime.cpp -o programa_animes.exe

2. Executar:

PowerShell

.\programa_animes.exe

Opção G++: Ativar o g++ para a sessão inteira do terminal

Se preferir ativar o comando g++ para que funcione diretamente sem precisar digitar todo o caminho:

PowerShell

$env:Path += ";C:\Program Files\CodeBlocks\MinGW\bin"

g++ -std=c++17 main.cpp GenrenciadorAnime.cpp -o programa_animes.exe

.\programa_animes.exe
