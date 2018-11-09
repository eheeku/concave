#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <string.h>
#include <unistd.h>

#define SERVERIP "127.0.0.1"
#define SERVERPORT 9000

#define BOARD_SIZE 10

SOCKET sock;

int board[BOARD_SIZE][BOARD_SIZE]; //보드판 배열
int check_number[BOARD_SIZE*BOARD_SIZE+1]={0}; //중복검사용 배열
//int socket_fd; //소켓 파일디스크립터
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
int recvn(SOCKET s, char *buf, int len, int flags)
{
	int received;
	char *ptr = buf;
	int left = len;

	while(left > 0){
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
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == INVALID_SOCKET) err_quit("socket()");

	// connect()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if(retval == SOCKET_ERROR) err_quit("connect()");

}

int value_check(int number) //점수 유효값 검사
{
	if(number<1||number>25||check_number[number]==1)
	{
		printf("값이 유효하지 않습니다. 다시입력해주세요 : ");
		scanf("%d", &number);
		number=value_check(number); //유효값 입력할때까지 재귀호출
	}
	return number;
}

void gameInit()
{
	int recv_len, recv_count;

	recv_len=0;

	while(recv_len!=sizeof(board))
	{
	    recv_count = recv(sock,(char*)&board,sizeof(board),0);
		if(recv_count== -0)
            break;
		printf("%d 바이트: board를 수신하였습니다\n", recv_count);
		recv_len += recv_count;
	}
	printf("out loop");
	return;
}
void gamePrint(int number, int turn_count){
        int i, j;
        unsigned char a = 0xa6;
        unsigned char b[12];

        printf("------ server ------\n");
        printf("turn: %d\n", turn_count);

        for (i = 1; i < 12; i++)
               b[i] = 0xa0 + i;
        printf("%c%c", a, b[3]);

        for (i = 0; i < BOARD_SIZE - 1; i++)
               printf("%c%c", a, b[8]);
        printf("%c%c", a, b[4]);
        printf("\n");

        for (i = 0; i < BOARD_SIZE - 1; i++)
        {
               printf("%c%c", a, b[7]);
               for (j = 0; j < BOARD_SIZE - 1; j++)
                       printf("%c%c", a, b[11]);
               printf("%c%c", a, b[9]);
               printf("\n");
        }

        printf("%c%c", a, b[6]);

        for (i = 0; i < BOARD_SIZE - 1; i++)
               printf("%c%c", a, b[10]);
        printf("%c%c", a, b[5]);
        printf("\n");

}

void server_turn()
{
	int recv_len=0;

	while(recv_len!=sizeof(turn)) // 패킷이 잘려서 올수도 있으므로 예외처리를 위한 조건문
	{
		int recv_count;

		recv_count= recv(sock,(char*)&turn,sizeof(turn),0);
		err_display("recv()");
		if(recv_count==0) break;
		printf("%d 바이트: 서버의 턴 정보를 수신하였습니다\n", recv_count);
		recv_len+=recv_count;
	}
	check_number[turn[0]]=1;
}

void client_turn(int turn_count)
{
	int array_len, recv_len=0;;

	printf("%d턴 숫자를 입력해주세요 : ", turn_count);
	scanf("%d", &turn[0]);
	turn[0]=value_check(turn[0]);
	check_number[turn[0]]=1;

	array_len = send(sock,(char*)&turn,sizeof(turn),0);
	printf("%d 바이트: 클라이언트의 턴 정보를 전송하였습니다\n", array_len);
	err_display("send()");

	while(recv_len!=sizeof(turn))
	{
		int recv_count;

		recv_count=recv(sock,(char*)&turn,sizeof(turn),0);
		err_display("recv()");
		if(recv_count==0) break;
		printf("%d 바이트: 서버의 턴 정보를 수신하였습니다\n", recv_count);
		recv_len+=recv_count;
	}
}

int main()
{
    int i;

	socket_setting();

	printf("게임을 시작합니다.\n");
	gameInit();
	gamePrint(0, 0);
	for(i=1;i<BOARD_SIZE*BOARD_SIZE;i++)
	{
		if(i%2==1)
			client_turn(i);
		else
			server_turn();

		gamePrint(turn[0], i);

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
	closesocket(sock);
	WSACleanup();

	printf("game over\n");
}
