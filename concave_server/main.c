#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <Windows.h>


#define SERVERPORT 9000
#define BOARD_SIZE 10

int server_board[BOARD_SIZE][BOARD_SIZE];
int client_board[BOARD_SIZE][BOARD_SIZE];
int check_number[BOARD_SIZE*BOARD_SIZE+1]={0}; // 중복 검사

SOCKET listen_sock;
SOCKET client_sock;
int turn[4];

void Gotoxy(int x, int y) {
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	return;
}

// 소켓 함수 오류 출력 후 종료
void err_quit(char *msg)
{
      LPVOID lpMsgBuf;
      FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
            NULL, WSAGetLastError(),
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPTSTR)&lpMsgBuf, 0, NULL);
      MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
      LocalFree(lpMsgBuf);
      exit(1);
}

// 소켓 함수 오류 출력
void err_display(char *msg)
{
      LPVOID lpMsgBuf;
      FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
            NULL, WSAGetLastError(),
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPTSTR)&lpMsgBuf, 0, NULL);
      printf("[%s] %s", msg, (char *)lpMsgBuf);
      LocalFree(lpMsgBuf);
}

int recvn(SOCKET s, char *buf, int len, int flags)
{
      int received;
      char *ptr = buf;
      int left = len;
      while(left > 0)
      {
            received = recv(s, ptr, left, flags);
            if(received == SOCKET_ERROR)
                  return SOCKET_ERROR;
            else if(received == 0)
                  break;
            left -= received;
            ptr += received;
      }
      return (len - left);
}

void socket_setting(){
    int retval;
    // 윈속 초기화
    WSADATA wsa;
    if(WSAStartup(MAKEWORD(2,2), &wsa) != 0)
        return -1;

    // socket()
    listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(listen_sock == INVALID_SOCKET)
        err_quit("socket()");

    // bind()
    SOCKADDR_IN serveraddr;
    ZeroMemory(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(SERVERPORT);
    retval = bind(listen_sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
    if(retval == SOCKET_ERROR)
          err_quit("bind()");

    // listen()
    retval = listen(listen_sock, SOMAXCONN);
    if(retval == SOCKET_ERROR)
          err_quit("listen()");

    // 데이터 통신에 사용할 변수
    SOCKADDR_IN clientaddr;
    int addrlen;

    // accept()
    addrlen = sizeof(clientaddr);
    client_sock = accept(listen_sock, (SOCKADDR *)&clientaddr, &addrlen);
    if(client_sock == INVALID_SOCKET){err_display("accept()");}

    // 접속한 클라이언트 정보 출력
    printf("\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n",
    inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
}

void serverGameInit(){
    int check_number[BOARD_SIZE*BOARD_SIZE] ={0};
    int i,j;
    srand(time(NULL));

    for (i=0;i<BOARD_SIZE;i++){
        for(j=0;j<BOARD_SIZE;j++){
            while(1){
                int temp = rand()%(BOARD_SIZE*BOARD_SIZE);

                if(check_number[temp]==0){ //중복 제거
                    check_number[temp]=1;
                    server_board[i][j]=temp+1;
                    break;
                }
            }
        }
    }
}

void clientGameInit(){
    int check_number[BOARD_SIZE*BOARD_SIZE] ={0};
    int i,j;
    int array_len;
    srand(time(NULL)+100);

    for (i=0;i<BOARD_SIZE;i++){
        for(j=0;j<BOARD_SIZE;j++){
            while(1){
                int temp = rand()%(BOARD_SIZE*BOARD_SIZE);

                if(check_number[temp]==0){ //중복 제거
                    check_number[temp]=1;
                    client_board[i][j]=temp+1;
                    break;
                }
            }
        }
    }
    array_len = send(client_sock,(char *)&client_board,sizeof(client_board),0);
	printf("%d 바이트를 전송하였습니다\n", array_len);
	err_display("send()");
}

void gamePrint(int turn_count){
    system("cls");
        int i, j;
        unsigned char a = 0xa6;
        unsigned char b[12];

        printf("------ server ------\n");
        printf("turn: %d\n", turn_count);
	printf("┌");	//위쪽
	for (int j = 0; j <26; j++) {
		printf("┬");
	}
	printf("┐\n");

	for (int i = 0; i < 25; i++) {	//가운데
		printf("├");
		for (int j = 0; j < 26; j++) {
			printf("┼");
		}
		printf("┤\n");
	}
	printf("└");	//마지막 줄
	for (int j = 0; j < 26; j++) {
		printf("┴");
	}
	printf("┘");

	for (i =0; i <BOARD_SIZE;i++){
        for(j =0;j<BOARD_SIZE;j++)
        if(server_board[i][j]==0){
            //printf("SERVER_BOARD %d,%d :",i,j);
            Gotoxy(i,j);
            printf("●");	//흑돌 출력
            Gotoxy(0,BOARD_SIZE);
            }
	}
}

int concave_check(int board[BOARD_SIZE][BOARD_SIZE])
{
    printf("concave_check()함수 호출");
    return 0;
}

void server_turn()
{
	int array_len;

	while(1)
	{
		turn[0]=rand()%25+1;
		if(check_number[turn[0]]==0)
		{
			check_number[turn[0]]=1;
			break;
		}
	}
	printf("here\n");
	game_run();

	array_len = send(client_sock,(char*)&turn,sizeof(turn),0);
	//array_len=write(client_fd, turn, sizeof(turn));

	printf("%d 바이트: 서버의 턴 정보를 전송하였습니다\n", array_len);
	err_display("send()");
	//error_check(array_len, "데이터전송");
}

void client_turn()
{
	int recv_len=0, array_len;

	while(recv_len!=sizeof(turn)) // 패킷이 잘려서 올수도 있으므로 예외처리를 위한 조건문
	{
		int recv_count;

        recv_count = recv(client_sock,(char *)&turn,sizeof(turn),0);
		err_display("recv()");
		if(recv_count==0) break;
		printf("%d 바이트: 클라이언트의 턴 정보를 수신하였습니다\n", recv_count);
		recv_len+=recv_count;
	}
	game_run();
	check_number[turn[0]]=1;

	array_len = send(client_sock,(char *)&turn,sizeof(turn),0);

	printf("%d 바이트: 클라이언트의 턴 정보를 전송하였습니다\n", array_len);
	err_display("send");
}

void board_black(int board[][BOARD_SIZE], int number)
{
	int i, j;

	for(i=0; i < BOARD_SIZE; i++)
	{
		for(j=0; j < BOARD_SIZE; j++)
		{
			if(board[i][j]==number)
				board[i][j]=0;
		}
	}
}

void game_run()
{
	board_black(server_board, turn[0]);
	board_black(client_board, turn[0]);
	turn[1]=concave_check(client_board);
	turn[2]=concave_check(server_board);

	if(turn[1]>=5&&turn[2]>=5)
		turn[3]=3; //무승부
	else if(turn[1]>=5)
		turn[3]=1; //클라이언트 승리
	else if(turn[2]>=5)
		turn[3]=2; //서버 승리
}

int main()
{
    int i,j;
    //sock setting
    socket_setting(SERVERPORT);
    printf("success create socket !");
    // server game init
    serverGameInit();
    // client game inot
    clientGameInit();
    // game print
    gamePrint(0);
    // terning
    for(i=1;i<=BOARD_SIZE*BOARD_SIZE;i++)
	{
	    printf("i :%d\n",i);
		if(i%2==1)
			client_turn();
		else
		{
			Sleep(1000); //대전을 체감하기위한 1초의 딜레이
			server_turn();
		}

		gamePrint(i);
		//for(j=0;j<4;j++) printf("turn[%d]=%d\n", j, turn[j]); //디버깅용
		if(turn[3]==1)
		{
			printf("클라이언트 승리\n");
			break;
		}
		else if(turn[3]==2)
		{
			printf("서버 승리\n");
			break;
		}
		else if(turn[3]==3)
		{
			printf("무승부\n");
			break;
		}
	}

	closesocket(client_sock);
	closesocket(listen_sock);

    WSACleanup();
	printf("game over\n");

    return 0;
}
