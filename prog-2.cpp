#include <iostream>
#include <string>
#include <cassert>

class vec
{
public:
    float data[3];

    float& operator[](size_t i)
    {
        return data[i];
    }

    const float& operator[](size_t i) const
    {
        return data[i];
    }
};

class object
{
public:
    std::string name;
    object() : name("") {}

    virtual ~object() {} //makes this class polymorphic
};

class sphere : public object
{
public:
    vec center;
    double radius;
    sphere() : center({0, 0, 0}), radius(0) {}
};

class point : public object
{
public:
    vec location;
    point() : location({0, 0, 0}) {}
};

void set_names(object** objects, size_t number_objects, const std::string& base_name)
{
    //std::cout << "number_objects is " << number_objects << std::endl;
    for(size_t i = 0; i < number_objects; i++)
    {
        //std::cout << "i is " << i << std::endl;
        std::string temp = base_name + std::to_string(i);
        objects[i]->name = temp;
    }
}

int main()
{
    object** balls  = new object*[10];
    object** points = new object*[10];

    vec origin;
    for(size_t i = 0; i < 3; i++)
        origin[i] = 0;

    for(size_t i = 0; i < 10; i++) {

      balls[i] = new sphere;
      points[i] = new point;
    }

    for(size_t i = 0; i < 10; i++)
    {
        sphere* temp_sphere = dynamic_cast<sphere*> (balls[i]);
        assert(temp_sphere != nullptr);

        temp_sphere->center = origin;
        temp_sphere->radius = 0.1 * (i + 1);



        point*  temp_point  = dynamic_cast<point*> (points[i]);
        assert(temp_point != nullptr);

        temp_point->location = origin;
        temp_point->location[0] = 0.2 * i;
    }

    set_names(balls, 10, "ball-");
    set_names(points, 10, "point-");

    for(size_t i = 0; i < 10; i++)
    {
        std::cout << balls[i]->name << " " << points[i]->name << std::endl;
    }


    for(size_t i = 0; i < 10; i++) {
      delete balls[i];
      delete points[i];
    }
    delete [] balls;
    delete [] points;

    return 0;
}
