#ifndef BATTLESHIP_REQUESTS

enum ClientRequests {

	REG1,	// REG1 username password
	REG2,	// REG2 username password
	CONN,	// CONN (ip?)
	USER,	// USER login
	PASS,	// PASS password
	GNEW,	// GNEW public || GNEW private identity_p2
	SIZE,	// SIZE dim1 dim2
	GRID,	// GRID grid_filled
	PLAY,	// PLAY dim1 dim2
	QUIT,	// QUIT
	QIT2,	// QIT2
	EXIT,	// EXIT
	//...

};


enum ServerRequests {

	INFO,	// INFO dim1 dim2
	TURN,	// TURN
	GEND,	// GEND nb_turns_played
	GWIN,	// GWIN
	GLOS,	// GLOS
	GQIT,	// GQIT
	//...

};

#endif