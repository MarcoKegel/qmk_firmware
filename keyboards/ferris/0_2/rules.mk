CUSTOM_MATRIX = lite

SRC += matrix.c
I2C_DRIVER_REQUIRED = yes
#DEFAULT_FOLDER = ferris/0_2/base
#TAP_DANCE_ENABLE = yes

# this is caused by a bug - no idea why this is needed only in my code - see readme
EXTRAINCDIRS += $(CHIBIOS)/os/oslib/include

