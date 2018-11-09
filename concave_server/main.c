#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#define SERVERPORT 9000
#define BOARD_SIZE 8

int server_board[BOARD_SIZE][BOARD_SIZE];
int client_board[BOARD_SIZE][BOARD_SIZE];
int check_number[BOARD_SIZE*BOARD_SIZE+1]={0}; // �ߺ� �˻�

SOCKET listen_sock;
SOCKET client_sock;
int turn[4];

// ���� �Լ� ���� ��� �� ����
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

// ���� �Լ� ���� ���
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

int recvn(Socket s, char *buf, int len, int flags)
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
    // ���� �ʱ�ȭ
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

    // ������ ��ſ� ����� ����
    SOCKADDR_IN clientaddr;
    int addrlen;
    char buf[BUFSIZE+1];

    // accept()
    addrlen = sizeof(clientaddr);
    client_sock = accept(listen_sock, (SOCKADDR *)&clientaddr, &addrlen);
    if(client_sock == INVALID_SOCKET){err_display("accept()");}

    // ������ Ŭ���̾�Ʈ ���� ���
    printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
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

                if(check_number[temp]==0){ //�ߺ� ����
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
    srand(time(NULL)+100);

    for (i=0;i<BOARD_SIZE;i++){
        for(j=0;j<BOARD_SIZE;j++){
            while(1){
                int temp = rand()%(BOARD_SIZE*BOARD_SIZE);

                if(check_number[temp]==0){ //�ߺ� ����
                    check_number[temp]=1;
                    client_board[i][j]=temp+1;
                    break;
                }
            }
        }
    }
    array_len = send(client_sock,(char *)&client_board,sizeof(client_board),0);
	printf("%d ����Ʈ�� �����Ͽ����ϴ�\n", array_len);
	err_display("send()");
}

void gamePrint(int turn_count){

}
int main()
{
    printf("Hello world!\n");
    return 0;
}
