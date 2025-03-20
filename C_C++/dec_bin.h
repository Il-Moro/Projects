#include <stdio.h>
#include <stdlib.h>



// definizione funzioni
void dec_bin();
void bin_dec();
int potenzaDiDue(int esponente);
int* conversione_intera(int* arr_int, int *lenght_int, int intera);
int* conversione_decimale(int* arr_dec, int *lenght_dec, float decimale);






// Funzione di conversione da decimale -> binario
void dec_bin(){

    int decisione = 1;


    // definizione variabili da usare:
    int* arr_int; // array per la parte intera 
    int lenght_int; // lunghezza per l'array 
    int* arr_dec; // stessa cosa
    int lenght_dec;
    int* arr_esp;
    int lenght_esp;
    int starting;

    // numero decimale da far inserire 
    float num;
    int esp, mantissa; // esponente e mantissa nel numero macchina
    int esponente_vero; // l'esponente corretto nella rappresentazione in virgola mobile standardizzata
    int esponente_calcolatore; // l'esponente che deve essere applicato al calcolatore (e* = e + bias)
    // dove e* è l'esponente nel calcolatore ed 'e' è l'esponente vero nella rappresentazione fl.p.
    arr_int = (int*)malloc(sizeof(int)*lenght_int);
    arr_esp = (int*)malloc(sizeof(int)*lenght_esp);
    arr_dec = (int*)malloc(sizeof(int)*lenght_dec);


    printf("Type number of exp: "); 
    scanf("%d", &esp);
    printf("Type number of mantissa: ");
    scanf("%d", &mantissa);
    

while (decisione == 1){

        printf("Type decimal number: ");
        scanf("%f", &num);

        //inizializzazione delle lunghezze dei vettori:
        lenght_int = 0;
        lenght_dec = 0;
        lenght_esp = 0; 
        //conteggio dei bit usati per la mantissa
        int mantissa_printed = 0;



        //divido parte intera e decimale
        int intera = (int)num;
        float decimale = num-intera;
        if (intera < 0){
            intera = -intera;
        }
        if(decimale < 0){
            decimale = -decimale;
        }
        





        // conversione in decimale della parte intera su arr_int al contrario. La lunghezza si trova in lenght_int 
        if(intera != 0){
            arr_int = conversione_intera(arr_int, &lenght_int, intera);
        }
        if (arr_int == NULL){
            printf("ERRORE dalla conversione dell'intero");
        }






        // conversione in decimale della parte decimale su arr_dec al contrario. La lunghezza si trova in lenght_dec
        if (decimale != 0){
            arr_dec = conversione_decimale(arr_dec, &lenght_dec, decimale);
        }
        if (arr_dec == NULL){
            printf("\nERRORE dalla conversione del decimale");
        }






        // calcolo dell'esponente corretto:
        if(intera>0){
            esponente_vero = lenght_int-1;
        }
        else{
            for (int i = 0; i < lenght_dec; i++) {
                if (arr_dec[i] == 1) {
                    esponente_vero = -(i+1);
                    break;
                }
                if(i == lenght_dec - 1){
                    printf("\nERRORE, numero num <<< 0\n");
                }
            }
        }

        esponente_calcolatore = esponente_vero + potenzaDiDue(esp-1)-1;






        // conversione dell'esponente
        arr_esp = conversione_intera(arr_esp, &lenght_esp, esponente_calcolatore);

        // controlli sull'esponente
        if (arr_esp == NULL){
            printf("\nERRORE dalla conversione dell'esponente\n");
        }






        printf("\nNumero decimale: %f -> IEEE-754r: ", num);

        // stampa dei risultati:


        // Zero
        if (num == 0){
            printf("0 ");
            for (int i = 0; i < esp; i++){
                printf("0");
            }
            printf(" ");
            for (int i = 0; i < mantissa; i++){
                printf("0");
            }
            printf("\n");
        }  else 
        // casi particolari: infinito
        if (lenght_esp > esp){
            if(num > 0){
                printf("+Inf");
            }
            if(num < 0){
                printf("-inf");
            }
        } else {

            // altri casi:
            // Stampa del bit del segno
            if(num < 0 ){
                printf("1"); // 1 per negativo
            }
            else{
                printf("0"); // 0 per positivo
            }




            printf(" ");





            // Stampa dell'esponente
            // bisogna verificare se lenght_espo < espo
            for(int i = 0; i < (esp - lenght_esp); i++){
                printf("0");
            }
            for(int i = lenght_esp-1; i >= 0; i--){
                printf("%d", arr_esp[i]);
            }






            printf(" ");







            // Stampa della parte intera della mantissa
            for (int i = lenght_int-1; i >= 0; i--) {
                printf("%d", arr_int[i]);
                mantissa_printed++;
            }

            // Stampa della parte frazionaria della mantissa

            if(intera == 0){
                starting =  -(esponente_vero)-1;
            }else{
                starting = 0;
            }

            if(lenght_dec > 0){
                for (int i = starting; i < mantissa+starting; i++){
                    printf("%d", arr_dec[i]);
                    mantissa_printed++;
                    if (mantissa_printed == mantissa){
                        break;
                    }
                }
            }


            // Padding con zeri se necessario per raggiungere la lunghezza specificata della mantissa
            while (mantissa_printed < mantissa) {
                printf("0");
                mantissa_printed++;
            }
        } 
        printf("\n");

        printf("\n\nType 1 to use this exp & mantissa or type 2");
        printf("     |---------------->   ");
        scanf("%d", &decisione);  
    }    
}


// potenza di due
int potenzaDiDue(int esponente) {
    if (esponente < 0) {
      return 0;
    }
    int risultato = 1;
    for (int i = 0; i < esponente; i++) {
      risultato = risultato * 2;
    }
    return risultato;
}




// mi salva la conversione della parte intera in binario in arr_int e l'ordine della lettura va dal
// fondo all'inizio 
int* conversione_intera(int * arr_int, int* lenght, int intera){
    if (intera > 0){ // controllo se intera > 0 per la prima malloc su arr_int
        arr_int = (int*)malloc(sizeof(int)*1); 
        *lenght = *lenght+1; //setto la nuova lunghezza per l'array della parte intera 
        do{ 
            if(intera%2 == 0){ 
                arr_int[*lenght-1] = 0;
            }
            else{
                arr_int[*lenght-1] = 1;
            }
            intera = intera/2;
    
    
            if(intera>0){
                *lenght = *lenght+1;
                arr_int = (int*) realloc(arr_int, (*lenght)*sizeof(int));
                if (arr_int == NULL){
                    printf("Errore nella reallocarray (funzione parte_intera())\n");
                    return NULL;
                }
            }
        } while (intera > 0);
    }    
    return arr_int;
}



// mi salva la conversione della parte decimale in binario in arr_dec e l'ordine 
// di letture va dall'inizio alla fine
int* conversione_decimale(int* arr_dec, int *lenght_dec, float decimale){
    if(decimale != 0){
        arr_dec = (int*) malloc(sizeof(int)*1);
        *lenght_dec = *lenght_dec + 1; 
    }
    do { 
        decimale = decimale * 2;
        if (decimale >= 1) {
            arr_dec[*lenght_dec-1] = 1;
            decimale = decimale - 1;
        } else {
            arr_dec[*lenght_dec-1] = 0;
        }
        if(decimale != 0){
            *lenght_dec = *lenght_dec+1;
            arr_dec = (int*)realloc(arr_dec, (*lenght_dec)*sizeof(int));
            if (arr_dec == NULL){
                printf("Errore nella reallocarray (funzione parte_decimale())\n");
                return NULL;
            }
        }
    } while (decimale != 0 && *lenght_dec < 100); 
    return arr_dec;
}