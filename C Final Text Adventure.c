#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{ // Enemy class
   char name[20];
   int health;
   int damage;
} enemy;

typedef struct
{ // Item class
   char name[50];
   int damage;
   int cost;
   int accuracy;
} item;

typedef struct
{ // Player class
   char name[100];
   int health;
   int money;
   item weapon;
   item inventory[4];
} player;

// Enemy and item definitions
item compass = {"Compass", 0, 0, 0};
item HealthPotion = {"Health Potion", -2, 10, 0};
item WoodenSword = {"Wooden Sword", 2, 20, 100};

enemy slime = {"Slime", 5, 1};
enemy rat = {"Rat", 3, 1};

enum Location
{
   Court,
   City,
   Forest,
   Mountains
} loc = Court; // global variable that tracks where we decided to go (court is essentially null, we start there since we havent chosen anything yet)


// to stop errors
int gameover();
int restart();
void gainGold(player *player, int amount);
void loseHealth(player *player, int amount);
void gainHealth(player *player, int amount);
int Battle(player *player, enemy *opponent);
void Encounter(player *player);
void GameLoop(player *player);

int startadv(player *p)
{ // Adventure starts here.

   printf("CMPT 242 FINAL PROJECT!!!\n");
   printf("PRESENTED BY BEN, ARKO & MISHA\n");
   printf("Hey! Wake up!\n");
   printf("You have been summoned to the castle!\n");
   printf("King: Speak Serf! What is your name?\n");
   printf("You: My Liege! My name is ");
   scanf("%49s", p->name);
   printf("King: Stand %s!\n", p->name);
   printf("King: You stand here because of your treacherous actions against me!\n");
   printf("King: Luckily, I'm feeling in a good mood so, rather than kill you or banish you, I will give you a choice of 3 errands.\n");
   printf("King: You can go to the (F)orest to retrieve my crown, the (C)ity to retrieve my court's archives or to the (M)ountains to defeat the beast of unknown depths.\n");

   char choice;
   printf("Which will it be?\n(F)orest\n(C)ity\n(M)ountains\n");
   scanf(" %c", &choice);
  

   if (choice == 'c' || choice == 'C')
   {
      printf("King: Alright, I'll need you to head west from the town square into the church to retrieve my court's documents.\n");
      printf("King: The Priest stole them from me. Consider this a pardon for your on treachery.\n");
      printf("You arrive at the city...\n");
      loc = City;
   }
   else if (choice == 'F' || choice == 'f')
   {
      printf("King: Well, this is the least you could do for your attempted assassination.\n");
      printf("King: Now you will endorse my monarchy and MY leadership as your punishment\n");
      printf("You go to the forest...\n");
      loc = Forest;
   }
   else if (choice == 'M' || choice == 'm')
   {
      printf("King: Change of heart? Community Service? Hmm...\n");
      printf("King: Well, you can service the community by getting rid of that monster in the mountains. Maybe then could I pardon you...\n");
      printf("You go to the Mountains...\n");
      loc = Mountains;
   }

   printf("King: Good Choice! Here is 50 G! and a compass.\n");
   gainGold(p, 50);
}


int gameover()
{ // Game over screen
   printf("GAME OVER\n");
   restart();
   return 0;
}

int restart()
{ // Restart option
   char input;
   printf(">Restart?(y/n)\n");
   scanf(" %c", &input);
   if (input == 'y' || input == 'Y')
   {
      return 1; // Restart game
   }
   else
   {
      return 0; // Exit program
   }
}

void gainGold(player *player, int amount)
{
   player->money += amount;
   printf("[i] You %s %dG! Current Money: %dG\n", amount > 0 ? "gained" : "lost", amount, player->money);
}

void loseHealth(player *player, int amount)
{
   player->health -= amount;
   if (player->health <= 0)
   {
      gameover();
   }
   else
   {
      printf("[i] You lost %d health! Current Health: %d\n", amount, player->health);
   }
}

void gainHealth(player *player, int amount)
{
   if (amount < 0)
   {
      loseHealth(player, amount);
      return;
   }
   player->health += amount;
   printf("[i] You gained %d health! Current Health: %d\n", amount, player->health);
}

int Battle(player *player, enemy *opponent)
{
   printf("[i] You have encountered a %s!\n", opponent->name);

   while (player->health > 0 && opponent->health > 0)
   {
      printf("[i] Your Health: %d\nEnemy Health: %d\n", player->health, opponent->health);

      printf("How do you want to interact?\n(A)ttack\n(D)efend\n(R)un\n");
      char choice;
      scanf(" %c", &choice);

      if (choice == 'A' || choice == 'a')
      {
         opponent->health -= player->weapon.damage;
         printf("You dealt %d damage to %s!\n", player->weapon.damage, opponent->name);
      }
      else if (choice == 'D' || choice == 'd')
      {
         int reducedDamage = opponent->damage / 2;
         loseHealth(player, reducedDamage);
         printf("You defended yourself and reduced incoming damage to %d!\n", reducedDamage);
      }
      else if (choice == 'R' || choice == 'r')
      {
         printf("You fled the battle!\n");
         return 1; // Fled successfully
      }

      if (opponent->health > 0)
      {
         loseHealth(player, opponent->damage);
         printf("%s dealt %d damage to you!\n", opponent->name, opponent->damage);
      }
   }

   if (player->health > 0)
   {
      printf("You defeated the %s!\n", opponent->name);
      int reward = rand() % 20 + 10; // Random gold reward
      gainGold(player, reward);
      return 1; // Battle won
   }

   return 0; // Player died
}

void Encounter(player *player) {
    int scenario = rand() % 4; // Choose a random scenario

    switch (scenario) {
        case 0: // Bandits
            printf("You are ambushed by a group of bandits! What do you do?\n");
            printf("(F)ight them\n(B)ribe them\n(R)un away\n");
            char choice;
            scanf(" %c", &choice);

            if (choice == 'F' || choice == 'f') {
                enemy opponents[] = {slime, rat};
                Battle(player, &opponents[rand() % 2]);
            } else if (choice == 'B' || choice == 'b') {
                int bribe = rand() % 20 + 10;
                if (player->money >= bribe) {
                    player->money -= bribe;
                    printf("You bribed the bandits with %dG and they let you go.\n", bribe);
                } else {
                    printf("You don't have enough money to bribe them! They attack you instead.\n");
                    enemy opponents[] = {slime, rat};
                    enemy selected = opponents[rand() % 2];
                    Battle(player, &selected);
                }
            } else if (choice == 'R' || choice == 'r') {
                printf("You try to run away...\n");
                if (rand() % 2 == 0) {
                    printf("You escaped successfully!\n");
                } else {
                    printf("The bandits catch you!\n");
                    enemy opponents[] = {slime, rat};
                    enemy selected = opponents[rand() % 2];
                    Battle(player, &selected);
                }
            } else {
                printf("Invalid choice. The bandits attack you!\n");
                enemy opponents[] = {slime, rat};
                enemy selected = opponents[rand() % 2];
                Battle(player, &selected);
            }
            break;

        case 1: // Mysterious merchant
            printf("You meet a mysterious merchant on the road. What do you do?\n");
            printf("(T)rade items\n(B)uy a health potion for 10G\n(I)gnore the merchant\n");
            scanf(" %c", &choice);

            if (choice == 'T' || choice == 't') {
                printf("The merchant isn't interested in trades right now.\n");
            } else if (choice == 'B' || choice == 'b') {
                if (player->money >= 10) {
                    player->money -= 10;
                    gainHealth(player, 5);
                    printf("You bought a health potion and gained 5 health!\n");
                } else {
                    printf("You don't have enough gold to buy a health potion.\n");
                }
            } else if (choice == 'I' || choice == 'i') {
                printf("You ignore the merchant and continue on your journey.\n");
            } else {
                printf("Invalid choice. The merchant leaves.\n");
            }
            break;

        case 2: // Lost traveler
            printf("You find a lost traveler who asks for help. What do you do?\n");
            printf("(G)ive them some gold\n(A)sk for a reward\n(I)gnore them\n");
            scanf(" %c", &choice);

            if (choice == 'G' || choice == 'g') {
                int donation = rand() % 10 + 5;
                if (player->money >= donation) {
                    player->money -= donation;
                    printf("You give the traveler %dG. They thank you and give you a small trinket!\n", donation);
                } else {
                    printf("You don't have enough gold to help the traveler.\n");
                }
            } else if (choice == 'A' || choice == 'a') {
                printf("The traveler gives you a map fragment as thanks for your kindness.\n");
            } else if (choice == 'I' || choice == 'i') {
                printf("You ignore the traveler and move on.\n");
            } else {
                printf("Invalid choice. The traveler leaves.\n");
            }
            break;

        default:
            printf("You continue your journey without incident.\n");
            break;
    }
}

void GameLoop(player *player)
{
   int encounters = 6;

   while (encounters > 0 && player->health > 0)
   {
      printf("\nYou continue on your journey...\n");
      Encounter(player);
      encounters--;
   }

   // here we put the final encounters for each storyline
   if (encounters <= 0)
   {
      switch (loc)
      {
      case City:
         printf("In the distance you spot the church. A hooded figure awaits you at the door.\n");
         break;
      case Forest:
         printf("You peel away foliage to reveal a serence clearing. In it stands the thousand-year-old oak. The crown is hidden somewhere here.\n");

         break;
      case Mountains:
         printf("You have arrived at the beast's lair. The air smells strongly of metal.\n");
         break;
      }
   }

   if (player->health > 0)
   {
      printf("Congratulations! You survived your adventure!\n");
      printf("Final Gold: %dG\n", player->money);
   }
}


int main()
{
   srand(time(NULL)); // Seed for random numbers

   player player = {"Hero", 20, 50, WoodenSword, {compass, HealthPotion}};

   startadv(&player);
   GameLoop(&player);

   return 0;
}
