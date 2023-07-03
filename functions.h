#include "structures.h"

// Files
FILE * FReservations;
FILE * FPreReservations;

char line[SIZE];

int firstHere;
int len;

// Aux variables
char name[SIZE];
char email[SIZE];
float duration;
int type;
int day;
int month;
int year;
int hour;
int min;
char service[SIZE];


// Menu interface bar
void barline() {
    printf("\n|                                              |");
}

// Menu interface bar 2
void barline2(){
    printf("\n|                                |");
}

// 
void EnterToContinue(){
    printf("\n\nPress \"ENTER\" to get back to menu...");
    fflush(stdin);
    getchar();
}

// Read from Reservation file 
void readReservationsFromFile(ListReservation* reservationList) {

    FReservations = fopen("Reservations.txt", "r");
    if (FReservations == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while (fgets(line, sizeof(line), FReservations)) {

        Reservation newReservation;

        sscanf(line, "Client:%[^ ] Email:%[^ ] Service:%[^ ] Date:%d/%d/%d Time:%d:%d Duration:%dmin",
               newReservation.client.name, newReservation.client.email, service, &newReservation.date.day,
               &newReservation.date.month, &newReservation.date.year, &newReservation.time.hour,
               &newReservation.time.min, &newReservation.duration);

        // Determine the reservation type based on the service
        if (strcmp(service, "Washing") == 0) {
            newReservation.type = 0;
        } else if (strcmp(service, "Maintenance") == 0) {
            newReservation.type = 1;
        } else {
            printf("Invalid service: %s\n", service);
            continue;
        }

        // Set default values for other reservation fields
        newReservation.completed = 0;

        // Create a new node and add it to the reservation list
        NoListReservation* newReservationNode = (NoListReservation*)malloc(sizeof(NoListReservation));
        if (newReservationNode == NULL) {
            printf("Not enough memory to create the node for the reservation.\n");
            fclose(FReservations);
            return;
        }
        newReservationNode->reservation = newReservation;
        newReservationNode->next = NULL;

        if (reservationList->start == NULL) {
            // The list is empty, make the new node the start
            reservationList->start = newReservationNode;
        } else {
            // Find the last node and append the new node
            NoListReservation* current = reservationList->start;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newReservationNode;
        }
        reservationList->size++;
    }
    fclose(FReservations);
}

// Read from Pre-Reservation file
void readPreFromFile(ListPre* preList) {

    FPreReservations = fopen("PreReservations.txt", "r");
    if (FPreReservations == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while (fgets(line, sizeof(line), FPreReservations)) {

        Pre newPre;

        sscanf(line, "Client:%[^ ] Email:%[^ ] Service:%[^ ] Date:%d/%d/%d Time:%d:%d Duration:%dmin",
               newPre.client.name, newPre.client.email, service, &newPre.date.day,
               &newPre.date.month, &newPre.date.year, &newPre.time.hour,
               &newPre.time.min, &newPre.duration);

        // Determine the reservation type based on the service
        if (strcmp(service, "Washing") == 0) {
            newPre.type = 0;
        } else if (strcmp(service, "Maintenance") == 0) {
            newPre.type = 1;
        } else {
            printf("Invalid service: %s\n", service);
            continue;
        }

        // Set default values for other reservation fields
        newPre.completed = 0;

        // Create a new node and add it to the reservation list
        NoListPre* newPreNode = (NoListPre*)malloc(sizeof(NoListPre));
        if (newPreNode == NULL) {
            printf("Not enough memory to create the node for the reservation.\n");
            fclose(FReservations);
            return;
        }
        newPreNode->pre = newPre;
        newPreNode->next = NULL;

        if (preList->start == NULL) {
            // The list is empty, make the new node the start
            preList->start = newPreNode;
        } else {
            // Find the last node and append the new node
            NoListPre* current = preList->start;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newPreNode;
        }
        preList->size++;
    }
    fclose(FPreReservations);
}
 
// Cheack is the list is not empty
int checkEmptyReservation (ListReservation *list) {
    if (list->size==0) {
        printf("\nThere is no data of reservations in this database to conclude this operation.");
        EnterToContinue();
        return 1;
    }
    return 0;
}
// Cheack is the list is not empty
int checkEmptyPreReservation (ListPre *list) {
    if (list->size==0) {
        printf("\nThere is no data of pre-reservations in this database to conclude this operation.");
        EnterToContinue();
        return 1;
    }
    return 0;
}


void warningNoMem() {
    printf("\nThe app can not function without data, so it will close now.");
    printf("\n\nPress \"ENTER\" to continue...");
    getchar();
    exit(0);
}

ListReservation *create_ListReservation () {

    ListReservation *list = malloc(sizeof(ListReservation));
    if (list) {
        list->start = NULL;
        list->size = 0;
    }
    else {
        printf("\n\nNot enough memory to create a Reservation List.");
        warningNoMem();
    }
    return list;
}

ListPre *create_ListPre () {

    ListPre *list = malloc(sizeof(ListPre));
    if (list) {
        list->start = NULL;
        list->size = 0;
    }
    else {
         printf("\n\nNot enough memory to create a Reservation List.");
        warningNoMem();
    }
    return list;
}


void printReservations (ListReservation* list) {

    NoListReservation* atual = list->start;
    while (atual) {

        printf("\n\nList of all the reservations in the database, from the oldest to the most recent:");

        printf("\nClient: %s", atual->reservation.client.name);
        printf("\nDate: %d/%d/%d", atual->reservation.date.day, atual->reservation.date.month, atual->reservation.date.year);
        printf("\nTime: %d:%d", atual->reservation.time.hour, atual->reservation.time.min);

        atual = atual->next;
    }

}

void printPre(ListPre* list) {

    NoListPre* atual = list->start;
    while (atual) {

        printf("\n\nList of all the pre-reservations in the database, from the oldest to the most recent:");
    
        printf("\nClient: %s", atual->pre.client.name);
        printf("\nDate: %d/%d/%d", atual->pre.date.day, atual->pre.date.month, atual->pre.date.year);
        printf("\nTime: %d:%d", atual->pre.time.hour, atual->pre.time.min);

        atual = atual->next;
    }
}

void writeListReservation(ListReservation *list) {

    firstHere=1;
    FReservations = fopen("Reservations.txt", "w");

    if (FReservations == NULL) {
        printf("Failed to open the Reservations file.\n");
        return;
    }

    NoListReservation* atualReservation = list->start;

    while(atualReservation) {
        firstHere = 0;

        if (atualReservation->reservation.type == 0) strcpy(service, "Washing");
        else strcpy(service, "Maintenance");

        fprintf(FReservations,"Client:%s ",atualReservation->reservation.client.name);
        fprintf(FReservations,"Email:%s ",atualReservation->reservation.client.email);
        fprintf(FReservations, "Service:%s ", service);
        fprintf(FReservations,"Date:%d/%d/%d ",atualReservation->reservation.date.day, atualReservation->reservation.date.month, atualReservation->reservation.date.year);
        fprintf(FReservations,"Time:%d:%d ",atualReservation->reservation.time.hour, atualReservation->reservation.time.min);
        fprintf(FReservations, "Duration:%dmin\n", atualReservation->reservation.duration);

        atualReservation = atualReservation->next;
    }

    if(firstHere) {
        printf("There is still no data in the database.");
        printf("\nData is not saving in the database.");

    }

    fclose(FReservations);
}

void writeListPre (ListPre *list) {

    firstHere=1;
    FPreReservations = fopen("PreReservations.txt","w");

    if (FPreReservations == NULL) {
        printf("Failed to open the Pre-reservations file.\n");
        return;
    }

    NoListPre * atualPre = list->start;

    while(atualPre) {
        firstHere=0;

        if (atualPre->pre.type == 0) strcpy(service, "Washing");
        else strcpy(service, "Maintenance");

        fprintf(FPreReservations, "Client:%s ", atualPre->pre.client.name);
        fprintf(FPreReservations, "Service:%s ", service);
        fprintf(FPreReservations, "Date:%d/%d/%d ", atualPre->pre.date.day, atualPre->pre.date.month,atualPre->pre.date.year);
        fprintf(FPreReservations, "Time:%d:%d ", atualPre->pre.time.hour, atualPre->pre.time.min);
        fprintf(FPreReservations, "Duration:%dmin\n", atualPre->pre.duration);
        atualPre=atualPre->next;
    }
    if(firstHere) printf("There is no registry of any reservations or pre-reservations in the database.");

    fclose(FPreReservations);
}

void cancelReservation(ListReservation* list, Reservation reservation) {

    NoListReservation* atual = list->start;
    NoListReservation* prev = NULL;
    while (atual) {
        if (strcmp(reservation.client.name, atual->reservation.client.name) == 0 && reservation.type == atual->reservation.type && reservation.date.day == atual->reservation.date.day && reservation.date.month == atual->reservation.date.month && reservation.date.year == atual->reservation.date.year &&  reservation.time.hour  == atual->reservation.time.hour && reservation.time.min == atual->reservation.time.min ){

            if (prev) prev->next = atual->next;
            else list->start = atual->next;
            free(atual);
            printf("\nReservation was canceled");
            return;
        }
        prev = atual;
        atual = atual->next;
    }
    printf("\nReservation was not found.");
}

void cancelPreReservation(ListPre* list, Pre pre) {

    NoListPre* atual = list->start;
    NoListPre* prev = NULL;
    while (atual) {
        if (strcmp(pre.client.name, atual->pre.client.name) == 0 && strcmp(pre.client.email, atual->pre.client.email) == 0 && pre.type == atual->pre.type && pre.date.day == atual->pre.date.day && pre.date.month == atual->pre.date.month && pre.date.year == atual->pre.date.year && pre.time.hour  == atual->pre.time.hour && pre.time.min == atual->pre.time.min  ){

            if (prev) prev->next = atual->next;
            else list->start = atual->next;
            free(atual);
            printf("\nPre-reservation was canceled");
            return;  
        }
        prev = atual;
        atual = atual->next;
    }
    printf("\nPre-Reservation was not found.");
}

int reservationAvailable(Reservation pending, ListReservation* reservation) {

    // Iterate over the reservations and check for conflicts
    NoListReservation* atualReservation = reservation->start;
    while (atualReservation) {
        if (atualReservation->reservation.type == pending.type && atualReservation->reservation.date.day == pending.date.day && atualReservation->reservation.date.month == pending.date.month && atualReservation->reservation.date.year == pending.date.year) {
            // Check if the existing reservation overlaps with the new reservation
            if (atualReservation->reservation.time.hour == pending.time.hour && atualReservation->reservation.time.min == pending.time.min) {
                printf("\nA reservation at the same time already exists.");
                return 0; 
            } else if (atualReservation->reservation.type == 0) {
                // Check if the existing reservation is for washing (30 minutes) and within 30 minutes of the new reservation
                int diffMin = (pending.time.hour * 60 + pending.time.min) - (atualReservation->reservation.time.hour * 60 + atualReservation->reservation.time.min);
                if (diffMin >= 0 && diffMin < 30) {
                    printf("\nA reservation with a washing service already exists within 30 minutes.");
                    return 0;
                }
            } else if (atualReservation->reservation.type == 1) {
                // Check if the existing reservation is for maintenance (60 minutes) and within 60 minutes of the new reservation
                int diffMin = (pending.time.hour * 60 + pending.time.min) - (atualReservation->reservation.time.hour * 60 + atualReservation->reservation.time.min);
                if (diffMin >= 0 && diffMin < 60) {
                    printf("\nA reservation with a maintenance service already exists within 60 minutes.");
                    return 0; 
                }
            }
        }
        atualReservation = atualReservation->next;
    }
    printf("\nThe slot is available. :)");
    return 1;
}


int reservar(ListReservation* ListReservation, Reservation reservation) {

    if ( !reservationAvailable(reservation, ListReservation)){
        return 0;
    }

    Reservation* newReservation = (Reservation*)malloc(sizeof(Reservation));
    if (newReservation == NULL) {
        printf("Not enough memory to conclude this operation.\n");
        return 0;
    }

    strcpy(newReservation->client.name, reservation.client.name);
    strcpy(newReservation->client.email, reservation.client.email);
    newReservation->type = reservation.type;
    newReservation->date = reservation.date;
    newReservation->time.hour = reservation.time.hour;
    newReservation->time.min = reservation.time.min;
    newReservation->duration = reservation.duration;
    newReservation->completed = 0; // Initialize as not completed
    
    // Add the new reservation to the reservation list
    NoListReservation* newReservationNode = (NoListReservation*)malloc(sizeof(NoListReservation));
    if (newReservationNode == NULL) {
        printf("Not enough memory to create the node to the reservation.\n");
        free(newReservation);
        return 0;
    }
    newReservationNode->reservation = *newReservation;
    newReservationNode->next = NULL;

    if (ListReservation->start == NULL) {
        // The list is empty, make the new node the start
        ListReservation->start = newReservationNode;
    } else {
        // Find the last node and append the new node
        NoListReservation* current = ListReservation->start;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newReservationNode;
    }

    ListReservation->size++;

    printf("\nThe reservation was booked with success:)\n");
    return 1;
}

int preReservar(ListPre* listPre, Reservation pre) {

    Pre* newReservation = (Pre*)malloc(sizeof(Pre));
    if (newReservation == NULL) {
        printf("Not enough memory to conclude this operation.\n");
        return 0;
    }

    strcpy(newReservation->client.name, pre.client.name);
    strcpy(newReservation->client.email, pre.client.email);
    newReservation->type = pre.type;
    newReservation->date = pre.date;
    newReservation->time = pre.time;
    newReservation->duration = pre.duration;
    newReservation->completed = 0; // Initialize as not completed
    
    // Add the new reservation to the reservation list
    NoListPre* newReservationNode = (NoListPre*)malloc(sizeof(NoListPre));
    if (newReservationNode == NULL) {
        printf("Not enough memory to create the node to the pre-reservation.\n");
        free(newReservation);
        return 0;
    }
    newReservationNode->pre = *newReservation;
    newReservationNode->next = NULL;

    // The list is empty, make the new node the start
    if (listPre->start == NULL)  listPre->start = newReservationNode;
    else {
        // Find the last node and append the new node
        NoListPre* current = listPre->start;
        while (current->next != NULL) current = current->next;
        current->next = newReservationNode;
    }
    listPre->size++;

    printf("\nThe pre-reservation was booked with success:)\n");
    return 1;
}

void printClientReservations(ListReservation* list, Client client){

    NoListReservation* atual = list->start;
    int found = 0;

    while (atual){
        if (strcmp(atual->reservation.client.name, client.name) == 0){
            if (!found) {
                printf("\n\nClient found:\n");
                printf("Name: %s\nEmail: %s\n", client.name, client.email);
                printf("Reservations:\n");
                found = 1;
            }
            printf("Date: %d/%d/%d\n", atual->reservation.date.day, atual->reservation.date.month, atual->reservation.date.year);
            printf("Time: %d:%d\n", atual->reservation.time.hour, atual->reservation.time.min);
            printf("Type: %s\n", (atual->reservation.type == 0) ? "Washing" : "Maintenance");
            printf("Duration: %d minutes\n", atual->reservation.duration);
            printf("Completed: %s\n", (atual->reservation.completed == 0) ? "No" : "Yes");
            printf("\n");
        }
        atual = atual->next;
    }

    if (!found) printf("\nNo reservations found for the given client.\n");
   
}
// Validate client name 
int validName(char name[]) {

    len = strlen(name);
    for (int i = 0; i < len; i++) {
        if (!isalpha(name[i])) { // Check if character is not alphabetic
            return 0;
        }
    }
    return 1;
}

// Validate client email
int validEmail(char email[]){

    len = strlen(email);
    if (len <= 10) { // Minimum length for "@gmail.com"
        return 0;
    }

    for (int i = 0; i < len; i++) {
        if (isupper(email[i])) { // Check for uppercase letters
            return 0;
        }
    }

    const char* suffix = "@gmail.com";
    int suffixLength = strlen(suffix);

    if (len < suffixLength || strcmp(email + len - suffixLength, suffix) != 0) {
        return 0;
    }

    return 1;


}

// Validate date
int validDate(int day, int month, int year){

    // Check if the year is greater than or equal to 2023, month is between 1 and 12, and day is between 1 and 31
    if(year >= 2023 && month > 0 && month < 13 && day > 0 && day < 32){
        // Check for February
        if(month == 2) {
            // Leap year calculation: divisible by 4 and not divisible by 100, or divisible by 400
            if(((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)){
                if(day < 30) return 1; 
                else return 0; 
            }
            else{
                if(day < 29) return 1; 
                else return 0; 
            }
        }
        // Check for April, June, September, November
        else if (month == 4 || month == 6 || month == 9 || month == 11){
            if(day < 31) return 1; 
            else return 0; 
        }
        else return 1; 
    
    }
    else return 0; 
    
}


int validTime(int hour, int minute) {
    // Check if hour is within the valid range (8 to 18)
    if (hour < 8 || hour > 18) return 0; //Invalid hour

    // Check if minute is within the valid range (0 to 59)
    if (minute < 0 || minute > 59) return 0; // Invalid minute

    // If both hour and minute are valid, return 1 (true)
    return 1;
}