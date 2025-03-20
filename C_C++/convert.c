#include <stdio.h>
#include <stdlib.h>
#include "dec_bin.h"
#include "bin_dec.h"

// Funzione principale
int main(){

    int decisione = 1;

    while(decisione == 1){
        printf("\nType '1' to 10->2 or type '2' to 2->10:     |----------------> ");
        scanf("%d", &decisione);
        
        if (decisione == 1){
            dec_bin();
        }
        else{
            // La conversione da binario a decimale non è implementata
        }
        printf("\n\nType 1 to continue");
        printf(" or type 0 to quit: ");
        printf("     |---------------->  ");
        scanf("%d", &decisione);

    }
    return 0;
}
