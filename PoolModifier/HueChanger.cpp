#include <opencv2\opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <time.h>
#include <fstream>
#include <filesystem>
#include <string.h> 
#include <random>
#include <sstream>
#include <map>
#include <vector>
#define ALL_ATTS  (FA_DIREC | FA_ARCH) 

using std::cout; using std::cerr; using std::ifstream;
using std::istringstream;
using std::endl; using std::string; using std::ostringstream;
using namespace cv;
using namespace std;
namespace fs = std::filesystem;

int ironblack[769] = { 255, 255, 255,
           253, 253, 253,
           251, 251, 251,
           249, 249, 249,
           247, 247, 247,

           245, 245, 245,
           243, 243, 243,
           241, 241, 241,
           239, 239, 239,
           237, 237, 237, 235, 235, 235, 233, 233, 233, 231, 231, 231, 229, 229, 229, 227, 227, 227, 225, 225, 225, 223, 223, 223, 221, 221, 221, 219, 219, 219, 217, 217, 217, 215, 215, 215, 213, 213, 213, 211, 211, 211, 209, 209, 209, 207, 207, 207, 205, 205, 205, 203, 203, 203, 201, 201, 201, 199, 199, 199, 197, 197, 197, 195, 195, 195, 193, 193, 193, 191, 191, 191, 189, 189, 189, 187, 187, 187, 185, 185, 185, 183, 183, 183, 181, 181, 181, 179, 179, 179, 177, 177, 177, 175, 175, 175, 173, 173, 173, 171, 171, 171, 169, 169, 169, 167, 167, 167, 165, 165, 165, 163, 163, 163, 161, 161, 161, 159, 159, 159, 157, 157, 157, 155, 155, 155, 153, 153, 153, 151, 151, 151, 149, 149, 149, 147, 147, 147, 145, 145, 145, 143, 143, 143, 141, 141, 141, 139, 139, 139, 137, 137, 137, 135, 135, 135, 133, 133, 133, 131, 131, 131, 129, 129, 129, 126, 126, 126, 124, 124, 124, 122, 122, 122, 120, 120, 120, 118, 118, 118, 116, 116, 116, 114, 114, 114, 112, 112, 112, 110, 110, 110, 108, 108, 108, 106, 106, 106, 104, 104, 104, 102, 102, 102, 100, 100, 100, 98, 98, 98, 96, 96, 96, 94, 94, 94, 92, 92, 92, 90, 90, 90, 88, 88, 88, 86, 86, 86, 84, 84, 84, 82, 82, 82, 80, 80, 80, 78, 78, 78, 76, 76, 76, 74, 74, 74, 72, 72, 72, 70, 70, 70, 68, 68, 68, 66, 66, 66, 64, 64, 64, 62, 62, 62, 60, 60, 60, 58, 58, 58, 56, 56, 56, 54, 54, 54, 52, 52, 52, 50, 50, 50, 48, 48, 48, 46, 46, 46, 44, 44, 44, 42, 42, 42, 40, 40, 40, 38, 38, 38, 36, 36, 36, 34, 34, 34, 32, 32, 32, 30, 30, 30, 28, 28, 28, 26, 26, 26, 24, 24, 24, 22, 22, 22, 20, 20, 20, 18, 18, 18, 16, 16, 16, 14, 14, 14, 12, 12, 12, 10, 10, 10, 8, 8, 8, 6, 6, 6, 4, 4, 4, 2, 2, 2, 0, 0, 0, 0, 0, 9, 2, 0, 16, 4, 0, 24, 6, 0, 31, 8, 0, 38, 10, 0, 45, 12, 0, 53, 14, 0, 60, 17, 0, 67, 19, 0, 74, 21, 0, 82, 23, 0, 89, 25, 0, 96, 27, 0, 103, 29, 0, 111, 31, 0, 118, 36, 0, 120, 41, 0, 121, 46, 0, 122, 51, 0, 123, 56, 0, 124, 61, 0, 125, 66, 0, 126, 71, 0, 127, 76, 1, 128, 81, 1, 129, 86, 1, 130, 91, 1, 131, 96, 1, 132, 101, 1, 133, 106, 1, 134, 111, 1, 135, 116, 1, 136, 121, 1, 136, 125, 2, 137, 130, 2, 137, 135, 3, 137, 139, 3, 138, 144, 3, 138, 149, 4, 138, 153, 4, 139, 158, 5, 139, 163, 5, 139, 167, 5, 140, 172, 6, 140, 177, 6, 140, 181, 7, 141, 186, 7, 141, 189, 10, 137, 191, 13, 132, 194, 16, 127, 196, 19, 121, 198, 22, 116, 200, 25, 111, 203, 28, 106, 205, 31, 101, 207, 34, 95, 209, 37, 90, 212, 40, 85, 214, 43, 80, 216, 46, 75, 218, 49, 69, 221, 52, 64, 223, 55, 59, 224, 57, 49, 225, 60, 47, 226, 64, 44, 227, 67, 42, 228, 71, 39, 229, 74, 37, 230, 78, 34, 231, 81, 32, 231, 85, 29, 232, 88, 27, 233, 92, 24, 234, 95, 22, 235, 99, 19, 236, 102, 17, 237, 106, 14, 238, 109, 12, 239, 112, 12, 240, 116, 12, 240, 119, 12, 241, 123, 12, 241, 127, 12, 242, 130, 12, 242, 134, 12, 243, 138, 12, 243, 141, 13, 244, 145, 13, 244, 149, 13, 245, 152, 13, 245, 156, 13, 246, 160, 13, 246, 163, 13, 247, 167, 13, 247, 171, 13, 248, 175, 14, 248, 178, 15, 249, 182, 16, 249, 185, 18, 250, 189, 19, 250, 192, 20, 251, 196, 21, 251, 199, 22, 252, 203, 23, 252, 206, 24, 253, 210, 25, 253, 213, 27, 254, 217, 28, 254, 220, 29, 255, 224, 30, 255, 227, 39, 255, 229, 53, 255, 231, 67, 255, 233, 81, 255, 234, 95, 255, 236, 109, 255, 238, 123, 255, 240, 137, 255, 242, 151, 255, 244, 165, 255, 246, 179, 255, 248, 193, 255, 249, 207, 255, 251, 221, 255, 253, 235, 255, 255, 24,
-1 };

float color_distance[256];

int PixPosFinder(int pixel[3]) {
    int index = 0;
    int smallestindex = 0;
    int smallestdistance = 99999;
    for (int i = 0; i < 255; i++)
    {
        color_distance[i] = sqrt(pow(abs(ironblack[index] - pixel[0]), 2) +
            pow(abs(ironblack[index + 1] - pixel[1]), 2) +
            pow(abs(ironblack[index + 2] - pixel[2]), 2));
        index = i * 3;
    }
    //Cari index berapa yg jaraknya paling deket ke warna pixel
    for (int f = 0; f < 255;f++) {
        if (color_distance[f] < smallestdistance) {
            smallestdistance = color_distance[f];
            smallestindex = f;
        }
    }
    return smallestindex;
}

int partition(int* arrayku, int lo, int hi) {
    int pivot = *(arrayku + hi);
    int i = lo;
    int container = 0;
    for (int j = lo;j < hi;j++) {
        if (*(arrayku + j) < pivot) {
            container = *(arrayku + j);
            *(arrayku + j) = *(arrayku + i);
            *(arrayku + i) = container;
            i++;
        }
    }
    container = *(arrayku + i);
    *(arrayku + i) = *(arrayku + hi);
    *(arrayku + hi) = container;
    return i;
}
void quicksort(int* arrayku, int lo, int hi) {
    if (lo < hi) {
        int p = partition(arrayku, lo, hi);
        //cout<<"p: "<<p<<endl; 
        quicksort(arrayku, lo, p - 1);
        quicksort(arrayku, p + 1, hi);
    }
}

void CSVAppender(std::string csvfilename, string imagename) {
    ifstream csvpointerin(csvfilename);
    fstream csvpointerout;
    csvpointerout.open(csvfilename + "new.csv", ios::out);
    int indeximagename = 0;
    string line, word; line.clear(); word.clear();
    vector<string> row;
    string container[8]; int activate = 8;
    int firsttime = 1; int start = 0; //ada start soalnya dy kadang baca doang tp gk tulis
    while (!csvpointerin.eof()) {
        row.clear();
        getline(csvpointerin, line);
        stringstream s(line);
        if (firsttime != 1 && start == 1) { csvpointerout << "\n"; };
        while (getline(s, word, ',')) {
            if (word == "160") { start = 1; }
            csvpointerout << word << ',';
            if (word == imagename) {
                cout << endl;
                cout << "Ditemukan !!" << endl;
                activate = 0;
            }
            if (activate < 8) {
                container[activate] = word;
                activate++;
            }
            row.push_back(word);
        }
        if (firsttime == 1) { csvpointerout << "\n"; };
        firsttime = 0;
    }
    csvpointerin.close();

    container[0] = "H2ue" + container[0];
    for (int cols = 0;cols < 8;cols++) {
        if (cols < 7) { csvpointerout << container[cols] << ','; }
        if (cols == 7) { csvpointerout << container[7] << '\n'; }
    }

    csvpointerout.close();
    remove(csvfilename.c_str());
    rename((csvfilename + "new.csv").c_str(), csvfilename.c_str());
}

int* Find2Clusters(int(*arraymu), int npivot) {
    //arraymu harus udah di sortir
    int distance1 = 0;
    int distance2 = 0;
    int group1[19200] = { 0 };
    int group2[19200] = { 0 };
    int idxgroup1 = 0; int idxgroup2 = 0;
    //assign 2 arbitrary pivot
    float pivot1 = (*(arraymu + 200));
    float pivot2 = (*(arraymu + 11000));

    for (int iter = 0; iter < 6; iter++) {
        //grouping ke pivot terdekat
        idxgroup1 = 0; idxgroup2 = 0;
        for (int p = 0;p < 19200;p++) {
            distance1 = abs(*(arraymu + p) - pivot1);
            distance2 = abs(*(arraymu + p) - pivot2);
            if (distance1 > distance2) {
                group2[idxgroup2] = (*(arraymu + p));
                idxgroup2++;
            }
            else {
                group1[idxgroup1] = (*(arraymu + p));
                idxgroup1++;
            }
        }

        //calculate the means of cluster, then change the pivot accordingly
        int sum1 = 0; int sum2 = 0;
        for (int x = 0;x < idxgroup1;x++) {
            sum1 += group1[x];
        }
        for (int y = 0; y < idxgroup2;y++) {
            sum2 += group2[y];
        }
        if (idxgroup1 <= 0.001 || idxgroup2 <= 0.001) { break; }
        sum1 = sum1 / idxgroup1;
        sum2 = sum2 / idxgroup2;
        pivot1 = (sum1);
        pivot2 = (sum2);
    }
    static int pivotz[2] = { pivot1,pivot2 };
    return pivotz;
}

int* huemodifier(int(*arraymu), int pivot) {
    float scale = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 1.2 + 0.3;;
    int exception = 130;
    if (scale < 0.6) { exception = 160; };
    float maxmagnitude = 255 - pivot - (scale * exception);
    float minmagnitude = pivot - (scale * 135); //120 adalah sekitar stengahnya dari 255
    int modder = static_cast<int>(maxmagnitude - minmagnitude + 1);
    if (modder == 0) { modder = 1; }
    float magnitude = minmagnitude + (rand() % modder);

    if (maxmagnitude < -minmagnitude) { maxmagnitude = 127;minmagnitude = 127; }
    if (scale >= 1.5) { scale = 1.5; minmagnitude = 110; maxmagnitude = 150; }
    else if (scale <= 0.3) { scale = 0.3; };
    if (magnitude > maxmagnitude) { magnitude = maxmagnitude; }
    if (magnitude < -minmagnitude) { magnitude = -minmagnitude; }

    //fungsi ini memodif arraynya, di skala dengan titik yg dikunci adalah pivot
    float container = 0;
    for (int i = 0; i < 19200; i++) {
        container = ((*(arraymu + i) - pivot) * scale) + (pivot);
        container = container + (magnitude);
        if (container >= 255) {
            container = 255;
        }
        else if (container <= 0) {
            container = 0;
        }
        *(arraymu + i) = container;
    }
    return 0;
}

int main()
{
    //This program grab random images from a folder than augment it (write to csv and to another folder)
    //Integrate several augmentation or make separate project ??
    clock_t tStart = clock();
    string image_dir = ("C:/Hansel/MasterPool/Pool/");
    std::filesystem::path file[10000];
    int n = 0;
    for (const auto& entry : fs::directory_iterator(image_dir)) {
        file[n] = (entry.path());
        n++;
    };

    int counter = 0;
    int bgrPixel[160][120][3];
    int allpixpos[19200];//[CMposition][image position]

    string namafilenya = "";
    string image_path;
    vector<string> done; int doneTrue = 0; int doneindex = 0;
    for (int m = 0; m < 1083;m++) {
        image_dir.clear();
        image_dir = ("C:/Hansel/MasterPool/Pool/");

        std::random_device rd;
        std::default_random_engine eng(rd());
        std::uniform_int_distribution<int> distr(0, n);
        int indexterpilih = distr(eng);
        namafilenya = file[indexterpilih].string().substr(image_dir.length(), static_cast<int>(file[indexterpilih].string().length()));
        cout << endl;
        doneTrue = 1;

        while ((namafilenya.find("basah") != std::string::npos) ||
            (namafilenya.find("Back") != std::string::npos) ||
            (namafilenya.find("bekas") != std::string::npos) ||
            (namafilenya.find("bottle") != std::string::npos) ||
            (namafilenya.find("glass") != std::string::npos) ||
            (namafilenya.find("hp") != std::string::npos) ||
            (namafilenya.find("kontras") != std::string::npos) ||
            (namafilenya.find("Grass") != std::string::npos) ||
            (namafilenya.find("Aspal") != std::string::npos) ||
            (namafilenya.find("rokok") != std::string::npos) ||
            (doneTrue == 1))
        {
            indexterpilih = distr(eng);
            cout << "I: ", indexterpilih, "; ";
            namafilenya = file[indexterpilih].string().substr(image_dir.length(), static_cast<int>(file[indexterpilih].string().length()));
            doneTrue = 0;
            for (int b = 0; b < done.size(); b++) {
                if (namafilenya.find(done[b]) != std::string::npos) {
                    cout << "Yg ini mah udah" << endl;
                    doneTrue = 1;
                }
            }
        };
        cout << "File terpilih: " << namafilenya;
        done.push_back(namafilenya); doneindex++;

        image_path.clear();
        image_path = (image_dir.append(namafilenya));
        string target_folder_path = ("C:/Hansel/MasterPool/trial/");
        Mat img = imread(image_path, IMREAD_COLOR);
        uint8_t* pixelPtr = (uint8_t*)img.data;
        int cn = img.channels();

        for (int x = 0; x < img.rows; x++)
        {
            for (int y = 0; y < img.cols; y++)
            {
                //Get all the value into bgrPixel
                bgrPixel[y][x][0] = pixelPtr[x * img.cols * cn + y * cn + 0]; // B
                bgrPixel[y][x][1] = pixelPtr[x * img.cols * cn + y * cn + 1]; // G
                bgrPixel[y][x][2] = pixelPtr[x * img.cols * cn + y * cn + 2]; // R
                // do something with BGR values...
            }
        }
        //as bgrPixel is now filled with pixel datas
        int clrindex = 0;
        int pixelcolor[3];
        for (int i = 0; i < img.rows; i++)
        {
            for (int j = 0; j < img.cols; j++)
            {
                for (int y = 0; y < 3; y++) {
                    pixelcolor[y] = bgrPixel[j][i][abs(2 - y)];
                }
                //Masukkan semua "Posisi di colormap" pixels ke allpixpos
                clrindex = PixPosFinder(pixelcolor); //Tambahkan secara manual
                allpixpos[(img.cols * i) + j] = clrindex;
                bgrPixel[j][i][0] = ironblack[clrindex * 3 + 2];
                bgrPixel[j][i][1] = ironblack[clrindex * 3 + 1];
                bgrPixel[j][i][2] = ironblack[clrindex * 3 + 0];

                //Langsung timpa
                pixelcolor[0] = bgrPixel[j][i][2];
                pixelcolor[1] = bgrPixel[j][i][1];
                pixelcolor[2] = bgrPixel[j][i][0];
                for (int u = 0; u < 3;u++) {
                    img.at<Vec3b>(Point(j, i))[u] = pixelcolor[2 - u];
                }
            }
        }
        //quicksort(allpixpos, 0, 19200 - 1);

        //imwrite("C:/Hansel/IsolatedEnv/post-13.jpg", img);
        printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

        //quicksort(arrtest, 0, size - 1);
        //for (int i = 0; i < 19200; i+=160) {
        //    cout << allpixpos[0][i] << endl;
        //}
        int* ptrpivotz;
        ptrpivotz = Find2Clusters(allpixpos, 2); //the output is an array called "pivotz"

        //TODO: do something wth background after succesfully find clusters
        //okay
        huemodifier(allpixpos, *(ptrpivotz + 1));

        for (int i = 0; i < img.rows; i++)
        {
            for (int j = 0; j < img.cols; j++)
            {
                //if ((allpixpos[(i*img.cols)+j] > ((*(ptrpivotz + 1)) - 5)) && (allpixpos[(i * img.cols) + j] < ((*(ptrpivotz + 1)) + 5))) {
                pixelcolor[0] = ironblack[allpixpos[(i * img.cols) + j] * 3 + 0];
                pixelcolor[1] = ironblack[allpixpos[(i * img.cols) + j] * 3 + 1];
                pixelcolor[2] = ironblack[allpixpos[(i * img.cols) + j] * 3 + 2];
                //}
                //else {
                //    pixelcolor[0] = 0;
                //    pixelcolor[1] = 0;
                //    pixelcolor[2] = 0;
                //}

                for (int u = 0; u < 3;u++) {
                    img.at<Vec3b>(Point(j, i))[u] = pixelcolor[2 - u];
                }
            }
        }
        string finalpath = "C:/Hansel/MasterPool/trial/";
        finalpath.append("H2ue" + namafilenya);
        CSVAppender(("C:/Hansel/MasterPool/TdrMixPool_labels.csv"), namafilenya);
        imwrite(finalpath, img);
    }
}
