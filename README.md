Passo 1: Entrar na pasta do projeto
No terminal do PowerShell, navegue até a pasta correta:

PowerShell:

cd C:\Users\aluno\Downloads\CRUD-Lista-de-Anime-main\CRUD-Lista-de-Anime-main\Arquivos-CRUD

Passo 2: avisar terminal onde está no codeblocks

$env:Path += ";C:\Program Files\CodeBlocks\MinGW\bin"

g++ -std=c++17 main.cpp GenrenciadorAnime.cpp -o programa_animes.exe

.\programa_animes.exe

para rodar tudo direto:

cd C:\Users\aluno\Downloads\CRUD-Lista-de-Anime-main\CRUD-Lista-de-Anime-main\Arquivos-CRUD; $env:Path += ";C:\Program Files\CodeBlocks\MinGW\bin"; g++ -std=c++17 main.cpp GenrenciadorAnime.cpp -o programa_animes.exe; if ($?) { .\programa_animes.exe }
