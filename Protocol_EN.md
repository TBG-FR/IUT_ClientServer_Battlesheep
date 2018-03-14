
# 'BatailleNavale' - Protocol [EN]

## 1. Connection & Authentification

### 1.1.1 Registration [Client Requests]
- `REG1 username password` : registering request
- `REG2 username password` : registering second-step (password verification)

### 1.1.2 Registration [Server Responses]

| HEADER | CODE | MESSAGE |
| ------ | ------ | ------ |
| R_OK | 100 | Registration allowed, please confirm |
| R_OK | 101 | Registration successful |
|  |  |  |
| R_ER | 200 | Registration error : COMMON/UNKNOWN |
| R_ER | 201 | Registration not allowed |
| R_ER | 202 | Registration error : Username already taken |
| R_ER | 203 | Registration error : Incorrect Password (too weak ?) |

### 1.2.1 Connection/Auth [Client Requests]
- `CONN` : connection request  
- `USER login` : client given login
- `PASS password` : client given password

### 1.2.2 Connection/Auth [Server Responses]

| HEADER | CODE | MESSAGE |
| ------ | ------ | ------ |
| R_OK | 110 | Connection allowed, please login |
| R_OK | 111 | Correct login, please auth |
| R_OK | 112 | Correct password, connection |
| R_OK | 113 | Connection successful |
|  |  |  |
| R_ER | 210 | Connection error : COMMON/UNKNOWN |
| R_ER | 211 | Connection not allowed |
| R_ER | 212 | Connection error : Unknown username |
| R_ER | 213 | Connection error : Incorrect password |

## 2. Game management - Begin

### 2.1.1 Game creation [Client Requests]
- `GNEW public` : creation of a new public game (room)
- `GNEW private identity_player2` : creation of a new private game (room)

### 2.1.2 Game creation [Server Responses]

| HEADER | CODE | MESSAGE |
| ------ | ------ | ------ |
| R_OK | 120 | Game created |
|  |  |  |
| R_ER | 220 | Game creation error : COMMON/UNKNOWN |
| R_ER | 221 | Game creation error : Already in a game |

### 2.2.1 Grid size defition [Client Requests]
- `SIZE dim1 dim2` : define the size of the game grid

### 2.2.2 Grid size definition [Server Responses]

| HEADER | CODE | MESSAGE |
| ------ | ------ | ------ |
| R_OK | 130 | Correct size, now waiting for second player |
|  |  |  |
| R_ER | 230 | Size definition error : COMMON/UNKNOWN |
| R_ER | 231 | Size definition error : Size too small |
| R_ER | 232 | Size definition error : Integers required |

### 2.3.1 Game initialization [Client Requests]
- `GRID grid_filled` : send player's game grid filled with boats

### 2.3.2 Game initialization [Server Responses]

| HEADER | CODE | MESSAGE |
| ------ | ------ | ------ |
| R_OK | 140 | Second player joined, waiting for players' grids |
| R_OK | 141 | Correct grid, launching game |
|  |  |  |
| R_ER | 240 | Game initialization error : COMMON/UNKNOWN |
| R_ER | 241 | Game initialization error : Still waiting for a second player |
| R_ER | 242 | Game initialization error : Invalid number of boats |
| R_ER | 242 | Game initialization error : Invalid placement of boats |

## 3. Gameplay

### 3.1.1 Play Turn [Client Requests]
- `PLAY dim1 dim2` : shoot on the given cell

### 3.1.2 Play Turn [Server Responses]

| HEADER | CODE | MESSAGE |
| ------ | ------ | ------ |
| R_OK | 150 | Turn played with success |
| R_OK | 151 | Shot fired on an empty cell |
| R_OK | 152 | Shot fired on an boat cell |
| R_OK | 153 | Shot fired on an already-shot boat cell |
|  |  |  |
| R_ER | 250 | Turn play error : COMMON/UNKNOWN |
| R_ER | 251 | Turn play error : Not your turn |
| R_ER | 252 | Turn play error : Out of grid |

### 3.1.3 Play Turn [Server Requests]
- `CASE dim1 dim2` : informs the player that the given cell has been shot
- `TURN` : informs the player that it's now his turn

### 3.2.1 End of Game [Client Requests]
*Nothing*

### 3.2.2 End of Game [Server Responses]
*Nothing* *16X & 26X*

### 3.2.3 End of Game [Server Requests]
- `GEND nb_turns` : informs the player that the game ended (with the number of turns)
- `GWIN` : informs the player that he won
- `GLOS` : informs the player that he lose

### 3.3.1 Play Again [Client Requests]
*TODO : RESTART, RESET, REPLAY ?*

### 3.3.2 Play Again [Server Responses]

| HEADER | CODE | MESSAGE |
| ------ | ------ | ------ |
| R_OK | 170 | *TODO* |
| R_OK | 171 | *TODO* |
| R_OK | 172 | *TODO* |
| R_OK | 173 | *TODO* |
|  |  |  |
| R_ER | 270 | *TODO* error : COMMON/UNKNOWN |
| R_ER | 271 | *TODO* error : *TODO* |
| R_ER | 272 | *TODO* : *TODO* |

### 3.2.3 Play Again [Server Requests]
*TODO*
_________________________________________________

## 4. Quit & Disconnect

### 4.1.1 Quitting Game [Client Requests]
- `QUIT` : request to quit the game
- `QIT2` : second step for quitting a game while playing

### 4.1.2 Quitting Game [Server Responses]

| HEADER | CODE | MESSAGE |
| ------ | ------ | ------ |
| R_OK | 180 | Quitting game : Success, leaving room |
| R_OK | 181 | Quitting game while playing... Ending game |
|  |  |  |
| R_ER | 280 | Quitting game error : COMMON/UNKNOWN |
| R_ER | 281 | Quitting game error : Currently playing, use QIT2 |

### 4.1.3 Quitting Game [Server Requests]
- `GQIT` : informs the player that the other player left the game

### 4.2.1 Disconnection [Client Requests]
- `EXIT` : request to disconnect properly from the server

### 4.2.2 Disconnection [Server Responses]

| HEADER | CODE | MESSAGE |
| ------ | ------ | ------ |
| R_OK | 190 | Disconnection... Bye ! |
|  |  |  |
| R_ER | 290 | Disconnection error : COMMON/UNKNOWN |
| R_ER | 291 | Disconnection error : Currently playing, use QUIT |
