#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#define SERVERPORT 9000
#define BOARD_SIZE 8

int server_board[BOARD_SIZE][BOARD_SIZE];
int client_board[BOARD_SIZE][BOARD_SIZE];
int check_number[BOARD_SIZE*BOARD_SIZE+1]={0}; // 중복 검사

SOCKET listen_sock;
SOCKET client_sock;
int turn[4];

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

int main()
{
    printf("Hello world!\n");
    return 0;
}
