#pragma once
/* ===== ===== ===== */
/* ===== ===== ===== */
#define USER_REGISTRATION_SUCCESS_ALLOWED				= 100;
#define USER_REGISTRATION_SUCCESS_SUCCESSFUL			= 101;
/* ----- ----- ----- */
#define USER_REGISTRATION_ERROR_COMMON_UNKNOWN			= 200;
#define USER_REGISTRATION_ERROR_NOT_ALLOWED				= 201;
#define USER_REGISTRATION_ERROR_USERNAME_ALREADY_TAKEN	= 202;
#define USER_REGISTRATION_ERROR_INVALID_PASSWORD		= 203;
#define USER_REGISTRATION_ERROR_INCORRECT_PASSWORD		= 204;
/* ===== ===== ===== */
/* ===== ===== ===== */
#define USER_CONNECTION_SUCCESS_CONNECTION_ALLOWED		= 110;
#define USER_CONNECTION_SUCCESS_LOGIN_CORRECT			= 111;
#define USER_CONNECTION_SUCCESS_PASSWORD_CORRECT		= 112;
#define USER_CONNECTION_SUCCESS_CONNECTION_SUCCESSFUL	= 113;
/* ----- ----- ----- */
#define USER_CONNECTION_ERROR_COMMON_UNKNOWN			= 210;
#define USER_CONNECTION_ERROR_CONNECTION_NOT_ALLOWED	= 211;
#define USER_CONNECTION_ERROR_UNKNOWN_HOST				= 212;
#define USER_CONNECTION_ERROR_UNKNOWN_USERNAME			= 213;
#define USER_CONNECTION_ERROR_INCORRECT_PASSWORD		= 214;
/* ===== ===== ===== */
/* ===== ===== ===== */
#define GAME_CREATION_SUCCESS_GAME_CREATED              = 120;
/* ----- ----- ----- */
#define GAME_CREATION_ERROR_COMMON_UNKNOWN              = 220;
#define GAME_CREATION_ERROR_ALREADY_INGAME              = 221
/* ===== ===== ===== */
/* ===== ===== ===== */
#define SIZE_DEFINITION_SUCCESS_SIZE_DEFINED            = 130;
/* ----- ----- ----- */
#define SIZE_DEFINITION_ERROR_COMMON_UNKNOWN            = 230;
#define SIZE_DEFINITION_ERROR_TOO_SMALL                 = 231;
#define SIZE_DEFINITION_ERROR_INTEGERS_REQUIRED         = 232;
/* ===== ===== ===== */
/* ===== ===== ===== */