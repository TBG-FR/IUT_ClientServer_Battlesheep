#ifndef BATTLESHIP_MESSAGES

 // Temporaire : évite de gérer l'arrivée des joueurs et la gestion des "rôles"
 // (joueur qui souhaite créer une partie, joueur qui souhaite rejoindre)
#define TEMP_CONN_PLAYER_ONE 888
#define TEMP_CONN_PLAYER_TWO 999
/* ===== ===== ===== */
/* ===== ===== ===== */
#define USER_REGISTRATION_SUCCESS_ALLOWED			    100
#define USER_REGISTRATION_SUCCESS_SUCCESSFUL		    101
/* ----- ----- ----- */
#define USER_REGISTRATION_ERROR_COMMON_UNKNOWN		    200
#define USER_REGISTRATION_ERROR_NOT_ALLOWED			    201
#define USER_REGISTRATION_ERROR_USERNAME_ALREADY_TAKEN  202
#define USER_REGISTRATION_ERROR_INVALID_PASSWORD	    203
#define USER_REGISTRATION_ERROR_INCORRECT_PASSWORD	    204
/* ===== ===== ===== */
/* ===== ===== ===== */
#define USER_CONNECTION_SUCCESS_CONNECTION_ALLOWED		110
#define USER_CONNECTION_SUCCESS_LOGIN_CORRECT			111
#define USER_CONNECTION_SUCCESS_PASSWORD_CORRECT		112
#define USER_CONNECTION_SUCCESS_CONNECTION_SUCCESSFUL	113
/* ----- ----- ----- */
#define USER_CONNECTION_ERROR_COMMON_UNKNOWN			210
#define USER_CONNECTION_ERROR_CONNECTION_NOT_ALLOWED	211
#define USER_CONNECTION_ERROR_UNKNOWN_HOST				212
#define USER_CONNECTION_ERROR_UNKNOWN_USERNAME			213
#define USER_CONNECTION_ERROR_INCORRECT_PASSWORD		214
/* ===== ===== ===== */
/* ===== ===== ===== */
#define GAME_CREATION_SUCCESS_GAME_CREATED              120
/* ----- ----- ----- */
#define GAME_CREATION_ERROR_COMMON_UNKNOWN              220
#define GAME_CREATION_ERROR_ALREADY_INGAME              221
/* ===== ===== ===== */
/* ===== ===== ===== */
#define SIZE_DEFINITION_SUCCESS_SIZE_DEFINED            130
/* ----- ----- ----- */
#define SIZE_DEFINITION_ERROR_COMMON_UNKNOWN            230
#define SIZE_DEFINITION_ERROR_TOO_SMALL                 231
#define SIZE_DEFINITION_ERROR_INTEGERS_REQUIRED         232
/* ===== ===== ===== */
/* ===== ===== ===== */
#define GAME_INITIALIZATION_SUCCESS_SECOND_PLAYER		140
#define GAME_INITIALIZATION_SUCCESS_CORRECT_GRID		141
#define GAME_INITIALIZATION_SUCCESS_CORRECT_GRIDS		142
/* ----- ----- ----- */
#define GAME_INITIALIZATION_ERROR_COMMON_UNKNOWN		240
#define GAME_INITIALIZATION_ERROR_WAITING_PLAYER		241
#define GAME_INITIALIZATION_ERROR_INVALID_NUMBER        242
#define GAME_INITIALIZATION_ERROR_INVALID_PLACEMENT     243
/* ===== ===== ===== */
/* ===== ===== ===== */
#define GAME_PLAY_SUCCESS_TURN_PLAYED                   150
#define GAME_PLAY_SUCCESS_SHOT_EMPTYCELL                151
#define GAME_PLAY_SUCCESS_SHOT_BOATCELL                 152
#define GAME_PLAY_SUCCESS_SHOT_ALREADYCELL              153
/* ----- ----- ----- */
#define GAME_PLAY_ERROR_COMMON_UNKNOWN                  250
#define GAME_PLAY_ERROR_ENEMY_TURN                      251
#define GAME_PLAY_ERROR_OUTSIDE_BOUNDS                  252
/* ===== ===== ===== */
/* ===== ===== ===== */
#define GAME_QUIT_SUCCESS_LEAVING_ROOM                  180
#define GAME_QUIT_SUCCESS_ENDING_GAME                   181
/* ----- ----- ----- */
#define GAME_QUIT_ERROR_COMMON_UNKNOWN                  280
#define GAME_QUIT_ERROR_CURRENTLY_PLAYING               281
/* ===== ===== ===== */
/* ===== ===== ===== */
#define SERVER_DISCON_SUCCESS_DISCON_OK                 190
/* ----- ----- ----- */
#define SERVER_DISCON_ERROR_COMMON_UNKNOWN              290
#define SERVER_DISCON_ERROR_CURRENTLY_PLAYING           291
/* ===== ===== ===== */
/* ===== ===== ===== */

#endif