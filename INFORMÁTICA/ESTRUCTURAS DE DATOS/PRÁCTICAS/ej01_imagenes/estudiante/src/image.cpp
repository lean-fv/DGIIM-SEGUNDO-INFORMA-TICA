/**
 * @file image.cpp
 * @brief Fichero con definiciones para los métodos primitivos de la clase Image
 *
 */

#include <cstring>
#include <cassert>
#include <iostream>

#include <image.h>
#include <imageIO.h>
#include <cmath>

using namespace std;

/************
      FUNCIONES PRIVADAS
************/
void Image::Allocate(int nrows, int ncols, byte * buffer){
    rows = nrows;
    cols = ncols;

    img = new byte * [rows];
    for (int i=0; i < rows; i++)
        img[i] = new byte [cols];

    if (buffer != 0) {
        for (int j = 0; j < rows * cols; j++)
            set_pixel(j, buffer[j]);
    }
}

// Función auxiliar para inicializar imágenes con valores por defecto o a partir de un buffer de datos
void Image::Initialize (int nrows, int ncols, byte * buffer){
    if ((nrows == 0) || (ncols == 0)){
        rows = cols = 0;
        img = 0;
    }
    else Allocate(nrows, ncols, buffer);
}

// Función auxiliar para copiar objetos Imagen

void Image::Copy(const Image & orig){
    Initialize(orig.rows,orig.cols);
    for (int k=0; k<rows*cols;k++)
        set_pixel(k,orig.get_pixel(k));
}

// Función auxiliar para destruir objetos Imagen
bool Image::Empty() const{
    return (rows == 0) || (cols == 0);
}

void Image::Destroy(){
    if (!Empty()){
        for (int i=0; i<rows; ++i)
            delete [] img[i];
        delete [] img;
    }
    img = nullptr;
}

LoadResult Image::LoadFromPGM(const char * file_path){
    if (ReadImageKind(file_path) != IMG_PGM)
        return LoadResult::NOT_PGM;

    byte * buffer = ReadPGMImage(file_path, rows, cols);
    if (!buffer)
        return LoadResult::READING_ERROR;

    Initialize(rows, cols, buffer);
    return LoadResult::SUCCESS;
}

/************
       FUNCIONES PÚBLICAS
************/

// Constructor por defecto

Image::Image(){
    Initialize();
}

// Constructores con parámetros
Image::Image (int nrows, int ncols, byte value){
    Initialize(nrows, ncols);
    for (int k=0; k<rows*cols; k++) set_pixel(k,value);
}

bool Image::Load (const char * file_path) {
    Destroy();
    return LoadFromPGM(file_path) == LoadResult::SUCCESS;
}

// Constructor de copias

Image::Image (const Image & orig){
    assert (this != &orig);
    Copy(orig);
}

// Destructor

Image::~Image(){
    Destroy();
}

// Operador de Asignación

Image & Image::operator= (const Image & orig){
    if (this != &orig){
        Destroy();
        Copy(orig);
    }
    return *this;
}

// Métodos de acceso a los campos de la clase

int Image::get_rows() const {
    return rows;
}

int Image::get_cols() const {
    return cols;
}

int Image::size() const{
    return get_rows()*get_cols();
}

// Métodos básicos de edición de imágenes
void Image::set_pixel (int i, int j, byte value) {
    img[i][j] = value;
}
byte Image::get_pixel (int i, int j) const {
    return img[i][j];
}

// This doesn't work if representation changes
void Image::set_pixel (int k, byte value) {
    // TODO this makes assumptions about the internal representation
    // TODO Can you reuse set_pixel(i,j,value)?
    set_pixel(k/cols,k%cols, value);
}

// This doesn't work if representation changes
byte Image::get_pixel (int k) const {
    // TODO this makes assumptions about the internal representation
    // TODO Can you reuse get_pixel(i,j)?
    return get_pixel(k/cols,k%cols);
}

// Métodos para almacenar y cargar imagenes en disco
bool Image::Save (const char * file_path) const {
    // TODO this makes assumptions about the internal representation

    byte * p = new byte [rows*cols];
    for (int i = 0; i < rows*cols; ++i)
        p[i]= get_pixel(i);

    return WritePGMImage(file_path, p, rows, cols);
}

Image Image::Crop(int nrow, int ncol, int height, int width) const {

    assert (nrow >= 0 && nrow <= rows && ncol >= 0 && ncol <= cols && height*width <= rows*cols);

    Image resultado(height, width);

    for(int i=0; i < height; i++)
        for(int j=0; j < width; j++)
            resultado.set_pixel(i,j, get_pixel(nrow+i, ncol+j));

    return resultado;
}

double Image::Mean(int row, int col, int height, int width) const {

    int sum=0;
    for (int i=0; i<height; i++)
        for (int j=0; j<width; j++)
            sum+=(int)get_pixel(i+row,j+col);

    return 1.0*sum/(height*width);
}


Image Image::Zoom2X() const{

    Image zoom_img((rows * 2) - 1, (cols * 2) - 1);

    for(int i=0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            zoom_img.set_pixel(2*i,2*j, get_pixel(i,j));
        }
    }

    for(int i=0; i < zoom_img.rows; i++) {
        for(int j=0; j < zoom_img.cols; j++) {

            if (i%2==0) {
                if (j % 2 != 0) {
                    zoom_img.set_pixel(i, j,round(((zoom_img.get_pixel(i, j+1) + zoom_img.get_pixel(i, j-1))/2.0)));
                }
            }

            else {
                if(j%2==0) {
                    zoom_img.set_pixel(i,j,round((zoom_img.get_pixel(i+1,j)+ zoom_img.get_pixel(i-1,j))/2.0));
                }
                else {
                    zoom_img.set_pixel(i,j, round(((zoom_img.get_pixel(i+1,j+1) + zoom_img.get_pixel(i-1,j-1) + zoom_img.get_pixel(i-1,j+1) + zoom_img.get_pixel(i+1,j-1))/4.0)));
                }
            }
        }
    }

    return zoom_img;

}

Image Image::Subsample(int factor) const {

    assert (factor > 0);

    int dimension= rows / factor;
    Image subsample(dimension, dimension);

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {

            subsample.set_pixel(i,j,round(Mean(i*factor,j*factor,factor, factor)));
        }
    }

    return subsample;
}

void Image::AdjustContrast (byte in1, byte in2, byte out1, byte out2){

    assert (0<=in1 && 0<=in2 && 0<=out1 && 0<=out2 && 255>=in1 && 255>=in2 && 255>=out1 && 255>=out2 && in1<in2 && out1<out2);

    const double factor1= 1.0*out1/in1;
    const double factor2= 1.0*(out2-out1)/(in2-in1);
    const double factor3= 1.0*(255-out2)/(255-in2);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int byte_ij=get_pixel(i,j);

            if (0 <= byte_ij && byte_ij < in1)        set_pixel(i,j,round(factor1*(byte_ij)));
            else if(in1 <= byte_ij && byte_ij <= in2) set_pixel(i,j,round(out1+factor2*(byte_ij-in1)));
            else                                      set_pixel(i,j,round(out2+factor3*(byte_ij-in2)));
        }
    }
}

void Image:: Invert(){
    for (int i=0; i<rows; i++)
        for (int j=0; j<cols; j++)
            set_pixel(i,j,255-get_pixel(i,j));
}

void Image:: ShuffleRows(){
    const int p = 9973;
    int newr;

    byte ** aux = new byte * [rows];

    for (int j=0; j < rows; ++j)
        aux[j]=img[j];

    for (int r=0; r < rows; ++r){
        newr = r*p % rows;
        img[r]=aux[newr];
    }
    delete [] aux;
    aux = nullptr;
}


