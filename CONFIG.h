#ifndef CONFIG__
#define CONFIG__

#define SYSCLOCK 16000000
#define WIIFREQ 400
#define PUCKFREQ 5
#define PI 3.14


#define RXADDRESS 0x60
#define CHANNEL 1
#define PACKET_LENGTH 10

#define MAX_WIDTH 1024
#define MAX_HEIGHT 768
#define CENTER_X 512
#define CENTER_Y 384

#define GAMETIME 1	//full court and systems
#define AIM_EAST 0	//use localization to detremine team
#define TEAM_SW 1	//use switch to determine team
#define BLUETEAM 0

#define DEBUG_ON 0
#define TEST_FWD 0
#define TEST_BKD 0
#define TEST_TURN 0
#define TEST_RUN 0
#define TEST_SENSORS 0
#define RESET 0
#define FIND_CTR 0
#define QUALIFYING 0
#define JUSTGO 0
#define NEED_WII 0
#define NEED_COMM 1



#endif