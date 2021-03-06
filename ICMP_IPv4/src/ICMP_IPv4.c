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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>           // close()
#include <string.h>           // strcpy, memset(), and memcpy()

#include <netdb.h>            // struct addrinfo
#include <sys/types.h>        // needed for socket(), uint8_t, uint16_t, uint32_t
#include <sys/socket.h>       // needed for socket()
#include <netinet/in.h>       // IPPROTO_RAW, IPPROTO_IP, IPPROTO_ICMP, INET_ADDRSTRLEN
#include <netinet/ip.h>       // struct ip and IP_MAXPACKET (which is 65535)
#include <netinet/ip_icmp.h>  // struct icmp, ICMP_ECHO
#include <arpa/inet.h>        // inet_pton() and inet_ntop()
#include <sys/ioctl.h>        // macro ioctl is defined
#include <bits/ioctls.h>      // defines values for argument "request" of ioctl.
#include <net/if.h>           // struct ifreq

#include <errno.h>            // errno, perror()

#include "bibliotekahe.h"

// Definiuje zmienne przechowujące długości nagłówków IP i ICMP.
//#define IP4_HDRLEN 20         // IPv4 header length
#define IP4_HDRLEN 20
#define ICMP_HDRLEN 8         // ICMP header length for echo request, excludes data

// Function prototypes
/////////////////////////////////uint16_t checksum (uint16_t *, int);
/////////////////////////////////char *allocate_strmem (int);
/////////////////////////////////uint8_t *allocate_ustrmem (int);
/////////////////////////////////int *allocate_intmem (int);

int
main (int argc, char **argv)
{

  int status, datalen, sd, *ip_flags;
  const int on = 1;
  char *interface, *target, *src_ip, *dst_ip;
  struct ip iphdr;
  struct icmp icmphdr;
  uint8_t *data, *packet;
  struct addrinfo hints, *res;
  struct sockaddr_in *ipv4, sin;
  struct ifreq ifr;
  void *tmp;

  // Allocate memory for various arrays.
  data = allocate_ustrmem (IP_MAXPACKET);
  packet = allocate_ustrmem (IP_MAXPACKET);
  interface = allocate_strmem (40);
  target = allocate_strmem (40);
  src_ip = allocate_strmem (INET_ADDRSTRLEN);
  dst_ip = allocate_strmem (INET_ADDRSTRLEN);
  ip_flags = allocate_intmem (4);


  /////////////////////////////////////////////////////
   int c;
   int wysylkaliczba=0;
   int versjaip=0;
   int spdlip=0;
   int sprttl=0;
      //int bflg;
      //int aflg;
      //int errflg;
      char *ifile;
      char *zipfile;
      char *ofile;
      char *protip;
      char *icmptyp;
      int *ilerazy;
      int ileraz;
      ilerazy=&ileraz;
      int wsipwers=-1;
      char *bipwers;
      bipwers=&wsipwers;
      int *wsdlip;
      int dlip;
      wsdlip=&dlip;
      int ttlint;
      int *wskttlint;
      wskttlint=&ttlint;
      int protokol=0;
//      int zm1;
//      int *zm2;
//      zm2=&zm1;
      extern char *optarg;
      extern int optind, optopt;
      printf("Dodaj opcje według wzoru  -w (ip vers 4) -l (dl 20) -b (ile razy wyslac?) -p ( IPPROTO_ICMP ) -t (ttl) -i (icmp_type) -f(dest IP) -z(zrip) -o (interf) arg\n");
  while ((c = getopt(argc, argv, ":w:l:b:p:t:i:f:z:o:")) != -1) {
          switch(c) {
          case 'w':
              //bipwers=optarg;
        	  wsipwers=atoi(optarg);
        	  versjaip=1;
              break;
          case 'l':
              dlip=atoi(optarg);
              spdlip=1;

              break;
          case 'b':
        	  ileraz= atoi(optarg);
        	  wysylkaliczba =1;

        	  break;
          case 'p':
                        protip = optarg;
                        protokol=1;
                        break;
          case 't':
              ttlint= atoi(optarg);
              sprttl =1;

                  	  break;
          case 'i':
              icmptyp= optarg;
              //icmptypsprttl =1;
              break;

          case 'f':
              ifile = optarg;

              break;

          case 'z':
              zipfile = optarg;
               break;

          case 'o':
              ofile = optarg;

              break;

          }}
  ///////////////////////////////////////////////////////////////////////////////
//
  // Interface to send packet through.
  strcpy (interface, ofile);//p8p1  wlp2s0

  // Submit request for a socket descriptor to look up interface.
  if ((sd = socket (AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0) {
    perror ("socket() failed to get socket descriptor for using ioctl() ");
    exit (EXIT_FAILURE);
  }

  // Use ioctl() to look up interface index which we will use to
  // bind socket descriptor sd to specified interface with setsockopt() since
  // none of the other arguments of sendto() specify which interface to use.
  memset (&ifr, 0, sizeof (ifr));
  snprintf (ifr.ifr_name, sizeof (ifr.ifr_name), "%s", interface);
  if (ioctl (sd, SIOCGIFINDEX, &ifr) < 0) {
    perror ("ioctl() failed to find interface ");
    return (EXIT_FAILURE);
  }
  close (sd);
  printf ("Index for interface %s is %i\n", interface, ifr.ifr_ifindex);

  // Source IPv4 address: you need to fill this out
  //strcpy (src_ip, zipfile);

  Set_Source_Addr(src_ip,zipfile);

  // Destination URL or IPv4 address: you need to fill this out
  //strcpy (target, ifile);

  Set_Dest_Addr(target,ifile);

 // Fill out hints for getaddrinfo().
  memset (&hints, 0, sizeof (struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = hints.ai_flags | AI_CANONNAME;

  // Resolve target using getaddrinfo().
  if ((status = getaddrinfo (target, NULL, &hints, &res)) != 0) {
    fprintf (stderr, "getaddrinfo() failed: %s\n", gai_strerror (status));
    exit (EXIT_FAILURE);
  }
  ipv4 = (struct sockaddr_in *) res->ai_addr;
  tmp = &(ipv4->sin_addr);
  if (inet_ntop (AF_INET, tmp, dst_ip, INET_ADDRSTRLEN) == NULL) {
    status = errno;
    fprintf (stderr, "inet_ntop() failed.\nError message: %s", strerror (status));
    exit (EXIT_FAILURE);
  }
  freeaddrinfo (res);

  // ICMP data
  datalen = 5;
  data[0] = 'P';
  data[1] = 'a';
  data[2] = 'w';
  data[3] = 'e';
  data[4] = 'l';

  // IPv4 header

  // IPv4 header length (4 bits): Number of 32-bit words in header = 5
 // printf("xdxdxdxdxdxdxdx\n");
  if (spdlip==0){
   IPv4_length2(&iphdr);
  }
  else{
   //IPv4_length(&iphdr,wsdlip);
  iphdr.ip_hl = 20 / sizeof (uint32_t);
   }


  // Internet Protocol version (4 bits): IPv4

  if(versjaip==0)
  {
	  //printf("\nWchodzi\n");
	  IPv4_Header_Set_Version2( &iphdr);

   }else{
	IPv4_Header_Set_Version( &iphdr,bipwers);
  }


  // Type of service (8 bits)

  Type_of_service( &iphdr,0);

  // Total length of datagram (16 bits): IP header + ICMP header + ICMP data
  iphdr.ip_len = htons (IP4_HDRLEN + ICMP_HDRLEN + datalen);

  // ID sequence number (16 bits): unused, since single datagram
  ID_sequence_number(&iphdr, 0);


  // Flags, and Fragmentation offset (3, 13 bits): 0 since single datagram

  // Zero (1 bit)
  ip_flags[0] = 0;

  // Do not fragment flag (1 bit)
  ip_flags[1] = 0;

  // More fragments following flag (1 bit)
  ip_flags[2] = 0;

  // Fragmentation offset (13 bits)
  ip_flags[3] = 0;

  iphdr.ip_off = htons ((ip_flags[0] << 15)
                      + (ip_flags[1] << 14)
                      + (ip_flags[2] << 13)
                      +  ip_flags[3]);

  // Time-to-Live (8 bits): default to maximum value

  if (sprttl==0)
  {
	  ttl2(&iphdr, 255);
  }
  else if( sprttl==1 && (*wskttlint>255 || *wskttlint<1))
  {
	  printf("Podaj odpowiedni ttl\n");

  }else
  {
	  if( sprttl==1)
		  ttl2(&iphdr, ttlint);
  }

  // Transport layer protocol (8 bits): 1 for ICMP
//

  //printf("xdxdxdxdxdxdxdx\n");
  if (protokol==0)
  {
  transport_icmp_proto2(&iphdr,IPPROTO_ICMP);
	  //iphdr.ip_p = IPPROTO_ICMP;
  }
  else if(protokol==1 && strcmp(protip,"IPPROTO_ICMP") != 0){

	  printf("zły protokol\n");
  }
  else
  {
	  if( protokol==1 && strcmp(protip,"IPPROTO_ICMP") ==0)
		  {
		  transport_icmp_proto2(&iphdr,IPPROTO_ICMP);
		  }
  }
 // printf("xdxdxdxdxdxdxdx\n");
  // Source IPv4 address (32 bits)
  if ((status = inet_pton (AF_INET,src_ip, &(iphdr.ip_src))) != 1) {
    fprintf (stderr, "inet_pton() failed.\nError message: %s", strerror (status));
    exit (EXIT_FAILURE);
  }

  // Destination IPv4 address (32 bits)
  if ((status = inet_pton (AF_INET, dst_ip, &(iphdr.ip_dst))) != 1) {
    fprintf (stderr, "inet_pton() failed.\nError message: %s", strerror (status));
    exit (EXIT_FAILURE);
  }

  // IPv4 header checksum (16 bits): set to 0 when calculating checksum
  //printf("xdxdxdxdxdxdxdx\n");
    checksum_funkcja(&iphdr,IP4_HDRLEN );
    iphdr.ip_sum = checksum ((uint16_t *) &iphdr, IP4_HDRLEN);


  // ICMP header / wypełnic tą strukturę parametrami wybranymi z klawiatury


    //strcmp(protip,"IPPROTO_ICMP") != 0
  // Message Type (8 bits): echo request
   if(icmptyp==1)
   {
    type_icmp(&icmphdr,ICMP_ECHO);

   }

  // icmphdr.icmp_type = htons(ICMP_ECHO);

  // Message Code (8 bits): echo request
   if(icmptyp==1)
      {
       type_icmp2(&icmphdr,0);
      }


  // Identifier (16 bits): usually pid of sending process - pick a number

  icmphdr.icmp_id = htons (1000);

  // Sequence Number (16 bits): starts at 0
  icmphdr.icmp_seq = htons (0);

  // ICMP header checksum (16 bits): set to 0 when calculating checksum
  icmphdr.icmp_cksum = 0;

  // Prepare packet.

  // First part is an IPv4 header.
  memcpy (packet, &iphdr, IP4_HDRLEN);

  // Next part of packet is upper layer protocol header.
  memcpy ((packet + IP4_HDRLEN), &icmphdr, ICMP_HDRLEN);

  // Finally, add the ICMP data.
  memcpy (packet + IP4_HDRLEN + ICMP_HDRLEN, data, datalen);

  // Calculate ICMP header checksum
  icmphdr.icmp_cksum = checksum ((uint16_t *) (packet + IP4_HDRLEN), ICMP_HDRLEN + datalen);


  memcpy ((packet + IP4_HDRLEN), &icmphdr, ICMP_HDRLEN);

  // The kernel is going to prepare layer 2 information (ethernet frame header) for us.
  // For that, we need to specify a destination for the kernel in order for it
  // to decide where to send the raw datagram. We fill in a struct in_addr with
  // the desired destination IP address, and pass this structure to the sendto() function.
  memset (&sin, 0, sizeof (struct sockaddr_in));
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = iphdr.ip_dst.s_addr;

  // Submit request for a raw socket descriptor.
  if ((sd = socket (AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0) {
    perror ("socket() failed ");
    exit (EXIT_FAILURE);
  }

  // Set flag so socket expects us to provide IPv4 header.
  if (setsockopt (sd, IPPROTO_IP, IP_HDRINCL, &on, sizeof (on)) < 0) {
    perror ("setsockopt() failed to set IP_HDRINCL ");
    exit (EXIT_FAILURE);
  }

  // Bind socket to interface index.
  if (setsockopt (sd, SOL_SOCKET, SO_BINDTODEVICE, &ifr, sizeof (ifr)) < 0) {
    perror ("setsockopt() failed to bind to interface ");
    exit (EXIT_FAILURE);
  }


  // Send packet.
int ile;

if (wysylkaliczba==0 ){
	printf("Domyslnie wysle 1\n");
	if (sendto (sd, packet, IP4_HDRLEN + ICMP_HDRLEN + datalen, 0, (struct sockaddr *) &sin, sizeof (struct sockaddr)) < 0)  {
		    perror ("sendto() failed ");
		    exit (EXIT_FAILURE);
}}
else if(wysylkaliczba==1 && *ilerazy==1){
	if (sendto (sd, packet, IP4_HDRLEN + ICMP_HDRLEN + datalen, 0, (struct sockaddr *) &sin, sizeof (struct sockaddr)) < 0)  {
	    perror ("sendto() failed ");
	    exit (EXIT_FAILURE);
}}else
{
printf ("Ile razy powtórzyć : %d \n",ileraz);
for (ile = 0 ;ile < *ilerazy; ile++){

  if (sendto (sd, packet, IP4_HDRLEN + ICMP_HDRLEN + datalen, 0, (struct sockaddr *) &sin, sizeof (struct sockaddr)) < 0)  {
    perror ("sendto() failed ");
    exit (EXIT_FAILURE);

}}}
  // Close socket descriptor.
  close (sd);

  // Free allocated memory.
  free (data);
  free (packet);
  free (interface);
  free (target);
  free (src_ip);
  free (dst_ip);
  free (ip_flags);

  return (EXIT_SUCCESS);
}

// Computing the internet checksum (RFC 1071).
// Note that the internet checksum does not preclude collisions.


///// 1 przeniesiona ///////

//uint16_t checksum (uint16_t *addr, int len)
//{
//  int count = len;
//  register uint32_t sum = 0;
//  uint16_t answer = 0;
//
//  // Sum up 2-byte values until none or only one byte left.
//  while (count > 1) {
//    sum += *(addr++);
//    count -= 2;
//  }
//
//  // Add left-over byte, if any.
//  if (count > 0) {
//    sum += *(uint8_t *) addr;
//  }
//
//  // Fold 32-bit sum into 16 bits; we lose information by doing this,
//  // increasing the chances of a collision.
//  // sum = (lower 16 bits) + (upper 16 bits shifted right 16 bits)
//  while (sum >> 16) {
//    sum = (sum & 0xffff) + (sum >> 16);
//  }
//
//  // Checksum is one's compliment of sum.
//  answer = ~sum;
//
//  return (answer);
//}

/////// 2 przeniesiona /////////

// Allocate memory for an array of chars.
//char *
//allocate_strmem (int len)
//{
//  void *tmp;
//
//  if (len <= 0) {
//    fprintf (stderr, "ERROR: Cannot allocate memory because len = %i in allocate_strmem().\n", len);
//    exit (EXIT_FAILURE);
//  }
//
//  tmp = (char *) malloc (len * sizeof (char));
//  if (tmp != NULL) {
//    memset (tmp, 0, len * sizeof (char));
//    return (tmp);
//  } else {
//    fprintf (stderr, "ERROR: Cannot allocate memory for array allocate_strmem().\n");
//    exit (EXIT_FAILURE);
//  }
//}

// Allocate memory for an array of unsigned chars.
//uint8_t *
//allocate_ustrmem (int len)
//{
//  void *tmp;
//
//  if (len <= 0) {
//    fprintf (stderr, "ERROR: Cannot allocate memory because len = %i in allocate_ustrmem().\n", len);
//    exit (EXIT_FAILURE);
//  }
//
//  tmp = (uint8_t *) malloc (len * sizeof (uint8_t));
//  if (tmp != NULL) {
//    memset (tmp, 0, len * sizeof (uint8_t));
//    return (tmp);
//  } else {
//    fprintf (stderr, "ERROR: Cannot allocate memory for array allocate_ustrmem().\n");
//    exit (EXIT_FAILURE);
//  }
//}
//
//// Allocate memory for an array of ints.
//int *
//allocate_intmem (int len)
//{
//  void *tmp;
//
//  if (len <= 0) {
//    fprintf (stderr, "ERROR: Cannot allocate memory because len = %i in allocate_intmem().\n", len);
//    exit (EXIT_FAILURE);
//  }
//
//  tmp = (int *) malloc (len * sizeof (int));
//  if (tmp != NULL) {
//    memset (tmp, 0, len * sizeof (int));
//    return (tmp);
//  } else {
//    fprintf (stderr, "ERROR: Cannot allocate memory for array allocate_intmem().\n");
//    exit (EXIT_FAILURE);
//  }
//}

