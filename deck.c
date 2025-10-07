#include "deck.h"

/*
 * Variable: deck_instance
 * -----------------------
 *  
 * Go Fish uses a single deck
 */
struct deck deck_instance;

int shuffle(){
    char suits[] = {'C', 'D', 'H', 'S'}; 
    char ranks[] = {'2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K', 'A'}; 

    int count= 0; 
    for (int i = 0; i <4; i++){ 
        for (int j =0; j < 13; j++){
            deck_instance.list[count].suit = suits[i]; 
            deck_instance.list[count].rank[0] = ranks[j]; 
            deck_instance.list[count].rank[1] = '\0'; 
            count ++; 
        }
    }

    for (int i = 0; i<52; i++) { 
        int r = i + (rand() % (52-i)); 
        struct card temp = deck_instance.list[i]; 
        deck_instance.list[i] = deck_instance.list[r]; 
        deck_instance.list[r] = temp; 
    }
    deck_instance.top_card = 0; 
    return 0; 
}

int deal_player_cards(struct player* target){ 
    if ((52 - deck_instance.top_card) < 7 ){
        return -1; 
    }
    target->hand_size = 0; 
    target->card_list = NULL; 
    for(int i = 0; i<7; i++){ 
        struct hand* node = (struct hand*) malloc(sizeof(struct hand)); 

        node-> top = deck_instance.list[deck_instance.top_card]; 
        deck_instance.top_card ++; 
        node-> next = target->card_list; 
        target-> card_list = node;  
        target-> hand_size ++; 
    }
    return 0; 
}

struct card* next_card(){
    if(deck_instance.top_card >=52){
        return NULL; 
    }
    struct card* top_card = &deck_instance.list[deck_instance.top_card]; 
    deck_instance.top_card ++; 
    return top_card; 

}

size_t deck_size(){
    int deck_count = 52 - deck_instance.top_card;  
    return deck_count; 
}