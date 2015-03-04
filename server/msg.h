#ifndef MSG_H
#define	MSG_H

#define KEY_MSG 666

typedef struct msgplayerbuf {
    long mtype; // 0 - player 1, 1 - player 2;
    int data[6];
// standar
//    0 - number of players; (3 - war) 
//    1 - resources;
//    2 - workers;
//    3 - light_soldiers;
//    4 - heavy_soldiers;
//    5 - cavalry;
} Player_msg;

/* Na start serwer wysyła dwie wiadomości (mtype = 5) z różnymi wartościami w polu data[X * * * * *] (X = 1,2)
 * Każdy z klientów odbiera jedną z wyżej opisanych wiadomości, która przypisuje mu jego ID.
 * Następnie każdy z klientów wysła komunikaty o mtype=ID (gracz pierszy mtype = 1, gracz drugi mtype = 2),
 * natomiast serwer wysyła wiadomości do różnych klientów o mtype=ID+2 (do gracza pierwszego mtype=3, dla gracza drugiego mtype=4).
 * Przykładowa wiadomość gracza:
 *  mtype = 1; (mtype = 1,2)
 *  data = {2 0 X X X X}; (gra jest kontynuowana (2 na miejscu 0), a X oznaczają ilość jednostek do wyprodukowania)
 * Przykładowa wiadomość z serwera:
 *  mtype = 3;  (mtype = 3,4)
 *  data = {2 2344 4 5 6 7 } (2 na pierwszym miejscu oznacza, że w grze dalej jest 2 graczy,
 *  nastepne wartosci opisuja ilosc surowców i jednostek)
 * Nietypowe wiadomości od gracza:
 *  pierwsza wiadomość [0 0 0 0 0 0]
 *  rezygnacja [-1 0 0 0 0 0]
 *  walka [2 1 0 0 0 0]
 * Nietypowe wiadomości z serwera:
 *  wiadomości startowe
 *  przerwanie gry [-1 0 0 0 0 0]
 *  wygrales walke [3 X X X X X]
 *  przegrales walke [4 X X X X X]
 *  wygrales [5 X X X X X]
 *  przegrales [6 X X X X X]
 */

#endif	/* MSG_H */

