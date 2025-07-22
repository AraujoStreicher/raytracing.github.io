//==============================================================================================
// Originally written in 2016 by Peter Shirley <ptrshrl@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication
// along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==============================================================================================

#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"


int main() {
    hittable_list world;

    //chão
    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

    //o círculo do rosto
    for (int i = 0; i < 25; i++) { //add as bolinhas em círculo
        double angle = 2 * pi * i/ 25;
        double x = cos(angle);
        double z = sin(angle);

        x += random_double(-0.1, 0.1); //coloca um ruído p ficar - certinho
        z += random_double(-0.1, 0.1);

        //seleciona um material aleatório pro rosto
        shared_ptr<material> face_material;
        auto choose_mat = random_double();

        if (choose_mat < 0.8) { //difuso
            auto albedo = color::random() * color::random();
            face_material = make_shared<lambertian>(albedo);
        } else if (choose_mat < 0.95) { //metal
            auto albedo = color::random(0.5, 1);
            auto fuzz = random_double(0, 0.5);
            face_material = make_shared<metal>(albedo, fuzz);
        } else { //vidro
            face_material = make_shared<dielectric>(1.5);
        }

        //add na cena 
        world.add(make_shared<sphere>(point3(x, 0.01, z), 0.1, face_material));
    }

    // os olhinhos
    auto eye_material   = make_shared<lambertian>(color(0.05, 0.05, 0.05));   // pretinho

    world.add(make_shared<sphere>(point3(-0.3, 0.11, -0.25), 0.1, eye_material)); // olho esquerdo
    world.add(make_shared<sphere>(point3( 0.3, 0.11, -0.25), 0.1, eye_material)); // olho direito

    // boca
    auto mouth_material = make_shared<lambertian>(color(0.3, 0.0, 0.0));  // vermelho
    int n_mouth = 8;
    double y = 0.01;
    for (int i = 0; i < n_mouth; ++i) { // add bolinhas em arco
        double theta = pi / (n_mouth - 1) * i;  
        double x = 0.4 * cos(theta);
        double z = 0.3 + 0.4 * sin(theta);
        world.add(make_shared<sphere>(point3(x, y, z), 0.1, mouth_material));
    }

    camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 960;
    cam.samples_per_pixel = 100;
    cam.max_depth         = 50;

    //alterei a câmera pra olhar de cima e tirei o desfoque
    cam.vfov     = 30;
    cam.lookfrom = point3(0, 5, 1.5);
    cam.lookat   = point3(0, 0, 0);
    cam.vup      = vec3(0, 0, -1);

    cam.defocus_angle = 0;
    cam.focus_dist    = 10.0;

    cam.render(world);
}
