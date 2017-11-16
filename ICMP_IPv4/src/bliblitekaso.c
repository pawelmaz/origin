/*
 * bliblitekaso.c
 *
 *  Created on: 11 lis 2017
 *      Author: pawel
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



uint16_t checksum (uint16_t *addr, int len)
{
  int count = len;
  register uint32_t sum = 0;
  uint16_t answer = 0;

  // Sum up 2-byte values until none or only one byte left.
  while (count > 1) {
    sum += *(addr++);
    count -= 2;
  }

  // Add left-over byte, if any.
  if (count > 0) {
    sum += *(uint8_t *) addr;
  }

  // Fold 32-bit sum into 16 bits; we lose information by doing this,
  // increasing the chances of a collision.
  // sum = (lower 16 bits) + (upper 16 bits shifted right 16 bits)
  while (sum >> 16) {
    sum = (sum & 0xffff) + (sum >> 16);
  }

  // Checksum is one's compliment of sum.
  answer = ~sum;

  return (answer);
}
////////////////////////////

void Set_Source_Addr(char * src_ip, char * zipfile)
{
	  strcpy (src_ip, zipfile);
}

void Set_Dest_Addr(char * target, char * ifile)
{
	  strcpy (target, ifile);
}
void IPv4_Header_Set_Version(struct ip *iphdr,char *bipwers)
{
	iphdr->ip_v =*bipwers;

}
void IPv4_Header_Set_Version2(struct ip *iphdr)
{
	iphdr->ip_v =4;
}

void Type_of_service(struct ip *iphdr, int zero)
{
	iphdr->ip_tos = zero;
}

void ID_sequence_number(struct ip *iphdr, int zero)
{
	iphdr->ip_id = htons (zero);
}

void IPv4_length(struct ip *iphdr ,char *wsdlip)
{
	iphdr->ip_hl = *wsdlip/ sizeof (uint32_t);
}
void IPv4_length2(struct ip *iphdr )
{
	iphdr->ip_hl = 20 / sizeof (uint32_t);
}

void ttl2(struct ip *iphdr, int dwadwa)
{
	iphdr->ip_ttl = dwadwa;
}

void ttl(struct ip *iphdr, int ttlint)
{
	iphdr->ip_ttl = ttlint;
}

void transport_icmp_proto2(struct ip *iphdr,char tablica)
{
	iphdr->ip_p = tablica;
}

void checksum_funkcja(struct ip *iphdr,int zero)
{
	iphdr->ip_sum = zero;
}


void type_icmp(struct icmp *icmphdr,char *icmptyp)
{
	icmphdr->icmp_type = *icmptyp;

}
void type_icmp2(struct icmp *icmphdr,char *icmptyp)
{
	icmphdr->icmp_code = 0;

}
//icmphdr.icmp_code = 0;


//////////////////////////////////////////////////////////////////////////////////////////////////





char *
allocate_strmem (int len)
{
  void *tmp;

  if (len <= 0) {
    fprintf (stderr, "ERROR: Cannot allocate memory because len = %i in allocate_strmem().\n", len);
    exit (EXIT_FAILURE);
  }

  tmp = (char *) malloc (len * sizeof (char));
  if (tmp != NULL) {
    memset (tmp, 0, len * sizeof (char));
    return (tmp);
  } else {
    fprintf (stderr, "ERROR: Cannot allocate memory for array allocate_strmem().\n");
    exit (EXIT_FAILURE);
  }
}


uint8_t *
allocate_ustrmem (int len)
{
  void *tmp;

  if (len <= 0) {
    fprintf (stderr, "ERROR: Cannot allocate memory because len = %i in allocate_ustrmem().\n", len);
    exit (EXIT_FAILURE);
  }

  tmp = (uint8_t *) malloc (len * sizeof (uint8_t));
  if (tmp != NULL) {
    memset (tmp, 0, len * sizeof (uint8_t));
    return (tmp);
  } else {
    fprintf (stderr, "ERROR: Cannot allocate memory for array allocate_ustrmem().\n");
    exit (EXIT_FAILURE);
  }
}

// Allocate memory for an array of ints.
int *
allocate_intmem (int len)
{
  void *tmp;

  if (len <= 0) {
    fprintf (stderr, "ERROR: Cannot allocate memory because len = %i in allocate_intmem().\n", len);
    exit (EXIT_FAILURE);
  }

  tmp = (int *) malloc (len * sizeof (int));
  if (tmp != NULL) {
    memset (tmp, 0, len * sizeof (int));
    return (tmp);
  } else {
    fprintf (stderr, "ERROR: Cannot allocate memory for array allocate_intmem().\n");
    exit (EXIT_FAILURE);
  }
}

///////////////////////////////////////////////////////////////////////




