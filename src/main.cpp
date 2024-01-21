#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

uint16_t version = MCUFRIEND_KBV_H_;

const int TFT_WIDTH = 120;
const int TFT_HEIGHT = 80;
bool next[TFT_WIDTH][TFT_HEIGHT] = {0};
bool prev[TFT_WIDTH][TFT_HEIGHT] = {0};

void drawBoard()
{
    for (int x = 0; x < TFT_WIDTH; x++)
    {
        for (int y = 0; y < TFT_HEIGHT; y++)
        {
            if(next[x][y] == prev[x][y])
            {
                continue;            
            }
            else if (next[x][y])
            {
                tft.fillRect(x * 4, y * 4, 3, 3, TFT_WHITE);
            }
            else
            {
                tft.fillRect(x * 4, y * 4, 3, 3, TFT_BLACK);
            }
        }
    }
}

void setup()
{
    uint16_t ID = tft.readID(); //
    tft.begin(ID);
    tft.fillScreen(TFT_BLACK);
    tft.setRotation(1);

    for (int x = 0; x < TFT_WIDTH; x++)
    {
        for (int y = 0; y < TFT_HEIGHT; y++)
        {
            prev[x][y] = rand()%2;
        }
    }
    
    drawBoard();
}

void loop()
{
    for (int x = 0; x < TFT_WIDTH; x++)
    {
        for (int y = 0; y < TFT_HEIGHT; y++)
        {
            // count the number of neighbors and store in array next
            int neighbors = 0;

            if (x > 0 && y > 0 && prev[x - 1][y - 1])
            {
                neighbors++;
            }

            if (x > 0 && prev[x - 1][y])
            {
                neighbors++;
            }

            if (x > 0 && y < TFT_HEIGHT - 1 && prev[x - 1][y + 1])
            {
                neighbors++;
            }

            if (y > 0 && prev[x][y - 1])
            {
                neighbors++;
            }

            if (y < TFT_HEIGHT - 1 && prev[x][y + 1])
            {
                neighbors++;
            }

            if (x < TFT_WIDTH - 1 && y > 0 && prev[x + 1][y - 1])
            {
                neighbors++;
            }

            if (x < TFT_WIDTH - 1 && prev[x + 1][y])
            {
                neighbors++;
            }

            if (x < TFT_WIDTH - 1 && y < TFT_HEIGHT - 1 && prev[x + 1][y + 1])
            {
                neighbors++;
            }

            // apply the rules of the game of life
            if (prev[x][y] && (neighbors == 2 || neighbors == 3))
            {
                next[x][y] = true;
            }
            else if (!prev[x][y] && neighbors == 3)
            {
                next[x][y] = true;
            }
            else
            {
                next[x][y] = false;
            }
        }
    }

    drawBoard();

    // copy the next board state to the previous board state
    for (int x = 0; x < TFT_WIDTH; x++)
    {
        for (int y = 0; y < TFT_HEIGHT; y++)
        {
            prev[x][y] = next[x][y];
        }
    }
}
