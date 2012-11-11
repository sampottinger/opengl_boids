#include "clockmac.c"
#include "minunit.h"
#include "boid.h"
#include "physics.h"

MU_TEST(test_init)
{
    Boid testBoid;
    PhysicsVector ans;
    PhysicsVector * positionVectorPtr;
    Boid * testBoidPtr = &testBoid;
    PhysicsVector * ansPtr = &ans;

    Boid_init(testBoidPtr, 1, 2, 3);

    positionVectorPtr = &(testBoid.physicsObject.position);
    PhysicsVector_init(ansPtr, 1, 2, 3);
    mu_check(PhysicsVector_eq(positionVectorPtr, ansPtr, 0.00005));

    mu_check(testBoid.minX == BOID_MIN_X);
    mu_check(testBoid.minY == BOID_MIN_Y);
    mu_check(testBoid.minZ == BOID_MIN_Z);
    mu_check(testBoid.maxX == BOID_MAX_X);
    mu_check(testBoid.maxY == BOID_MAX_Y);
    mu_check(testBoid.maxZ == BOID_MAX_Z);
}

MU_TEST(test_step)
{

}

MU_TEST(test_respondToFlock)
{

}

MU_TEST(test_calculateSeperation)
{
    PhysicsVector ans;
    Boid boids[3];

    PhysicsVector * ansPtr = &ans;
    Boid * b1ptr = &boids[0];
    Boid * b2ptr = &boids[1];
    Boid * b3ptr = &boids[2];
    PhysicsVector * accelerationPtr = &(b3ptr->physicsObject.acceleration);

    Boid_init(b1ptr, 5, 10, 0);
    Boid_init(b2ptr, 10, 4, 0);
    Boid_init(b3ptr, 10, 10, 0);

    Boid_calculateSeperation(b3ptr, (Boid *)(&boids), 3, 2);

    PhysicsVector_init(ansPtr, 0.076822124, 0.06401844, 0);
    mu_check(PhysicsVector_eq(accelerationPtr, ansPtr, 0.000005));
}

MU_TEST(test_calculateAlign)
{
    PhysicsVector ans;
    Boid boids[3];

    PhysicsVector * ansPtr = &ans;
    Boid * b1ptr = &boids[0];
    Boid * b2ptr = &boids[1];
    Boid * b3ptr = &boids[2];
    PhysicsVector * accelerationPtr = &(b3ptr->physicsObject.acceleration);

    Boid_init(b1ptr, 5, 10, 0);
    Boid_init(b2ptr, 10, 4, 0);
    Boid_init(b3ptr, 10, 10, 0);

    b1ptr->physicsObject.velocity.x = 1;
    b1ptr->physicsObject.velocity.y = 2;
    b2ptr->physicsObject.velocity.x = 3;
    b2ptr->physicsObject.velocity.y = 4;

    Boid_calculateAlign(b3ptr, (Boid *)(&boids), 3, 2);

    PhysicsVector_init(ansPtr, 0.05547002, 0.08320503, 0);
    mu_check(PhysicsVector_eq(accelerationPtr, ansPtr, 0.000005));
}

MU_TEST(test_calculateCohesion)
{
    PhysicsVector ans;
    Boid boids[3];

    PhysicsVector * ansPtr = &ans;
    Boid * b1ptr = &boids[0];
    Boid * b2ptr = &boids[1];
    Boid * b3ptr = &boids[2];
    PhysicsVector * accelerationPtr = &(b3ptr->physicsObject.acceleration);

    Boid_init(b1ptr, 5, 10, 0);
    Boid_init(b2ptr, 10, 4, 0);
    Boid_init(b3ptr, 10, 10, 0);

    Boid_calculateCohesion(b3ptr, (Boid *)(&boids), 3, 2);

    PhysicsVector_init(ansPtr, -0.06401844, -0.076822124, 0);
    mu_check(PhysicsVector_eq(accelerationPtr, ansPtr, 0.000005));
}

MU_TEST(test_steerTowardsLocation)
{
    PhysicsVector ans;
    PhysicsVector center;
    Boid testBoid;

    PhysicsVector * ansPtr = &ans;
    PhysicsVector * centerPtr = &center;
    Boid * testBoidPtr = &testBoid;
    PhysicsVector * accelerationPtr = 
        &(testBoidPtr->physicsObject.acceleration);

    Boid_init(testBoidPtr, 10, 10, 0);
    PhysicsVector_init(centerPtr, 5, 7, 0);

    Boid_steerTowardsLocation(testBoidPtr, centerPtr, 2);

    PhysicsVector_init(ansPtr, -0.08574929, -0.051449574, 0);
    mu_check(PhysicsVector_eq(accelerationPtr, ansPtr, 0.000005));
}

MU_TEST(test_updatePosition)
{

}

MU_TEST(test_wrapOnBorders)
{

}

MU_TEST_SUITE(test_boid)
{
    MU_RUN_TEST(test_init);
    MU_RUN_TEST(test_step);
    MU_RUN_TEST(test_respondToFlock);
    MU_RUN_TEST(test_calculateSeperation);
    MU_RUN_TEST(test_calculateAlign);
    MU_RUN_TEST(test_calculateCohesion);
    MU_RUN_TEST(test_steerTowardsLocation);
    MU_RUN_TEST(test_updatePosition);
    MU_RUN_TEST(test_wrapOnBorders);
}

int main(int argc, char * argv[])
{
    MU_RUN_SUITE(test_boid);
    MU_REPORT();

    return 0;
}
