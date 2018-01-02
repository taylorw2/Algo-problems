const MAXLEN =255;
typedef string nametype<MAXLEN>;

/* a node in the directory list*/
struct AirportNode_places{
		nametype AirportName;
		nametype AirportCode;
		double latitude;
		double longitude;
		double distance;
		AirportNode_places* next;
};

struct cityNode{
	nametype state;   
	nametype city;
};



/*result of a */
union findPlace_ret switch(int err){
	case 0:
		AirportNode_places* list; /*no error, return airport listing*/
	default:
		void; /* error occured nothing returned*/
};

/*IDL program*/
program PLACEPROG{
	version PLACE_VERS{
		findPlace_ret FINDPLACE(cityNode*) = 1;
	} = 1;
} = 0x34567880;