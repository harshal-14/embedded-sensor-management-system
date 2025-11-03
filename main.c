#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

//Enum for sensor types
// what is enum?
// enum is a user defined data type that consists of a set of constants
// it is used to define a set of constants with a common name and a value

typedef enum{
    TEMPERATURE,
    HUMIDITY,
    PRESSURE
}SensorType;

//Enum for sensor status
typedef enum{
    ACTIVE,
    INACTIVE,
    ERROR
}SensorStatus;


// what is union?
// union is a user defined data type that consists of a set of constants and variables that share the same memory location
// it is used to store different data types in the same memory location
// it is used to save memory and improve performance
// it is used to store different data types in the same memory location
typedef union{
    struct{
        short int min_range; // Temperature range min in celsius
        shortfloat reading; // Temperature reading in celsius
    }temperature;

    struct{
        float calibration; // Humidity calibration factor
        float reading; // Humidity reading in percentage latest
    }humidity;

    struct{
        short int altitude; // Altitude in meters
        float reading; // Latest reading
    }pressure;
}SensorData;

// struct for sensor
typedef struct{
    unsigned char id;
    char name[20];
    SensorType type;
    SensorStatus 
}