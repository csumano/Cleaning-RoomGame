#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _room{
    int state;
    int id;
    struct _room * north;
    struct _room * south;
    struct _room * east;
    struct _room * west;
    struct Creature* creatureArray[10];

} room;

typedef struct Creature{
    int type;
    int id;
    room * location;

} Creature;

int respect = 40;
room* rooms;
Creature* crs;
Creature* pc;

//void dirty(Creature *c);

//==============================================================================

void removeCeature(Creature* c, room* r){
    for (int i = 0; i < 10; i++) {
        if (r && r->creatureArray[i] ==  c) {
            r->creatureArray[i] = NULL;
            c->location = NULL;
            return;
        }
    }
}
void drill(Creature *c){
    printf("\n%d drills a hole in the ceiling and leaves through the roof.\n",  c->id);
    for (int i = 0; i < 10; i++) {
        if (c->location->creatureArray[i] != NULL && c->location->creatureArray[i] != c && c->location->creatureArray[i]->type != 0) {
            if (c->location->creatureArray[i]->type == 2) {
                respect -= 1;
                printf("%d grumbles. Respect is now ", c->location->creatureArray[i]->id);
                printf("%d \n", respect);
            } else if(c->location->creatureArray[i]->type == 1){
                respect -= 1;
                printf("%d growls. Respect is now ", c->location->creatureArray[i]->id);
                printf("%d \n", respect);
            }
        }
    }
    removeCeature(c, c->location);
}

void addCreaturesToRoom(Creature* c, room* r){
    for (int i = 0; i < 10; i++) {
        if (r && r->creatureArray[i] == NULL) {
            r->creatureArray[i] = c;
            c->location = r;
            return;
        }
    }
}

void look(){
    printf("Room %d, ", pc->location->id);

    if (pc->location->state == 0) {
        printf("clean, ");
    } else if (pc->location->state == 1) {
        printf("half-dirty, ");
    } else {
        printf("dirty, ");
    }

    if (pc->location->north != 0) {
        printf("neighbors %d north, ", pc->location->north->id);
    }
    if (pc->location->south != 0) {
        printf("neighbors %d south, ", pc->location->south->id);
    }
    if (pc->location->east != 0) {
        printf("neighbors %d east, ", pc->location->east->id);
    }
    if (pc->location->west != 0) {
        printf("neighbors %d west, ", pc->location->west->id);
    }
    if (pc->location->west == NULL && pc->location->north == NULL && pc->location->south == NULL && pc->location->east == NULL) {
        printf("no nieghbors, ");
    }
    printf("contains :\n");

    for (int i = 0; i < 10; i++) {
        if (pc->location->creatureArray[i] != NULL) {
            if (pc->location->creatureArray[i]->type == 0) {
                printf("PC\n");
            }else if(pc->location->creatureArray[i]->type == 1){
                printf("Animal %d\n", pc->location->creatureArray[i]->id);
            } else{
                printf("Human %d\n", pc->location->creatureArray[i]->id);
            }
        }
    }
}
int emptyspacein(room *r){
    int count = 0;
    for (int i = 0; i < 10; i++) {
        if (r->creatureArray[i] != NULL) {
            count++;
        }
        if (count == 10) {
            return 0;
        }
        return 1;

    }
}
int moveCreature(Creature *c, room *r){
    if (r == NULL) {
        printf("No neighbor in that direction\n");
        return 0;
    }
    if (!emptyspacein(r)) {
        printf("No space in that room\n");
        if (c->type == 2) {
            respect -= 1;
            printf("%d grumbles. Respect is now %d", c->id, respect);
        }else if(c->type == 1){
            respect -= 1;
            printf("%d growls. Respect is now %d", c->id, respect);
        }
        return 0;
    }
    if (c->type == 0) {
        if (c->location->north != NULL && c->location->north == r) {
            printf("You move towards north\n");
        }
        if (c->location->south != NULL && c->location->south == r) {
            printf("You move towards south\n");
        }
        if (c->location->east != NULL && c->location->east == r) {
            printf("You move towards east\n");
        }
        if (c->location->west != NULL && c->location->west == r) {
            printf("You move towards west\n");
        }

    }

    if(c->type == 1){
        if (c->location->north != NULL && c->location->state == 2) {
            c->location->state == 1;
        }
        if (c->location->south != NULL && c->location->state == 2) {
            c->location->state == 1;
        }
        if (c->location->east != NULL && c->location->state == 2) {
            c->location->state == 1;
        }
        if (c->location->west != NULL && c->location->state == 2) {
            c->location->state == 1;
        }

    } else if(c->type == 2){
        if (c->location->north != NULL && c->location->state == 0) {
            c->location->state == 1;
        }
        if (c->location->south != NULL && c->location->state == 0) {
            c->location->state == 1;
        }
        if (c->location->east != NULL && c->location->state == 0) {
            c->location->state == 1;
        }
        if (c->location->west != NULL && c->location->state == 0) {
            c->location->state == 1;
        }
    }

    removeCeature(c, c->location);
    addCreaturesToRoom(c, r);
    return 1;
}

void clean(Creature *c){
    if(c->type == 2){
        printf("%d grumbles a lot. Respect is now ", c->id);
        respect -= 3;
        printf("%d\n", respect);
    } else if(c->type == 1){
        printf("%d licks your face a lot. Respect is now ", c->id);
        respect += 3;
        printf("%d\n", respect);
    }

    if(pc->location->state != 0){
        for (int i = 0; i < 10; i++) {
            if (pc->location->creatureArray[i] != NULL) {
                if (pc->location->creatureArray[i]->type == 2  && c != pc->location->creatureArray[i]) {
                    printf("%d grumbles. Respect is now ", pc->location->creatureArray[i]->id);
                    respect -= 1;
                    printf("%d\n", respect);
                } else if(pc->location->creatureArray[i]->type  == 1  && c != pc->location->creatureArray[i]){
                    printf("%d animal licks your face. Respect is now ", pc->location->creatureArray[i]->id);
                    respect += 1;
                    printf("%d\n", respect);
                }
            }
        }
    }

    if (c->location->state == 1) {
        c->location->state = 0;
        for (int i = 0; i < 10; i++) {
            if (c->location->creatureArray[i] != NULL) {
                if (c->location->creatureArray[i]->type == 2) {
                    if (c->location->east != NULL) {
                        if (c->location->east->state == 0) {
                            c->location->east->state = 1;
                        }
                        printf("%d leaves towards the east\n", c->location->creatureArray[i]->id);
                        moveCreature(c->location->creatureArray[i], c->location->east);
                    }
                    else if(c->location->north != NULL){
                        if (c->location->north->state == 0) {
                            c->location->north->state = 1;
                        }
                        printf("%d leaves towards the north n", c->location->creatureArray[i]->id);
                        moveCreature(c->location->creatureArray[i], c->location->north);
                    }
                    else if(c->location->south != NULL){
                        if (c->location->south->state == 0) {
                            c->location->south->state = 1;
                        }
                        printf("%d leaves towards the south\n", c->location->creatureArray[i]->id);
                        moveCreature(c->location->creatureArray[i], c->location->south);
                    }
                    else if(c->location->west != NULL){
                        if (c->location->west->state == 0) {
                            c->location->west->state = 1;
                        }
                        printf("%d leaves towards the west\n", c->location->creatureArray[i]->id);
                        moveCreature(c->location->creatureArray[i], c->location->west);
                    }
                    else{
                        drill(c->location->creatureArray[i]);
                    }

                }
            }
        }
    }
 else if(c->location->state == 2){
        c->location->state = 1;
    }
    else{
        printf("room is already clean\n");
    }
}

void dirty(Creature *c){

    if (c->type == 2) {
        printf("%d smiles at you a lot. Respect is now ", c->id);
        respect += 3;
        printf("%d\n", respect);
    } else if(c->type == 1){
        printf("%d growls at you a lot. Respect is now ", c->id);
        respect -= 3;
        printf("%d\n", respect);
    }

    for (int i = 0; i < 10; i++) {
        if (pc->location->creatureArray[i] != NULL) {
            if (pc->location->creatureArray[i]->type == 2 && c != pc->location->creatureArray[i]) {
                printf("%d smiles. Respect is now ", pc->location->creatureArray[i]->id);
                respect += 1;
                printf("%d\n", respect);
            } else if(pc->location->creatureArray[i]->type  == 1 && c != pc->location->creatureArray[i]){
                printf("%d growls. Respect is now ", pc->location->creatureArray[i]->id);
                respect -= 1;
                printf("%d\n", respect);
            }
        }
    }

    if (c->location->state == 1) {
        c->location->state = 2;
        for (int i = 0; i < 10; i++) {
            if (c->location->creatureArray[i] != NULL) {
                if (c->location->creatureArray[i]->type == 1) {
                    if (c->location->east != NULL) {
                        if (c->location->east->state == 2) {
                            c->location->east->state = 1;
                        }
                        moveCreature(c->location->creatureArray[i], c->location->east);
                        printf("%d leaves towards the east \n", c->location->creatureArray[i]->id);
                    }
                    else if(c->location->north != NULL){
                        if (c->location->state == 2) {
                            c->location->north->state = 1;
                        }
                        moveCreature(c->location->creatureArray[i], c->location->north);
                        printf("%d leaves towards the north \n", c->location->creatureArray[i]->id);
                    }
                    else if(c->location->south != NULL){
                        if (c->location->south->state == 2) {
                            c->location->south->state = 1;
                        }
                        moveCreature(c->location->creatureArray[i], c->location->south);
                        printf("%d leaves towards the south \n", c->location->creatureArray[i]->id);
                    }
                    else if(c->location->west != NULL){
                        if (c->location->west->state == 2) {
                            c->location->west->state = 1;
                        }
                        moveCreature(c->location->creatureArray[i], c->location->west);
                        printf("%d leaves towards the west \n", c->location->creatureArray[i]->id);
                    }
                    else{
                        drill(c->location->creatureArray[i]);
                    }

                }
            }
        }
    }else if(c->location->state == 0){
        c->location->state = 1;
    }else{
        printf("room is already dirty\n");
    }
}

int main(){

    int n = 0;
    scanf("%d", &n);

    room* rooms = (room*)malloc(sizeof(room)*n);
    int north, south, east, west;

    for (int i = 0; i < n; i++) {
        rooms[i].id = i;
        scanf("%d %d %d %d %d", &rooms[i].state, &north, &south, &east, &west);
        for (int j = 0; j < 10; j++) {
            rooms[i].creatureArray[j] = NULL;
        }
        if (north == -1) {
            rooms[i].north = NULL;
        } else {
            rooms[i].north = &rooms[north];
        }
        if (south == -1) {
            rooms[i].south = NULL;
        } else {
            rooms[i].south = &rooms[south];
        }
        if(east == -1){
            rooms[i].east = NULL;
        } else {
            rooms[i].east = &rooms[east];
        }
        if(west == -1){
            rooms[i].west = NULL;
        } else {
            rooms[i].west = &rooms[west];
        }

    }

    int c = 0;
    scanf("%d", &c);
    int location;
    Creature* creatureArray = (struct Creature *)malloc(sizeof(struct Creature)*c); //create an array of creatures
    for (int i = 0; i < c; i++) {
        creatureArray[i].id = i;
        scanf("%d %d", &creatureArray[i].type, &location);
        if (creatureArray[i].type == 0) {
            pc = &creatureArray[i];
        }
        addCreaturesToRoom(&creatureArray[i], &rooms[location]);
    }

    char command[20] = "";

    while (strcmp(command, "exit") != 0 && respect <= 80 && respect > 0) {
        scanf("%s", command);
        printf("\n");
        if (strcmp(command, "look") == 0) {
            look();
        }
        if (strcmp(command, "clean") == 0) {
            clean(pc);
        }
        if (strcmp(command, "dirty") == 0) {
            dirty(pc);
        }
        if (strcmp(command, "east") == 0) {
            moveCreature(pc, pc->location->east);

        }
        if (strcmp(command, "north") == 0) {
            moveCreature(pc, pc->location->north);

        }
        if (strcmp(command, "south") == 0) {
            moveCreature(pc, pc->location->south);

        }
        if (strcmp(command, "west") == 0) {
            moveCreature(pc, pc->location->west);

        }
        if (strcmp(command, "help") == 0) {
            printf("Commands:\n");
            printf(" |--- 'look' : shows the contents of the room you are currently in \n");
            printf(" |---'clean' or 'dirty' : clean or dirties the room you are currently in \n");
            printf(" |--- (creature #) before any of the commands besides look does that action for the creature \n");
        }
        if (command[2] == 'c') {
            for (int i = 0; i < 10; i++) {
                if(pc->location->creatureArray[i] != NULL && (int)command[0] - (int)'0' == pc->location->creatureArray[i]->id){
                    clean(pc->location->creatureArray[i]);
                }
            }
        }
        if (command[2] == 'd') {
            for (int i = 0; i < 10; i++) {
                if(pc->location->creatureArray[i] != NULL && (int)command[0] - (int)'0' == pc->location->creatureArray[i]->id){
                    dirty(pc->location->creatureArray[i]);
                }
            }
        }
        if(command[2] == 'e'){
            for (int i = 0; i < 10; i++) {
                if(pc->location->creatureArray[i] != NULL && (int)command[0] - (int)'0' == pc->location->creatureArray[i]->id){
                    moveCreature(pc->location->creatureArray[i], pc->location->east);
                }
            }
        }
        if(command[2] == 'w'){
            for (int i = 0; i < 10; i++) {
                if(pc->location->creatureArray[i] != NULL && (int)command[0] - (int)'0' == pc->location->creatureArray[i]->id){
                    moveCreature(pc->location->creatureArray[i], pc->location->west);
                }
            }
        }
        if(command[2] == 'n'){
            for (int i = 0; i < 10; i++) {
                if(pc->location->creatureArray[i] != NULL && (int)command[0] - (int)'0' == pc->location->creatureArray[i]->id){
                    moveCreature(pc->location->creatureArray[i], pc->location->north);
                }
            }
        }
        if(command[2] == 's'){
            for (int i = 0; i < 10; i++) {
                if(pc->location->creatureArray[i] != NULL && (int)command[0] - (int)'0' == pc->location->creatureArray[i]->id){
                    moveCreature(pc->location->creatureArray[i], pc->location->south);
                }
            }
        }
        if (command[3] == 'c') {
            for (int i = 0; i < 10; i++) {
                if(pc->location->creatureArray[i] != NULL && ((int)command[0] - (int)'0')*10 + (int)command[1] - (int)'0' == pc->location->creatureArray[i]->id){
                    clean(pc->location->creatureArray[i]);
                }
            }
        }
        if (command[3] == 'd') {
            for (int i = 0; i < 10; i++) {
                if(pc->location->creatureArray[i] != NULL && ((int)command[0] - (int)'0')*10 + (int)command[1] - (int)'0' == pc->location->creatureArray[i]->id){
                    dirty(pc->location->creatureArray[i]);
                }
            }
        }
        if(command[3] == 'e'){
            for (int i = 0; i < 10; i++) {
                if(pc->location->creatureArray[i] != NULL && ((int)command[0] - (int)'0')*10 + (int)command[1] - (int)'0'  == pc->location->creatureArray[i]->id){
                    moveCreature(pc->location->creatureArray[i], pc->location->east);
                }
            }
        }
        if(command[3] == 'w'){
            for (int i = 0; i < 10; i++) {
                if(pc->location->creatureArray[i] != NULL && ((int)command[0] - (int)'0')*10 + (int)command[1] - (int)'0' == pc->location->creatureArray[i]->id){
                    moveCreature(pc->location->creatureArray[i], pc->location->west);
                }
            }
        }
        if(command[3] == 'n'){
            for (int i = 0; i < 10; i++) {
                if(pc->location->creatureArray[i] != NULL && ((int)command[0] - (int)'0')*10 + (int)command[1] - (int)'0' == pc->location->creatureArray[i]->id){
                    moveCreature(pc->location->creatureArray[i], pc->location->north);
                }
            }
        }
        if(command[3] == 's'){
            for (int i = 0; i < 10; i++) {
                if(pc->location->creatureArray[i] != NULL && (int)command[0] - (int)'0' == pc->location->creatureArray[i]->id){
                    moveCreature(pc->location->creatureArray[i], pc->location->south);
                }
            }
        }
    }

    if (respect > 80) {
        printf("You win! Everyone praises you!\n");
    }

    if (respect <= 0){
        printf("You lose! Everyone disgraces you!\n");
    }
    printf("Goodbye!\n");

    free(rooms);
    free(creatureArray);
}
