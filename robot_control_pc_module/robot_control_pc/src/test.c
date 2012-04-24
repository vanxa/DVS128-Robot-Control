#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include </usr/include/ncurses.h>
#include <stdlib.h>
#include <zig_control.h>
#include <zigbee.h>

typedef uint16_t uint16;

int main()
{
	char input;
    uint16 command;
    init_keyboard();
    printf("This is a command assemble test...");
    refresh();
    while(1)
    {
        printf("Send a command: w(Move Forward), s(Move Backward), "
                "a(Turn Forward Left), d(Turn Forward Right),"
                "z(Turn Backward Left), x(Turn Backward Right), "
                "q(Quit), c(Cancel last command), "
                "y(Check Robot Status)\r\n");
        refresh();

        input = wgetch(stdscr);

        if(input == 'q')
        {
            printf("Quitting...\n");
            refresh();
            break;
        }
        else if(input == 'c')
        {
            printf("CANCEL.\r\n");
            refresh();
            command = assemble16(0,0,0);
            printf("The command is: %u\r\n",command);
        }
        else if(input == 'y')
        {
            printf("STATUS \r\n");
            refresh();
            command = assemble16(0,0,0);
            printf("The command is: %u\r\n",command);
        }
        else
        {
            printf("Command: %c\r\n",input);
            uint16 cmd = input;
            switch(input)
            {
              case 'w':
                cmd = 1;
                break;
              case 's':
                cmd = 2;
                break;
              case 'a':
                cmd = 3;
                break;
              case 'd':
                cmd = 4;
                break;
              case 'z':
                cmd = 5;
                break;
              case 'x':
                cmd = 6;
                break;
             }
            uint16 speed = 0;
            uint16 time = 0;
            while(!speed)
            {
                printf("Now, enter movement speed value:\r\n1(40),\r\n2(80),"
                        "\r\n3(120),\r\n4(200),\r\n5(450),\r\n6(600),\r\n7(760),\r\n8(900),\r\n9(1023)\r\n");
                refresh();
                input = wgetch(stdscr);
                uint16 temp = atoi(&input);
                switch(temp)
                {
                    case 1:
                        speed=40;
                        break;
                    case 2:
                        speed=80;
                        break;
                    case 3:
                        speed=120;
                        break;
                    case 4:
                        speed=200;
                        break;
                    case 5:
                        speed=450;
                        break;
                    case 6:
                        speed=600;
                        break;
                    case 7:
                        speed=760;
                        break;
                        case 8:
                        speed=900;
                        break;
                    case 9:
                        speed=1023;
                        break;
                    default:
                        speed=0;
                        break;
                }
            }
            while(!time)
            {
                printf("Now, enter time for execution of command:\r\n1(1),\r\n2(2),"
                                            "\r\n3(3),\r\n4(4),\r\n5(5),\r\n6(6),\r\n7(7),\r\n8(8),\r\n9(9)\r\n");
                refresh();
                input = wgetch(stdscr);
                uint16 temp = atoi(&input);
                if(1 <= temp && temp <=9)
                    time = temp;
                else
                    time = 0;
            }
            printf("Command is: %d; speed is: %d; time is: %d\r\n", cmd, speed, time);
            printf("Sending...\r\n");
            refresh();
            command = assemble16(time, speed, cmd);
            printf("Output is: %d\r\nSize: %d\r\n", command, sizeof(command));
            refresh();
        }
    }

endwin();

return 0;
}
