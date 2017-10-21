/*
 ============================================================================
 Name        : ICMP_IPv4.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
/*
 ============================================================================
 Name        : ICMP_IPv4.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <sys/socket.h>
#include <netinet/ip.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BUF_SIZE 255
#define PORT 4033
    int sd, rc, odpowiedz = 0;
    char buf[BUF_SIZE], host[20];
    char dane[BUF_SIZE];
    struct sockaddr_in to;

    void wyslij_datagram();
    void odbierz_datagram();
    void odbierz_potwierdzenie();
    void sprawdz_odp();


    printf("cscsdmdfk");

main(int argv, char *args[]) {

    if(argv<2)
    {
        printf("Wpisz: %s <serwer>\n", args[0]);
        exit(1);
    }

    strcpy(host, args[0]);
    // gniazdo ...
    sd = socket(PF_INET, SOCK_DGRAM, 0);
    if (sd<0) {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // wysylanie danych

    to.sin_family=PF_INET;
    to.sin_port=htons(PORT);
    inet_aton(args[1], &to.sin_addr);

        //program wlasciwy
        memset(dane, 0x0, BUF_SIZE);
        //printf("%s> ", args[0]);
        //fputs("podaj ciag znakow: ", stdout);
        //fgets(dane, sizeof(dane), stdin);
         //  if (!strncmp(dane, "exit", 4))
         //return 1;
        strcpy(dane, args[2]);
        //dane[strlen(dane)-1]=0;   //usuwam znak przejscia do noewj lini
        wyslij_datagram(dane);
        //odbierz_datagram();

    // zamkniecie gniazda
    close(sd);
}

void wyslij_datagram(char msg[BUF_SIZE])
{
    rc = sendto(sd, msg, strlen(msg), 0, (struct sockaddr *) &to, sizeof(struct sockaddr_in));
    if(rc<0)
        printf("%s> nie mozna wyslac danych\n", host);
    else
        printf("%s> wyslano datagram: %s \n", host, msg);

    //oczekiwanie na potwierdzenie

    char tmp[2] = "RC";
    if(!(strncmp(tmp, msg, 2)==0))//datagram nie jest potwierdzeniem
    {
       // odbierz_potwierdzenie();//przerobic na odbierz_potwierdzenie()
        odbierz_datagram();
    }

}

void odbierz_datagram()
{
    char msg[BUF_SIZE];
    memset(msg, 0x0, BUF_SIZE);
    memset(buf, 0x0, BUF_SIZE);
    socklen_t tolen = sizeof(to);
    printf("Odbierz datagram");
    rc = recvfrom(sd, msg, BUF_SIZE, 0, (struct sockaddr *) &to, &tolen);

    if(rc<0)
        fprintf(stderr, "%s\n", strerror(errno));
    else
    {
        printf("%s> odebrano datagram: \n %s\n ", host, msg);
        strcpy(buf, msg);
    }

    char tmp[2] = "RC";
    if(!(strncmp(tmp, msg, 2)==0))//datagram nie jest potwierdzeniem
        wyslij_datagram("RC");
}
/*
void odbierz_potwierdzenie()
{   int i;
    pthread_t watek;
    pthread_create( &watek, 0, sprawdz_odp, NULL);
    for(i=0;i<3;i++)
    {

        if(odpowiedz == 1)
            break;
        //printf("FOR %d", i);
        sleep(1);
    }
    if(!odpowiedz)
        printf("%s> nie odebrano potwierdzenia", host);
    //pthread_exit(watek);
}*/

void sprawdz_odp(){
    memset(buf, 0x0, BUF_SIZE);
    socklen_t tolen = sizeof(to);
    printf("Dziala watek\n");
    recvfrom(sd, buf, BUF_SIZE, 0,(struct sockaddr *) &to, &tolen);
    printf("%s> odebrano potwierdzenie: %s\n", host, buf);
    odpowiedz = 1;
}
