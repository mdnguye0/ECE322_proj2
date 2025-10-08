
#include "gofish.h"

int main(int args, char* argv[]) 
{
  srand(time(NULL)); 
  int playing =1; 
  while(playing){
    printf("Shuffling deck...\n\n"); 
    shuffle(); 
    
    reset_player(&user); 
    reset_player(&computer); 

    deal_player_cards(&user); 
    deal_player_cards(&computer); 
    int current_player = 1; 
    while (!game_over(&user) && !game_over(&computer)){
      struct player* currentp; 
      struct player* otherp; 
      if(current_player == 1){
        currentp = &user;
        otherp = &computer;  
      }
      else { 
        currentp = &computer;
        otherp = &user; 
      }

      printf("Player 1's Hand -"); 
      print_hand(&user); 
      printf("Player 1's Book -"); 
      print_books(&user); 
      printf("Player 2's Book -"); 
      print_books(&computer); 
      printf("\n"); 

      char ask_rank; 
      if(current_player == 1){ 
        ask_rank = user_play(&user); 
      }
      else{ 
        printf("Player 2's turn, enter a Rank:"); 
        ask_rank = computer_play(&computer); 
        printf("%c\n", ask_rank); 
      }
      int transfered_card =  transfer_cards(otherp, currentp, ask_rank); 
      if (transfered_card > 0){
        if (ask_rank == 'T'){
          if (current_player == 1){
            printf(" -Player %d has %d 10's \n", 2, transfered_card); 
      } 
          else {
            printf(" -Player %d has %d 10's \n", 1, transfered_card);
        }
      }else{
        if (current_player == 1){
          printf(" -Player %d has %d %c's\n", 2, transfered_card, ask_rank); 
      } 
        else {
          printf(" -Player %d has %d %c's \n", 1, transfered_card, ask_rank);
        }
      }  
          printf(" -Player %d gets another turn\n", current_player); 
      } else {
          if (ask_rank == 'T'){
            if(current_player == 1){
            printf(" -Player 2 has no 10's\n"); 
          }
          else{
            printf(" -Player 1 has no 10's\n"); 
          }
          } else{ 
            if(current_player == 1){
            printf(" -Player 2 has no %c's\n",  ask_rank); 
          }
          else{
            printf(" -Player 1 has no %c's\n", ask_rank); 
          }
        }
    
    
          if (deck_size() > 0){
            struct card* new_card = next_card(); 
            add_card(currentp, new_card); 
            printf(" -Go Fish, Player %d draws %c%c\n",current_player, new_card->rank[0], new_card->suit); 

            if (new_card->rank[0] == ask_rank){
              printf(" -Player %d gets another turn\n", current_player); 
            }else{ 
              if(current_player == 1){ 
                current_player = 2; 
              }
              else{ 
                current_player = 1; 
              }
              printf(" -Player %d's turn\n", current_player); 
            }
          }else{ 
            printf(" -Deck is empty\n"); 
            if(current_player == 1){ 
              current_player = 2; 
            }
            else{ 
              current_player = 1; 
            }
            printf(" -Player %d's turn\n", current_player);
          }
      }
      char current_book; 
      while((current_book = check_add_book(currentp))){
        printf(" -Player %d's books -%c\n", current_player, current_book); 
        printf(" -Player %d gets another turn\n", current_player); 
      }
      printf("\n"); 
    }
    if (game_over(&user)){ 
      printf("Player 1 Wins! %ld-%ld",user.hand_size, computer.hand_size); 
    }else if (game_over(&computer)){ 
      printf("Player 2 Wins! %ld-%ld", computer.hand_size,user.hand_size);
    }else{ 
      printf("Game is a draw!\n"); 
    }

    char user_in; 
    printf("\nDo you want to play again [Y/N]: "); 
    scanf("%c", &user_in); 
    if(toupper(user_in) != 'Y'){
      playing = 0; 
      printf("Exiting.\n"); 
    }
  }
  return 0; 
}

void print_hand(struct player* target){ 
  if (target-> card_list == NULL){
    printf("\n"); 
    return; 
  }
  struct hand* current = target-> card_list; 
  while(current!= NULL){ 
    if (current -> top.rank[0] == 'T'){
      printf("10%c ", current-> top.suit); 
    }else{
      printf("%c%c ", current->top.rank[0], current->top.suit ); 
    }
      current = current-> next; 
  }
  printf("\n"); 
}

void print_books(struct player* target){ 
  for(int i = 0; i<7; i++){ 
    if(target-> book[i] != '\0' && target->book[i] != '-'){
      printf("%c ",target->book[i]); 
    }
  }
  printf("\n"); 
}