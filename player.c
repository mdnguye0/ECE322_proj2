#include "player.h"

/*
 * Instance Variables: user, computer   
 * ----------------------------------
 *  
 *  We only support 2 users: a human and a computer
 */
struct player user;
struct player computer;

int add_card(struct player* target, struct card* new_card) {
  if (target == NULL || new_card == NULL) {
    return 1;
  }

  struct hand* temp = (struct hand*)malloc(sizeof(struct hand));

  temp->top = *new_card;
  temp->next = target->card_list;
  target->card_list = temp;
  target->hand_size++;

  return 0;
}

int remove_card(struct player* target, struct card* old_card) {
  if (target == NULL || old_card == NULL) {
    return 1;
  }

  struct hand* curr = target->card_list;
  struct hand* prev = NULL;

  while (curr != NULL) {
    if ((curr->top.suit == old_card->suit) && (curr->top.rank == old_card->rank)) {
      if (prev == NULL) {
        target->card_list = curr->next;
        free(curr);
      }
      else {
        prev->next = curr->next;
        free(curr);
      }

      target->hand_size--;
      
      return 0;
    }

    prev = curr;
    curr = curr->next;
  }

  return 1;
}

char check_add_book(struct player* target) {
  if (target == NULL) {
    return 0;
  }

  struct hand* curr = target->card_list;

  while ((curr != NULL)) {
    struct hand* curr1 = target->card_list;
    struct card* remove[4] = {NULL};
    int count = 0;
    int idx = 0;

    while ((curr1 != NULL)) {
      if (curr->top.rank == curr1->top.rank) {
        count += 1;
        remove[idx] = &(curr1->top);
        idx += 1;
      }

      curr1 = curr1->next;
    }

    if (count == 4) {
      char temp;
      for (int i = 0; i < 7; i++) {
        if (target->book[i] == '\0') {
          target->book[i] = curr->top.rank[0];
          temp = curr->top.rank[0];
          break;
        }
      }

      for (int i = 0; i < 4; i++) {
        remove_card(target, remove[i]);
      }

      return temp;
    }

    curr = curr->next;
  }

  return 0;
}

int search(struct player* target, char rank) {
  if (target == NULL) {
    return 0;
  }

  struct hand* curr = target->card_list;

  while (curr != NULL) {
    if (curr->top.rank[0] == rank) {
      return 1;
    }

    curr = curr->next;
  }

  return 0;
}

int transfer_cards(struct player* src, struct player* dest, char rank) {
  if (src == NULL || dest == NULL) {
    return -1;
  }

  struct hand* curr = src->card_list;
  struct card* remove[4] = {NULL};
  struct card add[4];
  int idx = 0;

  while (curr != NULL) {
    if (curr->top.rank[0] == rank) {
      remove[idx] = &(curr->top);
      add[idx] = curr->top;
      idx += 1;
    }

    curr = curr->next;
  }

  if (idx != 0) {
    for (int i = 0; i < idx; i++) {
      add_card(dest, &add[i]);
      remove_card(src, remove[i]);
    } 

    return idx;
  }
  else {
    return 0;
  }
}

int game_over(struct player* target) {
    if (target->book[6] != '\0') {
        return 1;
    }

    return 0;
}

int reset_player(struct player* target) {
    if (target == NULL) {
        return -1;
    }

    struct hand* curr = target->card_list;
    struct hand* temp = NULL;

    while (curr != NULL) {
        temp = curr->next;
        free(curr);
        curr = temp;
    }

    target->card_list = NULL;
    target->hand_size = 0;
    
    for (int i = 0; i < 7; i++) {
        target->book[i] = '\0';
    }

    return 0;
}

void initialize(struct player* target) {
    target->card_list = NULL;
    target->hand_size = 0;
    
    for (int i = 0; i < 7; i++) {
        target->book[i] = '\0';
    }
}

char computer_play(struct player* target) {
    if (target->hand_size == 0 || target->card_list == NULL){ 
        return 1; 
    }
    int r = rand() % target->hand_size; 
    struct hand* curr = target->card_list; 
    for (int i = 0; i<r; i++){ 
        curr = curr->next; 
    }
    return curr->top.rank[0]; 
}

char user_play(struct player* target){
    char input[10]; 
    char rank_opt; 

    while(1){ 
        printf("Player 1's turn, enter a Rank: "); 
        scanf("%s", input); 
        

    }
}