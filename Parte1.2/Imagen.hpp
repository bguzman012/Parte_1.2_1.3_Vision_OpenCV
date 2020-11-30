#include <cstring>
#include <iostream>
#include <cstdlib>
#include <opencv2/core/core.hpp>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>
#include <cmath>
#include <stdlib.h>
#include <ctime>

using namespace std;
using namespace cv;


class Imagen
{

public:
    void leerImagen(string = "Default");
    vector<string> leerDirectorios(string);
    vector<Mat> readImagenes(vector<string>, string);
    vector<Mat> calcularHistogramas(vector<Mat>);
    vector<int> clasificarImagenes(vector<Mat>, vector<Mat>, vector<Mat>, vector<Mat>);
    vector<int> getPrecision(vector<int>, int);
    float getPorcentajePrecision(vector<int>);

    //listagrises

    vector<Mat> convertirEscalaGris(vector<Mat>);
    vector<Mat> calcularHistogramasGrises(vector<Mat>);
    vector<int> clasificarImagenesGrises(vector<Mat>, vector<Mat>, vector<Mat>, vector<Mat>);

    //listasHSV

    vector<Mat> convertirHSV(vector<Mat>);

private:
    float calcularDistancia(vector<Mat>, vector<Mat>);
    float calcularDistanciaGrises(vector<Mat>, vector<Mat>);
};
