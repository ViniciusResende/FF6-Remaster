#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

#define ENEMY_NUM 20
#define ENEMIES_VARIATY 4
#define STAGE_QUANTITY 4
#define HERO_ANIMATIONS_QTD 2
#define ENEMY_ANIMATIONS_QTD 4
#define HERO_HEALTH 200

const float FPS = 60;  
const int SCREEN_W = 640;
const int SCREEN_H = 480;
//variavel global que armazena o tamanho do noctis (quadrado que vai navegar pela tela)
const int HERO_SIZE = 32;
const int ENEMY_HITBOX = 40;

//----------------------- utils functions -------------------------------//

//aleatorio entre 0 e n-1
int randWithRange(int n){
  return rand()%n;
}

//aleatorio entre min e max (inclusive numeros negativos)
int randIntBetween(int min, int max){ //EX: min = 5, max = 10
  return min + randWithRange(max - min + 1);
}

float distBetweenCoordinates(int x1, int y1, int x2, int y2){
  return sqrt( pow(x1 - x2,2) + pow(y1 - y2,2) );
}

//----------------------- data structures -------------------------------//
typedef struct HeroInfo {
	int x, previousX;
	int y, previousY;
	int health;
	int maxHealth;
	int attack;
	int furyLevel;
	int speed;
	int level;
	int exp;
	int expToNextLevel;
}HeroInfo;

typedef struct EnemyInfo {
	int x;
	int y;
	int health;
	int initialHealth;
	int attack;
	int type;
}EnemyInfo;

typedef struct BattleInfo {
	HeroInfo *hero;
	EnemyInfo *enemy;
	int specialMoveActivated;
	int normalAttackActivated;
	int enemyAttackActivated;
}BattleInfo;

typedef struct EnemyAttackInfo{
	int x, y;
	int active;
	int speed;
}EnemyAttackInfo;

typedef struct animation{
	ALLEGRO_BITMAP *spriteImages[26];
	int n;
}animation;

//----------------------- inicialization functions -------------------------------//

void initEnemyAttack (EnemyAttackInfo *attack) {
	attack->x = 100;
	attack->y = 350;
	attack->active = 0;
	attack->speed = 10;
}

void createHero(HeroInfo *hero) {
	hero->x = 1;
	hero->y = 1;
	hero->previousX = 1;
	hero->previousY = 1;

	hero->speed = 20;
	hero->attack = 30;
	hero->health = HERO_HEALTH;
	hero->maxHealth = HERO_HEALTH;
	hero->furyLevel = 0;

	hero->level = 1;
	hero-> exp = 0;
	hero->expToNextLevel = 300;
}

void createEnemy(EnemyInfo *enemy, int currentStage) {
	int type = randIntBetween(1, 4);
	// type 1 -> dragon
	// type 2 -> tech monster
	// type 3 -> mantis
	// type 4 -> skeleton monster
	enemy->type = type;
	int health = 50*currentStage + (type-1)*15;
	enemy->health = health;
	enemy->initialHealth = health;
	enemy->attack = 15*currentStage + (type-1)*5;

	enemy->x = randIntBetween(0, SCREEN_H - 20);
	enemy->y = randIntBetween(0, SCREEN_H - 20);
}

//----------------------- atomic functions -------------------------------//
void drawBackground(ALLEGRO_BITMAP *BG) {
	al_draw_bitmap(BG, 0, 0, 0);
}

void drawStageExit(ALLEGRO_BITMAP *exit) {
	al_draw_bitmap(exit, 500, 280, 0);
}

void drawMapDetails(ALLEGRO_BITMAP *detailBitmap, int positionsArray[], int n) {
	int i;
	for(i = 0; i < n*2; i += 2) {
		al_draw_bitmap(detailBitmap, positionsArray[i], positionsArray[i+1], 0);
	}
}

void drawScore(int score, ALLEGRO_FONT *font) {
	char scoreText[40];
	sprintf(scoreText, "Pontos: %d", score);	
	al_draw_text(font, al_map_rgb(210, 255, 210), SCREEN_W-80, 5, 0, scoreText);
}

void drawCurrentLVL(int lvl, ALLEGRO_FONT *font) {
	char levelText[40];
	sprintf(levelText, "LVL: %d", lvl);	
	al_draw_text(font, al_map_rgb(210, 255, 210), 20, 5, 0, levelText);
}

void drawEXPBar(int currentExp, int requiredExp) {
	al_draw_filled_rounded_rectangle(10, 27, 80, 30, 2, 2, al_map_rgb(100,100,100));
	if(currentExp > 0) {
		float currentPercentage = (70*currentExp)/requiredExp;

		al_draw_filled_rounded_rectangle(10, 27, 10 + (int)currentPercentage, 30, 2, 2, al_map_rgb(210,255,210));
	}
}

void drawExpGap(int currentExp, int requiredExp, ALLEGRO_FONT *font) {
	char levelText[40];
	sprintf(levelText, "%d / %d", currentExp, requiredExp);	
	al_draw_text(font, al_map_rgb(210, 255, 210), 20, 35, 0, levelText);
}

void drawEnemy(ALLEGRO_BITMAP *enemies[], int type) {
	int x, y;
	switch (type)	{
		case 1:
		// dragon
			x = 30;
			y = 300;
			break;
		case 2:
		// tech Monster
			x = 60;
			y = 300;
			break;
		case 3:
		// mantis monster
			x = 60;
			y = 310;
			break;
		case 4:
		// mantis monster
			x = 60;
			y = 310;
			break;
	}
	al_draw_bitmap(enemies[type - 1], x, y, 0);
}

void drawEnemyAttack (EnemyAttackInfo attack, ALLEGRO_BITMAP *enemiesAttack[]) {
	if(attack.active) {
		int initialAttackPosition = 100;
		int attackDistance = 300;
		
		if (attack.x < initialAttackPosition + (attackDistance/5)) {
			al_draw_bitmap(enemiesAttack[0], attack.x, attack.y, 0);	
		} else if (attack.x < initialAttackPosition + (attackDistance/4)) {
			al_draw_bitmap(enemiesAttack[1], attack.x, attack.y, 0);
		} else if (attack.x < initialAttackPosition + (attackDistance/3)) {
			al_draw_bitmap(enemiesAttack[2], attack.x, attack.y, 0);
		} else if (attack.x < initialAttackPosition + (attackDistance/2) + 40) {
			al_draw_bitmap(enemiesAttack[3], attack.x, attack.y, 0);
		} else if (attack.x < initialAttackPosition + (attackDistance)) {
			al_draw_bitmap(enemiesAttack[4], attack.x, attack.y, 0);
		}	
	}
}

void updateAttack (EnemyAttackInfo *attack, BattleInfo *currentBattle) {
	if(attack->active){
		attack->x += attack->speed;
		if(attack->x >= 400) {
			attack->active = 0;
			attack->x = 100;
			currentBattle->hero->health -= currentBattle->enemy->attack;
		}
	}
}

int colisionBetweenHeroMonster(HeroInfo hero, EnemyInfo enemy){
	if(distBetweenCoordinates(hero.x, hero.y, enemy.x, enemy.y) <= ENEMY_HITBOX && enemy.health > 0)
		return 1;
	return 0;
}

int colisionBetweenMonsters(EnemyInfo firstEnemy, EnemyInfo secondEnemy){
	if(distBetweenCoordinates(firstEnemy.x, firstEnemy.y, secondEnemy.x, secondEnemy.y) <= ENEMY_HITBOX + 40)
		return 1;
	return 0;
}

int isPossibleToInsertMonster(EnemyInfo currentEnemy, EnemyInfo enemies[], int enemyQuantity) {
	for (int i = 0; i < enemyQuantity; i++)	{
		if(colisionBetweenMonsters(currentEnemy, enemies[i])) 
			return 0;
	}
	return 1;
}

void drawAnimation(animation animation, int tickRate, int renderPosition) {
	int i ;
	
	for (i = 0; i < animation.n; i++)	{
		if(renderPosition < tickRate*(i+1) && renderPosition >= tickRate*i)
			al_draw_bitmap(animation.spriteImages[i], 80, 200, 0);	
	}
}

void drawExplorationHero(int heroMovePosition, ALLEGRO_BITMAP *heroBitmap, HeroInfo heroData) {
	switch (heroMovePosition)	{
		case 0:
			//donw
			al_draw_rotated_bitmap(heroBitmap, 16, 16, heroData.x +16, heroData.y +16, 1, ALLEGRO_FLIP_HORIZONTAL);
			break;
		case 1:
			//right
			al_draw_bitmap(heroBitmap, heroData.x, heroData.y, ALLEGRO_FLIP_HORIZONTAL);
			break;
		case 2:
			//up
			al_draw_rotated_bitmap(heroBitmap, 16, 16, heroData.x+16, heroData.y+16,	5,	ALLEGRO_FLIP_HORIZONTAL);
			break;
		case 3:
			//left
			al_draw_bitmap(heroBitmap, heroData.x, heroData.y, 0);
			break;
		default:
			al_draw_bitmap(heroBitmap, heroData.x, heroData.y, ALLEGRO_FLIP_HORIZONTAL);
			break;
	}
}

void drawBattleMenuContainer() {
	al_draw_filled_rounded_rectangle(500, 390, 630, 460, 4, 4, al_map_rgb(89,86,247));
	al_draw_filled_rounded_rectangle(490, 380, 620, 450, 4, 4, al_map_rgb(255,255,247));
}

void drawBattleMenuSelector(int selectorPosition) {
	al_draw_filled_triangle(500, 390 + selectorPosition*20, 500, 400 + selectorPosition*20, 510, 395 + selectorPosition*20, al_map_rgb(255, 0, 255));
}

void drawBattleMenuText(ALLEGRO_FONT *font) {
	char attackText[20];
	sprintf(attackText, "Atacar");	
	al_draw_text(font, al_map_rgb(0, 0, 0), 520, 385, 0, attackText);
	char specialText[20];
	sprintf(specialText, "Special");	
	al_draw_text(font, al_map_rgb(0, 100, 100), 520, 405, 0, specialText);
	char runText[20];
	sprintf(runText, "Fugir");	
	al_draw_text(font, al_map_rgb(0, 0, 0), 520, 425, 0, runText);
}

void drawHeroLifeBar(BattleInfo currentBattle) {
	al_draw_filled_rounded_rectangle(370, 230, 520, 250, 4, 4, al_map_rgb(100,100,100));
	if(currentBattle.hero->health > 0) {
		int maxBar = currentBattle.hero->maxHealth;
		float currentPercentage = (150*currentBattle.hero->health)/maxBar;
		al_draw_filled_rounded_rectangle(370, 230, 370 + (int)currentPercentage, 250, 4, 4, al_map_rgb(14,200,14));
	}
}

void drawHeroFuryBar(BattleInfo currentBattle) {
	al_draw_filled_rounded_rectangle(400, 260, 490, 265, 4, 4, al_map_rgb(100,100,100));
	if(currentBattle.hero->furyLevel > 0)
		al_draw_filled_rounded_rectangle(400, 260, 400 + (currentBattle.hero->furyLevel*18), 265, 4, 4, al_map_rgb(255,114,20));
}

void drawEnemyLifeBar(BattleInfo currentBattle) {
	al_draw_filled_rounded_rectangle(25, 230, 175, 250, 4, 4, al_map_rgb(100,100,100));
	if(currentBattle.enemy->health > 0) {
		int maxBar = currentBattle.enemy->initialHealth;
		float currentPercentage = (150*currentBattle.enemy->health)/maxBar;

		al_draw_filled_rounded_rectangle(25, 230, 25 + (int)currentPercentage, 250, 4, 4, al_map_rgb(14,200,14));
	}
}

void heroRun(BattleInfo *currentBattle, int *isInBattleMode) {
	*isInBattleMode = 0;
	currentBattle->hero->x = currentBattle->hero->previousX;
	currentBattle->hero->y = currentBattle->hero->previousY;
}


//----------------------- event functions -------------------------------//

void fireEnemyAttack (EnemyAttackInfo *attack) {
	if(!attack->active) {
		attack->active = 1;
	}
}

void fireHeroRun(int *isInBattleMode, BattleInfo *currentBattle, EnemyAttackInfo *attack) {
	if(rand()%2){
		heroRun(currentBattle, isInBattleMode);
	} else {
		fireEnemyAttack(attack);
	}
}

void fireHeroAttack(BattleInfo *currentBattle) {
	currentBattle->normalAttackActivated = 1;
}

void fireHeroSpecialAttack(BattleInfo *currentBattle, EnemyAttackInfo *attack, int *enemiesDefeated) {
	if(randIntBetween(1, 10) + currentBattle->hero->furyLevel > 9) {
		currentBattle->specialMoveActivated = 1;
		currentBattle->hero->furyLevel = 0;
		currentBattle->hero->exp += (currentBattle->enemy->type*75);
		*enemiesDefeated += 1;
	} else {
		fireEnemyAttack(attack);
	}
}

//----------------------- handling functions -------------------------------//

void handleDrawExp(HeroInfo heroData, ALLEGRO_FONT *font) {
	drawCurrentLVL(heroData.level, font);
	drawEXPBar(heroData.exp , heroData.expToNextLevel);
	drawExpGap(heroData.exp , heroData.expToNextLevel, font);
}

void handleHeroAttackFinish(BattleInfo *currentBattle, EnemyAttackInfo *attack, int *enemiesDefeated) {
	currentBattle->normalAttackActivated = 0;
	currentBattle->enemy->health -= currentBattle->hero->attack;

	if(currentBattle->hero->furyLevel < 5) 
		currentBattle->hero->furyLevel += 1;

	if(currentBattle->enemy->health >= 0) {
		fireEnemyAttack(attack);
	} else {
		currentBattle->hero->exp += (currentBattle->enemy->type*85);
		*enemiesDefeated += 1;
	}
}

void handleEnemyAttack(EnemyAttackInfo *attack, BattleInfo *currentBattle, animation enemyAnimations[]) {
	drawEnemyAttack(*attack, enemyAnimations[(currentBattle->enemy->type) - 1].spriteImages);
	updateAttack(attack, currentBattle);
}

void handleDrawBattleHero(BattleInfo currentBattle, ALLEGRO_BITMAP *staticHero, animation heroAnimations[], int renderPosition) {
	if(currentBattle.specialMoveActivated) {
		drawAnimation(heroAnimations[0], 6, renderPosition);		
	} else if (currentBattle.normalAttackActivated) {
		drawAnimation(heroAnimations[1], 8, renderPosition);
	} else {
		al_draw_bitmap(staticHero, 380, 320, 0);
	}
}

void handleSpecialAttackFinish(BattleInfo *currentBattle, int *renderPosition) {
	if( *renderPosition > 155) {
		currentBattle->specialMoveActivated = 0;
		*renderPosition = 0;
		currentBattle->enemy->health = 0;
	}
}

void handleNormalAttackFinish(BattleInfo *currentBattle, int *renderPosition, EnemyAttackInfo *attack, int *enemiesDefeated) {
	if(*renderPosition > 39) {
		*renderPosition = 0;
		handleHeroAttackFinish(currentBattle, attack, enemiesDefeated);
	}
}

void handleDrawBattleMenu(int selectorPosition, ALLEGRO_FONT *font) {
	drawBattleMenuContainer();
	drawBattleMenuSelector(selectorPosition);
	drawBattleMenuText(font);
}

void handleDrawBattleLifeBars(BattleInfo currentBattle) {
	drawHeroLifeBar(currentBattle);
	drawEnemyLifeBar(currentBattle);
}

// void handleFinishRund(int enemiesDefeated) {
// 	drawEndGameMessage(enemiesDefeated);
// }
//----------------------- orchestrators functions -------------------------------//

void explorationOrchestrator (
	ALLEGRO_BITMAP *BG, 
	ALLEGRO_BITMAP *obstacle, 
	ALLEGRO_BITMAP *stageExit, 
	int brushPositions[], 
	int heroMovePosition, 
	ALLEGRO_BITMAP *heroBitmap, 
	HeroInfo heroData,
	int enemiesDefeated,
	ALLEGRO_FONT *font
	) {
	drawBackground(BG);
	drawStageExit(stageExit);
	drawExplorationHero(heroMovePosition, heroBitmap, heroData);
	// draw obstacle
	drawMapDetails(obstacle, brushPositions, 15);
	handleDrawExp(heroData, font); 
	drawScore(enemiesDefeated, font);
}

void battleOrchestrator (
	int menuPosition, 
	BattleInfo *currentBattle, 
	ALLEGRO_BITMAP *BG, 
	ALLEGRO_BITMAP *hero, 
	animation heroAnimations[],
	ALLEGRO_BITMAP *enemies[],
	animation enemyAnimations[],
	EnemyAttackInfo *attack,
	int *renderPosition,
	int *enemiesDefeated,
	ALLEGRO_FONT *font
	) {
  drawBackground(BG);

	drawEnemy(enemies, currentBattle->enemy->type);
	handleDrawBattleHero(*currentBattle, hero, heroAnimations, *renderPosition);

	handleEnemyAttack(attack, currentBattle, enemyAnimations);
	if(currentBattle->specialMoveActivated) 
		handleSpecialAttackFinish(currentBattle, renderPosition);
	if(currentBattle->normalAttackActivated)
		handleNormalAttackFinish(currentBattle, renderPosition, attack, enemiesDefeated);
	
	handleDrawBattleMenu(menuPosition, font);

	handleDrawBattleLifeBars(*currentBattle);
	drawHeroFuryBar(*currentBattle);
}
 
void battleActionsOrchestrator(int actionType, int *isInBattleMode, BattleInfo *currentBattle, EnemyAttackInfo *attack, int *enemiesDefeated) {
	switch (actionType)	{
		case 0:
			fireHeroAttack(currentBattle);
			break;
		case 1:
			fireHeroSpecialAttack(currentBattle, attack, enemiesDefeated);
			break;
		case 2:
			fireHeroRun(isInBattleMode, currentBattle, attack);
			break;
	}
}

int main(int argc, char **argv) {
	// inicia variaveis para serem usadas em laços pelo codigo
	int i;
	int j;
	
	// inicia instancias basicas do allegro inicialmente como NULL
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;

	// cria um vetor de animacoes com a quantidade de animações que terao no codigo
	animation heroAnimations[HERO_ANIMATIONS_QTD];
	animation enemyAnimations[ENEMY_ANIMATIONS_QTD];
	// variaveis de estado do jogo
	int isPlaying = 1;
	int isInBattleMode = 0;
	int hasFinishedRun = 0;
	int hasDied = 0;
	int currentStage= 1;

	// variavel usada como temporizador de renderizacao(Ex: usada para calcular tempo de cada sprite em animacao)
	int numOfRender = 0;

	// indica a posicao atual do menu de batalha
	int menuPosition = 0; // 0 -> ataque / 2 -> especial / 3 -> fugir
	// indica para onde o personagem deve estar direcionado
	int heroMovePosition = 1; // 0 -> baixo/ 1 -> direita / 2 -> cima / 3-> esqueda
	// contador de inimigos derrotados
	int enemiesDefeated = 0;

	BattleInfo currentBattle;
	
	// instancia uma struct do tipo HeroInfo, ou seja, cria a variavel para armazenar os dados do heroi
	HeroInfo NoctisLucisCaelum;
	createHero(&NoctisLucisCaelum);

	EnemyInfo enemy[ENEMY_NUM];

	for(i=0; i<ENEMY_NUM; i++) {
		do {
			createEnemy(&enemy[i], currentStage);
		} while (!isPossibleToInsertMonster(enemy[i], enemy, i));
		fprintf(stderr, "enemy coords: (x: %d, y: %d)\n", enemy[i].x, enemy[i].y);
	}

	EnemyAttackInfo enemyAttack;

	initEnemyAttack(&enemyAttack);

	// cria uma array contendo as posicoes das moitas no mapa primeiro o a[i] = x a[i+1] = y
	int brushPositions[30] = {0};

	for(int i = 0; i < 30; i++) {
		if(i % 2 == 0) {
			//width
			brushPositions[i] = rand()%400 - i;
		} else {
			//height
			brushPositions[i] = rand()%300 + i;
		}
	}

	//----------------------- rotinas de inicializacao allegro ---------------------------------------//
	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	if(!al_init_primitives_addon()){
	fprintf(stderr, "failed to initialize primitives!\n");
		return -1;
	}

	if(!al_init_image_addon()){
	fprintf(stderr, "failed to initialize images!\n");
		return -1;
	}
	
	if(!al_install_audio()){
	fprintf(stderr, "failed to install audio!\n");
		return -1;
	}

	timer = al_create_timer(1.0 / FPS);
	if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}
	al_set_window_title(display, "FF6 O MAIS BRABO");

	// inicializa o modulo allegro que carrega as fontes
  al_init_font_addon();
	// inicializa o modulo allegro que entende arquivos tff de fontes
  al_init_ttf_addon();
 	ALLEGRO_FONT *arial_size_16 = al_load_font("assets/fonts/arial.ttf", 16, 1);

	// inicializa o modulos do allegro para usar audio
	al_init_acodec_addon();
  al_reserve_samples(1); 
	ALLEGRO_SAMPLE* sound = al_load_sample("assets/sound/backgroundMusic.wav");
 	//----------------------- inicializacao de bitmaps ---------------------------------------//
	char str[80];
	// exploration
	ALLEGRO_BITMAP *explorationBackgrounds[STAGE_QUANTITY];
	for (i = 0; i < STAGE_QUANTITY; i++) {
   	sprintf(str, "assets/images/scenario/exploration/backgrounds/explorationBG%d.jpg", i);
		explorationBackgrounds[i] = al_load_bitmap(str);
	}

	// battle
	ALLEGRO_BITMAP *battleBackgrounds[STAGE_QUANTITY];
	for (i = 0; i < STAGE_QUANTITY; i++) {
   	sprintf(str, "assets/images/scenario/battle/battleBG%d.jpg", i);
		battleBackgrounds[i] = al_load_bitmap(str);
	}
	
	// obstacles
	ALLEGRO_BITMAP *obstacles[STAGE_QUANTITY];
	for (i = 0; i < STAGE_QUANTITY; i++) {
   	sprintf(str, "assets/images/scenario/exploration/obstacles/obstacle%d.png", i);
		obstacles[i] = al_load_bitmap(str);
	}

	// stage exits
	ALLEGRO_BITMAP *stageExits[STAGE_QUANTITY];
	for (i = 0; i < STAGE_QUANTITY; i++) {
   	sprintf(str, "assets/images/scenario/exploration/exits/stageExit%d.png", i);
		stageExits[i] = al_load_bitmap(str);
	}
	// hero
	ALLEGRO_BITMAP *noctis = al_load_bitmap("assets/images/hero/noctisSprite.png");

	
	// hero
	ALLEGRO_BITMAP *noctisBig = al_load_bitmap("assets/images/hero/noctisSpriteBig.png");
	// hero animations

	//hero special attack
	heroAnimations[0].n = 26;
	for (i = 0; i < 26; i++) {
   	sprintf(str, "assets/images/hero/specialAttack/noctisSpecial%d.png", i);
		heroAnimations[0].spriteImages[i] = al_load_bitmap(str);
	}

	//hero normal attack
	heroAnimations[1].n = 5;
	for (i = 0; i < 5; i++) {
   	sprintf(str, "assets/images/hero/normalAttack/noctisAttack%d.png", i);
		heroAnimations[1].spriteImages[i] = al_load_bitmap(str);
	}

	// enemies
	ALLEGRO_BITMAP *enemiesSprites[ENEMIES_VARIATY];
	for (i = 0; i < ENEMIES_VARIATY; i++) {
   	sprintf(str, "assets/images/enemy/enemiesSprites/enemy%d.png", i);
		enemiesSprites[i] = al_load_bitmap(str);
	}	

	//Enemy Attack animation
	for (i = 0; i <= ENEMY_ANIMATIONS_QTD; i++) {
		enemyAnimations[i].n = 5;
		for (j = 0; j < 5; j++) {
			sprintf(str, "assets/images/enemy/enemiesAttacks/enemy%dAttack%d.png", i, j);
			enemyAnimations[i].spriteImages[j] = al_load_bitmap(str);
		}	
	}
	

	if(!noctis) {
		fprintf(stderr, "failed to create noctis bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}
	  
	// possibilita o uso do teclado	
  al_install_keyboard();
 
	// desenha a tela de exploração como default
  explorationOrchestrator(explorationBackgrounds[currentStage-1], obstacles[currentStage-1], stageExits[currentStage-1], brushPositions, heroMovePosition, noctis, NoctisLucisCaelum, enemiesDefeated, arial_size_16);		
 
	// cria a fila de eventos
	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_bitmap(noctis);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}
 
	// registra na fila de eventos que eu quero identificar quando a tela foi alterada
  al_register_event_source(event_queue, al_get_display_event_source(display));
	// registra na fila de eventos que eu quero identificar quando o tempo alterou de t para t+1
  al_register_event_source(event_queue, al_get_timer_event_source(timer));
  // registra que a fila de eventos deve detectar quando uma tecla for pressionada no teclado
  al_register_event_source(event_queue, al_get_keyboard_event_source());   
 

	// reinicializa a tela
  al_flip_display();
	// inicia o temporizador
  al_start_timer(timer);
	//inicia som do jogo
	al_play_sample(sound, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
 
	// enquanto isPlaying o looping ira ser executado:
  while(isPlaying) {
    ALLEGRO_EVENT ev;

	  // espera por um evento e o armazena na variavel de evento ev
    al_wait_for_event(event_queue, &ev);

	  
		// para eventos de tecla pressionada
		if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
		// verifica se esta em modo de batalha
		if(!isInBattleMode){
			// se for modo de exploracao:

			// assim atualizo a variavel de previous x e previou y para o valor de x e y antes desse valor ser alterado
			NoctisLucisCaelum.previousX = NoctisLucisCaelum.x;
			NoctisLucisCaelum.previousY = NoctisLucisCaelum.y;

			// verifica a tecla pressionada e executa acao correspondente
			switch(ev.keyboard.keycode) {
				// se a tecla for o W
				case ALLEGRO_KEY_UP:
					// verifica se o heroi nao ira sair da tela por cima
					if(NoctisLucisCaelum.y > 0 + HERO_SIZE) {
						// subtrai o y pela velocidade do heroi
						NoctisLucisCaelum.y -= NoctisLucisCaelum.speed;	
						// altera a posicao do heroi para 2 -> cima
						heroMovePosition = 2;				
					}
				break;

				case ALLEGRO_KEY_DOWN:
					if(NoctisLucisCaelum.y < SCREEN_H - 2*HERO_SIZE)			
						NoctisLucisCaelum.y += NoctisLucisCaelum.speed;
						heroMovePosition = 0;
				break;

				case ALLEGRO_KEY_LEFT:
					if(NoctisLucisCaelum.x > 0 + HERO_SIZE) {
						NoctisLucisCaelum.x -= NoctisLucisCaelum.speed;
						heroMovePosition = 3;
					} 
				break;

				case ALLEGRO_KEY_RIGHT:
					if(NoctisLucisCaelum.x < SCREEN_W - HERO_SIZE) 
						NoctisLucisCaelum.x += NoctisLucisCaelum.speed;
						heroMovePosition = 1;
				break;

				// encerra o jogo
				case ALLEGRO_KEY_ESCAPE:
					isPlaying = 0;
				break;
			}
		} else {
			// se for modo de batalha:
			switch(ev.keyboard.keycode) {
				// se a tecla for o W
				case ALLEGRO_KEY_UP:
					// sobe a posicao do item selecionado e se chegar no primeiro item coloca a posicao para o ultimo item
					if(menuPosition > 0) {
						menuPosition--;
					} else {
						menuPosition = 2;
					}
				break;

				case ALLEGRO_KEY_DOWN:
					if(menuPosition < 2) {
						menuPosition++;
					} else {
						menuPosition = 0;
					}
				break;
				// escolhe opcao
				case ALLEGRO_KEY_ENTER:
					// verifica se as acoes de batalha estao toda em estado inativo
					if(!currentBattle.specialMoveActivated && !currentBattle.normalAttackActivated){
						// chama funcao que lida com o disparo de acoes de batalha
						battleActionsOrchestrator(menuPosition, &isInBattleMode, &currentBattle, &enemyAttack, &enemiesDefeated);
					}
				break;

				// encerra o jogo
				case ALLEGRO_KEY_ESCAPE:
					isPlaying = 0;
				break;
			}
		}
	}	  

		// no caso da vida do heroi chegar a 0 encerra o jogo e altera a variavel hasDied para 1
		if( NoctisLucisCaelum.health <= 0 ) {
			isPlaying = 0;
			hasDied = 1;
		}

		// no caso do personagem chegar a entrada da caverna
		if( NoctisLucisCaelum.x + HERO_SIZE >= 600 && NoctisLucisCaelum.y + HERO_SIZE  >= 440 ) {
			NoctisLucisCaelum.x = 0;
			NoctisLucisCaelum.y = 0;

			currentStage++;

			for(i=0; i<ENEMY_NUM; i++) {
				do {
					createEnemy(&enemy[i], currentStage);
				} while (!isPossibleToInsertMonster(enemy[i], enemy, i));
				fprintf(stderr, "enemy coords: (x: %d, y: %d)\n", enemy[i].x, enemy[i].y);
			}

			if( currentStage > 4) {
				isPlaying = 0;
				hasFinishedRun = 1;
			}
		}
 
		// no caso do persongem subir de nivel
		if(NoctisLucisCaelum.exp >= NoctisLucisCaelum.expToNextLevel && !isInBattleMode) {
			NoctisLucisCaelum.exp -= NoctisLucisCaelum.expToNextLevel;
			NoctisLucisCaelum.level += 1;
			NoctisLucisCaelum.expToNextLevel += NoctisLucisCaelum.expToNextLevel*(NoctisLucisCaelum.level/4);

			NoctisLucisCaelum.attack += 5*NoctisLucisCaelum.level;
			NoctisLucisCaelum.maxHealth += 15*NoctisLucisCaelum.level;
			NoctisLucisCaelum.health = NoctisLucisCaelum.maxHealth;
		}

		//se o tipo de evento for um evento do temporizador, ou seja, se o tempo passou de t para t+1
    if(ev.type == ALLEGRO_EVENT_TIMER) {
			// verifico o modo atual
			if(isInBattleMode) {
				// se modo de batalha: 

				// caso a vida do inimigo da batalha atual seja menor ou igual a 0 sai do modo de batalha
				if(currentBattle.enemy->health <= 0) {
					isInBattleMode = 0;
				}
				// chama a funcao orquestradora que desenha o cenario de batalha
				battleOrchestrator(menuPosition, &currentBattle, battleBackgrounds[currentStage-1], noctisBig, heroAnimations, enemiesSprites, enemyAnimations, &enemyAttack, &numOfRender, &enemiesDefeated, arial_size_16);
				
				// no caso de uma acao que contem animacao ser disparada, aumenta o contador de renderizacao
				if(currentBattle.specialMoveActivated || currentBattle.normalAttackActivated) {
					numOfRender++;
				}
			} else {
				// se modo de exploracao: 
				// chama a funcao orquestradora que desenha o cenario de exploracao
				explorationOrchestrator(explorationBackgrounds[currentStage-1], obstacles[currentStage-1], stageExits[currentStage-1], brushPositions, heroMovePosition, noctis, NoctisLucisCaelum, enemiesDefeated, arial_size_16);
			
				// para cada um dos inimigos
				for(i=0; i<ENEMY_NUM; i++) {
					// se existe colisao entre heroi e algum inimigo
					if(colisionBetweenHeroMonster(NoctisLucisCaelum, enemy[i])) {
						isInBattleMode = 1;

						// adiciona o heroi e o inimigo em questao a variavel que contem a batalha atual
						currentBattle.hero = &NoctisLucisCaelum;
						currentBattle.enemy = &enemy[i];

						// reinicia todos os eventos de batalha
						currentBattle.specialMoveActivated = 0;
						currentBattle.normalAttackActivated = 0;
						currentBattle.enemyAttackActivated = 0;
					}
				}
			}

			// reinicializa a tela
			al_flip_display();
    }

		//se o tipo de evento for o fechamento da tela (clique no x da janela)
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			//interrompe o while(1)
			break;
		}
 
  } //fim do while principal
  
	// carrega o arquivo arial.ttf da fonte Arial e define que sera usado o tamanho 32 (segundo parametro)
  ALLEGRO_FONT *size_32 = al_load_font("assets/fonts/arial.ttf", 32, 1);	
	
	char my_text[50];	
		
	//colore toda a tela de preto
	al_clear_to_color(al_map_rgb(0,0,0));

	// no caso do heroi ter terminado o jogo
	if(hasFinishedRun) {
		// imprime a mensagem de finlizacao e a quantidade de pontos
		sprintf(my_text, "Você finalizou o jogo!");	
		al_draw_text(size_32, al_map_rgb(0, 200, 30), SCREEN_W/2 - 150, SCREEN_H/5 - 10, 0, my_text);
		sprintf(my_text, "Você fez um total de %d pontos.", enemiesDefeated);	
		al_draw_text(size_32, al_map_rgb(52, 235, 168), SCREEN_W/2 - 220, SCREEN_H/2 - 10, 0, my_text);

		// inicializa variaveis para manipular aquivos
		FILE *arq, *arq_aux;
		// inicia variavel para armazenar recorde
		int maxScoreRecorded;
		// le arquivo e armazena valor na variavel
  	arq = fopen("maxScore.txt", "r");
		fscanf(arq, "%d", &maxScoreRecorded);

		// no caso do recorde ser menor que a pontuacao atual, aidicona "antigo " a variavel
		char previousRecord[10];
		sprintf(previousRecord, maxScoreRecorded >= enemiesDefeated ? "" : "antigo ");

		// imprime o recorde de pontos
		sprintf(my_text, "Seu %srecorde eh de %d pontos.", previousRecord, maxScoreRecorded);	
		al_draw_text(size_32, al_map_rgb(52, 235, 168), SCREEN_W/2 - 220, SCREEN_H - 150, 0, my_text);

		// caso o recorde tenha sido batido
		if(enemiesDefeated > maxScoreRecorded) {
			// escreve novo recorde no arquivo
  		arq_aux = fopen("maxScore.txt", "w");
			fprintf(arq_aux, "%d", enemiesDefeated);
  		fclose(arq_aux);
			// exibe mensagem de parabens por atingir novo recorde
			sprintf(my_text, "Parabens pelo novo recorde!!");	
			al_draw_text(size_32, al_map_rgb(52, 235, 168), SCREEN_W/2 - 220, SCREEN_H - 50, 0, my_text);
		}

		fclose(arq);
	}

	// no caso do heroi ter morrido :(
	if(hasDied){
		sprintf(my_text, "YOU DIED");	
		al_draw_text(size_32, al_map_rgb(255, 80, 40), SCREEN_W/2 - 80, SCREEN_H/2 - 10, 0, my_text);
	}
	
	//reinicializa a tela
	al_flip_display();	
  al_rest(3);		
   
	//procedimentos de fim de jogo (fecha a tela, limpa a memoria, etc)
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_bitmap(noctis);
	al_destroy_bitmap(noctisBig);

	for (i = 0; i < STAGE_QUANTITY; i++) {
		al_destroy_bitmap(explorationBackgrounds[i]);
	}

	for (i = 0; i < STAGE_QUANTITY; i++) {
		al_destroy_bitmap(battleBackgrounds[i]);
	}

	for (i = 0; i < STAGE_QUANTITY; i++) {
		al_destroy_bitmap(obstacles[i]);
	}

	for (i = 0; i < STAGE_QUANTITY; i++) {
		al_destroy_bitmap(stageExits[i]);
	}

	for (i = 0; i < ENEMIES_VARIATY; i++)	{
		al_destroy_bitmap(enemiesSprites[i]);
	}

	for(i=0; i<HERO_ANIMATIONS_QTD; i++) {
		for (j = 0; i < heroAnimations[i].n; i++)	{
			al_destroy_bitmap(heroAnimations[i].spriteImages[j]);
		}
	}

  return 0;
}