#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>

#define SERVERPORT 9000
#define BUFSIZE    512

//board
#define BOARD_SIZE 5
//#define BACKLOG 3
int server_board[BOARD_SIZE][BOARD_SIZE]; //서버 보드판 배열
int client_board[BOARD_SIZE][BOARD_SIZE]; //클라이언트 보드판 배열
int check_number[BOARD_SIZE*BOARD_SIZE+1]={0}; //중복검사용 배열
int server_fd, client_fd; //소켓 파일디스크립터
int turn[4]; //어플리케이션 프로토콜 정의

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
void sockSetting(){
          int retval;

      // 윈속 초기화
      WSADATA wsa;
      if(WSAStartup(MAKEWORD(2,2), &wsa) != 0)
            return 1;

      // socket()
      SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
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
      SOCKET client_sock;
      SOCKADDR_IN clientaddr;
      int addrlen;
      char buf[BUFSIZE+1];

            // accept()
            addrlen = sizeof(clientaddr);
            client_sock = accept(listen_sock, (SOCKADDR *)&clientaddr, &addrlen);
            if(client_sock == INVALID_SOCKET)
            {
                  err_display("accept()");
            }

            // 접속한 클라이언트 정보 출력
            printf("\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n",
                   inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
}
void serverGameInit(){
    int check_number[BOARD_SIZE*BOARD_SIZE]={0};    //remove same number
    int i,j;
    srand(time(NULL)); //time random

	for(i=0; i < BOARD_SIZE; i++){
		for(j=0; j < BOARD_SIZE; j++){
			while(1){
				int temp = rand()%25; // random 0~24

				if(check_number[temp]==0){//중복제거 알고리즘
					check_number[temp]=1;
					server_board[i][j]=temp+1;
					break;
				}
			}
		}
	}
}

void clientGameInit(){
    int check_number[BOARD_SIZE*BOARD_SIZE]={0};
	int i, j;
	int array_len;

	srand(time(NULL)+100); //서버 보드판과 다르게 하기위해 100을 추가

	for(i=0; i < BOARD_SIZE; i++)
	{
		for(j=0; j < BOARD_SIZE; j++)
		{
			while(1)
			{
				int temp = rand()%25; //0~24 난수 발생

				if(check_number[temp]==0) //중복제거 알고리즘
				{
					check_number[temp]=1;
					client_board[i][j]=temp+1;
					break;
				}
			}
		}
	}
	array_len = write(client_fd, client_board, sizeof(client_board));
	printf("%d 바이트를 전송하였습니다\n", array_len);
	err_display("send()");
	//error_check(array_len, "데이터전송");
}

void gamePrint(int turn_count)
{
	int i, j;

	system("clear"); //동적 효과를 위한 화면 초기화
	printf("%c[1;33m",27); //터미널 글자색을 노랑색으로 변경

	printf("@------   서버   ------@\n");
	printf("진행 턴수: %d\n", turn_count);
	printf("+----+----+----+----+----+\n");
	for(i=0; i < BOARD_SIZE; i++)
	{
		for(j=0; j < BOARD_SIZE; j++)
		{
			if(server_board[i][j]==0)
			{
				printf("| ");
				printf("%c[1;31m",27);
				printf("%2c ", 88);
				printf("%c[1;33m",27);
			}
			else
				printf("| %2d ", server_board[i][j]);
		}
		printf("|\n");
		printf("+----+----+----+----+----+\n");
	}
	printf("%c[0m", 27); //터미널 글자색을 원래색으로 변경
}

int bingo_check(int board[][BOARD_SIZE])
{
	int i;
	int count=0;

	for(i=0; i < BOARD_SIZE; i++) //가로
	{
		if(board[i][0]==0&&board[i][1]==0&&board[i][2]==0&&board[i][3]==0&&board[i][4]==0) //가로
		{
			count++;
		}
		if(board[0][i]==0&&board[1][i]==0&&board[2][i]==0&&board[3][i]==0&&board[4][i]==0) //세로
			count++;
	}
	if(board[0][0]==0&&board[1][1]==0&&board[2][2]==0&&board[3][3]==0&&board[4][4]==0)
		count++;
	if(board[0][4]==0&&board[1][3]==0&&board[2][2]==0&&board[3][1]==0&&board[4][0]==0)
		count++;
	return count;
}
void board_X(int board[][BOARD_SIZE], int number)
{
	int i, j;

	for(i=0; i < BOARD_SIZE; i++)
	{
		for(j=0; j < BOARD_SIZE; j++)
		{
			if(board[i][j]==number)
				board[i][j]=0; //X표 처리
		}
	}
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
	game_run();

	array_len=write(client_fd, turn, sizeof(turn));
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

		recv_count=read(client_fd, turn, sizeof(turn));
		err_display("recv()");
		//error_check(recv_count, "데이터수신");
		if(recv_count==0) break;
		printf("%d 바이트: 클라이언트의 턴 정보를 수신하였습니다\n", recv_count);
		recv_len+=recv_count;
	}
	game_run();
	check_number[turn[0]]=1;

	array_len=write(client_fd, turn, sizeof(turn));
	printf("%d 바이트: 클라이언트의 턴 정보를 전송하였습니다\n", array_len);
	err_display("send");
//	error_check(array_len, "데이터전송");
}
void game_run()
{
	board_X(server_board, turn[0]);
	board_X(client_board, turn[0]);
	turn[1]=bingo_check(client_board);
	turn[2]=bingo_check(server_board);

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
    sockSetting(SERVERPORT);
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
		if(i%2==1)
			client_turn();
		else
		{
			Sleep(1000); //대전을 체감하기위한 1초의 딜레이
			server_turn();
		}

		gamePrint(i);
		for(j=0;j<4;j++) printf("turn[%d]=%d\n", j, turn[j]); //디버깅용
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

	closesocket(client_fd);
	closesocket(server_fd);

	printf("game over\n");

    return 0;
}
