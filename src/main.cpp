#include <Arduino.h>
#include "IO.h"
#include "CShiftRegisterOutputExtender.h"
#include <STM32FreeRTOS.h>
#include <HardwareTimer.h>

#define SPEED 0.2

IO DS0(PA8);
IO SH_CP0(PA9);
IO DS1(PB3);
IO SH_CP1(PB4);

IO ST_CP(PA10);

// timer for output enagle
HardwareTimer *magtimer = new HardwareTimer(TIM2); // Select the appropriate timer for your pin

CShiftRegisterOutputExtender reg0(&DS0, &SH_CP0, &ST_CP);
CShiftRegisterOutputExtender reg1(&DS1, &SH_CP1, &ST_CP);

IO leftButton(PB8);
IO rightButton(PB9);
IO AButton(PB10);
IO BButton(PB12);

struct Position
{
  int x;
  int y;

  Position() : x(0), y(0) {}                         // Default constructor initializing x and y to 0
  Position(int xPos, int yPos) : x(xPos), y(yPos) {} // constructor
  // Equality operator to compare two Position objects
  bool operator==(const Position &other) const
  {
    return (x == other.x) && (y == other.y);
  }
};

bool Field[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
};
void drawField(void *parameter)
{
  while (true)
  {
    for (int row = 0; row < 8; row++)
    {
      int colresult = 0;
      for (int i = 0; i < 8; ++i)
      {
        colresult |= (Field[row][i] << (7 - i)); // Shift the bit into position and OR with result
      }
      reg1 = colresult;
      reg0 = 0xFF ^ (1 << row);
      reg0.updateOutput();

      vTaskDelay(1);
    }
  }
}
void clearfield()
{
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      Field[i][j] = 0;
    }
  }
}

//txt
unsigned char LetterA[] = {B00000000, B00111100, B01100110, B01100110, B01111110, B01100110, B01100110, B01100110};
unsigned char LetterB[] = {B01111000, B01001000, B01001000, B01110000, B01001000, B01000100, B01000100, B01111100};
unsigned char LetterC[] = {B00000000, B00011110, B00100000, B01000000, B01000000, B01000000, B00100000, B00011110};
unsigned char LetterD[] = {B00000000, B00111000, B00100100, B00100010, B00100010, B00100100, B00111000, B00000000};
unsigned char LetterE[] = {B00000000, B00111100, B00100000, B00111000, B00100000, B00100000, B00111100, B00000000};
unsigned char LetterF[] = {B00000000, B00111100, B00100000, B00111000, B00100000, B00100000, B00100000, B00000000};
unsigned char LetterG[] = {B00000000, B00111110, B00100000, B00100000, B00101110, B00100010, B00111110, B00000000};
unsigned char LetterH[] = {B00000000, B00100100, B00100100, B00111100, B00100100, B00100100, B00100100, B00000000};
unsigned char LetterI[] = {B00000000, B00111000, B00010000, B00010000, B00010000, B00010000, B00111000, B00000000};
unsigned char LetterJ[] = {B00000000, B00011100, B00001000, B00001000, B00001000, B00101000, B00111000, B00000000};
unsigned char LetterK[] = {B00000000, B00100100, B00101000, B00110000, B00101000, B00100100, B00100100, B00000000};
unsigned char LetterL[] = {B00000000, B00100000, B00100000, B00100000, B00100000, B00100000, B00111100, B00000000};
unsigned char LetterM[] = {B00000000, B00000000, B01000100, B10101010, B10010010, B10000010, B10000010, B00000000};
unsigned char LetterN[] = {B00000000, B00100010, B00110010, B00101010, B00100110, B00100010, B00000000, B00000000};
unsigned char LetterO[] = {B00000000, B00111100, B01000010, B01000010, B01000010, B01000010, B00111100, B00000000};
unsigned char LetterP[] = {B00000000, B00111000, B00100100, B00100100, B00111000, B00100000, B00100000, B00000000};
unsigned char LetterQ[] = {B00000000, B00111100, B01000010, B01000010, B01000010, B01000110, B00111110, B00000001};
unsigned char LetterR[] = {B00000000, B00111000, B00100100, B00100100, B00111000, B00100100, B00100100, B00000000};
unsigned char LetterS[] = {B00000000, B00111100, B00100000, B00111100, B00000100, B00000100, B00111100, B00000000};
unsigned char LetterT[] = {B00000000, B01111100, B00010000, B00010000, B00010000, B00010000, B00010000, B00000000};
unsigned char LetterU[] = {B00000000, B01000010, B01000010, B01000010, B01000010, B00100100, B00011000, B00000000};
unsigned char LetterV[] = {B00000000, B00100010, B00100010, B00100010, B00010100, B00010100, B00001000, B00000000};
unsigned char LetterW[] = {B00000000, B10000010, B10010010, B01010100, B01010100, B00101000, B00000000, B00000000};
unsigned char LetterX[] = {B00000000, B01000010, B00100100, B00011000, B00011000, B00100100, B01000010, B00000000};
unsigned char LetterY[] = {B00000000, B01000100, B00101000, B00010000, B00010000, B00010000, B00010000, B00000000};
unsigned char LetterZ[] = {B00000000, B00111100, B00000100, B00001000, B00010000, B00100000, B00111100, B00000000};
const unsigned char *getCharacterBitmap(char ch)
{
  switch (ch)
  {
  case 'A':
    return LetterA;
  case 'B':
    return LetterB;
  case 'C':
    return LetterC;
  case 'D':
    return LetterD;
  case 'E':
    return LetterE;
  case 'F':
    return LetterF;
  case 'G':
    return LetterG;
  case 'H':
    return LetterH;
  case 'I':
    return LetterI;
  case 'J':
    return LetterJ;
  case 'K':
    return LetterK;
  case 'L':
    return LetterL;
  case 'M':
    return LetterM;
  case 'N':
    return LetterN;
  case 'O':
    return LetterO;
  case 'P':
    return LetterP;
  case 'Q':
    return LetterQ;
  case 'R':
    return LetterR;
  case 'S':
    return LetterS;
  case 'T':
    return LetterT;
  case 'U':
    return LetterU;
  case 'V':
    return LetterV;
  case 'W':
    return LetterW;
  case 'X':
    return LetterX;
  case 'Y':
    return LetterY;
  case 'Z':
    return LetterZ;
  // Handle other characters if needed
  default:
    return nullptr;
  }
}
void scrollText(String appear)
{
  const unsigned char *bitmaps[32]; // Adjust size as needed
  int length = 0;

  for (int i = 0; i < appear.length(); ++i)
  {
    const unsigned char *bitmap = getCharacterBitmap(appear[i]);
    if (bitmap)
    {
      bitmaps[length++] = bitmap;
    }
  }
  const unsigned char *text[32];
  *text = *bitmaps;
  for (int offset = 0; offset < 8 * length; ++offset)
  {
    clearfield();
    int start = offset / 8;
    int end = start + 8;

    for (int i = start; i < end && i < length; ++i)
    {
      int xPos = (offset % 8) - (i - start) * 8;
      if (xPos >= 0 && xPos < 8)
      {
        for (int row = 0; row < 8; ++row)
        {
          Field[row][xPos] = (text[i][row] >> (7 - (xPos % 8))) & 1;
        }
      }
      // vTaskDelay(10);
    }
    vTaskDelay(100);
  }
}


/*
Buttons:
*/
struct ButtonState
{
  bool down;         // is the button really pressed
  bool downqueue;    // essentially a button queue
  int microspressed; // how long is it being pressed or was it being pressed last time
  int lastrise;
  ButtonState() : down(0), microspressed(0) {}                 // Default constructor initializing x and y to 0
  ButtonState(int d, int mic) : down(d), microspressed(mic) {} // constructor
};

ButtonState left;
ButtonState right;
ButtonState A;
ButtonState B;
void LeftButtonCallback()
{
  if (0 == leftButton)
  {
    left.down = 1;
    left.downqueue = 1;
    left.lastrise = micros();
  }
  else
  {
    left.down = 0;
    left.microspressed = micros() - left.lastrise;
  }
}
void RightButtonCallback()
{
  if (0 == rightButton)
  {
    right.down = 1;
    right.downqueue = 1;
    right.lastrise = micros();
  }
  else
  {
    right.down = 0;
    right.microspressed = micros() - right.lastrise;
  }
}
void AButtonCallback()
{
  if (0 == AButton)
  {
    A.down = 1;
    A.downqueue = 1;
    A.lastrise = micros();
  }
  else
  {
    A.down = 0;
    A.microspressed = micros() - A.lastrise;
  }
}
void BButtonCallback()
{
  if (0 == BButton)
  {
    B.down = 1;
    B.downqueue = 1;
    B.lastrise = micros();
  }
  else
  {
    B.down = 0;
    B.microspressed = micros() - A.lastrise;
  }
}

/*
Here begins the snake stuff

*/
struct snake
{
  Position head;
  Position body[64];
  int length;

  // Enum to define movement directions
  enum Direction
  {
    UP,
    DOWN,
    LEFT,
    RIGHT
  };

  Direction currentDirection; // Current direction of the snake
  snake() : head(Position(millis() % 8, millis() % 8)), currentDirection(Direction(millis() % 4)), length(0) {}
  // Constructor to initialize the snake
  snake(int headX, int headY) : head(headX, headY), currentDirection(RIGHT)
  {
    for (int i = 0; i < 64; ++i)
    {
      body[i] = Position(-1, -1); // -1 is unvalid
    }
    length = 0;
  }
};
struct Food
{
  Position position;

  // Function to generate food at a random position, avoiding the snake's body
  void generateNewFood(snake &snakeobject)
  {
    while (true)
    {
      // Randomly place food somewhere in the 8x8 field
      position.x = random(0, 8);
      position.y = random(0, 8);

      // Ensure the food is not placed on the snake's body
      bool isFoodOnSnake = false;
      if (position == snakeobject.head)
      {
        isFoodOnSnake = true;
      }
      for (int i = 0; i < snakeobject.length; ++i)
      {
        if (position == snakeobject.body[i])
        {
          isFoodOnSnake = true;
          break;
        }
      }

      // If food is not placed on the snake, break out of the loop
      if (!isFoodOnSnake)
        break;
    }
  }
};
void playsnake(void *parameter)
{
  snake snakeobject;
  Food food;                         // Initialize food object
  food.generateNewFood(snakeobject); // Generate initial food position
  while (true)
  {

    // Check button states and update snake's direction
    if (left.downqueue)
    {
      left.downqueue = 0;
      if (snakeobject.currentDirection == snake::UP)
      {
        snakeobject.currentDirection = snake::LEFT;
      }
      else if (snakeobject.currentDirection == snake::DOWN)
      {
        snakeobject.currentDirection = snake::RIGHT;
      }
      else if (snakeobject.currentDirection == snake::RIGHT)
      {
        snakeobject.currentDirection = snake::UP;
      }
      else if (snakeobject.currentDirection == snake::LEFT)
      {
        snakeobject.currentDirection = snake::DOWN;
      }
    }

    if (right.downqueue)
    {
      right.downqueue = 0;
      if (snakeobject.currentDirection == snake::UP)
      {
        snakeobject.currentDirection = snake::RIGHT;
      }
      else if (snakeobject.currentDirection == snake::DOWN)
      {
        snakeobject.currentDirection = snake::LEFT;
      }
      else if (snakeobject.currentDirection == snake::RIGHT)
      {
        snakeobject.currentDirection = snake::DOWN;
      }
      else if (snakeobject.currentDirection == snake::LEFT)
      {
        snakeobject.currentDirection = snake::UP;
      }
    }

    // Move the snake's body
    for (int i = snakeobject.length; i > 0; --i)
    {
      snakeobject.body[i] = snakeobject.body[i - 1];
    }
    snakeobject.body[0] = snakeobject.head;

    // Move the snake's head
    switch (snakeobject.currentDirection)
    {
    case snake::UP:
      snakeobject.head.y = (snakeobject.head.y - 1 + 8) % 8; // Wrap around vertically
      break;
    case snake::DOWN:
      snakeobject.head.y = (snakeobject.head.y + 1) % 8; // Wrap around vertically
      break;
    case snake::LEFT:
      snakeobject.head.x = (snakeobject.head.x - 1 + 8) % 8; // Wrap around horizontally
      break;
    case snake::RIGHT:
      snakeobject.head.x = (snakeobject.head.x + 1) % 8; // Wrap around horizontally
      break;
    }

    // Check if the snake hits itself
    for (int i = 0; i < snakeobject.length; ++i)
    {
      if (snakeobject.head == snakeobject.body[i])
      {
        // Snake hit itself, reset game
        snakeobject.length = 0;
        String s = "GAMEOVER";
        scrollText(s);

        break;
      }
    }

    /*
     *Snake position update
     */
    // Clear the field
    for (int row = 0; row < 8; ++row)
    {
      for (int col = 0; col < 8; ++col)
      {
        Field[row][col] = 0;
      }
    }
    // Update the field with the snake's new position
    Field[snakeobject.head.y][snakeobject.head.x] = 1; // Head position
    for (int i = 0; i < snakeobject.length; ++i)
    {
      Field[snakeobject.body[i].y][snakeobject.body[i].x] = 1; // Body positions
    }

    /*
     *Food
     */
    // Check if the snake eats the food
    if (snakeobject.head == food.position)
    {
      // Snake ate the food, increase its length
      if (snakeobject.length)
      { // not their first apple
        snakeobject.body[snakeobject.length + 1] = snakeobject.body[snakeobject.length];
      }
      else
      {
        // length is 0 first apple
        snakeobject.body[0] = snakeobject.head;
      }

      snakeobject.length++;
      food.generateNewFood(snakeobject); // Generate new food
    }
    // Update the field with the food's position
    Field[food.position.y][food.position.x] = 1;

    // Delay to control speed
    vTaskDelay(SPEED * 1000);
  }
}

void setup()
{
  attachInterrupt(leftButton.pin, LeftButtonCallback, CHANGE);
  attachInterrupt(rightButton.pin, RightButtonCallback, CHANGE);
  attachInterrupt(AButton.pin, AButtonCallback, CHANGE);
  attachInterrupt(BButton.pin, BButtonCallback, CHANGE);

  xTaskCreate(
      drawField,                           // Function name of the task
      "draw the field described in Field", // Name of the task (e.g. for debugging)
      2048,                                // Stack size (bytes)
      NULL,                                // Parameter to pass
      1,                                   // Task priority
      NULL                                 // Task handle
  );
  xTaskCreate(
      playsnake,             // Function name of the task
      "play the snake game", // Name of the task (e.g. for debugging)
      2048,                  // Stack size (bytes)
      NULL,                  // Parameter to pass
      1,                     // Task priority
      NULL                   // Task handle
  );

  vTaskStartScheduler();
}

void loop()
{
}
