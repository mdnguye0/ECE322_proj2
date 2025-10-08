#ifndef GOFISH_H
#define GOFISH_H

/*
   Define any prototype functions
   for gofish.h here.
*/

#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 
#include <ctype.h> 

#include "deck.h"
#include "card.h"
#include "player.h" 

void print_hand(struct player* target); 
void print_books(struct player* target); 
#endif
