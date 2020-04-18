#include <iostream>
#include <string>

#include <mpxx/mstruct.hpp>

struct my_fields
{
    std::string value;
};

namespace fields
{

    MPXX_FIELDS(
        (std::size_t, counter),
        (bool, valid),
        (std::string, label),
        (std::string, label2),
        (double, avg),
        (my_fields, toto)
    );

}    //namespace fields

MPXX_STRUCT(
    my_struct,
    (fields::counter),
    (fields::label),
    (fields::toto)
);

int main(int argc, char** argv)
{
    my_struct m;

    m.counter = 0;
    m.label = "toto";
    m.toto.value = "prout";

    std::cout << m.describe() << std::endl;
}
