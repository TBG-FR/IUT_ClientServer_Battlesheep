
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
| R_ER | 212 | Connection error : Incorrect password |




- `JOIN room_id/server_port/...` : connection request (to a specified room/server)
