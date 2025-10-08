#include "gofish.h"


int main(int args, char* argv[]) 
{
  srand(time(NULL)); 
  int playing = 1; 

  while (playing) {
    printf("\nShuffling deck...\n\n"); 
    shuffle();
    
    reset_player(&user); 
    reset_player(&computer); 

    deal_player_cards(&user); 
    deal_player_cards(&computer); 

    int current_player = 1; 

    while ((!game_over(&user)) && (!game_over(&computer))) {
      struct player* currentp; 
      struct player* otherp; 

      if (current_player == 1) {
        currentp = &user;
        otherp = &computer;  
      } else { 
        currentp = &computer;
        otherp = &user; 
      }

      printf("Player 1's Hand - "); 
      print_hand(&user); 
      printf("Player 1's Book - "); 
      print_books(&user); 
      printf("Player 2's Book - "); 
      print_books(&computer); 

      char ask_rank;

      if (current_player == 1) { 
        ask_rank = user_play(&user); 
      } else { 
          printf("Player 2's turn, enter a Rank: "); 
          ask_rank = computer_play(&computer); 

          if (ask_rank == 'T') {
            int temp = 10;
            printf("%d\n", temp);
          } else {
            printf("%c\n", ask_rank);
          }
      }

      char transfered_suit[4] = {'\0', '\0', '\0', '\0'};
      int transfered_card = search_suit(otherp, transfered_suit, ask_rank);
      transfered_card =  transfer_cards(otherp, currentp, ask_rank); 

      if (transfered_card > 0) {
        if (ask_rank == 'T') {
          if (current_player == 1) {
            printf(" - Player %d has ", 2);

            for (int i = 0; i < 4; i++) {
              if (transfered_suit[i] != '\0') {
                printf("10%c ", transfered_suit[i]); 
              }
            }

            printf("\n");
          } else {
            printf(" - Player %d has ", 1);

            for (int i = 0; i < 4; i++) {
              if (transfered_suit[i] != '\0') {
                printf("10%c ", transfered_suit[i]); 
              }
            }

            printf("\n");
        }
        } else {
          if (current_player == 1) {
            printf(" - Player %d has ", 2);

              for (int i = 0; i < 4; i++) {
                if (transfered_suit[i] != '\0') {
                  printf("%c%c ", ask_rank, transfered_suit[i]); 
                }
              }

              printf("\n");
          } else {
            printf(" - Player %d has ", 1);

              for (int i = 0; i < 4; i++) {
                if (transfered_suit[i] != '\0') {
                  printf("%c%c ", ask_rank, transfered_suit[i]); 
                }
              }

              printf("\n");
          }
        }   

        char current_book = check_add_book(currentp); 

        if (current_book != 0) {
          char suits[] = {'C', 'D', 'H', 'S'};
          printf(" - Player %d has ", current_player);

          for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
              if ((suits[i] == transfered_suit[j]) && (transfered_suit[j] != '\0')) {
                suits[i] = '\0';
              }
            }
          }

          for (int i = 0; i < 4; i++) {
            if (suits[i] != '\0') {
              printf("%c%c ", ask_rank, suits[i]);
            }
          }
          
          printf("\n");

          if (current_book == 'T') {
            printf(" - Player %d books 10\n", current_player);
          } else {
            printf(" - Player %d books %c\n", current_player, current_book);
          }

          printf(" - Player %d gets another turn\n\n", current_player);
        } else {
          if (current_player == 1) {
            current_player = 2;
          } else {
            current_player = 1;
          }

          printf(" - Player %d's turn\n\n", current_player);
        }

      } else {
        if (ask_rank == 'T') {
          if (current_player == 1) {
            printf(" - Player 2 has no 10's\n"); 
          } else {
            printf(" - Player 1 has no 10's\n"); 
          }
        } else { 
            if (current_player == 1) {
              printf(" - Player 2 has no %c's\n",  ask_rank); 
            } else {
              printf(" - Player 1 has no %c's\n", ask_rank); 
            }
        }
    
        if (deck_size() > 0) {
          struct card* new_card = next_card(); 
          add_card(currentp, new_card); 
            
          if (current_player == 1) {
            if (new_card->rank[0] == 'T') {
              printf(" - Go Fish, Player %d draws 10%c\n",current_player, new_card->suit);
            } else {
              printf(" - Go Fish, Player 1 draws %c%c\n", new_card->rank[0], new_card->suit);
            }
          } else {
            if (new_card->rank[0] == ask_rank) {
              if (new_card->rank[0] == 'T') {
                printf(" - Go Fish, Player 2 draws 10%c\n", new_card->suit);
              } else {
                printf(" - Go Fish, Player 2 draws %c%c\n", new_card->rank[0], new_card->suit);
              }
            } else {
              printf(" - Go Fish, Player 2 draws a card\n"); 
            }
          }

          char current_book = check_add_book(currentp);

          if (current_book != 0) {
            char temp_suit[] = {'\0', '\0', '\0', '\0'};
            int same_cards = search_suit(currentp, temp_suit, new_card->rank[0]);

            printf(" - Player %d has ", current_player);

            for (int i = 0; i < same_cards; i++) {
              if (temp_suit[i] != '\0') {
                printf("%c%c ", new_card->rank[0], temp_suit[i]);
              }
            }
              
            printf("\n");

            if (current_book == 'T') {
              printf(" - Player %d books 10\n", current_player);
            } else {
              printf(" - Player %d books %c\n", current_player, current_book);
            }

            printf(" - Player %d gets another turn\n\n", current_player); 
          } else if (new_card->rank[0] == ask_rank) {
            printf(" - Player %d gets another turn\n\n", current_player); 
          } else { 
            if (current_player == 1) { 
              current_player = 2; 
            } else { 
              current_player = 1; 
            }
            
            printf(" - Player %d's turn\n\n", current_player); 
          }
        } else { 
          printf(" - Deck is empty\n"); 

          if (current_player == 1) { 
            current_player = 2; 
          } else { 
            current_player = 1; 
          }

          printf(" - Player %d's turn\n\n", current_player);
          }
      }
 
    }

    if (game_over(&user)) { 
      printf("Player 1 Wins! %ld-%ld",user.hand_size, computer.hand_size); 
    } else if (game_over(&computer)) { 
      printf("Player 2 Wins! %ld-%ld", computer.hand_size,user.hand_size);
    } else { 
      printf("Game is a draw!\n"); 
    }

    char user_in; 

    printf("\nDo you want to play again [Y/N]: "); 
    scanf("%c", &user_in); 

    if (toupper(user_in) != 'Y') {
      playing = 0; 
      printf("Exiting.\n"); 
    }
  }

  return 0; 
}

void print_hand(struct player* target) { 
  if (target-> card_list == NULL) {
    printf("\n"); 
    return; 
  }
  struct hand* current = target-> card_list; 
  while (current!= NULL) { 
    if (current -> top.rank[0] == 'T') {
      printf("10%c ", current-> top.suit); 
    } else {
      printf("%c%c ", current->top.rank[0], current->top.suit); 
    }
      current = current-> next; 
  }
  printf("\n"); 
}

void print_books(struct player* target) { 
  for (int i = 0; i<7; i++) { 
    if (target-> book[i] != '\0') {
      if (target->book[i] == 'T') {
        printf("%d ", 10);
      } else {
        printf("%c ",target->book[i]); 
      }
    }
  }
  printf("\n"); 
}

int search_suit(struct player* target, char suits[], char rank) {
  struct hand* curr = target->card_list;
  int idx = 0;

  while (curr != NULL) {
    if (curr->top.rank[0] == rank) {
      suits[idx] = curr->top.suit;
      idx += 1;
    }

    curr = curr->next;
  }

  return idx;
}
