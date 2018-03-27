#include "Server.cpp"
#include "Client.cpp"

using namespace std;

int main(int argc, char *argv[]) {

    srand(time(NULL));

    cout << "Lancement..." << endl;

    if(argv[1] == "server") {

        Server server = Server();

    }

    else if(argv[1] == "client") {

        Client client = Client();

    }

    else {

        cout << "Vous devez entrer \"client\" ou \"server\" comme premier argument !" << endl;

        return EXIT_FAILURE;

    }

    return EXIT_SUCCESS;

}
