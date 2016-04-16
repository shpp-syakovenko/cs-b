#include <iostream>
#include <QImage>
#include <QColor>
#include <QPoint>
#include "myqueue.h"
#include <fstream>

using namespace std;

// create two-dimensional array where "1" it is silhouettes "0" it is background
int ** creatArrayImage(QImage * img);

// show array in the text file.
void showSilhouette(int ** matrix, QImage * img);

//  search of the silhouettes on the image and return  number of the found silhouettes.
int searchSilhouettes(int ** matrix, int width, int height);

/*
 * replace every pixel with "1" on the "0".
 * matrix: two-dimensional array of the image
 * height: height of the image
 * width: width of the image
 * y: coordinate "y" pixel.
 * x: coordinate "x" pixel.
 * */
void replacePixels(int** matrix, int height, int width, int y, int x);

// point in range of the array.
bool isArrayRange(QPoint point, int height, int width);

// change matrix where "1" it is silhouettes "0" it is background
void changeMatrix(int** matrix, QImage * img, int background, int silhouett);

int main()
{
    string fileName;
    cout << "Image must contain only background and sillhouetes without any watermarks!!! "<<endl << endl;
    cout << "Input path to silhouette file: ";

    getline(cin,fileName);

    QImage *img = new QImage(fileName.c_str());

    cout << "Height: " << img->height() << endl;
    cout << "Width: " << img->width() << endl;

    int ** matrix = creatArrayImage(img);
    showSilhouette(matrix, img);

    int countSilhouettes = searchSilhouettes(matrix, img->width(), img->height());

    cout << "Silhouettes: " << countSilhouettes;

    for(int i = 0; i < img->height(); i++)
        delete [] matrix[i];
    delete [] matrix;

    delete img;

    return 0;
}

// point in range of the array.
bool isArrayRange(QPoint point, int height, int width){
    if(point.x() >= 0 && point.y() >= 0 && point.x() < width && point.y() < height)
        return true;
    return false;
}

/*
 * replace every pixel with "1" on the "0".
 * matrix: two-dimensional array of the image
 * height: height of the image
 * width: width of the image
 * y: coordinate "y" pixel.
 * x: coordinate "x" pixel.
 * */
void replacePixels(int **matrix, int height, int width, int y, int x){
    myQueue<QPoint> *q = new myQueue<QPoint>;
    QPoint point(x,y);
    q->push(point);
    while(!q->empty()){
        QPoint temp = q->front();
        q->pop();
        x = temp.x();
        y = temp.y();

        for(int i = -1; i < 2; i++){
            for(int j = -1; j < 2; j++){
                if(isArrayRange(QPoint(x + i, y + j), height, width) && matrix[y + j][x + i] != 0){
                    matrix[y + j][x + i] = 0;
                    q->push(QPoint(x + i, y + j));
                }
            }
        }
    }

    delete q;
}

//  search of the silhouettes on the image and return  number of the found silhouettes.
int searchSilhouettes(int **matrix, int width, int height){
    int count = 0;

    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            if(matrix[y][x] == 1){
                replacePixels(matrix, height, width, y, x);
                count++;
            }
        }
    }
    return count;
}


// create two-dimensional array where "1" it is silhouettes "0" it is background
int ** creatArrayImage(QImage *img){
    const int width = img->width();
    const int height = img->height();

    int ** matrix = new int*[height];

    for(int i = 0; i < height; i++)
        matrix[i] = new int[width];

    int white = 0, black = 0;

// running by top of the line image and define of the background.
    for(int y = 0; y < 1; y++){
        for(int x = 0; x < width; x++){
            int color = QColor(img->pixel(x,y)).lightness();
            if(color >= 127) white++;
            else black++;
        }
    }
// if background is white
    if(white > black){
        changeMatrix(matrix,img,0,1);
    }
// else background is black
    else{
        changeMatrix(matrix,img,1,0);
    }
    return matrix;
}

// change matrix where "1" it is silhouettes "0" it is background
void changeMatrix(int **matrix, QImage *img, int background, int silhouette){
    for(int y = 0; y < img->height(); y++){
        for(int x = 0; x < img->width(); x++){
            int color = QColor(img->pixel(x,y)).lightness();
            if(color >= 127){
                matrix[y][x] = background;
            }else{
                matrix[y][x] = silhouette;
            }
        }
    }
}

// show array in the text file.
void showSilhouette(int ** matrix, QImage * img){

    ofstream fileWrite(".\\showSilhouette.txt");

    for(int y = 0; y < img->height(); y++){
        for(int x = 0; x < img->width(); x++){
            if(matrix[y][x] == 0){
                fileWrite << 0;
            }else{
                fileWrite << 1;
            }
        }
        fileWrite << '\n';
    }
}

