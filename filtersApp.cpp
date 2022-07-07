// FCAI – Programming 1 – 2022 - Assignment 3
// Program Name: CS112_2022_2nd_S16_20210262_20210278_20210513_A3_Part1.cpp
// Description: This is a simple application for photo editing that uses 12 filters
// the program takes name of photo as an input and allow multiple filters on photo
// the user may choose to save it whenever he wants and exit the application whenever he wants
// The app works with Grayscale images
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
unsigned char image[SIZE][SIZE];
unsigned char temp[SIZE][SIZE];

// Initializing functions
void loadImage();
void blackAndWhite();
void invertImage();
void mergeImages();
void flipImage();
void rotateImage();
void rotateImage90();
void rotateImage180();
void rotateImage270();
void opacity();
void edgeDetect();
void mirrorImage();
void blurImage();
void enlargeImage();
void shuffleImage();
void shrinkImage();
void saveImage();

int main()
{
    char command;
    // Greeting the user
    cout << "Photoshop Application\nHello User!\n";
    loadImage();
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
            blackAndWhite();
        else if (command == '2')
            invertImage();
        else if (command == '3')
            mergeImages();
        else if (command == '4')
            flipImage();
        else if (command == '5')
            rotateImage();
        else if (command == '6')
            opacity();
        else if (command == '7')
            edgeDetect();
        else if (command == '8')
            enlargeImage();
        else if (command == '9')
            shrinkImage();
        else if (command == 'a')
            mirrorImage();
        else if (command == 'b')
            shuffleImage();
        else if (command == 'c')
            blurImage();
        else if (command == 's')
            saveImage();
    }
    return 0;
}






void loadImage()
{
    // Function to load an image
    char imageFileName[100];
    cout << "\nEnter the image file name: ";
    cin >> imageFileName;
    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

void blackAndWhite()
{
    // Intializing the 2d Array
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            // if the pixel is a light gray convert to white
            if (image[i][j] > 127)
                image[i][j] = 255;
            // else if the pixel is dark gray convert it to black
            else
                image[i][j] = 0;
        }
    }
}

void invertImage()
{
    // Intializing the 2d Array
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            // invert color of the image by subtracting it from 255
            image[i][j] = 255 - image[i][j];
        }
    }
}

void mergeImages()
{
    // load another image
    unsigned char image2[SIZE][SIZE];
    char imageNew[100];
    cout << "Enter image file name to merge with: ";
    cin >> imageNew;
    strcat(imageNew, ".bmp");
    readGSBMP(imageNew, image2);
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            // take average of each pixel of two images
            image[i][j] = (image[i][j] + image2[i][j]) / 2;
        }
    }
}

void flipImage()
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
                // swap pixels of rows with 255 - the pixel to flip horizontally
                swap(image[i][j], image[255 - i][255 - j]);
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
                // swap the pixel of the image with 255-column to swap vertically
                swap(image[i][j], image[i][255 - j]);
            }
        }
    }
}

void rotateImage90()
{
    // Intializing the 2d Array
    for (int i = 0; i < SIZE / 2; i++)
    {
        for (int j = i; j < SIZE - i - 1; j++)
        {
            int image2 = image[i][j];
            image[i][j] = image[255 - j][i];
            image[255 - j][i] = image[255 - i][255 - j];
            image[255 - i][255 - j] = image[j][255 - i];
            image[j][255 - i] = image2;
        }
    }
}

void rotateImage180()
{
    // Intializing the 2d Array
    for (int i = 0; i < 128; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            // swap pixels of rows with 255 - the pixel, to rotate 180
            swap(image[i][j], image[255 - i][255 - j]);
        }
    }
}

void rotateImage270()
{
    // using the function of rotate 180 and rotate 90 to rotate the image 270 degrees
    rotateImage90();
    rotateImage180();
}

void rotateImage()
{
    char rotate;
    cout << " 1-90\n 2-180\n 3-270\n ===> ";
    cin >> rotate;
    if (rotate == '1')
        rotateImage90();
    if (rotate == '2')
        rotateImage180();
    if (rotate == '3')
        rotateImage270();
}

void opacity()
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
                // take average between pixel color and white
                image[i][j] = (image[i][j] + 255) / 2;
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
                // take average between pixel color and black(0)
                image[i][j] = image[i][j] * 0.5;
            }
        }
    }
}

void edgeDetect()
{
    // Intializing the 2d Array
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            // If the difference between the pixel & the one beside it or under it is bigger than 45 or smaller than -45 then take that pixel as an edge and convert it to black
            if (image[i][j] - image[i + 1][j] > 45 || image[i][j] - image[i][j + 1] > 45 || image[i][j] - image[i][j + 1] < -45 || image[i][j] - image[i + 1][j] < -45)
            {
                image[i][j] = 0;
            }
            else
            {
                // Convert everything else to white
                image[i][j] = 255;
            }
        }
    }
}

void enlargeImage()
{
    int choice;
    cout << "Please enter the quarter to be enlarged \n 1 or 2 or 3 or 4\n ===> ";
    cin >> choice;
    //storing pixels of chosen quarter in temporary array of size 128*128 
    switch (choice) {
        case 1:
            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0; j < SIZE / 2; j++)
                    temp[i][j] = image[i][j];
            }
            break;
        case 2:
            for (int i = 0; i < SIZE / 2 ; i++) {
                for (int j = 0; j < SIZE /2 ; j++)
                    temp[i][j] = image[i][j + (SIZE / 2)];
            }
            break;
        case 3:
            for (int i = 0; i < SIZE /2 ; i++) {
                for (int j = 0; j < SIZE /2; j++)
                    temp[i][j] = image[i + (SIZE / 2)][j];
            }
            break;
        case 4:
            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0; j < SIZE / 2; j++)
                    temp[i][j] = image[i + (SIZE / 2)][j + (SIZE / 2)];
            }
            break;
        default:
            cout << "invalid input\n";
            enlargeImage();
    }
    // initializing for loop to enlarge a quarter to be 256*256 by storing each pixel in 4 neighboring pixels.
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE / 2; j ++) {
            image[i*2][j*2]=image[i*2][j*2+1]=image[i*2+1][j*2]=image[i*2+1][j*2+1] = temp[i][j];
        }
    }
}

void mirrorImage()
{
    int mirror;    //Taking a command to specify how to mirror the image
    cout << " 1-Left 1/2\n 2-Right 1/2\n 3-Upper 1/2\n 4-Lower 1/2\n ===>";
    cin >> mirror;

    if(mirror == 1)  //If the command is 1 Mirror the left half of the image 
    {
        //Intializing the 2D Array
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE/2; j++)
            {
                image[i][255-j] = image[i][j];   //Swaping pixels to get the mirror effect
            }
        }
    }
    else if(mirror == 2)   // If the command is 2 Mirror the right half of the image 
    {
        //Intializing the 2D Array
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE/2; j++)
            {
                image[i][j] = image[i][255-j];   //Swaping pixels to get the mirror effect
            }
        }
    }
    else if(mirror == 3)   // If the command is 3 Mirror the upper half of the image 
    {
        //Intializing the 2D Array
        for (int i = 0; i < SIZE/2; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                image[255-i][j] = image[i][j];   //Swaping pixels to get the mirror effect
            }
        }
    }
    else if(mirror == 4)   // If the command is 4 Mirror the bottom half of the image 
    {
        //Intializing the 2D Array
        for (int i = 0; i < SIZE/2; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                image[i][j] = image[255-i][j];   //Swaping pixels to get the mirror effect
            }
        }
    }
}

void blurImage()
{
    // loop 3 times to increase blur
    for (int counter = 0; counter < 3; counter++)
    {
        // loop through each pixel
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                // detecting edges of photo
                // first row
                if (i == 0)
                {
                    // first col
                    if (j == 0)
                    {
                        // average of surrounding pixels
                        image[i][j] = (image[i][j + 1] + image[i + 1][j] + image[i + 1][j + 1]) / 3;
                    }
                    // last col
                    else if (j == SIZE - 1)
                    {
                        // average of surrounding pixels
                        image[i][j] = (image[i][j - 1] + image[i + 1][j] + image[i + 1][j - 1]) / 3;
                    }
                    // rest
                    else
                    {
                        // average of surrounding pixels
                        image[i][j] = (image[i][j - 1] + image[i][j + 1] + image[i + 1][j] + image[i + 1][j - 1] + image[i + 1][j + 1]) / 5;
                    }
                }
                // last row
                else if (i == SIZE - 1)
                {
                    // first col
                    if (j == 0)
                    {
                        image[i][j] = (image[i][j + 1] + image[i - 1][j] + image[i - 1][j + 1]) / 3;
                    }
                    // last col
                    else if (j == SIZE - 1)
                    {
                        image[i][j] = (image[i][j - 1] + image[i - 1][j] + image[i - 1][j - 1]) / 3;
                    }
                    // rest
                    else
                    {
                        image[i][j] = (image[i][j - 1] + image[i][j + 1] + image[i - 1][j] + image[i - 1][j - 1] + image[i - 1][j + 1]) / 5;
                    }
                }
                // left side pixels
                else if (j == 0)
                {
                    image[i][j] = (image[i][j + 1] + image[i - 1][j] + image[i - 1][j + 1] + image[i + 1][j + 1] + image[i + 1][j]) / 5;
                }
                // right side pixels
                else if (j == SIZE - 1)
                {
                    image[i][j] = (image[i][j - 1] + image[i - 1][j] + image[i - 1][j - 1] + image[i + 1][j - 1] + image[i + 1][j]) / 5;
                }
                // rest pixels
                else
                {
                    image[i][j] = (image[i][j - 1] + image[i - 1][j] + image[i - 1][j - 1] + image[i + 1][j - 1] + image[i + 1][j] + image[i + 1][j + 1] + image[i][j + 1] + image[i - 1][j + 1]) / 8;
                }
            }
        }
    }
}

void shuffleImage()
{
    unsigned char tempImage[SIZE][SIZE];
    for(int i=0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            tempImage[i][j]=image[i][j];
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
            
            if (choice == 1)
                image[i][j] = tempImage[i][j]; 
            else if (choice == 2)
                image[i][j] = tempImage[i][y]; 
            else if (choice == 3)
                image[i][j] = tempImage[x][j]; 
            else if (choice == 4)
                image[i][j] = tempImage[x][y]; 
        
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
            
            if (choice == 1)
                image[i][y] = tempImage[i][j]; 
            else if (choice == 2)
                image[i][y] = tempImage[i][y]; 
            else if (choice == 3)
                image[i][y] = tempImage[x][j]; 
            else if (choice == 4)
                image[i][y] = tempImage[x][y]; 
        
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
            
            if (choice == 1)
                image[x][j] = tempImage[i][j]; 
            else if (choice == 2)
                image[x][j] = tempImage[i][y];
            else if (choice == 3)
                image[x][j] = tempImage[x][j]; 
            else if (choice == 4)
                image[x][j] = tempImage[x][y];
        
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
            
            if (choice == 1)
                image[x][y] = tempImage[i][j]; 
            else if (choice == 2)
                image[x][y] = tempImage[i][y]; 
            else if (choice == 3)
                image[x][y] = tempImage[x][j]; 
            else if (choice == 4)
                image[x][y] = tempImage[x][y]; 
        
        }
    }
}

void shrinkImage()
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
                    image[i][j]=(image[i][y]+image[i][y+1])/2;
                    y+=2;
                }
            }
            // make the rest of image white
            for (int i = 0; i < SIZE; i++) {
                for(int j = SIZE/2; j < SIZE; j++){
                    image[i][j]=255;
                }
            }
            for (int i = SIZE/2; i < SIZE; i++) {
                for(int j = 0; j < SIZE/2; j++){
                    image[i][j]=255;
                }
            }
            break;
        case '2':
            y=0;
            // take average between every 3 pixels and join in one pixel in order
            for (int i = 0; i < SIZE/3; i++) {
                for(int j = 0; j < SIZE; j++){
                    image[i][j]=(image[i][y]+image[i][y+1]+image[i][y+2])/3;
                    y+=3;
                }
            }
            // make the rest of image white
            for (int i = 0; i < SIZE; i++) {
                for(int j = SIZE/3; j < SIZE; j++){
                    image[i][j]=255;
                }
            }
            for (int i = SIZE/4; i < SIZE; i++) {
                for(int j = 0; j < SIZE/3; j++){
                    image[i][j]=255;
                }
            }
            break;
        case '3':
            y=0;
            // take average between every 4 pixels and join in one pixel in order
            for (int i = 0; i < SIZE/4; i++) {
                for(int j = 0; j < SIZE; j++){
                    image[i][j]=(image[i][y]+image[i][y+1]+image[i][y+2]+image[i][y+3])/4;
                    y+=4;
                }
            }
            // make the rest of image white
            for (int i = 0; i < SIZE; i++) {
                for(int j = SIZE/4; j < SIZE; j++){
                    image[i][j]=255;
                }
            }
            for (int i = SIZE/5; i < SIZE; i++) {
                for(int j = 0; j < SIZE/2; j++){
                    image[i][j]=255;
                }
            }
            break;
    }
}

void saveImage()
{
    // Function to save the image
    char imageFileName[100];
    cout << "Enter the name you would like to save the image: ";
    cin >> imageFileName;
    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}