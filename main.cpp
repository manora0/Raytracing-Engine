//
// Created by marco on 10/10/2025.
//

#include <iostream>
#include <fstream>
using namespace std;

int main() {
    string filename = "image.ppm";
    ofstream outfile(filename);
    
    clog << "Reading from: " << filename << "\n";

    int image_width = 256;
    int image_height = 256;

    outfile << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int i = 0; i < image_height; i++){
        clog << "Reading line: " << i << " " << "Remaining: "<< image_height - i << "\n";
        for (int j = 0; j < image_width; j++){
            
            auto r = double(i) / (image_width - 1);
            auto g = double(j) / (image_height - 1);
            auto b = 0.0;

            int ir = int(255.999 * r);
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);

            outfile << ir << " " << ig << " " << ib << '\n';
        }
    }

    clog << "Closing...";
    outfile.close();
    return 0;
}