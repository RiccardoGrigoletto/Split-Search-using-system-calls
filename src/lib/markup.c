#include "markup.h"
#include <stdio.h>

typedef int bool;
#define TRUE 1
#define FALSE 0

//flag di controllo marcatori
bool flag_v,flag_o,flag_i,flag_a,flag_m = FALSE;

/*gestione marcatori -v,-i.
    fa uno switch v,i per capire quale marcatore si vuole gestire
    se c'è un altro elemento in argv, se il marcatore non era presente
    in precedenza si fa puntare a target l'oggetto puntato da argv[ind_element+1]
    e ritorna true
    altrimenti ritorna false
*/
bool v_i(char opt,int ind_element,char** target,char** argv, int argc) {
    ind_element++;
    bool* flag;
    switch(opt) {
        case('v') :
        flag = &flag_v; break;
        case('i') :
        flag= &flag_i; break;
        default: return FALSE;
        }
    if (ind_element<argc) {
        if (*flag==FALSE) {
            *target = argv[ind_element];
            *flag=TRUE;
            return TRUE;
        }
        else {
            return FALSE;
        }
    }
    else return FALSE;
}


//gestione marcatore -o.
//Simile a v_i ma se il marcatore è l'ultimo elemento di argv torna comunque true
bool o(char opt,int ind_element,char** target,char** argv, int argc)
{
    ind_element++;
    if (flag_o==FALSE)
    {
        if (ind_element<argc)
        {
            *target = argv[ind_element];
            flag_o=TRUE;
        }
        else
        {
            flag_o= TRUE;
        }
        return TRUE;
    }
    else return FALSE;
}

//gestione marcatore -m
bool m(int ind_element,int* target,char** argv, int argc) {
    ind_element++;
    if (ind_element<argc) {
        if (flag_m==FALSE) {
            *target = atoi(argv[ind_element]);
            flag_m=TRUE;
            return TRUE;
    }
        else {
            return FALSE;
        }
    }
}

/*gestione marcatore -a
    se -a non è stato utilizzato in precedenza si pone il target a 1
    (viene visualizzato il procedimento) e ritorna TRUE.
    altrimenti ritorna FALSE
*/
bool a(int* target) {
    if (flag_a==FALSE) {
        *target = 1;
        flag_a=TRUE;
        return TRUE;
    }
    else
    return FALSE;
}

//controlla se i marcatori obbligatori -v e -i sono presenti e ritorna il risultato
bool check_obb_marks(){
    if (flag_v==FALSE || flag_i==FALSE) {
        return FALSE;
    }
    else return TRUE;
}

//ritorna se il marcatore -o è presente
bool get_o() {
    return flag_o;
}
