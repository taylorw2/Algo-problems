/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "places.h"

void
placeprog_1(char *host,char * city, char * state)
{
	CLIENT *clnt;
	findPlace_ret  *result_1;
	cityNode  findplace_1_arg;
	AirportNode_places ** temp;

#ifndef	DEBUG
	clnt = clnt_create (host, PLACEPROG, PLACE_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */
	findplace_1_arg.city = city;
	findplace_1_arg.state = state;
	printf("%s \n" , findplace_1_arg.city);
	printf("%s \n", findplace_1_arg.state);
	result_1 = findplace_1(&findplace_1_arg, clnt);
	if (result_1 == (findPlace_ret *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	temp = &result_1->findPlace_ret_u.list;
	printf("%s  \n", (*temp)->AirportName);
	printf("%s  \n", (*temp)->AirportCode);
	printf("%f  \n", (*temp)->latitude);
	printf("%f  \n", (*temp)->longitude);
	printf("%f  \n", (*temp)->distance);
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	char * city = argv[2];
	char * state = argv[3];
	placeprog_1 (host,city,state);
exit (0);
}
