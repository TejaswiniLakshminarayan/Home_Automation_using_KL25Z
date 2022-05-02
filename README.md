# Home Automation using KL25Z

![home](https://user-images.githubusercontent.com/90485608/166335294-7f47bd77-e583-401d-9b6f-a092cd2c0ea2.png)


## Objective
The objective of this project is to create a home automation system with KL25Z. The home automation system will allow the user to interact through command prompt 
with the device, pass commands to control various parts of the home.

## Requirements
### Hardware Requirements
1. KL25Z
2. SHT21 sensor
3. Intefacing KL25Z with SHT21
### Software Requirements
1. Implementing an interactive command prompt for the user to provide inputs
2. Configuring capacitive touch sensor to change the LED intensity
3. Maintaining the system state machine when the device is running
4. Using the KL25Z timer module to track schedules given by the user to turn on or turn off the LED
5. Using PWM to control the LEDs on KL25Z
6. Implementing communication between SHT21 and KL25Z using I2C
7. Reading temperature and humidity from SHT21

## Project Concept
The KL25Z development board comes with LEDs on-board. An SHT21 temperature and humidity sensor will be interfaced with the KL25Z through I2C. The primary goal of 
this project is to create a simple home automation system. The user can input commands to board and the board is going to take that input, process it and provide 
an appropriate action or an output. The user can give the below commands and the response to the commands as follows
- **Turn on light** - Turns on the LED. The color of the LED is initially set to white with an intensity of 25%. 
                  A turn on light command while the light is already on gives a response saying the light is already on
- **Turn off light** - Turns off the LED. A turn off light command while the light is already on gives a response saying the light is already off 
- **Change light color** - This input gives an user to choose the colors from Red, Blue, Green, White. Based on the given color input, the LED changes its color. In                              case of unknown color, it prompts the user to that the color is unknown and cannot change the color.
- **Change light intensity** - This input informs the user to use the touch slider to change the light intensity. Based on the input to the touch slider
                               The percentage change in the intesnity(in terms of percentage) is informed to the user
- **Set light timer** - This input informs the user about the current state of LED (if the LED is on or off) and then prompt the user to set a timer value in seconds
                        (seconds are used for the demo purpose. This can be extended to minutes and hours)
- **What is the temperature** - This gives the temperature and humidity values on the command prompt.
- **unsupported command** - In case of user inputting an unsupported command, the reponse would be "I'm sorry. I do not understand that command. Would you like to do                               something else? Type help to know more about supported commands"
- **help** - This provides all the supported commands.

The results from this project demonstrates a basic functionality of home automation and this system can be expanded further to realize bigger products such as the Alexa and Google assistant devices.

## Functionalities
Some of the core concepts and functionalities used are:
- UART controller
- Command processor
- Interrupt Handling
- Timer functionality
- PWM
- I2C
- Circular buffers
- State Machine
- GPIO lines
- Testing

## Hardware Setup
Below is the hardware setup. PTE0 is connected to SDA and PTE1 is connected to SCL
![kl25z_board](https://user-images.githubusercontent.com/90485608/166333677-4764cb55-4060-46be-9ba6-c28b240c6d0f.png)

![SHT1](https://user-images.githubusercontent.com/90485608/166333965-3ad2aa61-4e8c-4231-8dd1-edee5a1605a5.png)

![sht2](https://user-images.githubusercontent.com/90485608/166334172-3b803c89-5eed-4a1a-baed-388ae8f969c3.png)


## Testing Strategy
### Automated Tests
Function test_cbfifo() ensures the correctness the circular buffer for various corner cases.
### Manual Testing
I have used the manual tests to verify the below functionality
1. Temperature and Humidity sensor
- Room Temperature
![room_temp_humidity](https://user-images.githubusercontent.com/90485608/166187574-fbce347e-77e1-4c41-8b0f-861a159a2704.png)


- Using Hairdryer
![hair_dryer](https://user-images.githubusercontent.com/90485608/166170423-b4869eff-037a-451b-8d03-0e047a054783.png)


- Using Cooling Fan
![cooling_fan](https://user-images.githubusercontent.com/90485608/166170436-9760b6f5-f638-47d3-aa86-31b2e94f3e35.png)


2. Testing LEDs for different intensities. (Some of the intensities aren't very well reproduced on phone Camera)
- RED LED
- Red at 25% intensity
![RED_25](https://user-images.githubusercontent.com/90485608/166173123-25fcf990-1a24-424b-aa51-73be326e8994.jpg)

- Red at 50% intensity
![RED_50](https://user-images.githubusercontent.com/90485608/166173129-52f7c879-7b73-4b6f-81af-2c13a73097d4.jpg)

- Red at 100% intensity
![RED_100](https://user-images.githubusercontent.com/90485608/166173135-b3111800-01b3-403f-81e0-f941321c8beb.jpeg)

- GREEN LED
- Green at 25% intensity
![GREEN_25](https://user-images.githubusercontent.com/90485608/166173622-50e301b3-f9ec-4c7b-ad0e-3386896bc33d.jpg)

- Green at 75% intensity
![GREEN_75](https://user-images.githubusercontent.com/90485608/166173625-825e7f8e-bd18-4c86-a20f-1114119a27ee.jpg)

- Green at 100% intensity
![GREEN_100](https://user-images.githubusercontent.com/90485608/166174763-1c5b7df6-5198-4bc9-b7e4-c2fd07cd1bc8.jpg)

- BLUE LED
- Blue at 25%
![BLUE_25](https://user-images.githubusercontent.com/90485608/166174540-24701b39-6fb5-424c-a2a8-2e446bc23629.jpg)

- Blue at 50%
![BLUE_50](https://user-images.githubusercontent.com/90485608/166174541-53f6342f-0ddc-4678-8da7-0953bfaa9480.jpg)

- Blue at 75%
![BLUE_75](https://user-images.githubusercontent.com/90485608/166174543-ff38914d-29b0-4a92-8b85-c6f84b6acf1e.jpg)

- Blue at 100%
![20220501_172441](https://user-images.githubusercontent.com/90485608/166174820-f595a47a-fed3-47c1-802e-4b24eafef4e6.jpg)

- White LED
- White at 75%
![WHITE_25](https://user-images.githubusercontent.com/90485608/166175190-b53d4e1a-fab3-4287-8f54-3a4d44e3d947.jpg)

- White at 50%
![WHITE_75](https://user-images.githubusercontent.com/90485608/166175192-a79d1399-8b90-4dd6-8702-393e8f1c5d82.jpg)

### Complete Functional test
The below functional test screenshot of the command window demonstrates all the functionalities
![Main_complete_functionality](https://user-images.githubusercontent.com/90485608/166189319-7d773595-e4dd-45b0-a5e3-233ca2cfba93.png)

## Development Environment
MCUXpresso IDE Version 11.2.0
## How to run
- Enable the floating point operation in the project settings.
- Set the Baud rate for UART0 to 115200 and stop bit as 1 as shown below
![baud](https://user-images.githubusercontent.com/90485608/166180844-8ab047cc-9892-4a6d-acd5-dcf385b72fc8.png)

## Video Link
https://drive.google.com/file/d/1GImlCSKYZLN1jSd458Iao5LcMUiMhDVm/view?usp=sharing 

## References
1. https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code
2. https://www.farnell.com/datasheets/1780639.pdf

