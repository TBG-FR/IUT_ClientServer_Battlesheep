
// "InstanceOf"
// https://stackoverflow.com/questions/500493/c-equivalent-of-instanceof
// usage: if (instanceof<BaseClass>(ptr)) { ... }
template<typename Base, typename T>
inline bool instanceof(const T*) { return std::is_base_of<Base, T>::value; }

// Custom stoi (string to int) function (no exception, positive values on success, -1 on fail)
// https://stackoverflow.com/questions/7663709/convert-string-to-int-c
// https://stackoverflow.com/questions/2844817/how-do-i-check-if-a-c-string-is-an-int
int stoi_noex(string s) {

    try {

        int i = stoi(s);
        return i;

    }
    
    catch ( const std::exception & Exp )  {

        //std::cerr << "[ERR] : " << Exp.what() << ".\n";

    }

    //return NULL;
    return -1;

}

// stog (string to grid) function (0 for success, negatives values for errors)
// Grid format example : L.0.0.1.1.0.0.0.L.1.0.0.0.0.0.1.L.1.0.0.0.0.0.1.L.0.0.0.0.0.0.1
// equals : 0 0 1 1 0 0 0
//          1 0 0 0 0 0 1
//          1 0 0 0 0 0 1
//          0 0 0 0 0 0 1
int stog(string s) {

    // TODO;

}

int grid_check(int* grid, int dim1, int dim2) {

    // TODO
    // Verif 1 = Count(0) + Count(1) = dim1 * dim2
    // Verif 2 = Count(1) = nb_bots_cases (= (dim1 * dim2) * 0.2 ?)
    // Verif 3 = Placement
    
    return 0;
    
    /*
                    switch(grid_check) {

                    case 0: // Correct Grid
                        server_return(GAME_INITIALIZATION_SUCCESS_CORRECT_GRIDS);
                        game_status == INGAME;
                        break;

                    case -1: // Invalid number of boats
                        server_return(GAME_INITIALIZATION_ERROR_INVALID_NUMBER);
                        break;

                    case -2: // Invalid boat placement
                        server_return(GAME_INITIALIZATION_ERROR_INVALID_PLACEMENT);
                        break;

                    default: // Other answer
                        server_return(GAME_INITIALIZATION_ERROR_COMMON_UNKNOWN);
                        break;
                        */

}

// Other tools have their place here