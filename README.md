<h1 align="center">
  FF6 O MAIS BRABO
</h1>

<strong>Nome:</strong><span> Vinícius Alves de Faria Resende</span>
</br>
<strong>Disciplina:</strong><span> Programação e Desenvolvimento de Software 1</span>
</br>
<strong>Professor:</strong><span> Pedro O. S. Vaz de Melo</span>

<h4 align="center">
  Sumário
</h4>

<p align="center">
  <a href="#mag_right-about-the-project">Resumo Informal</a>&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
  <a href="#desktop_computer-layout-of-the-applicationdesktop">Game Lore</a>&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
  <a href="#rocket-launching-the-project">Gameplay</a>&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
  <a href="#man_technologist-used-technologies">Código & Arquitetura</a>&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
  <a href="#raising_hand_man-developer">Developer</a> &nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
  <a href="#trophy-acknowledgment">Acknowledgment</a> 
</p>

</br>

## Resumo Informal:

<p align="justify">
Olá! Esta parte da documentação é completamente opcional, e foi feita apenas com o intuito de desenvolver uma apresentação geral da 
documentação de forma descontraída. Começando, teremos 3 partes principais na documentação, primeiramente você poderá ver a sessão 
de Game Lore, nela eu descrevo um pouco do contexto do jogo, lá, também, você poderá conhecer o nosso personagem Noctis Lucis Caelum, 
alguns dos inimigos e um pouco sobre o espaço. Prosseguindo, teremos a parte de Gameplay, lá há uma breve explicação sobre as features 
do jogo, de forma bem dinâmica e interativa, dessa forma, é possível entender como jogar e no que cada funcionalidade influencia. 
Finalizando, teremos a sessão de Código & Arquitetura, nessa parte final, explicarei com detalhes a arquitetura que tentei 
desenvolver e seguir durante o desenvolvimento da aplicação, além disso falarei sobre as estruturas de dados que existem no 
projeto e para que cada uma funciona, entrarei também nas funções do código explicando o que cada uma faz. Sobre como cada 
função faz o que faz, deixei o código com comentários linha a linha para explicar o funcionamento mais atômico de cada parte do código.

</p>

## Game Lore:

<p align="justify">
No nosso jogo, o herói tenta avançar a todo custo o mais longe que pode para alcançar seu objetivo final de ficar mais poderoso e trazer a paz ao mundo de Final Fantasy, contudo diversos inimigos aparecerão em seu caminho e seu objetivo é derrotá-los independentemente do que aconteça!
</p>

#### Quem é o nosso personagem?

<p align="justify">
Noctis Lucis Caelum é o nosso personagem, mas por que a escolha dele? Bom, por mais que ele não estivesse presente em Final Fantasy durante o jogo 6, pensei em trazê-lo para o contexto do nosso jogo de releitura. Isso porque ele é um dos meus personagens favoritos de todo Final Fantasy, aqui vai uma breve descrição sobre ele:
</p>

<p align="justify">
“Herdeiro aparente do trono de Lucian, as provas de Noctis começam quando ele parte da cidade da coroa para casar com Lunafreya Nox Fleuret. Em combate, ele empunha armas espectrais que forja do ar rarefeito, um poder possuído por aqueles de sua linha real.” ~ Descrição Oficial do Personagem
</p>

<p align="justify">
Agora que conhecemos mais sobre o contexto do nosso personagem, vou apresentar algumas imagens para termos uma aproximação com ele.
</p>

<p align="center">
  <img alt="noctis" src="https://res.cloudinary.com/viniciusalvesdefaria/image/upload/v1630169480/PDS1-TP/noctisGrupo_cnt5wx.png" width="600px" />
</p>

<p align="justify">
No nosso jogo usaremos sprites no estilo 16 bits do personagem, espero que as animações sejam imersivas o suficiente para que ocorra uma identificação com o personagem.
</p>

<p align="justify">
Como vimos acima, nosso personagem pode forjar armas espectrais do nada e com isso ataca seus inimigos, contudo, no momento do jogo, Noctis ainda é bem inexperiente e só consegue forjar um espada simples para seus ataques normais. Apesar disso, Noctis está desenvolvendo suas habilidades e consegue usar um ataque especial extremamente poderoso, porém ainda não o controla muito bem, por isso sua chance de acerto é baixa, mas quando o ataque especial é bem executado, Noctis cria uma espada espectral com magia e pode usá-la para se teletransportar e desferir um ataque diretamente no inimigo, assim pode matar qualquer um dos monstros que está presente na área de exploração com apenas um golpe!!
</p>

#### Quais inimigos podem ser encontrados?

- Scorpio-dragon
  </br>
  <img alt="Scorpio-dragon" src="https://res.cloudinary.com/viniciusalvesdefaria/image/upload/v1630169528/PDS1-TP/enemy0_zk93cb.png" width="150px" />

<p align="justify">
Esse inimigo, apesar de assustador, é o mais fraco que pode ser encontrado no ambiente hostil das missões, porém tome cuidado! Esse dragão tem um rabo de escorpião e pode ser traiçoeiro a qualquer momento para te pegar com a guarda baixa!
</p>

- Tech-Terror
  </br>
  <img alt="Tech-Terror" src="https://res.cloudinary.com/viniciusalvesdefaria/image/upload/v1630169529/PDS1-TP/enemy1_k0rta9.png" width="150px" />

<p align="justify">
Esse inimigo é conhecido por ser o terror tecnológico. Produto de experimentos fracassados, essas máquinas tomaram consciência própria e estão prontas para matar, além disso, o seu nível de poder é superior ao do Scorpio-Dragon. Melhor ficar atento, a inteligência artificial desse monstro possibilita um comportamento único em batalha!
</p>

- Deepcut-Mantis
  </br>
  <img alt="Deepcut-Mantis" src="https://res.cloudinary.com/viniciusalvesdefaria/image/upload/v1630169529/PDS1-TP/enemy2_kg4opt.png" width="150px" />

<p align="justify">
Esse monstro pode até mesmo parecer somente um grande inseto, mas não se engane! O poder do Deepcut-Mantis é superior até a de um Tech-Terror, esse monstro têm inteligência reduzida, contudo, não é necessário para um monstro especializado em matar, seus instintos são mais que o suficiente para acabar um guerreiro inatento, o corte de um Deepcut-Mantis é mais profundo do que o corte de qualquer espada de aço.
</p>

- Hell-Entrance
  </br>
  <img alt="Hell-Entrance" src="https://res.cloudinary.com/viniciusalvesdefaria/image/upload/v1630169529/PDS1-TP/enemy3_wkcc3t.png" width="150px" />

<p align="justify">
Esse monstro, com toda certeza, é o mais temido da região. A aparência assustadora não é só por condolência, essa criatura recebe o nome de Entrada para o Inferno pois ao encontrar esse monstro, poucos guerreiros conseguem sobreviver. Opte por não enfrentar esse monstro, ou guarde suas melhores armas para ele, essa besta é mais poderosa até que um Deepcut-Mantis!
</p>

#### Onde a aventura acontece?

<p align="justify">
Em nosso jogo, a aventura acontece no universo de Final Fantasy e é possível passar por ambientes extremamente hostis onde diversos monstros podem ser encontrados, não se deixe vencer pelo cansaço e vá adiante!
</p>

<p align="justify">
De começo, nosso herói está em um ambiente um pouco mais tranquilo, uma floresta ao entardecer. Contudo os monstros continuam aparecendo no ambiente, e todos eles podem atacar a qualquer momento! Mas neste estágio você pode ficar um pouco mais tranquilo, aproveite para melhorar suas habilidades nesse primeiro estágio, pois no universo de Final Fantasy, o ambiente influencia diretamente no poder dos monstros, e quanto mais você avançar, mais poderosos os monstros ficarão, como uma espécie de enriquecimento de poder por ambiente.
</p>

<p align="justify">
Passando pela primeira floresta, o objetivo é alcançar a caverna do desespero, a caverna tem esse nome pois é um lugar repleto de monstros poderosos, mais poderosos, inclusive, que os monstros da floresta. Nesse ambiente é bom ficar ligado, mas é importante saber que, nesse momento, o desafio está só começando!
</p>

<p align="justify">
Saindo da caverna, nosso herói desemboca diretamente em um ambiente de deserto, mas não um deserto comum, o deserto está posicionado em uma região de mana forte, e, por isso, é comum vermos monstros muito poderosos no local. Mas essa parte da trajetória é necessária, pois nesse deserto está localizado o portal interdimensional, que levará nosso herói para a dimensão corrupta.
</p>

<p align="justify">
Após entrar no portal, Noctis entrará na dimensão corrupta, lá os monstros são extremamente poderosos, sendo mais poderosos que qualquer monstro dos outros ambientes, nesse momento é primordial que o nosso herói esteja bem experiente em batalha, pois, caso contrário, estará em apuros para chegar à luz final.
</p>

## Gameplay:

<p align="justify">
Nessa parte irei apresentar algumas informações sobre como jogar o nosso jogo, de forma que fique claro o entendimento. Então vamos lá!
</p>

#### Movimentação:

<p align="justify">
A movimentação no modo de exploração, se dá pelo uso das setas direcionais do teclado, como demonstrado no vídeo abaixo:
</p>

<p align="center">
  <img alt="Movimentação" src="https://res.cloudinary.com/viniciusalvesdefaria/image/upload/v1630169571/PDS1-TP/TPMovimentacao_gduahm.gif" width="400px" />
</p>

<p align="justify">
A movimentação é bem simples, o objetivo é chegar ao canto inferior direito do mapa. Vale salientar que os “obstáculos” do mapa não interferem na movimentação.
</p>

#### Encontros com Inimigos:

<p align="justify">
  Ao se movimentar pelo mapa, há uma chance de ser interceptado por um inimigo, entrando assim em modo de batalha, segue o vídeo demonstrativo:
</p>

<p align="center">
  <img alt="Encontros com Inimigos" src="https://res.cloudinary.com/viniciusalvesdefaria/image/upload/v1630169594/PDS1-TP/EncontroDeBatalhaTP_xzcchi.gif" width="400px" />
</p>

#### Menu de Batalha:

<p align="justify">
  Durante uma batalha, pode-se usar a seta direcional para cima e para baixo para a navegação no menu e a tecla ‘enter’ para selecionar uma das opções, segue o vídeo demonstrativo:
</p>

<p align="center">
  <img alt="Menu de Batalha" src="https://res.cloudinary.com/viniciusalvesdefaria/image/upload/v1630169617/PDS1-TP/MenuBatalhaTP_hwomzb.gif" width="400px" />
</p>

#### Ação de Ataque:

<p align="justify">
  Ao selecionar a primeira opção do menu, um ataque comum será disparado, e, caso o inimigo não morra com o seu ataque, você receberá um ataque em resposta. É necessário ressaltar que, ao acertar um ataque, o nível de fúria do personagem aumenta, até um máximo de cinco. Segue o vídeo de demonstração: 
</p>

<p align="center">
  <img alt="Ação de Ataque" src="https://res.cloudinary.com/viniciusalvesdefaria/image/upload/v1630169634/PDS1-TP/AtaqueTP_zjqeq1.gif" width="400px" />
</p>

#### Ação de Ataque Especial:

<p align="justify">
  Ao selecionar a ação de ataque especial, há, inicialmente, uma chance de baixa de acerto, contudo, conforme a barra de fúria de Noctis aumenta, mais motivado o herói fica, e assim tem mais chances de acerto! Segue o vídeo de demonstração: 
</p>

<p align="center">
  <img alt="Ação de Ataque Especial" src="https://res.cloudinary.com/viniciusalvesdefaria/image/upload/v1630169653/PDS1-TP/SpecialTP_rnbll7.gif" width="400px" />
</p>

#### Ação de Fuga:

<p align="justify">
  Ao entrar em uma batalha, existe a opção de tentar uma fuga, contudo a chance de fuga não é tão alta, e, no caso de falha, o herói receberá dano. Vale ressaltar que ao fugir de um inimigo, ele continua no mesmo lugar, e pode ser encontrado novamente! Segue o vídeo de demonstração: 
</p>

<p align="center">
  <img alt="Ação de Fuga" src="https://res.cloudinary.com/viniciusalvesdefaria/image/upload/v1630169652/PDS1-TP/FugaTP_yhwqqq.gif" width="400px" />
</p>

#### Níveis e experiência:

<p align="justify">
  Ao abater um inimigo, esse abate é convertido em experiência, e, então, no caso da quantidade de XP necessária para subir de nível ser alcançada, o personagem irá receber um levelUP, dessa forma, irá aumentar sua vida máxima, dano causado e recuperar sua vida para 100%. Utilize isso para conseguir continuar lutando. Você pode consultar sua experiência e nível no menu de exploração:
</p>

<p align="center">
  <img alt="Níveis e experiência" src="https://res.cloudinary.com/viniciusalvesdefaria/image/upload/v1630170647/PDS1-TP/Screenshot_from_2021-08-22_19-00-40_mdyew8.png" width="400px" />
</p>

#### Pontuação:

<p align="justify">
  Ao abater um inimigo, você irá receber uma determinada quantidade de pontos, que serão somados até que se alcance o objetivo final, nesse momento você poderá bater seu recorde pessoal, e esse recorde será armazenado para sessões futuras! Você pode consultar sua pontuação na tela de exploração: 
</p>

<p align="center">
  <img alt="Pontuação" src="https://res.cloudinary.com/viniciusalvesdefaria/image/upload/v1630170647/PDS1-TP/Screenshot_from_2021-08-22_19-03-47_yngagr.png" width="400px" />
</p>

<p align="justify">
  Acho que agora não são mais necessárias explicações, só aproveitar o jogo e fazer as últimas descobertas por si mesmo!
</p>

## Código & Arquitetura:

<p align="justify">
Nessa parte da documentação, a ideia é passar informações sobre o código, de forma que uma pessoa que não participou do desenvolvimento do jogo possa ter entendimento completo acerca do funcionamento. Sendo assim, primeiramente irei descrever um pouco da estratégia de arquitetura do código.
</p>

<p align="justify">
Como um desenvolvedor preocupado com aumentar meu repertório de linguagens que atualmente é limitado ao universo do JavaScript, tentei aproveitar o trabalho para explorar um pouco mais do funcionamento dos ponteiros de C. Nesse sentido, desenvolvi uma espécie de ‘Arquitetura’ para minha aplicação. A ideia principal era separar as responsabilidades do código da melhor maneira, tentando trazer o máximo de atomicidade ao código. Por conta da minha falta de experiência com a linguagem C e sua sintaxe, acredito que não tenha conseguido alcançar, em totalidade, o objetivo que desejava com a arquitetura em questão. Contudo, ainda assim acredito que o resultado foi satisfatório e auxiliou a estrutura lógica do projeto.
</p>

<p align="justify">
Nesse sentido, irei começar setorizando as funções dispostas no código, de forma a categorizá-las por responsabilidade. Segue abaixo alguns bullets que irão facilitar a leitura acerca de cada tipo de função.
</p>

- <p align="justify">
    <strong>Funções Utilitárias (utils functions):</strong> Essas funções têm o intuito único de serem chamadas por outras funções a fim de facilitarem a execução de alguma lógica de maneira modularizada e reaproveitável.
  </p>
- <p align="justify">
    <strong>Funções Inicializadoras (inicialization functions):</strong> Essas funções têm por finalidade, instanciar alguma struct de forma a conter valores estáticos que serão atribuídos à struct em questão, são usadas também para manipular variações entre structs do mesmo tipo.
  </p>
- <p align="justify">
    <strong>Funções Atômicas (atomic functions):</strong> Essas funções, como o próprio nome sugere, tem funcionalidade atômica, ou seja, são responsáveis pelo desenvolvimento de algo extremamente individual, individual ao ponto de que seu nome é suficiente para descrever todo o seu escopo.
  </p>
- <p align="justify">
    <strong>Funções Disparadoras de Evento (event functions):</strong> Essas funções têm como intuito a ativação de eventos no jogo, normalmente irão alterar valores ou chamar alguma função para tal, e essas alterações impactarão em outras partes do código, que estarão ‘escutando’ por esses eventos.
  </p>
- <p align="justify">
    <strong>Funções Manuseadoras (handling functions):</strong> Essas funções têm um nível de abstração um pouco maior, elas são responsáveis por manejar alguma funcionalidade, ou seja, serão responsáveis pelo desenvolvimento de uma feature maior, fazendo chamadas para funções atômicas que, em conjunto, irão executar a ação mútua desejada.
  </p>
- <p align="justify">
    <strong>Funções orquestradoras (orchestrators functions):</strong> Essas funções estão no maior nível de abstração dentre as outras, haja vista que são chamadas diretamente pela função main. Basicamente, uma função orquestradora é responsável por receber vários parâmetros e repassá-los para as respectivas funções que necessitam deles, desenvolvendo assim, uma regra de negócio essencial do código.
  </p>

<p align="justify">
  Após a explicação sobre os tipos de funções, é importante saber qual a responsabilidade da função main no código. Nesse código em específico, a função main é responsável pelo armazenamento de várias variáveis e estruturas de dados, bem como a manipulação do allegro em si, isto é, rotinas de inicialização, captação de eventos, cleanup entre outros. Além disso, a função main possui determinada lógica a fim de discernir sobre a necessidade de chamar determinada função de acordo com a alteração de algum estado ou ação do jogador.
</p>

<p align="justify">
  Passaremos então para as estruturas de dados, quais são e sua importância para o código. Dentre as estruturas de dados, teremos:
</p>

- <p align="justify">
    <strong>HeroInfo:</strong> Nessa estrutura, armazena-se informações gerais do herói que é controlado pelo jogador. De forma sistematizada, são armazenadas informações sobre o posicionamento, atributos de combate, velocidade e atributos de nível do personagem.
  </p>
- <p align="justify">
    <strong>EnemyInfo:</strong> A função dessa estrutura é similar à anterior, nela são armazenadas informações sobre um determinado inimigo, como: posicionamento, atributos de combate e tipo.
  </p>
- <p align="justify">
    <strong>BattleInfo:</strong> Nessa estrutura são armazenados dados sobre uma batalha que está ocorrendo, sempre que uma batalha se inicia, é armazenado em uma estrutura do tipo BattleInfo, o herói e inimigo em questão. Além disso, também são armazenadas variáveis para ações das batalhas.
  </p>
- <p align="justify">
    <strong>EnemyAttackInfo:</strong> Uma vez que o ataque dos inimigos é um projétil, evidenciou-se a necessidade de desenvolver uma struct para conter as informações acerca desse projétil. Portanto, existem informações como posição, activeness e velocidade.
  </p>
- <p align="justify">
    <strong>animation:</strong> Essa struct têm por finalidade facilitar a utilização de um conjunto de imagens para o desenvolvimento de animações no jogo.
  </p>

<p align="justify">
Essencialmente, pensei em ter uma função main com a menor responsabilidade possível, sendo assim a função main é responsável por armazenar
</p>
