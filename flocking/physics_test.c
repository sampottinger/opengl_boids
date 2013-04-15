/**
 * Name: physics_test.c
 * Desc: Unit tests for physics / linear algebra logic.
 * Auth: Sam Pottinger
 * Licn: GNU GPL v2
**/

#include "clockmac.c"
#include "minunit.h"
#include "physics.h"

#include <math.h>

MU_TEST(test_vector)
{
    float length;
    float otherLength;

    PhysicsVector v1;
    PhysicsVector v2;
    PhysicsVector v3;
    PhysicsVector v4;
    PhysicsVector v5;
    PhysicsVector v6;
    PhysicsVector v7;
    PhysicsVector v8;

    PhysicsVector ans1;
    PhysicsVector ans2;
    PhysicsVector ans3;
    PhysicsVector ans4;

    PhysicsVector * v1ptr = &v1;
    PhysicsVector * v2ptr = &v2;
    PhysicsVector * v3ptr = &v3;
    PhysicsVector * v4ptr = &v4;
    PhysicsVector * v5ptr = &v5;
    PhysicsVector * v6ptr = &v6;
    PhysicsVector * v7ptr = &v7;
    PhysicsVector * v8ptr = &v8;

    PhysicsVector * ans1ptr = &ans1;
    PhysicsVector * ans2ptr = &ans2;
    PhysicsVector * ans3ptr = &ans3;
    PhysicsVector * ans4ptr = &ans4;

    // Test equality
    PhysicsVector_init(v1ptr, 1, 2, 3);
    PhysicsVector_init(v2ptr, 1, 2, 3);
    PhysicsVector_init(v3ptr, 7, 8, 9);
    mu_check(PhysicsVector_eq(v1ptr, v2ptr, 0.005));
    mu_check(!PhysicsVector_eq(v1ptr, v3ptr, 0.005));

    // Test add
    PhysicsVector_init(v1ptr, 1, 2, 3);
    PhysicsVector_init(v2ptr, 4, 5, 6);
    PhysicsVector_init(v3ptr, 7, 8, 9);
    PhysicsVector_init(v4ptr, 10, 11, 12);
    PhysicsVector_init(v5ptr, -1, -2, -3);

    PhysicsVector_add(v1ptr, v2ptr, v3ptr);
    PhysicsVector_add(v2ptr, v2ptr, v3ptr);
    PhysicsVector_add(v3ptr, v3ptr, v3ptr);

    PhysicsVector_init(ans1ptr, 11, 13, 15);
    PhysicsVector_init(ans2ptr, 11, 13, 15);
    PhysicsVector_init(ans3ptr, 14, 16, 18);
    mu_check(PhysicsVector_eq(ans1ptr, v1ptr, 0.005));
    mu_check(PhysicsVector_eq(ans2ptr, v2ptr, 0.005));
    mu_check(PhysicsVector_eq(ans3ptr, v3ptr, 0.005));

    // Test subtract
    PhysicsVector_init(v1ptr, 1, 2, 3);
    PhysicsVector_init(v2ptr, 4, 6, 8);
    PhysicsVector_init(ans1ptr, -3, -4, -5);
    PhysicsVector_sub(v3ptr, v1ptr, v2ptr);
    mu_check(PhysicsVector_eq(ans1ptr, v3ptr, 0.005));

    // Test multiply
    PhysicsVector_init(ans1ptr, -10, -22, -36);
    PhysicsVector_mult(v1ptr, v5ptr, v4ptr);
    mu_check(PhysicsVector_eq(ans1ptr, v1ptr, 0.005));

    // Test divide
    PhysicsVector_div(v1ptr, v1ptr, v4ptr);
    mu_check(PhysicsVector_eq(v1ptr, v5ptr, 0.005));

    // Test multiply scalar
    PhysicsVector_init(ans2ptr, 2, 4, 6);
    PhysicsVector_multScalar(v2ptr, v5ptr, -2);
    mu_check(PhysicsVector_eq(ans2ptr, v2ptr, 0.005));

    // Test divide scalar
    PhysicsVector_divScalar(v2ptr, v2ptr, -2);
    mu_check(PhysicsVector_eq(v5ptr, v2ptr, 0.005));

    // Test length
    PhysicsVector_init(v6ptr, 1, 2, 3);
    length = PhysicsVector_length(v6ptr);
    mu_check(fabs(sqrt(14) - length) < 0.000005);

    // Test distance vector
    PhysicsVector_init(v7ptr, 4, 8, 12);
    PhysicsVector_init(ans4ptr, -3, -6, -9);
    PhysicsVector_distVector(v8ptr, v6ptr, v7ptr);
    mu_check(PhysicsVector_eq(ans4ptr, v8ptr, 0.005));

    // Test distance
    length = PhysicsVector_dist(v6ptr, v7ptr);
    otherLength = PhysicsVector_length(v8ptr);
    mu_check(fabs(otherLength - length) < 0.000005);

    // Test normalize
    PhysicsVector_init(v1ptr, 10, 20, 2);
    PhysicsVector_init(ans1ptr, 0.4454354, 0.8908708, 0.089087084);
    PhysicsVector_normalize(v2ptr, v1ptr);
    mu_check(PhysicsVector_eq(ans1ptr, v2ptr, 0.005));

    // Test limit
    PhysicsVector_init(v1ptr, 10, 20, 2);
    PhysicsVector_init(ans1ptr, 2.2271771, 4.4543543, 0.4454354);
    PhysicsVector_limit(v2ptr, v1ptr, 5);
    mu_check(PhysicsVector_eq(ans1ptr, v2ptr, 0.005));
}

MU_TEST(test_object)
{
    PhysicsObject obj;
    PhysicsObject * objPtr = &obj;

    PhysicsVector v1;
    PhysicsVector v2;
    PhysicsVector v3;
    PhysicsVector zeros;

    PhysicsVector ans1;
    PhysicsVector ans2;
    PhysicsVector ans3;

    PhysicsVector * v1ptr = &v1;
    PhysicsVector * v2ptr = &v2;
    PhysicsVector * v3ptr = &v3;
    PhysicsVector * zerosPtr = &zeros;

    PhysicsVector * ans1ptr = &ans1;
    PhysicsVector * ans2ptr = &ans2;
    PhysicsVector * ans3ptr = &ans3;

    PhysicsVector_init(v1ptr, 1, 2, 3);
    PhysicsVector_init(v2ptr, 4, 5, 6);
    PhysicsVector_init(v3ptr, 7, 8, 9);
    PhysicsVector_init(zerosPtr, 0, 0, 0);

    PhysicsObject_init(objPtr, 2, 1, 2, 3);

    mu_check(PhysicsVector_eq(&(objPtr->position), v1ptr, 0.005));
    mu_check(PhysicsVector_eq(&(objPtr->acceleration), zerosPtr, 0.005));
    mu_check(PhysicsVector_eq(&(objPtr->velocity), zerosPtr, 0.005));

    PhysicsObject_addForce(objPtr, v2ptr);
    PhysicsVector_init(ans1ptr, 8, 10, 12);
    mu_check(PhysicsVector_eq(&(objPtr->acceleration), ans1ptr, 0.005));

    PhysicsObject_addForce(objPtr, v3ptr);
    PhysicsVector_init(ans2ptr, 22, 26, 30);
    mu_check(PhysicsVector_eq(&(objPtr->acceleration), ans2ptr, 0.005));

    PhysicsObject_updateVelocity(objPtr, 2);
    PhysicsVector_init(ans3ptr, 44, 52, 60);
    mu_check(PhysicsVector_eq(&(objPtr->velocity), ans3ptr, 0.005));
}

MU_TEST_SUITE(test_physics)
{
    MU_RUN_TEST(test_vector);
    MU_RUN_TEST(test_object);
}

int main(int argc, char * argv[])
{
    MU_RUN_SUITE(test_physics);
    MU_REPORT();

    return 0;
}