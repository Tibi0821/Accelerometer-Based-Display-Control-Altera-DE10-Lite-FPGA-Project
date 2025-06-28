#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <altera_up_avalon_accelerometer_spi.h>
#include <alt_types.h>
#include <altera_avalon_pio_regs.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

alt_up_accelerometer_spi_dev* accelerometer_device = NULL;

#define TURN_ON_UP_LEDS 0x9C
#define TURN_ON_DOWN_LEDS 0xA3
#define HEX_BASE_ADDR  HEX_0_BASE
#define HEX_OFFSET     0x10

#define UP_LEDS 1
#define DOWN_LEDS 0

#define TURN_OFF 0xFF
#define TURN_ON 0x80

uint32_t* get_hex_address(int hex_index)
{
    return (uint32_t*)(HEX_BASE_ADDR + hex_index * HEX_OFFSET);
}

void set_hex_circle(alt_u8 position, alt_u8 hex_index) {
    if (position)
    {
        IOWR_ALTERA_AVALON_PIO_DATA(get_hex_address(hex_index), TURN_ON_UP_LEDS);
    }
    else
    {
        IOWR_ALTERA_AVALON_PIO_DATA(get_hex_address(hex_index), TURN_ON_DOWN_LEDS);
    }
}

void set_hex_value(alt_u8 value, alt_u8 hex_index)
{
    IOWR_ALTERA_AVALON_PIO_DATA(get_hex_address(hex_index), value);
}

void hex_init(uint32_t hexState)
{
    for (int i = 0; i < 6; i++)
    {
        IOWR_ALTERA_AVALON_PIO_DATA(get_hex_address(i), hexState);
    }
}

// Functie pentru calculul si afisarea unghiului
void display_angle_in_terminal(alt_32 x, alt_32 y)
{
    float angle = atan2((float)y, (float)x) * (180.0 / M_PI); // Calcularea unghiului in grade
    printf("Unghiul de inclinare: %.2f deg\n", angle);
}

// Functie pentru detectarea directiei de miscare
void detect_movement_direction(alt_32 x, alt_32 y)
{
    if (y > 0)
        printf("Directie: Sus\n");
    else if (y < 0)
        printf("Directie: Jos\n");

    if (x > 0)
        printf("Directie: Dreapta\n");
    else if (x < 0)
        printf("Directie: Stanga\n");
}

int main()
{
    printf("Accelerometer Application Using Altera DE10 Lite\r\n");
    hex_init(TURN_OFF);
    accelerometer_device = alt_up_accelerometer_spi_open_dev("/dev/accelerometer_spi_0");

    alt_32 x, y;
    alt_32 y_inclination = 89;

    while (1)
    {
        // Citirea valorilor brute de la accelerometru
        alt_up_accelerometer_spi_read_x_axis(accelerometer_device, &x);
        alt_up_accelerometer_spi_read_y_axis(accelerometer_device, &y);

        // Afisarea unghiului in terminal
        display_angle_in_terminal(x, y);

        // Detectarea directiei de miscare
        if (y > y_inclination)
        {
            printf("Directie: Sus\n");
        }
        else if (y < -y_inclination)
        {
            printf("Directie: Jos\n");
        }
        else
        {
            printf("Pozitie: Mijloc\n"); // Adaugam afisare pentru cazul „mijloc”
        }

        // Calcularea pozitiei cercului pe matricea HEX
        x = (x * 6) / (2 * 86);
        x += 2;
        x = (x < 0) ? 0 : (x >= 6) ? 5 : x;

        // Controlul LED-urilor pe baza valorilor
        if (y > y_inclination)
        {
            set_hex_value(TURN_ON_DOWN_LEDS, x);
        }
        else if (y < -y_inclination)
        {
            set_hex_value(TURN_ON_UP_LEDS, x);
        }
        else
        {
            set_hex_value(0xBF, x); // Liniuta pentru pozitia mijloc
        }

        // Dezactivarea LED-urilor neutilizate
        for (int i = 0; i < 6; i++)
        {
            if (i != x)
            {
                set_hex_value(0xFF, i);
            }
        }

        usleep(10000); // Pauza pentru actualizare (10 ms)
    }

    return 0;
}
