#include <stdint.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

uint64_t Pow10(uint8_t power);
uint8_t GetNumber(int64_t x, uint64_t exp);
int64_t Invert(int64_t x, uint64_t exp);

int main()
{
    uint8_t found_vertical = FALSE;
    uint8_t zero_found = 0;
    uint8_t first_zero = TRUE;
    uint8_t sign = FALSE;

    char buffer;
    
    
    unsigned before_point_value = 0;
    unsigned after_point_value = 0;
    unsigned point = 1;
    
    while((buffer = getchar()) != EOF && buffer != '\n' && buffer != '\0')
    {
        switch(buffer)
        {
        case '-':
            if(point == 1)
            {
                sign = TRUE;
            }
            else
            {
                printf("Input error.\n");
                exit(-1);
            }
        case ' ':
            break;
        case '|':
            if(!found_vertical)
            {
                found_vertical = TRUE;
                before_point_value = Invert(before_point_value, point / 10);
                point = 1;
            }
            else
            {
                printf("Input error. Found second vertical.\n");
                exit(-1);
            }
        case '0':
            if(found_vertical && first_zero)
            {
                zero_found++;
            }
            break;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            if(found_vertical && first_zero)
            {
                first_zero = FALSE;
            }
            if(!found_vertical)
            {
                before_point_value += (buffer - '0') * point;
                point *= 10;
            }
            else
            {
                after_point_value += (buffer - '0') * point;
                point *= 10;
            }
            break;
        default:
            printf("Input error.\n");
            exit(-1);
        }
        if(point % 10 && point != 1)
        {
            printf("Input error. Input is high.\n");
            exit(-1);
        }
    }
    
    if(!found_vertical)
    {
        printf("Input error. Vertical not found.\n");
        exit(-1);   
    }
    
    after_point_value = Invert(after_point_value, point / 10);
    
    double value =
        (double)before_point_value +
        (double)after_point_value / (double)point / (double)Pow10(zero_found - 1);
    
    if(sign)
    {
        value *= -1;
    }
    
    printf("%lf\n", value);
}

int64_t Invert(int64_t x, uint64_t exp)
{
    int64_t r_x = 0;
    uint64_t p = 1;
    
    for(uint64_t e = exp; e > 0; e /= 10)
    {
        r_x += GetNumber(x, e) * p;
        p *= 10;
    }
    
    return r_x;
}

uint8_t GetNumber(int64_t x, uint64_t exp)
{
    if(x < 0)
    {
        x *= -1;
    }
    if(exp == 0)
    {
        return 0;
    }
    return (x / exp) % 10;
}

uint64_t Pow10(uint8_t power)
{
    uint64_t x = 1;
    for(uint8_t p = 0; p < power; p++)
    {
        x *= 10;
    }
    return x;
}






























