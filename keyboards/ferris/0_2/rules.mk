CUSTOM_MATRIX = lite

SRC += matrix.c
I2C_DRIVER_REQUIRED = yes

COMBO_ENABLE = yes

# this is caused by a bug - no idea why this is needed only in my code - see readme
EXTRAINCDIRS += $(CHIBIOS)/os/oslib/include

