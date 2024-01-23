#define CATCH_CONFIG_MAIN // Просит Catch2 реализовать свой main, снимая эту задачу с разработчика

#include <catch2/catch.hpp>
#include "../circle/circle.h"


// Тестирование конструкторов
TEST_CASE("CircleConstructor") {
    SECTION("DefaultConstructor") {
        Prog2::Circle a1;
        REQUIRE(a1.getP().x == 0);
        REQUIRE(a1.getP().y == 0);
        REQUIRE(a1.getR() == 1);
    }
    SECTION("InitConstructors") {
        Prog2::Circle a2(3);
        Prog2::Point p(2, 3);
        REQUIRE(a2.getR() == 3);
        REQUIRE(a2.getP().x == 0);
        REQUIRE(a2.getP().y == 0);
        Prog2::Circle a3(p, 8);
        REQUIRE(a3.getP().x == 2);
        REQUIRE(a3.getP().y == 3);
        REQUIRE(a3.getR() == 8);
        Prog2::Circle a4(-4, -5, 3);
        REQUIRE(a4.getP().x == -4);
        REQUIRE(a4.getP().y == -5);
        REQUIRE(a4.getR() == 3);
    }
    SECTION("TestException") {
        Prog2::Point p;
        REQUIRE_THROWS(Prog2::Circle(2, 5, -5));
        REQUIRE_THROWS(Prog2::Circle(p, -1));
    }
}

// Тестирование других методов
TEST_CASE("CircleMethods", "Setters")
{
    SECTION("Setters") {
        Prog2::Circle a;
        Prog2::Point p1(3, 2);
        a.setP(p1);
        REQUIRE(a.getP().x == 3);
        REQUIRE(a.getP().y == 2);
        Prog2::Point p2(-3, -2);
        a.setP(p2);
        REQUIRE(a.getP().x == -3);
        REQUIRE(a.getP().y == -2);
        a.setR(2);
        REQUIRE(a.getR());
        REQUIRE_THROWS(a.setR(-1));
    }
    SECTION("Parameters") {
        Prog2::Circle a1;
        const double PI = 3.14159;
        REQUIRE(a1.area() == Approx(PI));
        REQUIRE(a1.perimeter() == Approx(2 * PI));
        REQUIRE(a1.distance() == 0);
        REQUIRE(a1.f(1).first == 0);
        REQUIRE(a1.f(1).second == 0);
        REQUIRE(a1.f(0).first == 1);
        REQUIRE(a1.f(0).second == -1);
        REQUIRE_THROWS(a1.f(2));
        REQUIRE(a1.frm() == "x ^ 2 + y ^ 2 = 1");
        Prog2::Circle a2(1, 3, 2);
        REQUIRE(a2.area() == Approx(PI * 4));
        REQUIRE(a2.perimeter() == Approx(2 * PI * 2));
        REQUIRE(a2.distance() == Approx(sqrt(10)));
        REQUIRE(a2.f(1).first == 5);
        REQUIRE(a2.f(1).second == 1);
        REQUIRE(a2.f(0).first == Approx(3 + sqrt(3)));
        REQUIRE(a2.f(0).second == Approx(3 - sqrt(3)));
        REQUIRE_THROWS(a2.f(-2));
        REQUIRE(a2.frm() == "(x - 1) ^ 2 + (y - 3) ^ 2 = 4");
    }
}
