#include <stdio.h>
#include <string.h>
#include <unistd.h> //UART
#include <fcntl.h> //UART
#include <termios.h> //UART

#define DEV 1

int configureUART0(int* uart0_Handle) {
  *uart0_Handle = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY);
  printf("Handle = %d\n", *uart0_Handle);

  if(*uart0_Handle == -1) {
    printf("Unable to open UART #0\n");
    return -1;
  } else {
    printf("UART #0 openning succesful!!\n");
  }

  struct termios options;
  tcgetattr(*uart0_Handle, &options);
  options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
  options.c_iflag = IGNPAR;
  options.c_oflag = 0;
  options.c_lflag = 0;
  tcflush(*uart0_Handle, TCIFLUSH);
  tcsetattr(*uart0_Handle, TCSANOW, &options);

  return 0; 
}

int transmitData(int* uart0_Handle, char* tx_data, int tx_length) {
  if(*uart0_Handle != -1) {
    int count = write(*uart0_Handle, tx_data, tx_length);
    if(count > 0) {
      printf("Send succesful!\n");
      printf("Sent %d characters\n", count);
      return 0;
    } else {
      printf("Tx error\n");
      return -1;
    }
  }
}

int receiveData(int* uart0_Handle,char* rx_data, int* rx_length, int blockMode ) {
  if(*uart0_Handle != -1) {
    if(blockMode) {
      *rx_length = 0;
      while(*rx_length <= 0) {
	printf("Waiting...\n");
	*rx_length = read(*uart0_Handle, rx_data, 255);
	printf("waiting...\n");
	usleep(1000000);
      }
    } else {
      *rx_length = read(*uart0_Handle, rx_data, 255);
    }
    printf("Characters received: %d\n", *rx_length);
    if(*rx_length > 0) {
      char* aux = rx_data;
      aux += *rx_length;
      *aux = '\0';
      printf("Data received= %s\n", rx_data);
      return 0;
    }
  }
  return -1;
}

int main() {
  int result;
  char exitCode[] = "N";
  char userInput[256];
  char rx_data[256];
  int uart0_Handle = -1;
  int rx_length;

  if(!(configureUART0(&uart0_Handle))) {
    printf("Configuration of UART0 succesful!!\n");
    while(1) {
      result = receiveData(&uart0_Handle, &rx_data[0], &rx_length, 1);
    }
    close(uart0_Handle);
  }
  return 0;
}
