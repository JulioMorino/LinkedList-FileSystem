<h1>Resumo</h1>

<span>A ideia geral é criar um diretório raiz e, a partir dele, criar arquivos, pastas e navegar pelo sistema de arquivos;</span>

<span>Um diretório tem como "child" os arquivos ou pastas dentro dele. Arquivos/pastas no mesmo diretório ligam-se um ao outro pelo campo "sibling" e todos possuem o diretório como "parent" em comum;</span>

<span>É apenas uma representação com lista ligada, então nenhum arquivo será gerado no computador que estiver rodando o programa;</span>

<span>Quando quiser alterar o diretório, use o caminho completo, exemplo: \C:\pasta1exemplo\pasta2exemplo</span>

![explicacao_trabalho](https://github.com/user-attachments/assets/78e7e36a-fd5d-4474-97aa-04640ab1d9d1)


<h2>Inserindo arquivos/pastas</h2>
<li>Quando um arquivo é criado, cria-se um novo nó, com "isDirectory" marcado como 0 e inicializa-se "size" com a entrada digitada pelo usuário;</li>
<li>Mesma ideia para pastas, mas elas possuem "isDirectory" marcado como 1 e são inicializadas com "size" 0;</li>
<li>Cada arquivo/pasta terá como "parent" o diretório em que ele está e "sibling" o próximo arquivo ou pasta nesse mesmo diretório;</li>
<li>Cada inserção dispara uma recursiva que atualiza o tamanho dos diretórios, isto é, "subo" a lista em direção aos pais e vou atualizando "size";</li>
<hr>
<h2>Navegando pelos caminhos</h2>
<li>A lógica para navegar foi feita utilizando o strtok do "wishedPath" indicado pelo usuário; <li>
<li>O strtok é importante para dividirmos esse "wishedPath" em tokens separadas por "\" e assim, um por um, ir avançando o diretorio para o destino desejado.</li>

Exemplo de navegação:
"\C:\pasta1exemplo\pasta2exemplo"

Primeiro salta-se o "\C:" pois já tratei o caso em que o usuário quer retornar a raiz. Como o separador é a barra, nosso primeiro token será:
pasta1exemplo


O programa procura se existe algum nó com esse nome && é um diretório (isDirectory == 1). Se não, já indica que o caminho é inválido, se sim,
entra nesse diretório (mesmo que ir para o filho dessa pasta) e continua a busca.

Nosso segundo token será:
pasta2exemplo

Assim segue o ciclo, tendo como condição de parada um token igual a NULL, que ocorrerá quando a string path acaba.
Por fim, retorna o ponteiro e o caminho atual guardado na main (ponteiro currentDirectory) é alterado.

