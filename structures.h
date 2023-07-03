#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>


#define SIZE 256

// Date structure
typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    int hour;
    int min;
} Time;

// Client structure
typedef struct Client {
    char name[SIZE];
    char email[SIZE];
    struct ListReservation* reservation;
    struct ListPre* pre;
} Client;

// Reservation structure
typedef struct Reservation {
    struct Client client;
    int type; // waching = 0, manteinance = 1
    Date date;
    Time time;
    int completed; // 0 - não concluído, 1 - concluído
    int duration; // 30 or 60 (in minutes)
} Reservation;

typedef struct NoListReservation {
    struct Reservation reservation;
    struct NoListReservation* next;
} NoListReservation;

typedef struct ListReservation {
    struct NoListReservation* start;
    int size;
} ListReservation;

typedef struct Pre {
    struct Client client;
    int type; // waching = 0, manteinance = 1
    Date date;
    Time time;
    int completed; // 0 - não concluído, 1 - concluído
    int duration; // 30 or 60 (in minutes)
} Pre;

typedef struct NoListPre {
    struct Pre pre;
    struct NoListPre* next;
} NoListPre;

typedef struct ListPre {
    struct NoListPre* start;
    int size;
} ListPre;
