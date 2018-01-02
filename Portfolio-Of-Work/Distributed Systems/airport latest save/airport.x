const MAXLEN =255;
typedef string nametype_air<MAXLEN>;

/* a node in the directory list*/
struct AirportNode{
		nametype_air AirportName;
		nametype_air AirportCode;
		double latitude;
		double longitude;
		double distance;
		AirportNode* next;
};

struct geoCord{
	double latitude;
	double longitude;
};

/*result of a readdir operation*/
union findAirport_ret switch(int err){
	case 0:
		AirportNode* list; /*no error, return airport listing*/
	default:
		void; /* error occured nothing returned*/
};

/*IDL program*/
program AIRPROG{
	version AIR_VERS{
		findAirport_ret FINDAIR(geoCord*) = 1;
	} = 1;
} = 0x34567881;