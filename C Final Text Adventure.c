#include <stdio.h>
#include <stdlib.h>
//Final project by Ben Onime, Arko Chakraborty & Misha Smirnov
//Contributions (Please, once you edit this file, put in your contributions in front of your names and also, please explain what your tidbit of code does or is supposed to do.)
//Ben: Base File: The enemy and item classes/structs, The Game Over Screen, The Restart menu, Status screens, Starting adventures, Battle scenarios, Basic money and gameplay systems.
//Arko: 
//Misha: 
typedef struct{//This defines the enemy class. This should be useful for battle instances.
   char name[20];
   int health;
   int damage;
   int loot[5];
}enemy;

typedef struct{//This defines the item class. Both the player and enemies should be able to hold items.
   char name[50];
   int damage; //Attack points
   int cost; //Cost to buy or trade for in shop
   int accuracy; //x/100 / x%
}item;

typedef struct{//This defines the player class. This should be useful for the player's stats and inventory.
   char name[100];
   int health;
   int money;
   item weapon;
   item inventory[4];

}player;

int gameover(){//This should be the game over screen
   printf("GAME OVER\n");
   restart();
   return 0;
}
int restart(){//If all things go well, this should go to startadv
   char input;
   scanf(">Restart?(y/n)\n",input);
   if (input == 'y' || input == 'Y'){//Goes to the beginning of the adventure
      startadv();
   }else if (input == 'n' || input == 'N'){//Completely exits the program
      return 0;
   }
}
int HealthStatus(int health){//This is to check how much health the player has.
   if (health < 0){health = 0;}
   printf ("Health: %d\n", health);
   if (health = 0){gameover(); return 0;}
}

int EnemyHealthStatus(int health){//This is to check how much health the enemy has.
   printf("Enemy Health: %d\n", health);
   return health;
}

int MoneyStatus(int money){printf ("Money: %dG\n", money);}//Checks the amount of money being held.

int startadv(){//Adventure starts here.
   int health = 10, key = 0, money = 0, damage = 1;
   char name[100];
   printf("CMPT 242 FINAL PROJECT!!!\n");
   printf("PRESENTED BY BEN, ARKO & MISHA\n");
   HealthStatus(health);
   MoneyStatus(money);
   printf("Hey! Wake up!\n");
   printf("You have been summoned to the castle!\n");
   printf("King: Speak Serf! What is your name?\n");
   scanf("You: My Liege! My name is \n", name);
   printf("King: Stand %c!\n", *name);
   printf("King: You stand here because of your treacherous actions against me!\n");
   printf("King: Luckily, I'm feeling in a good mood so, rather than kill you or banish you, I will give you a choice of 3 errands.\n");
   printf("King: You can go to the (F)orest to retrieve my crown, the (C)ity to retrieve my court's archives or to the (M)ountains to defeat the beast of unknown depths.\n");
   char choice;
   scanf("Which will it be?\n(F)orest\n(C)ity\n(M)ountains\n", choice);
   printf("King: Good Choice! Here is 50 G! and a compass.\n");
   money = money+50;
   if (choice == 'c' || choice == 'C'){
      printf("King: Alright, I'll need you to head west from the town square into the church to retrieve my court's documents.\n");
      printf("King: The Priest stole them from me. Consider this a pardon for your on treachery.\n");
      printf("You arrive at the city...\n");
      City(health, money, name);
   }else if (choice == 'F' || choice == 'f'){
      printf("King: Well, this is the least you could do for your attempted assassination.\n");
      printf("King: Now you will endorse my monarchy and MY leadership as your punishment\n");
      printf("You go to the forest...\n");
      Forest(health, money, name);
   }else if (choice == 'M' || choice == 'm'){
      printf("King: Change of heart? Community Service? Hmm...\n");
      printf("King: Well, you can service the community by getting rid of that monster in the mountains. Maybe then could I pardon you...\n");
      printf("You go to the Mountains...\n");
      Mountains(health, money, name);
   }
}
int City(int health, int money, char name[100]){//This is for the City storyline
   HealthStatus(health);
   MoneyStatus(money);
}
int Forest(int health, int money, char name[100]){// This is for the forest storyline
   HealthStatus(health);
   MoneyStatus(money);
}
int Mountains(int health, int money, char name[100]){//This is for the mountains storyline
   HealthStatus(health);
   MoneyStatus(money);
}
int Shop(int money){//Shop to buy stuff from. Should only be accessible in the city storyline
   printf("Welcome to the Shop! what do you wanna buy?\n");
   MoneyStatus(money);
}
int Battle(int health, int money, char name[100], int enemyHealth, int enemyDamage, char enemyname[20], int damage){
   //health = player's health
   //money = player's money
   //name = your character's name
   //enemyHealth = current opponent's health. Should be declared as enemy.health to be used properly.
   //enemyDamage = how much the current opponent deals in a single turn. There are no Critical hit values or Accuracy values for simplicity sake (as simple as this project can be.) Can be implemented as enemy.damage or enemy.damage+item.damage
   //enemyname = current opponent's name. This can hold a maximum of 20 characters. Should be declared as enemy.name
   //damage = player's attack points. This is the amount of hitpoints the player can take from the enemy in a single turn. This is by default one but can be changed with damage += item.damage
   char interact;
   printf("You have encountered %c!\n", enemyname);
   while (enemyHealth > 0 && health > 0){
      HealthStatus(health);
      EnemyHealthStatus(enemyHealth);
      scanf("How do you want to interact?\n(A)ttack?\n(D)efend?\n(R)un?\n", interact);
      if (interact == 'A'||interact == 'a'){//Attack scenario. Takes off hitpoints from the opponent during your turn.
         enemyHealth -= damage;
         printf("You took %d from %c!\n", damage, enemyname);
      }else if (interact == 'D'||interact == 'd'){//This adds the amount of damage the enmy would have done to the player for that turn so that it gets subtracted when the enemy attacks.
         health += enemyDamage;
         printf("You chose to defend yourself this round!\n");
      }else if (interact == 'R'|| interact == 'r'){//This exits the battle scenario.
         printf("You fled the conflict!\n");
         return health, money;
      }
      //This is the enemy's turn. This can be a case or if-then-else tree if you want.
      health -= enemyDamage;
      printf("%c took %d from you!\n", enemyname, enemyDamage);
   }
   if (enemyHealth <= 0){//This should reward the player then exit the battle scenario
      printf("You have slain %c!\n", enemyname);
      int reward = rand() % 500; //This is how the random function works for some reason...
      money += reward;
      return health, money;
   }else if (health <= 0){//This should go to the gameover screen.
      gameover();
   }
}


int main() {
   setbuf(stdout, NULL);
   startadv();
   return 0;
}
//(._.) slime
//\(_)^> rat