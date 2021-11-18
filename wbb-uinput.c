/*
* Emulates a controller with the inputs of the Wii Balance Board
* No drivers or other programs needed!!!
*
* Connect the Wii Balance Board via Bluetooth
* If the blue light stays on it's connected
* Use ls /dev/input to find out which one the board is
* It should be the /dev/input/event* with the highest number
* Compile and run this file with the path specified in stdin
* Use antimicrox or other programs to configure the inputs
*
* Modified code from https://github.com/keldu/WiiWeight
* and https://github.com/GrantEdwards/uinput-joystick-demo
*/

#include <fcntl.h>
#include <linux/uinput.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static void setup_abs(int fdw, unsigned chan, int min, int max);

struct weight_values
{
	int fr, fl, br, bl;
} weight;

static int x, y;

void setWeight(int co, int val)
{
	switch(co){
	case ABS_HAT0X: weight.fr = val; break;
	case ABS_HAT1X: weight.fl = val; break;
	case ABS_HAT0Y: weight.br = val; break;
	case ABS_HAT1Y: weight.bl = val; break;
	}
	
	x=((weight.fr+weight.br)-(weight.fl+weight.bl))*0.1; /* set x axis multiplier */
	y=((weight.bl+weight.br)-(weight.fl+weight.fr))*0.1; /* set y axis multiplier */
}

int main(int argc, char** argv)
{
	char* input_device=NULL;
	int fdr, bytes;
	struct input_event evr;
	struct input_event evw[8];
	memset(&evw, 0, sizeof evw);

	if (argc<2){
		printf("Missing device path! Specify path. /dev/input/event*\n");
		return 1;
	}

	input_device=argv[1];
	fdr=open(input_device, O_RDONLY);

	if (fdr<0){
		perror("Failed to open device! Correct path?\n");
		return 1;
	}

	int fdw = open("/dev/uinput", O_WRONLY | O_NONBLOCK);

	if (fdw < 0) {
		perror("open /dev/uinput");
		return 1;
	}

	ioctl(fdw, UI_SET_EVBIT, EV_ABS);

	setup_abs(fdw, ABS_X,    -512,   512);
	setup_abs(fdw, ABS_Y,    -512,   512);
	setup_abs(fdw, ABS_Z,  -32767, 32767);

	struct uinput_setup setup = {
		.name = "Userspace Joystick",
		.id = {
			.bustype = BUS_USB,
			.vendor  = 0x3,
			.product = 0x3,
			.version = 2,
		}
	};

	if (ioctl(fdw, UI_DEV_SETUP, &setup)) {
		perror("UI_DEV_SETUP");
		return 1;
	}

	if (ioctl(fdw, UI_DEV_CREATE)) {
		perror("UI_DEV_CREATE");
		return 1;
	}

	while (1) {
		bytes=read(fdr, &evr, sizeof(struct input_event));

		if (evr.type==EV_ABS){
			setWeight(evr.code, evr.value);
			printf("x %d\ny %d\n", x, y); /* not needed, comment out if you want */
		}

		evw[4].type  = EV_ABS;
		evw[4].code  = ABS_Y;
		evw[4].value = y;

		evw[5].type  = EV_ABS;
		evw[5].code  = ABS_X;
		evw[5].value = x;

		evw[7].type  = EV_SYN;
		evw[7].code  = SYN_REPORT;
		evw[7].value = 0;

		if (write(fdw, &evw, sizeof evw) < 0) {
			perror("write");
			return 1;
		}
	}

	if (ioctl(fdw, UI_DEV_DESTROY)) {
		perror("UI_DEV_DESTROY");
		return 1;
	}
	
	close(fdw);
	return 0;
}

static void setup_abs(int fd, unsigned chan, int min, int max)
{
	if (ioctl(fd, UI_SET_ABSBIT, chan))
		perror("UI_SET_ABSBIT");

	struct uinput_abs_setup s = {
		.code = chan,
		.absinfo = {
			.minimum = min,
			.maximum = max
		}
	};

	if (ioctl(fd, UI_ABS_SETUP, &s))
		perror("UI_ABS_SETUP");
}
