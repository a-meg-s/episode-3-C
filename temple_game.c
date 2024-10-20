#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_HEALTH 50
#define FIGHTER_DEFENSE 12
#define MAGE_DEFENSE 8
#define SLIME_ATTACK_DAMAGE 2
#define SKELETON_SWORD_DAMAGE 5
#define SKELETON_ARROW_DAMAGE 3
#define MIMIC_BITE_DAMAGE 10

// Character structure
struct Character
{
    char type[10];
    int health;
    int defense;
    int mana;
    int attack_bonus;
};

// Function Prototypes
void introduction();
void chooseCharacter(struct Character *player);
void firstRoom(struct Character *player);
void secondRoom(struct Character *player);
void pressEnterToContinue();
void battleSlime(struct Character *player);
void battleSkeleton(struct Character *player);
int rollDice(int sides);

// Main
int main()
{
    srand(time(0)); // Seed for random number generation
    struct Character player;
    introduction();
    chooseCharacter(&player);
    firstRoom(&player);
    return 0;
}

// Function Implementations
void pressEnterToContinue()
{
    printf("[Press enter to continue]");
    while (getchar() != '\n')
        ; // Wait for enter key
}

void introduction()
{
    printf("Hello brave adventurer, welcome to the Temple of the Fallen King.\n");
    printf("Many before you have attempted to claim this long lost Treasure and uncover the Secrets of the Temple, but all have failed.\n");
    printf("Even so, you have decided to venture in. Good Luck on your Quest.\n");
    pressEnterToContinue();
    printf("-----------------------------------------------------------------------------------\n");
}

void chooseCharacter(struct Character *player)
{
    char choice[10];
    while (1)
    {
        printf("To begin with, are you a Fighter or a Mage? (options: fighter/mage)\n");
        scanf("%s", choice);
        for (int i = 0; choice[i]; i++)
            choice[i] = tolower(choice[i]);
        getchar(); // Consume newline

        if (strcmp(choice, "fighter") == 0 || strcmp(choice, "mage") == 0)
        {
            strcpy(player->type, choice);
            player->health = MAX_HEALTH;
            player->mana = (strcmp(choice, "mage") == 0) ? 15 : 0;
            player->defense = (strcmp(choice, "fighter") == 0) ? FIGHTER_DEFENSE : MAGE_DEFENSE;
            player->attack_bonus = 0;
            break;
        }
        else
        {
            printf("Do not attempt to deceive the Temple, the Temple knows all. Your answer was not valid.\n");
        }
    }
    printf("----------------------------------------------------------------------------------\n");
}

void firstRoom(struct Character *player)
{
    char choice[10];
    int inspected = 0;
    int slimeDefeated = 0;

    printf("You, brave adventurer, have stepped into the temple. The large stone doors have slammed shut behind you and cannot be opened anymore.\n");
    printf("As you look around, you smell the scent of decay and moss. Torches suddenly burst into life around the corners of what seems to be the first chamber, illuminating your surroundings.\n");
    pressEnterToContinue();
    printf("----------------------------------------------------------------------------------\n");

    while (1)
    {
        printf("What would you like to do next?\n");
        printf("1. Fight the slime\n");
        printf("2. Go to the next room (north)\n");
        if (inspected)
        {
            printf("3. Search the room\n");
        }
        printf("4. Look around\n");
        printf("5. Return to the previous room\n");
        scanf("%s", choice);
        for (int i = 0; choice[i]; i++)
            choice[i] = tolower(choice[i]);
        getchar(); // Consume newline

        if (strcmp(choice, "1") == 0 && !slimeDefeated)
        {
            printf("You engage the slime in battle...\n");
            pressEnterToContinue();
            battleSlime(player);
            slimeDefeated = 1;
        }
        else if (strcmp(choice, "2") == 0)
        {
            printf("You move towards the northern exit and enter the next room.\n");
            pressEnterToContinue();
            secondRoom(player);
            break;
        }
        else if (inspected && strcmp(choice, "3") == 0)
        {
            printf("You search the room thoroughly but find nothing of interest besides the moss-covered etchings.\n");
            pressEnterToContinue();
        }
        else if (strcmp(choice, "4") == 0)
        {
            printf("The walls are made of stone and covered in moss. Under the moss, old stone etchings can be seen, depicting what is assumed to be the Fallen King.\n");
            pressEnterToContinue();
            inspected = 1;
        }
        else if (strcmp(choice, "5") == 0)
        {
            printf("There is no way back, the large stone doors have sealed shut.\n");
            pressEnterToContinue();
        }
        else
        {
            printf("Invalid option. Please try again.\n");
        }
    }
    printf("----------------------------------------------------------------------------------\n");
}

void secondRoom(struct Character *player)
{
    char choice[10];
    int skeletonDefeated = 0;
    int chestOpened = 0;
    int foundSecret = 0;

    printf("You enter a larger room with two visible exits. One to the east and one to the west.\n");
    pressEnterToContinue();
    printf("There is a small fountain at the north wall of the room, and in the northeast corner, you see a skeleton warrior guarding a small treasure chest.\n");
    pressEnterToContinue();

    while (1)
    {
        printf("What would you like to do next?\n");
        printf("1. Fight the skeleton warrior\n");
        printf("2. Go to the east exit\n");
        printf("3. Go to the west exit\n");
        if (foundSecret)
        {
            printf("4. Go through the secret passage\n");
        }
        if (!skeletonDefeated)
        {
            printf("5. Search the room\n");
        }
        if (skeletonDefeated)
        {
            printf("5. Open the treasure chest\n");
        }
        printf("6. Look around\n");
        scanf("%s", choice);
        for (int i = 0; choice[i]; i++)
            choice[i] = tolower(choice[i]);
        getchar(); // Consume newline

        if (strcmp(choice, "1") == 0 && !skeletonDefeated)
        {
            printf("You engage the skeleton warrior in battle...");
            pressEnterToContinue();
            battleSkeleton(player);
            if (player->health > 0)
            {
                skeletonDefeated = 1;
                printf("The skeleton drops a key.You can now open the treasure chest.");
                pressEnterToContinue();
            }
        }
        else if (strcmp(choice, "2") == 0)
        {
            printf("You move towards the eastern exit.\n");
            pressEnterToContinue();
            // Function to move to next room to be implemented here
        }
        else if (strcmp(choice, "3") == 0)
        {
            printf("You move towards the western exit.\n");
            pressEnterToContinue();
            // Function to move to next room to be implemented here
        }
        else if (strcmp(choice, "5") == 0 && !skeletonDefeated)
        {
            printf("You search the room and discover a secret passage behind the fountain!");
            foundSecret = 1;
            pressEnterToContinue();
        }
        else if (strcmp(choice, "5") == 0 && skeletonDefeated && !chestOpened)
        {
            printf("You open the treasure chest and find a pair of adventuring glasses (attack +1) and a cape of billowing (looks really cool). You equip them.");
            player->attack_bonus += 1;
            chestOpened = 1;
            pressEnterToContinue();
        }
        else if (foundSecret && strcmp(choice, "4") == 0)
        {
            printf("You move through the secret passage you discovered.\n");
            pressEnterToContinue();
            // Function to move through secret passage to be implemented here
        }
        else if (strcmp(choice, "6") == 0)
        {
            printf("You look around but don't find anything of particular interest.\n");
            pressEnterToContinue();
        }
        else
        {
            printf("Invalid option. Please try again.\n");
        }
    }
    printf("----------------------------------------------------------------------------------\n");
}

int rollDice(int sides)
{
    return (rand() % sides) + 1;
}

void battleSlime(struct Character *player)
{
    int slimeHealth = 10;
    int attackRoll;
    char choice[10];
    while (player->health > 0 && slimeHealth > 0)
    {
        printf("It's your turn! What would you like to do?\n");
        printf("1. Attack\n");
        printf("2. Defend\n");
        scanf("%s", choice);
        for (int i = 0; choice[i]; i++)
            choice[i] = tolower(choice[i]);
        getchar(); // Consume newline

        if (strcmp(choice, "1") == 0)
        {
            printf("You attack the slime!\n");
            attackRoll = rollDice(20);
            if (attackRoll == 1)
            {
                printf("Critical fail! You miss the slime completely.\n");
            }
            else if (attackRoll == 20)
            {
                printf("Critical hit! You deal double damage to the slime.\n");
                slimeHealth -= 20;
            }
            else if (attackRoll >= 10)
            {
                printf("You hit the slime and deal 10 damage!\n");
                slimeHealth -= 10;
            }
            else
            {
                printf("Your attack missed the slime.\n");
            }
        }
        else if (strcmp(choice, "2") == 0)
        {
            printf("You brace yourself for the slime's attack, increasing your defense for this turn.\n");
            player->defense += 5;
        }
        else if (strcmp(choice, "3") == 0)
        {
            printf("You attempt to run away, but the skeleton gets a parting attack!");
            attackRoll = rollDice(20) + 1;
            if (attackRoll >= player->defense)
            {
                printf("The skeleton's attack hits! You take %d damage.", SKELETON_SWORD_DAMAGE);
                player->health -= SKELETON_SWORD_DAMAGE;
            }
            else
            {
                printf("The skeleton's attack missed you.");
            }
            if (player->health <= 0)
            {
                printf("You have been defeated while trying to escape... Game Over.");
                exit(0);
            }
            printf("You successfully run away to the other side of the room.");
            pressEnterToContinue();
            break;
        }
        else
        {
            printf("Invalid choice, you lose your turn!");
        }

        if (slimeHealth <= 0)
        {
            printf("You have defeated the slime!\n");
            pressEnterToContinue();
            break;
        }

        printf("The slime attacks you!\n");
        attackRoll = rollDice(20) - 10;
        if (attackRoll >= player->defense)
        {
            printf("The slime's attack hits! You take %d damage.\n", SLIME_ATTACK_DAMAGE);
            player->health -= SLIME_ATTACK_DAMAGE;
        }
        else
        {
            printf("The slime's attack missed you.\n");
        }

        if (player->health <= 0)
        {
            printf("You have been defeated by the slime... Game Over.\n");
            exit(0);
        }

        // Reset defense if player defended
        if (strcmp(choice, "defend") == 0)
        {
            player->defense -= 5;
        }

        pressEnterToContinue();
    }
}

void battleSkeleton(struct Character *player)
{
    int skeletonHealth = 20;
    int attackRoll;
    char choice[10];
    while (player->health > 0 && skeletonHealth > 0)
    {
        printf("It's your turn! What would you like to do?\n");
        printf("1. Attack\n");
        printf("2. Defend\n");
        printf("3. Run away\n");
        scanf("%s", choice);
        for (int i = 0; choice[i]; i++)
            choice[i] = tolower(choice[i]);
        getchar(); // Consume newline

        if (strcmp(choice, "1") == 0)
        {
            printf("You attack the skeleton!\n");
            attackRoll = rollDice(20);
            if (attackRoll == 1)
            {
                printf("Critical fail! You miss the skeleton completely.\n");
            }
            else if (attackRoll == 20)
            {
                printf("Critical hit! You deal double damage to the skeleton.\n");
                skeletonHealth -= 20;
            }
            else if (attackRoll + player->attack_bonus >= 10)
            {
                printf("You hit the skeleton and deal 10 damage!\n");
                skeletonHealth -= 10;
            }
            else
            {
                printf("Your attack missed the skeleton.\n");
            }
        }
        else if (strcmp(choice, "2") == 0)
        {
            printf("You brace yourself for the skeleton's attack, increasing your defense for this turn.\n");
            player->defense += 5;
        }
        else
        {
            printf("Invalid choice, you lose your turn!\n");
        }

        if (skeletonHealth <= 0)
        {
            printf("You have defeated the skeleton! It drops a key.\n");
            pressEnterToContinue();
            break;
        }

        printf("The skeleton attacks you with its sword!\n");
        attackRoll = rollDice(20) + 1;
        if (attackRoll >= player->defense)
        {
            printf("The skeleton's sword hits! You take %d damage.\n", SKELETON_SWORD_DAMAGE);
            player->health -= SKELETON_SWORD_DAMAGE;
        }
        else
        {
            printf("The skeleton's attack missed you.\n");
        }

        if (player->health <= 0)
        {
            printf("You have been defeated by the skeleton... Game Over.\n");
            exit(0);
        }

        // Reset defense if player defended
        if (strcmp(choice, "defend") == 0)
        {
            player->defense -= 5;
        }

        pressEnterToContinue();
    }
}
