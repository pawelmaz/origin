/*
 * bibliotekahe.h
 *
 *  Created on: 11 lis 2017
 *      Author: pawel
 */

#ifndef BIBLIOTEKAHE_H_
#define BIBLIOTEKAHE_H_


uint16_t checksum (uint16_t *addr, int len);
char *
allocate_strmem (int len);
uint8_t *
allocate_ustrmem (int len);
int *
allocate_intmem (int len);


void Set_Source_Addr(char *,char *);
void Set_Dest_Addr(char *,char *);
void IPv4_Header_Set_Version(struct ip *,char *);
void IPv4_Header_Set_Version2(struct ip *);
void Type_of_service(struct ip *, int);
void ID_sequence_number(struct ip *, int );
void IPv4_length(struct ip *,char *);
void IPv4_length2(struct ip *);
void ttl2(struct ip *,int );
void ttl(struct ip *,int );
void transport_icmp_proto2(struct ip *,char );
void transport_icmp_proto(struct ip *,char *);
void checksum_funkcja(struct ip *,int);
void type_icmp(struct icmp *,char *);
void type_icmp2(struct icmp *,char *);


#endif /* BIBLIOTEKAHE_H_ */
