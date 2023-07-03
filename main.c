//Sofia Yankova 2021230188
//Mafalda Figueiredo 20218309

#include "functions.h"

int main(){

    int menu=1; // menu switch
    int valid; 
    int option;
    ListReservation *reservations = create_ListReservation(); // Create lists for reservations
    ListPre *preReservations = create_ListPre(); // Create lists for pre-reservations
    Date date;
    Time time;
    Client client;
    Reservation pending;
    // Load data from file and save in the Reservation list
    printf("\nLoading Reservation data...");
    readReservationsFromFile(reservations);
    // Load data from file and save in the Pre-Reservation list
    printf("\nLoading Pre-Reservation data...");
    readPreFromFile(preReservations);

    while(menu){

        printf("\n ______________________________________________");
        barline();
        barline();
        printf("\n|                 AUTOLANDIA!                  |");
        barline();
        printf("\n|                                              |");
        barline();
        printf("\n|   1 - Book a Washing                         |"); 
        barline();
        printf("\n|   2 - Book a Maintenance                     |"); 
        barline();       
        printf("\n|   3 - Cancel a Reservation                   |"); 
        barline();
        printf("\n|   4 - Cancel a Pre-Reservation               |"); 
        barline();
        printf("\n|   5 - List Section                           |");
        barline();
        printf("\n_______________________________________________");
        barline(); 
        printf("\n|  0 - End session and keep everything saved.  |");
        printf("\n|______________________________________________|");
        
        printf("\n\n>>>> ");
        fflush(stdin);

        scanf("%d", &menu);       

        if(menu < 0 || menu > 10) printf( "\nFailure. Please enter a number.\n");
        else ("\nValid number.\n");

        switch (menu){
            
        case 1:

                printf("\n\nWashing Reservation");
                printf("\nPS: the duration is 30 minutos\n");

                printf("Name>>> ");
                fflush(stdin);
                fgets(name, SIZE, stdin);
                name[strcspn(name, "\n")] = '\0';

                if(validName(name) == 0 ){
                    printf("Name is not valid.\n");
                    break;
                }

                printf("Email>>> ");
                fflush(stdin);
                fgets(email, SIZE, stdin);
                email[strcspn(email, "\n")] = '\0';

                if(validEmail(email) == 0 ){
                    printf("Email is not valid.\n");
                    break;
                }
                printf("Date (d/m/a)>>>> ");
                fflush(stdin);
                scanf("%d/%d/%d", &day, &month, &year);

                if(validDate(day,month,year) == 0 ){
                    printf("Date is not valid.\n");
                    break;
                }

                printf("Time (h:m)>>>> ");
                fflush(stdin);
                scanf("%d:%d", &hour, &min);

                if(validTime(hour, min) == 0){
                    printf("Time is not valid.\n");
                    break;  
                }

                strcpy(pending.client.name, name);
                strcpy(pending.client.email, email);
                pending.date.day=day;
                pending.date.month=month;
                pending.date.year=year; 
                pending.time.hour= hour;
                pending.time.min= min;
                pending.type = 0;
                pending.duration = 30;

                if(reservar(reservations, pending))
                    printf("\nThe reservation was a success!");
                else{
                    printf("\nThere is not an available spot for the day and time. "); 
                    printf("\nThe reservation is on a waiting list");
                    preReservar(preReservations, pending);
                }

                EnterToContinue();   
                break;

        case 2:

                printf("\n\nMaintenance Reservations");
                printf("\nThe duration is 60 minutos\n");

                printf("Name>>> ");
                fflush(stdin);
                fgets(name, SIZE, stdin);
                name[strcspn(name, "\n")] = '\0';

                if(validName(name) == 0 ){
                    printf("Name is not valid.\n");
                    break;
                }

                printf("Email>>> ");
                fflush(stdin);
                fgets(email, SIZE, stdin);
                email[strcspn(email, "\n")] = '\0';

                if(validEmail(email) == 0 ){
                    printf("Email is not valid.\n");
                    break;
                }

                printf("Date (d/m/a)>>>> ");
                fflush(stdin);
                scanf("%d/%d/%d", &day, &month, &year);

                if(validDate(day,month,year) == 0 ){
                    printf("Date is not valid.\n");
                    break;
                }

                printf("Time (h:m)>>>> ");
                fflush(stdin);
                scanf("%d:%d", &hour, &min);
                if(validTime(hour, min) == 0){
                    printf("Time is not valid.\n");
                    break;  
                }

                strcpy(pending.client.name, name);
                strcpy(pending.client.email, email);
                pending.date.day=day;
                pending.date.month=month;
                pending.date.year=year; 
                pending.time.hour= hour;
                pending.time.min= min;
                pending.type = 1;
                pending.duration = 60;

                if(reservar(reservations, pending))
                    printf("\nThe reservation was a success!");
                else{
                    printf("\nThere is not an available spot for the day and time. "); 
                    printf("\nThe reservation is on a waiting list");
                    preReservar(preReservations, pending);
                }

                break;

        case 3:
            // Check if the list Reservation is empty
            if(checkEmptyReservation(reservations)) break;

            printf("\n\n -Cancel a reservation- \n\n"); 

            printf("Name>>> ");
            fflush(stdin);
            fgets(name, SIZE, stdin);
            name[strcspn(name, "\n")] = '\0';

            if(validName(name) == 0 ){
                printf("Name is not valid.\n");
                break;
            }

            printf("Email>>> ");
            fflush(stdin);
            fgets(email, SIZE, stdin);
            email[strcspn(email, "\n")] = '\0';

            if(validEmail(email) == 0 ){
                printf("Email is not valid.\n");
                break;
            }

            printf("Date (d/m/y)>>> ");
            fflush(stdin);
            scanf("%d/%d/%d", &day, &month, &year);
            if(validDate(day, month, year) == 0) {
                printf("Date is not valid.\n");
                break;
            }

            printf("Time (h:m)>>>> ");
            fflush(stdin);
            scanf("%d:%d", &hour, &min);
            if(validTime(hour, min) == 0) {
                printf("Time is not valid.\n");
                break;
            }

            Reservation reservation;
            reservation.date.day = day;
            strcpy(reservation.client.name, name); 
            cancelReservation(reservations, reservation);
            EnterToContinue();
            break;
            
        case 4:
            // Check if the list Pre-Reservation is empty
            if(checkEmptyPreReservation(preReservations)) break;

            printf("\n\n -Cancel a Pre-Reservation- \n\n");

            printf("Name>>> ");
            fflush(stdin);
            fgets(name, SIZE, stdin);
            name[strcspn(name, "\n")] = '\0';

            if(validName(name) == 0 ){
                printf("Name is not valid.\n");
                break;
            }

            printf("Email>>> ");
            fflush(stdin);
            fgets(email, SIZE, stdin);
            email[strcspn(email, "\n")] = '\0';

            if(validEmail(email) == 0 ){
                printf("Email is not valid.\n");
                break;
            }

            printf("Date (d/m/y)>>> ");
            fflush(stdin);
            scanf("%d/%d/%d", &day, &month, &year);
            if(validDate(day, month, year) == 0) {
                printf("Date is not valid.\n");
                break;
            }

            printf("Time (h:m)>>>> ");
            fflush(stdin);
            scanf("%d:%d", &hour, &min);
            if(validTime(hour, min) == 0) {
                printf("Time is not valid.\n");
                break;
            }

            Pre pre;
            pre.date.day = day;
            strcpy(pre.client.name, name); 
            cancelPreReservation(preReservations, pre);
            printf("\nThe reservation was cancelled with success!");
            EnterToContinue();
            break;
            
        case 5:
            printf("\n ________________________________");
            barline2();
            printf("\n|       -List Reservation-       |");
            barline2();
            printf("\n|  1 - Reservations              |");
            barline2();
            printf("\n|  2 - Pre-Reservations          |");
            barline2();
            printf("\n|  3 - Client Reservations       |");
            barline2();
            printf("\n|  4 - Client PreReservations    |");
            printf("\n ________________________________");
            barline2();
            printf("\n|  0 - Go back to menu.          |");
            printf("\n|________________________________|");

            printf("\n\n>>>");
            fflush(stdin);

            scanf("%d", &option);

            if(option < 0 || option > 5) printf( "Failure. Please enter a number.\n");
            else ("Valid number.\n");

            int getback = 0;

            switch(option) {
                case 1:
                    if(checkEmptyReservation(reservations)) break;

                    printf("Reservations:\n");
                    printReservations(reservations);
                    EnterToContinue();
                    break;
                case 2:
                    if(checkEmptyPreReservation(preReservations)) break;

                    printf("Pre-Reservations:\n");
                    printPre(preReservations);
                    EnterToContinue();
                    break;
                case 3:
                    if(checkEmptyReservation(reservations)) break;

                    printf("Reservations by Client:\n");
                    
                    printf("Name>>> ");
                    fflush(stdin);
                    fgets(name, SIZE, stdin);
                    name[strcspn(name, "\n")] = '\0';
                        
                    if(validName(name) == 0 ){
                        printf("Name is not valid.\n");
                        break;
                    }

                    printf("Email>>> ");
                    fflush(stdin);
                    fgets(email, SIZE, stdin);
                    email[strcspn(email, "\n")] = '\0';

                    if(validEmail(email) == 0 ){
                        printf("Email is not valid.\n");
                        break;
                    }

                    strcpy(client.name, name);
                    strcpy(client.email, email);

                    printClientReservations(reservations, client);
                    EnterToContinue();
                    break;
                case 4:
                    if(checkEmptyPreReservation(preReservations)) break;

                    printf("Pre-Reservations by Client:\n");
                    
                    printf("Name>>> ");
                    fflush(stdin);
                    fgets(name, SIZE, stdin);
                    name[strcspn(name, "\n")] = '\0';
                        
                    if(validName(name) == 0 ){
                        printf("Name is not valid.\n");
                        break;
                    }

                    printf("Email>>> ");
                    fflush(stdin);
                    fgets(email, SIZE, stdin);
                    email[strcspn(email, "\n")] = '\0';

                    if(validEmail(email) == 0 ){
                        printf("Email is not valid.\n");
                        break;
                    }
        
                    strcpy(client.name, name);
                    strcpy(client.email, email);

                    EnterToContinue();
                    break;
                case 0:
                    getback=1;
                    break;
                
            }
            if (getback=1){
                break;
            }

        case 0:
            printf("\n ____________________________________");
            printf("\n|         Ending session...          |");
            printf("\n|____________________________________|");
            printf("\n\nSaving the new data into database, please dont interrupt the proccess...");

            writeListReservation(reservations);
            writeListPre(preReservations);

            printf("\n\nAll alterations were saved into the database with success:)\n\n");
            break;

        default:
            printf("\n\nError!!\n");
            break;
        }
    }
    return 0;

}