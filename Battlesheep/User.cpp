#include "User.h"

User::User()
{
	/* TODO */
}

User::User(string login, string pass)
{
	username = login;
	password = pass;
}

User::~User()
{
	/* TODO */
}

string User::getUsername()
{
	return username;
}

string User::getPassword()
{
	return password;
}