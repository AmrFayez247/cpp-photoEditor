// FCAI – Programming 1 – 2022 - Assignment 3
// Program Name: CS112_2022_2nd_S16_20210262_20210278_20210513_A3_Part1.cpp
// Description: This is a simple application for photo editing that uses 12 filters
// the program takes name of photo as an input and allow multiple filters on photo
// the user may choose to save it whenever he wants and exit the application whenever he wants
// The app works with colored rgb images
// Last Modification Date: 22/4/2022
// Author1 and ID and Group: Omar Ayman-20210262-S16
// Author2 and ID and Group: Amr Fayez-20210278-S16
// Author3 and ID and Group: Sara Ali-20210513-S16
// Teaching Assistant: Nesma Mohamed - Yousra Ayman

// Dependencies
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include "bmplib.cpp"

using namespace std;
unsigned char imageRGB[SIZE][SIZE][RGB];
unsigned char tempRGB[SIZE][SIZE][RGB];
unsigned char tempImageRGB[SIZE][SIZE][RGB];

// Initializing functions
void loadImageRGB();
void blackAndWhiteRGB();
void invertImageRGB();
void mergeImagesRGB();
void flipImageRGB();
void rotateImageRGB();
void rotateImage90RGB();
void rotateImage180RGB();
void rotateImage270RGB();
void opacityRGB();
void edgeDetectRGB();
void enlargeImageRGB();
void mirrorImageRGB();
void shuffleImageRGB();
void shrinkImageRGB();
void blurImageRGB();
void saveImageRGB();

int main()
{
    char command, rotate;
    // Greeting the user
    cout << "Photoshop Application\nHello User!\n";
    loadImageRGB();
    // While the command is not to end the program, ask for another command
    while (command != '0')
    {
        cout << "\n";
        // The main menu shown to the user
        cout << " 1-B&W Filter\n 2-Invert Image\n 3-Merge Images\n 4-Flip Image\n 5-Rotate Image\n 6-Darken & Lighten Image\n 7-Edge Detection\n 8-Enlarge Image\n 9-Shrink Image\n a-Mirror Image\n b-Shuffle Image\n c-Blur Image\n s-Save Image\n 0-Exit\n===> ";
        cin >> command;
        cin.ignore();
        if (command == '0')
        {
            cout << "Thank you, Goodbye!\n";
            break;
        }
        if (command == '1')
            blackAndWhiteRGB();
        else if (command == '2')
            invertImageRGB();
        else if (command == '3')
            mergeImagesRGB();
        else if (command == '4')
            flipImageRGB();
        else if (command == '5')
            rotateImageRGB();
        else if (command == '6')
            opacityRGB();
        else if (command == '7')
            edgeDetectRGB();
        else if (command == '8')
            enlargeImageRGB();
        else if (command == '9')
            shrinkImageRGB();
        else if (command == 'a')
            mirrorImageRGB();
        else if (command == 'b')
            shuffleImageRGB();
        else if (command == 'c')
            blurImageRGB();
        else if (command == 's')
            saveImageRGB();
    }
    return 0;
}








void loadImageRGB()
{
    // Function to load an image
    char imageFileName[100];
    cout << "\nEnter the image file name: ";
    cin >> imageFileName;
    strcat(imageFileName, ".bmp");
    readRGBBMP(imageFileName, imageRGB);
}

void blackAndWhiteRGB()
{
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            for (int k = 0; k < RGB; k++){
                
                imageRGB[i][j][k] = imageRGB[i][j][1];
                if (imageRGB[i][j][k] > 127)
                {
                    imageRGB[i][j][k] = 255;
                }
                else if (imageRGB[i][j][k] < 127)
                {
                    imageRGB[i][j][k] = 0;
                }  
            }
        }
    }
}

void invertImageRGB()
{
    for (int i = 0; i <SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k <RGB ; k++){
                imageRGB[i][j][k] = 255 - imageRGB[i][j][k];
            }
        }
    }
}

void mergeImagesRGB()
{
    // load another image
    unsigned char imageRGB2[SIZE][SIZE][RGB];
    char imageNew[100];
    cout << "Enter image file name to merge with: ";
    cin >> imageNew;
    strcat(imageNew, ".bmp");
    readRGBBMP(imageNew, imageRGB2);
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = 0; k < RGB; k++)
            {
                // take average of each pixel of two images
                imageRGB[i][j][k] = (imageRGB[i][j][k] + imageRGB2[i][j][k]) / 2;
            }
        }
    }
}

void flipImageRGB()
{
    int flip;
    cout << "1-Horizontal Flip\n2-Vertical Flip\n===> ";
    cin >> flip;
    // Intializing the 2d Array
    if(flip == 1){
        for (int i = 0; i < SIZE / 2; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB ; k++)
                {
                    // swap pixels of rows with 255 - the pixel to flip horizontally
                    swap(imageRGB[i][j][k], imageRGB[255 - i][255 - j][k]);
                }
            }
        }
    }
    else if(flip == 2)
    {
        // Intializing the 2d Array
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE / 2; j++)
            {
                for (int k = 0; k < RGB ; k++)
                {
                // swap the pixel of the image with 255-column to swap vertically
                swap(imageRGB[i][j][k], imageRGB[i][255 - j][k]);
                }
            }
        }
    }
}

void rotateImage90RGB()
{
    // Intializing the 2d Array
    for (int i = 0; i < SIZE / 2; i++)
    {
        for (int j = i; j < SIZE - i - 1; j++)
        {
            for (int k = 0; k < RGB ; k++)
            {
                int image2 = imageRGB[i][j][k];
                imageRGB[i][j][k] = imageRGB[255 - j][i][k];
                imageRGB[255 - j][i][k] = imageRGB[255 - i][255 - j][k];
                imageRGB[255 - i][255 - j][k] = imageRGB[j][255 - i][k];
                imageRGB[j][255 - i][k] = image2;
            }
        }
    }
}

void rotateImage180RGB()
{
    // Intializing the 2d Array
    for (int i = 0; i < 128; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = 0; k < RGB ; k++)
            {
            // swap pixels of rows with 255 - the pixel, to rotate 180
            swap(imageRGB[i][j][k], imageRGB[255 - i][255 - j][k]);

            }
        }
    }
}

void rotateImage270RGB()
{
    rotateImage90RGB();
    rotateImage180RGB();
}

void rotateImageRGB()
{
    char rotate;
    cout << " 1-90\n 2-180\n 3-270\n===> ";
    cin >> rotate;
    if (rotate == '1')
        rotateImage90RGB();
    if (rotate == '2')
        rotateImage180RGB();
    if (rotate == '3')
        rotateImage270RGB();  
}

void opacityRGB()
{
    char action;
    cout << "1-Lighten or 2-Darken \n ===> ";
    cin >> action;
    // check valid input
    while (action != '1' && action != '2')
    {
        cout << "Please enter 1 or 2,\n";
        cout << "1-Lighten or 2-Darken \n ===> ";
        cin >> action;
    }
    // to lighten
    if (action == '1')
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    // take average between pixel color and white
                    imageRGB[i][j][k] = (imageRGB[i][j][k] + 255) / 2;
                }
                
            }
        }
    }
    // to darken
    if (action == '2')
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    // take average between pixel color and black(0)
                    imageRGB[i][j][k] = imageRGB[i][j][k] / 2;
                }
            }
        }
    }
}

void edgeDetectRGB()
{
    // Intializing the 2d Array
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = 0; k < RGB ; k++)
            {
                // If the difference between the pixel & the one beside it or under it is bigger than 45 or smaller than -45 then take that pixel as an edge and convert it to black
                if (imageRGB[i][j][k] - imageRGB[i + 1][j][k] > 30 || imageRGB[i][j][k] - imageRGB[i][j + 1][k] > 30 || imageRGB[i][j][k] - imageRGB[i][j + 1][k] < -30 || imageRGB[i][j][k] - imageRGB[i + 1][j][k] < -30)
                {
                    imageRGB[i][j][k] = 0;
                }
                else
                {
                    // Convert everything else to white
                    imageRGB[i][j][k] = 255;
                }
            }

        }
    }
    blackAndWhiteRGB();

}

void mirrorImageRGB()
{
    int mirror;    //Taking a command to specify how to mirror the image
    cout << " 1-Left 1/2\n 2-Right 1/2\n 3-Upper 1/2\n 4-Lower 1/2\n ===>";
    cin >> mirror;

    if(mirror == 1)  //If the command is 1 Mirror the left half of the image 
    {
        //Intializing the 2D Array
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB ; k++)
                {
                    imageRGB[i][255-j][k] = imageRGB[i][j][k];   //Swaping pixels to get the mirror effect
                }
            }
        }
    }
    else if(mirror == 2)   // If the command is 2 Mirror the right half of the image 
    {
        //Intializing the 2D Array
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB ; k++)
                {
                    imageRGB[i][j][k] = imageRGB[i][255-j][k];   //Swaping pixels to get the mirror effect
                }
            }
        }
    }
    else if(mirror == 3)   // If the command is 3 Mirror the upper half of the image 
    {
        //Intializing the 2D Array
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB ; k++)
                {
                    imageRGB[255-i][j][k] = imageRGB[i][j][k];   //Swaping pixels to get the mirror effect
                }
            }
        }
    }
    else if(mirror == 4)   // If the command is 4 Mirror the bottom half of the image 
    {
        //Intializing the 2D Array
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB ; k++)
                {
                    imageRGB[i][j][k] = imageRGB[255-i][j][k];   //Swaping pixels to get the mirror effect
                }
            }
        }
    }
}

void blurImageRGB()
{
    // loop 4 times to increase blur
    for (int counter = 0; counter < 4; counter++)
    {
        // loop through each pixel
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB; k++){
                    // detecting edges of photo
                    // first row
                    if (i == 0)
                    {
                        // first col
                        if (j == 0)
                        {
                            // average of surrounding pixels
                            imageRGB[i][j][k] = (imageRGB[i][j + 1][k] + imageRGB[i + 1][j][k] + imageRGB[i + 1][j + 1][k]) / 3;
                        }
                        // last col
                        else if (j == SIZE - 1)
                        {
                            // average of surrounding pixels
                            imageRGB[i][j][k] = (imageRGB[i][j - 1][k] + imageRGB[i + 1][j][k] + imageRGB[i + 1][j - 1][k]) / 3;
                        }
                        // rest
                        else
                        {
                            // average of surrounding pixels
                            imageRGB[i][j][k] = (imageRGB[i][j - 1][k] + imageRGB[i][j + 1][k] + imageRGB[i + 1][j][k] + imageRGB[i + 1][j - 1][k] + imageRGB[i + 1][j + 1][k]) / 5;
                        }
                    }
                    // last row
                    else if (i == SIZE - 1)
                    {
                        // first col
                        if (j == 0)
                        {
                            imageRGB[i][j][k] = (imageRGB[i][j + 1][k] + imageRGB[i - 1][j][k] + imageRGB[i - 1][j + 1][k]) / 3;
                        }
                        // last col
                        else if (j == SIZE - 1)
                        {
                            imageRGB[i][j][k] = (imageRGB[i][j - 1][k] + imageRGB[i - 1][j][k] + imageRGB[i - 1][j - 1][k]) / 3;
                        }
                        // rest
                        else
                        {
                            imageRGB[i][j][k] = (imageRGB[i][j - 1][k] + imageRGB[i][j + 1][k] + imageRGB[i - 1][j][k] + imageRGB[i - 1][j - 1][k] + imageRGB[i - 1][j + 1][k]) / 5;
                        }
                    }
                    // left side pixels
                    else if (j == 0)
                    {
                        imageRGB[i][j][k] = (imageRGB[i][j + 1][k] + imageRGB[i - 1][j][k] + imageRGB[i - 1][j + 1][k] + imageRGB[i + 1][j + 1][k] + imageRGB[i + 1][j][k]) / 5;
                    }
                    // right side pixels
                    else if (j == SIZE - 1)
                    {
                        imageRGB[i][j][k] = (imageRGB[i][j - 1][k] + imageRGB[i - 1][j][k] + imageRGB[i - 1][j - 1][k] + imageRGB[i + 1][j - 1][k] + imageRGB[i + 1][j][k]) / 5;
                    }
                    // rest of pixels
                    else
                    {
                        imageRGB[i][j][k] = (imageRGB[i][j - 1][k] + imageRGB[i - 1][j][k] + imageRGB[i - 1][j - 1][k] + imageRGB[i + 1][j - 1][k] + imageRGB[i + 1][j][k] + imageRGB[i + 1][j + 1][k] + imageRGB[i][j + 1][k] + imageRGB[i - 1][j + 1][k]) / 8;
                    }
                }
            }
        }
    } 
}

void enlargeImageRGB()
{
    int choice;
    cout << "Please enter the quarter to be enlarged \n 1 or 2 or 3 or 4\n ===> ";
    cin >> choice;
    //storing pixels of chosen quarter in temporary array of size 128*128 
    switch (choice) {
        case 1:
            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0; j < SIZE / 2; j++){
                    for (int k = 0; k < RGB; k++){
                        tempRGB[i][j][k] = imageRGB[i][j][k];
                    }
                }
            }
            break;
        case 2:
            for (int i = 0; i < SIZE / 2 ; i++) {
                for (int j = 0; j < SIZE /2 ; j++){
                    for (int k = 0; k < RGB; k++){
                        tempRGB[i][j][k] = imageRGB[i][j + (SIZE / 2)][k];
                    }
                }
            }
            break;
        case 3:
            for (int i = 0; i < SIZE /2 ; i++) {
                for (int j = 0; j < SIZE /2; j++){
                    for (int k = 0; k < RGB; k++){
                        tempRGB[i][j][k] = imageRGB[i + (SIZE / 2)][j][k];
                    }
                }
            }
            break;
        case 4:
            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0; j < SIZE / 2; j++){
                    for (int k = 0; k < RGB; k++){
                        tempRGB[i][j][k] = imageRGB[i + (SIZE / 2)][j + (SIZE / 2)][k];
                    }
                }
            }
            break;
        default:
            cout << "invalid input\n";
            enlargeImageRGB();
    }
    // initializing for loop to enlarge a quarter to be 256*256 by storing each pixel in 4 neighboring pixels.
        for (int i = 0; i < SIZE; i++){
            for (int j = 0; j < SIZE / 2; j ++){
                for (int k = 0; k < RGB; k++){
                 imageRGB[i*2][j*2][k]=imageRGB[i*2][j*2+1][k]=imageRGB[i*2+1][j*2][k]=imageRGB[i*2+1][j*2+1][k] = tempRGB[i][j][k];
            }
        }
    }
}

void shrinkImageRGB() 
{
    char action;
    // take action input
    cout << "Do you want to shrink to\n1- Half(1/2)\n2- Third(1/3)\n3- Quarter(1/4)"<<endl;
    cin >> action;
    // check valid input
    while(action!='1'&&action!='2'&&action!='3'){
        cout<<"Please enter 1 or 2 or 3"<<endl;
        cout << "Do you want to shrink to\n1- Half(1/2)\n2- Third(1/3)\n3- Quarter(1/4)"<<endl;
        cin >> action;
    }
    int y;
    switch (action){
        case '1':
            y=0;
            // take average between every 2 pixels and join in one pixel in order
            for (int i = 0; i < SIZE/2; i++) {
                for(int j = 0; j < SIZE/2; j++){
                    imageRGB[i][j][0]=(imageRGB[i][y][0]+imageRGB[i][y+1][0])/2;
                    imageRGB[i][j][1]=(imageRGB[i][y][1]+imageRGB[i][y+1][1])/2;
                    imageRGB[i][j][2]=(imageRGB[i][y][2]+imageRGB[i][y+1][2])/2;
                    y+=2;
                }
            }
            // make the rest of image white
            for (int i = 0; i < SIZE; i++) {
                for(int j = SIZE/2; j < SIZE; j++){
                    for(int k=0; k<RGB; k++){
                        imageRGB[i][j][k]=255;
                    }
                }
            }
            for (int i = SIZE/2; i < SIZE; i++) {
                for(int j = 0; j < SIZE/2; j++){
                    for(int k=0; k<RGB; k++){
                        imageRGB[i][j][k]=255;
                    }
                }
            }
            break;
        case '2':
            y=0;
            // take average between every 3 pixels and join in one pixel in order
            for (int i = 0; i < SIZE/3; i++) {
                for(int j = 0; j < SIZE; j++){
                    imageRGB[i][j][0]=(imageRGB[i][y][0]+imageRGB[i][y+1][0]+imageRGB[i][y+2][0])/3;
                    imageRGB[i][j][1]=(imageRGB[i][y][1]+imageRGB[i][y+1][1]+imageRGB[i][y+2][1])/3;
                    imageRGB[i][j][2]=(imageRGB[i][y][2]+imageRGB[i][y+1][2]+imageRGB[i][y+2][2])/3;
                    y+=3;
                }
            }
            // make the rest of image white
            for (int i = 0; i < SIZE; i++) {
                for(int j = SIZE/3; j < SIZE; j++){
                    for(int k=0;k<RGB;k++){
                        imageRGB[i][j][k]=255;
                    }
                }
            }
            for (int i = SIZE/4; i < SIZE; i++) {
                for(int j = 0; j < SIZE/3; j++){
                    for(int k=0;k<RGB;k++){
                        imageRGB[i][j][k]=255;
                    }
                }
            }
            break;
        case '3':
            y=0;
            // take average between every 4 pixels and join in one pixel in order
            for (int i = 0; i < SIZE/4; i++) {
                for(int j = 0; j < SIZE; j++){
                    imageRGB[i][j][0]=(imageRGB[i][y][0]+imageRGB[i][y+1][0]+imageRGB[i][y+2][0]+imageRGB[i][y+3][0])/4;
                    imageRGB[i][j][1]=(imageRGB[i][y][1]+imageRGB[i][y+1][1]+imageRGB[i][y+2][1]+imageRGB[i][y+3][1])/4;
                    imageRGB[i][j][2]=(imageRGB[i][y][2]+imageRGB[i][y+1][2]+imageRGB[i][y+2][2]+imageRGB[i][y+3][2])/4;
                    y+=4;
                }
            }
            // make the rest of image white
            for (int i = 0; i < SIZE; i++) {
                for(int j = SIZE/4; j < SIZE; j++){
                    for(int k=0;k<RGB;k++){
                        imageRGB[i][j][k]=255;
                    }
                }
            }
            for (int i = (SIZE/5)+1; i < SIZE; i++) {
                for(int j = 0; j < SIZE/2; j++){
                    for(int k=0;k<RGB;k++){
                        imageRGB[i][j][k]=255;
                    }
                }
            }
            break;
    }
}

void shuffleImageRGB()
{
    for(int i=0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            for(int k = 0; k < SIZE; k++){
                tempImageRGB[i][j][k]=imageRGB[i][j][k];
            }
        }
    }

    int choice;
    cout << "choose which quarter to be placed in the first quarter: " << endl;
    cout << " 1-Quarter1\n 2-Quarter2\n 3-Quarter3\n 4-Quarter4" << endl;
    cin >> choice;


    while (choice!=1 && choice!=2 && choice!=3 && choice!=4)
    {
        cout << "choose 1 or 2 or 3 or 4" << endl;
        cout << " 1-Quarter1\n 2-Quarter2\n 3-Quarter3\n 4-Quarter4r" << endl;
        cin >> choice;
    }

    for (int i = 0,x = 128; i < 128;i++, x++){
        for (int j = 0,y = 128; j < 128; j++,y++){
           for (int k=0; k<RGB; k++){
            
            if (choice == 1)
                imageRGB[i][j][k] = tempImageRGB[i][j][k]; 
            else if (choice == 2)
                imageRGB[i][j][k] = tempImageRGB[i][y][k]; 
            else if (choice == 3)
                imageRGB[i][j][k] = tempImageRGB[x][j][k]; 
            else if (choice == 4)
                imageRGB[i][j][k] = tempImageRGB[x][y][k];
           }
        
        }
    }

    cout << "choose which quarter to be placed in the second quarter: " << endl;
    cout << " 1-Quarter1\n 2-Quarter2\n 3-Quarter3\n 4-Quarter4" << endl;
    cin >> choice;

    
    while (choice!=1 && choice!=2 && choice!=3 && choice!=4)
    {
        cout << "choose 1 or 2 or 3 or 4" << endl;
        cout << " 1-Quarter1\n 2-Quarter2\n 3-Quarter3\n 4-Quarter4" << endl;
        cin >> choice;
    }

    for (int i = 0,x=128; i < 128;i++,x++){
        for (int j = 0,y=128; j < 128;j++,y++){
           for (int k=0; k<RGB; k++){
            
            if (choice == 1)
                imageRGB[i][y][k] = tempImageRGB[i][j][k]; 
            else if (choice == 2)
                imageRGB[i][y][k] = tempImageRGB[i][y][k]; 
            else if (choice == 3)
                imageRGB[i][y][k] = tempImageRGB[x][j][k]; 
            else if (choice == 4)
                imageRGB[i][y][k] = tempImageRGB[x][y][k]; 
           }
        
        }
    }

    cout << "choose which quarter to be placed in the third quarter: " << endl;
    cout << " 1-Quarter1\n 2-Quarter2\n 3-Quarter3\n 4-Quarter4" << endl;
    cin >> choice;

   
    while (choice!=1 && choice!=2 && choice!=3 && choice!=4)
    {
        cout << "choose 1 or 2 or 3 or 4" << endl;
        cout << " 1-Quarter1\n 2-Quarter2\n 3-Quarter3\n 4-Quarter4" << endl;
        cin >> choice;
    }
    
    for (int i = 0,x=128; i < 128;i++,x++){
        for (int j = 0,y=128; j < 128;j++,y++){
           for (int k=0; k<RGB; k++){
            
            if (choice == 1)
                imageRGB[x][j][k] = tempImageRGB[i][j][k]; 
            else if (choice == 2)
                imageRGB[x][j][k] = tempImageRGB[i][y][k];
            else if (choice == 3)
                imageRGB[x][j][k] = tempImageRGB[x][j][k]; 
            else if (choice == 4)
                imageRGB[x][j][k] = tempImageRGB[x][y][k];
           }
        
        }
    }

    cout << "choose which quarter to be placed in the fourth quarter: " << endl;
    cout << " 1-Quarter1\n 2-Quarter2\n 3-Quarter3\n 4-Quarter4" << endl;
    cin >> choice;

    
    while (choice!=1 && choice!=2 && choice!=3 && choice!=4)
    {
        cout << "choose 1 or 2 or 3 or 4" << endl;
        cout << " 1-Quarter1\n 2-Quarter2\n 3-Quarter3\n 4-Quarter4" << endl;
        cin >> choice;
    }

    for (int i = 0,x=128; i < 128;i++,x++){
        for (int j = 0,y=128; j < 128;j++,y++){
           for (int k=0; k<RGB; k++){
            
            if (choice == 1)
                imageRGB[x][y][k] = tempImageRGB[i][j][k]; 
            else if (choice == 2)
                imageRGB[x][y][k] = tempImageRGB[i][y][k]; 
            else if (choice == 3)
                imageRGB[x][y][k] = tempImageRGB[x][j][k]; 
            else if (choice == 4)
                imageRGB[x][y][k] = tempImageRGB[x][y][k];
           } 
        
        }
    }
}

void saveImageRGB()
{
    // Function to save the image
    char imageFileName[100];
    cout << "Enter the name you would like to save the image: ";
    cin >> imageFileName;
    strcat(imageFileName, ".bmp");
    writeRGBBMP(imageFileName, imageRGB);
}